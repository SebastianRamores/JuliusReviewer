// ============================================================
// PROGRAM: Pattern 1 - A 5x5 Square of Stars
// TOPIC: a nested loop whose inner bound is a CONSTANT
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - The easiest nested-loop pattern there is, used as the baseline for every
//   other pattern in this folder.
// - That when every row is identical, the inner loop's bound is a NUMBER, not a
//   variable, and it never changes from row to row.
// - That `endl` belongs AFTER the inner loop, not inside it, because a row is
//   not finished until the inner loop has finished.
// - How one extra condition turns a solid block into an outline, using `if`
//   inside the inner loop.
//
// EXPECTED OUTPUT:
// === Part 1: a solid 5x5 square of stars ===
// *****
// *****
// *****
// *****
// *****
// the inner loop ran 5 times on each of 5 rows: 5 x 5 = 25 stars
//
// === Part 2: a 4x4 square where each cell shows its position ===
// (1,1) (1,2) (1,3) (1,4)
// (2,1) (2,2) (2,3) (2,4)
// (3,1) (3,2) (3,3) (3,4)
// (4,1) (4,2) (4,3) (4,4)
// the row and the column are still in step, because both loops go 1 to 4
//
// === Part 3: a hollow 5x5 square, drawn with an if inside the inner loop ===
// *****
// *   *
// *   *
// *   *
// *****
// a hollow square is still 5 x 5 = 25 visits to a cell; only 16 print a star
//
// === Part 4: the hollow square with no if at all, for comparison ===
// *****
// *****
// *****
// *****
// *****
// this is Part 1 again - the shape on your paper has to come from the code
//
// IMPORTANT SYNTAX:
// for (int row = 1; row <= 5; row++)      -> 5 rows, so row runs 1 to 5
//     for (int col = 1; col <= 5; col++)  -> 5 stars per row; 5 is a CONSTANT
//         cout << "*";                    -> one cell; no space, so cells touch
//     cout << endl;                        -> ONE break per row, after the inner loop
// if (row == 1 || row == 5 || col == 1 || col == 5) -> print only the border cells
//
// THE VOCABULARY THIS WHOLE FOLDER USES
//   ROW      = one horizontal line of output, produced by ONE pass of the outer loop
//   CELL     = one position within a row, produced by ONE pass of the inner loop
//   OUTER    = the loop that counts rows
//   INNER    = the loop that counts cells within the current row
//   BOUND    = the limit in the loop's test, e.g. `col <= 5`
//
// STEP-BY-STEP EXPLANATION:
// 1. Count the drawing BEFORE writing code. This one has five rows of five.
// 2. Rows go in the OUTER loop, because a row is one whole line of output and
//    one line break finishes one row.
// 3. Cells go in the INNER loop, one per execution, and the star is printed
//    with no space so the cells sit next to each other.
// 4. Both bounds are the literal number 5. Nothing in this program depends on
//    `row`, so every row comes out identical. THAT is what "constant inner
//    bound" means, and it is the fact the next seven files change one piece at
//    a time.
// 5. `endl` sits after the inner loop and inside the outer loop. Inside the
//    inner loop it would give one star per line - 25 single-star lines instead
//    of five rows of five.
// 6. Part 2 changes only the printed text and the size, so it teaches that the
//    LOOPS and the SHAPE are separate decisions.
// 7. Part 3 keeps the loop structure identical and adds one test per cell. A
//    cell prints a star when it is on the top row, the bottom row, the left
//    column or the right column; everywhere else it prints nothing.
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

    cout << "=== Part 1: a solid 5x5 square of stars ===" << endl;

    for (int row = 1; row <= 5; row++) {
        // THE OUTER LOOP COUNTS ROWS. `row` is 1, 2, 3, 4, 5 - five passes,
        // one per line of output. The `row` variable is not used anywhere in
        // the body of this program, and that is not an oversight: it is the
        // proof that the shape does not depend on which row is being printed.

        for (int col = 1; col <= 5; col++) {
            // THE INNER LOOP COUNTS THE CELLS IN THE CURRENT ROW.
            //
            // THE BOUND IS THE LITERAL NUMBER 5 - A CONSTANT. It is written
            // here as `col <= 5`, and there is no `row` anywhere in the test.
            // So the inner loop runs 1, 2, 3, 4, 5 on row 1, and then runs
            // 1, 2, 3, 4, 5 again on row 2, and again on row 3. Five times
            // every time, on every row, forever. A bound that never changes
            // is what makes every row of the square identical.
            //
            // `col` also restarts at 1 each row, because `int col = 1;` is part
            // of this loop's header and headers re-run from the top.

            cout << "*";
            // ONE `cout` CALL PER CELL, printing the symbol with NO SPACE after
            // it. That is what makes the stars touch and form a solid block.
            // The alternative `cout << "* ";` puts a gap after the last star
            // too, which would leave every line ending in a space and would
            // stop the block looking solid.
        }

        // `endl` GOES HERE: after the inner loop, inside the outer loop.
        // This is the single most important placement decision in patterns.
        // Here it means "one line break per finished row", which is what makes
        // rows. Placing it inside the inner loop would mean "a break after
        // every star", giving 25 lines of one star each and no square at all.
        cout << endl;
    }

    cout << "the inner loop ran 5 times on each of 5 rows: 5 x 5 = 25 stars" << endl;

    cout << endl;
    cout << "=== Part 2: a 4x4 square where each cell shows its position ===" << endl;

    for (int row = 1; row <= 4; row++) {
        for (int col = 1; col <= 4; col++) {
            if (col > 1) {
                // A GAP IS PRINTED BEFORE EVERY CELL EXCEPT THE FIRST ON THE
                // LINE. Testing `col > 1` means "print a space unless this is
                // the first cell", and that is what stops any line from ending
                // in a space. Printing `" "` after every cell instead would
                // give the same visible shape but a trailing space on each line.
                cout << " ";
            }
            cout << "(" << row << "," << col << ")";
        }
        cout << endl;
    }

    cout << "the row and the column are still in step, because both loops go 1 to 4"
         << endl;

    cout << endl;
    cout << "=== Part 3: a hollow 5x5 square, drawn with an if inside the inner loop ==="
         << endl;

    for (int row = 1; row <= 5; row++) {
        for (int col = 1; col <= 5; col++) {
            // THE FOUR BORDER CONDITIONS, JOINED WITH `||`.
            //
            // `||` is the LOGICAL OR. It is true when AT LEAST ONE side is
            // true, which is exactly what "this cell is on the border" means -
            // a corner cell satisfies two of the four tests at once and still
            // counts only once.
            //
            // A cell on the BORDER prints a star. A cell in the MIDDLE prints
            // nothing at all - not a space, nothing. That is deliberate: the
            // interior of the square is empty, and an empty cell needs no
            // output, so the spaces you can see are just the gaps between the
            // three stars that were printed.
            //
            // Note what has NOT changed: both loops still run 1 to 5, and the
            // inner loop still makes 25 visits. A hollow square is not made by
            // printing fewer cells; it is made by printing fewer STARS.
            if (row == 1 || row == 5 || col == 1 || col == 5) {
                cout << "*";
            } else {
                // THE ELSE BRANCH IS WHAT MAKES THE INTERIOR LOOK EMPTY.
                // Without it, an interior cell prints NOTHING, so row 2 would
                // come out as `**` - the two border stars butted together with
                // no gap at all. Printing one space per interior cell gives the
                // row its width, which is what you see as `*   *` on screen.
                //
                // NOTE: an interior cell is not "skipped". The inner loop still
                // visits it; this branch simply decides it has nothing to say
                // except a space. Loop visits and printed symbols are different
                // counts, and patterns that look sparse are usually full of
                // visits that print very little.
                cout << " ";
            }
        }
        cout << endl;
    }

    cout << "a hollow square is still 5 x 5 = 25 visits to a cell; only 16 print a star"
         << endl;

    cout << endl;
    cout << "=== Part 4: the hollow square with no if at all, for comparison ===" << endl;

    for (int row = 1; row <= 5; row++) {
        for (int col = 1; col <= 5; col++) {
            cout << "*";
            // SAME LOOPS AS PART 1, `if` AND `else` DELETED. The output is a
            // solid square again. This part exists to make one point
            // unarguable: if removing a line of code changes the printed shape,
            // that line was doing the shaping, and no amount of re-reading the
            // loop bounds will explain a shape the bounds do not describe.
        }
        cout << endl;
    }

    cout << "this is Part 1 again - the shape on your paper has to come from the code"
         << endl;

    // ------------------------------------------------------------
    // HOW I DERIVED THIS CODE
    // ------------------------------------------------------------
    // The rule for every pattern in this folder: build the code FROM the
    // picture, never from memory. Six steps, done on paper before typing.
    //
    // STEP 1: COUNT THE ROWS IN THE DRAWING.
    //   Part 1's drawing is five lines tall. FIVE ROWS.
    //   Five lines of output can only come from five passes of the loop that
    //   produces lines. So the OUTER LOOP runs 1 to 5: `row <= 5`.
    //   Ask yourself "how many lines does this drawing have?" and the outer
    //   bound has answered itself. If the answer is 3, the bound is 3.
    //
    // STEP 2: COUNT THE ITEMS IN THE FIRST ROW.
    //   Count the stars in the TOP row only. There are FIVE.
    //   One pass of the inner loop prints one item, so the inner loop must be
    //   able to run at least five times: `col <= 5`.
    //
    // STEP 3: COUNT THE ITEMS IN THE LAST ROW.
    //   Count the stars in the BOTTOM row. There are FIVE as well.
    //   First row 5, last row 5, and nothing in between looks different. When
    //   the first and last rows hold THE SAME NUMBER OF ITEMS, every row in
    //   between must hold that number too. That is a proof, not a guess.
    //
    // STEP 4: ASK HOW MANY ITEMS ARE IN ROW N - THE REAL QUESTION.
    //   Row 1: 5. Row 2: 5. Row 3: 5. Row 4: 5. Row 5: 5.
    //   Written as a rule: "row N contains 5 items, whatever N is."
    //   The formula has no N in it. The count does not depend on the row.
    //
    // STEP 5: DECIDE THE TWO BOUNDS.
    //   OUTER BOUND = the number of ROWS          = 5  -> `row <= 5`
    //   INNER BOUND = the number of items per row  = 5  -> `col <= 5`
    //
    // STEP 6: STATE WHAT THE INNER BOUND DEPENDS ON.
    //   THIS PROGRAM'S ANSWER: it depends on NOTHING. It is the constant 5.
    //   Write that sentence down. It is the sentence that has to change in
    //   every other pattern in this folder, and naming it here is what makes
    //   those changes obvious instead of mysterious.
    //
    //   For reference, here is how the answers differ in the other files:
    //     02_increasing_triangle    inner bound = row          (grows)
    //     03_decreasing_triangle    inner bound = 5 - row      (shrinks)
    //     04_number_triangle        inner bound = row          (grows)
    //     05_repeated_number        inner bound = row          (grows)
    //     06_inverted_number        inner bound = row, start=row
    //     07_right_aligned          inner bound = row, plus a third loop
    //     08_pyramid                inner bound = row, plus spaces
    //
    // ------------------------------------------------------------
    // TRACE TABLE - the first 9 cells of Part 1, and the whole of Part 3
    // ------------------------------------------------------------
    // +-------+---------+---------+-----------+-----------+-------------------+
