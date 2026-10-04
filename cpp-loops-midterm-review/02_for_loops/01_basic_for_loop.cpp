/*
  ============================================================
  PROGRAM: Basic for Loop - Printing the Numbers 1 to 5
  TOPIC: for loops - the three header parts
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - The three parts of a for loop header and what each one does.
  - The exact ORDER in which those three parts execute.
  - How to work out on paper how many times a loop repeats.
  - How to print one number per line with cout and endl.

  EXPECTED OUTPUT:
  1
  2
  3
  4
  5

  IMPORTANT SYNTAX:
  for (start; condition; update) { body }  -> repeat while the condition is true
  int i = 1;                  -> make a whole-number variable called i, holding 1
  i <= 5                      -> "is i less than or equal to 5?"
  i++                         -> add 1 to i (shorthand for i = i + 1)
  cout << i << endl;          -> print i, then move to the start of a new line
  ;                           -> ends a statement

  STEP-BY-STEP EXPLANATION:
  1. `int i = 1` runs ONCE: the variable i is created holding the value 1.
  2. `i <= 5` is tested. If it is true the body runs; if it is false the loop
     is left behind and the program continues after the closing brace.
  3. `cout << i << endl;` prints the current value of i on its own line.
  4. `i++` adds 1 to i, so i changes from 1 to 2.
  5. Go back to step 2 and repeat until i is 6 and `i <= 5` is false.
  6. That gives 5 iterations, because i takes the values 1, 2, 3, 4, 5.
  ============================================================
*/

#include <iostream>
/*
  <iostream> is a HEADER FILE. It lends us the tools for talking to the
  screen: `cout` (console output), `endl` (end line) and `cin` (keyboard
  input). Without this line the compiler reports "cout was not declared",
  because C++ itself has no printing - every facility comes from a library.
*/

using namespace std;
/*
  `std` is the name of the STANDARD library, which is where cout and endl
  live. A NAMESPACE is just a labelled box that groups names together so
  that two different libraries cannot collide over the same word.
  `std::cout` means "the cout that lives inside the std box"; the `::` is
  called the scope resolution operator and means "inside".
  `using namespace std;` says "stop making me type std:: in front of every
  name" - which is why we can write plain `cout` below.
*/

