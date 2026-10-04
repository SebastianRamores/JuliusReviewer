/*
  ============================================================
  PROGRAM: Decrementing - i--, i -= 1 and i = i - 1
  TOPIC: for loops - counting DOWN with a decreasing counter
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - Three spellings of "subtract 1" that behave identically.
  - Why a decreasing counter needs `>` or `>=` in the condition.
  - Why `i >= 1` is correct for a countdown to 1, and what `i <= 1` does.
  - Countdown loops that finish on 0 instead of on 1.

  EXPECTED OUTPUT:
  Using i--        : 10 9 8 7 6 5 4 3 2 1
  Using i -= 1     : 10 9 8 7 6 5 4 3 2 1
  Using i = i - 1  : 10 9 8 7 6 5 4 3 2 1
  All three decrement methods produced identical output.
  Countdown from 5 down to 1 (condition i >= 1):
  5
  4
  3
  2
  1
  Countdown from 3 down to 0 (condition i >= 0):
  3
  2
  1
  0

  IMPORTANT SYNTAX:
  i--               -> subtract 1 from i (shorthand for i = i - 1)
  i -= 1            -> compound assignment: "subtract 1 from i"
  i = i - 1         -> long hand
  i >= 1            -> "is i still 1 or more?"  correct for a countdown to 1
  i > 1             -> stops one step earlier, so 1 is never printed
  i <= 1            -> WRONG with a decreasing counter: endless loop!

  STEP-BY-STEP EXPLANATION:
  1. A countdown is written exactly like a count-up, with two differences:
     the update is `i--` instead of `i++`, and the comparison is flipped
     from `<` / `<=` to `>` / `>=`.
  2. `i--` is the DECREMENT operator: i = i - 1. `i -= 1` and `i = i - 1`
     do exactly the same thing, so all three countdowns print 10 to 1.
  3. A countdown to 1 must use `i >= 1`. The `>=` is essential: it lets the
     value 1 through the test one last time so that 1 can be printed.
  4. Using `i > 1` would stop one step early and never print the 1.
  5. Using `i <= 1` is the fatal mistake. The counter shrinks while the
     test keeps asking for a small number, so the test is true forever -
     an infinite loop that prints 1, 0, -1, -2, ... without end.
  6. A countdown that must INCLUDE 0 uses `i >= 0` instead of `i >= 1`.
  ============================================================
*/

#include <iostream>
/*
  The one include this project needs. It provides `cout` for console output
  and `endl` for a newline. C++ has no printing of its own, so this line
  must be the first thing after the header comment block.
*/

using namespace std;
/*
  The standard tools live in a namespace named `std`, and `::` means
  "inside" - so `std::cout` reads "the cout that belongs to std".
  `using namespace std;` is the shortcut that saves typing `std::` in
  front of every name, which is why plain `cout` works below. Both forms
  are correct C++.
*/

