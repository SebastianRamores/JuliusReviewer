/*
  ============================================================
  PROGRAM: Incrementing - i++, i += 1 and i = i + 1
  TOPIC: for loops - the update (third) part of the header
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - Three different spellings of "add 1" that behave identically.
  - That the update lives INSIDE the header, not after the loop.
  - What `i++` and `++i` mean, and why a beginner only needs `i++`.
  - The evaluation order when an increment sits inside a cout statement.

  EXPECTED OUTPUT:
  Using i++        : 1 2 3 4 5
  Using i += 1     : 1 2 3 4 5
  Using i = i + 1  : 1 2 3 4 5
  All three update methods produced identical output.
  Postfix i++ inside cout, with i = 1: prints 1
  then i holds 2
  Prefix  ++i inside cout, with i = 1: prints 2
  then i holds 2

  IMPORTANT SYNTAX:
  i++               -> add 1 to i (postfix: hands over the OLD value)
  ++i               -> add 1 to i (prefix:  hands over the NEW value)
  i += 1            -> "i = i + 1" written with a compound assignment operator
  i = i + 1         -> the long hand version; completely valid
  cout << i++       -> prints the old value, THEN adds 1
  cout << ++i       -> adds 1 FIRST, then prints the new value

  STEP-BY-STEP EXPLANATION:
  1. The three loops below are the same loop with three spellings of the
     update. All three print 1 2 3 4 5, which is the proof.
  2. `i++` is the shortest form and the one examiners expect to see.
  3. `i += 1` uses a compound assignment operator: variable, then `+=`,
     then the amount to add. The same shape gives `i -= 1`, `i *= 2`.
  4. `i = i + 1` is the long hand. It works because the right-hand side is
     worked out first and the result is then stored back in i.
  5. Inside a cout statement the position of ++ matters, because cout
     prints whatever value the expression hands it. That is why
     `cout << i++` prints 1 and `cout << ++i` prints 2.
  6. For loops, always write `i++`. The prefix/postfix difference only
     shows up when the increment is used inside a bigger expression.
  ============================================================
*/

#include <iostream>
/*
  The only header this project needs. It supplies `cout` for writing to the
  screen and `endl` for starting a new line. The language itself has no
  printing built in, so this line must come before any use of `cout`.
*/

using namespace std;
/*
  C++ keeps its standard tools inside a namespace called `std`, and `::`
  means "inside" - so `std::cout` is "the cout belonging to std".
  `using namespace std;` is the shortcut that saves us typing `std::`
  before every single name. Both forms are valid C++; the shortcut is what
  beginners and almost every exam answer use.
*/

