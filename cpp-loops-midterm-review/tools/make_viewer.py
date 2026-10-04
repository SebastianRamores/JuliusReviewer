#!/usr/bin/env python3
"""
make_viewer.py
==============

Builds a browsable HTML study viewer for every .cpp file in the project.

WHAT IT PRODUCES
----------------
    viewer/
      index.html              dashboard: overview + folder cards + progress
      assets/viewer.css       stylesheet (design tokens, light + dark)
      assets/viewer.js        behaviour (highlight, fold, search, trainer)
      assets/data.js          ALL project data: folder metadata, per-file
                             metadata and the FULL source of every file
      <folder>/<name>.html    one self-describing page per .cpp file

WHY ONE PAGE PER FILE
---------------------
The brief is to study ONE concept at a time, so every file gets its own page
with its own address, its own progress tick and its own prev/next links. The
pages share assets only.

WHY EVERYTHING IS GENERATED
---------------------------
The viewer must never drift out of sync with the .cpp files. Parsing the real
sources on every run means the HTML can be regenerated after editing any
example and will always be correct.

USAGE
-----
    python3 tools/make_viewer.py
"""

import html
import json
import os
import re
import shutil
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
VIEWER = os.path.join(ROOT, 'viewer')

# Folder id -> (display title, one-line description, open by default?)
FOLDER_META = {
    '01_fundamentals': ('Fundamentals',
                        'The ten smallest loops. Start here if a for loop still '
                        'looks strange. Includes the deep anatomy file.'),
    '02_for_loops': ('for Loops',
                     'Every variation of the for header: start value, end '
                     'condition, step size, two counters, braces.'),
    '03_while_and_do_while': ('while and do...while',
                              'The other two loop forms and how they differ '
                              'from for.'),
    '04_counters_and_accumulators': ('Counters and Accumulators',
                                      'The two ideas behind almost every '
                                      'exam loop: count things, and add things '
                                      'up.'),
    '05_conditions_inside_loops': ('Conditions Inside Loops',
                                   'if / else placed inside a loop, plus '
                                   'largest, smallest and divisibility tests.'),
    '06_break_and_continue': ('break and continue',
                              'The two keywords that leave a loop early, and '
                              'how to tell them apart under exam pressure.'),
    '07_nested_loops': ('Nested Loops',
                        'A loop inside a loop. How to count executions and '
                        'trace them on paper.'),
    '08_patterns': ('Patterns',
                    'Printing stars and numbers. Learn to derive the code from '
                    'the picture, not memorise it.'),
    '09_input_and_problem_solving': ('Input and Problem Solving',
                                     'Real programs that read from the keyboard '
                                     'and answer a question.'),
    '10_number_problems': ('Number Problems',
                            'Factorial, reverse, palindrome, primes, '
                            'Fibonacci, digit sum, GCD.'),
    '11_loop_tracing': ('Loop Tracing',
                        'The exam skill of predicting output. Every file has a '
                        'full trace table and a row-by-row trainer.'),
    '12_common_mistakes': ('Common Mistakes',
                           'Deliberately broken code: what is wrong, what '
                           'happens, and the fix.'),
    '13_exam_practice': ('Exam Practice',
                         'Questions first, solution after a clear divider. Try '
                         'before you scroll.'),
    '14_challenges': ('Challenges',
                      'Longer programs that combine input, loops, conditions, '
                      'modulo, counters and accumulators.'),
}

# Section names (uppercase) -> which card they land in
CARD_TEACH = {'WHAT THIS PROGRAM TEACHES', 'CONCEPTS USED', 'CONCEPTS',
              'TOPICS COVERED', 'WHAT YOU SHOULD IDENTIFY'}
CARD_SYNTAX = {'IMPORTANT SYNTAX', 'SYNTAX', 'KEY SYNTAX', 'KEYWORDS USED',
               'IMPORTANT CONCEPTS', 'SYNTAX USED'}
CARD_STEPS = {'STEP-BY-STEP EXPLANATION', 'HOW IT WORKS', 'EXPLANATION',
              'STEP BY STEP', 'WHAT HAPPENS', 'STEP-BY-STEP EXECUTION ORDER'}
CARD_QUESTIONS = {'EXAM QUESTIONS', 'EXAM QUESTIONS:', 'QUESTIONS',
                  'SELF-TEST QUESTIONS'}
CARD_OUT = {'EXPECTED OUTPUT', 'EXPECTED OUTPUT:', 'SAMPLE OUTPUT',
            'SAMPLE INPUT', 'SAMPLE RUN'}

