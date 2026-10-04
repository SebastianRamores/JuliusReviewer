#!/usr/bin/env python3
"""
fold_comments.py
================

PURPOSE
-------
Turn long runs of consecutive `//` comment lines into `/* ... */` block
comments so that they become FOLDABLE in every text editor.

WHY THIS MATTERS FOR THIS PROJECT
----------------------------------
Every file in this project explains itself line by line, which is exactly what
a beginner needs - but it also pushes the real code lines far apart.  A block
comment is the one construct that *every* editor (VS Code, Sublime, Notepad++,
Vim with `foldmethod=syntax`, Atom, ...) can collapse into a single line.

`//` line comments cannot be collapsed as a group by most editors.
`/* ... */` blocks can.  So we convert only the LONG runs and leave the short
one-line glosses as `//`, which keeps the important hints always visible.

WHAT IT CHANGES
---------------
  A run of >= MIN_RUN consecutive comment-only lines becomes:

      /*
      PROGRAM: Count from 1 to 10
      TOPIC: for loops
      */

  Short runs (< MIN_RUN) are left exactly as they are.

SAFETY RULES
------------
  1. A run is only converted if NONE of its lines contain `*/` or `/*`.
     (Block comments cannot be nested and cannot contain their own terminator.)
  2. We never touch lines that are already inside a block comment.
  3. The transformation is IDEMPOTENT: running it twice changes nothing more.
  4. `--check` only reports what it would do, without writing.

USAGE
-----
    python3 tools/fold_comments.py            # convert all .cpp files
    python3 tools/fold_comments.py --check    # dry run, report only
    python3 tools/fold_comments.py --min 4    # fold runs of 4+ lines instead
"""

import argparse
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# A "comment-only" line: optional whitespace, then //, then the text.
LINE_COMMENT = re.compile(r'^(\s*)//(.*)$')


def strip_comment_body(text):
    """Remove the leading `//` and normalise the spacing behind it.

    Why one space is ADDED when none is present
    ---------------------------------------------
    Inside `/* ... */` the `//` prefix is redundant, but the ASCII trace tables
    keep their column alignment only if EVERY row loses the same width.

        // +-----------+      <-- border row: already one space wide
        //|     1     |      <-- data row:   zero spaces

    After stripping one leading space from each body and re-adding a single
    space, both rows put their symbol in the same column, so the table still
    lines up. Normalising is therefore safe for ASCII art and also fixes the
    ugly `//No space` that creeps into hand-written comments.
    """
    if text.startswith(' '):
        return text[1:]
    if text and not text.startswith(('/', '*', '|', '+', '-', '=')):
        # Real prose missing its space: give it one.
        return ' ' + text
    return text


def split_into_runs(lines):
    """Yield (kind, payload) tuples.

    kind == 'code'    -> payload is the raw line
    kind == 'raw'     -> payload is a line that sits inside an existing
                         `/* ... */` block, or is the opener/closer itself
    kind == 'comment' -> payload is (indent, [bodies]) for a maximal run
                         of consecutive `//`-only lines
    """
    runs = []
    i = 0
    n = len(lines)
    in_block = False
    while i < n:
        line = lines[i]
        # Track (but never modify) pre-existing block comments.
        if not in_block and '/*' in line:
            in_block = True
            runs.append(('raw', line))
            if '*/' in line:
                in_block = False
            i += 1
            continue
        if in_block:
            runs.append(('raw', line))
            if '*/' in line:
                in_block = False
            i += 1
            continue

        m = LINE_COMMENT.match(line)
        if not m:
            runs.append(('code', line))
            i += 1
            continue

        indent = m.group(1)
        bodies = []
        raw = []
        start = i
        while i < n:
            mm = LINE_COMMENT.match(lines[i])
            if not mm or mm.group(1) != indent:
                break
            bodies.append(strip_comment_body(mm.group(2).rstrip('\n')))
            raw.append(lines[i])
            i += 1
        runs.append(('comment', (indent, bodies, raw, start)))
    return runs


def is_convertible(bodies, min_run):
    """Can this comment run safely become a block comment?"""
    if len(bodies) < min_run:
        return False
    for b in bodies:
        # A block comment must not contain its own terminator or opener.
        if '*/' in b or '/*' in b:
            return False
        # A line consisting of a single `*` is a continuation marker style we
        # do not generate, but tolerate it for safety.
        if b.strip() == '*':
            return False
    return True


def convert(text, min_run):
    """Return (new_text, blocks_created)."""
    lines = text.split('\n')
    runs = split_into_runs(lines)
    out = []
    created = 0

    for kind, payload in runs:
        if kind == 'raw':
            out.append(payload)
            continue
        if kind == 'code':
            out.append(payload)
            continue

        indent, bodies, raw, _start = payload
        if not is_convertible(bodies, min_run):
            # Short runs stay as `//` comments. `strip_comment_body` already
            # removed the one canonical space, so we put it back here. This
            # also repairs `//No space` in hand-written comments, and it keeps
            # ASCII-art rows aligned with their `+---+` borders.
            out.extend((indent + '// ' + b).rstrip() if b else indent + '//'
                       for b in bodies)
            continue

        created += 1
        pad = '  '  # inner indent for readability
        out.append(indent + '/*')
        for b in bodies:
            if b == '':
                out.append('')
            else:
                out.append(indent + pad + b)
        out.append(indent + '*/')

    return '\n'.join(out), created


def already_wrapped(lines, start):
    """Guard against re-processing: is the line above `start` an opener?"""
    j = start - 1
    while j >= 0 and lines[j].strip() == '':
        j -= 1
    return j >= 0 and lines[j].strip() == '/*'


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--check', action='store_true',
                    help='report only, do not write')
    ap.add_argument('--min', type=int, default=3,
                    help='fold runs of at least this many comment lines')
    ap.add_argument('--dir', default=ROOT, help='project root')
    args = ap.parse_args()

    files = []
    for folder, _sub, names in os.walk(args.dir):
        if os.path.basename(folder) in ('tools', 'viewer', 'node_modules'):
            continue
        for n in sorted(names):
            if n.endswith('.cpp'):
                files.append(os.path.join(folder, n))
    files.sort()

    total_blocks = 0
    changed_files = 0
    for path in files:
        with open(path, 'r', encoding='utf-8') as fh:
            original = fh.read()
        new_text, blocks = convert(original, args.min)
        rel = os.path.relpath(path, args.dir)
        if new_text == original:
            continue
        total_blocks += blocks
        changed_files += 1
        print(f'  {rel}: {blocks} foldable comment block(s)')
        if not args.check:
            with open(path, 'w', encoding='utf-8') as fh:
                fh.write(new_text)

    print()
    print(f'files scanned   : {len(files)}')
    print(f'files changed   : {changed_files}')
    print(f'blocks created  : {total_blocks}')
    if args.check:
        print('(dry run - nothing written)')
    else:
        print('Done. Fold blocks in your editor with: '
              'Ctrl+K then Ctrl+0  (VS Code), '
              'Ctrl+Shift+[ / ] for all comments.')


if __name__ == '__main__':
    sys.exit(main())