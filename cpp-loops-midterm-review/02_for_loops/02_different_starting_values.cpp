/*
  ============================================================
  PROGRAM: Different Starting Values in a for Loop
  TOPIC: for loops - the initialization part
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - The FIRST part of the header is called the initialization.
  - Changing only the start value changes BOTH the first printed number
    and the total number of iterations.
  - Three identical loops that differ in one character.
  - How to read a loop header backwards to check your work.

  EXPECTED OUTPUT:
  Starting from 1:
  1
  2
  3
  4
  5
  Starting from 0:
  0
  1
  2
  3
  4
  5
  Starting from 5:
  5
  6
  7
  8
  9
  10

  IMPORTANT SYNTAX:
  int i = 0;             -> the loop counter begins life holding 0
  for (int i = 1; ...)   -> start part of the header: where the counter begins
  i <= 5                 -> the end condition decides when to stop
  i++                    -> the update decides the step size
  cout << "text" << endl;-> print literal text in double quotes, then a newline

  STEP-BY-STEP EXPLANATION:
  1. The three loops below are identical except for the number in the
     initialization part of the header.
  2. Loop 1 starts at 1 and stops after 5  -> prints 1,2,3,4,5  (5 values).
  3. Loop 2 starts at 0 and stops after 5  -> prints 0,1,2,3,4,5 (6 values).
     One extra value, because 0 was added in front of the old list.
  4. Loop 3 starts at 5 and stops after 10 -> prints 5,6,7,8,9,10 (6 values).
     Same count as loop 2: the window 0..5 and the window 5..10 are both
     six numbers wide.
  5. CONCLUSION: the start value decides the FIRST number printed, and it
     also decides how many numbers there are.
  ============================================================
*/

#include <iostream>
/*
  The one and only include this project needs. <iostream> provides `cout`
  for output, `endl` for a newline and `cin` for input. C++ has no built-in
  printing, so without this line every `cout` below would be an unknown name.
*/

using namespace std;
/*
  Standard C++ keeps cout and endl inside a namespace called `std`. The `::`
  operator means "inside", so `std::cout` reads "the cout inside std".
  `using namespace std;` is a shortcut that lets us drop the `std::` prefix
  and write plain `cout`. Exam note: both spellings are correct; the prefix
  version is considered safer in very large programs.
*/