int main() {
/*
  `main` is the ENTRY POINT: the first function the operating system runs.
  `int` is the return type - a whole number handed back when it ends.
  `()` means it takes no inputs. The `{ }` braces are the BODY: the
  instructions, executed from top to bottom.
*/

    /*
      ============================================================
      PART A - THREE SPELLINGS OF "SUBTRACT 1"
      ============================================================
    */
    cout << "Using i--        :";
    // Label with no newline, so the numbers land on the same row.

    for (int i = 10; i >= 1; i--) {
    /*
                        |     |
                        |     +-- UPDATE: i-- subtracts 1 each pass
                        +-------- CONDITION: >= means "1 or more"
    */
        /*
          `i--` is the DECREMENT operator. It means "subtract 1 from i" and
          is pure shorthand for `i = i - 1`.

          A countdown uses the SAME header layout as a count-up; only two
          things change: the update becomes `i--`, and the condition is
          written with `>` or `>=` instead of `<` or `<=`.

          Trace: i = 10 (true) print 10, i-- makes 9; ... i = 1 (true) print
          1, i-- makes 0, then `0 >= 1` is FALSE and the loop ends.
          Ten iterations, ten numbers, none of them zero.
        */
        cout << " " << i;
    }
    cout << endl;

    cout << "Using i -= 1     :";
    // Padding spaces keep the three labels aligned in the terminal.

    for (int i = 10; i >= 1; i -= 1) {
    //                          +------
        /*
          `-=` is a compound assignment operator: subtract the right-hand
          side from what is already stored in the variable on the left.
              i -= 1   means   i = i - 1
          The same family works the same way for `+=`, `*=`, `/=` and
          `%=`. Beginners should still prefer `i--` because it is shorter
          and cannot be misread.
        */
        cout << " " << i;
    }
    cout << endl;

    cout << "Using i = i - 1  :";
    // The third and longest spelling of the same update.

    for (int i = 10; i >= 1; i = i - 1) {
    //                          +---------
        /*
          The long hand, which hides two steps:
            step 1 - work out `i - 1` from the value i has NOW;
            step 2 - store that answer back into i.
          Assignment always works right to left, so `i = i - 1` is sensible
          and `i - 1 = i` would be a syntax error.
        */
        cout << " " << i;
    }
    cout << endl;

    cout << "All three decrement methods produced identical output." << endl;
    // The proof, printed by the program rather than merely claimed.

    /*
      ============================================================
      PART B - COUNTDOWN TO 1: WHY THE CONDITION IS `i >= 1`
      ============================================================
    */
    cout << "Countdown from 5 down to 1 (condition i >= 1):" << endl;
    // A label on its own line, so the countdown reads clearly below it.

    for (int i = 5; i >= 1; i--) {
        /*
          The condition has to be `>=` and not `>`, and here is why.

          The test asks a QUESTION before every pass: "is i >= 1?"
            i = 5 -> true, print 5, i becomes 4
            i = 4 -> true, print 4, i becomes 3
            i = 3 -> true, print 3, i becomes 2
            i = 2 -> true, print 2, i becomes 1
            i = 1 -> true, print 1, i becomes 0     <-- the `=` earns its
            i = 0 -> "0 >= 1" is FALSE, leave the loop

          With `i > 1` the test would fail while i is 1, so the number 1
          would never be printed and the countdown would stop at 2.
        */
        cout << i << endl;
        // One number per line, because a countdown is easier to read
        // downwards than across.
    }

    /*
      ============================================================
      PART C - COUNTDOWN THAT ALSO INCLUDES 0
      ============================================================
    */
    cout << "Countdown from 3 down to 0 (condition i >= 0):" << endl;
    // The limit moved from 1 to 0, so the condition must allow 0 through.

    for (int i = 3; i >= 0; i--) {
        /*
          `i >= 0` lets the value 0 print before the loop ends.
          Trace: 3, 2, 1, 0 all pass; then i becomes -1 and "-1 >= 0" is
          false, so the loop stops. Negative numbers never appear.

          THE RULE TO REMEMBER: the condition must be true for every value
          you WANT printed, and false for the first value you do not want.
        */
        cout << i << endl;
    }

    /*
      ============================================================
      PART D - THE FATAL MISTAKE: `i <= 1`
      ============================================================
      The loop below is NEVER RUN in this program, and it is left as a
      comment on purpose, because running it would hang the program for
      ever and you could not close the window.

          for (int i = 5; i <= 1; i--) {
              cout << i << endl;
          }

      WHY IT NEVER ENDS:
        The counter starts at 5 and SHRINKS: 5, 4, 3, 2, 1, 0, -1, -2 ...
        The test asks "is i <= 1?". It becomes true at i = 1 and stays
        true for ever after, because a decreasing whole number keeps going
        down without limit. The exit door can never be reached.
        The program would print 1, 0, -1, -2, -3 ... with no end.

      THE RULE THAT PREVENTS IT: the direction of the comparison must
      match the direction of the counter.
          counter goes UP   (i++) -> test with <  or <=
          counter goes DOWN (i--) -> test with >  or >=

      If you ever see a loop that appears to hang, check that pairing
      first. The same mistake with a rising counter is shown in
      ../12_common_mistakes/05_infinite_loop.cpp.
    */

    /*
      ------------------------------------------------------------
      TRACE TABLE
      ------------------------------------------------------------
      TRACE TABLE
      +-----------+------------+-----------------+----------+------------+----------+
      | Iteration | i at start | Update written   | Printed  | i after    | next     |
      |           |            |                 |          | update     | test     |
      +-----------+------------+-----------------+----------+------------+----------+
      |     1     |    10      | i-- (= i-1)      |    10    |     9      |  9>=1 T  |
      +-----------+------------+-----------------+----------+------------+----------+
      |     2     |     9      | i--              |     9    |     8      |  8>=1 T  |
      +-----------+------------+-----------------+----------+------------+----------+
      |     3     |     8      | i -= 1 (= i-1)  |     8    |     7      |  7>=1 T  |
      +-----------+------------+-----------------+----------+------------+----------+
      |     4     |     7      | i = i - 1       |     7    |     6      |  6>=1 T  |
      +-----------+------------+-----------------+----------+------------+----------+
      |     5     |     6      | i--              |     6    |     5      |  5>=1 T  |
      +-----------+------------+-----------------+----------+------------+----------+
      |     6     |     5      | i--              |     5    |     4      |  4>=1 T  |
      +-----------+------------+-----------------+----------+------------+----------+
      |     7     |     4      | i--              |     4    |     3      |  3>=1 T  |
      +-----------+------------+-----------------+----------+------------+----------+
      |     8     |     3      | i--              |     3    |     2      |  2>=1 T  |
      +-----------+------------+-----------------+----------+------------+----------+
      |     9     |     2      | i--              |     2    |     1      |  1>=1 T  |
      +-----------+------------+-----------------+----------+------------+----------+
      |    10     |     1      | i--              |     1    |     0      |  0>=1 F  |
      +-----------+------------+-----------------+----------+------------+----------+
      |    11     |     0      | (never reached)  |  STOP    |     0      |  -       |
      +-----------+------------+-----------------+----------+------------+----------+

      The last row is the important one. i reached 0, the test failed, and
      nothing was printed - a failed test never produces output.

      THE 10-SECOND EXAM METHOD (counting a downward loop)
        1. First value (from the start part).
        2. Last value allowed (from the condition).
        3. Step size (1 for `i--`).
        4. Going DOWN: count = (first - last) / step + 1
        Here: (10 - 1) / 1 + 1 = 9 + 1 = 10 iterations. Correct.

      THE COMMON TRAP IN THIS FILE
        Copying the condition from a count-up loop without changing the
        direction. `for (int i = 5; i <= 1; i--)` looks reasonable at a
        glance and hangs for ever. Say the condition out loud in English -
        if the sentence cannot become false, the loop cannot end.
    */

    return 0;
    // Leaves main and hands 0 (success) back to the operating system. Any
    // statement after this line would never be reached.
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: What does `i--` mean?                                      -> subtract 1 from i; it is shorthand for i = i - 1
  Q2: How many values does `for (int i = 10; i >= 1; i--)` print?  -> 10  (10 9 8 7 6 5 4 3 2 1)
  Q3: What is the value of i when that loop finally stops?       -> 0
  Q4: Which condition prints the number 1 on the last pass?      -> i >= 1 (the `>=` lets 1 pass the test)
  Q5: What happens with `for (int i = 5; i <= 1; i--)`?         -> an infinite loop: the counter falls while the test keeps succeeding, so 1 0 -1 -2 ... prints for ever
  Q6: How do you make a countdown that also prints 0?           -> change the condition to `i >= 0`
  ============================================================
*/
