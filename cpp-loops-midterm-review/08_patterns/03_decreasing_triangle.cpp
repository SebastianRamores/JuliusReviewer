// ============================================================
// PROGRAM: Pattern 3 - A Decreasing Triangle of Stars
// TOPIC: an inner bound written as a CONSTANT minus the row number
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - How to make a pattern NARROW by writing the inner bound as `5 - row`.
// - Why that bound SHRINKS while the row counter GROWS, which is backwards from
//   almost everything else in this folder.
// - Why `col <= row` cannot produce this shape no matter how the outer loop
//   runs, and what to write instead.
// - Why numbering the rows from 0 makes the `5 - row` bound come out exactly
//   right with no off-by-one fudging.
//
// EXPECTED OUTPUT:
// === Part 1: the decreasing triangle ===
// * * * * *
// * * * *
// * * *
// * *
// *
// the first row has 5 stars, the last has 1, and each row loses exactly one
// total stars printed = 5 + 4 + 3 + 2 + 1 = 15
//
// === Part 2: the bound `5 - row` with the rows numbered from 1 ===
// * * * *
// * * *
// * *
// *
//
// the last row is EMPTY, because `5 - row` is 0 when row is 5
// this is the off-by-one, and it is why Part 1 numbers the rows from 0
//
// === Part 3: why `col <= row` cannot work here ===
// *
// * *
// * * *
// * * * *
// * * * * *
// `col <= row` grows with the row, so every row came out the same length
//
// IMPORTANT SYNTAX:
// for (int row = 0; row < 5; row++)        -> 5 rows, numbered 0 to 4
//     for (int col = 1; col <= 5 - row; col++)  -> the bound SHRINKS as row grows
//         if (col > 1) { cout << " "; }         -> gap BEFORE all but the first star
//         cout << "*";                          -> the star, no trailing gap
//     cout << endl;                              -> one break per finished row
//
// THE ONLY TWO THINGS THAT MAKE A PATTERN NARROW
//   1. the inner bound must SHRINK as the row number grows:  `5 - row`
//   2. the outer loop must visit its rows in the order the drawing shows
//   Change either one and the shape stops narrowing.
//
// STEP-BY-STEP EXPLANATION:
// 1. Count five rows, and note that the FIRST row printed is the WIDEST.
// 2. The first row has 5 stars and the last has 1, so the number of stars per
//    row FALLS by one each time.
// 3. A bound that falls by one each row is written as `5 - row`, because
//    subtracting a growing `row` from the fixed total 5 produces a falling
//    bound. This is the opposite of `col <= row`, which rises.
// 4. Numbering the rows from 0 makes `5 - row` give 5, 4, 3, 2, 1 exactly -
//    no adjustment needed. Part 2 shows what goes wrong starting from 1.
// 5. Part 3 demonstrates the failure of the growing bound: five identical rows.
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

    cout << "=== Part 1: the decreasing triangle ===" << endl;

    for (int row = 0; row < 5; row++) {
        // THE OUTER LOOP COUNTS THE ROWS: 0, 1, 2, 3, 4.
        //
        // THE ROWS ARE NUMBERED FROM 0, NOT 1, AND THAT IS THE POINT. The inner
        // bound below is `5 - row`, and starting `row` at 0 makes that bound
        // come out as 5, 4, 3, 2, 1 - exactly the row lengths the drawing asks
        // for, with no off-by-one correction anywhere.
        //
        // The test is `row < 5` rather than `row <= 5` precisely because the
        // last value needed is 4. With `row <= 5` the loop would run six times
        // and ask for a sixth row of `5 - 5` = 0 stars, which prints an empty
        // line. Part 2 shows that mistake in full.
        //
        // The row number is never printed. It exists only to drive the bound,
        // and starting it at 0 is a TOOL, not something the output needs.

        for (int col = 1; col <= 5 - row; col++) {
            // THE INNER BOUND IS `5 - row` - A CONSTANT MINUS THE ROW NUMBER.
            // This is the one line that makes the pattern narrow. Watch the
            // bound fall while the row number rises:
            //
            //     row = 0  ->  `col <= 5`  ->  col: 1 2 3 4 5  -> 5 stars
            //     row = 1  ->  `col <= 4`  ->  col: 1 2 3 4    -> 4 stars
            //     row = 2  ->  `col <= 3`  ->  col: 1 2 3      -> 3 stars
            //     row = 3  ->  `col <= 2`  ->  col: 1 2        -> 2 stars
            //     row = 4  ->  `col <= 1`  ->  col: 1          -> 1 star
            //
            // THE SUBTRACTION IS THE WHOLE MECHANISM. The total height 5 is
            // fixed. `row` climbs from 0 to 4, so `5 - row` falls from 5 to 1.
            // A bound that falls produces rows that get shorter, and a drawing
            // whose rows get shorter is exactly a decreasing triangle.
            //
            // CONTRAST WITH 02_increasing_triangle.cpp, where the bound is `row`
            // itself and therefore climbs. There, one line of arithmetic goes
            // the same way as the counter. Here, the subtraction makes it go the
            // OPPOSITE way. Getting that backwards is the standard mistake.

            if (col > 1) {
                cout << " ";
            }
            cout << "*";
            // The gap is printed BEFORE every star except the first of the row,
            // so the stars read as separate items and no line ends in a space.
            // `cout << "* ";` would give the same visible shape but would also
            // leave a trailing space at the end of each line, since the gap
            // would belong to the star rather than sitting between two stars.
        }
        cout << endl;
        // After the inner loop, inside the outer loop: one break per row.
    }

    cout << "the first row has 5 stars, the last has 1, and each row loses exactly one"
         << endl;
    cout << "total stars printed = 5 + 4 + 3 + 2 + 1 = " << (5 + 4 + 3 + 2 + 1) << endl;
    // The SAME 15 as the increasing triangle in 02_increasing_triangle.cpp.
    // Reversing a pattern reverses the ORDER of the row lengths, never the
    // lengths themselves, so the total is unchanged.

    cout << endl;
    cout << "=== Part 2: the bound `5 - row` with the rows numbered from 1 ===" << endl;

    for (int row = 1; row <= 5; row++) {
        for (int col = 1; col <= 5 - row; col++) {
            if (col > 1) {
                cout << " ";
            }
            cout << "*";
            // THE ONLY CHANGE FROM PART 1 IS THE OUTER LOOP'S NUMBERING.
            //
            // Starting at 1 shifts every bound down by one: 4, 3, 2, 1, 0. The
            // shape is still narrowing - so the DIRECTION is right - but the
            // top row is one star short and the bottom row is empty. That is the
            // classic off-by-one, and it is the reason Part 1 starts `row` at 0.
            //
            // TWO WAYS TO FIX IT, AND IT IS WORTH KNOWING BOTH:
            //   (a) number the rows from 0 and keep the bound `5 - row`
            //       - what Part 1 does, and the cleanest.
            //   (b) number the rows from 1 and write the bound `6 - row`, so it
            //       comes out as 5, 4, 3, 2, 1.
            // Both produce the right shape. Option (a) is easier to check,
            // because `5 - row` visibly equals the row's distance from the top.
        }
        cout << endl;
        // The last row prints NOTHING at all, so this line is empty. It is not
        // a formatting accident - the bound was 0, so the inner body ran zero
        // times. An empty line here is the visible symptom of the off-by-one.
    }

    cout << "the last row is EMPTY, because `5 - row` is 0 when row is 5" << endl;
    cout << "this is the off-by-one, and it is why Part 1 numbers the rows from 0"
         << endl;

    cout << endl;
    cout << "=== Part 3: why `col <= row` cannot work here ===" << endl;

    for (int row = 1; row <= 5; row++) {
        for (int col = 1; col <= row; col++) {
            // THE MISTAKE, WRITTEN OUT SO IT CAN BE COMPARED SIDE BY SIDE.
            // `col <= row` CLIMBS with the row number, so it prints rows of
            // 1, 2, 3, 4, 5 stars - an increasing triangle, the opposite shape.
            //
            // THE TEST TO APPLY BEFORE WRITING ANY BOUND:
            //     As you read the drawing DOWN, do the rows get LONGER or SHORTER?
            //     Shorter  ->  the bound must shrink  ->  write it as `total - row`
            //     Longer   ->  the bound must grow    ->  write it as `row`
            //     Same     ->  the bound is a constant ->  write the number
            //
            // That single question settles every pattern in this folder. Note
            // also that changing the outer loop's direction does NOT rescue
            // `col <= row`: the row LENGTHS are decided by the inner bound, so
            // a rising bound always produces rows that grow, whatever order the
            // rows are printed in.
            if (col > 1) {
                cout << " ";
            }
            cout << "*";
        }
        cout << endl;
    }

    cout << "`col <= row` grows with the row, so every row came out the same length"
         << endl;

    // ------------------------------------------------------------
    // HOW I DERIVED THIS CODE
    // ------------------------------------------------------------
    // Never start from a remembered `5 - row`. Start from the paper, and do
    // these six steps in order. Every pattern in this folder comes out of the
    // same procedure.
    //
    // STEP 1: COUNT THE ROWS IN THE DRAWING.
    //   Five lines tall: FIVE ROWS. OUTER BOUND = 5.
    //   Then look at WHICH row is the widest, because it has to be printed
    //   first. Here the WIDEST row is at the TOP, so the widest row is printed
    //   first and the rows must be visited from widest to narrowest.
    //
    // STEP 2: COUNT THE ITEMS IN THE FIRST ROW.
    //   The top row - the first one printed - holds FIVE stars. So on the first
    //   pass the inner loop must run five times.
    //
    // STEP 3: COUNT THE ITEMS IN THE LAST ROW.
    //   The bottom row holds ONE star. So on the last pass the inner loop must
    //   run exactly once. Never zero: the drawing has a star in its last row.
    //
    // STEP 4: ASK HOW MANY ITEMS ARE IN ROW N.
    //   Lay the row lengths out against the row numbers, in the order the code
    //   will visit them:
    //
    //       row number   0   1   2   3   4
    //       stars         5   4   3   2   1
    //       bound =    5-row
    //
    //   Two things fall out of this table.
    //   First, the pattern of the row lengths is FALLING, so the bound must
    //   fall. A bound that falls has to be written as something MINUS the row.
    //   Second, the row lengths 5, 4, 3, 2, 1 line up exactly with row numbers
    //   0, 1, 2, 3, 4 once you NUMBER FROM ZERO - which is why `5 - row` needs
    //   no adjustment at all.
    //
    //   If you prefer to number rows from 1, then row numbers 1, 2, 3, 4, 5
    //   must give 5, 4, 3, 2, 1 stars, and the only subtraction that does that
    //   is `6 - row`. Part 2 shows what happens if you forget this.
    //
    // STEP 5: DECIDE THE TWO BOUNDS.
    //   OUTER BOUND = 5 rows, numbered 0 to 4  ->  `row = 0; row < 5; row++`
    //   INNER BOUND = 5 - row                ->  `col <= 5 - row`
    //   Note the inner bound can be as high as 5 and as low as 1, and never 0
    //   with this numbering - which matches the drawing, whose last row has one
    //   star rather than none.
    //
    // STEP 6: STATE WHAT THE INNER BOUND DEPENDS ON.
    //   THIS PROGRAM'S ANSWER: it depends on `row`, and it DEPENDS ON IT
    //   BACKWARDS. The bound is the total height MINUS the row number, so as the
    //   row number grows the bound SHRINKS.
    //
    //       "the inner loop runs while the cell counter is less than or equal
    //        to the total height minus the row number, so every row prints one
    //        fewer item than the row above it."
    //
    //   The three files side by side:
    //     01_square_stars      inner bound = 5        constant, no dependence
    //     02_increasing_triangle inner bound = row     GROWS with the row
    //     03_decreasing_triangle inner bound = 5 - row SHRINKS with the row
    //
    // ------------------------------------------------------------
    // TRACE TABLE - every pass of Part 1, with the bound falling
    // +-------+---------+---------+--------------------+-----------+--------------+
    // | Pass  | OUTER   | INNER   | Test as written   | Stars     | Stars so far |
    // |       | row     | col     | on this pass      | printed   |              |
    // +-------+---------+---------+--------------------+-----------+--------------+
    // |   1   |    0    |    1    | col <= 5 - 0 = 5  |    5      |      5       |
    // |   2   |    0    |    2    | col <= 5 - 0 = 5  |          |      5       |
    // |   3   |    0    |    3    | col <= 5 - 0 = 5  |          |      5       |
    // |   4   |    0    |    4    | col <= 5 - 0 = 5  |          |      5       |
    // |   5   |    0    |    5    | col <= 5 - 0 = 5  |          |      5       |
    // |   6   |    1    |    1    | col <= 5 - 1 = 4  |    4      |      9       |
    // |   7   |    1    |    2    | col <= 5 - 1 = 4  |          |      9       |
    // |   8   |    1    |    3    | col <= 5 - 1 = 4  |          |      9       |
    // |   9   |    1    |    4    | col <= 5 - 1 = 4  |          |      9       |
    // |  10   |    2    |    1    | col <= 5 - 2 = 3  |    3      |     12       |
    // |  11   |    2    |    2    | col <= 5 - 2 = 3  |          |     12       |
    // |  12   |    2    |    3    | col <= 5 - 2 = 3  |          |     12       |
    // |  13   |    3    |    1    | col <= 5 - 3 = 2  |    2      |     14       |
    // |  14   |    3    |    2    | col <= 5 - 3 = 2  |          |     14       |
    // |  15   |    4    |    1    | col <= 5 - 4 = 1  |    1      |     15       |
    // +-------+---------+---------+--------------------+-----------+--------------+
    // | TOTAL | 5 rows  | 15 runs | 5, then 4, 3, 2, 1|    15     |     15       |
    // +-------+---------+---------+--------------------+-----------+--------------+
    //
    // READ THE BOUND COLUMN DOWN: 5, 5, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 2, 2, 1.
    // It is CONSTANT within each group of five and FALLS between groups. That
    // is the signature of a bound built from `row`, and the groups get shorter
    // each time - which is the pattern, visible as arithmetic.
    //
    // THE TOTAL IS 15 EXECUTIONS OF THE INNER BODY
    //   5 + 4 + 3 + 2 + 1 = 15
    // It is an ADDITION, not a multiplication. A square's rows are all the same
    // length, so its total is rows x cells = 5 x 5 = 25. Here every row is a
    // DIFFERENT length, so there is no single cells-per-row figure to multiply
    // by and the row lengths must be added. Any question asking "how many stars"
    // about a pattern like this wants the sum.
    //
    // `cout << "*";` VERSUS `cout << "* ";`
    //   `"* "` prints a star and then a gap, so items appear separated. It also
    //   prints a gap after the LAST star of each row, so every line ends in a
    //   space. Invisible on screen, but a real character: it makes the program's
    //   output differ from an expected-output block whose trailing whitespace an
    //   editor has trimmed.
    //   This file prints the gap FIRST, guarded by `if (col > 1)`, which gives
    //   the same visible shape with clean line endings.
    //   THE RULE: a gap belongs BETWEEN two items, never after the last one.
    //
    // WHY `endl` GOES AFTER THE INNER LOOP, NOT INSIDE IT
    //   A row is finished only when the inner loop has finished, so the line
    //   break belongs immediately after the inner loop:
    //
    //       for (row ...) {
    //           for (col ...) {
    //               ... print one star ...
    //           }
    //           cout << endl;   // <-- this row is complete
    //       }
    //
    //   Inside the inner loop, `endl` would break after every STAR, so the
    //   triangle would come out as 15 lines of one star each. After the inner
    //   loop, it breaks once per completed ROW, which is what produces 5 lines
    //   of 5, 4, 3, 2, 1 stars. The placement of `endl` is a decision about the
    //   SHAPE: inside the inner loop gives lines per item, after it gives lines
    //   per row.
    //
    // COMMON TRAP
    //   Using `col <= row` because that worked for the increasing triangle. The
    //   two shapes are opposite, so their bounds are opposite too: one grows,
    //   the other shrinks. Copying the bound across without asking whether the
    //   rows in the NEW drawing get longer or shorter is what produces a square
    //   where a triangle should be, as Part 3 shows.
    //
    //   The second trap is numbering the rows from 1 and keeping `5 - row`, which
    //   prints 4, 3, 2, 1, 0 - an empty last line. The shape still narrows, so
    //   it looks nearly right, which is exactly what makes it hard to spot. Part
    //   2 prints it deliberately: when a narrowing pattern has a blank final
    //   row, the bound is off by one.
    //
    //   The third trap is assuming `5 - row` needs `5` to be a named constant
    //   or something typed twice. In this file 5 appears once in the outer
    //   bound and once in the inner expression, and changing the pattern's
    //   height means changing both - which is exactly why the rows are numbered
    //   from 0 in the first place, since it makes the two agree.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: What is the inner loop's bound in Part 1, and why does it shrink?  -> it is `5 - row`; the total 5 is fixed while `row` climbs from 0 to 4, so the bound falls from 5 to 1
// Q2: Why does the outer loop start `row` at 0 rather than 1?  -> so `5 - row` comes out as 5, 4, 3, 2, 1 with no off-by-one; starting at 1 would give 4, 3, 2, 1, 0 and an empty last row
// Q3: How many stars are printed in total, and is it a multiplication or an addition?  -> 15, by addition - 5 + 4 + 3 + 2 + 1 - because every row has a different length
// Q4: Why can `col <= row` not produce this shape?  -> because that bound grows with the row number, so the rows get longer going down instead of shorter
// Q5: What would happen if `endl` were moved inside the inner loop?  -> the line would break after every star, giving 15 single-star lines instead of five rows