int main() {
/*
  `main` is the ENTRY POINT - the very first thing the operating system
  runs. `int` is the return type (a whole number handed back at the end),
  `()` means main receives no inputs, and `{ }` delimits the BODY holding
  the instructions.
*/

    /*
      ============================================================
      PART A - THREE SPELLINGS OF "ADD 1"
      ============================================================
      All three loops below print exactly the same numbers. That is the
      whole point of this file: the choice is style, not behaviour.
    */

    cout << "Using i++        :";
    // Label only - no endl yet, so the numbers join it on one line.

    for (int i = 1; i <= 5; i++) {
    //                               |
    //                               +-- UPDATE, the third header part
        /*
          `i++` is the INCREMENT operator and it means "add 1 to i".
          It is pure shorthand - the compiler treats it as `i = i + 1`.

          WHERE DOES THE UPDATE GO?  Inside the ( ) braces, as the third
          part. It is NOT a line written underneath the loop. Putting it
          after the closing brace is the number one exam mistake, because
          it then runs once, after the loop has ended, instead of once per
          pass - and the loop never gets a new value, so it never ends.

          WHEN DOES IT RUN?  After the body has finished, once per
          repetition. Not before the first test, not after the last one.
        */
        cout << " " << i;
    }
    cout << endl;

    cout << "Using i += 1     :";
    // The labels are padded with spaces so the columns line up on screen.

    for (int i = 1; i <= 5; i += 1) {
    //                             +------
        /*
          `+=` is a COMPOUND ASSIGNMENT OPERATOR: "add the right-hand side
          to what is already in the variable on the left".
              i += 1   means   i = i + 1
          The family of these operators is worth memorising, because each
          one works the same way:
              i += 2    add 2
              i -= 1    subtract 1
              i *= 3    multiply by 3
              i /= 2    divide by 2
        */
        cout << " " << i;
    }
    cout << endl;

    cout << "Using i = i + 1  :";
    // Third and last spelling of the same update.

    for (int i = 1; i <= 5; i = i + 1) {
    //                             +-----------
        /*
          The long hand. Two steps are hidden inside it:
            step 1 - work out `i + 1` using the value i has NOW;
            step 2 - store the answer back into i.
          That is why you must write `i = i + 1` and never `i + 1 = i`.
          The left of `=` is the place you store; the right is the
          calculation.
        */
        cout << " " << i;
    }
    cout << endl;

    cout << "All three update methods produced identical output." << endl;
    // Proves the point in the program itself rather than only in a comment.

    /*
      ============================================================
      PART B - THE POSTFIX / PREFIX DIFFERENCE
      ============================================================
      An increment operator can be written in two places:
          i++   POSTFIX - the ++ is written AFTER the variable
          ++i   PREFIX  - the ++ is written BEFORE the variable
      In a LOOP UPDATE the position never matters: both add exactly 1.
      It only matters when the expression is USED for its value, which is
      what cout does.

      THE RULE, in one line:
          postfix  i++   hands back the value i had BEFORE adding 1
          prefix   ++i   adds 1 first and hands back the NEW value

      BEGINNER ADVICE: in loop headers always write the postfix `i++`. It
      is what every textbook and every marking scheme uses, and it is one
      character shorter. Learn the prefix form only so you can read it.
    */

    int i = 1;
    /*
      Declare the counter OUTSIDE the loop this time, so that we can print
      its value after an expression that changes it.
      `int` means whole numbers only. `= 1` stores the value 1 in it.
    */

    cout << "Postfix i++ inside cout, with i = 1: prints " << i++ << endl;
    /*
      Follow this one expression carefully:
        1. cout needs a value to print, so it looks at `i++`.
        2. `i++` is POSTFIX, so the value it hands over is the OLD one: 1.
           The number 1 goes into the output.
        3. The side effect happens as part of that same step, so i now
           holds 1 + 1 = 2. Note that nothing has read i since.
      The increment happens exactly where it is written, and the printed
      number is the value from BEFORE it.

      IMPORTANT RULE ABOUT `i` IN ONE STATEMENT: never change `i` and also
      READ `i` inside the same statement. Such code has no defined answer,
      and g++ reports it as:
          warning: operation on 'i' may be undefined [-Wsequence-point]
      So the "and afterwards i holds ..." line below is a SEPARATE
      statement. That is how you are meant to write it.
    */

    cout << "then i holds " << i << endl;
    // Read i again, now that the previous statement has finished. The
    // answer is 2, which proves the postfix increment did happen.

    i = 1;
    // Reset the counter. Without this line the value 2 from above would
    // still be sitting in i, and the comparison would be confusing.

    cout << "Prefix  ++i inside cout, with i = 1: prints " << ++i << endl;
    /*
      Now the side effect happens FIRST:
        1. cout looks at `++i`, which is PREFIX, so it adds 1 immediately:
           i goes from 1 to 2 and the value handed over is the NEW one: 2.
        2. The number 2 is printed.
      So the same statement that printed 1 in the postfix case prints 2
      here, from the very same starting value.

      SUMMARY: both forms always add 1. The ONLY difference is whether the
      old value or the new value is handed to whatever uses the expression.
    */

    cout << "then i holds " << i << endl;
    // And i is 2 again. Both forms added exactly 1 - the prefix version
    // just reported the value AFTER the change instead of before it.

    /*
      ------------------------------------------------------------
      TRACE TABLE
      ------------------------------------------------------------
      TRACE TABLE
      +-----------+------------+-------------------+----------+------------+----------+
      | Iteration | i at start | Update written     | Printed  | i after    | i at     |
      |           |            |                   |          | update     | next test|
      +-----------+------------+-------------------+----------+------------+----------+
      |     1     |     1      | i++  (= i+1)      |    1     |     2      |    2     |
      +-----------+------------+-------------------+----------+------------+----------+
      |     2     |     2      | i += 1 (= i+1)    |    2     |     3      |    3     |
      +-----------+------------+-------------------+----------+------------+----------+
      |     3     |     3      | i = i + 1         |    3     |     4      |    4     |
      +-----------+------------+-------------------+----------+------------+----------+
      |     4     |     4      | i++               |    4     |     5      |    5     |
      +-----------+------------+-------------------+----------+------------+----------+
      |     5     |     5      | i++               |    5     |     6      |    6     |
      +-----------+------------+-------------------+----------+------------+----------+
      |     6     |     6      | (not reached)     |  STOP    |     6      |    6     |
      +-----------+------------+-------------------+----------+------------+----------+

      The middle "Update written" column is the ONLY column that differs
      between the three loops. Read across: every other column is identical,
      which is exactly why the three loops print the same thing.

      THE 10-SECOND EXAM METHOD
        If a question asks how many times a loop runs, the update tells you
        the STEP SIZE:
            i++       step is 1
            i += 2    step is 2
            i *= 3    the numbers jump: 1 3 9 27 ...
        Then count = (limit - start) / step + 1, going up.

      THE COMMON TRAP IN THIS FILE
        Writing the update AFTER the loop, or forgetting it altogether:
            for (int i = 1; i <= 5; ) { cout << i; }
        Here i never changes, the condition `i <= 5` stays true forever,
        and the program prints 1 for ever. An update that is missing or
        misplaced is the most common cause of an infinite loop.
    */

    return 0;
    /*
      Leaves main and hands 0 (success) back to the operating system.
      The `0` is a convention; writing it explicitly is good practice and
      earns easy marks.
    */
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: Are `i++`, `i += 1` and `i = i + 1` different?         -> No, all three add exactly 1 and produce identical output
  Q2: In which part of the header does the update go?          -> the third part, inside the ( ) after the second semicolon
  Q3: What does `cout << i++` print when i holds 1?           -> 1, and afterwards i holds 2
  Q4: What does `cout << ++i` print when i holds 1?           -> 2, and afterwards i holds 2
  Q5: What is the difference between prefix and postfix?      -> postfix hands back the old value, prefix adds first and hands back the new value
  Q6: Which spelling should a beginner always write?           -> the postfix `i++`
  Q7: What happens if the update is left out of the header?   -> i never changes, the condition never fails, and the loop runs for ever
  ============================================================
*/
