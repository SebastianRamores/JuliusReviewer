// ============================================================
// PROGRAM: Pattern 6 - An Inverted Triangle of Numbers
// TOPIC: an inner loop that STARTS at the row number, not at 1
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - How to print `1 2 3 4 5`, then `2 3 4 5`, then `3 4 5`, then `4 5`, then `5`.
// - That the inner loop must START at the row number: `int col = row;`.
// - The TWO changes this pattern makes to an increasing one: the START value
//   moves to `row`, and the END value is the constant 5.
// - How to combine a moving start with a fixed end, which is the opposite
//   arrangement from every earlier file.
//
// EXPECTED OUTPUT:
// === Part 1: the inverted triangle ===
// 1 2 3 4 5
// 2 3 4 5
// 3 4 5
// 4 5
// 5
// row 1 printed 5 values, row 5 printed 1 value
// total values printed = 5 + 4 + 3 + 2 + 1 = 15
//
// === Part 2: the SAME inner bound but starting at 1 again ===
// 1
// 1 2
// 1 2 3
// 1 2 3 4
// 1 2 3 4 5
// the end value still moves, but the start never does
//
// === Part 3: start at row AND end at row, for comparison ===
// 1
// 2
// 3
// 4
// 5
// a moving start and a moving end that meet immediately: one value per row
//
// IMPORTANT SYNTAX:
// for (int row = 1; row <= 5; row++)     -> the outer loop counts the ROWS
//     for (int col = row; col <= 5; col++)  -> the inner loop STARTS at `row`
//         if (col > row) { cout << " "; }     -> gap BEFORE all but the first
//         cout << col;                        -> prints col, which starts at row
//     cout << endl;                            -> one break per finished row
//
// THE TWO CHANGES, IN ONE PLACE
//   INCREASING TRIANGLE          this pattern
//   for (row = 1; row <= 5;)     for (row = 1; row <= 5;)      <- same
//     for (col = 1;              for (col = row;              <- CHANGE 1: the start
//         col <= row;)               col <= 5)                   CHANGE 2: the end
//   "row N holds N values"       "row N holds N values, starting at N"
//
// STEP-BY-STEP EXPLANATION:
// 1. Five rows, so the outer loop runs 1 to 5 - unchanged from every other
//    pattern in this folder.
// 2. The first row holds five values and the last holds one, so the number of
//    values per row FALLS. The end value must therefore be the constant 5.
// 3. The first row STARTS at 1, the second at 2, the third at 3. The start
//    value must therefore RISE with the row - which means it is `row` itself.
// 4. So the inner loop begins at `row` and ends at 5, and every value it
//    produces is in the range from the row number up to 5.
// 5. Part 3 shows what happens when both ends move: they meet straight away and
//    each row prints a single value.
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

    cout << "=== Part 1: the inverted triangle ===" << endl;

    for (int row = 1; row <= 5; row++) {
        // THE OUTER LOOP COUNTS THE ROWS: 1, 2, 3, 4, 5. This is exactly the
        // same outer loop as every other pattern in this folder - the outer
        // loop is almost never the interesting part of a pattern.

        for (int col = row; col <= 5; col++) {
            // THE KEY LINE OF THIS ENTIRE FILE: `for (int col = row; ...)`.
            //
            // THE INNER LOOP STARTS AT THE ROW NUMBER, NOT AT 1. In every other
            // pattern here the initial value is the literal 1, so each row's
            // values begin from the same place. Here the starting point MOVES
            // down the drawing as the rows advance:
            //
            //     row = 1  ->  col: 1 2 3 4 5  -> 5 values, from 1 up to 5
            //     row = 2  ->  col: 2 3 4 5    -> 4 values, from 2 up to 5
            //     row = 3  ->  col: 3 4 5      -> 3 values, from 3 up to 5
            //     row = 4  ->  col: 4 5        -> 2 values, from 4 up to 5
            //     row = 5  ->  col: 5          -> 1 value,  from 5 up to 5
            //
            // And the END is the FIXED CONSTANT 5. Read those two together:
            // the start rises, the end does not, so the gap between them - which
            // is the number of values printed - NARROWS. That is precisely the
            // shape in the drawing.
            //
            // THE PATTERN TO RECOGNISE: a loop bounded by `row` to `5` prints
            // the numbers from `row` up to 5, so it prints `5 - row + 1` of
            // them. The number of values is decided by WHERE THE TWO ENDS MEET,
            // not by either end alone.
            //
            // NOTE THAT `col` IS BOTH THE STARTING VALUE AND THE PRINTED VALUE.
            // That works here because the drawing wants consecutive integers
            // starting at the row number - the same situation as in
            // 04_number_triangle.cpp.

            if (col > row) {
                // THE GAP GOES BEFORE EVERY VALUE EXCEPT THE FIRST OF THE ROW.
                //
                // THE TEST IS `col > row`, NOT `col > 1`. That is the one
                // adjustment this pattern needs beyond the inner bound itself,
                // and it is easy to get wrong by copying the condition from
                // another file in this folder.
                //
                // WHY: the first value of THIS row is `row`, not 1. A gap is
                // needed BETWEEN two values, so the test has to ask "is this
                // value past the first one?" - and the first one here is `row`.
                // With `col > 1`, row 1 would be correct (its first value IS 1)
                // but every row from 2 down would begin with a stray space:
                //
                //       col > 1  ->  rows 2..5 each start one space in
                //       col > row ->  every row starts flush against the margin
                //
                // The general rule: compare against this row's FIRST POSSIBLE
                // VALUE, never against the number 1, unless the row really does
                // start at 1.
                cout << " ";
            }

            cout << col;
            // THE VALUE IS `col`, WHICH ALREADY STARTS AT `row`. No accumulator
            // and no arithmetic are needed here: the inner loop's initial value
            // does the work an accumulator does in 04_number_triangle.cpp.
        }
        cout << endl;
        // AFTER the inner loop: one break per finished row. Inside the inner
        // loop it would break after every value, giving 15 lines of one number.
    }

    cout << "row 1 printed 5 values, row 5 printed 1 value" << endl;
    cout << "total values printed = 5 + 4 + 3 + 2 + 1 = " << (5 + 4 + 3 + 2 + 1)
         << endl;
    // An ADDITION, not a multiplication: every row is a different length. And
    // the number of values on row N is `5 - N + 1`, which runs 5, 4, 3, 2, 1.

    cout << endl;
    cout << "=== Part 2: the SAME inner bound but starting at 1 again ===" << endl;

    for (int row = 1; row <= 5; row++) {
        for (int col = 1; col <= row; col++) {
            // ONE CHANGE FROM PART 1: THE START IS BACK TO 1.
            //
            // The end still moves with the row, so the rows still GROW and the
            // shape is still a triangle - just the increasing one from
            // 02_increasing_triangle.cpp. The values now run 1 to row on every
            // row, restarting at 1 each time.
            //
            // THIS IS THE MOST USEFUL COMPARISON IN THE FILE, because the end
            // value behaved correctly in both programs. What changed the output
            // completely was one number in the initialiser.
            if (col > 1) {
                cout << " ";
            }
            cout << col;
        }
        cout << endl;
    }

    cout << "the end value still moves, but the start never does" << endl;

    cout << endl;
    cout << "=== Part 3: start at row AND end at row, for comparison ===" << endl;

    for (int row = 1; row <= 5; row++) {
        for (int col = row; col <= row; col++) {
            // BOTH ENDS ARE `row`, SO THEY MEET IMMEDIATELY. The inner loop
            // runs exactly once and prints one value per row.
            //
            // This makes the arithmetic of the whole file concrete. The count of
            // values is the distance from the start to the end, plus one:
            //
            //     Part 1:  from `row` to 5   ->  5 - row + 1 values
            //     Part 3:  from `row` to row ->  row - row + 1 = 1 value
            //
            // Holding one end still and moving the other is what produces every
            // triangle in this folder. Moving both ends towards each other is
            // what produces a diagonal of single values.
            cout << row;
            // No gap needed at all: there is only ever one value on the line.
        }
        cout << endl;
    }

    cout << "a moving start and a moving end that meet immediately: one value per row"
         << endl;

    // ------------------------------------------------------------
    // HOW I DERIVED THIS CODE
    // ------------------------------------------------------------
    // Build it from the drawing. Six steps, the same six used for every pattern.
    //
    // STEP 1: COUNT THE ROWS IN THE DRAWING.
    //   Five lines:
    //       1 2 3 4 5
    //       2 3 4 5
    //       3 4 5
    //       4 5
    //       5
    //   FIVE ROWS. OUTER BOUND = 5  ->  `row <= 5`. This is the same outer loop
    //   as every other pattern, and it is worth noticing how rarely the outer
    //   loop is where the difficulty lives.
    //
    // STEP 2: COUNT THE ITEMS IN THE FIRST ROW.
    //   The top row holds FIVE values. So on the first pass the inner loop must
    //   run five times.
    //
    // STEP 3: COUNT THE ITEMS IN THE LAST ROW.
    //   The bottom row holds ONE value. So on the last pass the inner loop must
    //   run once.
    //
    // STEP 4: ASK HOW MANY ITEMS ARE IN ROW N - AND WHICH ONES.
    //   The count first:
    //       row 1 -> 5 items       row 4 -> 2 items
    //       row 2 -> 4 items       row 5 -> 1 item
    //       row 3 -> 3 items
    //   The count FALLS, so the inner bound must produce fewer values as `row`
    //   grows. Two ways to do that are available, and which one to pick is
    //   decided by the values, not the counts.
    //
    //   Now the values, which is the part that actually decides the code:
    //       row 1 -> 1 2 3 4 5     starts at 1, ends at 5
    //       row 2 -> 2 3 4 5       starts at 2, ends at 5
    //       row 3 -> 3 4 5         starts at 3, ends at 5
    //       row 4 -> 4 5           starts at 4, ends at 5
    //       row 5 -> 5             starts at 5, ends at 5
    //
    //   READ THE START COLUMN: 1, 2, 3, 4, 5. It rises in step with the row
    //   number, so the start IS `row`.
    //   READ THE END COLUMN: 5, 5, 5, 5, 5. It never changes, so the end is the
    //   CONSTANT 5.
    //
    //   Those two readings are the entire pattern: `for (int col = row; col <= 5;
    //   col++)`. The rising start and the fixed end are what make the rows
    //   narrow, because the gap between the two ends closes by one each time.
    //
    // STEP 5: DECIDE THE TWO BOUNDS.
    //   OUTER BOUND = 5 rows                     ->  `row <= 5`
    //   INNER START = the row number              ->  `int col = row`
    //   INNER END   = the constant 5              ->  `col <= 5`
    //
    // STEP 6: STATE WHAT THE INNER BOUND DEPENDS ON.
    //   THIS PROGRAM'S ANSWER: only the START depends on `row`; the end does not.
    //   That is what makes this pattern different from every other one in the
    //   folder, where the END is the part that moves.
    //
    //       "the inner loop starts at the current row number and runs while the
    //        cell counter is less than or equal to 5, so row N prints the
    //        numbers from N up to 5 - that is, 5 - N + 1 of them."
    //
    //   Compare across the folder:
    //     01_square_stars          bound = 5        to 5        fixed both ends
    //     02_increasing_triangle   bound = 1 to row              fixed start, moving end
    //     03_decreasing_triangle   bound = 1 to 5 - row          fixed start, moving end
    //     04_number_triangle       bound = 1 to row              fixed start, moving end
    //     05_repeated_number       bound = 1 to row              fixed start, moving end
    //     06_inverted_number       bound = row to 5   <- MOVING START, fixed end
    //
    //   Six files, and the last one is the odd one out. That is worth noticing,
    //   because "the inner loop always starts at 1" is the assumption that makes
    //   this pattern hard to see coming.
    //
    // ------------------------------------------------------------
    // TRACE TABLE - every execution of the inner body, all 15
    // +-------+---------+---------+--------------+---------------+-------------------+
    // | Pass  | OUTER   | INNER   | Range of     | Printed       | Values in this   |
    // |       | row     | col     | values this  | value         | row so far       |
    // |       |         |         | row          |               |                   |
    // +-------+---------+---------+--------------+---------------+-------------------+
    // |   1   |    1    |    1    | 1 to 5       |      1        |   1              |
    // |   2   |    1    |    2    | 1 to 5       |      2        |   1 2            |
    // |   3   |    1    |    3    | 1 to 5       |      3        |   1 2 3          |
    // |   4   |    1    |    4    | 1 to 5       |      4        |   1 2 3 4        |
    // |   5   |    1    |    5    | 1 to 5       |      5        |   1 2 3 4 5      |
    // |   6   |    2    |    2    | 2 to 5       |      2        |   2              |
    // |   7   |    2    |    3    | 2 to 5       |      3        |   2 3            |
    // |   8   |    2    |    4    | 2 to 5       |      4        |   2 3 4          |
    // |   9   |    2    |    5    | 2 to 5       |      5        |   2 3 4 5        |
    // |  10   |    3    |    3    | 3 to 5       |      3        |   3              |
    // |  11   |    3    |    4    | 3 to 5       |      4        |   3 4            |
    // |  12   |    3    |    5    | 3 to 5       |      5        |   3 4 5          |
    // |  13   |    4    |    4    | 4 to 5       |      4        |   4              |
    // |  14   |    4    |    5    | 4 to 5       |      5        |   4 5            |
    // |  15   |    5    |    5    | 5 to 5       |      5        |   5              |
    // +-------+---------+---------+--------------+---------------+-------------------+
    //
    // READ THE INNER COLUMN DOWN: 1 2 3 4 5, 2 3 4 5, 3 4 5, 4 5, 5.
    //
    // Two things are happening at once and both are visible in that one column:
    //
    //   - it RESETS, like every inner counter ever: 5 then 2 then 3 then 4.
    //     The reset happens because `int col = row` is part of the inner loop's
    //     header and headers re-run from the top on every outer pass.
    //   - it RESETS TO `row`, NOT TO 1. That is the whole difference between
    //     this pattern and 04_number_triangle.cpp. Same reset, different
    //     starting point, entirely different drawing.
    //
    // Note row 5: the range is 5 to 5, so the loop runs once. A row whose start
    // and end are equal is a row with a single value, and Part 3 shows what
    // happens when every row is like that.
    //
    // THE OUTER AND INNER COLUMNS ARE BOTH REQUIRED. One row per execution of
    // the inner body, so 15 rows - never 5.
    //
    // THE TOTAL NUMBER OF TIMES THE INNER BODY EXECUTES
    //   5 + 4 + 3 + 2 + 1 = 15 executions, and 15 values printed.
    //   An ADDITION, not a multiplication, because each row is a different
    //   length. The general form is `total height minus row plus one`:
    //       row N prints 5 - N + 1 values
    //   which is the same figure the star triangle of
    //   03_decreasing_triangle.cpp arrives at, reached from the other direction.
    //
    // THE INNER BOUND HAS TWO ENDS, AND BOTH MATTER
    //   A `for` loop is `start`, then `test`, then `update`. The values printed
    //   are decided by the start and the test TOGETHER - the loop prints every
    //   value from the start up to and including whatever the test allows.
    //
    //       1 to 5    ->  1 2 3 4 5     five values
    //       2 to 5    ->  2 3 4 5       four values
    //       row to 5  ->  3 4 5         three values, and the start MOVES
    //       row to row ->  one value, and both ends MOVE
    //
    //   When the start is a constant, only the end has to be reasoned about,
    //   which is why most patterns feel easy. This file is the one where both
    //   ends have to be read off the drawing, and the start is the interesting
    //   one.
    //
    // `cout << col;` VERSUS `cout << col << " ";`
    //   Appending a space to every value would separate them correctly BUT would
    //   also leave a space at the end of every line, because the gap would
    //   belong to the value rather than sitting between two values. Invisible on
    //   screen, but a real character: it makes the program's output differ from
    //   an expected-output block whose trailing whitespace an editor has trimmed.
    //
    //   Part 1 instead prints the gap BEFORE each value, guarded by
    //   `if (col > row)`. That builds each row as
    //   gap-value-gap-value-gap-value, and because the gap is printed only when
    //   there is a value AFTER it, no line can end in a space.
    //
    //   Note the test is `col > row` and NOT `col > 1`. A gap belongs BETWEEN
    //   two values, and the first value of this row is `row` - not 1. Writing
    //   `col > 1` here would indent rows 2 to 5 by one space, which is a small
    //   and easily missed error that still looks nearly right on screen.
    //
    // WHY `endl` GOES AFTER THE INNER LOOP, NOT INSIDE IT
    //   A row is complete only when the inner loop has finished, so the break
    //   belongs immediately after the inner loop:
    //
    //       for (row ...) {
    //           for (col ...) {
    //               ... print one value ...
    //           }
    //           cout << endl;   // <-- this row is complete
    //       }
    //
    //   Inside the inner loop it would break after every value, giving 15 lines
    //   of a single number each. After the inner loop it breaks once per
    //   completed ROW, which is what produces the 5 lines the drawing asks for.
    //
    // COMMON TRAP
    //   Leaving the start at 1 and only changing the end. Part 2 does exactly
    //   that, and it produces the increasing triangle from
    //   02_increasing_triangle.cpp - a perfectly good pattern, just not the one
    //   that was asked for. The end value behaved correctly in both programs;
    //   one number in the initialiser changed everything.
    //
    //   The second trap is using `if (col > 1)` for the gap. It looks like the
    //   condition from every other file in the folder, and it silently indents
    //   rows 2 to 5 by one space. The general rule is to compare against the
    //   first value this row can possibly hold, and here that value is `row`.
    //
    //   The third trap is assuming the inner loop always starts at 1. Five of the
    //   six pattern files here do, which makes this one genuinely surprising.
    //   The habit worth building is to read the inner loop's header as TWO
    //   separate facts - what does it start at, and where does it stop - and to
    //   take both from the drawing rather than from the previous file.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: What does the inner loop of this pattern start at, and what does it end at?  -> it starts at `row`, the current row number, and ends at the constant 5
// Q2: What are the two changes needed to turn an increasing triangle into this one?  -> the inner loop's start becomes `row` instead of 1, and its end becomes the constant 5 instead of `row`
// Q3: Why does each row print one value fewer than the row above it?  -> the start rises by one each time while the end stays at 5, so the distance between them closes by one
// Q4: How many times does the inner body run on row N, and how many values does that row print?  -> row N prints 5 - N + 1 values, which totals 5 + 4 + 3 + 2 + 1 = 15 over all rows
// Q5: Why must the gap test be `col > row` rather than `col > 1`?  -> because the first value of each row is the row number, so comparing against 1 would wrongly put a leading space on rows 2 to 5
