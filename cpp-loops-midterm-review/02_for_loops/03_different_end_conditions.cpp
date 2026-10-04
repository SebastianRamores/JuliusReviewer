/*
  ============================================================
  PROGRAM: Different End Conditions in a for Loop
  TOPIC: for loops - the condition part and the four comparison signs
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - All four comparison operators: < , <= , > , >= .
  - The difference between `i < 10` and `i <= 10`, with iteration counts.
  - Why the direction of the counter decides which operator is sensible.
  - What happens when the condition can never become true (zero output).

  EXPECTED OUTPUT:
  Loop with i < 5  : 1 2 3 4
  Loop with i <= 5 : 1 2 3 4 5
  Loop with i > 5  : 10 9 8 7 6
  Loop with i >= 5 : 10 9 8 7 6 5
  Loop with i > 10 (counter goes UP): (nothing printed)

  IMPORTANT SYNTAX:
  i < 5    -> true when i is 1,2,3,4 only          (5 is EXCLUDED)
  i <= 5   -> true when i is 1,2,3,4,5            (5 is INCLUDED)
  i > 5    -> true when i is 10,9,8,7,6           (5 is EXCLUDED)
  i >= 5   -> true when i is 10,9,8,7,6,5         (5 is INCLUDED)
  i++      -> add 1 (counter goes UP, so use < or <=)
  i--      -> subtract 1 (counter goes DOWN, so use > or >=)
  cout << " " << i;  -> print a space, then i, with NO newline yet

  STEP-BY-STEP EXPLANATION:
  1. The first two loops count UP from 1 and stop at the same limit, but
     use a different sign. `<` stops one value early; `<=` includes the
     limit itself.
  2. The last value printed by `i < 5` is 4; the last value printed by
     `i <= 5` is 5. That single extra number IS the whole difference.
  3. The third and fourth loops count DOWN from 10, so the comparison has
     to be flipped: `>` and `>=` are the sensible signs for a decreasing
     counter. (`i < 5` on a decreasing counter never becomes true again,
     so the loop would run forever - see the warning at the bottom.)
  4. The fifth loop tests `i > 10` while the counter is going UP from 1.
     The very first test fails, so the body never runs and nothing at all
     is printed. A loop may legally run ZERO times.
  ============================================================
*/

#include <iostream>
/*
  The single include for this project. It gives us `cout` to write to the
  screen and `endl` to start a new line. C++ ships with no built-in
  printing, so this line must come before any use of `cout`.
*/

using namespace std;
/*
  Standard C++ groups cout, endl and cin inside a namespace named `std`
  (short for "standard"). A namespace is a labelled box of names, and the
  `::` symbol means "inside that box", so `std::cout` is "the cout in std".
  This line lets us omit `std::` everywhere and simply write `cout`.
*/