HEAD_RE = re.compile(r'^[A-Z][A-Z0-9 \'/&+()#._-]{2,}:?\s*$')
RULE_RE = re.compile(r'^\s*[-=]{3,}\s*$')
BORDER_RE = re.compile(r'^\s*(?://\s*)?\+-[-+]+\+\s*$')
ROW_RE = re.compile(r'^\s*(?://\s*)?\|.*\|\s*$')


def strip_comment_mark(line):
    """Remove a leading `//` or `/*` style marker so comment text can be
    matched by the same regexes whether or not the file has been folded."""
    s = line.strip()
    s = re.sub(r'^//\s?', '', s)
    s = re.sub(r'^/\*\+?', '', s)
    s = re.sub(r'\*+/\s*$', '', s)
    return s.rstrip()


def clean_title(t):
    """Trim the trailing remark some PROGRAM: lines carry.

    "Anatomy of a for Loop  (DEEP-DIVE FILE - memorise this)" reads badly as a
    page heading, so the parenthetical remark is moved out of the title.
    """
    t = re.sub(r'\s*[(\[][^)\]]*(?:memorise|DEEP[- ]DIVE)[^)\]]*[)\]]',
               '', t, flags=re.I)
    t = re.sub(r'\s*[-–—]\s*$', '', t).strip()
    return t or 'Untitled example'


def parse_header(lines):
    """Pull PROGRAM / TOPIC / DIFFICULTY out of the leading comment block."""
    meta = {'program': '', 'topic': '', 'difficulty': ''}
    for ln in lines[:60]:
        t = strip_comment_mark(ln)
        m = re.match(r'^(PROGRAM|TOPIC|DIFFICULTY|LEVEL)\s*:\s*(.+)$', t)
        if m:
            key = m.group(1).lower()
            if key in meta:
                meta[key] = m.group(2).strip()
    return meta


def is_real_code(line, in_block):
    """Is this line actual program code rather than comment text?

    `in_block` is the block-comment state carried in from the previous line,
    so this works for both `//` and folded `/* ... */` files.
    """
    s = line.strip()
    if not s:
        return False
    if in_block:
        return False
    if s.startswith('//') or s.startswith('/*') or s.startswith('*'):
        return False
    return True


def find_sections(lines):
    """Split the file into (HEADING, [body lines]).

    A heading is an ALL-CAPS line, optionally underlined with dashes or
    equals. Everything else belongs to the current heading.

    CRITICAL RULE: a section body STOPS at the first line of real program
    code. Without this the last header section ("STEP-BY-STEP EXPLANATION")
    would swallow the entire source file and the page would show the program
    twice - once as prose and once in the code viewer.
    """
    secs = []
    cur = None
    i = 0
    n = len(lines)
    in_block = False
    while i < n:
        raw = lines[i]

        # Block-comment state as it stands BEFORE this line is examined.
        # It must be captured first, otherwise the `/*` on the opening line
        # would immediately hide the whole header block from the parser.
        was_in_block = in_block
        if '/*' in raw and not raw.strip().startswith('//'):
            in_block = True
        if '*/' in raw:
            in_block = False

        if is_real_code(raw, was_in_block):
            # a code line: close the section and stop collecting
            if cur is not None:
                secs.append(cur)
                cur = None
            i += 1
            continue

        t = strip_comment_mark(raw)
        is_head = bool(HEAD_RE.match(t)) and len(re.sub(r'[^A-Z]', '', t)) >= 3
        if is_head and i + 1 < n and RULE_RE.match(lines[i + 1]):
            is_head = True
        elif RULE_RE.match(raw) and cur is not None:
            cur[1].append(raw)
            i += 1
            continue
        if is_head:
            if cur is not None:
                secs.append(cur)
            cur = (t.rstrip(':').strip(), [])
        else:
            if cur is None:
                cur = ('', [])
            cur[1].append(raw)
        i += 1
    if cur is not None:
        secs.append(cur)
    return secs


def clean_body(body):
    """Strip comment decoration and blank padding from a section body."""
    out = []
    for ln in body:
        t = strip_comment_mark(ln)
        out.append(t.rstrip())
    while out and not out[0].strip():
        out.pop(0)
    while out and not out[-1].strip():
        out.pop()
    return out


