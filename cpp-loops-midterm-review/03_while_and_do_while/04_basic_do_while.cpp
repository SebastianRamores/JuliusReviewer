/*
  ============================================================
  PROGRAM: Basic do...while Loop
  TOPIC: do...while loops - a loop whose body always runs at least once
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - The shape of a do...while loop and, crucially, WHERE the semicolon
    goes: after the closing parenthesis, not after the closing brace.
  - That the condition is tested at the BOTTOM of the loop, so the body
    is always carried out at least once.
  - A countdown, which is the everyday situation a do...while suits.
  - A value-checking loop: lowering a number until it is small enough.
  - Why `do` is a keyword you may not use as a variable name.

  EXPECTED OUTPUT:
  === Part 1: do...while printing 1 to 5 ===
  1
  2
  3
  4
  5
  === Part 2: a countdown that must run at least once ===
  Starting countdown from 3
  3
  2
  1
  Liftoff!
  === Part 3: lowering a value until it is small enough ===
  Checking 5 against the limit of 2
  5 is too big, reducing by 2
  3 is too big, reducing by 2
  The accepted value is 1
  Yes, 1 is within the limit of 2.

  IMPORTANT SYNTAX:
  do { body } while (condition);  -> do the body first, THEN test, then repeat
  do                              -> a keyword: the body always runs once
  while (i <= 5);                 -> the test; note the semicolon after the )
  if (value > limit) { ... }       -> run the block only when value is too big
  count--;                         -> take 1 away (shorthand for count = count - 1;)

  STEP-BY-STEP EXPLANATION:
  1. Part 1 jumps straight into the body, prints 1, then adds 1 and tests
     `i <= 5`. It keeps going until i reaches 6, when 6 <= 5 is false.
  2. Part 2 prints the countdown before testing, so 3 is printed even if
     the starting value had already been 0. That "at least once" promise
     is the whole reason this loop type exists.
  3. Part 3 checks a value and shrinks it while it is too big. It stops as
     soon as the value is small enough, then a final if confirms it.
  4. Compare with a while loop, which would test first and so might never
     run the body at all. See 05_do_while_runs_once.cpp for the proof.
  ============================================================
*/

#include <iostream>
/*
  <iostream> is the header file that gives C++ its ability to talk to the
  terminal: it supplies `cout` for output, `cin` for input and `endl` for
  ending a line. The language itself can only calculate and compare, so every
  facility for showing a result is borrowed from a library - and this line
  invites that library in. Without it the compiler says cout is not declared.
*/

using namespace std;
/*
  A NAMESPACE is a labelled box that groups related names so two libraries
  cannot fight over the same word. `std` is the box belonging to the C++
  STANDARD library, where `cout` and `endl` live, so the full name of our
  printing command is `std::cout`. The `::` between them is the SCOPE
  RESOLUTION OPERATOR and means "inside". `using namespace std;` says "the
  names I write come from std", which is why plain `cout` works below.
*/

