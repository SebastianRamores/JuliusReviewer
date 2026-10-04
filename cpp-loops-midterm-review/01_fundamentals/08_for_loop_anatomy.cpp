/*
  ============================================================
  PROGRAM: Anatomy of a for Loop  (DEEP-DIVE FILE - memorise this)
  TOPIC: for loops - every single character explained
  DIFFICULTY: Beginner (but this is the most important file in the project)

  !!! READ THIS FILE SLOWLY. IT IS THE FOUNDATION OF EVERY OTHER FILE. !!!

  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - The exact meaning of every character in a for loop.
  - The exact ORDER in which the three header parts execute.
  - Why `for` is used instead of `while` when you know the count in advance.
  - How to count iterations on paper in under 10 seconds.

  THE LOOP WE ARE DISSECTING:
       for (int i = 1; i <= 10; i++) {
           cout << i << endl;
       }

  SPLIT IT PIECE BY PIECE:
       for
       (
       int i = 1
       ;
       i <= 10
       ;
       i++
       )
       {
           ...
       }

  ============================================================
*/

#include <iostream>
// Needed for cout and endl.

using namespace std;
// Removes the need to write std:: in front of standard names.

int main() {
/*
    main() is where the program starts.
    `int`  = the type of value returned when the function ends.
    `()`   = no parameters are passed in.
    `{ }`  = the function body: the instructions.
*/

    /*
      ================================================================
      THE LOOP, EXPLAINED CHARACTER BY CHARACTER
      ================================================================
    */
    for (int i = 1; i <= 10; i++) {
    /*
      |    | |  |   |   | |  |    |  |
      |    | |  |   |   | |  |    |  +-- ) closes the header
      |    | |  |   |   | |  |    +----- the UPDATE
      |    | |  |   |   | |  +---------- the CONDITION
      |    | |  |   |   | +------------- 2nd semicolon
      |    | |  |   |   +--------------- the INITIALIZATION
      |    | |  |   +------------------- 1st semicolon
      |    | |  +----------------------- start of the header
      |    | +-------------------------- start of the initialization
      |    +---------------------------- the `for` keyword

      `for` is a KEYWORD - a word reserved by C++, so you may not use it as
      a variable name. The loop repeats the block in its { } braces.

      ( ... )  is called the loop HEADER. It holds exactly THREE parts
                separated by SEMICOLONS, ALWAYS in this order:
                    1. initialization  (run ONCE, before everything)
                    2. condition       (tested before every repetition)
                    3. update          (run once after every repetition)
    */

        /*
          ------------------------------------------------------------
          PART 1 - INITIALIZATION:   int i = 1
          ------------------------------------------------------------
            `int`  : DATA TYPE. It can only hold whole numbers.
                     Whole numbers with no decimal point: ... -2, -1, 0, 1, 2 ...
                     (For decimals you would use `double`, e.g. double pi = 3.14;)
            `i`    : VARIABLE NAME. We choose it. `i` traditionally stands for
                     "index" or "iteration". Any name works: count, n, k, number.
                     It only exists inside this loop and dies at the closing brace.
            `=`    : ASSIGNMENT. "Store the value on the right in the variable
                     on the left." So i is given the value 1.
            `1`    : the starting value.
            `;`    : the SEMICOLON that ends this part of the header.

            EXECUTION: this part runs EXACTLY ONCE. No matter how many times
            the loop repeats, `i` is never re-initialised. This is why the
            variable is usually declared HERE (as `int i`), which keeps its
            scope limited to the loop.
        */

        /*
          ------------------------------------------------------------
          PART 2 - CONDITION:   i <= 10
          ------------------------------------------------------------
            `i`       : the current value of the counter
            `<=`      : "less than or equal to"
            `10`      : the limit
            `;`       : the semicolon separating condition from update.

            Read it as a QUESTION: "is i <= 10?"
              - If TRUE  -> run the body, then do the update, then test again.
              - If FALSE -> skip the body and LEAVE the loop.

            THIS IS THE EXIT DOOR. A loop ends ONLY when the condition becomes
            false. If the condition is always true, the loop never ends.

            All six comparison operators:
                a <  b    a is smaller than b
                a <= b    a is smaller than b OR equal to b   (allows b itself)
                a >  b    a is bigger than b
                a >= b    a is bigger than b OR equal to b   (allows b itself)
                a == b    a is EXACTLY equal to b
                a != b    a is NOT equal to b
        */

        /*
          ------------------------------------------------------------
          PART 3 - THE BODY  { cout << i << endl; }
          ------------------------------------------------------------
            This is the work that gets repeated.
            `cout`  : console output - sends text to the screen.
            `<<`    : the stream insertion operator. Point the arrow in the
                      direction of travel: data flows INTO cout. They can be
                      chained: "send this, then that, then that".
            `i`     : the current number.
            `endl`  : "end line" - moves the cursor to the start of the next
                      line so the next print starts on a new row.

            *** BRACES ARE MANDATORY HERE because the body has MORE THAN ONE
            statement. See 02_for_loops/09_for_loop_without_braces.cpp for
            what happens if you forget them. ***
        */

        cout << i << endl;
        // Print the current value of i on its own line.
    }

    /*
      ================================================================
      PART 4 - THE UPDATE:   i++
      ================================================================
        WAIT - where is it? Look again at the header:

            for (int i = 1; i <= 10; i++) {
                                         ^^^^ HERE, inside the ( )

        It is NOT after the closing brace. This is the #1 exam error:
        students write the update below the loop. That is wrong.

        `i++` : the INCREMENT operator. It means "add 1 to i".
                 It is shorthand for:  i = i + 1;   or   i += 1;
        `i--` : the DECREMENT operator. It means "subtract 1 from i".
                 Shorthand for:       i = i - 1;   or   i -= 1;

        WHEN DOES IT RUN?  After the body has finished, once per repetition.
        NOT before the first test, and NOT after the loop has finished.
    */

    /*
      ================================================================
      THE EXACT EXECUTION ORDER - memorise this list
      ================================================================

         1. INITIALIZATION      -> int i = 1          (once, ever)
         2. CONDITION CHECK     -> is i <= 10 ?
         3. EXECUTE THE BODY    -> cout << i << endl;
         4. UPDATE              -> i++
         5. CONDITION CHECK     -> is i <= 10 ?      (back to step 2)
         6. EXECUTE THE BODY
         7. UPDATE
         8. ... repeat steps 5-7 ...
         9. CONDITION BECOMES FALSE
        10. EXIT THE LOOP - the first statement AFTER the closing brace runs

       Written as a flow chart in text:

             [int i = 1]
                   |
                   v
             <i <= 10 ?> --no--> [EXIT LOOP] --> continue after the loop
                   | yes
                   v
             [body: print i]
                   |
                   v
                [i++]
                   |
                   +------ back to the condition test
    */

    /*
      ================================================================
      FULL TRACE TABLE
      ================================================================
      +----------+-----------+--------------+-----------+-----------+
      |Iteration | i BEFORE  | i <= 10 ?    |  Output   | i AFTER   |
      |          | the test  |              |           | update    |
      +----------+-----------+--------------+-----------+-----------+
      |    1     |     1     | 1 <= 10 true |    1      |     2     |
      |    2     |     2     | 2 <= 10 true |    2      |     3     |
      |    3     |     3     | 3 <= 10 true |    3      |     4     |
      |    4     |     4     | 4 <= 10 true |    4      |     5     |
      |    5     |     5     | 5 <= 10 true |    5      |     6     |
      |    6     |     6     | 6 <= 10 true |    6      |     7     |
      |    7     |     7     | 7 <= 10 true |    7      |     8     |
      |    8     |     8     | 8 <= 10 true |    8      |     9     |
      |    9     |     9     | 9 <= 10 true |    9      |    10     |
      |   10     |    10     | 10 <= 10 true|   10      |    11     |
      |   11     |    11     | 11 <= 10 false| STOP   |    12     |
      +----------+-----------+--------------+-----------+-----------+

       Total iterations = 10.
    */

    /*
      ================================================================
      THE 10-SECOND EXAM METHOD (how to count iterations quickly)
      ================================================================
        Step 1: What is the FIRST value of i?      (from the initialization)
        Step 2: What is the LAST value allowed?   (from the condition)
        Step 3: How much does i change each time?(from the update)
        Step 4: iterations = (last - first) / step   + 1   if going UP
                iterations = (first - last) / step   + 1   if going DOWN

        Check: (10 - 1) / 1 + 1 = 9 + 1 = 10   correct!
        Check for step 2 from 1 to 10:  (10-1)/2 + 1 = 4.5 + 1 -> the real
        answer comes from counting: 1,3,5,7,9 = 5 iterations. When the
        division is not exact, just write the sequence out and count.
    */

    return 0;
    // Hand 0 (success) back to the operating system.
}

/*
  ============================================================
  EXAM QUESTIONS ON THIS EXACT LOOP
  ============================================================
  Q1: How many times does the body run?                        -> 10
  Q2: What is i's value after the loop?                        -> 11
  Q3: Which part runs exactly once?                            -> the initialization
  Q4: In which order are the three parts run?                  -> init, cond, body, update, cond, body, update...
  Q5: If the condition were i < 10, what changes?              -> 9 iterations; 10 never printed
  Q6: If the update were i += 2, which values are printed?     -> 1 3 5 7 9
  Q7: If the initialization were i = 0?                       -> prints 0..10 (11 values)
  ============================================================
*/
