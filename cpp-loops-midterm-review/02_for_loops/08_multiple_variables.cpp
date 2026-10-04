/*
  ============================================================
  PROGRAM: Multiple Variables in and around a for Loop
  TOPIC: for loops - two counters, meeting counters, counters and sums
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - How to use TWO separate counters inside one for loop.
  - How to make two counters walk towards each other until they meet.
  - How a counter (how many times) and an accumulator (running total) are
    used together.
  - SCOPE: a variable declared inside the loop header does not exist after
    the loop, while a variable declared before the loop does.

  EXPECTED OUTPUT:
  (a) Two separate counters updated inside one loop:
  step 1: i = 2, j = 110
  step 2: i = 3, j = 120
  step 3: i = 4, j = 130

  (b) i and j moving towards each other:
  start  : i = 1, j = 5
  step 1 : i = 2, j = 4
  step 2 : i = 3, j = 3
  They met in the middle at 3.

  (c) A counter and an accumulator used together:
  add 1 -> total 1
  add 2 -> total 3
  add 3 -> total 6
  add 4 -> total 10
  add 5 -> total 15
  Final total = 15
  (d) After the loop sum is still 15, because it was declared before it.

  IMPORTANT SYNTAX:
  int i = 1;              -> declare a variable that outlives the loop
  for (int step = 1; ...) -> the loop variable lives and dies with the loop
  sum = sum + i;          -> accumulate: keep a running total
  count++;                -> count: add one to a tally
  if (i >= j) { ... }     -> compare two variables to decide when to stop
  i = i + 1;  j = j + 1;  -> two separate statements on two separate lines

  STEP-BY-STEP EXPLANATION:
  1. Part (a) declares two counters, i and j, BEFORE the loop, then updates
     both of them inside the body. Both survive the loop, so they can be
     printed afterwards.
  2. Part (b) makes i grow and j shrink. Each pass moves them one place
     closer until they are equal, which is how you find a MIDDLE point.
  3. Part (c) pairs a counter (i, which walks 1 to 5) with an accumulator
     (sum, which collects a running total). The counter decides HOW MANY
     passes happen; the accumulator decides WHAT is remembered.
  4. Part (d) proves the scope rule: sum was declared before its loop, so
     it still holds 15 afterwards. The loop variable i from part (c) is
     gone and cannot be printed - trying to do so is a compile error.
  5. NOTE ON STYLE: this file never joins two statements with a comma in
     the loop header. Every extra statement gets its own line and its own
     semicolon. That is slower to write but impossible to misread.
  ============================================================
*/

#include <iostream>
/*
  The single header this project needs. It provides `cout` for output and
  `endl` for a newline. C++ itself has no printing facility, so this line
  must appear before any use of `cout`.
*/

using namespace std;
/*
  The standard tools are grouped in a namespace named `std`, and the `::`
  symbol means "inside", so `std::cout` reads "the cout inside std".
  `using namespace std;` is the shortcut that saves us typing `std::`
  before every single name.
*/

