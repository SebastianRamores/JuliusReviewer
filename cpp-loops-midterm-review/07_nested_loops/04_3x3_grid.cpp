// ============================================================
// PROGRAM: Nested Loops - A 3x3 Grid, and What Each Variable Means
// TOPIC: the row variable versus the column variable, and the inner loop's reset
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - How to print a small grid with one nested loop pair.
// - That the OUTER variable is the ROW variable and the INNER variable is the
//   COLUMN variable, and that those words describe a job, not a number.
// - That `(row, column)` names ONE cell, and that the pair repeats over the
//   whole grid because the two loops repeat.
// - WHY the inner loop restarts at 1 on every outer pass, and what actually
//   breaks if you start it at 0 instead.
//
// EXPECTED OUTPUT:
// === Part 1: a 3x3 grid of numbers, cell value = row * column ===
// 1 2 3
// 2 4 6
// 3 6 9
// every cell is row x column, and there are 3 x 3 = 9 cells
//
// === Part 2: a 3x3 grid of stars ===
// * * *
// * * *
// * * *
// three rows of three stars, made by 3 x 3 = 9 executions of the inner body
//
// === Part 3: a grid where every cell shows its own row and column ===
// (1,1) (1,2) (1,3)
// (2,1) (2,2) (2,3)
// (3,1) (3,2) (3,3)
// read any cell as "row, column" - the row never changes going across a line
//
// === Part 4: what happens if the inner loop starts at 0 instead of 1 ===
// the inner loop still runs 3 times, but the columns are numbered 0, 1, 2
// here is the same grid with the inner loop starting at 0:
// 0 1 2
// 0 2 4
// 0 3 6
// the columns are now mislabelled: there is no column 0, and column 3 is
// missing, so the grid has a hole in it
//
// IMPORTANT SYNTAX:
// for (int row = 1; row <= 3; row++)     -> the ROW loop: pick which row you are on
//     for (int col = 1; col <= 3; col++) -> the COLUMN loop: pick which column in that row
//         cout << "( " << row << "," << col << ")";  -> one CELL, named by its two numbers
//     cout << endl;                       -> break the line AFTER a whole row is finished
//
// ROW VARIABLE VERSUS COLUMN VARIABLE
//   The row variable counts DOWN a column of the grid: it changes only when a
//   whole row has been printed, so it is the OUTER loop.
//   The column variable counts ACROSS a row: it changes on every single cell,
//   so it is the INNER loop.
//   If your drawn grid has more columns than rows, it is the INNER loop that has
//   the bigger bound - and nothing else about the two is different.
//
// STEP-BY-STEP EXPLANATION:
// 1. Count the shape before writing any code: 3 rows, 3 columns. Two directions,
//    so two loops, nested.
// 2. The outer loop counts rows. On row 1 the column loop runs 1, 2, 3; on row 2
//    it runs 1, 2, 3 AGAIN, because the inner header re-executes from the top.
// 3. Part 1 multiplies the two variables, which is why the middle cell is 4 and
//    the bottom-right is 9 - a useful self-check that both loops are running.
// 4. Part 2 changes only what is printed, not the loops. Nine stars, and the
//    count proves the loops ran: 3 x 3 = 9.
// 5. Part 3 prints both variables in every cell. The value printed for row is
//    the same on all three cells of a line; only the column changes going across.
// 6. Part 4 changes the inner loop's START from 1 to 0. The number of
//    executions is unchanged, so the total is still 3 x 3 = 9, but the
//    COLUMNS are renumbered and the grid no longer means what it should.
// 7. That is the real lesson of Part 4: a loop's three parts each have a job,
//    and changing the start value changes WHAT THE LOOP MEANS, not how fast it
//    runs.
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

    cout << "=== Part 1: a 3x3 grid of numbers, cell value = row * column ===" << endl;

    for (int row = 1; row <= 3; row++) {
        // THE ROW VARIABLE, and the OUTER LOOP because of it.
        // `row` only advances after the whole inner loop has run, so the row
        // number stays the same for every cell printed on the current line.
        for (int col = 1; col <= 3; col++) {
            // THE COLUMN VARIABLE, and the INNER LOOP because of it.
            // `col` restarts at 1 on every new row. That reset is what places
            // the cells in columns instead of letting them run off in a line.

            if (col > 1) {
                // The gap goes BEFORE the second and later cells only, so no
                // printed line ends in a space.
                cout << " ";
            }
            cout << row * col;
        }
        cout << endl;
        // ONE `endl` PER ROW. This line is inside the outer loop and outside
        // the inner loop, so the line break happens once the row is complete,
        // which is exactly what turns nine numbers into three lines of three.
    }

    cout << "every cell is row x column, and there are 3 x 3 = 9 cells" << endl;

    cout << endl;
    cout << "=== Part 2: a 3x3 grid of stars ===" << endl;

    for (int row = 1; row <= 3; row++) {
        for (int col = 1; col <= 3; col++) {
            if (col > 1) {
                cout << " ";
            }
            cout << "*";
            // `cout << "*"` prints ONE star. Printing a star and a space in a
            // single statement (`cout << "* ";`) would also work, but it puts
            // a space after the LAST star too, and every line would end in one.
        }
        cout << endl;
    }

    cout << "three rows of three stars, made by 3 x 3 = 9 executions of the inner body"
         << endl;

    cout << endl;
    cout << "=== Part 3: a grid where every cell shows its own row and column ===" << endl;

    for (int row = 1; row <= 3; row++) {
        for (int col = 1; col <= 3; col++) {
            if (col > 1) {
                cout << " ";
            }
            cout << "(" << row << "," << col << ")";
            // A CELL IS NAMED BY ITS PAIR OF NUMBERS. `(2,3)` means row 2,
            // column 3. Printing the pair inside the cell is the quickest way
            // to see the two variables working independently: `row` is constant
            // across a line, `col` changes on every cell.
        }
        cout << endl;
    }

    cout << "read any cell as \"row, column\" - the row never changes going across a line"
         << endl;

    cout << endl;
    cout << "=== Part 4: what happens if the inner loop starts at 0 instead of 1 ===" << endl;
    cout << "the inner loop still runs 3 times, but the columns are numbered 0, 1, 2"
         << endl;
    cout << "here is the same grid with the inner loop starting at 0:" << endl;

    for (int row = 1; row <= 3; row++) {
        for (int col = 0; col < 3; col++) {
            // ONLY THE INNER LOOP'S START AND TEST CHANGED. `col` now takes the
            // values 0, 1, 2 instead of 1, 2, 3. It still runs three times, so
            // the number of cells is unchanged - but there is no column 0 in
            // this grid and column 3 has vanished. The SHAPE survived and the
            // LABELS did not.
            if (col > 0) {
                cout << " ";
            }
            cout << row * col;
        }
        cout << endl;
    }

    cout << "the columns are now mislabelled: there is no column 0, and column 3 is"
         << endl;
    cout << "missing, so the grid has a hole in it" << endl;

    // ------------------------------------------------------------
    // THE GROUPED TRACE OF PART 1 - the row loop holds still while the
    // column loop runs, and that is the whole story of a grid
    // ------------------------------------------------------------
    //   row = 1
    //       col = 1
    //       col = 2
    //       col = 3
    //
    //   row = 2
    //       col = 1
    //       col = 2
    //       col = 3
    //
    //   row = 3
    //       col = 1
    //       col = 2
    //       col = 3
    //
    //   3 rows x 3 columns = 9 executions of the inner body = 9 cells
    //
    // ------------------------------------------------------------
    // TRACE TABLE - all nine cells of Part 1
    // +---------+------+------+---------------+--------------+---------------+
    // | Cell    | row  | col  | row * col     | Output       | Executions so |
    // | number  |      |      |               |              | far           |
    // +---------+------+------+---------------+--------------+---------------+
    // |    1    |  1   |  1   | 1 * 1 = 1     | 1            |      1        |
    // |    2    |  1   |  2   | 1 * 2 = 2     | 1 2          |      2        |
    // |    3    |  1   |  3   | 1 * 3 = 3     | 1 2 3        |      3        |
    // |    4    |  2   |  1   | 2 * 1 = 2     | 2            |      4        |
    // |    5    |  2   |  2   | 2 * 2 = 4     | 2 4          |      5        |
    // |    6    |  2   |  3   | 2 * 3 = 6     | 2 4 6        |      6        |
    // |    7    |  3   |  1   | 3 * 1 = 3     | 3            |      7        |
    // |    8    |  3   |  2   | 3 * 2 = 6     | 3 6          |      8        |
    // |    9    |  3   |  3   | 3 * 3 = 9     | 3 6 9        |      9        |
    // +---------+------+------+---------------+--------------+---------------+
    //
    // The "Output" column here shows the WHOLE LINE after each cell, so you can
    // see the third row of that column is exactly the third line of Part 1's
    // output. Rows 1, 2 and 3 of the grid are the last three rows of the table.
    //
    // WHY THE INNER LOOP MUST RESET - THE EXACT REASON
    //   The inner loop is not a piece of code that runs once. It is a piece of
    //   code that runs nine times, and each run STARTS AT THE TOP. Starting at
    //   the top means running `int col = 1;` again, which puts col back to 1.
    //
    //   So on row 1 the sequence of col values is 1, 2, 3. On row 2 it is
    //   1, 2, 3 again, NOT 4, 5, 6. The reset is what keeps the grid's columns
    //   lined up. Without a reset, every row would start further to the right
    //   than the row above it, and the output would be a staircase.
    //
    //   Try it as an experiment: declare `int col = 0;` BEFORE the outer loop
    //   and write `col++` in the inner loop instead of `col = 1`. Then col
    //   really does run 1 to 9 across the whole program, and you get the
    //   staircase. Both programs print nine things; only one of them is a grid.
    //
    // WHAT HAPPENS IF THE INNER LOOP STARTS AT 0 - PART 4 PROVES IT
    //   Nothing CRASHES and nothing loops forever. The loop runs the same
    //   number of times. What changes is the MEANING of the counter: `col` now
    //   counts 0, 1, 2, which are not the column numbers the grid is using.
    //   The first column of Part 4 prints row * 0, which is always 0, so the
    //   whole left column of the grid reads 0 - a column that should have held
    //   1, 2, 3. The grid has not lost a column; it has relabelled them, and
    //   shifted every cell one place to the left.
    //
    //   In an exam, "start at 0" is the right answer when the question counts
    //   from zero (array indices, "the 0th row"), and the wrong answer when
    //   the drawing is numbered from 1. Matching the numbering of the question
    //   is worth more marks than any cleverer alternative.
    //
    // COMMON TRAP
    //   Believing the inner loop carries its counter on from the previous row,
    //   and therefore writing a trace with col running 1 to 9. If your trace
    //   does not restart at 1, your grid will be a staircase rather than a
    //   grid - and the trace above is the fastest way to notice.
    //
    //   The second trap is naming the variables `i` and `j` and then writing
    //   comments that say "row i, column j" in one place and "i is the inner
    //   loop" in another. Naming them `row` and `col` costs nothing and makes
    //   the answer self-checking, which matters far more in an exam than
    //   looking conventional.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: Which variable is the row variable in a grid, and which is the column variable?  -> the outer loop's variable is the row; the inner loop's variable is the column
// Q2: Why does the column variable restart at 1 on every new row?  -> because the inner loop's header, including its initial value, is re-executed from the top on every pass of the outer loop
// Q3: If the inner loop started at 0 instead of 1, how many cells would the 3x3 grid print?  -> still 9, because the number of executions depends on the bounds, but the columns would be numbered 0, 1, 2 and the grid would be relabelled
// Q4: Where must the `endl` be placed to get one output line per row?  -> after the inner loop but inside the outer loop, so it fires once per completed row
// Q5: What does `(3,2)` mean in Part 3's output, and which loop produced it?  -> row 3, column 2, produced on the third pass of the outer loop and the second pass of the inner loop
