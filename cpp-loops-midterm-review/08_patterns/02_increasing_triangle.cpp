// ============================================================
// PROGRAM: Pattern 2 - An Increasing Triangle of Stars
// TOPIC: an inner bound that is the ROW number, not a constant
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - THE central idea of this whole folder: the inner loop's bound can be a
//   VARIABLE, and when it is the outer loop's own variable the row count grows
//   as the outer loop runs.
// - How to derive that bound from the drawing in six steps instead of
//   memorising `j <= i`.
// - Why `cout << "* "` (star AND gap) is the right form here and `cout << "*"`
//   is the wrong one.
// - That the number of stars printed overall is 1 + 2 + 3 + 4 + 5 = 15, not 25.
//
// EXPECTED OUTPUT:
// === Part 1: the increasing triangle ===
// *
// * *
// * * *
// * * * *
// * * * * *
// row 1 printed 1 star, row 5 printed 5 stars
// total stars printed = 1 + 2 + 3 + 4 + 5 = 15
//
// === Part 2: the same triangle with a wider gap between the stars ===
// *
// *  *
// *  *  *
// *  *  *  *
// *  *  *  *  *
// one more space in the `col > 1` test, and every gap grows - nothing else
//
// === Part 3: the inner bound as an expression: a triangle of height 7 ===
// *
// * *
// * * *
// * * * *
// * * * * *
// * * * * * *
// * * * * * * *
// the constant 7 only appears in the OUTER loop; the inner bound is still row
//
// === Part 4: what the WRONG inner bound prints ===
// * * * * *
// * * * * *
// * * * * *
// * * * * *
// * * * * *
// with `col <= 5` inside, every row prints 5 stars, so this is a square
// and NOT a triangle
//
// IMPORTANT SYNTAX:
// for (int row = 1; row <= 5; row++)     -> the OUTER loop counts the ROWS
//     for (int col = 1; col <= row; col++) -> the INNER bound is `row` itself
//         if (col > 1) { cout << " "; }   -> gap BEFORE all but the first item
//         cout << "*";                   -> the item, with no trailing gap
//     cout << endl;                        -> one break per row, after the inner loop
//
// THE ONE-LINE DIFFERENCE FROM A SQUARE
//   Square:      for (int col = 1; col <= 5;   col++)   <- a constant
//   Triangle:    for (int col = 1; col <= row; col++)   <- the row variable
//   Every other line of the two programs is identical. One number in one
//   position is the whole difference between a square and a triangle.
//
// STEP-BY-STEP EXPLANATION:
// 1. Draw the shape, then count its rows. Five lines tall, so the outer loop
//    runs 1 to 5.
// 2. Count the stars in the FIRST row. One star, so the inner loop must be
//    able to run once on row 1.
// 3. Count the stars in the LAST row. Five stars, so the inner loop must be
//    able to run five times by row 5.
// 4. So the number of stars per row is not a constant at all - it rises from 1
//    to 5 in step with the row number. "Row N contains N items."
// 5. That sentence IS the code. `col <= row` means "keep going while the cell
//    counter has not yet reached the row number", which is exactly "N items".
// 6. Part 2 changes only the printed string, Part 3 changes only the outer
//    constant, and Part 4 puts the constant back inside the inner loop to show
//    what the mistake looks like.
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

    cout << "=== Part 1: the increasing triangle ===" << endl;

    for (int row = 1; row <= 5; row++) {
        // THE OUTER LOOP COUNTS THE ROWS: 1, 2, 3, 4, 5.
        // It knows which row is being printed, and it makes that number
        // available to the inner loop through the variable `row`.

        for (int col = 1; col <= row; col++) {
            // THE KEY LINE OF THIS ENTIRE FILE.
            //
            // THE INNER BOUND IS `row`, THE OUTER LOOP'S OWN VARIABLE - NOT A
            // CONSTANT. Compare it with the square in 01_square_stars.cpp, where
            // the same line reads `col <= 5`. Here the bound MOVES as the outer
            // loop advances:
            //
            //     outer row = 1  ->  test is `col <= 1`  ->  col: 1        -> 1 star
            //     outer row = 2  ->  test is `col <= 2`  ->  col: 1, 2     -> 2 stars
            //     outer row = 3  ->  test is `col <= 3`  ->  col: 1, 2, 3  -> 3 stars
            //     outer row = 4  ->  test is `col <= 4`  ->  col: 1..4     -> 4 stars
            //     outer row = 5  ->  test is `col <= 5`  ->  col: 1..5     -> 5 stars
            //
            // `row` is not changing WHILE the inner loop runs - it is fixed for
            // the whole of that row. It changes once per outer pass, between
            // one finished row and the next. So the count of stars per row is
            // decided at the moment the outer loop enters each new row, and the
            // inner loop then faithfully makes that many stars.
            //
            // `col` still restarts at 1 each row, because `int col = 1;` is
            // part of the inner loop's header and headers re-run from the top.

            // THE GAP IS PRINTED BEFORE EACH STAR EXCEPT THE FIRST ON THE LINE.
            // The test `col > 1` asks "is this cell something other than the
            // first?", so the very first star of every row lands flush against
            // the left edge and all the later ones are preceded by a space.
            //
            // THE TEXTBOOK SHORTCUT IS `cout << "* ";` - a star and a gap in
            // one statement - and it prints the same visible shape. This file
            // deliberately does NOT use it, because it puts a space at the END
            // of every line as well, including the last one. A trailing space
            // is invisible on screen but it is a real character: it makes the
            // program's output differ from an expected-output block whose
            // trailing whitespace an editor has trimmed, and it breaks any
            // later program that reads this text back.
            //
            // Printing the gap BEFORE the item avoids that entirely: a gap is
            // needed only BETWEEN two items, never after the last one.
            if (col > 1) {
                cout << " ";
            }
            cout << "*";
            // The star itself is printed with NO trailing space. Compare the
            // square in 01_square_stars.cpp, where no gap is wanted at all and
            // `cout << "*";` is used on its own. The difference between the two
            // files is the gap, not the star.
        }

        // ONE `endl` PER ROW, placed AFTER the inner loop and INSIDE the outer
        // loop. Placing it inside the inner loop would put each star on its own
        // line and there would be no triangle.
        cout << endl;
    }

    cout << "row 1 printed 1 star, row 5 printed 5 stars" << endl;
    cout << "total stars printed = 1 + 2 + 3 + 4 + 5 = " << (1 + 2 + 3 + 4 + 5) << endl;
    // The count is an ADDITION here, not a multiplication. This is worth
    // pausing on: a 5x5 square prints 5 x 5 = 25 stars because every row is the
    // same length, but a triangle's rows are all different lengths, so there is
    // no single multiplication to do. Add the rows: 1 + 2 + 3 + 4 + 5 = 15. Any
    // question that asks "how many stars" for a pattern like this wants the sum.

    cout << endl;
    cout << "=== Part 2: the same triangle with a wider gap between the stars ==="
         << endl;

    // THE ONLY CHANGE IS `"  "` INSTEAD OF `" "` INSIDE THE `col > 1` TEST.
    // Two spaces of gap instead of one, and every gap in the shape grows by one
    // character. The loops, the bounds and the number of stars are untouched.
    // This is worth seeing because it shows that the SPACING of a pattern is a
    // free parameter: it is one string literal, and it can be tuned without
    // touching the logic that produces the shape.
    for (int row = 1; row <= 5; row++) {
        for (int col = 1; col <= row; col++) {
            if (col > 1) {
                cout << "  ";
            }
            cout << "*";
        }
        cout << endl;
    }

    cout << "one more space in the `col > 1` test, and every gap grows - nothing else"
         << endl;

    cout << endl;
    cout << "=== Part 3: the inner bound as an expression: a triangle of height 7 ===" << endl;

    // ONLY THE OUTER BOUND CHANGED: 5 became 7. The inner loop still says
    // `col <= row`, so it needs no editing at all when the triangle gets taller.
    // This is the practical reward for making the inner bound a variable: the
    // height of the pattern lives in exactly ONE place.
    for (int row = 1; row <= 7; row++) {
        for (int col = 1; col <= row; col++) {
            if (col > 1) {
                cout << " ";
            }
            cout << "*";
        }
        cout << endl;
    }

    cout << "the constant 7 only appears in the OUTER loop; the inner bound is still row"
         << endl;

    cout << endl;
    cout << "=== Part 4: what the WRONG inner bound prints ===" << endl;

    for (int row = 1; row <= 5; row++) {
        for (int col = 1; col <= 5; col++) {
            // THE MISTAKE: A CONSTANT 5 IN THE INNER BOUND, COPIED ACROSS FROM
            // THE SQUARE. The outer loop still counts rows, so five lines are
            // printed - but each is five stars long, so the shape is a square.
            if (col > 1) {
                cout << " ";
            }
            cout << "*";
        }
        cout << endl;
    }

    cout << "with `col <= 5` inside, every row prints 5 stars, so this is a square"
         << endl;
    cout << "and NOT a triangle" << endl;
    // Part 4 has the same outer loop as Part 1 and one different number in the
    // inner loop, and it produces a different shape. That is the cleanest proof
    // available that the SHAPE of a pattern is decided by the inner bound.

    // ------------------------------------------------------------
    // HOW I DERIVED THIS CODE
    // ------------------------------------------------------------
    // Never start from `j <= i`. Start from the paper, and do these six steps
    // in order. Every pattern in this folder comes out of this same procedure.
    //
    // STEP 1: COUNT THE ROWS IN THE DRAWING.
    //   The triangle is five lines tall: FIVE ROWS.
    //   Five lines of output can only come from five passes of the loop that
    //   produces lines. OUTER BOUND = 5  ->  `row <= 5`.
    //
    // STEP 2: COUNT THE ITEMS IN THE FIRST ROW.
    //   Look at the TOP row alone. It holds ONE star.
    //   So on the first outer pass the inner loop must run ONCE. If the first
    //   row held 3 items, the first inner pass would have to run three times.
    //   This step alone already rules out a constant inner bound of 5.
    //
    // STEP 3: COUNT THE ITEMS IN THE LAST ROW.
    //   The BOTTOM row holds FIVE stars. So on the last outer pass the inner
    //   loop must run five times.
    //   Compare with step 2: the first row needs 1 and the last row needs 5.
    //   THEY ARE DIFFERENT, and that is the finding that drives everything else.
    //
    // STEP 4: ASK HOW MANY ITEMS ARE IN ROW N.
    //   Write out what the drawing says, row by row:
    //       row 1 -> 1 item
    //       row 2 -> 2 items
    //       row 3 -> 3 items
    //       row 4 -> 4 items
    //       row 5 -> 5 items
    //   Now say it as a RULE rather than as a list: "row N contains N items."
    //   The formula mentions N. The item count DEPENDS ON THE ROW.
    //
    // STEP 5: DECIDE THE TWO BOUNDS.
    //   OUTER BOUND = number of rows              = 5  ->  `row <= 5`
    //   INNER BOUND = items in the current row    = row -> `col <= row`
    //   Note that the inner bound is not "5". It is a variable that happens to
    //   reach 5 on the last row.
    //
    // STEP 6: STATE WHAT THE INNER BOUND DEPENDS ON.
    //   THIS PROGRAM'S ANSWER: it depends on `row`, the OUTER LOOP'S VARIABLE.
    //   Say the whole sentence out loud, because it is the answer to the
    //   question examiners actually ask:
    //       "the inner loop runs while the cell counter is less than or equal
    //        to the current row number, so the number of items per row grows
    //        by one on every pass of the outer loop."
    //
    //   Compare with the square in 01_square_stars.cpp, where step 6's answer
    //   is "it depends on nothing - it is the constant 5". One sentence of
    //   difference, one number of difference in the code.
    //
    // ------------------------------------------------------------
    // TRACE TABLE - every execution of the inner body, all 15 of them
    // ------------------------------------------------------------
    // +-------+-------+-------+--------------+-------------+----------------+
    // | Pass  | OUTER | INNER | Stars on     | Gap printed | Stars printed  |
    // |       | row   | col   | this row so  | before this | so far         |
    // |       |       |       | far          | star        |                |
    // +-------+-------+-------+--------------+-------------+----------------+
    // |   1   |   1   |   1   |      1       |   (none)    |       1        |
    // |   2   |   2   |   1   |      1       |   (none)    |       2        |
    // |   3   |   2   |   2   |      2       |   one       |       3        |
    // |   4   |   3   |   1   |      1       |   (none)    |       4        |
    // |   5   |   3   |   2   |      2       |   one       |       5        |
    // |   6   |   3   |   3   |      3       |   two       |       6        |
    // |   7   |   4   |   1   |      1       |   (none)    |       7        |
    // |   8   |   4   |   2   |      2       |   one       |       8        |
    // |   9   |   4   |   3   |      3       |   two       |       9        |
    // |  10   |   4   |   4   |      4       |   three     |      10        |
    // |  11   |   5   |   1   |      1       |   (none)    |      11        |
    // |  12   |   5   |   2   |      2       |   one       |      12        |
    // |  13   |   5   |   3   |      3       |   two       |      13        |
    // |  14   |   5   |   4   |      4       |   three     |      14        |
    // |  15   |   5   |   5   |      5       |   four      |      15        |
    // +-------+-------+-------+--------------+-------------+----------------+
    // | TOTAL | 5 rows| 1..5  |  1,2,3,4,5  |  0+1+2+3+4 |      15        |
    // +-------+-------+-------+--------------+-------------+----------------+
    //
    // THE "GAP PRINTED" COLUMN IS THE INTERESTING ONE. It says `(none)` on the
    // FIRST execution of every row and a count on every execution after it,
    // which is exactly what `if (col > 1)` does. Printing the gap BEFORE the
    // star rather than after it is what keeps every line free of a trailing
    // space - and the totals row shows the whole run added up: 0 + 1 + 2 + 3 + 4
    // = 10 gaps for 15 stars, because the first star of each row never needs
    // one.
    // | Pass   | OUTER | INNER | Stars on     | Star + gap       | Stars printed |
    // |        | row   | col   | this row so  | printed          | so far        |
    // |        |       |       | far          |                  |              |
    // +--------+-------+-------+--------------+------------------+--------------+
    // |    1   |   1   |   1   |      1       | "* "             |      1        |
    // |    2   |   2   |   1   |      1       | "* "             |      2        |
    // |    3   |   2   |   2   |      2       | "*  "            |      3        |
    // |    4   |   3   |   1   |      1       | "* "             |      4        |
    // |    5   |   3   |   2   |      2       | "*  "            |      5        |
    // |    6   |   3   |   3   |      3       | "*  *  "         |      6        |
    // |    7   |   4   |   1   |      1       | "* "             |      7        |
    // |    8   |   4   |   2   |      2       | "*  "            |      8        |
    // |    9   |   4   |   3   |      3       | "*  *  "         |      9        |
    // |   10   |   4   |   4   |      4       | "*  *  *  "      |     10        |
    // |   11   |   5   |   1   |      1       | "* "             |     11        |
    // |   12   |   5   |   2   |      2       | "*  "            |     12        |
    // |   13   |   5   |   3   |      3       | "*  *  "         |     13        |
    // |   14   |   5   |   4   |      4       | "*  *  *  "      |     14        |
    // |   15   |   5   |   5   |      5       | "*  *  *  *  "   |     15        |
    // +--------+-------+-------+--------------+------------------+--------------+
    // | TOTAL  | 5 rows | 1..5  |  1,2,3,4,5  | the whole shape  |     15        |
    // +--------+-------+-------+--------------+------------------+--------------+
    //
    // READ THE INNER COLUMN DOWN: 1, then 1 2, then 1 2 3, then 1 2 3 4, then
    // 1 2 3 4 5. It is the same pattern as any nested trace - the inner counter
    // restarts at 1 every time - but its END value grows on each new group. In a
    // square the end value was stuck at 5; here it climbs 1, 2, 3, 4, 5.
    //
    // WHY THE TOTAL IS 15 AND NOT 25
    //   A square has every row the same length, so the total is a multiplication:
    //   rows x cells = 5 x 5 = 25. A triangle does NOT have that, because the
    //   rows are different lengths and there is no single "cells per row" to
    //   multiply by. The total is the SUM of the row lengths: 1 + 2 + 3 + 4 + 5
    //   = 15. If an exam asks how many stars, add the rows. If it asks how many
    //   executions of the inner body, add the rows too - they are the same
    //   number here, because every execution prints exactly one star.
    //
    // `cout << "*";` VERSUS `cout << "* ";`
    //   `"* "` prints the symbol and a following gap, so items end up SEPARATED:
    //       * * *
    //   `"*"` prints the symbol alone, so items end up TOUCHING:
    //       ***
    //   Both are legitimate, and which one is correct depends entirely on the
    //   drawing you were given. Solid blocks of symbols want `"*"`. Anything
    //   where the symbols read as separate items - triangles, grids, hollow
    //   squares - wants a gap between them.
    //
    //   THIS FILE USES NEITHER BARE FORM. It prints the gap first and the star
    //   second, guarded by `if (col > 1)`:
    //
    //       if (col > 1) { cout << " "; }
    //       cout << "*";
    //
    //   That produces `* * *` - the same visible shape as `cout << "* ";` -
    //   without leaving a space at the END of the last line. `"* "` always puts
    //   a gap after the final item as well, so every line ends in a space. On
    //   screen that is invisible, but it is a real character: it makes the
    //   program's output differ from an expected-output block whose trailing
    //   whitespace an editor has trimmed, and it would confuse any later program
    //   reading the text back.
    //
    //   THE GENERAL RULE: a gap belongs BETWEEN two items, never after the last
    //   one. Print the gap before the item and guard it with a test, and no line
    //   can ever end in a space.
    //
    // WHY `endl` GOES AFTER THE INNER LOOP, NOT INSIDE IT
    //   A row is finished when the inner loop finishes, not before. Putting
    //   `endl` inside the inner loop breaks the line after every STAR, so the
    //   triangle would come out as 15 lines of one star. Putting it after the
    //   inner loop breaks the line once per completed ROW, which is what a
    //   triangle is. The placement of `endl` is a decision about the SHAPE:
    //   inside the inner loop gives you lines per item, after the inner loop
    //   gives you lines per row.
    //
    // COMMON TRAP
    //   Copying the inner bound from a square, so the program prints five rows
    //   of five stars. It is the single most common pattern mistake and Part 4
    //   exists to let you see it side by side. The symptom is always the same:
    //   the right NUMBER of lines with the wrong THINGS on them.
    //
    //   The second trap is `col < row` instead of `col <= row`. That prints a
    //   triangle with 0, 1, 2, 3, 4 stars - four stars in the last row and a
    //   blank first line. One character of difference, and the shape is wrong.
    //   When step 2 told you the first row holds ONE item, that is proof the
    //   test must be `<=`, not `<`.
    //
    //   The third trap is expecting the triangle to be the same width all the
    //   way down. `row` grows the COUNT of stars; it does nothing at all to
    //   where they sit. Aligning a triangle's left edge is the default with no
    //   extra work, and shifting it rightwards needs extra loops, which is
    //   exactly what 07_right_aligned_triangle.cpp is for.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: What is the inner loop's bound in this program, and what does that make it do?  -> it is `row`, the outer loop's own variable, so the number of stars per row grows with the row number
// Q2: How many stars are printed in total, and why is it an addition rather than a multiplication?  -> 15, because the rows have different lengths (1 to 5) so there is no single cells-per-row figure to multiply by
// Q3: Why must the inner test be `col <= row` and not `col < row`?  -> the first row of the drawing holds one star, and only `<=` gives the inner loop one execution when row is 1
// Q4: If the inner bound were changed to the constant 5, what would the program print?  -> five rows of five stars - a square rather than a triangle - as Part 4 shows
// Q5: Why is `cout << endl;` placed after the inner loop here?  -> so the line breaks once per finished row; inside the inner loop it would break after every star and give 15 single-star lines
