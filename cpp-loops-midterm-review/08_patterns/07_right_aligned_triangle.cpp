// ============================================================
// PROGRAM: Pattern 7 - A Right-Aligned Triangle of Stars
// TOPIC: leading spaces printed by a THIRD loop
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - How to print `    *`, `   * *`, `  * * *`, ` * * * *`, `* * * * *`.
// - That each extra leading space is ONE extra execution of a SEPARATE loop
//   that prints a single space, sitting between the two star loops.
// - That a pattern with leading indentation has THREE directions in the drawing,
//   and therefore three loops.
// - The one-line `cout << " ";` alternative, and why this project prefers the
//   loop.
//
// EXPECTED OUTPUT:
// === Part 1: the right-aligned triangle ===
//     *
//    * *
//   * * *
//  * * * *
// * * * * *
// row 1 had 4 leading spaces and 1 star
// row 5 had 0 leading spaces and 5 stars
// total stars = 15, total spaces = 10, total characters = 25
//
// === Part 2: the same triangle with 2 spaces per step instead of 1 ===
//         *
//       * *
//     * * *
//   * * * *
// * * * * *
// the star loop is untouched; only the space loop's count changed
//
// === Part 3: the non-aligned starting point, for comparison ===
// *
// * *
// * * *
// * * * *
// * * * * *
// this is 02_increasing_triangle.cpp: no space loop at all
//
// IMPORTANT SYNTAX:
// THE THREE BOUNDS THIS PATTERN NEEDS
//   for (int row = 1; row <= 5; row++)       -> the ROW loop: which row
//     for (int s = 1; s <= 5 - row; s++)     -> the SPACE loop: the lead of spaces
//         cout << " ";
//     }
//     for (int col = 1; col <= row; col++) { -> the STAR loop: still `col <= row`
//         if (col > 1) { cout << " "; }
//         cout << "*";
//     }
//     cout << endl;                            -> ONE break, after both inner loops
//
// THREE LOOPS, THREE DIRECTIONS
//   SPACE LOOP  moves LEFT across the screen  -> the leading indentation
//   STAR LOOP   moves RIGHT across the screen -> the stars on the row
//   ROW LOOP    moves DOWN the screen         -> which row is being printed
//   One loop per direction. The drawing has three directions, so it needs three.
//
// STEP-BY-STEP EXPLANATION:
// 1. The star part is exactly the increasing triangle of
//    02_increasing_triangle.cpp: outer loop on rows, inner loop bounded by `row`.
// 2. The difference is the indentation in front of each row.
// 3. Row 1 has four spaces, row 2 has three, row 3 has two, row 4 has one, row 5
//    has none. The count of spaces FALLS as the row number RISES.
// 4. So the space loop runs while `s <= 5 - row`, giving 4, 3, 2, 1, 0 spaces.
// 5. The space loop is written BEFORE the star loop, because the spaces have to
//    be printed before the stars they push along.
// 6. `endl` goes after BOTH inner loops, or row 1 would break before its stars.
// ============================================================

#include <iostream>
// The only header this project uses. It supplies `cout` for printing and
// `endl` for ending a line. The C++ language can calculate, store and compare
// but it cannot talk to a screen, so every piece of terminal output comes from
// this library, and this include line is what makes it available.

using namespace std;
// A NAMESPACE is a labelled box that groups related names so two libraries
// cannot fight over the same word. `std` is the box holding the C++ STANDARD
// library, where `cout` and `endl` live. The `::` is the SCOPE RESOLUTION
// OPERATOR and means "inside", so `std::cout` reads "the cout inside std".
// This line tells the compiler to take bare names from that box, which is why
// plain `cout` works in this file.