int main() {
/*
  `main` is the ENTRY POINT of the program. `int` is the return type - main
  hands a whole number back to the operating system when it finishes.
  `()` means no inputs are passed in. The `{ }` braces mark the BODY, the
  list of instructions that run from top to bottom.
*/

    /*
      ============================================================
      PART A - COUNTING UP:  `<`  versus  `<=`
      ============================================================
    */
    cout << "Loop with i < 5  :";
    // A label with no newline yet, so the numbers appear on the same line.

    for (int i = 1; i < 5; i++) {
    /*
                             |    |
                             |    +-- UPDATE: i grows by 1
                             +------- CONDITION: < means "strictly smaller"
    */
        /*
          `<` is "strictly less than", so 5 is NOT allowed. The values that
          pass the test are 1, 2, 3, 4 - four iterations, four numbers.

          Note the comparison is made BEFORE the body runs, using the value
          i has at that moment. That is why the last value printed (4) is
          always one smaller than the number written after `<`.
        */
        cout << " " << i;
        /*
          Print a SPACE first, then the number. There is no `endl` inside
          this loop on purpose: without it all the numbers would land on
          separate lines and we could not see the sequence in one row.
        */
    }
    cout << endl;
    // The newline is written OUTSIDE the loop, so it happens exactly once,
    // after the loop has finished.

    cout << "Loop with i <= 5 :";
    // Same label, one character wider, so the two rows line up in the
    // terminal and the extra number is easy to spot.

    for (int i = 1; i <= 5; i++) {
    //                       |
    //                       +-- the difference: an extra `=`
        /*
          `<=` means "less than OR equal to". The extra `=` ADDS the limit
          itself to the allowed set: 1, 2, 3, 4, 5 - five iterations.

          THE KEY EXAM IDEA, put plainly:
              for (int i = 1; i < 10;  i++)   -> 9 values: 1 2 3 4 5 6 7 8 9
              for (int i = 1; i <= 10; i++)   -> 10 values: 1 2 ... 9 10
          The `=` adds exactly ONE value to the output, and adds exactly
          ONE to the iteration count.
        */
        cout << " " << i;
    }
    cout << endl;

    /*
      ============================================================
      PART B - COUNTING DOWN:  `>`  versus  `>=`
      ============================================================
    */
    cout << "Loop with i > 5  :";
    // The counter now shrinks, so the direction of the comparison flips.

    for (int i = 10; i > 5; i--) {
    /*
                           |     |
                           |     +-- UPDATE: i-- means "subtract 1"
                           +-------- CONDITION: > means "strictly bigger"
    */
        /*
          `i--` is the DECREMENT operator: i = i - 1. Because i falls, the
          test has to be `>`, i.e. "is i still bigger than 5?".
          `>` is strict, so 5 itself is refused and the values are
          10, 9, 8, 7, 6 - five iterations.
        */
        cout << " " << i;
    }
    cout << endl;

    cout << "Loop with i >= 5 :";
    // Identical label width, so this row sits directly under the previous
    // one and the single extra number stands out.

    for (int i = 10; i >= 5; i--) {
        // The `=` lets 5 through this time, so the values are
        // 10, 9, 8, 7, 6, 5 - six iterations, one more than the row above.
        cout << " " << i;
    }
    cout << endl;

    /*
      ============================================================
      PART C - A LOOP THAT RUNS ZERO TIMES
      ============================================================
    */
    cout << "Loop with i > 10 (counter goes UP):";
    /*
      The counter climbs from 1 to 6 to 11 to ... so `i > 10` will only be
      true from 11 upwards. But the first test happens when i is 1, and
      1 > 10 is FALSE, so the loop is skipped entirely.
    */

    for (int i = 1; i > 10; i++) {
        /*
          *** THIS BODY IS NEVER EXECUTED. It is dead code at runtime. ***
          A loop is allowed to run zero times - the condition is checked
          BEFORE the first pass, not after, so a condition that starts out
          false means the body never runs at all.
          The same loop is "correct" but produces no output, which is why
          the answer is printed by hand below. Loops do not warn you; they
          simply do nothing. Always trace the FIRST test.
        */
        cout << " " << i;
    }
    cout << " (nothing printed)";
    // A message in plain text so the empty line is not mistaken for a bug
    // in the output.
    cout << endl;

    /*
      ------------------------------------------------------------
      TRACE TABLE
      ------------------------------------------------------------
      TRACE TABLE
      +-----------+------------+----------------+------------+-----------+
      | Iteration | i at start | i < 5 ?       | Output     | i <= 5 ? |
      +-----------+------------+----------------+------------+-----------+
      |     1     |     1      | true          |    1       | true     |
      +-----------+------------+----------------+------------+-----------+
      |     2     |     2      | true          |    2       | true     |
      +-----------+------------+----------------+------------+-----------+
      |     3     |     3      | true          |    3       | true     |
      +-----------+------------+----------------+------------+-----------+
      |     4     |     4      | true          |    4       | true     |
      +-----------+------------+----------------+------------+-----------+
      |     5     |     5      | FALSE -> stop |    -       | true     |
      +-----------+------------+----------------+------------+-----------+
      |     6     |     6      |    -          |    -       | FALSE -> stop |
      +-----------+------------+----------------+------------+-----------+

      `i < 5`  -> 4 iterations, last printed value 4
      `i <= 5` -> 5 iterations, last printed value 5

      THE 10-SECOND EXAM METHOD
        1. Write the comparison symbol as WORDS.
           <  -> "smaller than"      -> the limit is excluded
           <= -> "smaller or equal"  -> the limit is included
        2. Ask: does the limit itself pass the test?
        3. If YES, add one extra to your iteration count.
        That single question answers most condition marks in the exam.

      THE COMMON TRAP IN THIS FILE
        Mixing the direction of travel with the direction of the symbol.
        A counter that goes UP needs `<` or `<=`. A counter that goes DOWN
        needs `>` or `>=`. Pairing them wrongly is the classic infinite
        loop: `for (int i = 10; i < 5; i--)` can never satisfy the test, so
        it would never stop. That mistake is demonstrated in
        ../12_common_mistakes/05_infinite_loop.cpp.
    */

    return 0;
    // Finishes the program and hands 0 (success) to the operating system.
    // Anything written after this line would never be reached.
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: How many values does `for (int i = 1; i < 5; i++)` print?   -> 4  (1 2 3 4)
  Q2: How many values does `for (int i = 1; i <= 5; i++)` print?  -> 5  (1 2 3 4 5)
  Q3: What is printed by `for (int i = 10; i >= 5; i--)`?          -> 10 9 8 7 6 5
  Q4: Why does `for (int i = 1; i > 10; i++)` print nothing?       -> the condition is false on the very first test, so the body runs zero times
  Q5: How many values does `for (int i = 1; i <= 10; i++)` print?  -> 10
  Q6: What is the danger in `for (int i = 10; i < 5; i--)`?        -> infinite loop: the counter shrinks while the test demands a large value, so the test never fails
  ============================================================
*/
