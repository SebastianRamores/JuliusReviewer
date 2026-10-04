/*
  ============================================================
  PROGRAM: Print the Even Numbers from 1 to 20
  TOPIC: for loops + the modulo operator (%) to detect even numbers
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - The DEFINITION of an even number: divisible by 2 with NO remainder.
  - How to test "divisible by 2" using the modulo operator `%`.
  - Putting an `if` INSIDE a loop so the loop body can react to each number.

  EXPECTED OUTPUT:
    2
    4
    6
    8
    10
    12
    14
    16
    18
    20

  IMPORTANT SYNTAX:
    if (i % 2 == 0) { ... }
    %   = modulo, gives the REMAINDER after division
    ==  = "is equal to?"  (a COMPARISON, two equals signs)

  STEP-BY-STEP EXPLANATION:
    The loop visits every number 1, 2, 3 ... 20.
    For each number we ask: "does dividing by 2 leave a remainder?"
    If the remainder is 0 the number is even, and only then do we print it.
  ============================================================
*/

#include <iostream>
// Brings in cout for output and endl for line breaks.

using namespace std;
// Lets us write cout instead of std::cout.

int main() {
// Execution starts here. Returns an int; takes no parameters.

    for (int i = 1; i <= 20; i++) {
    //  Visit every number from 1 to 20 one at a time.
    //  Step is 1 because we must EXAMINE all numbers, not just some of them.

        if (i % 2 == 0) {
        /*
          WHAT IS `%`?
            `%` is the MODULO operator. It performs division and gives you what
            is LEFT OVER. Examples:
                10 % 2  ->  1     (2 goes into 10 four times, 2 left over)
                 9 % 2  ->  1     (odd)
                12 % 2  ->  0     (even - no remainder at all)
                 7 % 3  ->  1
                15 % 5  ->  0     (15 is divisible by 5)
            RULE: n % d == 0  means "n divides evenly by d".

          WHAT IS `==`?
            `==` is the EQUALITY COMPARISON operator. It asks a question:
            "is the left side equal to the right side?" and answers true/false.

            *** VERY IMPORTANT - `=` versus `==` ***
            `=`  (ONE equals sign)  = ASSIGNMENT. It STORES a value.
                 i = 5;      means "put 5 into i". i now HOLDS 5.
            `==` (TWO equals signs) = COMPARISON. It CHECKS a value.
                 i == 5      means "is i equal to 5?" -> true or false.
            Writing `if (i = 2 == 0)` is nonsense; `if (i % 2 = 0)` will not
            even compile properly - it tries to ASSIGN to a calculation.

          WHAT IS `if`?
            `if (condition) { ... }` runs the block only when the condition is
            true. The condition here is the whole expression `i % 2 == 0`.
            So: "if the remainder of dividing i by 2 is zero, then..."
        */

            cout << i << endl;
            // This line is INSIDE the if-block, so it only runs for even
            // numbers. This nesting is the key skill: loop + condition.
        }

    } // end of the for loop

    /*
      TRACE TABLE
      +-----------+------------+---------------+-------------+----------+
      | Iteration | i at start | i % 2         | i % 2 == 0 ? | Output   |
      +-----------+------------+---------------+-------------+----------+
      |     1     |     1      | 1 % 2 = 1     |    false     | (nothing)|
      |     2     |     2      | 2 % 2 = 0     |    true      |    2     |
      |     3     |     3      | 3 % 2 = 1     |    false     | (nothing)|
      |     4     |     4      | 4 % 2 = 0     |    true      |    4     |
      |     5     |     5      | 5 % 2 = 1     |    false     | (nothing)|
      |     ...   |    ...     |     ...       |     ...      |   ...    |
      |    20     |    20      | 20 % 2 = 0    |    true      |   20     |
      +-----------+------------+---------------+-------------+----------+

      Note the ODD numbers: the loop DID visit them, but the `if` blocked the
      printing. Visiting != printing. This is why the loop must step by 1.
    */

    return 0;
    // All done, successfully.
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: How many even numbers are in 1..20?              -> 10
  Q2: Write the test for an ODD number.               -> if (i % 2 != 1) or i % 2 == 1
  Q3: What does 0 % 2 equal?                         -> 0  (so 0 IS even)
  Q4: Print only the even numbers but also show their count. (counter needed)
  Q5: Rewrite the same program with a WHILE loop.
  ============================================================
*/