int main() {
/*
  `main` is the ENTRY POINT: the first function the operating system calls
  when the program starts.
  `int` is the RETURN TYPE - when main finishes it hands a whole number back
  to the operating system.
  `()` means main takes NO parameters (nothing is passed into it).
  The `{ }` braces are the BODY: every instruction between them runs, top
  to bottom, one at a time.
*/

    /*
      ------------------------------------------------------------
      THE LOOP
      ------------------------------------------------------------
    */
    for (int i = 1; i <= 5; i++) {
    /*
          |   |       |   |
          |   |       |   +-- ) closes the header
          |   |       +------ UPDATE:      i++  (after every pass)
          |   +-------------- CONDITION:   i <= 5 (before every pass)
          +------------------ INITIALIZATION: int i = 1 (once, ever)

      `for` is a KEYWORD - a word reserved by the language, so you may not
      use `for` as a variable name. The ( ... ) part is called the loop
      HEADER and it always holds exactly THREE parts, separated by TWO
      semicolons, ALWAYS in this order: start, condition, update.

      PART 1 - INITIALIZATION:  int i = 1
        `int`  is the DATA TYPE. It can only hold whole numbers
               (..., -2, -1, 0, 1, 2, ...) and never a decimal like 2.5.
        `i`    is the VARIABLE NAME, and we choose it. `i` is short for
               "index" (the counter of a loop). Other names work too: n,
               count, k, number.
        `=`    is ASSIGNMENT: store the value on the RIGHT in the variable
               on the LEFT. So i is given the value 1.
        This part runs EXACTLY ONCE, before the very first condition test.
        The loop is never re-initialised, which is why the declaration is
        usually written HERE - it keeps i's scope limited to this loop.

      PART 2 - CONDITION:  i <= 5
        Read it as a QUESTION: "is i <= 5?"
          - TRUE  -> run the body, then run the update, then ask again.
          - FALSE -> skip the body and LEAVE the loop. Control jumps to the
                    first statement AFTER the closing brace.
        This test is the ONLY exit door out of the loop. If the condition
        stays true forever, the loop never ends (an infinite loop).
        `<=` means "less than OR equal to", so the value 5 itself is still
        allowed through. Using `<` instead would print only 1 to 4.

      PART 3 - THE BODY  { cout << i << endl; }
        This is the repeated work. It sits inside { } braces.
        `cout` = console output; it sends text to the screen.
        `<<`   = the stream insertion operator. Point the arrows in the
                 direction the data travels: into cout. They can be
                 chained, meaning "send this, then that, then that".
        `i`    = the number the loop variable currently holds.
        `endl` = "end line" - it prints a newline so the next output begins
                 on the next row down.
    */
        cout << i << endl;
        // Print whatever i holds right now, then move to a new line.

        /*
          PART 3 CONTINUED - THE UPDATE:  i++
          The update is NOT after the closing brace - it is the third part
          of the header, inside the ( ). This is the number one exam error:
          students write the update below the loop. That is wrong.
          `i++` is the INCREMENT operator: "add 1 to i".
          It is shorthand for  i = i + 1;  and for  i += 1;
          It runs AFTER the body has finished, once per repetition - not
          before the first test, and not after the loop has ended.
        */
    }

    /*
      AFTER THE LOOP
        The closing brace `}` marks the end of the loop body. The statement
        after it is the first code to run once the loop is finished.
        IMPORTANT: `i` does NOT exist here. It was declared inside the loop
        header, so it was destroyed at the closing brace. Trying to print it
        now is a compile error. See 08_multiple_variables.cpp.
    */

    /*
      ------------------------------------------------------------
      TRACE TABLE - follow the loop with a pen on paper
      ------------------------------------------------------------
      TRACE TABLE
      +-----------+------------+----------------+-----------+
      | Iteration | i at start | condition i<=5? | Output    |
      +-----------+------------+----------------+-----------+
      |     1     |     1      |  1 <= 5  true  |    1      |
      +-----------+------------+----------------+-----------+
      |     2     |     2      |  2 <= 5  true  |    2      |
      +-----------+------------+----------------+-----------+
      |     3     |     3      |  3 <= 5  true  |    3      |
      +-----------+------------+----------------+-----------+
      |     4     |     4      |  4 <= 5  true  |    4      |
      +-----------+------------+----------------+-----------+
      |     5     |     5      |  5 <= 5  true  |    5      |
      +-----------+------------+----------------+-----------+
      |     6     |     6      |  6 <= 5  FALSE | STOP     |
      +-----------+------------+----------------+-----------+

      Row 6 is where the loop dies. The body ran 5 times, not 6: the failed
      test does not print anything.

      THE 10-SECOND EXAM METHOD (how to count iterations fast)
        1. What is the FIRST value of the counter?   (from the start part)
        2. What is the LAST value allowed?           (from the condition)
        3. How much does the counter change each pass? (from the update)
        4. Going UP:   count = (last - first) / step + 1
           Going DOWN: count = (first - last) / step + 1
        Here: (5 - 1) / 1 + 1 = 4 + 1 = 5 iterations. Correct.

      THE COMMON TRAP IN THIS FILE
        Writing `i < 5` instead of `i <= 5` prints only 1 2 3 4 and runs 4
        times. `<` excludes the limit; `<=` includes it. Read the symbol
        aloud as English - "less than 5" means 5 is not allowed in.
    */

    return 0;
    /*
      `return 0;` ends main immediately and hands the value 0 back to the
      operating system. 0 conventionally means "everything worked". The
      number rarely matters on a modern system, but every exam answer
      expects to see it, and it is good habit to always write it.
    */
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: How many times does the loop body run?                      -> 5 times
  Q2: What is the value of i the last time the condition is tested? -> 6
  Q3: Which header part runs exactly once?                        -> the initialization `int i = 1`
  Q4: List the execution order in one line.                        -> init, test, body, update, test, body, update, ...
  Q5: If the condition were `i < 5` instead, what changes?         -> 4 iterations, prints 1 2 3 4 only
  Q6: Is `i` usable after the closing brace?                       -> no, it was scoped to the loop
  ============================================================
*/
