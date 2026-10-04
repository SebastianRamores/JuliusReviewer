/*
  ============================================================
  PROGRAM: Count Down from 10 to 1
  TOPIC: for loops - decrementing loops
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - How to make a loop run backwards by starting high and using `i--`.
  - Why the condition must also be written for "going down" (`i >= 1`).
  - What happens if the direction of the condition does not match the update.

  EXPECTED OUTPUT:
    10
    9
    8
    7
    6
    5
    4
    3
    2
    1

  IMPORTANT SYNTAX:
    for (int i = 10; i >= 1; i--)
    i--   is shorthand for i = i - 1;

  STEP-BY-STEP EXPLANATION:
    i starts at 10 (the BIG value) and moves DOWN towards 1.
    The condition `i >= 1` keeps the loop alive while i has not yet reached 1.
    Each pass subtracts 1. When i becomes 0, `0 >= 1` is false, so we stop.
  ============================================================
*/

#include <iostream>
// Provides cout, cin and endl.

using namespace std;
// Allows the short form `cout` instead of `std::cout`.

int main() {
// Program entry point. `int` return type, no parameters, body in braces.

    for (int i = 10; i >= 1; i--) {
    /*
       int i = 10 -> start at the TOP of the range
       i >= 1     -> "is i at least 1?" keep going while yes
       i--        -> move DOWN by 1 after each pass

      KEY IDEA: a countdown loop has three things reversed compared with a
      counting-up loop:
          start at the maximum, use `>=`, and decrement with `i--`.
    */

        cout << i << endl;
        // Print the current value. Since i shrinks each pass, the screen shows
        // 10, 9, 8 ... 1 in that order.
    }

    /*
      TRACE TABLE
      +-----------+------------+-----------+----------+
      | Iteration | i at start | i >= 1 ? | Output   |
      +-----------+------------+-----------+----------+
      |     1     |    10      |   true   |   10     |
      |     2     |     9      |   true   |    9     |
      |     3     |     8      |   true   |    8     |
      |     4     |     7      |   true   |    7     |
      |     5     |     6      |   true   |    6     |
      |     6     |     5      |   true   |    5     |
      |     7     |     4      |   true   |    4     |
      |     8     |     3      |   true   |    3     |
      |     9     |     2      |   true   |    2     |
      |    10     |     1      |   true   |    1     |
      |    11     |     0      |   false  |  STOP    |
      +-----------+------------+-----------+----------+
    */

    /*
      ---------------------------------------------------------------
      THE #1 EXAM TRAP: mismatched condition and update
      ---------------------------------------------------------------
        for (int i = 10; i <= 1; i--)   <-- BROKEN, infinite loop
        Why? i starts at 10 and DECREASES, so i <= 1 is true at the start
        and stays true forever: 10, 9, 8, 7 ... never crosses 1 downwards.
        The loop can never end. (See 12_common_mistakes/05_infinite_loop.cpp)

        Rule of thumb: the comparison must "point towards" the update.
            update goes UP   (i++)  ->  condition uses  <= or <
            update goes DOWN (i--)  ->  condition uses  >= or >
    */

    return 0;
    // Successful completion.
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: How many iterations?                       -> 10
  Q2: What is i after the loop?                  -> 0
  Q3: How many iterations if it were i > 1?      -> 9  (2..10 printed)
  Q4: Spot the bug: i >= 1 with i++              -> infinite loop
  Q5: Rewrite as a while loop.                   -> while (i >= 1) { ... i--; }
  ============================================================
*/
