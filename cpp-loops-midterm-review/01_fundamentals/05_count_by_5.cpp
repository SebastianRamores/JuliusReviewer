/*
  ============================================================
  PROGRAM: Count by 5 (Multiples and Grouping)
  TOPIC: for loops - larger step sizes, multiples
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - Using a step size of 5 to visit only multiples of 5.
  - How to count "how many numbers are in this range" by dividing.
  - The difference between a "stepping" loop and a "counting" loop.

  EXPECTED OUTPUT:
    5
    10
    15
    20
    25
    30

  IMPORTANT SYNTAX:
    for (int i = 5; i <= 30; i += 5)
    integer division with `/` in an expression such as 30 / 5

  STEP-BY-STEP EXPLANATION:
    Start at 5 (the first multiple) and jump 5 at a time.
    i takes the values 5, 10, 15, 20, 25, 30, then 35 - and 35 > 30 stops it.
    So the multiples of 5 from 1 to 30 are printed: six of them.
  ============================================================
*/

#include <iostream>
// Supplies cout, cin and endl.

using namespace std;
// Lets us use standard names directly.

int main()
// Program starts here; returns an integer exit code.
{

    for (int i = 5; i <= 30; i += 5) {
    /*
       start at the first multiple of 5 (5), stop after 30, step by 5.

       WHY START AT 5 AND NOT 1?
       Starting at 1 with step 5 would print 1, 6, 11, 16 ... which are NOT
       multiples of 5. To list multiples of 5 you must start at 5 (or 0) and
       step by 5. This is the single most common stepping-loop question.
    */

        cout << i << endl;
        // Print the current multiple.
    }

    /*
      TRACE TABLE
      +-----------+------------+-----------+----------+
      | Iteration | i at start | i <= 30 ? | Output   |
      +-----------+------------+-----------+----------+
      |     1     |     5      |   true    |    5     |
      |     2     |    10      |   true    |   10     |
      |     3     |    15      |   true    |   15     |
      |     4     |    20      |   true    |   20     |
      |     5     |    25      |   true    |   25     |
      |     6     |    30      |   true    |   30     |
      |     7     |    35      |   false   |  STOP    |
      +-----------+------------+-----------+----------+
    */

    /*
      ---------------------------------------------------------------
      USEFUL EXAM ARITHMETIC (integer division - no decimals)
      ---------------------------------------------------------------
        How many numbers are in 1..30?          -> 30 - 1 + 1 = 30
        How many multiples of 5 in 1..30?      -> 30 / 5 = 6
        How many even numbers in 1..30?        -> 30 / 2 = 15
        How many multiples of 3 in 1..30?      -> 30 / 3 = 10

        NOTE: `30 / 5` uses INTEGER division because both sides are whole
        numbers, so the answer is 6 (not 6.0). If you want a decimal you must
        write one side as a decimal, e.g. 30 / 5.0.
    */

    return 0;
    // Finished, no errors.
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: Print the multiples of 7 from 1 to 70.      -> i=7; i<=70; i+=7
  Q2: How many multiples of 5 from 1 to 30?      -> 6
  Q3: How many multiples of 4 from 1 to 100?     -> 25
  Q4: Print 100, 90, 80 ... 10.                  -> i=100; i>=10; i-=10
  Q5: Print multiples of 3 from 0 to 30.          -> i=0; i<=30; i+=3  (11 values)
  ============================================================
*/
