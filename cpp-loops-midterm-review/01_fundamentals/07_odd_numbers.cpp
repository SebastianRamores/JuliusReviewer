/*
  ============================================================
  PROGRAM: Print the Odd Numbers from 1 to 20
  TOPIC: for loops + modulo, and the `!=` operator
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - The definition of an odd number.
  - Two correct ways to test for odd, and why both work.
  - The `!=` (not equal to) operator.

  EXPECTED OUTPUT:
    1
    3
    5
    7
    9
    11
    13
    15
    17
    19

  IMPORTANT SYNTAX:
    if (i % 2 != 0) { ... }      // remainder is NOT zero  -> odd
    if (i % 2 == 1) { ... }      // remainder is exactly 1 -> odd

  STEP-BY-STEP EXPLANATION:
    Visit every number 1..20. For each one ask: "does dividing by 2 leave a
    remainder?" If something is left over, the number is odd, so print it.
    20 is even, so the last odd printed is 19.
  ============================================================
*/

#include <iostream>
// Provides cout, cin, endl.

using namespace std;
// Use standard-library names without the std:: prefix.

int main() {
// Where the program begins. Returns an integer; takes no inputs.

    for (int i = 1; i <= 20; i++) {
    // Visit each number 1 to 20 in turn.

        if (i % 2 != 0) {
        /*
          `!=` means "is NOT equal to". Read the condition aloud:
              "if the remainder of i divided by 2 is not zero"

          Why does that mean odd? Dividing a whole number by 2 leaves either
          a remainder of 0 (exact, so EVEN) or a remainder of 1 (so ODD).
          Anything other than zero therefore means odd.

          EQUALLY CORRECT alternative:  if (i % 2 == 1)
          Both pass in the exam. Some lecturers prefer the second because it
          is more explicit about the actual remainder value.

          COMPARISON OPERATORS you must know:
              <    less than
              <=   less than or equal to
              >    greater than
              >=   greater than or equal to
              ==   exactly equal to
              !=   not equal to
        */

            cout << i << endl;
            // Printed only when i is odd.
        }

    } // end for

    /*
      TRACE TABLE (condensed - only the interesting columns)
      +-----------+------------+--------------+----------+
      | Iteration | i          | i % 2 != 0 ? | Output   |
      +-----------+------------+--------------+----------+
      |     1     |     1      |    true      |    1     |
      |     2     |     2      |    false     | (nothing)|
      |     3     |     3      |    true      |    3     |
      |     4     |     4      |    false     | (nothing)|
      |     5     |     5      |    true      |    5     |
      |     ...   |    ...     |     ...      |   ...    |
      |    19     |    19      |    true      |   19     |
      |    20     |    20      |    false     | (nothing)|
      +-----------+------------+--------------+----------+
      Total odd numbers in 1..20 = 10. Total even numbers = 10.
    */

    /*
      ---------------------------------------------------------------
      QUICK COMPARE: odd / even / divisible-by-3 tests
      ---------------------------------------------------------------
        even?          i % 2 == 0
        odd?           i % 2 != 0     (or i % 2 == 1)
        divisible by 3? i % 3 == 0
        divisible by 5? i % 5 == 0
        divisible by 10? i % 10 == 0
        divisible by BOTH 2 and 5 (i.e. by 10)?  i % 2 == 0 && i % 5 == 0
            `&&` is the AND operator: "both sides must be true".
    */

    return 0;
    // Successful end.
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: How many odd numbers in 1..20?                  -> 10
  Q2: What does 9 % 3 equal?                         -> 0 (9 is divisible by 3)
  Q3: Write the condition "i is divisible by 3".       -> i % 3 == 0
  Q4: Write the condition "i is divisible by both 2 and 5". -> i % 2 == 0 && i % 5 == 0
  Q5: Rewrite using i % 2 == 1.                      -> identical output
  ============================================================
*/
