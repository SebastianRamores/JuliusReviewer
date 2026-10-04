// ============================================================
// PROGRAM: Tracing a Nested Loop - Every Single Execution
// TOPIC: how to hand-trace nested loops without running the program
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - A repeatable 4-step method for tracing ANY loop on paper, before you ever
//   run it.
// - That a trace has ONE ROW PER EXECUTION of the INNER body.
// - That the OUTER counter changes slowly, once per group, while the INNER
//   counter changes quickly, once per row. That single sentence is the whole
//   trick to reading a trace.
// - How to record a running total ("executions so far") in the last column.
// - How to write the same information twice: once vertically, once as a table.
//
// EXPECTED OUTPUT:
// === Part 1: the loop we are going to trace by hand ===
// for (int i = 1; i <= 3; i++) {
//     for (int j = 1; j <= 3; j++) {
//         print i, j, i * j and i + j on one line
//     }
// }
// the outer loop has 3 values and the inner loop has 3 values
// 3 x 3 = 9 executions of the inner body, so the trace has 9 rows
//
// === Part 2: what the program actually prints ===
// i = 1  j = 1  i*j = 1  i+j = 2
// i = 1  j = 2  i*j = 2  i+j = 3
// i = 1  j = 3  i*j = 3  i+j = 4
// i = 2  j = 1  i*j = 2  i+j = 3
// i = 2  j = 2  i*j = 4  i+j = 4
// i = 2  j = 3  i*j = 6  i+j = 5
// i = 3  j = 1  i*j = 3  i+j = 4
// i = 3  j = 2  i*j = 6  i+j = 5
// i = 3  j = 3  i*j = 9  i+j = 6
//
// === Part 3: the same 9 executions, numbered, with a running total ===
// execution 1: i = 1, j = 1, i*j = 1, i+j = 2
// execution 2: i = 1, j = 2, i*j = 2, i+j = 3
// execution 3: i = 1, j = 3, i*j = 3, i+j = 4
// execution 4: i = 2, j = 1, i*j = 2, i+j = 3
// execution 5: i = 2, j = 2, i*j = 4, i+j = 4
// execution 6: i = 2, j = 3, i*j = 6, i+j = 5
// execution 7: i = 3, j = 1, i*j = 3, i+j = 4
// execution 8: i = 3, j = 2, i*j = 6, i+j = 5
// execution 9: i = 3, j = 3, i*j = 9, i+j = 6
// final row number = 10, so the last execution was number 9
//
// === Part 4: the vertical grouped trace, one group per outer value ===
//   i = 1
//       j = 1
//       j = 2
//       j = 3
//
//   i = 2
//       j = 1
//       j = 2
//       j = 3
//
//   i = 3
//       j = 1
//       j = 2
//       j = 3
//
// each group holds one full run of the inner loop, from j = 1 again
// 3 groups x 3 inner steps = 9 executions of the inner body
//
// IMPORTANT SYNTAX:
// int row = 1;                 -> a trace row counter; it exists only to number the rows
//     cout << "execution " << row;  -> prints the row number so you can tick rows off
//   row++;                      -> AFTER printing, not before, or every row is off by one
//
// THE THREE NUMBERS EVERY TRACE NEEDS BEFORE YOU START
//   outer start, outer end      -> here 1 and 3, so i is 1, 2, 3
//   inner start, inner end      -> here 1 and 3, so j is 1, 2, 3
//   total executions            -> outer count x inner count = 3 x 3 = 9 rows
// Get these three right and the rest of the trace is just filling in a grid
// nine squares long. Get the total wrong and every row number after it is wrong.
//
// STEP-BY-STEP EXPLANATION:
// 1. Read the question first. "How many times does the body run?" wants the
//    multiplication. "What is the 6th value printed?" wants the trace table.
// 2. Write down the outer loop's range: i goes 1, 2, 3. That is the number of
//    GROUPS in your trace.
// 3. Write down the inner loop's range: j goes 1, 2, 3. That is the number of
//    ROWS inside each group.
// 4. Multiply to get the number of rows in total: 3 x 3 = 9. Draw 9 rows before
//    you fill anything in. If you run out of rows, or have rows left over, your
//    two counts do not agree with each other.
// 5. Fill in the rows. Outer value changes SLOWLY (once every 3 rows); inner
//    value changes FAST (once every row). This is why i reads 1,1,1,2,2,2,3,3,3
//    and j reads 1,2,3,1,2,3,1,2,3.
// 6. Only now compute anything. i*j and i+j are ordinary arithmetic on the two
//    values in that row; doing them first, before the values are right, is how
//    students produce a beautifully formatted wrong answer.
// 7. Part 4 shows the same nine executions grouped under their outer value,
//    which is the shape examiners hand back to you when they ask for "a trace".
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

    cout << "=== Part 1: the loop we are going to trace by hand ===" << endl;
    cout << "for (int i = 1; i <= 3; i++) {" << endl;
    cout << "    for (int j = 1; j <= 3; j++) {" << endl;
    cout << "        print i, j, i * j and i + j on one line" << endl;
    cout << "    }" << endl;
    cout << "}" << endl;
    cout << "the outer loop has 3 values and the inner loop has 3 values" << endl;
    cout << "3 x 3 = 9 executions of the inner body, so the trace has 9 rows" << endl;

    cout << endl;
    cout << "=== Part 2: what the program actually prints ===" << endl;

    // THE LOOP BEING TRACED. Compare it with the listing printed above: it does
    // exactly what the listing says, so the listing is a fair description of
    // the code and not a summary of it.
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            // The inner body. It prints the values it was given rather than
            // anything clever, because a tracing exercise is about the LOOP
            // values, not about arithmetic. Every number on the line comes from
            // i, from j, or from an expression built out of i and j.
            cout << "i = " << i << "  j = " << j
                 << "  i*j = " << i * j
                 << "  i+j = " << i + j << endl;
        }
    }

    cout << endl;
    cout << "=== Part 3: the same 9 executions, numbered, with a running total ===" << endl;

    // THE ROW COUNTER IS DECLARED BEFORE BOTH LOOPS, for the same reason as any
    // accumulator: if it were declared inside a loop it would be reset to 1 on
    // every pass and the numbers would all come out as 1.
    int row = 1;

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << "execution " << row << ": "
                 << "i = " << i << ", "
                 << "j = " << j << ", "
                 << "i*j = " << i * j << ", "
                 << "i+j = " << i + j << endl;
            // `row` is printed BEFORE it is increased. Reversing those two
            // statements would label the first execution 2 and the last 10 -
            // and the last row would say 10 while only 9 executions happened.
            row++;
        }
    }

    cout << "final row number = " << row << ", so the last execution was number "
         << (row - 1) << endl;

    cout << endl;
    cout << "=== Part 4: the vertical grouped trace, one group per outer value ===" << endl;

    for (int i = 1; i <= 3; i++) {
        cout << "  i = " << i << endl;
        for (int j = 1; j <= 3; j++) {
            cout << "      j = " << j << endl;
        }
        cout << endl;
        // The blank line comes AFTER the inner loop, once per group. Placing
        // `endl` inside the inner loop would put a blank line after every j and
        // the three groups would no longer read as three groups.
    }

    cout << "each group holds one full run of the inner loop, from j = 1 again"
         << endl;
    cout << "3 groups x 3 inner steps = 9 executions of the inner body" << endl;

    // ------------------------------------------------------------
    // THE TRACE TABLE - the exact format an exam answer should use
    // ------------------------------------------------------------
    // +---------+-----+-----+-------+-------+----------------------+---------------+
    // | Iteration| i   | j   | i*j   | i+j   | Output               | Executions so |
    // |         |     |     |       |       |                      | far           |
    // +---------+-----+-----+-------+-------+----------------------+---------------+
    // |    1    |  1  |  1  |   1   |   2   | i = 1  j = 1         |       1       |
    // |    2    |  1  |  2  |   2   |   3   | i = 1  j = 2         |       2       |
    // |    3    |  1  |  3  |   3   |   4   | i = 1  j = 3         |       3       |
    // |    4    |  2  |  1  |   2   |   3   | i = 2  j = 1         |       4       |
    // |    5    |  2  |  2  |   4   |   4   | i = 2  j = 2         |       5       |
    // |    6    |  2  |  3  |   6   |   5   | i = 2  j = 3         |       6       |
    // |    7    |  3  |  1  |   3   |   4   | i = 3  j = 1         |       7       |
    // |    8    |  3  |  2  |   6   |   5   | i = 3  j = 2         |       8       |
    // |    9    |  3  |  3  |   9   |   6   | i = 3  j = 3         |       9       |
    // +---------+-----+-----+-------+-------+----------------------+---------------+
    //
    // CHECK THE TABLE THREE DIFFERENT WAYS - this is how you catch a wrong trace
    //   1. ROW COUNT. 9 rows, because 3 x 3 = 9. If your own trace has 6 or 12
    //      rows, one of your two ranges was miscounted.
    //   2. COLUMN VALUES. Read the i column down: 1, 1, 1, 2, 2, 2, 3, 3, 3.
    //      Every value must appear exactly as many times as the inner loop has
    //      steps. Read the j column down: 1, 2, 3, 1, 2, 3, 1, 2, 3 - it must
    //      restart from 1 at the top of every group.
    //   3. ARITHMETIC. i*j on row 6 is 2 * 3 = 6, and i+j on row 9 is 3 + 3 = 6.
    //      Interesting: both are 6 on different rows. A trace where you are not
    //      sure which is which is a trace you should redo.
    //
    // THE VERTICAL GROUPED TRACE OF THE SAME NINE EXECUTIONS
    //   i = 1
    //       j = 1
    //       j = 2
    //       j = 3
    //
    //   i = 2
    //       j = 1
    //       j = 2
    //       j = 3
    //
    //   i = 3
    //       j = 1
    //       j = 2
    //       j = 3
    //
    // THE TOTAL NUMBER OF TIMES THE INNER BODY EXECUTES
    //   outer passes x inner passes = total inner executions
    //          3     x      3        =          9
    //
    // WHY "ONE ROW PER INNER EXECUTION" AND NEVER ONE ROW PER OUTER PASS
    //   The outer loop passes 3 times. The inner loop passes 3 times. Those are
    //   two different counts of two different things, and a trace has to be
    //   about one of them in particular. The rule is: a row is one trip through
    //   the body that sits between the two loops' braces, so 9 rows. The inner
    //   counter changing value is the signal that a new row has begun.
    //
    // COMMON TRAP
    //   Swapping the speeds of the two counters and writing
    //       i = 1 j = 1 / i = 2 j = 1 / i = 3 j = 1 / i = 1 j = 2 / ...
    //   That is the shape of a mistake, not of a nested loop. The outer value
    //   cannot go back to 1 while the inner loop is still running, because the
    //   outer loop's `i++` only runs when the inner loop has finished. Fix for
    //   this in your head: hold the outer value still for the whole group, then
    //   move it on one step.
    //
    //   The second trap is tidying the table too early. A trace with a neatly
    //   aligned answer in a column you have not filled from top to bottom will
    //   have an error somewhere, and the tidying hides it instead of showing it.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: How many times does the body of a nested loop run when the outer loop has 4 values and the inner loop has 5?  -> 4 x 5 = 20 times, because each outer pass runs a complete inner loop
// Q2: In a nested trace, which counter changes once per row and which changes once per group?  -> the inner counter changes once per row; the outer counter changes once per group, after the inner loop has finished
// Q3: Why does the value of j return to 1 three times in the table above?  -> because the inner loop header including int j = 1 is re-executed at the start of every outer pass
// Q4: A trace of a nested loop needs one row per execution of what?  -> per execution of the inner body, so outer passes x inner passes rows in total
// Q5: On which row of the table above is i*j equal to 6, and what is i+j on that same row?  -> on row 6, where i = 2 and j = 3 give i*j = 6, and i+j is 5 on that row
