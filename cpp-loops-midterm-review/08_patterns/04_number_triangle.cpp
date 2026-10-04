// ============================================================
// PROGRAM: Pattern 4 - A Triangle of Consecutive Numbers
// TOPIC: the accumulator, and why it must be declared outside both loops
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - How to print `1`, then `1 2`, then `1 2 3`, with a nested loop whose inner
//   bound is the row number.
// - That an ACCUMULATOR is a variable that carries information from one pass of
//   a loop into the next, and that a variable declared INSIDE a loop can do no
//   such thing.
// - Why the accumulator has to be declared OUTSIDE both loops: it has to be
//   readable and resettable in two different places.
// - That deleting one line - the reset - turns the same program into a
//   completely different pattern, and that the printed values are decided by
//   the accumulator while the printed SHAPE is decided by the inner bound.
// - The variant that uses a single counter and no inner loop at all.
//
// EXPECTED OUTPUT:
// === Part 1: nested loops, with the accumulator reset each row ===
// 1
// 1 2
// 1 2 3
// 1 2 3 4
// 1 2 3 4 5
// the accumulator was reset before every row, so each row starts again at 1
// the inner body ran 1 + 2 + 3 + 4 + 5 = 15 times
//
// === Part 2: the SAME program with the reset line deleted ===
// 1
// 2 3
// 4 5 6
// 7 8 9 10
// 11 12 13 14 15
// one line of code removed, and the values no longer restart
// this is what an accumulator WITHOUT a reset does: it carries its value
// on
//
// === Part 3: the accumulator declared INSIDE the outer loop ===
// 1
// 1 2
// 1 2 3
// 1 2 3 4
// 1 2 3 4 5
// the shape is IDENTICAL to Part 1, so the bug is invisible in the output
// but the running total after the loops is 6, not 16
//
// === Part 4: the single-counter version, with NO inner loop ===
// 1
// 1 2
// 1 2 3
// 1 2 3 4
// 1 2 3 4 5
// one loop, one counter, and a test that decides when the row is complete
// total printed = 15, exactly matching the nested version
//
// IMPORTANT SYNTAX:
// int n = 1;                    -> the ACCUMULATOR, declared before BOTH loops
//     n = 1;                    -> an explicit RESET; the line Part 2 deletes
//     cout << n;                -> print the carried value
//     n++;                      -> advance it, AFTER printing
// if (next == endOfRow) { ... } -> Part 4's test for "this row is finished"
//
// AN ACCUMULATOR, DEFINED PRECISELY
//   A loop COUNTER counts passes of one loop and forgets everything between.
//   An ACCUMULATOR carries a value forward: it is updated during the loop and
//   still holds that value afterwards. `n` here is an accumulator because it
//   remembers what it was doing on the previous row.
//
// STEP-BY-STEP EXPLANATION:
// 1. Count five rows, so the outer loop runs 1 to 5.
// 2. Count the first row: one number. Count the last row: five numbers.
// 3. So row N holds N numbers and the inner bound is `col <= row`, exactly as
//    in the star triangle of 02_increasing_triangle.cpp.
// 4. The difference is the printed VALUE. It comes from `n`, not from `col`.
// 5. `n` is declared before both loops so it survives between rows, and reset
//    explicitly at the top of each row so the numbers restart at 1.
// 6. Part 2 deletes only the reset, and the values run on unbroken - proving
//    that the accumulator, not the loop bound, decides the values.
// 7. Part 4 produces the identical triangle from ONE loop, using a test that
//    ends each row at the right number.
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

    cout << "=== Part 1: nested loops, with the accumulator reset each row ==="
         << endl;

    // THE ACCUMULATOR, DECLARED BEFORE BOTH LOOPS.
    //
    // AN ACCUMULATOR is a variable that is UPDATED as a loop runs so that it
    // carries information from one pass into the next. A plain loop counter like
    // `i` counts passes and forgets; an accumulator remembers.
    //
    // `n` starts at 1 because the first number of the triangle IS 1. It is
    // declared HERE, outside every loop, and that placement is the whole lesson
    // of this file - see Part 3 for what happens when it moves inside.
    int n = 1;

    for (int row = 1; row <= 5; row++) {
        // THE OUTER LOOP COUNTS THE ROWS: 1, 2, 3, 4, 5.

        n = 1;
        // THE RESET, AND THE LINE THAT MAKES THIS PATTERN WHAT IT IS.
        //
        // This statement sits BETWEEN the two loops, so it runs once per outer
        // pass - that is, once per row - before the inner loop starts. It puts
        // the accumulator back to 1 at the top of every row, which is why row 2
        // prints 1 and row 3 prints 1, 2 and so on.
        //
        // It only works because `n` was declared OUTSIDE the outer loop. Had it
        // been declared inside, it would have been rebuilt at 1 on every pass
        // anyway and this line would be redundant - which is exactly what makes
        // Part 3's bug invisible in the output.
        //
        // The statement is NOT part of the inner loop. Putting it inside would
        // reset the accumulator on every single number, and every row would
        // print nothing but 1s. Its position between the loops is the position
        // that gives "once per row".

        for (int col = 1; col <= row; col++) {
            // THE INNER LOOP COUNTS THE NUMBERS IN THE CURRENT ROW. Its bound is
            // `row`, so row 1 prints one number, row 2 prints two, and so on.
            // That is the same inner bound as the star triangle in
            // 02_increasing_triangle.cpp, because it is the same SHAPE.

            if (col > 1) {
                cout << " ";
            }
            cout << n;
            // THE PRINTED VALUE IS `n`, NOT `col`. This is the difference that
            // separates this pattern from a star triangle. In the star triangle
            // the cell counter and the printed thing are the same value. Here
            // `col` says WHICH position this is and `n` says WHAT to print.

            n++;
            // ADVANCE THE ACCUMULATOR AFTER PRINTING, NEVER BEFORE.
            //
            // The order matters and is worth being able to explain. With `n++`
            // first, the first number printed would be 2, the triangle would
            // read 2 / 2 3 / 2 3 4, and every row would be shifted up by one.
            // `n++` sits inside the inner body, so it runs once per printed
            // number: 15 times over this program.
        }

        cout << endl;
        // AFTER the inner loop, inside the outer loop: one break per finished
        // row. Inside the inner loop it would break after every number, giving
        // 15 lines of one number each.
    }

    cout << "the accumulator was reset before every row, so each row starts again at 1"
         << endl;
    cout << "the inner body ran 1 + 2 + 3 + 4 + 5 = " << (1 + 2 + 3 + 4 + 5)
         << " times" << endl;
    // An ADDITION rather than a multiplication, because every row is a different
    // length. A square's total is rows x cells; a triangle's is the sum of the
    // row lengths. Here both figures are 15: the inner body ran 15 times and
    // printed 15 numbers.

    cout << endl;
    cout << "=== Part 2: the SAME program with the reset line deleted ===" << endl;

    // ONE LINE REMOVED FROM PART 1 - the `n = 1;` between the loops. That is all
    // it takes to turn one pattern into a different one.
    int carried = 1;

    for (int row = 1; row <= 5; row++) {
        // NO RESET HERE. So `carried` keeps whatever value the previous row left
        // it at, and the numbers run on unbroken: 1, then 2 3, then 4 5 6.
        //
        // THIS IS WHAT AN ACCUMULATOR NATURALLY DOES. It carries its value
        // forward, so leaving it alone gives you a single unbroken sequence laid
        // out in rows of increasing length. Part 1 and Part 2 print the same
        // NUMBER of values in the same SIZES of rows; the only difference is
        // which numbers those are.
        //
        // It is worth noticing that this second shape is a perfectly good
        // pattern too - it is the number pyramid from 08_pyramid.cpp. Patterns
        // are not right or wrong; they are decided by the accumulator you write.

        for (int col = 1; col <= row; col++) {
            if (col > 1) {
                cout << " ";
            }
            cout << carried;
            carried++;
        }
        cout << endl;
    }

    cout << "one line of code removed, and the values no longer restart" << endl;
    cout << "this is what an accumulator WITHOUT a reset does: it carries its value"
         << endl;
    cout << "on" << endl;
    // The counter ends at 16, one more than the 15 numbers printed, because the
    // final `carried++` runs after the last print.

    cout << endl;
    cout << "=== Part 3: the accumulator declared INSIDE the outer loop ===" << endl;

    // Compare this pair of loops with Part 1's and find the one line that moved.
    for (int row = 1; row <= 5; row++) {
        // THE BUG, WRITTEN ON PURPOSE. In Part 1 this declaration was above the
        // outer loop; here it has moved down between the two loops.
        //
        // THE CONSEQUENCE: on every pass of the outer loop the compiler builds a
        // BRAND NEW variable, starting again at 1, and destroys it at the end of
        // the pass. It cannot carry anything between rows, because it does not
        // exist between rows.
        //
        // AND THE OUTPUT DOES NOT CHANGE. Each row restarts at 1 either way -
        // Part 1 restarts by the explicit `n = 1;`, this one restarts because
        // the variable is brand new every time. The bug is completely invisible
        // in the printed shape.
        //
        // What changes is the value left behind afterwards. In Part 1 the
        // accumulator ends at 16 because it counted all 15 prints. Here it ends
        // at 6, because it was rebuilt five times and only ever counted the
        // five prints of its own final row.
        //
        // THE LESSON: never judge an accumulator from the shape of the output
        // alone. Ask what the variable is supposed to REMEMBER once the loops
        // have finished, then print it and check. A value that looks right
        // inside the loops and wrong after them is the signature of a
        // declaration in the wrong place.
        int inside = 1;

        for (int col = 1; col <= row; col++) {
            if (col > 1) {
                cout << " ";
            }
            cout << inside;
            inside++;
        }
        cout << endl;
    }

    cout << "the shape is IDENTICAL to Part 1, so the bug is invisible in the output"
         << endl;
    cout << "but the running total after the loops is 6, not 16" << endl;
    // To see the difference you would have to print the accumulator after the
    // loops - which is exactly what Part 1 does with `n`, and why that file can
    // get away with the placement.

    cout << endl;
    cout << "=== Part 4: the single-counter version, with NO inner loop ===" << endl;

    // A COMPLETELY DIFFERENT APPROACH TO THE SAME OUTPUT: ONE LOOP, NO INNER
    // LOOP, AND NO ACCUMULATOR THAT CARRIES ACROSS ROWS.
    //
    // Parts 1 to 3 ask two questions per row: "which row is this?" (outer loop)
    // and "how many numbers does it hold?" (inner loop). This version asks one
    // question per number instead: "which position am I in within my row?"
    //
    // The insight is that for THIS shape, the position within the row IS the
    // number to print, and the row length is simply "one more than last time".
    // So both quantities can be held in two variables and updated by hand,
    // and the whole triangle becomes a single loop over the 15 numbers.
    int positionInRow = 1;
    // `positionInRow` counts 1, 2, 3 ... across a row, and it is both the
    // COLUMN NUMBER and the VALUE PRINTED. One variable doing two jobs is
    // possible here only because of the special shape of this pattern; a star
    // triangle cannot do it, since the star does not need a number.
    int rowLen = 1;
    // `rowLen` is how many numbers the CURRENT row holds. It starts at 1 and
    // grows by 1 at the end of every row. This single growing value is what
    // replaced the outer loop's `row` in Part 1 - and note that it is updated
    // MANUALLY, which is the only thing the outer loop was doing.

    int step = 1;
    for (; step <= 15; step++) {
        // `step` is a plain loop counter over the 15 numbers to print. It has no
        // connection to the shape at all - remove its bound and this would run
        // forever, which is why it is bounded by 15 and not by anything about
        // rows or columns.
        //
        // It is declared BEFORE the loop rather than inside the `for` header so
        // that its final value can be printed afterwards as the total count.

        if (positionInRow > 1) {
            cout << " ";
        }
        cout << positionInRow;
        // The gap goes before every number except the first of the row, so no
        // line ends in a space. And the value printed is `positionInRow`
        // itself, which is why no accumulator is needed: the number to print
        // and the position within the row are the same thing here.

        positionInRow++;

        if (positionInRow > rowLen) {
            cout << endl;
            // THE ROW IS OVER. `positionInRow` has just become one past the
            // number of values the row was allowed, so the line breaks here.
            positionInRow = 1;
            rowLen++;
            // Back to the start of a row, and the next row is one longer. These
            // two lines together do everything the outer loop of Part 1 was
            // doing: deciding where a row ends and making the next one bigger.
        }
    }

    cout << "one loop, one counter, and a test that decides when the row is complete"
         << endl;
    cout << "total printed = " << (step - 1) << ", exactly matching the nested version"
         << endl;
    // 15, the same figure Part 1 reported. Same output, same count, a different
    // number of loops - which is the point of showing both.

    // ------------------------------------------------------------
    // HOW I DERIVED THIS CODE
    // ------------------------------------------------------------
    // Build it from the drawing. Six steps, the same six used for every pattern.
    //
    // STEP 1: COUNT THE ROWS IN THE DRAWING.
    //   Five lines:
    //       1
    //       1 2
    //       1 2 3
    //       1 2 3 4
    //       1 2 3 4 5
    //   FIVE ROWS. OUTER BOUND = 5  ->  `row <= 5`.
    //
    // STEP 2: COUNT THE ITEMS IN THE FIRST ROW.
    //   The top row holds ONE number. So on the first pass the inner loop must
    //   run ONCE. Already this rules out any constant inner bound above 1.
    //
    // STEP 3: COUNT THE ITEMS IN THE LAST ROW.
    //   The bottom row holds FIVE numbers. So on the last pass the inner loop
    //   must run five times.
    //
    // STEP 4: ASK HOW MANY ITEMS ARE IN ROW N.
    //       row 1 -> 1 item        row 4 -> 4 items
    //       row 2 -> 2 items       row 5 -> 5 items
    //       row 3 -> 3 items
    //   The rule: "row N contains N items". The same rule, and the same inner
    //   bound, as the star triangle in 02_increasing_triangle.cpp - because it
    //   is the same SHAPE.
    //
    //   Now the question that actually separates this pattern from that one,
    //   and it cannot be read off the loop bounds at all:
    //
    //       WHICH numbers go in row N?
    //           row 1 -> the number 1
    //           row 2 -> the numbers 1, 2
    //           row 3 -> the numbers 1, 2, 3
    //
    //   Every row STARTS AGAIN AT 1. Two facts follow from that line, and
    //   between them they are the whole of this file:
    //     (a) the accumulator must be RESET to 1 at the top of every row - that
    //         is the `n = 1;` line sitting between the two loops;
    //     (b) it must be declared where a reset can reach it from between the
    //         loops AND it can still be read after them - which is outside both.
    //
    //   A DRAWING NOTE WORTH MAKING: because each row restarts at 1, the value
    //   printed in a cell is the same as the cell's position in the row. The
    //   simplest correct code for this exact shape is therefore
    //
    //       for (row = 1; row <= 5; row++) {
    //           for (col = 1; col <= row; col++) {
    //               if (col > 1) cout << " ";
    //               cout << col;        // <-- col, no accumulator at all
    //           }
    //           cout << endl;
    //       }
    //
    //   Part 1 deliberately uses an accumulator instead, because the point of
    //   this file is WHERE an accumulator has to be declared and what that
    //   placement decides. Part 4 then shows the shape with no nested loop at
    //   all. All three are worth being able to read.
    //
    // STEP 5: DECIDE THE TWO BOUNDS.
    //   OUTER BOUND = 5 rows                    ->  `row <= 5`
    //   INNER BOUND = items in the current row  ->  `col <= row`
    //   The bounds describe the SHAPE. They say nothing whatever about which
    //   values appear, which is why Part 2 can change the values completely
    //   without touching a single bound.
    //
    // STEP 6: STATE WHAT THE INNER BOUND DEPENDS ON.
    //   THIS PROGRAM'S ANSWER: it depends on `row`, and it grows with it.
    //
    //       "the inner loop runs while the cell counter is less than or equal
    //        to the row number, so row N prints N values."
    //
    //   Compare across the folder:
    //     01_square_stars          inner bound = 5        constant
    //     02_increasing_triangle   inner bound = row      grows
    //     03_decreasing_triangle   inner bound = 5 - row  shrinks
    //     04_number_triangle       inner bound = row      grows, as here
    //
    // ------------------------------------------------------------
    // TRACE TABLE - Part 1, every execution of the inner body, all 15
    // +-------+---------+---------+---------+--------------+--------+---------------+
    // | Pass  | OUTER   | INNER   | Value   | n AFTER      | Gap    | Values in    |
    // |       | row     | col     | PRINTED | printing     | before | this row so  |
    // |       |         |         |         | (the ++ ran) |        | far          |
    // +-------+---------+---------+---------+--------------+--------+---------------+
    // |   1   |    1    |    1    |    1    |      2       |  none  |      1        |
    // |   2   |    2    |    1    |    1    |      2       |  none  |      1        |
    // |   3   |    2    |    2    |    2    |      3       |  yes   |      2        |
    // |   4   |    3    |    1    |    1    |      2       |  none  |      1        |
    // |   5   |    3    |    2    |    2    |      3       |  yes   |      2        |
    // |   6   |    3    |    3    |    3    |      4       |  yes   |      3        |
    // |   7   |    4    |    1    |    1    |      2       |  none  |      1        |
    // |   8   |    4    |    2    |    2    |      3       |  yes   |      2        |
    // |   9   |    4    |    3    |    3    |      4       |  yes   |      3        |
    // |  10   |    4    |    4    |    4    |      5       |  yes   |      4        |
    // |  11   |    5    |    1    |    1    |      2       |  none  |      1        |
    // |  12   |    5    |    2    |    2    |      3       |  yes   |      2        |
    // |  13   |    5    |    3    |    3    |      4       |  yes   |      3        |
    // |  14   |    5    |    4    |    4    |      5       |  yes   |      4        |
    // |  15   |    5    |    5    |    5    |      6       |  yes   |      5        |
    // +-------+---------+---------+---------+--------------+--------+---------------+
    //
    // THE OUTER AND INNER COLUMNS ARE BOTH REQUIRED, one row per execution of
    // the inner body - 15 rows, never 5.
    //
    // READ THE "VALUE PRINTED" COLUMN DOWN: 1, 1, 2, 1, 2, 3, 1, 2, 3, 4, 1, 2,
    // 3, 4, 5. It RESETS at the start of every group. That single column is the
    // `n = 1;` line doing its job, and it is why row 4 starts again with 1
    // rather than carrying on from 7.
    //
    // READ THE "n AFTER PRINTING" COLUMN: 2, 2, 3, 2, 3, 4, 2, ... It never
    // climbs past 6, because the accumulator is reset on every row. Compare
    // Part 2's identical-shape program, where the same column reads 2, 3, 4, 5,
    // 6, 7 and keeps going - because that copy has no reset line.
    //
    // THE "GAP BEFORE" COLUMN IS ALSO WORTH A LOOK. It says `none` on the first
    // execution of every row and `yes` on every other one. That is what
    // `if (col > 1)` is for: it is true only when this is not the first value of
    // the row, so the first value lands flush against the margin and no line
    // ever ends in a space.
    //
    // THE TOTAL NUMBER OF TIMES THE INNER BODY EXECUTES
    //   1 + 2 + 3 + 4 + 5 = 15 executions, and 15 values printed.
    //   An ADDITION, not a multiplication, because every row is a different
    //   length. And because the accumulator lives outside both loops it counts
    //   all 15 - whereas Part 3's copy, declared inside the outer loop, can only
    //   ever count the five prints of its own final row and finishes at 6.
    //
    // WHY THE ACCUMULATOR MUST BE DECLARED OUTSIDE BOTH LOOPS
    //   A variable declared inside a loop is a NEW variable on every pass,
    //   initialised to its starting value and destroyed at the end of the pass.
    //   It cannot remember anything, because it does not exist between passes.
    //
    //   Declared outside, it is created once and lives until the end of `main`,
    //   so the code can reset it at the top of each row AND read its final value
    //   after the loops. That is exactly the pair of things Part 1 needs and
    //   Part 3 cannot do - and the printed shape is identical in both, which is
    //   what makes this the most dangerous bug in the folder. The shape cannot
    //   reveal it. Only the printed total can.
    //
    // `cout << n;` VERSUS `cout << n << " ";`
    //   The same rule applies to numbers as to symbols. `cout << n << " ";`
    //   separates every value with a gap AND leaves a gap at the end of the
    //   line, because the gap belongs to the value rather than sitting between
    //   two values. Printing the gap first, guarded by `if (col > 1)`, gives the
    //   same visible result with no trailing space. A gap belongs BETWEEN two
    //   items, never after the last one.
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
    //   of one number each. Part 4 is the interesting exception: there the break
    //   goes INSIDE its single loop, because that loop's body is not an inner
    //   body - it is the whole row, and the `if` decides when the row ends.
    //
    // COMMON TRAP
    //   Believing the accumulator resets by itself because the inner loop
    //   restarts. The inner loop restarts `col`, because `int col = 1` is part of
    //   its header. It does NOT restart `n`, because `n` was declared elsewhere
    //   and the inner loop contains no instruction to reset it. Part 2 shows
    //   what an unreset accumulator produces, and Part 1 shows the line that
    //   prevents it.
    //
    //   The second trap is incrementing before printing. With `n++` above
    //   `cout << n;` the first value printed is 2, every row is shifted up by
    //   one, and the triangle ends at 16. Print first, then increment - and
    //   remember the counter's value after the loops is one MORE than the number
    //   of prints, which is why Part 1 ends at 16 while the count of prints is
    //   15.
    //
    //   The third trap is reaching for the single-loop version of Part 4 under
    //   time pressure. It is shorter and it works, but it requires holding two
    //   manually updated variables and reasoning about when a row ends. In an
    //   exam, the nested version is far easier to write correctly first time,
    //   and Part 4 is worth reading rather than imitating.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: What does the inner bound `col <= row` decide in this pattern, and what decides the printed values?  -> the bound decides the shape, the number of values per row; the accumulator `n` decides which values are printed
// Q2: What does deleting the `n = 1;` line in Part 2 do?  -> the accumulator carries its value between rows, so the numbers run on unbroken as 1, then 2 3, then 4 5 6
// Q3: Why is the bug in Part 3 invisible in the printed output?  -> a fresh accumulator starts at 1 on every pass anyway, which is the same restart the explicit line was performing
// Q4: Why must the accumulator in Part 1 be declared outside the outer loop?  -> so the same variable is visible both at the reset before the inner loop and after the loops, and so it can carry a value between rows
// Q5: How many times does the inner body run, and is the total a multiplication or an addition?  -> 15 times, by addition: 1 + 2 + 3 + 4 + 5, because each row has a different length
