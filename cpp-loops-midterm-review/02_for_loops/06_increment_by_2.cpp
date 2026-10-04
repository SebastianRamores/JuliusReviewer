/*
  ============================================================
  PROGRAM: Stepping by 2 and Doubling with i *= 2
  TOPIC: for loops - changing the update to change the step size
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - Changing only the update to make a loop skip numbers.
  - Stepping by 2 starting from an odd value and from an even value.
  - Doubling with `i *= 2`, which is NOT stepping - it multiplies.
  - The difference between a STEPPING loop and a TESTING loop.

  EXPECTED OUTPUT:
  Stepping by 2 starting at 1: 1 3 5 7 9
  Stepping by 2 starting at 2: 2 4 6 8 10
  Doubling with i *= 2        : 1 2 4 8 16 32
  Testing loop - even numbers from 1 to 10: 2 4 6 8 10
  How many even numbers were found: 5

  IMPORTANT SYNTAX:
  i += 2            -> add 2 each pass (STEP size 2)
  i *= 2            -> multiply i by 2 each pass (the value EXPLODES)
  i % 2             -> "remainder after dividing by 2" (modulo)
  i % 2 == 0        -> true exactly when i is even
  count++           -> add 1 to the counter inside the loop

  STEP-BY-STEP EXPLANATION:
  1. A loop prints 1,2,3,4,5 only because the update adds 1. Change the
     update to `i += 2` and the counter now lands on 1,3,5,7,9 - it visits
     every second number, so the count changes too. The 11 is never
     printed, because the condition `i <= 10` fails before the body runs.
  2. Starting at 1 with a step of 2 visits the ODD numbers.
     Starting at 2 with a step of 2 visits the EVEN numbers.
     The start value alone decides which of the two you get.
  3. `i *= 2` is a completely different animal: it multiplies instead of
     adding, so the numbers grow much faster - 1, 2, 4, 8, 16, 32.
     With `i <= 32` the loop happens to stop after six values.
  4. A STEPPING loop SKIPS values on purpose: it only lands on the numbers
     it cares about. A TESTING loop walks EVERY value and asks a question
     about it, printing only when the answer is yes.
  5. The last loop walks 1 to 10 one number at a time and keeps the even
     ones using `% 2 == 0`.
  ============================================================
*/

#include <iostream>
/*
  The single header this project needs. It supplies `cout` for output and
  `endl` for a newline. C++ has no printing built in, so this line has to
  be present before any use of `cout`.
*/

using namespace std;
/*
  Standard C++ keeps cout and endl inside a namespace named `std`, and the
  `::` operator means "inside", so `std::cout` reads "the cout in std".
  `using namespace std;` is the shortcut that lets us write plain `cout`.
*/