def collect_tables(lines):
    """Find ASCII trace tables in the comments.

    Returns a list of {caption, headers, rows, stop_rows}.
    """
    tables = []
    i = 0
    n = len(lines)
    while i < n:
        if BORDER_RE.match(lines[i]):
            start = i
            caption = ''
            # look backwards for a caption such as "TRACE TABLE"
            k = i - 1
            while k >= 0 and not strip_comment_mark(lines[k]).strip():
                k -= 1
            if k >= 0:
                cand = strip_comment_mark(lines[k]).strip()
                if cand and not ROW_RE.match(lines[k]):
                    caption = cand
            block = []
            j = i
            while j < n and (BORDER_RE.match(lines[j]) or ROW_RE.match(lines[j])):
                block.append(lines[j])
                j += 1
            cells = []
            for ln in block:
                t = strip_comment_mark(ln).strip()
                if not t.startswith('|'):
                    continue
                cells.append([c.strip() for c in t.strip('|').split('|')])
            if cells:
                headers = cells[0]
                rows = []
                for r in cells[1:]:
                    joined = ' '.join(r).lower()
                    stop = ('stop' in joined or 'exit' in joined or 'false' in joined
                            and 'no' in joined)
                    rows.append({'cells': r, 'stop': stop})
                tables.append({'caption': caption or 'Trace table',
                               'headers': headers, 'rows': rows})
            i = j
            continue
        i += 1
    return tables


def parse_questions(body):
    """Turn 'Q1: question -> answer' lines into quiz items."""
    items = []
    qre = re.compile(r'^\s*(?:Q(?:uestion)?\s*)?(\d+)[.):]\s*(.+)$')
    for ln in body:
        t = ln.strip()
        m = qre.match(t)
        if not m:
            continue
        text = m.group(2).strip()
        ans = ''
        if '->' in text:
            text, ans = text.split('->', 1)
            ans = ans.strip()
        items.append({'q': text.strip(), 'a': ans})
    return items


def inline_md(t):
    """Render `code` and **bold** in a plain string as HTML."""
    t = html.escape(t)
    t = re.sub(r'`([^`]+)`', r'<code>\1</code>', t)
    t = re.sub(r'\*\*([^*]+)\*\*', r'<b>\1</b>', t)
    return t