int main() {
/*
  `main` is the ENTRY POINT: the first code the operating system runs.
  `int` is the return type - a whole number handed back at the end.
  `()` means no parameters. `{ }` delimits the BODY of the function.
*/

    /*
      ============================================================
      (a) TWO SEPARATE COUNTERS, BOTH UPDATED IN ONE LOOP
      ============================================================
    */
    int i = 1;
    int j = 100;
    /*
      Two declarations, on two separate lines, each with its own semicolon.
      `int` means whole numbers only. `i` starts at 1, `j` starts at 100.

      WHY DECLARE THEM OUT HERE AND NOT IN THE HEADER?
        Because anything declared inside `for ( ... )` is destroyed when
        the loop ends. These two need to outlive the loop, so they live in
        main's body, where they are visible to the whole function.
    */

    cout << "(a) Two separate counters updated inside one loop:" << endl;
    // A label on its own line, so part (a) is easy to find in the output.

    for (int step = 1; step <= 3; step++) {
    /*
          |          |          |
          |          |          +-- UPDATE: the loop variable of THIS loop
          |          +------------- CONDITION: three passes only
          +------------------------ START: the pass number, 1 to 3
    */
        /*
          `step` is the loop variable. It counts how many times we have
          gone round. It is a THIRD variable, separate from i and j.

          The loop condition says nothing at all about i or j. It only
          knows about step. That is normal and it is safe: the loop repeats
          three times, and each pass happens to advance both i and j.
        */

        i = i + 1;
        // i grows by 1 each pass: 1 -> 2 -> 3 -> 4.
        j = j + 10;
        // j grows by 10 each pass: 100 -> 110 -> 120 -> 130.
        // Two separate statements, two separate lines, two semicolons.

        cout << "step " << step << ": i = " << i << ", j = " << j << endl;
        /*
          One line of output per pass. Chaining `<<` like this just means
          "print this, then that, then that". The comma between i and j is
          inside a STRING LITERAL in double quotes, so it is printed as a
          character and is not the comma operator.
        */
    }

    cout << endl;
    // A blank line, so part (b) starts clearly below part (a).

    /*
      ============================================================
      (b) TWO COUNTERS MOVING TOWARDS EACH OTHER
      ============================================================
      A very common exam pattern: one value climbs from the low end while
      another falls from the high end. When they become equal, they have
      met in the middle.
    */

    i = 1;
    j = 5;
    /*
      Re-assignment. `i` and `j` already exist, so the keyword here would
      be wrong: writing `int i = 1;` a second time here would create a
      brand new variable that shadows the first one, and the compiler
      would warn about it. Plain `i = 1;` simply reuses the old variable.
    */

    cout << "(b) i and j moving towards each other:" << endl;
    // Label for the second pattern.

    cout << "start  : i = " << i << ", j = " << j << endl;
    // Print the starting pair before anything changes, so the reader can
    // see both ends of the journey.

    for (int step = 1; step <= 2; step++) {
        /*
          Two passes are enough for 1 and 5 to meet at 3. With a bigger
          gap you would need more passes - which is exactly why the limit
          in the condition has to match the distance between the ends.
        */
        i = i + 1;
        // The low end climbs: 1 -> 2 -> 3.
        j = j - 1;
        // The high end falls: 5 -> 4 -> 3.
        cout << "step " << step << " : i = " << i << ", j = " << j << endl;
        // Note the extra space after "step " in this label so the three
        // lines above and below it line up in the terminal.
    }

    if (i >= j) {
    /*
      |  |
      |  +-- `>=` means "greater than or equal to", so this also covers
      |      the case where they crossed each other rather than meeting
      |      exactly
      +----- i, the counter that climbed
    */
        /*
          Two VARIABLES on both sides of the comparison. This is the moment
          the loop is allowed to stop, and the test needs both of them.
          With only one counter you could never express "they met".
        */
        cout << "They met in the middle at " << i << "." << endl;
        /*
          The meeting point is 3. If they had crossed over instead of
          landing on the same number, `i` would be the larger of the two
          and reporting it as "the middle" would still be reasonable.
        */
    }

    cout << endl;
    // Another blank line to separate the parts visually.

    /*
      ============================================================
      (c) A COUNTER AND AN ACCUMULATOR TOGETHER
      ============================================================
      COUNTER      - counts passes:  "how many times have we been round?"
      ACCUMULATOR  - collects a value: "what have we added up so far?"

      The counter is the loop variable `i`, declared in the header, which
      is the normal place for it. The accumulator `sum` MUST be declared
      outside the loop, because it has to remember its value from one pass
      to the next AND be readable after the loop finishes.
    */

    int sum = 0;
    /*
      The accumulator. `= 0` is essential - adding to an uninitialised
      variable would use whatever junk happened to be in memory, and the
      answer would be meaningless. Always start an accumulator at 0.
    */

    cout << "(c) A counter and an accumulator used together:" << endl;
    // Label for the third pattern.

    for (int i = 1; i <= 5; i++) {
    /*
          |        |
          |        +-- UPDATE: the counter that decides the pass count
          +----------- START: the counter that supplies each number
    */
        /*
          NOTE THE SHADOWING: this `i` is a NEW variable, unrelated to the
          `i` declared in part (a). Two variables may share a name as long
          as they do not live at the same time. When this loop ends, this
          `i` is destroyed and the outer `i` becomes visible again.

          A WORD ON WRITING BOTH ON ONE LINE. It is legal to write
              for (int i = 1, sum = 0; i <= 5; i++)
          where the comma between `i = 1` and `sum = 0` separates two
          DECLARATIONS inside one `int`. That is a completely different
          thing from the comma OPERATOR, which squeezes two whole
          statements into one slot. Beginners mix the two up constantly,
          so this project always uses one declaration per line.
        */

        sum = sum + i;
        /*
          The accumulator's one job. Read it as: "the new sum is the old
          sum plus i". Written the other way round, `sum + i = sum`, the
          left of `=` must be a variable you can store into, so it would be
          a syntax error.
        */

        cout << "add " << i << " -> total " << sum << endl;
        // Print the running total after every addition, which makes the
        // accumulation visible step by step: 1, 3, 6, 10, 15.
    }

    cout << "Final total = " << sum << endl;
    // The answer, read AFTER the loop. This line only compiles because sum
    // was declared outside the braces.

    /*
      ============================================================
      (d) THE SCOPE RULE, PROVED
      ============================================================
    */
    cout << "(d) After the loop sum is still " << sum << ", because it was declared before it." << endl;
    /*
      `sum` still holds 15 here, one line after its loop has finished.

      SCOPE, DEFINED PLAINLY: every variable has a LIFETIME, and braces
      control it. A variable exists from the line it is declared until the
      closing brace of the block it was declared in.

        Declared in main's body -> alive until main's closing brace.
        Declared in a for header -> alive only until the loop ends.
        Declared inside the loop's { } -> alive only inside the loop.

      TRYING TO USE A DEAD VARIABLE. Uncommenting the two lines below
      gives a compile error, because `i` from loop (c) no longer exists:

          cout << "i is now " << i << endl;
          error: 'i' was not declared in this scope

      The same error appears if you use the loop variable in the middle of
      the program by mistake. The rule to remember: if you want a variable
      after the loop, declare it BEFORE the loop.

      A NASTY RELATED CASE, shown for understanding and never run:
          for (int n = 1; n <= 3; n++) {
              int extra = n * 10;   // extra dies with each pass
          }
          cout << extra;            // error: 'extra' was not declared
      A variable declared INSIDE the braces is thrown away and rebuilt on
      every pass, so it can never carry anything out of the loop.
    */

    /*
      ------------------------------------------------------------
      TRACE TABLE
      ------------------------------------------------------------
      TRACE TABLE
      Part (a): i and j both move on every pass
      +-----------+------------+--------+-----------+---------------+
      | Iteration | step       | i      | i update  | j and update  |
      +-----------+------------+--------+-----------+---------------+
      |     1     | 1 <= 3 T  | 1      | 1+1 = 2   | 100+10 = 110  |
      +-----------+------------+--------+-----------+---------------+
      |     2     | 2 <= 3 T  | 2      | 2+1 = 3   | 110+10 = 120  |
      +-----------+------------+--------+-----------+---------------+
      |     3     | 3 <= 3 T  | 3      | 3+1 = 4   | 120+10 = 130  |
      +-----------+------------+--------+-----------+---------------+
      |     4     | 4 <= 3 F  | 4      | no update | STOP          |
      +-----------+------------+--------+-----------+---------------+

      Part (b): i climbs while j falls
      +-----------+------------+--------+---------+-------------------+
      | Iteration | step       | i      | j       | Distance left    |
      +-----------+------------+--------+---------+-------------------+
      |     1     | 1 <= 2 T  | 1      | 5       | j - i = 4        |
      +-----------+------------+--------+---------+-------------------+
      |     2     | 2 <= 2 T  | 2      | 4       | j - i = 2        |
      +-----------+------------+--------+---------+-------------------+
      |     3     | 3 <= 2 F  | 3      | 3       | j - i = 0 (met)  |
      +-----------+------------+--------+---------+-------------------+

      Part (c): the counter and the accumulator side by side
      +-----------+------------+------------------+-------------------+
      | Iteration | i at start | sum BEFORE        | sum AFTER         |
      +-----------+------------+------------------+-------------------+
      |     1     |     1      | 0                | 0 + 1 = 1         |
      +-----------+------------+------------------+-------------------+
      |     2     |     2      | 1                | 1 + 2 = 3         |
      +-----------+------------+------------------+-------------------+
      |     3     |     3      | 3                | 3 + 3 = 6         |
      +-----------+------------+------------------+-------------------+
      |     4     |     4      | 6                | 6 + 4 = 10        |
      +-----------+------------+------------------+-------------------+
      |     5     |     5      | 10               | 10 + 5 = 15       |
      +-----------+------------+------------------+-------------------+
      |     6     |     6      | 15               | loop stops here   |
      +-----------+------------+------------------+-------------------+

      THE 10-SECOND EXAM METHOD
        1. List EVERY variable the loop touches: the loop variable, any
           variable updated in the body, and any accumulator.
        2. For each one, ask: was it declared before the loop or inside it?
        3. Anything declared before is readable afterwards. Anything
           declared inside is gone. That single question answers every
           scope question in the exam.

      THE COMMON TRAP IN THIS FILE
        Declaring a variable inside the header when it is needed later:
            for (int n = 1; n <= 5; n++) { sum = sum + n; }
            cout << n;          // error: 'n' was not declared in this scope
        Fix: move `int n = 1;` above the loop and leave the header starting
        with a plain semicolon: `for (; n <= 5; n++)`. A quick way to spot
        the bug before compiling is to ask, for every printed variable,
        "which line declared it, and is it still inside those braces?"
    */

    return 0;
    // Leaves main and hands 0 (success) back to the operating system. Any
    // code after this line would never be reached.
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: How many passes does part (a) make, and what is i at the end?  -> 3 passes; i = 4 and j = 130
  Q2: Which variable decides when the loop in part (a) stops?         -> `step`, the loop variable, NOT i or j
  Q3: What are i and j after the loop in part (b)?                   -> i = 3 and j = 3, they met in the middle
  Q4: Why is the test `if (i >= j)` needed in part (b)?              -> to find out when the two moving counters have met; one counter alone could not say it
  Q5: What is the value of sum after part (c)?                       -> 15
  Q6: Why must `sum` be declared BEFORE the loop?                    -> so it keeps its value between passes and can still be read after the loop ends
  Q7: Can you print `i` after the loop in part (c)?                  -> no, it is destroyed at the loop's closing brace: error: 'i' was not declared in this scope
  Q8: What is an accumulator, in one sentence?                       -> a variable declared before the loop that is updated inside it to collect a running result such as a total
  Q9: Is `for (int i = 1, sum = 0; i <= 5; i++)` legal?             -> yes, the comma separates two declarations inside one `int`; beginners should still use one declaration per line
  ============================================================
*/