int main() {
/*
  `main` is the function where execution BEGINS - the operating system calls
  it first. `int` is its return type (a whole number handed back on exit),
  `()` means it accepts no inputs, and `{ }` delimits the body that holds
  the instructions. Nothing in this file asks the user for anything, so
  there is no `cin` anywhere.
*/

    /*
      ============================================================
      LOOP 1 - START AT 1
      ============================================================
    */
    cout << "Starting from 1:" << endl;
    /*
      `cout << "Starting from 1:"` prints the words between the double
      quotes. The quotes are the compiler's signal that this is TEXT and
      not the name of a variable. `<< endl` then moves to a new line so the
      numbers start on a fresh row.
    */

    for (int i = 1; i <= 5; i++) {
    /*
                          |    |
                          |    +-- UPDATE: add 1 each pass
                          +------- CONDITION: keep going while i <= 5
                                  START: the counter is created holding 1
    */
        /*
          The initialization `int i = 1` runs once. The condition then asks
          "is i <= 5?" five times successfully, so the body runs five times
          and prints 1, 2, 3, 4, 5.
        */
        cout << i << endl;
        // One number per line. endl ends the line AND flushes the output
        // buffer, which is why it appears everywhere in this folder.
    }

    /*
      ============================================================
      LOOP 2 - START AT 0
      ============================================================
    */
    cout << "Starting from 0:" << endl;
    // Same idea: a label so the output can be matched to the loop below it.

    for (int i = 0; i <= 5; i++) {
        /*
          ONLY CHANGE: `1` became `0`.

          Two consequences, and exam questions love both of them:
            (a) the FIRST number printed is 0 instead of 1;
            (b) the number of iterations goes UP by one, from 5 to 6,
                because 0 was pushed in front of the old list:
                    0, 1, 2, 3, 4, 5   = 6 values.

          Quick check with the formula: (last - first) / step + 1
                                       = (5 - 0) / 1 + 1
                                       = 5 + 1 = 6. Correct.
        */
        cout << i << endl;
    }

    /*
      ============================================================
      LOOP 3 - START AT 5
      ============================================================
    */
    cout << "Starting from 5:" << endl;
    // A third label, to make the third block obvious on the screen.

    for (int i = 5; i <= 10; i++) {
        /*
          TWO changes from loop 1: the start moved to 5 AND the limit moved
          to 10, because otherwise the loop would stop immediately.

          Why two changes? With `int i = 5; i <= 5;` the condition is true
          exactly once (i is 5), the body prints 5, then i++ makes it 6,
          the test fails and the loop ends. One value, never a zero.

          Result: 5, 6, 7, 8, 9, 10 = 6 values. Same count as loop 2,
          because 5..10 is also six numbers wide.
        */
        cout << i << endl;
    }

    /*
      ------------------------------------------------------------
      TRACE TABLE - all three loops on one sheet
      ------------------------------------------------------------
      TRACE TABLE
      Loop 1:  for (int i = 1; i <= 5; i++)     -> 5 iterations
      +-----------+------------+--------------+-----------+
      | Iteration | i at start | condition    | Output    |
      |           |            | i <= 5 ?     |           |
      +-----------+------------+--------------+-----------+
      |     1     |     1      | true         |    1      |
      +-----------+------------+--------------+-----------+
      |     2     |     2      | true         |    2      |
      +-----------+------------+--------------+-----------+
      |     3     |     3      | true         |    3      |
      +-----------+------------+--------------+-----------+
      |     4     |     4      | true         |    4      |
      +-----------+------------+--------------+-----------+
      |     5     |     5      | true         |    5      |
      +-----------+------------+--------------+-----------+
      |     6     |     6      | FALSE ->STOP |  -        |
      +-----------+------------+--------------+-----------+

      Loop 2:  for (int i = 0; i <= 5; i++)     -> 6 iterations
      +-----------+------------+--------------+-----------+
      | Iteration | i at start | condition    | Output    |
      |           |            | i <= 5 ?     |           |
      +-----------+------------+--------------+-----------+
      |     1     |     0      | true         |    0      |
      +-----------+------------+--------------+-----------+
      |     2     |     1      | true         |    1      |
      +-----------+------------+--------------+-----------+
      |     3     |     2      | true         |    2      |
      +-----------+------------+--------------+-----------+
      |     4     |     3      | true         |    3      |
      +-----------+------------+--------------+-----------+
      |     5     |     4      | true         |    4      |
      +-----------+------------+--------------+-----------+
      |     6     |     5      | true         |    5      |
      +-----------+------------+--------------+-----------+
      |     7     |     6      | FALSE ->STOP |  -        |
      +-----------+------------+--------------+-----------+

      Loop 3:  for (int i = 5; i <= 10; i++)    -> 6 iterations
      +-----------+------------+---------------+-----------+
      | Iteration | i at start | condition     | Output    |
      |           |            | i <= 10 ?     |           |
      +-----------+------------+---------------+-----------+
      |     1     |     5      | true          |    5      |
      +-----------+------------+---------------+-----------+
      |     2     |     6      | true          |    6      |
      +-----------+------------+---------------+-----------+
      |     3     |     7      | true          |    7      |
      +-----------+------------+---------------+-----------+
      |     4     |     8      | true          |    8      |
      +-----------+------------+---------------+-----------+
      |     5     |     9      | true          |    9      |
      +-----------+------------+---------------+-----------+
      |     6     |    10      | true          |   10      |
      +-----------+------------+---------------+-----------+
      |     7     |    11      | FALSE ->STOP  |  -        |
      +-----------+------------+---------------+-----------+

      THE 10-SECOND EXAM METHOD
        Write the sequence of values on paper BEFORE you answer. If you
        cannot list the values, you do not yet understand the loop.
        Then count the entries in your list - that is the iteration count.

      THE COMMON TRAP IN THIS FILE
        Counting by looking at the LIMIT only. `i <= 5` never tells you the
        count on its own - it depends on the start value too. Reading a
        header backwards (update, then condition, then start) is the habit
        that stops this mistake.
    */

    return 0;
    // Ends the program and hands 0 back to the operating system. 0 means
    // "no errors". Any code placed after this line would never run.
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: How many values does `for (int i = 1; i <= 5; i++)` print?  -> 5
  Q2: How many values does `for (int i = 0; i <= 5; i++)` print?  -> 6
  Q3: What is the difference between the two counts?               -> the start value moved from 1 down to 0, adding one extra value at the front
  Q4: What is printed on the very first line of loop 3?           -> 5
  Q5: If loop 3 started at 5 but stopped at `i < 10`, how many values? -> 5 (prints 5 6 7 8 9)
  Q6: Why must the limit be changed in loop 3?                    -> otherwise the loop would print only 5 and stop on the second test
  ============================================================
*/
