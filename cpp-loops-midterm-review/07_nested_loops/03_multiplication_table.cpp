// ============================================================
// PROGRAM: Nested Loops - Building a Multiplication Table
// TOPIC: two loops needed for a grid, one loop enough for a single list
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - Turning a table you can draw on paper into exactly two loops.
// - The naming that makes it readable: `i` is the OUTER loop (which table is
//   this), `j` is the INNER loop (which multiple of it).
// - That ONE LOOP IS ENOUGH when the shape is a single straight line of items,
//   and you need a second loop only when the shape has ROWS.
// - Why a calculation like `j * i` is written in the order the question asks
//   for it, not in the order the variables happen to be declared in.
//
// EXPECTED OUTPUT:
// === Part 1: five tables, one after another, made with TWO nested loops ===
// --- table of 1 ---
// 1 x 1 = 1
// 2 x 1 = 2
// 3 x 1 = 3
// 4 x 1 = 4
// 5 x 1 = 5
// --- table of 2 ---
// 1 x 2 = 2
// 2 x 2 = 4
// 3 x 2 = 6
// 4 x 2 = 8
// 5 x 2 = 10
// --- table of 3 ---
// 1 x 3 = 3
// 2 x 3 = 6
// 3 x 3 = 9
// 4 x 3 = 12
// 5 x 3 = 15
// --- table of 4 ---
// 1 x 4 = 4
// 2 x 4 = 8
// 3 x 4 = 12
// 4 x 4 = 16
// 5 x 4 = 20
// --- table of 5 ---
// 1 x 5 = 5
// 2 x 5 = 10
// 3 x 5 = 15
// 4 x 5 = 20
// 5 x 5 = 25
//
// === Part 2: the whole 5x5 table as a grid of products ===
// 1 2 3 4 5
// 2 4 6 8 10
// 3 6 9 12 15
// 4 8 12 16 20
// 5 10 15 20 25
//
// === Part 3: ONE table, made with a SINGLE loop ===
// 1 x 7 = 7
// 2 x 7 = 14
// 3 x 7 = 21
// 4 x 7 = 28
// 5 x 7 = 35
// one table of one number is a single straight line, so one loop is enough
// the extra loop in Part 1 exists only to repeat that whole line 5 times
//
// IMPORTANT SYNTAX:
// cout << j << " x " << i << " = " << j * i << endl;  -> one fact, in the order asked for
// if (j > 1) { cout << " "; }  -> print the gap BEFORE a cell, not after, so no line ends in a space
//
// THE DECISION RULE, IN ONE LINE
//   How many ROWS does your drawing have?  That is how many loops you need.
//   One row of items -> 1 loop.  A grid with rows and columns -> 2 loops.
//   A cube with rows, columns and layers -> 3 loops, one inside the other.
//
// STEP-BY-STEP EXPLANATION:
// 1. Draw the answer first. Five tables of five facts is a picture with FIVE
//    ROW-GROUPS, and each group has FIVE LINES. Two directions means two loops.
// 2. The outer loop picks which table is being printed, so it runs 1 to 5. That
//    is `i`, and it is the OUTER LOOP.
// 3. The inner loop picks which multiple is being printed, so it runs 1 to 5.
//    That is `j`, and it is the INNER LOOP.
// 4. Each line prints `j`, then `i`, then `j * i`. The multiplication is
//    `j * i` and NOT `i * j` only because the question says "j x i" - the
//    numbers are identical either way, but the printed order follows the words.
// 5. Part 2 keeps both loops but prints one number per cell instead of a whole
//    sentence, so all 25 products appear together as a grid.
// 6. Part 3 throws the outer loop away. One table of 7 is five lines in a
//    straight column, and a straight column is exactly what one loop does.
// 7. So the honest answer to "why does a single loop work here?" is: because
//    nothing in the output goes back to a previous line. There is no second
//    direction to move in, so there is nothing for a second loop to control.
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

    cout << "=== Part 1: five tables, one after another, made with TWO nested loops ==="
         << endl;

    // THE OUTER LOOP: which table are we printing? i = 1, 2, 3, 4, 5.
    for (int i = 1; i <= 5; i++) {
        cout << "--- table of " << i << " ---" << endl;

        // THE INNER LOOP: which multiple of i are we printing? j = 1 to 5.
        // It runs all the way from 1 to 5 again for EVERY value of i, because
        // its header, including `int j = 1`, is re-executed from the top each
        // time the outer loop comes round.
        for (int j = 1; j <= 5; j++) {
            cout << j << " x " << i << " = " << j * i << endl;
            // `j * i` is the INNER BODY. It is evaluated once per execution of
            // this line, using whatever values the two loops have at that
            // moment. Multiplication is commutative, so `j * i` and `i * j`
            // give the same number; only the ORDER OF PRINTING differs.
        }
    }

    // 5 outer passes x 5 inner passes = 25 executions of the inner body, which
    // is why the table above has 25 lines of facts.

    cout << endl;
    cout << "=== Part 2: the whole 5x5 table as a grid of products ===" << endl;

    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            // THE GAP IS PRINTED BEFORE THE NUMBER, NOT AFTER IT.
            // Printing " " after every cell would leave a space at the end of
            // every line, and a line that ends in a space is a line that looks
            // wrong in the source and gets eaten by editors. Testing `j > 1`
            // means "print a gap only when this is not the first cell".
            if (j > 1) {
                cout << " ";
            }
            cout << i * j;
        }

        // `endl` GOES HERE, AFTER the inner loop and INSIDE the outer loop.
        // That is what makes one output line per row of the grid. If `endl`
        // were inside the inner loop, every single product would land on its
        // own line and there would be no grid at all - just 25 separate rows.
        cout << endl;
    }

    cout << endl;
    cout << "=== Part 3: ONE table, made with a SINGLE loop ===" << endl;

    // Only ONE loop here, and that is the entire lesson of this part.
    for (int j = 1; j <= 5; j++) {
        cout << j << " x 7 = " << j * 7 << endl;
    }

    cout << "one table of one number is a single straight line, so one loop is enough"
         << endl;
    cout << "the extra loop in Part 1 exists only to repeat that whole line 5 times"
         << endl;

    // ------------------------------------------------------------
    // THE GROUPED TRACE OF PART 1 - one group per table
    // ------------------------------------------------------------
    //   i = 1
    //       j = 1
    //       j = 2
    //       j = 3
    //       j = 4
    //       j = 5
    //
    //   i = 2
    //       j = 1
    //       j = 2
    //       j = 3
    //       j = 4
    //       j = 5
    //
    //   i = 3
    //       j = 1
    //       ... and so on through i = 4 and i = 5
    //
    //   5 groups x 5 inner steps = 25 executions of the inner body
    //
    // ------------------------------------------------------------
    // TRACE TABLE - the first 10 executions of the inner body of Part 1
    // +-------+-----+-----+------------------+-------------------------+-------------+
    // | Outer | i   | j   | j x i            | Output                  | Executions  |
    // | pass  |     |     |                  |                         | so far      |
    // +-------+-----+-----+------------------+-------------------------+-------------+
    // |   1   |  1  |  1  | 1 * 1            | 1 x 1 = 1               |      1      |
    // |   1   |  1  |  2  | 2 * 1            | 2 x 1 = 2               |      2      |
    // |   1   |  1  |  3  | 3 * 1            | 3 x 1 = 3               |      3      |
    // |   1   |  1  |  4  | 4 * 1            | 4 x 1 = 4               |      4      |
    // |   1   |  1  |  5  | 5 * 1            | 5 x 1 = 5               |      5      |
    // |   2   |  2  |  1  | 1 * 2            | 1 x 2 = 2               |      6      |
    // |   2   |  2  |  2  | 2 * 2            | 2 x 2 = 4               |      7      |
    // |   2   |  2  |  3  | 3 * 2            | 3 x 2 = 6               |      8      |
    // |   2   |  2  |  4  | 4 * 2            | 4 x 2 = 8               |      9      |
    // |   2   |  2  |  5  | 5 * 2            | 5 x 2 = 10              |     10      |
    // |   ... | ... | ... | ...              | ...                     |    ...      |
    // |   5   |  5  |  5  | 5 * 5            | 5 x 5 = 25              |     25      |
    // +-------+-----+-----+------------------+-------------------------+-------------+
    //
    // The "Outer pass" column is not a second counter. It just records how many
    // times the outer loop has been round, and it stays the same for five rows
    // in a row. If you ever find yourself needing a column like that on paper,
    // write the row number instead and divide by the inner count.
    //
    // WHY PART 3 NEEDS NO NESTED LOOP - THE FULL ARGUMENT
    //   A loop is a machine for "do this body several times". A SECOND loop is
    //   a machine for "do that whole machine several times". You only need the
    //   second one when the output has a shape that repeats in two directions.
    //
    //   Part 1's output repeats in two directions: five tables, and five facts
    //   inside each table. Two directions, two loops. The outer loop moves
    //   through the tables; the inner loop moves through the facts.
    //
    //   Part 3's output repeats in only ONE direction: five facts, all in a
    //   single column. One direction, one loop. There is no row to come back
    //   to, so there is nothing for an outer loop to control.
    //
    //   A single loop is also FASTER here, and that is not a metaphor: the
    //   nested version in Part 1 has to set j back to 1 twenty-five times,
    //   while the single loop sets its counter to 1 exactly once. Use the
    //   simplest loop that can produce the shape you were asked for.
    //
    //   The rule to remember for exams: count the DIRECTIONS in the drawing,
    //   then write one loop per direction, nesting each new loop inside the
    //   previous one.
    //
    // COMMON TRAP
    //   Writing `cout << " " << i * j;` inside the inner loop instead of
    //   testing `j > 1` first. It looks shorter and it prints the same visible
    //   grid, but every line now ends in a space. That matters for two
    //   reasons: an expected-output block in a document loses the trailing
    //   space when it is trimmed, so your output stops matching; and any
    //   program that later reads the text back would see an extra gap.
    //
    //   The second trap is putting `endl` inside the inner loop out of habit
    //   from Part 1. Part 1 wants one line per fact. Part 2 wants one line per
    //   row. The same two loops, a different placement of `endl`, produce two
    //   completely different shapes - and `endl` after the inner loop is the
    //   one that builds grids.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: How many times does the inner body of Part 1 run, and how is that worked out?  -> 25 times, from outer passes x inner passes = 5 x 5
// Q2: Which loop in Part 1 is called the outer loop, and what does its counter control?  -> the loop over i, which controls which of the five tables is being printed
// Q3: Why is `endl` placed after the inner loop in Part 2 but inside it in Part 1?  -> inside the inner loop it breaks after every fact; after the inner loop it breaks once per completed row, which is what makes a grid
// Q4: Why can Part 3 print a table of 7 with only one loop?  -> a single table is one straight column of items with only one direction to move in, so there is nothing for an outer loop to control
// Q5: Why is the gap in Part 2 printed with `if (j > 1)` instead of after every number?  -> so that no output line ends in a trailing space, since a gap is needed only between cells and never after the last one
