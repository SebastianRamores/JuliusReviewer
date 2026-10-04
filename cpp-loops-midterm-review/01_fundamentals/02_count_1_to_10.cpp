/*
  ============================================================
  PROGRAM: Count from 1 to 10
  TOPIC: for loops - the classic counting loop
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - The single most common exam loop: print numbers from 1 to some limit.
  - How the start value, end value and step work together.
  - Why we usually write `i <= 10` and not `i < 10`.

  EXPECTED OUTPUT:
    1
    2
    3
    4
    5
    6
    7
    8
    9
    10

  IMPORTANT SYNTAX:
    for (int i = 1; i <= 10; i++)
    cout << i << endl;

  STEP-BY-STEP EXPLANATION:
    i is created as 1. While i <= 10 is true we print i, then add 1.
    When i becomes 11 the condition fails and the loop ends.
  ============================================================
*/

#include <iostream>
// Brings in cout (screen output), cin (keyboard input) and endl (new line).
// Without it the compiler does not know what cout means.

using namespace std;
// Lets us write `cout` instead of `std::cout`. `std` is the namespace holding
// all standard-library names.

int main() {
/*
  The entry point. Execution always begins here.
  `int` = it gives back a whole number (the exit code).
  `()`  = it accepts no inputs.
  `{ }` = the body, the block of instructions.
*/

    for (int i = 1; i <= 10; i++) {
    /*
       int i = 1  -> create counter i and start it at 1
       i <= 10    -> keep going while i is at most 10
       i++        -> then add 1 to i

      `<=` is "less than or equal to". Because i STARTS at 1, using `<= 10`
      includes 10 itself. If we wrote `i < 10`, the body would stop after
      printing 9, and 10 would never appear.
    */

        cout << i << endl;
        /*
          Print the CURRENT value of i, then move to the next line.
          `cout` is the output stream. `<<` means "send into the stream".
          Here we send three things in a row: the number i, and then endl.
          Because i changes each time round, the printed numbers change too.
        */
    }

    /*
      TRACE TABLE
      +-----------+------------+-----------+----------+
      | Iteration | i at start | i <= 10 ? | Output   |
      +-----------+------------+-----------+----------+
      |     1     |     1      |   true    |    1     |
      |     2     |     2      |   true    |    2     |
      |     3     |     3      |   true    |    3     |
      |     4     |     4      |   true    |    4     |
      |     5     |     5      |   true    |    5     |
      |     6     |     6      |   true    |    6     |
      |     7     |     7      |   true    |    7     |
      |     8     |     8      |   true    |    8     |
      |     9     |     9      |   true    |    9     |
      |    10     |    10      |   true    |    10    |
      |     11     |    11      |   false   |  STOP    |
      +-----------+------------+-----------+----------+

      Formulas worth memorising:
        to print 1..N        -> start 1, condition i <= N, step i++
        number of iterations -> N  (for 1..N with step 1)
    */

    return 0;
    // Tell the operating system: finished successfully.
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: Change the loop to print 1 to 5.           -> i <= 5
  Q2: How many iterations with `i <= 10`?       -> 10
  Q3: How many iterations with `i < 10`?        -> 9
  Q4: Why is 10 printed with `<=` but not `<`?  -> `<=` includes 10 itself
  Q5: How many iterations if update is i += 3?  -> 1,4,7,10 -> 4
  ============================================================
*/
