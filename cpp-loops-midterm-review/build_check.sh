#!/usr/bin/env bash
# ============================================================
# build_check.sh - compile every .cpp file in the project
# ============================================================
# WHAT IT DOES:
#   1. Finds every .cpp file in every folder.
#   2. Compiles each one with warnings switched on.
#   3. Prints a final PASS / FAIL summary.
#
# HOW TO USE:
#   ./build_check.sh          compile everything
#   ./build_check.sh -run     compile AND run (only safe for files that
#                             do not ask for keyboard input)
# ============================================================
GXX="g++"
if ! command -v "$GXX" >/dev/null 2>&1; then
    if [ -x /mnt/c/msys64/ucrt64/bin/g++.exe ]; then
        GXX=/mnt/c/msys64/ucrt64/bin/g++.exe
    fi
fi

FLAGS="-std=c++17 -Wall -Wextra"
PASS=0
FAIL=0
FAILED_LIST=""

echo "=============================================="
echo " COMPILING ALL .cpp FILES"
echo " compiler : $($GXX --version 2>/dev/null | head -1)"
echo " flags    : $FLAGS"
echo "=============================================="

while IFS= read -r f; do
    if [ -n "$WSLPATH_OVERRIDE" ]; then :; fi
    # Windows-native compilers need Windows paths.
    SRC="$f"
    OUT="/tmp/cppbuild_$(basename "$f" .cpp).exe"
    if command -v wslpath >/dev/null 2>&1; then
        case "$f" in /mnt/*) SRC=$(wslpath -w "$f");; esac
        case "$OUT" in /mnt/*) OUT=$(wslpath -w "$OUT");; esac
    fi
    ERR=$($GXX $FLAGS -o "$OUT" "$SRC" 2>&1 </dev/null)
    if [ $? -eq 0 ]; then
        if [ -z "$ERR" ]; then
            PASS=$((PASS+1))
            printf "  [ OK ]   %s\n" "$f"
        else
            PASS=$((PASS+1))
            printf "  [WARN]   %s\n" "$f"
            echo "$ERR" | sed 's/^/            /'
        fi
    else
        FAIL=$((FAIL+1))
        FAILED_LIST="$FAILED_LIST\n  $f"
        printf "  [FAIL]   %s\n" "$f"
        echo "$ERR" | sed 's/^/            /'
    fi
done < <(find . -name '*.cpp' | sort)

echo "=============================================="
echo " TOTAL FILES : $((PASS+FAIL))"
echo " COMPILED OK : $PASS"
echo " FAILED      : $FAIL"
[ "$FAIL" -gt 0 ] && echo -e " FAILED LIST :$FAILED_LIST"
echo "=============================================="
[ "$FAIL" -eq 0 ] && echo " ALL FILES COMPILE SUCCESSFULLY."
exit $FAIL
