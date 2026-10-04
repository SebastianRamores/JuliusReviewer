#!/usr/bin/env bash
# ============================================================
# rebuild.sh - regenerate everything from the .cpp sources
# ============================================================
# RUN THIS AFTER YOU EDIT ANY .cpp FILE:
#
#   ./rebuild.sh
#
# It does three things, in order:
#   1. tools/fold_comments.py  - turns long `//` runs into foldable
#                                /* ... */ blocks (idempotent)
#   2. tools/make_viewer.py    - rebuilds the HTML study viewer from the
#                                real sources, so it can never drift
#   3. build_check.sh          - compiles every .cpp with warnings on
#
# SAFE TO RUN AS OFTEN AS YOU LIKE.
# ============================================================
set -e
cd "$(dirname "$0")"

echo
echo "### 1/3  making comment blocks foldable"
python3 tools/fold_comments.py

echo
echo "### 2/3  rebuilding the HTML viewer"
python3 tools/make_viewer.py

echo
echo "### 3/3  compiling every example"
./build_check.sh

echo
echo "Open viewer/index.html in a browser to study."
