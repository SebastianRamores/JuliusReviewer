/*
  ============================================================
  PROGRAM: Count by 2 (Stepping / Skipping Loops)
  TOPIC: for loops - custom increment size
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - How to change the SIZE of the step in a counting loop.
  - `i += 2` (compound assignment) and why it is easier than `i = i + 2`.
  - How to count even numbers without testing each number with `%`.

  EXPECTED OUTPUT:
    2
    4
    6
    8
    10

  IMPORTANT SYNTAX:
    i += 2     means  i = i + 2
    i += 1     means  i = i + 1   (the same as i++)

  STEP-BY-STEP EXPLANATION:
    Start at 2 and jump 2 each time. i visits 2, 4, 6, 8, 10 and then 12.
    At 12 the test `i <= 10` fails, so the loop stops.
    Because i starts at an even number and only ever grows by 2, every value
    printed is even. That is the trick for "print the even numbers".
  ============================================================
*/

#include <iostream>
// Gives us cout for printing and endl for line breaks.

using namespace std;
// Use the standard names without writing std:: in front.

int main() {
// Where execution begins. Returns an int exit code, takes no inputs.

    for (int i = 2; i <= 10; i += 2) {
    /*
       int i = 2  -> the first even number
       i <= 10    -> stay inside the range
       i += 2     -> COMPOUND ASSIGNMENT: add 2 to i

      `+=` is one of the "compound assignment" operators. It reads as
      "i plus-equals 2", i.e. "increase i by 2". It is EXACTLY the same as
      writing:  i = i + 2;
      The compound form is shorter and is the style examiners expect.

      The update does not have to be 1. Any amount may be used:
          i += 1   (same as i++)
          i += 2   (skip every other number)
          i += 5   (groups of five)
          i *= 2   (double each time: 1, 2, 4, 8, ...)
          i -= 3   (go down by three)
    */

        cout << i << endl;
        // Print the current value of i, then a newline.
    }

    /*
      TRACE TABLE
      +-----------+------------+-----------+----------+
      | Iteration | i at start | i <= 10 ? | Output   |
      +-----------+------------+-----------+----------+
      |     1     |     2      |   true    |    2     |
      |     2     |     4      |   true    |    4     |
      |     3     |     6      |   true    |    6     |
      |     4     |     8      |   true    |    8     |
      |     5     |    10      |   true    |   10     |
      |     6     |    12      |   false   |  STOP    |
      +-----------+------------+-----------+----------+
    */

    /*
      ---------------------------------------------------------------
      TWO WAYS TO PRINT THE EVEN NUMBERS 1..10 - know both!
      ---------------------------------------------------------------
        WAY A (stepping - what this file does):
            for (int i = 2; i <= 10; i += 2) cout << i << endl;
            Fast, clean. But only works if the range STARTS on a multiple.

        WAY B (testing every number with the modulo operator):
            for (int i = 1; i <= 10; i++)
                if (i % 2 == 0) cout << i << endl;
            Works for any range. `%` gives the remainder after division.
            4 % 2 == 0 means 4 divides evenly by 2, so 4 is even.
    */

    return 0;
    // Report success to the operating system.
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: Print the ODD numbers from 1 to 9.        -> for (i=1; i<=9; i+=2)
  Q2: Print 0, 5, 10, ..., 50.                 -> for (i=0; i<=50; i+=5)
  Q3: How many iterations does 1..100 step 5 print?  -> 20
  Q4: Rewrite  i += 2  without += .            -> i = i + 2;
  Q5: What does 7 % 2 equal?                   -> 1  (so 7 is odd)
  ============================================================
*/
