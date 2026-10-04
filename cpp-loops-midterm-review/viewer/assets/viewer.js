/* ============================================================
   C++ LOOPS MIDTERM REVIEW - viewer behaviour
   ------------------------------------------------------------
   No framework, no build step, no network. One plain script.
   Data lives in assets/data.js as window.PROJECT.
   ============================================================ */
(function () {
  'use strict';

  /* ---------- tiny helpers ---------------------------------- */
  var $  = function (s, r) { return (r || document).querySelector(s); };
  var $$ = function (s, r) { return Array.prototype.slice.call((r || document).querySelectorAll(s)); };
  function el(tag, cls, txt) {
    var n = document.createElement(tag);
    if (cls) n.className = cls;
    if (txt != null) n.textContent = txt;
    return n;
  }
  function esc(s) {
    return String(s).replace(/&/g, '&amp;').replace(/</g, '&lt;')
                    .replace(/>/g, '&gt;').replace(/"/g, '&quot;');
  }
  function toast(msg) {
    var t = $('#toast');
    if (!t) return;
    t.textContent = msg;
    t.classList.add('show');
    clearTimeout(t._t);
    t._t = setTimeout(function () { t.classList.remove('show'); }, 1900);
  }

  /* ---------- theme ------------------------------------------ */
  function applyTheme(mode) {
    var m = mode;
    if (!m) {
      m = localStorage.getItem('cpp-theme') ||
          (window.matchMedia('(prefers-color-scheme: dark)').matches ? 'dark' : 'light');
    }
    document.documentElement.setAttribute('data-theme', m);
    localStorage.setItem('cpp-theme', m);
    var b = $('#themeBtn');
    if (b) b.textContent = m === 'dark' ? '\u2600' : '\u263C';
  }
  function toggleTheme() {
    var cur = document.documentElement.getAttribute('data-theme');
    applyTheme(cur === 'dark' ? 'light' : 'dark');
  }

  /* ---------- progress --------------------------------------- */
  var DONE_KEY = 'cpp-done';
  function getDone() {
    try { return JSON.parse(localStorage.getItem(DONE_KEY)) || {}; }
    catch (e) { return {}; }
  }
  function setDone(path, on) {
    var d = getDone();
    if (on) d[path] = 1; else delete d[path];
    localStorage.setItem(DONE_KEY, JSON.stringify(d));
    renderProgress();
  }
  function renderProgress() {
    var P = window.PROJECT;
    if (!P) return;
    var done = getDone();
    var total = P.files.length;
    var n = P.files.filter(function (f) { return done[f.path]; }).length;
    var pct = total ? Math.round(n / total * 100) : 0;
    var bar = $('#barFill'), lbl = $('#progLabel'), btn = $('#resetBtn');
    if (bar) bar.style.width = pct + '%';
    if (lbl) lbl.textContent = n + ' / ' + total + ' studied';
    if (btn) btn.hidden = n === 0;
    $$('.folder .count').forEach(function (c) {
      var fp = c.getAttribute('data-folder');
      var files = P.files.filter(function (f) { return f.folder === fp; });
      var d = files.filter(function (f) { return done[f.path]; }).length;
      c.innerHTML = d > 0 ? '<span class="done">' + d + '</span>/' + files.length
                          : files.length;
    });
    $$('.dash .st').forEach(function (s) {
      var fp = s.getAttribute('data-folder');
      var files = P.files.filter(function (f) { return f.folder === fp; });
      var d = files.filter(function (f) { return done[f.path]; }).length;
      s.innerHTML = '<b>' + d + '</b> of ' + files.length + ' studied';
    });
  }

  /* ---------- sidebar ---------------------------------------- */
  function buildSidebar(activePath) {
    var P = window.PROJECT;
    var nav = $('#nav');
    if (!nav || !P) return;
    var done = getDone();
    nav.innerHTML = '';

    P.folders.forEach(function (fo) {
      var files = P.files.filter(function (f) { return f.folder === fo.id; });
      if (!files.length) return;

      var det = el('details', 'folder');
      det.setAttribute('data-folder', fo.id);
      if (fo.open !== false) det.open = true;

      var sum = el('summary');
      sum.appendChild(el('i', 'caret'));
      sum.appendChild(el('span', null, fo.id.replace(/_/g, ' ')));
      var cnt = el('span', 'count');
      cnt.setAttribute('data-folder', fo.id);
      sum.appendChild(cnt);
      det.appendChild(sum);

      files.forEach(function (f) {
        var a = el('a', 'file-link');
        /* Links must be built from the VIEWER ROOT, not from the current
           folder, otherwise clicking a file in another folder 404s. */
        a.href = (window.VIEWER_DEPTH || '') + (f.url || f.href);
        a.setAttribute('data-path', f.path);
        a.setAttribute('data-search',
          (f.name + ' ' + (f.title || '') + ' ' + (f.topic || '') + ' ' +
           (f.folder + ' ' + f.folder).replace(/_/g, ' ') + ' ' +
           f.code + ' ' + f.teaches.join(' ')).toLowerCase());
        if (f.path === activePath) a.classList.add('active');

        var tick = el('input', 'tick');
        tick.type = 'checkbox';
        tick.checked = !!done[f.path];
        tick.title = 'Mark as studied';
        tick.addEventListener('click', function (ev) {
          ev.stopPropagation();
          setDone(f.path, tick.checked);
        });

        a.appendChild(tick);
        a.appendChild(el('span', 'nm', f.name.replace(/^\d+_/, '').replace(/_/g, ' ')));
        det.appendChild(a);
      });
      nav.appendChild(det);
    });

    var empty = el('div', 'empty-hits', 'No file matches that search.');
    empty.id = 'noHits';
    empty.hidden = true;
    nav.appendChild(empty);
    renderProgress();
  }

  /* ---------- search ----------------------------------------- */
  function wireSearch() {
    var box = $('#search');
    if (!box) return;
    var clear = $('#searchClear');
    function run() {
      var q = box.value.trim().toLowerCase();
      var nav = $('#nav');
      var hits = 0;
      $$('.file-link', nav).forEach(function (a) {
        var ok = !q || a.getAttribute('data-search').indexOf(q) !== -1;
        a.style.display = ok ? '' : 'none';
        if (ok) hits++;
      });
      $$('.folder', nav).forEach(function (d) {
        var any = $$('.file-link', d).some(function (a) { return a.style.display !== 'none'; });
        d.style.display = any ? '' : 'none';
        if (q && any) d.open = true;
      });
      $('#noHits').hidden = hits !== 0;
      if (clear) clear.style.visibility = q ? 'visible' : 'hidden';
    }
    box.addEventListener('input', run);
    if (clear) clear.addEventListener('click', function () { box.value = ''; box.focus(); run(); });
    document.addEventListener('keydown', function (e) {
      if (e.key === '/' && document.activeElement !== box &&
          !/^(INPUT|TEXTAREA)$/.test((document.activeElement || {}).tagName)) {
        e.preventDefault(); box.focus(); box.select();
      }
    });
  }

  /* ============================================================
     C++ SYNTAX HIGHLIGHTER
     A small hand-written tokenizer. It returns, for every physical
     line, a list of {cls, text} tokens. Comment state is carried
     across lines so multi-line block comments work.
     ============================================================ */
  var KEYWORDS = ('int main return for while do if else break continue const char '
    + 'double float bool void long short unsigned signed switch case default '
    + 'struct class public private new delete sizeof using namespace true false '
    + 'null nullptr std and or not').split(' ');

  var BUILTINS = ('cout cin endl endl cin cout std using namespace include iostream '
    + 'INT_MAX RAND_MAX').split(' ');
  // Only the ones we actually colour.
  BUILTINS = ['cout', 'cin', 'endl', 'std', 'using', 'namespace', 'include', 'string',
              'iostream', 'srand', 'rand', 'time', 'system', 'setw', 'setprecision',
              'fixed', 'limits', 'INT_MAX'];

  var TYPES = ('int double float char bool void long short unsigned signed').split(' ');

  function tokenize(src) {
    var lines = src.split('\n');
    var out = [];
    var inBlock = false;      // inside /* ... */
    var blockStartLine = -1;  // line index where the current block opened

    for (var li = 0; li < lines.length; li++) {
      var line = lines[li];
      var toks = [];
      var i = 0;
      var openHere = inBlock;

      if (inBlock) {
        var end = line.indexOf('*/');
        if (end === -1) {
          toks.push({ cls: 'tk-cm', text: line });
          out.push({ toks: toks, cmt: true, blkStart: blockStartLine });
          continue;
        }
        toks.push({ cls: 'tk-cm', text: line.slice(0, end + 2) });
        i = end + 2;
        inBlock = false;
      }

      while (i < line.length) {
        var c = line[i];
        var rest = line.slice(i);

        // line comment
        if (c === '/' && line[i + 1] === '/') {
          toks.push({ cls: 'tk-cm', text: line.slice(i) });
          i = line.length;
          break;
        }
        // block comment opens
        if (c === '/' && line[i + 1] === '*') {
          var e2 = line.indexOf('*/', i + 2);
          if (e2 === -1) {
            toks.push({ cls: 'tk-cm', text: line.slice(i) });
            inBlock = true;
            blockStartLine = li;
            i = line.length;
          } else {
            toks.push({ cls: 'tk-cm', text: line.slice(i, e2 + 2) });
            i = e2 + 2;
          }
          continue;
        }
        // string literal
        if (c === '"' || c === "'") {
          var q = c, j = i + 1;
          while (j < line.length) {
            if (line[j] === '\\') { j += 2; continue; }
            if (line[j] === q) { j++; break; }
            j++;
          }
          toks.push({ cls: 'tk-st', text: line.slice(i, Math.min(j, line.length)) });
          i = Math.min(j, line.length);
          continue;
        }
        // preprocessor
        if (c === '#' && /^\s*#/.test(line)) {
          toks.push({ cls: 'tk-pp', text: line.slice(i) });
          i = line.length;
          continue;
        }
        // number
        if (/[0-9]/.test(c) || (c === '.' && /[0-9]/.test(line[i + 1] || ''))) {
          var k = i;
          while (k < line.length && /[0-9a-fA-FxX.eE]/.test(line[k])) k++;
          toks.push({ cls: 'tk-nu', text: line.slice(i, k) });
          i = k;
          continue;
        }
        // identifier / keyword
        if (/[A-Za-z_]/.test(c)) {
          var m = /^[A-Za-z_][A-Za-z0-9_]*/.exec(rest);
          var w = m[0];
          var cls = null;
          if (KEYWORDS.indexOf(w) !== -1) cls = 'tk-kw';
          else if (BUILTINS.indexOf(w) !== -1) cls = 'tk-bi';
          else if (TYPES.indexOf(w) !== -1) cls = 'tk-ty';
          else if (line[i + w.length] === ':' && line[i + w.length + 1] === ':') cls = 'tk-ns';
          toks.push({ cls: cls, text: w });
          i += w.length;
          continue;
        }
        // operators / punctuation - grouped so spacing survives
        var op = /^(::|<<=|>>=|\+\+|--|->|<<|>>|<=|>=|==|!=|&&|\|\||\+=|-=|\*=|\/=|\%=)/.exec(rest);
        if (op) {
          toks.push({ cls: 'tk-op', text: op[0] });
          i += op[0].length;
          continue;
        }
        toks.push({ cls: '', text: c });
        i++;
      }

      out.push({
        toks: toks,
        cmt: isCommentOnly(toks),
        blkStart: openHere ? blockStartLine : -1
      });
    }
    return out;
  }

  function isCommentOnly(toks) {
    if (!toks.length) return false;
    var seen = '';
    for (var i = 0; i < toks.length; i++) {
      if (toks[i].cls === 'tk-cm') seen += toks[i].text;
    }
    var joined = toks.map(function (t) { return t.text; }).join('');
    return seen.length > 0 && seen.replace(/\s/g, '') === joined.replace(/\s/g, '');
  }

  /* ============================================================
     CODE VIEWER
     Builds the line-numbered, highlighted, collapsible view.

     Comment FOLDING MODEL
     --------------------
       * `/* ... *\/` blocks become one <div class="blk">. The header row is a
         click target; clicking collapses the whole explanation to a single
         preview line.
       * A run of >= 3 consecutive `//` lines is treated the same way, because
         in this project those runs are multi-line explanations.
       * A one- or two-line `//` gloss stays visible inline - it is short
         enough that hiding it would just add clicks.
       * "Hide comments" switches off EVERY comment row at once, which is the
         fastest way to see the program's real shape.
     ============================================================ */
  var FOLD_MIN_RUN = 3;

  function renderCode(host, src) {
    var rows = tokenize(src);
    host.innerHTML = '';
    var block = null;          // current <div class="blk">
    var blockBuf = [];         // pending rows for the current block
    var openCmts = [];         // comment rows waiting to become a block

    function flushOpenComments() {
      if (openCmts.length < FOLD_MIN_RUN) {
        openCmts.forEach(function (r) { host.appendChild(makeRow(r, r.i + 1)); });
        openCmts = [];
        return;
      }
      var blk = makeBlock(openCmts, false);
      host.appendChild(blk);
      openCmts = [];
    }

    function flushBlock() {
      if (block && blockBuf.length) {
        blockBuf.forEach(function (r) { block.appendChild(makeRow(r, r.i + 1)); });
        blockBuf = [];
      }
      block = null;
    }

    rows.forEach(function (r, idx) {
      r.i = idx;
      if (!r.cmt) {
        flushOpenComments();
        flushBlock();
        host.appendChild(makeRow(r, idx + 1));
        return;
      }
      if (r.blkStart === idx) {
        // opening line of a block comment
        flushOpenComments();
        flushBlock();
        block = makeBlock([], true);
        blockBuf.push(r);
        return;
      }
      if (block) { blockBuf.push(r); return; }
      openCmts.push(r);
    });
    flushOpenComments();
    flushBlock();
  }

  function makeRow(r, num) {
    var d = el('div', 'ln');
    if (r.cmt) d.className += ' cmt';
    if (!r.toks.length || (r.toks.length === 1 && r.toks[0].text.trim() === '')) {
      d.className += ' blank';
    }
    d.appendChild(el('span', 'n', String(num)));
    var t = el('span', 't');
    r.toks.forEach(function (tk) {
      if (!tk.cls) { t.appendChild(document.createTextNode(tk.text)); }
      else {
        var s = el('span', tk.cls, tk.text);
        t.appendChild(s);
      }
    });
    d.appendChild(t);
    return d;
  }

  function previewOf(rows) {
    for (var i = 0; i < rows.length; i++) {
      var txt = rows[i].toks.map(function (t) { return t.text; }).join('');
      txt = txt.replace(/^\s*\/\*+/, '').replace(/\*+\/\s*$/, '')
               .replace(/^\s*\/\/ ?/, '').trim();
      // Skip banner rules such as "=====" or "-----" or "*****": they are
      // decoration, so they make a useless one-word fold preview.
      if (txt && !/^[=\-*_~#|+]+$/.test(txt)) return txt;
    }
    return rows.length + ' comment lines';
  }

  function makeBlock(rows, isBlockComment) {
    var blk = el('div', 'blk');
    var hd = el('div', 'hd');
    hd.appendChild(el('i', 'tw'));
    hd.appendChild(el('span', 'prev', previewOf(rows)));
    hd.appendChild(el('span', 'tag', isBlockComment ? 'note' : 'comment'));
    hd.setAttribute('role', 'button');
    hd.setAttribute('tabindex', '0');
    hd.title = 'Click to expand / collapse this explanation';
    blk.appendChild(hd);

    // count of hidden lines, shown when collapsed
    hd.addEventListener('click', function () {
      blk.classList.toggle('open');
    });
    hd.addEventListener('keydown', function (e) {
      if (e.key === 'Enter' || e.key === ' ') { e.preventDefault(); blk.classList.toggle('open'); }
    });
    return blk;
  }

  /* ---------- global code-view toggles ------------------------ */
  function setHideComments(on) {
    document.body.classList.toggle('hide-comments', on);
    var cb = $('#tgComments');
    if (cb) { cb.checked = on; cb.parentNode.classList.toggle('on', on); }
    try { localStorage.setItem('cpp-hide-comments', on ? '1' : '0'); } catch (e) {}
  }
  function setFoldAll(open) {
    $$('.code .blk').forEach(function (b) { b.classList.toggle('open', open); });
    var cb = $('#tgFold');
    if (cb) { cb.checked = open; cb.parentNode.classList.toggle('on', open); }
    try { localStorage.setItem('cpp-fold', open ? '1' : '0'); } catch (e) {}
  }
  function setLineNums(on) {
    document.body.classList.toggle('no-nums', !on);
    var cb = $('#tgNums');
    if (cb) { cb.checked = on; cb.parentNode.classList.toggle('on', on); }
    try { localStorage.setItem('cpp-nums', on ? '1' : '0'); } catch (e) {}
  }

  /* ============================================================
     TRACE-TABLE TRAINER
     Rows are hidden one at a time so the student predicts the next row
     before checking. This is the exact skill the exam tests.
     ============================================================ */
  function wireTrace(tables) {
    tables.forEach(function (tbl, idx) {
      var rows = $$('tbody tr', tbl);
      var box = tbl.parentNode;
      var shown = rows.length;   // open by default; 'Hide all' starts the drill

      var tools = el('div', 'trace-tools');
      var reveal = el('button', 'btn-mini', 'Reveal next row');
      var showAll = el('button', 'btn-mini', 'Reveal all');
      var reset = el('button', 'btn-mini', 'Hide all');
      tools.appendChild(reveal);
      tools.appendChild(showAll);
      tools.appendChild(reset);

      var count = el('span', 'tbl-cap', '');
      box.parentNode.insertBefore(tools, box);
      box.parentNode.insertBefore(count, tools.nextSibling);

      function paint() {
        rows.forEach(function (r, i) {
          r.hidden = i >= shown;
          r.classList.remove('hi');
        });
        if (shown > 0 && shown - 1 < rows.length) rows[shown - 1].classList.add('hi');
        count.textContent = shown === 0
          ? 'Predict each row, then reveal.'
          : shown >= rows.length
            ? 'All ' + rows.length + ' rows shown.'
            : 'Row ' + shown + ' of ' + rows.length + ' shown.';
        reveal.disabled = shown >= rows.length;
      }
      reveal.addEventListener('click', function () { shown = Math.min(shown + 1, rows.length); paint(); });
      showAll.addEventListener('click', function () { shown = rows.length; paint(); });
      reset.addEventListener('click', function () { shown = 0; paint(); });
      paint();
    });
  }

  /* ============================================================
     PAGE BOOT
     ============================================================ */
  function boot() {
    applyTheme();
    renderProgress();

    var tb = $('#themeBtn');
    if (tb) tb.addEventListener('click', toggleTheme);

    var rb = $('#resetBtn');
    if (rb) rb.addEventListener('click', function () {
      if (confirm('Clear every "studied" tick?')) {
        localStorage.removeItem(DONE_KEY);
        $$('.file-link .tick').forEach(function (t) { t.checked = false; });
        renderProgress();
      }
    });

    var me = $('#navToggle');
    if (me) me.addEventListener('click', function () {
      document.body.classList.toggle('nav-open');
    });
    var sc = $('#scrim');
    if (sc) sc.addEventListener('click', function () { document.body.classList.remove('nav-open'); });

    /* ---- per-file page ------------------------------------- */
    var host = $('#code');
    if (host) {
      var f = window.CURRENT_FILE;
      buildSidebar(f.path);
      wireSearch();
      renderCode(host, f.code);

      /* --- the bare listing at the very top of the page --------- */
      var bareHost = $('#codeBare');
      if (bareHost && f.bare != null) {
        renderCode(bareHost, f.bare);
        var cbb = $('#copyBareBtn');
        if (cbb) cbb.addEventListener('click', function () {
          navigator.clipboard.writeText(f.bare).then(
            function () { toast('Comment-free code copied'); },
            function () { toast('Copy failed - select the text manually'); }
          );
        });
      }

      var saved = function (k, dflt) {
        var v = localStorage.getItem(k);
        return v === null ? dflt : v === '1';
      };
      setHideComments(saved('cpp-hide-comments', false));
      setFoldAll(saved('cpp-fold', false));
      setLineNums(saved('cpp-nums', true));

      var cb1 = $('#tgComments');
      if (cb1) cb1.addEventListener('change', function () { setHideComments(cb1.checked); });
      var cb2 = $('#tgFold');
      if (cb2) cb2.addEventListener('change', function () { setFoldAll(cb2.checked); });
      var cb3 = $('#tgNums');
      if (cb3) cb3.addEventListener('change', function () { setLineNums(cb3.checked); });

      var eb = $('#examBtn');
      if (eb) eb.addEventListener('click', function () {
        var on = !document.body.classList.contains('exam');
        document.body.classList.toggle('exam', on);
        setHideComments(on);
        eb.textContent = on ? '\u2713 Exit exam mode' : 'Exam mode';
        eb.classList.toggle('on', on);
      });

      var cp = $('#copyBtn');
      if (cp) cp.addEventListener('click', function () {
        navigator.clipboard.writeText(f.code).then(
          function () { toast('Full source copied to the clipboard'); },
          function () { toast('Copy failed - select the code manually'); }
        );
      });

      wireTrace($$('table.grid'));

      /* ---- keyboard shortcuts ------------------------------ */
      var keys = $('#keys');
      document.addEventListener('keydown', function (e) {
        if (e.metaKey || e.ctrlKey || e.altKey) return;
        if (/^(INPUT|TEXTAREA)$/.test((document.activeElement || {}).tagName)) return;
        var k = e.key.toLowerCase();
        if (k === 'c') { setHideComments(!document.body.classList.contains('hide-comments')); e.preventDefault(); }
        else if (k === 'f') { setFoldAll(!document.querySelector('.code .blk.open')); e.preventDefault(); }
        else if (k === 'n') { var n = $('#nextLink'); if (n) location.href = n.href; }
        else if (k === 'p') { var p = $('#prevLink'); if (p) location.href = p.href; }
        else if (k === 'e') { if (eb) eb.click(); }
        else if (k === '?') { if (keys && keys.showModal) keys.showModal(); }
        else if (k === 't') { toggleTheme(); }
      });
      var kb = $('#keysBtn');
      if (kb) kb.addEventListener('click', function () { if (keys && keys.showModal) keys.showModal(); });
      var kc = $('#keysClose');
      if (kc) kc.addEventListener('click', function () { keys.close(); });
      var kb2 = $('#topKeys');
      if (kb2) kb2.addEventListener('click', function () { if (keys && keys.showModal) keys.showModal(); });
    }

    /* ---- dashboard ----------------------------------------- */
    if ($('.dash')) {
      buildSidebar(null);
      wireSearch();
      var nav2 = $('#nav');
      if (nav2) nav2.hidden = false;
    }
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', boot);
  } else { boot(); }
})();