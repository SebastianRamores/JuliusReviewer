// ============================================================
// PROGRAM: Pattern 8 - A Centred Pyramid of Stars and of Numbers
// TOPIC: two loops per row, and a counter that runs across every row
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - How to print a CENTRED pyramid:
//
//       *
//      * *
//     * * *
//    * * * *
//   * * * * *
//
// - That centring needs `6 - row` spaces, not `5 - row`, and why the extra one
//   is what makes row 1 narrower than row 2 by exactly two.
// - That the number pyramid - `1`, `2 3`, `4 5 6`, `7 8 9 10`, `11..15` - is
//   the same loops with an accumulator that is NEVER reset.
// - That "same shape, different values" is a one-token change, and that the
//   difference between the two number patterns in this folder is a single reset.
//

// EXPECTED OUTPUT:
// === Part 1: a centred pyramid of stars ===
//      *
//     * *
//    * * *
//   * * * *
//  * * * * *
// row 1 had 5 spaces and 1 star; row 5 had 1 space and 5 stars
// the whole frame is 5 lead columns + 4 gap columns + 5 star columns = 14
// measured on screen, each row is 6, 7, 8, 9 and 10 characters
//
// === Part 2: the number pyramid, with an accumulator that never resets ===
//      1
//     2 3
//    4 5 6
//   7 8 9 10
//  11 12 13 14 15
// the numbers ran on unbroken from 1 to 15 because nothing ever reset them
// total numbers printed = 15
//
// === Part 3: the SAME code with the accumulator reset each row ===
//      1
//     1 2
//    1 2 3
//   1 2 3 4
//  1 2 3 4 5
// one line of code changed, and the numbers restart on every row

