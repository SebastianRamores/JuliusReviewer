// ============================================================
// PROGRAM: Pattern 5 - A Triangle of Repeated Numbers
// TOPIC: the printed VALUE comes from the outer loop, the inner loop only counts
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - How to print `1`, then `2 2`, then `3 3 3`, then `4 4 4 4`.
// - That the outer loop's variable supplies the VALUE that is printed, while the
//   inner loop's variable only supplies the COUNT of times it is printed.
// - Why those two jobs must be kept apart, and what breaks when the inner loop
//   prints its own counter instead.
// - That the inner bound is `row`, exactly as for a star triangle - only the
//   printed text is different.
//
// EXPECTED OUTPUT:
// === Part 1: row n prints the number n, n times ===
// 1
// 2 2
// 3 3 3
// 4 4 4 4
// 5 5 5 5 5
// total values printed = 1 + 2 + 3 + 4 + 5 = 15
//
// === Part 2: printing the INNER counter instead ===
// 1
// 1 2
// 1 2 3
// 1 2 3 4
// 1 2 3 4 5
// the shape is right and the counts are right, but the VALUES are wrong
// `col` runs 1, 2, 3 within EVERY row - it forgets which row it is in
//
// === Part 3: both values printed together, so the difference shows ===
// 1:1
// 2:1 2:2
// 3:1 3:2 3:3
// 4:1 4:2 4:3 4:4
// 5:1 5:2 5:3 5:4 5:5
// the left number is `row`, printed everywhere in the row
// the right number is `col`, and it changes on every single value
//
// IMPORTANT SYNTAX:
// for (int row = 1; row <= 5; row++)     -> supplies the VALUE: 1, then 2, ...
//     for (int col = 1; col <= row; col++)  -> supplies the COUNT: row times
//         cout << row;                     -> prints the OUTER value
//     cout << endl;                          -> one break per finished row
//
// THE TWO JOBS, IN ONE TABLE
// +----------------------+-------------------+---------------------------+
// | Variable             | Job in this file  | What changes              |
// +----------------------+-------------------+---------------------------+
// | row (OUTER, from the | the VALUE printed | every value on a row      |
// | outer loop)          |                   |                           |
// | col (INNER, from the | the COUNT of      | every single value, and  |
// | inner loop)          | repetitions       | decides where a row ends  |
// +----------------------+-------------------+---------------------------+
// Printing `row` gives this pattern. Printing `col` gives Part 2's pattern.
// Both are legitimate; the drawing decides which one is wanted.
//
// STEP-BY-STEP EXPLANATION:
// 1. Count five rows, so the outer loop runs 1 to 5.
// 2. The first row holds one value, the last holds five, so the inner bound is
//    `row` - the same bound as every increasing triangle in this folder.
// 3. The first row's value is 1, the second's is 2: the value is the ROW NUMBER.
// 4. So the printed text must come from the OUTER loop's variable.
// 5. Part 2 prints the inner counter instead, and the values come out as 1 /
//    2 3 / 3 4 5 - the shape is unchanged, so only a trace reveals the error.
// 6. Part 3 prints both so the two can be compared directly on every row.
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

    cout << "=== Part 1: row n prints the number n, n times ===" << endl;

    for (int row = 1; row <= 5; row++) {
        // THE OUTER LOOP SUPPLIES THE VALUE.
        //
        // `row` runs 1, 2, 3, 4, 5, and the drawing says row 1 prints the
        // number 1, row 2 prints the number 2, and so on. So the number that
        // appears in the output IS the row number, and every value on a row is
        // the same one.
        //
        // This is the crucial point of the whole file: `row` is not used to
        // decide HOW MANY values to print - the inner loop does that. `row` is
        // used to decide WHAT gets printed.

        for (int col = 1; col <= row; col++) {
            // THE INNER LOOP SUPPLIES ONLY THE COUNT.
            //
            // The bound is `row`, so row 1 prints one value and row 5 prints
            // five. That is exactly the same inner bound as the star triangle in
            // 02_increasing_triangle.cpp, and for the same reason: the two
            // patterns have the same SHAPE. `col` is never printed in this
            // part. It counts repetitions and then forgets it.

            if (col > 1) {
                cout << " ";
            }
            cout << row;
            // `cout << row;` NOT `cout << col;`. This is the whole pattern in
            // one token. Because `row` does not change while the inner loop
            // runs, every pass of the inner loop prints the SAME number - and
            // together with the bound `col <= row` that gives n copies of n.
            //
            // The gap goes before every value except the first of the row, so
            // the values read as separate items and no line ends in a space.

            // `col` is never printed. That is not a wasted variable: it is what
            // decides how many times the `cout` above runs. Printing `row`
            // `row` times needs a counter to count with, and that is `col`.
        }
        cout << endl;
        // AFTER the inner loop, INSIDE the outer loop: one break per finished
        // row. Inside the inner loop it would break after every value, giving
        // 15 lines of one number each.
    }

    cout << "total values printed = 1 + 2 + 3 + 4 + 5 = " << (1 + 2 + 3 + 4 + 5)
         << endl;
    // An ADDITION rather than a multiplication, because the rows are all
    // different lengths. There are 15 executions of the inner body and 15
    // values printed, since each execution prints exactly one.

    cout << endl;
    cout << "=== Part 2: printing the INNER counter instead ===" << endl;

    for (int row = 1; row <= 5; row++) {
        for (int col = 1; col <= row; col++) {
            if (col > 1) {
                cout << " ";
            }
            cout << col;
            // THE MISTAKE: PRINTING `col` INSTEAD OF `row`.
            //
            // The shape is still exactly right, because the bound `col <= row`
            // is untouched. Row 1 still prints one value, row 5 still prints
            // five, and the drawing's SHAPE is reproduced perfectly.
            //
            // But the VALUES are wrong, and the reason is worth understanding
            // rather than just noting. `col` restarts at 1 in EVERY row, because
            // `int col = 1;` is part of the inner loop's header. So row 2 prints
            // 1 and 2 - the same two values as row 1's single pass and as row 3's
            // first two. The inner counter knows WHICH ROW IT IS IN only through
            // the outer loop's counter, and it has no idea what that number is.
            //
            // THE RULE THIS DEMONSTRATES: the inner counter answers "how many
            // times?", never "what?". If the drawing needs the same value
            // repeated, the value has to come from the OUTER loop.
        }
        cout << endl;
    }

    cout << "the shape is right and the counts are right, but the VALUES are wrong"
         << endl;
    cout << "`col` runs 1, 2, 3 within EVERY row - it forgets which row it is in"
         << endl;

    cout << endl;
    cout << "=== Part 3: both values printed together, so the difference shows ==="
         << endl;

    for (int row = 1; row <= 5; row++) {
        for (int col = 1; col <= row; col++) {
            if (col > 1) {
                cout << " ";
            }
            cout << row << ":" << col;
            // BOTH COUNTERS PRINTED IN EVERY CELL, separated by a colon.
            //
            // This is the debugging technique to reach for when a pattern's shape
            // is right and its contents are not. Print the value AND the
            // position on every single cell and the fault is obvious at a
            // glance: the left number is constant across each line, and the
            // right number runs 1, 2, 3 ...
            //
            // Reading the output above, row 3 prints `3:1 3:2 3:3` - the left
            // number never changes on a line, the right number always does.
            // Part 1 needs the LEFT one. Part 2 printed the RIGHT one, which is
            // why every line restarted at 1.
        }
        cout << endl;
    }

    cout << "the left number is `row`, printed everywhere in the row" << endl;
    cout << "the right number is `col`, and it changes on every single value" << endl;

    // ------------------------------------------------------------
    // HOW I DERIVED THIS CODE
    // ------------------------------------------------------------
    // Build it from the drawing. Six steps, the same six used for every pattern.
    //
    // STEP 1: COUNT THE ROWS IN THE DRAWING.
    //   Five lines: 1 / 2 2 / 3 3 3 / 4 4 4 4 / 5 5 5 5 5.
    //   FIVE ROWS. OUTER BOUND = 5  ->  `row <= 5`.
    //
    // STEP 2: COUNT THE ITEMS IN THE FIRST ROW.
    //   The top row holds ONE value. So the inner loop must run once on row 1.
    //
    // STEP 3: COUNT THE ITEMS IN THE LAST ROW.
    //   The bottom row holds FIVE values. So the inner loop must run five times
    //   by row 5.
    //
    // STEP 4: ASK HOW MANY ITEMS ARE IN ROW N.
    //       row 1 -> 1 item        row 4 -> 4 items
    //       row 2 -> 2 items       row 5 -> 5 items
    //       row 3 -> 3 items
    //   The rule: "row N contains N items", so the inner bound is `col <= row`.
    //   THE SAME RULE AS 02_increasing_triangle.cpp - the shapes are identical.
    //
    //   Now the question specific to this pattern, and it is not about counts:
    //
    //       WHICH value goes in row N?
    //           row 1 -> the number 1, once
    //           row 2 -> the number 2, twice
    //           row 3 -> the number 3, three times
    //           row 4 -> the number 4, four times
    //
    //   Read the VALUES down the rows: 1, then 2, then 3, then 4, then 5. They
    //   line up exactly with the ROW NUMBERS. So the value to print is `row`.
    //
    //   That single line of reasoning answers the question the drawing is really
    //   asking, and it is the step people skip. "How many times?" comes from the
    //   inner bound; "what?" comes from matching the values against the row
    //   numbers. Two separate questions, two separate loops' variables.
    //
    // STEP 5: DECIDE THE TWO BOUNDS.
    //   OUTER BOUND = 5 rows                    ->  `row <= 5`
    //   INNER BOUND = items in the current row  ->  `col <= row`
    //   And the printed text:  `row`.
    //
    // STEP 6: STATE WHAT THE INNER BOUND DEPENDS ON.
    //   THIS PROGRAM'S ANSWER: it depends on `row`, and it grows with it.
    //
    //       "the inner loop runs while the cell counter is less than or equal
    //        to the row number, so row N produces N values; and each of those
    //        N values is the row number itself, printed from the outer loop's
    //        variable rather than the inner loop's."
    //
    //   Compare across the folder:
    //     01_square_stars          inner bound = 5        constant
    //     02_increasing_triangle   inner bound = row      grows, prints col
    //     03_decreasing_triangle   inner bound = 5 - row  shrinks
    //     04_number_triangle       inner bound = row      grows, prints an accumulator
    //     05_repeated_number       inner bound = row      grows, prints row
    //
    //   Note that 02, 04 and 05 all have the SAME inner bound and three quite
    //   different patterns. The bound fixes the shape; only the printed
    //   expression fixes the contents.
    //
    // ------------------------------------------------------------
    // TRACE TABLE - every execution of the inner body, all 15
    // +-------+---------+---------+---------+------------------------+---------------+
    // | Pass  | OUTER   | INNER   | Printed | What `col` would have   | Values in    |
    // |       | row     | col     | (row)   | printed instead         | this row so  |
    // |       |         |         |         | (Part 2)                | far          |
    // +-------+---------+---------+---------+------------------------+---------------+
    // |   1   |    1    |    1    |    1    |           1             |      1        |
    // |   2   |    2    |    1    |    2    |           1             |      1        |
    // |   3   |    2    |    2    |    2    |           2             |      2        |
    // |   4   |    3    |    1    |    3    |           1             |      1        |
    // |   5   |    3    |    2    |    3    |           2             |      2        |
    // |   6   |    3    |    3    |    3    |           3             |      3        |
    // |   7   |    4    |    1    |    4    |           1             |      1        |
    // |   8   |    4    |    2    |    4    |           2             |      2        |
    // |   9   |    4    |    3    |    4    |           3             |      3        |
    // |  10   |    4    |    4    |    4    |           4             |      4        |
    // |  11   |    5    |    1    |    5    |           1             |      1        |
    // |  12   |    5    |    2    |    5    |           2             |      2        |
    // |  13   |    5    |    3    |    5    |           3             |      3        |
    // |  14   |    5    |    4    |    5    |           4             |      4        |
    // |  15   |    5    |    5    |    5    |           5             |      5        |
    // +-------+---------+---------+---------+------------------------+---------------+
    //
    // READ THE TWO VALUE COLUMNS SIDE BY SIDE. The PRINTED column is
    // 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5 - which is the drawing. The
    // "what col would have printed" column is 1, 1, 2, 1, 2, 3, 1, 2, 3, 4, 1,
    // 2, 3, 4, 5 - which is Part 2's wrong output. Both columns come from the
    // SAME loops; only the expression inside `cout` differs.
    //
    // THE OUTER AND INNER COLUMNS ARE BOTH REQUIRED. One row per execution of
    // the inner body, so 15 rows - never 5, one per outer pass.
    //
    // THE INNER COLUMN IS WHAT DECIDES WHERE A ROW ENDS
    //   Read it down and watch it restart: 1 / 1 2 / 1 2 3 / 1 2 3 4 / 1 2 3 4 5.
    //   The restart at 1 is what puts a line break after row passes, because
    //   `col <= row` becomes false the moment `col` exceeds the row number. The
    //   inner loop never decides to end a row - it simply runs out of numbers,
    //   and that is where the shape comes from.
    //
    // THE TOTAL NUMBER OF TIMES THE INNER BODY EXECUTES
    //   1 + 2 + 3 + 4 + 5 = 15 executions, and 15 values printed.
    //   An ADDITION, not a multiplication, because each row is a different
    //   length. A square would be 5 x 5 = 25; a triangle of any sort is the sum
    //   of its row lengths.
    //
    // WHY THE VALUE COMES FROM THE OUTER LOOP - THE FULL ARGUMENT
    //   The two loops have two separate jobs, and the jobs do not overlap:
    //
    //     the OUTER loop chooses WHAT value this row is about
    //     the INNER loop chooses HOW MANY times to print it
    //
    //   The inner loop cannot supply the value, because `col` restarts at 1 in
    //   every row and so has no idea which row it is in. Part 2's output proves
    //   it: rows of 1, then 1 2, then 1 2 3 - the counter is faithfully
    //   reporting its own position, which is simply the wrong question.
    //
    //   The outer loop cannot supply the count, because `row` does not change
    //   while the inner loop runs. Printing `row` in a loop bounded by a
    //   constant would give the same value on every row of the same length.
    //   The count has to come from something that is still moving, and only the
    //   inner loop's counter is.
    //
    // `cout << row;` VERSUS `cout << row << " ";`
    //   Appending `" "` to every value separates them correctly BUT also puts a
    //   space at the end of the last value on every line, because the gap
    //   belongs to the value rather than sitting between two values. Invisible
    //   on screen, but a real character, and it makes the program's output
    //   differ from an expected-output block whose trailing whitespace an editor
    //   has trimmed. Printing the gap first, guarded by `if (col > 1)`, gives
    //   the same visible shape with clean line endings.
    //   THE RULE: a gap belongs BETWEEN two items, never after the last one.
    //
    // WHY `endl` GOES AFTER THE INNER LOOP, NOT INSIDE IT
    //   A row is complete only when the inner loop has finished, so the line
    //   break belongs immediately after the inner loop:
    //
    //       for (row ...) {
    //           for (col ...) {
    //               ... print one value ...
    //           }
    //           cout << endl;   // <-- this row is complete
    //       }
    //
    //   Inside the inner loop it would break after every value, giving 15 lines
    //   of a single number each - which is not a triangle in any sense. After
    //   the inner loop it breaks once per completed ROW, which is exactly the 5
    //   lines of 1, 2, 3, 4, 5 repetitions that were asked for.
    //
    // COMMON TRAP
    //   Printing `col` and getting a shape that looks correct. This is the most
    //   dangerous kind of pattern bug, because the SHAPE - the number of values
    //   per row, the number of rows, the alignment - is all perfectly right, and
    //   so nothing in the outline of the output looks wrong. Only the contents
    //   are wrong, and an outline is exactly what most people check.
    //
    //   The second trap is assuming the inner bound must be different because
    //   the output is different from a star triangle. The bound is IDENTICAL -
    //   `col <= row`. Only the expression inside `cout` changed. Recount the
    //   rows and the items per row before assuming a bound needs changing.
    //
    //   The third trap is reading `cout << row;` as printing the row's total. It
    //   prints the row's NUMBER. Row 4 prints the number 4 four times, and those
    //   two facts - which number, and how many times - are decided by two
    //   different variables. Say both out loud before writing the line.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: Which loop supplies the value that is printed, and which supplies the number of times it is printed?  -> the outer loop supplies the value through `row`, and the inner loop supplies the count through `col <= row`
// Q2: What is the inner loop's bound, and how does it compare with the star triangle's?  -> `col <= row`, exactly the same bound, because the two patterns have the same shape
// Q3: What goes wrong if `cout << col;` is used instead of `cout << row;`?  -> the shape stays correct but the values restart at 1 in every row, giving 1, then 1 2, then 1 2 3
// Q4: Why can the inner counter not supply the value on its own?  -> because it restarts at 1 on every row and so does not know which row it is in
// Q5: How many times does the inner body run in total?  -> 15 times, by addition: 1 + 2 + 3 + 4 + 5, since each row is a different length