int main() {
/*
  `main` is the ENTRY POINT: the first function the operating system runs
  when the program starts. `int` is its RETURN TYPE, so when main finishes
  it hands a whole number back as an exit status. `()` is the parameter list
  and it is empty. The `{ }` braces are the BODY - run top to bottom.
*/

    /*
      ================================================================
      PART 1 - THE SIMPLEST do...while
      ================================================================
    */
    cout << "=== Part 1: do...while printing 1 to 5 ===" << endl;

    int i = 1;

    /*
      do { body } while ( condition );
                         ^ SEMICOLON - do not forget it

      `do` is a KEYWORD reserved by the language, so it can never be a
      variable name. It marks the START of the loop, and its body is
      whatever sits between the braces that follow it.
    */
    do {
        // The BODY runs first, before anything has been tested.
        cout << i << endl;

        // `i++` is the INCREMENT operator, shorthand for `i = i + 1;`.
        i++;
    }

    /*
      Now, and only now, the condition is examined. TRUE sends control
      back up to the word `do`; FALSE lets the program fall through to the
      next line. Testing at the bottom is what makes the body run at least
      once - the exact opposite of a plain while loop, which tests at the
      top and may therefore run the body zero times.
    */
    while (i <= 5);

    /*
      ================================================================
      PART 2 - A COUNTDOWN, THE CLASSIC USE FOR do...while
      ================================================================
    */
    cout << "=== Part 2: a countdown that must run at least once ===" << endl;

    int countdown = 3;
    cout << "Starting countdown from " << countdown << endl;

    do {
        cout << countdown << endl;

        /*
          `countdown--` is the DECREMENT operator: take 1 away. It is
          identical to `countdown = countdown - 1;` or `countdown -= 1;`.
          It is what eventually makes `countdown > 0` become false.
        */
        countdown--;
    } while (countdown > 0);

    /*
      Only reachable once the loop has finished. The count below is 0, so
      the final test `0 > 0` failed and the body was skipped - meaning the
      body can run zero times at the END, even though it ran at least once
      at the START. The promise is only about the first pass.
    */
    cout << "Liftoff!" << endl;

    /*
      ================================================================
      PART 3 - CHECKING A VALUE OVER AND OVER
      ================================================================
    */
    cout << "=== Part 3: lowering a value until it is small enough ===" << endl;

    /*
      A fixed value stands in for one the user might have typed. Nothing is
      read from the keyboard here, so the program always does the same
      thing and can be marked by hand.
    */
    int candidate = 5;
    int limit = 2;
    cout << "Checking " << candidate << " against the limit of " << limit << endl;

    do {
        /*
          `if (candidate > limit)` asks "is candidate greater than limit?".
          `>` is the "greater than" comparison. TRUE runs the block, FALSE
          skips it entirely. Nesting a condition inside a loop is one of
          the four skills this course is built on.
        */
        if (candidate > limit) {
            cout << candidate << " is too big, reducing by 2" << endl;

            /*
              `candidate -= 2` is compound subtraction, shorthand for
              `candidate = candidate - 2;`. This is the line that moves the
              value towards the point where the loop can stop.
            */
            candidate -= 2;
        }
    } while (candidate > limit);

    // 5 -> 3 -> 1. On each pass the value was still too big, and after the
    // second pass 1 > 2 is false, so the loop ends with a usable value.
    cout << "The accepted value is " << candidate << endl;

    // A final `if / else` checks the result and reports on it. `if` has no
    // condition of its own else: `else` means "and if not".
    if (candidate <= limit) {
        cout << "Yes, " << candidate << " is within the limit of " << limit << "." << endl;
    } else {
        cout << "No acceptable value was found." << endl;
    }

    /*
      ================================================================
      TRACE TABLE - PART 1, the simplest do...while
      ================================================================
      +-----------+------------+----------------+--------+
      | Iteration | i at start | Test: i <= 5   | Output |
      +-----------+------------+----------------+--------+
      | 1         | 1          | 1 <= 5   TRUE  | 1      |
      | 2         | 2          | 2 <= 5   TRUE  | 2      |
      | 3         | 3          | 3 <= 5   TRUE  | 3      |
      | 4         | 4          | 4 <= 5   TRUE  | 4      |
      | 5         | 5          | 5 <= 5   TRUE  | 5      |
      | 6         | 6          | 6 <= 5   FALSE | (none) |
      +-----------+------------+----------------+--------+

      Identical to the while-loop trace in 01_basic_while.cpp, and that is
      the point: when the condition is true to begin with, the two loop
      types behave the same. They only part company when the condition is
      FALSE from the start - see the next file.

      ================================================================
      TRACE TABLE - PART 3, shrinking a value
      ================================================================
      +-----------+-----------+--------------------+-----------------+--------+
      | Iteration | candidate | Test: cand > limit | Body action     | Output |
      +-----------+-----------+--------------------+-----------------+--------+
      | 1         | 5         | 5 > 2     TRUE     | print, then 5-2 | line 1 |
      | 2         | 3         | 3 > 2     TRUE     | print, then 3-2 | line 2 |
      | 3         | 1         | 1 > 2     FALSE    | body not run    | (none) |
      +-----------+-----------+--------------------+-----------------+--------+

      Note that the test in this table is the one at the BOTTOM, so the
      value printed on a row is always the value the row started with.

      THE COMMON TRAP IN THIS FILE
        Two mistakes, both made in every exam sitting:
          1. Writing `} while (i <= 5)` with no semicolon. That is a COMPILE
             ERROR, because the grammar demands the `;` here and nowhere
             else in the loop.
          2. Putting the semicolon somewhere else by habit, for instance
             `while (i <= 5); { ... }` from copying a while loop. In a do...
             while the braces belong to the `do`, above the test, and the
             semicolon belongs after the closing parenthesis.
    */

    return 0;
    /*
      `return 0;` ends main straight away and hands 0 back to the operating
      system. Zero is the conventional code for "success": the program ran
      to the end without an error. Exams expect to see it, so it is always
      written as the last statement of main.
    */
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: Where is the condition tested in a do...while loop?  -> at the bottom, after the body has already run once
  Q2: What is the smallest number of times the body can run?  -> once, even when the condition is false from the very start
  Q3: What does Part 2 print, and what is countdown at the end?  -> 3 2 1 then Liftoff, and countdown is 0
  Q4: How many passes does Part 3 make before it stops?  -> 2, because 5 -> 3 -> 1 and 1 > 2 is false
  Q5: Which semicolon must not be forgotten here, and where?  -> the one after `while (i <= 5)` - omit it and it will not compile
*/