int main() {
/*
  `main` is the ENTRY POINT: the first code the operating system runs.
  `int` is the return type - a whole number handed back at the end.
  `()` means no parameters. `{ }` delimits the BODY of the function.
*/

    /*
      ============================================================
      PART A - STEPPING BY 2 FROM AN ODD START
      ============================================================
    */
    cout << "Stepping by 2 starting at 1:";
    // Label only; no newline yet, so the numbers share its row.

    for (int i = 1; i <= 10; i += 2) {
    //                         +------
        /*
          `i += 2` is a compound assignment: "add 2 to i". It is the ONLY
          difference between this loop and the basic one, yet it changes
          everything: the counter now lands on 1, 3, 5, 7, 9 and then jumps
          to 11, which fails the test.

          THE MOST IMPORTANT SENTENCE IN THIS FILE: a number is printed
          only if it PASSED the condition first. The counter reaches 11,
          the test `11 <= 10` is FALSE, and the body never runs - so 11 is
          never printed. The update is what moves i; it does not print.

          Trace: 1(T) 3(T) 5(T) 7(T) 9(T) 11(F)  -> five values printed.
        */
        cout << " " << i;
        // A space first, then the number, and no endl, so the whole
        // sequence stays on one line where it is easy to compare.
    }
    cout << endl;

    /*
      ============================================================
      PART B - STEPPING BY 2 FROM AN EVEN START
      ============================================================
    */
    cout << "Stepping by 2 starting at 2:";
    // Identical label width, so the two rows sit directly under one another.

    for (int i = 2; i <= 10; i += 2) {
        /*
          The update is IDENTICAL to part A. Only the starting value moved
          from 1 to 2, and that is enough to change the entire sequence:
          starting on an odd number with a step of 2 can only ever visit
          odd numbers, and starting on an even number visits even ones.

          This is the practical reason the start value matters: it is how
          you print the evens OR the odds without testing anything.
        */
        cout << " " << i;
    }
    cout << endl;

    /*
      ============================================================
      PART C - DOUBLING WITH `i *= 2`
      ============================================================
    */
    cout << "Doubling with i *= 2        :";
    // The label is padded so all three rows line up.

    for (int i = 1; i <= 32; i *= 2) {
    //                         +------
        /*
          `*=` means "multiply i by 2". THIS IS NOT STEPPING.
            Stepping  = the counter moves by a FIXED amount each pass, so
                        the gaps between printed numbers are all the same.
            Doubling  = the AMOUNT OF MOVEMENT GROWS, so the gaps widen:
                        +1, +1, +1...  versus  +1, +2, +4, +8, +16...

          Values: 1 (T) 2 (T) 4 (T) 8 (T) 16 (T) 32 (T) 64 (F) -> six
          values printed, then the loop ends because 64 > 32.

          The limit must be chosen with care: too small and nothing is
          printed at all, because even the first test fails.
        */
        cout << " " << i;
    }
    cout << endl;

    /*
      ============================================================
      PART D - STEPPING LOOP versus TESTING LOOP
      ============================================================
      STEP 1 - THE DEFINITIONS
        A STEPPING loop jumps straight to the values it cares about.
            for (int i = 2; i <= 10; i += 2)
        The counter never looks at 3, 5, 7 or 9 at all. It is faster and
        shorter, but it can ONLY find numbers that are a fixed distance
        apart. Multiples of 5 work; prime numbers do not.

        A TESTING loop walks every single value and asks a question.
            for (int i = 1; i <= 10; i++)  { if ( ... ) cout << i; }
        It looks at all ten numbers, so it can pick out anything at all -
        primes, squares, palindromes - but it does more work.

      STEP 2 - THE TESTING LOOP, WRITTEN OUT
    */
    cout << "Testing loop - even numbers from 1 to 10:";
    // A longer label because it explains two ideas at once.

    int count = 0;
    /*
      An ACCUMULATOR: a variable declared BEFORE the loop and updated
      inside it, so it survives from one pass to the next and can be read
      after the loop ends. `int` holds whole numbers, `= 0` starts it off.
    */

    for (int i = 1; i <= 10; i++) {
    //                    +---
        /*
          `i++` means this loop examines EVERY value from 1 to 10 - one at
          a time, ten passes, no skipping.

          `%` is the MODULO operator. `i % 2` is the REMAINDER left after
          dividing i by 2:
              1 % 2 -> 1        2 % 2 -> 0        3 % 2 -> 1
              4 % 2 -> 0        5 % 2 -> 1        6 % 2 -> 0
          A remainder of 0 means the division came out exact, which is the
          definition of an EVEN number.

          `==` is the "is exactly equal to" test. Note it is TWO equals
          signs; a single `=` is ASSIGNMENT and would change i instead of
          comparing it. That single-character slip is a classic exam mark.
        */
        if (i % 2 == 0) {
        /*
           |  | |  | |
           |  | |  | +-- 0, the remainder we want
           |  | |  +---- the number to divide by
           |  | +------- modulo
           |  +--------- i, the number being tested
           +------------ an IF: run the block only when this is TRUE
        */
            cout << " " << i;
            // Only reached on the even passes, so only the even numbers
            // reach the screen.
            count++;
            /*
              Add one to the accumulator each time a number qualifies.
              Without this, the variable would be declared and then never
              used, and the answer after the loop would always be 0.
            */
        }
    }
    cout << endl;
    // Printed once, after the loop, which is the whole point of putting
    // `count` outside the braces.

    cout << "How many even numbers were found: " << count << endl;
    /*
      `count` is still alive here because it was declared in main's body,
      not inside the loop header. Contrast this with `i`, which no longer
      exists. See 08_multiple_variables.cpp for that scope rule.
    */

    /*
      ------------------------------------------------------------
      TRACE TABLE
      ------------------------------------------------------------
      TRACE TABLE
      +-----------+------------+----------------+-------------+----------+
      | Iteration | i at start | Update i += 2  | condition    | Output   |
      |           |            |                | i <= 10 ?    |          |
      +-----------+------------+----------------+-------------+----------+
      |     1     |     1      | 1 + 2 = 3      |  true        |    1     |
      +-----------+------------+----------------+-------------+----------+
      |     2     |     3      | 3 + 2 = 5      |  true        |    3     |
      +-----------+------------+----------------+-------------+----------+
      |     3     |     5      | 5 + 2 = 7      |  true        |    5     |
      +-----------+------------+----------------+-------------+----------+
      |     4     |     7      | 7 + 2 = 9      |  true        |    7     |
      +-----------+------------+----------------+-------------+----------+
      |     5     |     9      | 9 + 2 = 11     |  true        |    9     |
      +-----------+------------+----------------+-------------+----------+
      |     6     |    11      | (not reached)  |  11<=10 FALSE|   -    |
      +-----------+------------+----------------+-------------+----------+

      Read the "Update" column carefully: it computes the NEXT value of i,
      not the one printed. The value printed is always the value at the
      start of the row, and ONLY if that row's condition says true.
      Row 6 is the proof: i reached 11, the test failed, and the Output
      column is empty. Five rows printed a number - five iterations.

      THE 10-SECOND EXAM METHOD (counting a stepping loop)
        count = (limit - start) / step + 1
        Check part A: (10 - 1) / 2 + 1 = 4 + 1 = 5. Five iterations - and
        the program printed exactly five numbers. The formula works here
        because the division comes out exact. When it does NOT come out
        exact, do not trust the formula: write the sequence out on paper
        and count the entries instead. Trust the paper, not the arithmetic.

      THE COMMON TRAP IN THIS FILE
        Forgetting to change the update, and expecting the loop to skip by
        itself. A loop with `i++` ALWAYS walks through every value. To
        visit only some of them you must either step (`i += 2`) or test
        (`if (i % 2 == 0)`) - and you must never try to do both at once,
        because stepping already guarantees the test is unnecessary.
    */

    return 0;
    // Ends the program and hands 0 (success) back to the operating system.
    // Code after this line would never run.
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: What does `for (int i = 1; i <= 10; i += 2)` print?             -> 1 3 5 7 9  (five values)
  Q2: Why is 11 not printed, even though the counter reached it?      -> the condition `i <= 10` was tested first and failed, so the body never ran for that value
  Q3: What does `for (int i = 2; i <= 10; i += 2)` print?             -> 2 4 6 8 10  (the even numbers)
  Q4: Which single change makes a loop print only odd numbers?        -> start at 1 with a step of 2
  Q5: What does `for (int i = 1; i <= 32; i *= 2)` print?             -> 1 2 4 8 16 32  (six values)
  Q6: Why is `i *= 2` NOT a stepping loop?                            -> the step size grows instead of staying constant, so the gaps widen (1, 2, 4, 8...)
  Q7: What is the difference between a stepping loop and a testing loop? -> a stepping loop jumps only to the values it wants; a testing loop visits every value and asks a question about each
  Q8: What does `i % 2 == 0` test for?                                -> true exactly when i is an even number
  ============================================================
*/