// | Pass  | OUTER   | INNER   | Printed   | Cell is   | Part 3 prints   |
// |       | row     | col     | by Part 1 | on border |                |
// +-------+---------+---------+-----------+-----------+-----------------+
// |   1   |    1    |    1    |     *     |   YES     |  *             |
// |   2   |    1    |    2    |     *     |   YES     |  *             |
// |   3   |    1    |    3    |     *     |   YES     |  *             |
// |   4   |    1    |    4    |     *     |   YES     |  *             |
// |   5   |    1    |    5    |     *     |   YES     |  *             |
// |   6   |    2    |    1    |     *     |   YES     |  *             |
// |   7   |    2    |    2    |     *     |    no     |  (one space)   |
// |   8   |    2    |    3    |     *     |    no     |  (one space)   |
// |   9   |    2    |    4    |     *     |    no     |  (one space)   |
// |  ...  |   ...   |   ...   |     *     |   ...     |  ...           |
// |  25   |    5    |    5    |     *     |   YES     |  *             |
// +-------+---------+---------+-----------+-----------+-----------------+
// | total | 5 rows  | 5 each  |    25     |  16 YES   | 16 stars, 9 gaps|
// +-------+---------+---------+-----------+-----------+-----------------+
    //
    // THE OUTER AND INNER COLUMNS ARE BOTH REQUIRED. One row per execution of
    // the inner body, so 25 rows for a 5x5 square - never 5. And note the last
    // two summary lines: both versions visit 25 cells, and only the star counts
    // differ. The `if` changed what is printed, not how many times the loop ran.
    //
    // `cout << "*";` VERSUS `cout << "* ";`
    //   `"*"` prints the symbol and nothing else, so the next symbol lands
    //   directly beside it. That is what makes a solid block like *****.
    //   `"* "` prints the symbol AND a gap after it, which is what you want
    //   when items should be SEPARATED, such as a triangle `* * *`.
    //   The trap is using `"* "` for a solid block: it looks nearly identical
    //   on screen but every line then ends in a space, so an expected-output
    //   block in your notes will not match what the program prints once the
    //   editor trims it. Choose the form that matches the DRAWING.
    //
    // WHY `endl` GOES AFTER THE INNER LOOP
    //   A row is not finished until every cell in it has been printed. The
    //   inner loop knows when that is, so the line break belongs immediately
    //   after the inner loop finishes and before the outer loop moves on:
    //
    //       for (row ...) {          // row 1
    //           for (col ...) {      // five cells
    //               cout << "*";
    //           }
    //           cout << endl;        // <-- row 1 is complete, break the line
    //       }                        // now row 2 may begin
    //
    //   Put it inside the inner loop and the break happens after EVERY cell,
    //   so a 5x5 square becomes 25 lines of a single star. The rule for exams:
    //   `endl` AFTER the inner loop makes ROWS; `endl` INSIDE the inner loop
    //   makes one line per ITEM.
    //
    // COMMON TRAP
    //   Deciding the inner bound by counting the rows instead of the items in a
    //   row. For a square the two numbers happen to be the same, so the mistake
    //   is invisible here - which is exactly why it survives. It appears the
    //   moment the drawing is 4 wide and 7 tall, and then a "constant" inner
    //   bound written as 7 produces rows of seven stars that do not line up.
    //   Always count items in ONE row, on its own, away from the row count.
    //
    //   The second trap is reusing the same variable name for both loops.
    //   `for (int i = 1; i <= 5; i++) { for (int i = 1; i <= 5; i++) {...} }`
    //   declares a SECOND, SHADOWED `i` inside the outer loop's body. It
    //   compiles and prints the right square, so the error only shows up when
    //   you later try to print the row number inside the inner body and find
    //   that `i` is not what you thought. Distinct names cost nothing and make
    //   the trace table readable.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: How many times does the inner body of Part 1 run, and why?  -> 25 times, because there are 5 outer passes and the inner loop runs 5 times on each of them, so 5 x 5
// Q2: What is special about the inner loop's bound in Part 1?  -> it is the constant 5 and never changes from row to row, because every row of a square holds the same number of stars
// Q3: Why is `cout << endl;` written after the inner loop instead of inside it?  -> so the line breaks once per finished row rather than once per star, which is what creates rows
// Q4: How does Part 3 produce a hollow square without changing either loop?  -> the loops still make 25 visits, but an `if` with four `||` conditions prints a star only for cells on the border
// Q5: In Part 3, how many stars are printed, and why is that not 25?  -> 16, because the 9 interior cells satisfy none of the four border conditions and print nothing at all