int main() {
// `main` is the ENTRY POINT: the first function the operating system runs when
// the program starts. `int` is the RETURN TYPE, handing a whole number back
// as an exit status when main finishes. `()` is the parameter list and it is
// empty, since this program takes no arguments and reads no keyboard input.
// The `{ }` braces are the BODY, executed from top to bottom.

    cout << "=== Part 1: the right-aligned triangle ===" << endl;

    // THE ROW LOOP AND THE SPACE LOOP PRINT NOTHING BETWEEN THEM, so every row
    // begins flush against the margin.
    for (int row = 1; row <= 5; row++) {
        // THE OUTER LOOP COUNTS THE ROWS, as in every pattern in this folder.

        for (int s = 1; s <= 5 - row; s++) {
            // THE SPACE LOOP - THE NEW THING IN THIS FILE.
            //
            // ITS BODY PRINTS EXACTLY ONE SPACE AND NOTHING ELSE. That is the
            // whole trick: a loop that runs four times prints four spaces, and
            // the number of iterations IS the indentation.
            //
            // THE BOUND IS `5 - row` - THE TOTAL WIDTH MINUS THE ROW NUMBER.
            //     row 1  ->  s: 1 2 3 4  ->  4 spaces
            //     row 2  ->  s: 1 2 3    ->  3 spaces
            //     row 3  ->  s: 1 2      ->  2 spaces
            //     row 4  ->  s: 1        ->  1 space
            //     row 5  ->  s: (none)   ->  0 spaces
            //
            // NOTE THAT THE SPACE COUNT FALLS AS THE ROW NUMBER RISES, which is
            // the whole reason for the subtraction. This is exactly the bound
            // from 03_decreasing_triangle.cpp, reused for the indentation:
            // anything that gets SHORTER going down the drawing is written as
            // `total - row`.
            //
            // THE OFF-BY-ONE THAT MATTERS HERE: the test uses `<=` against
            // `5 - row`, and `5 - row` reaches 0 on row 5, which correctly
            // prints NO spaces at all. Written as `s < 5 - row` the bottom row
            // would start with one space and the whole shape would sit one place
            // too far right - a shape that still looks like a triangle but is
            // not flush against the right-hand edge.
            cout << " ";
        }

        for (int col = 1; col <= row; col++) {
            // THE STAR LOOP IS COMPLETELY UNCHANGED from
            // 02_increasing_triangle.cpp: `col <= row`, so row N prints N stars.
            //
            // That is worth pausing on. Adding the indentation did not change
            // the star loop at all - the two loops are independent, each doing
            // its own job, and together they produce the whole row.
            if (col > 1) {
                cout << " ";
            }
            cout << "*";
        }

        cout << endl;
        // ONE BREAK, AND IT GOES AFTER BOTH INNER LOOPS.
        //
        // This is the placement mistake specific to three-loop patterns. Put
        // the `endl` between the space loop and the star loop and row 1 prints
        // four spaces, breaks, and prints its star on the next line - so the
        // triangle comes out with every star on a line of its own and all the
        // indentation stranded above.
        //
        // The rule is unchanged and worth restating: a ROW is finished when
        // everything that row contains has been printed. Here a row contains
        // spaces AND stars, so both loops have to run first.
    }

    cout << "row 1 had 4 leading spaces and 1 star" << endl;
    cout << "row 5 had 0 leading spaces and 5 stars" << endl;
    cout << "total stars = 15, total spaces = 10, total characters = "
         << (15 + 10) << endl;
    // Spaces: 0 + 1 + 2 + 3 + 4 = 10. Stars: 1 + 2 + 3 + 4 + 5 = 15. Both are
    // ADDITIONS, since each group has a different length. Total 25 characters,
    // which is a useful sanity check: every row comes out 5 characters wide,
    // because each row trades one space for one extra star. Row 1 is 4 + 1 and
    // row 5 is 0 + 5. A row of a different width would mean a loop is wrong.

    cout << endl;
    cout << "=== Part 2: the same triangle with 2 spaces per step instead of 1 ==="
         << endl;

    for (int row = 1; row <= 5; row++) {
        // ONLY THE SPACE LOOP'S COUNT CHANGED, and only by changing the value
        // printed from one space to two. The star loop and its bound are
        // identical to Part 1.
        for (int s = 1; s <= 5 - row; s++) {
            cout << "  ";
            // TWO spaces per execution instead of one. The bound is unchanged,
            // so the loop still runs 4, 3, 2, 1, 0 times - it just does twice
            // as much work each pass, and the triangle leans over further.
        }
        for (int col = 1; col <= row; col++) {
            if (col > 1) {
                cout << " ";
            }
            cout << "*";
        }
        cout << endl;
    }

    cout << "the star loop is untouched; only the space loop's count changed" << endl;
    // This is the practical benefit of using a loop for the spaces rather than a
    // fixed string: the SHAPE is decided by a bound, and the SIZE of each unit
    // is decided by a literal. Change either without touching the other.

    cout << endl;
    cout << "=== Part 3: the non-aligned starting point, for comparison ===" << endl;

    // THE SAME PROGRAM WITH THE SPACE LOOP DELETED. That is the only difference,
    // and the result is the left-aligned triangle from 02_increasing_triangle.cpp.
    //
    // The single-line alternative is to replace the whole space loop with one
    // statement:
    //
    //     cout << " ";    // for each of the row-1 spaces, written out by hand
    //
    // or, in a loop-free style, to print a literal run of spaces chosen per row
    // with an `if` chain - four spaces on row 1, three on row 2, and so on.
    //
    // BOTH WORK AND BOTH ARE SHORTER. This file uses a loop anyway, for three
    // reasons worth knowing before an exam:
    //
    //   1. It SCALES. Changing 5 to 7 means editing one number. Writing the
    //      spaces out by hand means editing every row of the program.
    //   2. It SHOWS THE STRUCTURE. The number of spaces and the number of stars
    //      are two independent counts, each produced by its own loop. That makes
    //      the shape easy to reason about and easy to trace.
    //   3. It IS THE GENERAL RULE. Three directions in the drawing means three
    //      loops. Any other solution is a special case of this one, worked out
    //      by hand instead of by a loop.
    for (int row = 1; row <= 5; row++) {
        for (int col = 1; col <= row; col++) {
            if (col > 1) {
                cout << " ";
            }
            cout << "*";
        }
        cout << endl;
    }

    cout << "this is 02_increasing_triangle.cpp: no space loop at all" << endl;

    // ------------------------------------------------------------
    // HOW I DERIVED THIS CODE
    // ------------------------------------------------------------
    // Build it from the drawing. The same six steps, with one extra question
    // that only this pattern asks.
    //
    // STEP 1: COUNT THE ROWS IN THE DRAWING.
    //   Five lines, so FIVE ROWS and OUTER BOUND = 5  ->  `row <= 5`.
    //   Count them as LINES OF THE DRAWING, ignoring the leading spaces - the
    //   spaces are part of a line, not extra lines.
    //
    // STEP 2: COUNT THE ITEMS IN THE FIRST ROW.
    //   The top row holds ONE star. So on the first pass the star loop must run
    //   once.
    //
    // STEP 3: COUNT THE ITEMS IN THE LAST ROW.
    //   The bottom row holds FIVE stars. So on the last pass the star loop must
    //   run five times.
    //
    // STEP 4: ASK HOW MANY ITEMS ARE IN ROW N.
    //       row 1 -> 1 star       row 4 -> 4 stars
    //       row 2 -> 2 stars      row 5 -> 5 stars
    //       row 3 -> 3 stars
    //   The rule: "row N contains N stars"  ->  the star loop is `col <= row`,
    //   exactly as in 02_increasing_triangle.cpp. That part is not in doubt.
    //
    //   THE EXTRA QUESTION, AND IT IS THE WHOLE OF THIS FILE:
    //
    //       HOW MANY SPACES COME BEFORE THE FIRST STAR OF ROW N?
    //           row 1 -> 4 spaces
    //           row 2 -> 3 spaces
    //           row 3 -> 2 spaces
    //           row 4 -> 1 space
    //           row 5 -> 0 spaces
    //
    //   The count FALLS while the row number RISES, so this bound also has to
    //   fall, so the bound is written as `5 - row` - the SAME expression as
    //   03_decreasing_triangle.cpp uses for its star count. Anything that gets
    //   shorter going down the drawing is `total - row`. `row - 1` would give
    //   0, 1, 2, 3, 4 instead, which is the exact opposite: that pushes the
    //   WIDE rows to the right and leaves the narrow ones at the margin.
    //
    //   Notice that this is a SECOND count in the same row. The row needs two
    //   numbers - a width for the indentation and a width for the stars - and
    //   the drawing supplies two different rules for them.
    //
    // STEP 5: DECIDE THE BOUNDS.
    //   OUTER BOUND  = 5 rows                     ->  `row <= 5`
    //   SPACE BOUND  = 5 - row spaces              ->  `s <= 5 - row`
    //   STAR BOUND   = N stars in row N           ->  `col <= row`
    //   THREE BOUNDS, because the drawing has THREE directions.
    //
    // STEP 6: STATE WHAT EACH INNER BOUND DEPENDS ON.
    //   THE SPACE LOOP: it depends on `row`, and it SHRINKS as the row grows -
    //       bound `5 - row`.
    //   THE STAR LOOP: it depends on `row`, and it GROWS as the row grows -
    //       bound `row`.
    //
    //       "before the stars, a loop prints one space while a counter runs up
    //        to 5 minus the row number, giving row N a lead of 5 - N spaces; then
    //        a second loop prints N stars while its counter runs up to the row
    //        number itself."
    //
    //   Compare with the other patterns in the folder, all of which have ONE
    //   inner loop:
    //     01_square_stars          inner bound = 5        constant
    //     02_increasing_triangle   inner bound = row      grows
    //     03_decreasing_triangle   inner bound = 5 - row  shrinks
    //     06_inverted_number       inner bound = row to 5 moving start
    //     07_right_aligned         TWO inner loops       spaces shrink, stars grow
    //
    //   The pattern of the folder is that each file adds ONE new idea to the
    //   shape. This one adds a third loop.
    //
    // ------------------------------------------------------------
    // TRACE TABLE - every pass of Part 1, showing all three loops
    // +-------+---------+----------------+------------+-----------+----------+------------+
    // | Pass  | OUTER   | SPACE LOOP     | Spaces     | STAR LOOP | Stars    | Chars    |
    // |       | row     | s takes        | printed    | col takes | printed  | so far   |
    // +-------+---------+----------------+------------+-----------+----------+------------+
    // |   1   |    1    | 1 2 3 4        |     4      |    1      |    1     |     4    |
    // |   2   |    1    | 1 2 3 4        |     4      |    2      |    1     |     5    |
    // |   3   |    1    | 1 2 3 4        |     4      |    3      |    1     |     6    |
    // |   4   |    1    | 1 2 3 4        |     4      |    4      |    1     |     7    |
    // |   5   |    1    | 1 2 3 4        |     4      |    5      |    1     |     8    |
    // |   6   |    2    | 1 2 3          |     3      |    1      |    2     |    10    |
    // |   7   |    2    | 1 2 3          |     3      |    2      |    2     |    11    |
    // |   8   |    2    | 1 2 3          |     3      |    3      |    2     |    12    |
    // |   9   |    2    | 1 2 3          |     3      |    4      |    2     |    13    |
    // |  10   |    2    | 1 2 3          |     3      |    5      |    2     |    14    |
    // |  11   |    3    | 1 2            |     2      |    1      |    3     |    16    |
    // |  ...  |   ...   | ...            |    ...     |   ...     |   ...    |    ...   |
    // |  17   |    4    | 1              |     1      |    4      |    4     |    22    |
    // |  18   |    5    | (none)         |     0      |    1      |    5     |    23    |
    // |  19   |    5    | (none)         |     0      |    5      |    5     |    25    |
    // +-------+---------+----------------+------------+-----------+----------+------------+
    //
    // THE LAST ROW OF THE TABLE IS THE COMPLETION OF ROW 5, not a row of its
    // own. The `Chars so far` column ends at 25, which is 10 spaces + 15 stars,
    // and it is the single best check on the whole program: if the final figure
    // is not 25, at least one of the three loops is wrong.
    //
    // NOTE THAT ROW 5 HAS A SPACE COUNT OF 0, so `s <= 5 - row` is
    // `s <= 0` and the loop never runs. The space loop DOES produce a pass where
    // its body does not execute, and the trace above records that as
    // `(none)`. A loop whose bound reaches 0 is not an error - it is the
    // mechanism that makes the bottom row flush against the right margin.

    //
    // THREE COLUMNS OF COUNTERS ARE NEEDED HERE, NOT TWO. A nested-loop trace
    // table normally records the outer and inner counters; this file has a
    // THIRD loop sitting between them, so the SPACE LOOP column is as
    // important as the other two. Omitting it would hide the entire mechanism.
    //
    // READ THE SPACES COLUMN DOWN: 4, 4, 4, 4, 3, 3, 3, 2, 2, 1, 1, 0. It FALLS
    // in blocks of four, three, two and one - one block per outer pass - and its
    // value per row is `5 - row`.
    // READ THE STARS COLUMN DOWN: 1, 1, 2, 1, 2, 3, 1, ... 4, 5. It RESETS once
    // per outer pass and its step size GROWS, because its value per row is
    // `row`.
    //
    // THE TWO COLUMNS MOVE IN OPPOSITE DIRECTIONS, AND THAT IS THE WHOLE PATTERN:
    // one falls as `5 - row`, the other rises as `row`, and their SUM is the same
    // on every row:
    //
    //       row 1:  4 spaces + 1 star  = 5 characters
    //       row 2:  3 spaces + 2 stars = 5 characters
    //       row 3:  2 spaces + 3 stars = 5 characters
    //       row 4:  1 space  + 4 stars = 5 characters
    //       row 5:  0 spaces + 5 stars = 5 characters
    //
    // Every row being exactly 5 wide is what makes the right-hand edge line up,
    // and it is the fastest check that both bounds are right. If one row comes
    // out a different width, exactly one of the two bounds is wrong.
    //
    // THE TOTAL EXECUTIONS OF EACH LOOP
    //   space loop: 0 + 1 + 2 + 3 + 4 = 10 executions, each printing one space
    //   star loop:  1 + 2 + 3 + 4 + 5 = 15 executions, each printing one star
    //   row loop:   5 executions
    //   Total characters printed = 10 + 15 = 25, which matches the "chars so
    //   far" column's final entry and is the best single check on the program.
    //
    // WHY A SEPARATE LOOP, AND NOT A STRING OF SPACES
    //   The alternative is one `cout << " ";` statement per space, written out
    //   by hand, or a literal like `cout << "    ";` for row 1 and a shorter one
    //   for row 2. Both produce identical output.
    //
    //   A loop is better here for three reasons, and the third is the one that
    //   matters in an exam:
    //
    //     1. SCALE. `row <= 5` becomes `row <= 9` and the whole pattern grows.
    //       Written out by hand, every row of code needs editing.
    //     2. NO OFF-BY-ONE TO HIDE. The bound `s <= 5 - row` states the rule,
    //       and makes the zero on the last row fall out automatically. Four
    //       literal spaces state nothing about why there are four.
    //     3. IT MATCHES THE RULE. The drawing has three directions - left,
    //       right, down - so the program has three loops. Any hand-written
    //       version is this program with one loop replaced by arithmetic, which
    //       is harder to check and easier to get wrong.
    //
    // `cout << "*";` VERSUS `cout << "* ";`
    //   Not about the stars here but about the same rule applied to the spaces.
    //   Printing `" "` after every star would separate the stars AND leave a
    //   space at the end of every row - and here it would ALSO undo the
    //   alignment, since the trailing space adds one to the row's width.
    //   Printing the gap BEFORE each star, guarded by `if (col > 1)`, keeps
    //   every row exactly as wide as it should be and ends no line with a space.
    //   THE RULE: a gap belongs BETWEEN two items, never after the last one.
    //
    // WHY `endl` GOES AFTER BOTH INNER LOOPS
    //   A row contains spaces AND stars, so it is finished only when BOTH inner
    //   loops have finished. The break therefore goes after the star loop, which
    //   is the last thing the row contains:
    //
    //       for (row ...) {
    //           for (s ...)   { cout << " "; }   // the indentation
    //           for (col ...) { ... stars ... }  // the stars themselves
    //           cout << endl;                    // <-- row complete
    //       }
    //
    //   BETWEEN the two inner loops it would end the line after the spaces, so
    //   every row's stars would appear on the line BELOW its indentation - a
    //   staircase of spaces with a lone star under each. That is the specific
    //   mistake a three-loop pattern invites, and it is worth checking for first
    //   when a right-aligned shape comes out wrong.
    //
    // COMMON TRAP
    //   Writing `s < row` instead of `s <= 5 - row`. This is the mistake this
    //   file is most likely to produce, because the star loop's bound really is
    //   `row` and it is tempting to make the space loop match. The rows then get
    //   MORE indented as they get wider, so the triangle leans the wrong way and
    //   the NARROW rows sit at the right margin. Every row still has the right
    //   number of stars, so the shape survives; only the alignment is wrong.
    //   Step 4's table catches it immediately: row 1 must have FOUR leading
    //   spaces and row 5 must have NONE.
    //
    //   The second trap is putting `endl` between the two inner loops, discussed
    //   above. The third is forgetting the gap BETWEEN the stars - printing
    //   `cout << "*";` with no `if (col > 1)` guard gives a solid block of stars
    //   pushed rightwards rather than a triangle of separated stars.
    //
    //   The fourth is assuming the star bound must change because the pattern
    //   looks different. It does not change at all: it is still `col <= row`.
    //   Only the space loop was added.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: How many leading spaces does row N of this pattern print, and why?  -> 5 - N spaces, because the count falls as the row number rises, which the bound `s <= 5 - row` expresses directly
// Q2: Why must the space loop come before the star loop in the source code?  -> the spaces have to be printed before the stars they push along, since cout sends text to the screen strictly in the order it is written
// Q3: Where must `cout << endl;` go, and what happens if it goes between the two inner loops?  -> after the star loop, once per row; between the loops it would break the line after the spaces and leave every row's stars stranded on the next line
// Q4: What is the star loop's bound in this pattern, and how does it compare with the plain increasing triangle?  -> it is `col <= row`, completely unchanged, because the indentation added a loop rather than altering the star count
// Q5: How many spaces are printed in total, and what check does that give you?  -> 0 + 1 + 2 + 3 + 4 = 10; together with 15 stars it gives 25 characters, so every row should be exactly 5 wide