// IMPORTANT SYNTAX:
// for (int row = 1; row <= 5; row++)          -> the ROW loop
//     for (int s = 1; s <= 6 - row; s++) {     -> the SPACE loop: 6 - row spaces
//         cout << " ";
//     }
//     for (int col = 1; col <= row; col++) {  -> the STAR or NUMBER loop
//         if (col > 1) { cout << " "; }
//         cout << value;                        // value is `*`, or a counter
//     }
//     cout << endl;                             -> ONE break, after both inner loops
//
// WHY THE SPACE BOUND IS READ OFF THE DRAWING, NOT DERIVED FROM A RULE
//   There is no theory that tells you the lead is 6 rather than 5. You COUNT
//   the spaces in front of the first row of the drawing and write the bound
//   that produces that count - here 5 spaces on row 1, so `s <= 6 - row`.
//
//   What the bound expresses is the one thing that IS true of every row of a
//   centred shape: the lead FALLS BY ONE per row. So read the first row, and
//   everything after it follows. `5 - row` would draw the very same pyramid one
//   column to the left, which is why counting the drawing rather than
//   theorising is the only reliable method.
//
// STEP-BY-STEP EXPLANATION:
// 1. Five rows, so the outer loop runs 1 to 5.
// 2. Row N has N items, so the item loop's bound is `row` - unchanged.
// 3. Row 1 needs the MOST indentation and row 5 the least, so the space count
//    falls as the row number rises: `6 - row`.
// 4. The number pyramid reuses both loops and changes only the printed text.
// 5. The numbers keep running across rows because the accumulator is declared
//    outside both loops and never reset - that is the entire mechanism.
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

    cout << "=== Part 1: a centred pyramid of stars ===" << endl;

    for (int row = 1; row <= 5; row++) {
        // THE OUTER LOOP COUNTS THE ROWS: 1, 2, 3, 4, 5.

        for (int s = 1; s <= 6 - row; s++) {
            // THE SPACE LOOP - ONE SPACE PER PASS, AS IN
            // 07_right_aligned_triangle.cpp.
            //
            // THE BOUND IS `6 - row`: ONE LESS THAN THE TOTAL WIDTH.
            //
            //     row 1  ->  s: 1 2 3 4 5  ->  5 spaces
            //     row 2  ->  s: 1 2 3 4    ->  4 spaces
            //     row 3  ->  s: 1 2 3      ->  3 spaces
            //     row 4  ->  s: 1 2        ->  2 spaces
            //     row 5  ->  s: 1          ->  1 space
            //
            // THE ONE FACT THAT MATTERS: the lead FALLS BY ONE ON EVERY ROW.
            // That is true of every centred shape, and it is why writing the
            // bound as `total - row` works. What decides the total is nothing
            // more than counting the spaces in front of the FIRST row of the
            // drawing - 5 here, so the bound is `6 - row`.
            //
            // WHY BOTH EDGES MOVE, WHICH IS WHAT MAKES IT CENTRED. The lead
            // falls by one, so the first star of each row sits one place further
            // LEFT than the row above. The star loop adds one star, so the last
            // star sits one place further RIGHT. Left edge in by one, right edge
            // out by one: both edges slope, and the shape is symmetrical about
            // its middle. A right-aligned triangle has only ONE sloping edge
            // and a straight one, which is why its lead count and a pyramid's
            // differ.
            //
            // THE CHECK, AND IT IS WORTH DOING ONCE: measure the rows on
            // screen. They come out 6, 7, 8, 9 and 10 characters - widening by
            // exactly ONE per row, with row N being `5 + N` wide. Any set of
            // widths that does not rise by one per row means the spacing is
            // wrong.
            cout << " ";
        }

        for (int col = 1; col <= row; col++) {
            // THE STAR LOOP IS UNCHANGED: `col <= row`, so row N has N stars.
            if (col > 1) {
                cout << " ";
            }
            cout << "*";
        }

        cout << endl;
        // ONE BREAK, AFTER BOTH INNER LOOPS. Between them, every row's stars
        // would land on the line below its own indentation.
    }

    cout << "row 1 had 5 spaces and 1 star; row 5 had 1 space and 5 stars" << endl;
    cout << "the whole frame is 5 lead columns + 4 gap columns + 5 star columns = "
         << (5 + 4 + 5) << endl;
    cout << "measured on screen, each row is 6, 7, 8, 9 and 10 characters" << endl;
    // Measuring the widths is the best single check on a centred shape: row N is
    // 5 + N characters, so every row must be exactly ONE wider than the row
    // above. If two rows come out the same width, the spacing is off by one and
    // the shape is not centred.

    cout << endl;
    cout << "=== Part 2: the number pyramid, with an accumulator that never resets ==="
         << endl;

    // THE SAME TWO LOOPS. Only the printed text changes.
    //
    // THE ACCUMULATOR IS DECLARED HERE, OUTSIDE BOTH LOOPS, AND IS NEVER RESET.
    // That single fact is what makes the numbers run on unbroken across every
    // row, so row 1 prints 1, row 2 prints 2 and 3, row 3 prints 4, 5 and 6,
    // and the last row prints 11 to 15.
    //
    // Compare with 04_number_triangle.cpp, which declares its accumulator in
    // the same place and then resets it at the top of every row. The two files
    // differ in ONE line of code, and that line is the difference between
    // "1, then 2 3, then 4 5 6" and "1, then 1 2, then 1 2 3".
    int n = 1;

    for (int row = 1; row <= 5; row++) {
        for (int s = 1; s <= 6 - row; s++) {
            cout << " ";
        }
        for (int col = 1; col <= row; col++) {
            if (col > 1) {
                cout << " ";
            }
            cout << n;
            // THE PRINTED VALUE IS THE ACCUMULATOR, NOT `col`.
            //
            // That is the whole difference from Part 1, and it is worth being
            // able to say why `col` cannot be used instead: `col` restarts at 1
            // on every row, so printing it would give 1 on row 2 and 1 2 on row
            // 3 - which is 04_number_triangle.cpp's pattern, not this one. Only
            // a value declared outside the loops can know what has already been
            // printed.
            n++;
            // AFTER PRINTING, NEVER BEFORE. With `n++` first, the first value
            // printed would be 2 and the whole pyramid would be shifted up by
            // one, ending at 16.
        }
        cout << endl;
    }

    cout << "the numbers ran on unbroken from 1 to 15 because nothing ever reset them"
         << endl;
    cout << "total numbers printed = " << (n - 1) << endl;
    // 15, one less than `n` because the final `n++` runs after the last print.
    // An ADDITION rather than a multiplication: the rows hold 1, 2, 3, 4 and 5
    // values, so 1 + 2 + 3 + 4 + 5 = 15.

    cout << endl;
    cout << "=== Part 3: the SAME code with the accumulator reset each row ===" << endl;

    // ONE LINE ADDED, AND THE OUTPUT CHANGES COMPLETELY. Nothing else about the
    // loops is different: same outer bound, same space bound, same item bound.
    int restart = 1;

    for (int row = 1; row <= 5; row++) {
        restart = 1;
        // THE ONLY DIFFERENCE FROM PART 2. This statement sits BETWEEN the two
        // loops, so it runs once per row, before the numbers are printed.
        //
        // It can go there only because `restart` was declared above the outer
        // loop. A variable declared inside a loop is rebuilt at its initial
        // value on every pass and this statement would be redundant - which is
        // exactly the trap documented in 04_number_triangle.cpp.
        for (int s = 1; s <= 6 - row; s++) {
            cout << " ";
        }
        for (int col = 1; col <= row; col++) {
            if (col > 1) {
                cout << " ";
            }
            cout << restart;
            restart++;
        }
        cout << endl;
    }

    cout << "one line of code changed, and the numbers restart on every row" << endl;
    // The shape is IDENTICAL to Part 2 - same rows, same widths, same alignment.
    // Only the values differ. This is the clearest demonstration in the folder
    // that a pattern's SHAPE and its CONTENTS are decided by different parts of
    // the code, and that changing one leaves the other untouched.

    // ------------------------------------------------------------
    // HOW I DERIVED THIS CODE - THE STAR PYRAMID (Part 1)
    // ------------------------------------------------------------
    // Build it from the drawing. The same six steps, plus one extra measurement
    // that only a centred shape needs.
    //
    // STEP 1: COUNT THE ROWS IN THE DRAWING.
    //   Five lines. FIVE ROWS. OUTER BOUND = 5  ->  `row <= 5`.
    //
    // STEP 2: COUNT THE ITEMS IN THE FIRST ROW.
    //   The top row holds ONE star. So the item loop must run once on row 1.
    //
    // STEP 3: COUNT THE ITEMS IN THE LAST ROW.
    //   The bottom row holds FIVE stars. So the item loop must run five times.
    //
    // STEP 4: ASK HOW MANY ITEMS ARE IN ROW N.
    //       row 1 -> 1 star        row 4 -> 4 stars
    //       row 2 -> 2 stars       row 5 -> 5 stars
    //       row 3 -> 3 stars
    //   "row N contains N items"  ->  the item loop is `col <= row`, exactly as
    //   in 02_increasing_triangle.cpp and 07_right_aligned_triangle.cpp.
    //
    //   THE EXTRA QUESTION, AND IT IS SPECIFIC TO A CENTRED SHAPE:
    //
    //       HOW MANY SPACES COME BEFORE THE FIRST STAR OF ROW N?
    //           row 1 -> 5 spaces
    //           row 2 -> 4 spaces
    //           row 3 -> 3 spaces
    //           row 4 -> 2 spaces
    //           row 5 -> 1 space
    //
    //   THE ONLY RULE HERE IS THAT THE COUNT FALLS BY ONE PER ROW: 5, 4, 3, 2,
    //   1. Anything that shrinks going down the drawing is written as
    //   `total - row`, which is the same idea as 03_decreasing_triangle.cpp and
    //   07_right_aligned_triangle.cpp.
    //
    //   SO READ THE FIRST ROW AND WORK OUT THE TOTAL. The drawing shows 5 spaces
    //   on row 1, and `s <= total - row` gives `total - 1` spaces on row 1, so
    //   the total is 6 and the bound is `s <= 6 - row`. There is no formula
    //   that predicts the 5 - it is simply counted, because the drawing is what
    //   defines the shape.
    //
    //   WHY THE TOTAL IS 6 AND NOT 5, WHICH IS THE USUAL QUESTION:
    //   `5 - row` gives 4, 3, 2, 1, 0. That is not a WRONG shape - it is this
    //   exact pyramid drawn one column further left, with no leading space at
    //   all on the bottom row. Both are centred; they differ only in where the
    //   block sits. Since the drawing decides the position, the drawing decides
    //   the 6. Writing `5 - row` here produces a shape that looks almost right,
    //   which is exactly why it is worth counting rather than assuming.
    //
    //   THE SYMMETRY, WHICH IS WHAT "CENTRED" ACTUALLY MEANS: the lead falls by
    //   one, so the first star moves one place LEFT each row; the star loop adds
    //   a star, so the last star moves one place RIGHT each row. Both edges
    //   slope. A right-aligned triangle has one sloping edge and one straight
    //   edge, which is the whole visual difference between the two shapes.
    //
    // STEP 5: DECIDE THE THREE BOUNDS.
    //   OUTER BOUND = 5 rows                    ->  `row <= 5`
    //   SPACE BOUND = 6 - row spaces            ->  `s <= 6 - row`
    //   ITEM BOUND  = N items in row N          ->  `col <= row`
    //   THREE BOUNDS for THREE directions in the drawing: down, left, right.
    //
    // STEP 6: STATE WHAT EACH INNER BOUND DEPENDS ON.
    //   THE SPACE LOOP: depends on `row`, and SHRINKS - bound `6 - row`.
    //   THE ITEM LOOP: depends on `row`, and GROWS - bound `row`.
    //
    //       "before each row's stars, a loop prints one space while its counter
    //        runs up to 6 minus the row number, giving row N a lead of 6 - N
    //        spaces; then a second loop prints N items while its counter runs up
    //        to N itself."
    //
    //   MEASURE THE RESULT: the rows come out 6, 8, 10, 12 and 14 characters
    //   wide. A centred shape's rows always widen by exactly two, and that is
    //   the cheapest possible test that the shape is centred rather than merely
    //   shifted.
    //
    // ------------------------------------------------------------
    // HOW I DERIVED THIS CODE - THE NUMBER PYRAMID (Part 2)
    // ------------------------------------------------------------
    // The SAME six steps, because the SHAPE is identical. Only the last two
    // steps ask different questions.
    //
    // STEP 1: COUNT THE ROWS IN THE DRAWING.
    //   Five lines:
    //       1
    //       2 3
    //       4 5 6
    //       7 8 9 10
    //       11 12 13 14 15
    //   FIVE ROWS. OUTER BOUND = 5  ->  `row <= 5`.
    //
    // STEP 2: COUNT THE ITEMS IN THE FIRST ROW.
    //   The top row holds ONE value. So the item loop must run once on row 1.
    //
    // STEP 3: COUNT THE ITEMS IN THE LAST ROW.
    //   The bottom row holds FIVE values - note they are DOUBLE-DIGIT numbers,
    //   which makes row 5 wider than the star pyramid's. It is still five
    //   values, so the item loop still runs five times.
    //
    // STEP 4: ASK HOW MANY ITEMS ARE IN ROW N - AND WHICH ONES.
    //   THE COUNT IS THE SAME AS PART 1:
    //       row 1 -> 1 item        row 4 -> 4 items
    //       row 2 -> 2 items       row 5 -> 5 items
    //       row 3 -> 3 items
    //   So the item bound is `col <= row` again. Nothing changes there.
    //
    //   THE VALUES ARE WHERE THIS PATTERN DIFFERS, AND THE DRAWING SAYS TWO
    //   THINGS ABOUT THEM:
    //
    //       (a) THE VALUES KEEP RUNNING ACROSS ROWS.
    //           Row 1 ends at 1. Row 2 STARTS at 2, not at 1. Row 3 starts at
    //           4, not at 1. Every row begins where the row above stopped, and
    //           the whole shape is the sequence 1 to 15 unbroken.
    //
    //       THIS IS THE WHOLE MECHANISM, AND IT IS ONE VARIABLE.
    //       An accumulator declared before both loops and never reset keeps its
    //       value from one row into the next, so `cout << n; n++;` naturally
    //       produces 1 / 2 3 / 4 5 6 without anybody deciding what row 2
    //       should start at.
    //
    //       (b) THE SPACES ARE THE SAME AS PART 1: `6 - row`.
    //           Reading the drawing, row 1 is indented furthest and row 5 least,
    //           so the lead still falls as the row number rises.
    //
    //   NOTICE WHAT IS NOT NEEDED: no arithmetic such as `n + row` or a look-up
    //   of the row's starting number. Because the accumulator simply carries
    //   its value forward, the "where does this row start" question never has to
    //   be answered at all. That is the reward for declaring it outside the
    //   loops.
    //
    // STEP 5: DECIDE THE THREE BOUNDS.
    //   OUTER BOUND = 5 rows             ->  `row <= 5`
    //   SPACE BOUND = 6 - row spaces     ->  `s <= 6 - row`
    //   ITEM BOUND  = N items in row N   ->  `col <= row`
    //   IDENTICAL TO PART 1. Not a coincidence: same shape, different contents.
    //
    // STEP 6: STATE WHAT EACH INNER BOUND DEPENDS ON.
    //   THE SPACE LOOP: depends on `row`, SHRINKS - bound `6 - row`.
    //   THE ITEM LOOP: depends on `row`, GROWS - bound `row`.
    //   PLUS THE THIRD FACTOR, WHICH IS NOT A BOUND AT ALL:
    //       the VALUE printed comes from an accumulator declared OUTSIDE both
    //       loops and never reset, so it runs continuously from 1 to 15.
    //
    //       "the item loop prints the current value of a counter that is
    //        declared before the outer loop and increased after every print, so
    //        because nothing resets it the values run on unbroken from row to
    //        row - row N ends on value N and row N + 1 begins on value N + 1."
    //
    //   THAT LAST CLAUSE IS WORTH CHECKING AGAINST THE OUTPUT: row 1 ends on 1,
    //   row 2 begins on 2. Row 2 ends on 3, row 3 begins on 4. Row 3 ends on 6,
    //   row 4 begins on 7. The ends are 1, 3, 6, 10, 15 and each new row starts
    //   one higher - the TRIANGULAR NUMBERS again, appearing as a by-product
    //   rather than being written down anywhere.
    //
    // ------------------------------------------------------------
    // TRACE TABLE - Part 2, every execution of the item loop
    // +-------+---------+------------+-----------+---------+-----------------+-------------+
    // | Pass  | OUTER   | SPACE LOOP | Spaces    | ITEM    | Value printed   | n after     |
    // |       | row     | s takes    | printed   | col     |                 | the n++     |
    // +-------+---------+------------+-----------+---------+-----------------+-------------+
    // |   1   |    1    | 1 2 3 4 5  |     5     |    1    |       1         |      2      |
    // |   2   |    2    | 1 2 3 4    |     4     |    1    |       2         |      3      |
    // |   3   |    2    | 1 2 3 4    |     4     |    2    |       3         |      4      |
    // |   4   |    3    | 1 2 3      |     3     |    1    |       4         |      5      |
    // |   5   |    3    | 1 2 3      |     3     |    2    |       5         |      6      |
    // |   6   |    3    | 1 2 3      |     3     |    3    |       6         |      7      |
    // |   7   |    4    | 1 2        |     2     |    1    |       7         |      8      |
    // |   8   |    4    | 1 2        |     2     |    2    |       8         |      9      |
    // |   9   |    4    | 1 2        |     2     |    3    |       9         |     10      |
    // |  10   |    4    | 1 2        |     2     |    4    |      10         |     11      |
    // |  11   |    5    | 1          |     1     |    1    |      11         |     12      |
    // |  12   |    5    | 1          |     1     |    2    |      12         |     13      |
    // |  13   |    5    | 1          |     1     |    3    |      13         |     14      |
    // |  14   |    5    | 1          |     1     |    4    |      14         |     15      |
    // |  15   |    5    | 1          |     1     |    5    |      15         |     16      |
    // +-------+---------+------------+-----------+---------+-----------------+-------------+
    //
    // THREE COLUMNS OF COUNTERS ARE NEEDED, NOT TWO. This program has a space
    // loop sitting between the outer loop and the item loop, so a two-column
    // nested-loop table would leave out the mechanism that centres the shape.
    // Omitting the SPACE LOOP column is how a right-aligned triangle quietly
    // becomes a left-aligned one without the trace noticing anything odd.
    //
    // READ THE THREE COUNTER COLUMNS TOGETHER, AND THEY TELL THE WHOLE STORY:
    //
    //     SPACE LOOP  5 5 5 4 4 4 3 3 3 3 2 2 2 2 1  -> falls, value 6 - row
    //     ITEM  LOOP  1, then 1 2, then 1 2 3, ...    -> resets, value row
    //     VALUES       1 2 3 4 5 6 7 8 9 ...          -> NEVER resets
    //
    // The spaces fall, the item counter resets, and the values do neither. All
    // three behaviours are visible in the columns, and each one traces back to a
    // single decision in the source: a bound of `6 - row`, a header of
    // `int col = 1`, and a declaration placed above the outer loop with no
    // reset between the loops.
    //
    // READ THE "n AFTER" COLUMN: 2, 3, 4, 5, ... 16. It never drops, which is
    // the observable proof that nothing resets the accumulator. In Part 3 the
    // equivalent column would read 2, 2, 3, 2, 3, 4, 2, 3, 4, 5, 2 - dropping
    // back to 2 at the start of every row.
    //
    // THE TOTAL NUMBER OF TIMES THE ITEM LOOP BODY EXECUTES
    //   1 + 2 + 3 + 4 + 5 = 15 executions, and 15 values printed.
    //   An ADDITION, not a multiplication, because every row is a different
    //   length. The space loop adds 5 + 4 + 3 + 2 + 1 = 15 more characters, and
    //   the gaps between values add 0 + 1 + 2 + 3 + 4 = 10, for a grand total of
    //   40 characters - worth adding up once, because a mismatch points straight
    //   at whichever loop is wrong.
    //
    // WHY `6 - row` AND NOT `5 - row` - THE FULL ARGUMENT
    //   A right-aligned triangle of N stars has a widest row of `2N - 1`
    //   characters. For N = 5 that is 9. A right-aligned triangle puts all 9 at
    //   the far right, so its leads are 0, 1, 2, 3, 4 - which is `5 - row`.
    //
    //   The difference between the two shapes is that a centred pyramid is
    //   SYMMETRIC: both its left edge and its right edge slope inward. Here the
    //   lead falls by one each row, so the first star moves one place LEFT, and
    //   the star loop adds one star, so the last star moves one place RIGHT. A
    //   right-aligned triangle has one sloping edge and one dead-straight edge,
    //   because its lead RISES as its stars grow and pushes everything right.
    //
    //   The number 6 itself is not derived from any theory - it is COUNTED from
    //   the drawing. `5 - row` would give 4, 3, 2, 1, 0 leading spaces, which is
    //   this same pyramid shifted one column to the left with nothing before the
    //   bottom row. It is not a wrong shape, just the wrong one for this
    //   drawing, which is why the count has to come from the picture.
    //
    //   The cheap test is to measure the rows: they must come out 6, 7, 8, 9, 10
    //   characters, each exactly one wider than the row above. Anything else
    //   means the lead is off by one somewhere.
    //
    // `cout << "*";` VERSUS `cout << "* ";`
    //   Not about the stars here but about the same rule applied to spaces and
    //   gaps. Printing `" "` after every item would leave a space at the end of
    //   every row, and here it would ALSO break the centring, because a trailing
    //   space adds one to the row's visible width. Printing the gap BEFORE each
    //   item, guarded by `if (col > 1)`, keeps the widths exactly as intended.
    //   THE RULE: a gap belongs BETWEEN two items, never after the last one.
    //
    // WHY `endl` GOES AFTER BOTH INNER LOOPS
    //   A row contains spaces AND items, so it is finished only when both inner
    //   loops have finished. The break belongs after the item loop:
    //
    //       for (row ...) {
    //           for (s ...)   { cout << " "; }    // the lead
    //           for (col ...) { ... items ... }   // the row's contents
    //           cout << endl;                      // <-- row complete
    //       }
    //
    //   BETWEEN the two inner loops it would end the line after the spaces, so
    //   every row's items would appear on the line BELOW its own indentation -
    //   a staircase of spaces with a lone item under each. That is the mistake a
    //   three-loop pattern invites, and it is worth checking first when a centred
    //   shape comes out wrong.
    //
    // COMMON TRAP
    //   Copying `5 - row` from 07_right_aligned_triangle.cpp, because the star
    //   loop really is identical and the pattern really does look similar. The
    //   shape then comes out as a right-aligned triangle with one space too few
    //   on every row - still a triangle, so it looks nearly right, but visibly
    //   not centred. Measuring the row widths catches it at once.
    //
    //   The second trap is resetting the accumulator by reflex. The numbers in
    //   this pyramid run ON across the rows - 1 / 2 3 / 4 5 6 - and a `restart =
    //   1;` line between the loops silently turns it into 04_number_triangle's
    //   pattern. Part 3 exists so that the difference is visible side by side,
    //   and the drawing decides which one is correct: read whether row 2 starts
    //   at 1 or at 2.
    //
    //   The third trap is expecting `col` to supply the values. It restarts at 1
    //   in every row and cannot know what came before, so printing it gives a
    //   restarting triangle. Only a variable declared outside both loops can
    //   carry a value between them.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: What is the space loop's bound in this pyramid, and how was the 6 arrived at?  -> `s <= 6 - row`; the drawing shows 5 leading spaces on row 1, and `total - row` gives `total - 1` there, so the total is 6
// Q2: How many leading spaces does row N print, and how does that change as the rows go down?  -> 6 - N spaces, so row 1 has 5 and the count falls by one on every row
// Q3: Why can the inner loop not print the numbers in Part 2?  -> because `col` restarts at 1 on every row and so cannot know which numbers have already been printed
// Q4: What does adding `restart = 1;` between the loops do to Part 2?  -> it resets the accumulator at the top of every row, so the numbers restart at 1 instead of running on unbroken from 1 to 15
// Q5: What are the three bounds in this program, and what does each one decide?  -> `row <= 5` decides how many rows, `s <= 6 - row` decides the leading indentation, and `col <= row` decides how many items each row holds