def section_card(name, body):
    """Turn one section into an HTML card."""
    body = clean_body(body)
    if not body:
        return ''

    key = name.upper().rstrip(':').strip()
    h = html.escape(name)

    # ---- bullets -------------------------------------------------
    if key in CARD_TEACH or all(b.lstrip().startswith('-') for b in body if b.strip()):
        items = [b.strip()[1:].strip() for b in body if b.strip().startswith('-')]
        if items:
            lis = ''.join('<li>%s</li>' % inline_md(i) for i in items)
            return ('<div class="card teach"><header><i class="dot"></i>'
                    '<h2>%s</h2></header><div class="body">'
                    '<ul class="bul">%s</ul></div></div>' % (h, lis))

    # ---- syntax pairs --------------------------------------------
    if key in CARD_SYNTAX:
        pairs = []
        pending = ''
        for b in body:
            if not b.strip():
                continue
            looks_code = ('(' in b or ')' in b or b.strip().endswith(';')
                          or '=' in b or '++' in b or '--' in b
                          or b.strip().startswith('if') or b.strip().startswith('for'))
            if looks_code:
                pending = b.strip()
            else:
                pairs.append((pending, b.strip()))
                pending = ''
        if pairs:
            out = ['<div class="card syn"><header><i class="dot"></i>'
                   '<h2>%s</h2></header><div class="body"><div class="syn-list">' % h]
            for code, gloss in pairs:
                out.append('<div class="syn-item"><code>%s</code><span>%s</span></div>'
                           % (html.escape(code or ''), inline_md(gloss)))
            out.append('</div></div></div>')
            return ''.join(out)

    # ---- expected output ----------------------------------------
    if key in CARD_OUT:
        txt = '\n'.join(body)
        return ('<div class="card exp"><header><i class="dot"></i>'
                '<h2>%s</h2></header><div class="body">'
                '<pre class="plain">%s</pre></div></div>' % (h, html.escape(txt)))

    # ---- questions ------------------------------------------------
    if key in CARD_QUESTIONS or name.upper().startswith('EXAM QUESTION'):
        qs = parse_questions(body)
        if qs:
            out = ['<div class="card quiz"><header><i class="dot"></i>'
                   '<h2>Exam questions</h2></header><div class="body">']
            for q in qs:
                ans = ('<b>Answer:</b> %s' % inline_md(q['a'])) if q['a'] else ''
                out.append('<details class="q"><summary>%s</summary>'
                           '<div class="a">%s</div></details>'
                           % (inline_md(q['q']), ans))
            out.append('</div></div>')
            return ''.join(out)

    # ---- numbered steps -------------------------------------------
    numbered = [b for b in body if re.match(r'^\s*\d+[.)]\s', b)]
    if numbered and len(numbered) >= max(2, len([b for b in body if b.strip()]) // 2):
        lis = []
        for b in body:
            s = b.strip()
            if not s:
                continue
            s = re.sub(r'^\d+[.)]\s*', '', s)
            lis.append('<li>%s</li>' % inline_md(s))
        return ('<div class="card"><header><i class="dot"></i><h2>%s</h2></header>'
                '<div class="body"><ol class="steps">%s</ol></div></div>'
                % (h, ''.join(lis)))

    # ---- default: preformatted ------------------------------------
    return ('<div class="card"><header><i class="dot"></i><h2>%s</h2></header>'
            '<div class="body"><pre class="plain wrap">%s</pre></div></div>'
            % (h, html.escape('\n'.join(body))))


# ============================================================
# COMMENT STRIPPING
# Produces the "bare" listing shown at the very top of each page:
# the same program with every explanation deleted, so the student
# can see the code they would actually write on paper.
# ============================================================

def strip_comments(src):
    """Remove C++ comments, respecting string and character literals.

    Why the literal handling matters: `cout << "//";` prints two slashes and
    is NOT a comment. A naive `re.sub(r'//.*', '', line)` would destroy it.
    This walks the text character by character instead.
    """
    out = []
    i = 0
    n = len(src)
    in_block = False
    quote = None
    while i < n:
        c = src[i]
        nxt = src[i + 1] if i + 1 < n else ''

        # --- inside a string or character literal: copy verbatim ---
        if quote is not None:
            out.append(c)
            if c == '\\' and nxt:
                out.append(nxt)
                i += 2
                continue
            if c == quote:
                quote = None
            i += 1
            continue

        # --- inside a block comment: drop it, keep the newlines ---
        if in_block:
            if c == '*' and nxt == '/':
                in_block = False
                i += 2
            else:
                if c == '\n':
                    out.append(c)
                i += 1
            continue

        # --- open a literal ---
        if c == '"' or c == "'":
            quote = c
            out.append(c)
            i += 1
            continue

        # --- line comment: drop the rest of the line ---
        if c == '/' and nxt == '/':
            while i < n and src[i] != '\n':
                i += 1
            continue

        # --- block comment opens ---
        if c == '/' and nxt == '*':
            in_block = True
            i += 2
            continue

        out.append(c)
        i += 1
    return ''.join(out)


def tidy_bare(src):
    """Strip comments, then tighten the vertical spacing.

    Removing a comment block leaves an empty line behind. Emitting every one
    of those would double the height of the listing for no benefit, so blank
    lines are dropped when they sit directly after an opening brace or
    directly before a closing brace - exactly the places where real C++
    listings also skip a blank line.
    """
    lines = strip_comments(src).split('\n')
    res = []
    pending_blank = False
    for ln in lines:
        if not ln.strip():
            pending_blank = True
            continue
        if pending_blank:
            pending_blank = False
            prev = res[-1] if res else ''
            cur = ln.strip()
            keep = (bool(prev.strip())
                    and not prev.rstrip().endswith('{')
                    and not cur.startswith('}')
                    and not cur.startswith('#'))
            if keep:
                res.append('')
        res.append(ln.rstrip())
    return '\n'.join(res)


def count_fold_blocks(src, min_run=3):
    """Count how many collapsible explanation blocks this file will show."""
    n = 0
    lines = src.split('\n')
    run = 0
    in_block = False
    for ln in lines:
        st = ln.strip()
        if st.startswith('/*'):
            n += 1
            in_block = '*/' not in st[2:]
            run = 0
            continue
        if in_block:
            if '*/' in st:
                in_block = False
            continue
        if st.startswith('//'):
            run += 1
        else:
            if run >= min_run:
                n += 1
            run = 0
    if run >= min_run:
        n += 1
    return n


def build_data():
    files = []
    folders = []
    for fid in sorted(os.listdir(ROOT)):
        d = os.path.join(ROOT, fid)
        if not os.path.isdir(d) or fid in ('tools', 'viewer'):
            continue
        names = sorted(n for n in os.listdir(d) if n.endswith('.cpp'))
        if not names:
            continue
        title, desc = FOLDER_META.get(fid, (fid.replace('_', ' ').title(), ''))
        folders.append({'id': fid, 'title': title, 'desc': desc, 'count': len(names)})
        for n in names:
            path = os.path.join(d, n)
            with open(path, encoding='utf-8') as fh:
                src = fh.read()
            lines = src.split('\n')
            meta = parse_header(lines)
            secs = find_sections(lines)
            tables = collect_tables(lines)
            teaches = []
            for name, body in secs:
                if name.upper().rstrip(':') in CARD_TEACH:
                    teaches = [strip_comment_mark(b).strip()[1:].strip()
                               for b in body if strip_comment_mark(b).strip().startswith('-')]
                    break
            stem = n[:-4]
            title_txt = clean_title(meta['program'] or
                                   stem.replace('_', ' ').capitalize())
            files.append({
                'path': '%s/%s' % (fid, n),
                'folder': fid,
                'name': n,
                'stem': stem,
                'title': title_txt,
                'topic': meta['topic'],
                'difficulty': meta['difficulty'],
                'lines': len(lines),
                'bytes': len(src),
                'blocks': count_fold_blocks(src),
                'bare': tidy_bare(src),
                'teaches': teaches,
                'code': src,
                'secs': secs,
                'tables': tables,
                'href': '%s.html' % stem,
                'url': '%s/%s.html' % (fid, stem),   # relative to viewer/
            })
    return folders, files


PAGE_HEAD = """<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>{title}</title>
<link rel="stylesheet" href="{depth}assets/viewer.css">
<link rel="icon" href="data:image/svg+xml,<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 32 32'><text y='26' font-size='26'>&#9881;</text></svg>">
</head>
<body>

<div class="app">
  <div class="scrim" id="scrim"></div>
  <nav class="sidebar">
    <div class="brand">
      <div class="logo">C++</div>
      <div>
        <b>Loops Midterm Review</b>
        <small>{nfiles} annotated examples</small>
      </div>
    </div>
    <div class="side-tools">
      <div class="search-wrap">
        <svg viewBox="0 0 24 24"><path d="M15.5 14h-.79l-.28-.27A6.47 6.47 0 0016 9.5 6.5 6.5 0 109.5 16c1.61 0 3.09-.59 4.23-1.57l.27.28v.79l5 4.99L20.49 19l-4.99-5zm-6 0C7.01 14 5 11.99 5 9.5S7.01 5 9.5 5 14 7.01 14 9.5 11.99 14 9.5 14z"/></svg>
        <input id="search" type="search" placeholder="Search all files and code..." autocomplete="off">
        <button id="searchClear" title="Clear search" style="visibility:hidden">&times;</button>
      </div>
      <div class="progress-row">
        <span id="progLabel">0 / {nfiles} studied</span>
        <span class="bar"><i id="barFill"></i></span>
        <button class="btn-mini" id="resetBtn" hidden>reset</button>
      </div>
    </div>
    <div class="nav" id="nav"></div>
  </nav>

  <main class="main">
    <div class="topbar">
      <button class="icon-btn nav-only" id="navToggle" title="Show file list">&#9776;</button>
      <div class="crumb">
        <span>{folder}</span> / <b>{name}</b>
      </div>
      <span class="spacer"></span>
      <button class="icon-btn" id="topKeys" title="Keyboard shortcuts (?)">?</button>
      <button class="icon-btn" id="themeBtn" title="Toggle light / dark (t)">&#9680;</button>
    </div>

    <div class="scroll">
      <div class="wrap">
"""

PAGE_TAIL = """      </div>
    </div>
  </main>
</div>

<dialog id="keys">
  <header>Keyboard shortcuts <span class="spacer"></span>
    <button class="icon-btn" id="keysClose">&#10005;</button></header>
  <div class="body">
    <div class="krow"><span>Toggle all comments</span><kbd>c</kbd></div>
    <div class="krow"><span>Fold / unfold every note</span><kbd>f</kbd></div>
    <div class="krow"><span>Exam mode (code only)</span><kbd>e</kbd></div>
    <div class="krow"><span>Next file</span><kbd>n</kbd></div>
    <div class="krow"><span>Previous file</span><kbd>p</kbd></div>
    <div class="krow"><span>Focus search</span><kbd>/</kbd></div>
    <div class="krow"><span>Light / dark theme</span><kbd>t</kbd></div>
    <div class="krow"><span>Open this dialog</span><kbd>?</kbd></div>
  </div>
</dialog>

<div class="toast" id="toast"></div>

<script src="{depth}assets/data.js"></script>
<!--PAGEVAR-->
<script>window.VIEWER_DEPTH = "{depth}";</script>
<script src="{depth}assets/viewer.js"></script>
</body>
</html>
"""


def render_page(f, folders, files, depth):
    title = html.escape(f['title'])
    crumbs = []
    out = [PAGE_HEAD.format(
        title=title + ' - C++ Loops Midterm Review',
        depth=depth, nfiles=len(files),
        folder=html.escape(f['folder']),
        name=html.escape(f['name']))]

    diff = f['difficulty'].lower()
    diff = diff.split('/')[0].strip()
    dclass = diff if diff in ('beginner', 'intermediate', 'advanced') else ''

    out.append('        <!-- ============ THE BARE PROGRAM (comments removed) '
               '=========== -->')
    bare_lines = f['bare'].count('\n') + 1
    bare_pct = (100.0 * (bare_lines / float(f['lines']))) if f['lines'] else 100
    out.append('        <div class="card bare-card">')
    out.append('          <header><i class="dot"></i>'
               '<h2>The program, comments removed</h2>'
               '<span class="badge ok">the code you would write in the exam</span>'
               '<span class="spacer"></span>'
               '<span class="badge">%d lines (from %d)</span></header>'
               % (bare_lines, f['lines']))
    out.append('          <div class="toolbar bare-tools">')
    out.append('            <span class="hint">Every explanation has been deleted. '
               'This is the complete program on its own &mdash; read it top to '
               'bottom until you can predict each line.</span>')
    out.append('            <button class="tgl" id="copyBareBtn">Copy bare code</button>')
    out.append('          </div>')
    out.append('          <div class="codewrap bare"><div class="code" id="codeBare">'
               '</div></div>')
    out.append('        </div>')

    out.append('        <div class="hero">')
    out.append('          <div class="path">%s/%s</div>' % (html.escape(f['folder']),
                                                          html.escape(f['name'])))
    out.append('          <h1>%s</h1>' % title)
    out.append('          <div class="badges">')
    if dclass:
        out.append('            <span class="badge %s">%s</span>'
                   % (dclass, html.escape(f['difficulty'])))
    if f['topic']:
        out.append('            <span class="badge topic">%s</span>'
                   % html.escape(f['topic']))
    out.append('            <span class="badge">%d lines</span>' % f['lines'])
    out.append('            <span class="badge">%d kb</span>' % max(1, f['bytes'] // 1024))
    out.append('          </div>')
    out.append('        </div>')

    out.append('        <div class="note info"><b>Reading tip.</b> Every grey note '
               'below is a collapsible explanation. Click its header to read it, '
               'or press <b>C</b> to hide every comment at once so the program '
               'logic stands on its own.</div>')

    # sections
    seen_tables = 0
    for name, body in f['secs']:
        if not name:
            continue
        key = name.upper().rstrip(':')
        if key in ('PROGRAM', 'TOPIC', 'DIFFICULTY', 'LEVEL'):
            continue
        card = section_card(name, body)
        if card:
            out.append('        ' + card)

    # tables
    if f['tables']:
        out.append('        <div class="card trace"><header><i class="dot"></i>'
                   '<h2>Trace tables</h2></header><div class="body">')
        for tb in f['tables']:
            out.append('          <p class="tbl-cap">%s</p>'
                       % inline_md(tb['caption']))
            out.append('          <div class="tbl-scroll"><table class="grid"><thead><tr>')
            for h in tb['headers']:
                out.append('<th>%s</th>' % html.escape(h))
            out.append('</tr></thead><tbody>')
            for r in tb['rows']:
                cls = ' class="stop"' if r['stop'] else ''
                cells = ''.join('<td>%s</td>' % html.escape(c) for c in r['cells'])
                out.append('<tr%s>%s</tr>' % (cls, cells))
            out.append('</tbody></table></div>')
            seen_tables += 1
        out.append('        </div></div>')

    # code
    out.append('        <div class="card code-card" id="annotated">')
    out.append('          <header><i class="dot"></i><h2>The program, annotated</h2></header>')
    out.append('          <div class="toolbar">')
    out.append('            <label class="tgl"><input type="checkbox" id="tgComments"> '
               'Hide all comments <kbd>C</kbd></label>')
    out.append('            <label class="tgl"><input type="checkbox" id="tgFold"> '
               'Unfold every note <kbd>F</kbd></label>')
    out.append('            <label class="tgl keep"><input type="checkbox" id="tgNums" checked> '
               'Line numbers</label>')
    out.append('            <button class="tgl" id="examBtn">Exam mode <kbd>E</kbd></button>')
    out.append('            <button class="tgl" id="copyBtn">Copy source</button>')
    out.append('            <a class="tgl" href="../../%s" download>Download .cpp</a>'
               % html.escape(f['path']))
    out.append('          </div>')
    out.append('          <div class="codewrap"><div class="code" id="code"></div></div>')
    out.append('        </div>')

    # pager
    idx = [x['path'] for x in files].index(f['path'])
    out.append('        <div class="pager">')
    if idx > 0:
        p = files[idx - 1]
        out.append('          <a class="prev" id="prevLink" href="%s"><span class="dir">Previous</span>'
                   '<span class="nm">%s</span></a>'
                   % (html.escape('../' + p['url']),
                      html.escape(p['stem'].replace('_', ' '))))
    else:
        out.append('          <a class="prev" href="../index.html"><span class="dir">Back</span>'
                   '<span class="nm">Dashboard</span></a>')
    if idx < len(files) - 1:
        nx = files[idx + 1]
        out.append('          <a class="next" id="nextLink" href="%s"><span class="dir">Next</span>'
                   '<span class="nm">%s</span></a>'
                   % (html.escape('../' + nx['url']),
                      html.escape(nx['stem'].replace('_', ' '))))
    else:
        out.append('          <a class="next" href="../index.html"><span class="dir">Finished</span>'
                   '<span class="nm">Dashboard</span></a>')
    out.append('        </div>')

    out.append(PAGE_TAIL.format(depth=depth))
    return '\n'.join(out)


def render_index(folders, files):
    total_lines = sum(f['lines'] for f in files)
    covered = set()
    for f in files:
        for t in f['teaches']:
            for w in re.findall(r'[a-zA-Z_]{4,}', t):
                covered.add(w.lower())

    out = []
    out.append(PAGE_HEAD.format(
        title='C++ Loops Midterm Review',
        depth='', nfiles=len(files),
        folder='Dashboard', name='Start here'))

    out.append('        <div class="dash">')
    out.append('          <div class="dash-hero">')
    out.append('            <h1>C++ Loops Midterm Review</h1>')
    out.append('            <p>Every example is a complete, compilable program whose '
              'purpose is to be <em>understood</em>, not just compiled. Each file '
              'carries a line-by-line explanation, a full trace table and the exam '
              'questions it prepares you for.</p>')
    out.append('            <p>Open a folder, work through it in order, and tick each '
              'file as you master it. Your progress is stored in the browser.</p>')
    out.append('          </div>')

    out.append('          <div class="tiles">')
    out.append('            <div class="tile"><b>%d</b><span>examples</span></div>' % len(files))
    out.append('            <div class="tile"><b>%d</b><span>foldable notes</span></div>'
               % sum(f['blocks'] for f in files))
    out.append('            <div class="tile"><b>%d</b><span>lines of code</span></div>' % total_lines)
    out.append('            <div class="tile"><b>%d</b><span>sections</span></div>' % len(folders))
    out.append('          </div>')

    out.append('          <div class="note info"><b>The two shortcuts you will use most.</b> '
               'Press <b>C</b> to hide every comment and read the bare program; press '
               '<b>E</b> for exam mode, which strips the page down to code only. '
               'Everything else is optional.</div>')

    out.append('          <h2 style="font-size:15px;margin:22px 0 10px">Study order</h2>')
    out.append('          <div class="grid-cards">')
    for fo in folders:
        fset = [f for f in files if f['folder'] == fo['id']]
        topics = []
        for f in fset:
            if f['topic'] and f['topic'] not in topics:
                topics.append(f['topic'])
        out.append('            <a class="fcard" href="%s/index.html">' % html.escape(fo['id']))
        out.append('              <div class="num">%s</div>' % html.escape(fo['id']))
        out.append('              <h3>%s</h3>' % html.escape(fo['title']))
        out.append('              <p>%s</p>' % html.escape(fo['desc']))
        out.append('              <div class="st" data-folder="%s"><b>0</b> of %d studied</div>'
                   % (html.escape(fo['id']), len(fset)))
        out.append('            </a>')
    out.append('          </div>')

    out.append('          <h2 style="font-size:15px;margin:26px 0 8px">Build &amp; run</h2>')
    out.append('          <div class="card"><div class="body">')
    out.append('            <pre class="plain wrap"># compile one file\ng++ -std=c++17 -Wall -Wextra '
               '-o prog 01_fundamentals/01_hello_loop.cpp\n\n# run it\n./prog\n\n'
               '# compile every file in the project at once\n./build_check.sh</pre>')
    out.append('            <p style="margin-top:10px">Full instructions, the loop '
               'syntax quick-reference and the mistake list live in '
               '<code>README.md</code>.</p>')
    out.append('          </div></div>')
    out.append('        </div>')

    out.append(PAGE_TAIL.format(depth=''))
    return '\n'.join(out)


def folder_index(fid, fdata, files, all_folders):
    """A small index page for each folder listing its files."""
    depth = '../'
    out = [PAGE_HEAD.format(
        title=fdata['title'] + ' - C++ Loops Midterm Review',
        depth=depth, nfiles=len(files),
        folder=html.escape(fid), name='Section')]
    out.append('        <div class="dash">')
    out.append('          <div class="dash-hero">')
    out.append('            <h1>%s</h1>' % html.escape(fdata['title']))
    out.append('            <p>%s</p>' % html.escape(fdata['desc']))
    out.append('          </div>')
    out.append('          <div class="grid-cards">')
    for f in fdata['files']:
        d = f['difficulty'].lower().split('/')[0].strip()
        d = d if d in ('beginner', 'intermediate', 'advanced') else ''
        out.append('            <a class="fcard" href="%s">' % html.escape(f['href']))
        out.append('              <div class="num">%s &middot; %d lines</div>'
                   % (html.escape(f['stem'].split('_')[0]), f['lines']))
        out.append('              <h3>%s</h3>' % html.escape(f['title']))
        if f['teaches']:
            out.append('              <p>%s</p>'
                       % html.escape(f['teaches'][0][:150]))
        out.append('              <div class="badges" style="margin-top:8px">')
        if d:
            out.append('                <span class="badge %s">%s</span>'
                       % (d, html.escape(f['difficulty'])))
        out.append('                <span class="badge topic">%s</span>'
                   % html.escape(f['topic'][:60] if f['topic'] else 'loops'))
        out.append('              </div>')
        out.append('            </a>')
    out.append('          </div>')
    out.append('          <div class="pager"><a href="../index.html">'
               '<span class="dir">Back</span>'
               '<span class="nm">All sections</span></a></div>')
    out.append('        </div>')
    out.append(PAGE_TAIL.format(depth=depth))
    return '\n'.join(out)


def main():
    folders, files = build_data()
    if not files:
        print('ERROR: no .cpp files found under', ROOT)
        return 1

    # strip generated html so re-runs never leave stale pages behind
    if os.path.isdir(VIEWER):
        for fo in folders:
            fid = fo['id']
            p = os.path.join(VIEWER, fid)
            if os.path.isdir(p):
                shutil.rmtree(p)

    os.makedirs(os.path.join(VIEWER, 'assets'), exist_ok=True)
    for asset in ('viewer.css', 'viewer.js'):
        src = os.path.join(VIEWER, 'assets', asset)
        if not os.path.exists(src):
            print('ERROR: missing', src)
            return 1

    # ---- data.js ------------------------------------------------
    payload = {
        'generated': True,
        'folders': folders,
        # `secs`/`tables` stay out of the client payload: the pages are
        # pre-rendered, so the client only needs navigation + search data.
        'files': [{
            'path': f['path'], 'folder': f['folder'], 'name': f['name'],
            'href': f['href'], 'url': f['url'],
            'title': f['title'], 'topic': f['topic'],
            'difficulty': f['difficulty'], 'lines': f['lines'],
            'teaches': f['teaches'], 'code': f['code'], 'bare': f['bare'],
        } for f in files],
    }
    with open(os.path.join(VIEWER, 'assets', 'data.js'), 'w', encoding='utf-8') as fh:
        fh.write('/* Generated by tools/make_viewer.py - do not edit by hand. */\n')
        fh.write('window.PROJECT = ')
        json.dump(payload, fh, ensure_ascii=False)
        fh.write(';\n')

    # ---- one page per file --------------------------------------
    for f in files:
        d = os.path.join(VIEWER, f['folder'])
        os.makedirs(d, exist_ok=True)
        with open(os.path.join(d, f['href']), 'w', encoding='utf-8') as fh:
            fh.write(render_page(f, folders, files, '../'))
        # tell the page which file it is
        path = os.path.join(d, f['href'])
        s = open(path, encoding='utf-8').read()
        inject = ('<script>window.CURRENT_FILE = window.PROJECT.files.filter('
                  'function (x) { return x.path === %s; })[0];</script>'
                  % json.dumps(f['path']))
        if '<!--PAGEVAR-->' not in s:
            raise SystemExit('ERROR: page marker missing in ' + path)
        s = s.replace('<!--PAGEVAR-->', inject, 1)
        open(path, 'w', encoding='utf-8').write(s)

    # ---- folder indexes -----------------------------------------
    for fo in folders:
        fdata = {
            'title': fo['title'], 'desc': fo['desc'],
            'files': [f for f in files if f['folder'] == fo['id']],
        }
        with open(os.path.join(VIEWER, fo['id'], 'index.html'), 'w', encoding='utf-8') as fh:
            fh.write(folder_index(fo['id'], fdata, files, folders))

    # ---- dashboard ----------------------------------------------
    with open(os.path.join(VIEWER, 'index.html'), 'w', encoding='utf-8') as fh:
        fh.write(render_index(folders, files))

    size = sum(os.path.getsize(os.path.join(dp, fn))
               for dp, _dn, fns in os.walk(VIEWER) for fn in fns)
    print('viewer built')
    print('  sections   :', len(folders))
    print('  file pages :', len(files))
    print('  total size : %.1f MB' % (size / 1048576.0))
    print('  open       : viewer/index.html')
    return 0


if __name__ == '__main__':
    sys.exit(main())