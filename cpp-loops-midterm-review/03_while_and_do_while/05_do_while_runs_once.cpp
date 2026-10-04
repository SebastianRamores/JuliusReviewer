/*
  ============================================================
  PROGRAM: A do...while Loop ALWAYS Runs Its Body at Least Once
  TOPIC: the one big difference between do...while and while
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - THE CENTRAL FACT: a do...while loop runs its body one time at least,
    even when the condition is false from the very first test.
  - Proof by comparison: the SAME false condition in a plain while loop
    runs the body ZERO times.
  - What happens when the condition is true to begin with - the loop then
    behaves exactly like a while loop.
  - Where the compulsory semicolon goes, and what a stray one does.

  EXPECTED OUTPUT:
  === Example A: the condition is FALSE right from the start ===
  Body pass number 1 ran, even though the test will fail.
  do...while body ran 1 time(s).
  === Example B: the condition is TRUE to begin with ===
  Body pass number 1 ran.
  Body pass number 2 ran.
  Body pass number 3 ran.
  do...while body ran 3 time(s).
  === Example C: the same test in a plain while loop ===
  while body ran 0 time(s).
  === Example D: the semicolon after while(...) is compulsory ===
  This line printed because the semicolon after while is present.
  The do...while above compiled and ran exactly once.
  === SUMMARY ===
  do...while with a false condition runs 1 time.
  while with the same false condition runs 0 times.
  Confirmed: the two loop types disagree when the condition starts false.

  IMPORTANT SYNTAX:
  do { body } while (condition);  -> run the body FIRST, then test, then repeat
  while (condition) { body }       -> test FIRST, so the body may run 0 times
  while (up <= 0) { ... }         -> a false test, so this body never runs
  a != b                          -> "is a NOT equal to b?"

  STEP-BY-STEP EXPLANATION:
  1. Example A sets up a condition that is FALSE before the loop starts.
     The body still prints once, then the failing test ends the loop.
  2. Example B uses a condition that is TRUE to begin with, so the loop
     runs as many times as it would in a while loop - three of them.
  3. Example C rewrites Example A as a plain while loop. The test comes
     first and is false, so the body is skipped completely and the pass
     counter stays at 0. The line inside the braces never prints.
  4. Example D shows the required semicolon after the closing parenthesis.
  5. The summary compares the two counters with `!=`, which is true, so
     the disagreement is confirmed out loud.
  ============================================================
*/

#include <iostream>
/*
  <iostream> is the header file that gives C++ its ability to talk to the
  terminal: it supplies `cout` for output, `cin` for input and `endl` for
  ending a line. The language itself can only calculate and compare, so every
  facility for showing a result comes from a library - and this line invites
  that library in. Without it the compiler says cout is not declared.
*/

using namespace std;
/*
  A NAMESPACE is a labelled box that groups related names so two libraries
  cannot fight over the same word. `std` is the box belonging to the C++
  STANDARD library, where `cout` and `endl` live, so the full name of our
  printing command is `std::cout`. The `::` is the SCOPE RESOLUTION OPERATOR
  and means "inside". `using namespace std;` says "the names I write come
  from std", which is why plain `cout` works below.
*/

int main() {
/*
  `main` is the ENTRY POINT: the first function the operating system runs
  when the program starts. `int` is its RETURN TYPE, so when main finishes
  it hands a whole number back as an exit status. `()` is the parameter list
  and it is empty. The `{ }` braces are the BODY, run top to bottom.
*/

    /*
      ================================================================
      EXAMPLE A - A CONDITION THAT IS FALSE FROM THE START
      ================================================================
    */
    cout << "=== Example A: the condition is FALSE right from the start ===" << endl;

    // limit is 0 and attempts starts at 0, so `attempts < limit` asks
    // "is 0 less than 0?" - FALSE. Nothing is allowed through.
    int attempts = 0;
    int limit = 0;

    /*
      The pass counter exists so the answer can be printed as a number at
      the end. It is a COUNTER, not an accumulator: it adds 1 each pass
      instead of folding values together.
    */
    int passesA = 0;

    do {
        // Reaching this line at all is the proof: a while loop would have
        // tested first, found the condition false, and skipped past here.
        cout << "Body pass number " << passesA + 1 << " ran, even though the test will fail." << endl;

        // `++` is the INCREMENT operator: add 1. `passesA + 1` in the print
        // is plain addition, which is why it shows 1 on the first pass.
        passesA++;
        attempts++;
    } while (attempts < limit);

    cout << "do...while body ran " << passesA << " time(s)." << endl;

    /*
      ================================================================
      EXAMPLE B - A CONDITION THAT IS TRUE TO BEGIN WITH
      ================================================================
    */
    cout << "=== Example B: the condition is TRUE to begin with ===" << endl;

    int up = 1;
    int passesB = 0;
    do {
        cout << "Body pass number " << passesB + 1 << " ran." << endl;
        passesB++;
        up++;
    } while (up <= 3);

    /*
      Three passes: 1, 2, 3 are each allowed in, and by the time the test
      runs again up is 4, so `4 <= 3` is false - exactly how a while loop
      would behave with the same values.
    */
    cout << "do...while body ran " << passesB << " time(s)." << endl;

    /*
      ================================================================
      EXAMPLE C - THE SAME FALSE CONDITION IN A PLAIN while LOOP
      ================================================================
    */
    cout << "=== Example C: the same test in a plain while loop ===" << endl;

    int up2 = 1;
    int passesC = 0;
    /*
      `up2 <= 0` is "is 1 less than or equal to 0?" - false. A while loop
      tests BEFORE running the body, so control never enters the braces and
      the line inside is never reached.
    */
    while (up2 <= 0) {
        cout << "This line NEVER prints." << endl;
        passesC++;
        up2++;
    }

    // Zero. That is the whole difference in one number: the same false
    // condition gave one pass in Example A and none at all here.
    cout << "while body ran " << passesC << " time(s)." << endl;

    /*
      ================================================================
      EXAMPLE D - THE COMPULSORY SEMICOLON
      ================================================================
    */
    cout << "=== Example D: the semicolon after while(...) is compulsory ===" << endl;

    int mandatory = 0;
    do {
        cout << "This line printed because the semicolon after while is present." << endl;
        mandatory++;
    } while (mandatory < 0);
    /*
          ^ THE SEMICOLON IS NOT OPTIONAL. A do...while is the ONLY loop in
          C++ that ends with one; delete it and the compiler stops with
          "expected ';' after while statement". It goes after the closing
          parenthesis, NOT after the brace.
    */

    /*
      By contrast an EXTRA semicolon after a finished do...while is
      harmless, because a lone `;` is just an empty statement that does
      nothing. It is only dangerous in a while or for HEADER:

          while (up2 <= 0) ;        <- the ';' becomes the whole body
          { ...print something... } <- this block then runs ONCE, outside
                                       the loop, with no test at all

      (shown as a comment on purpose: the empty body never changes up2, so
      that version would never end and the program would hang.)
    */
    int harmless = 3;
    do {
        harmless--;
    } while (harmless > 0)
        ;   // an extra `;` here is simply an empty statement - harmless

    cout << "The do...while above compiled and ran exactly once." << endl;

    /*
      ================================================================
      SUMMARY - THE DIFFERENCE STATED AS DATA
      ================================================================
    */
    cout << "=== SUMMARY ===" << endl;
    cout << "do...while with a false condition runs 1 time." << endl;
    cout << "while with the same false condition runs 0 times." << endl;

    /*
      `!=` is the NOT-EQUAL comparison: it asks "is passesA different from
      passesC?". It is the mirror image of `==`, which asks "are these two
      the same?". One equals sign would be a mistake here - `passesA =
      passesC` asks nothing at all, it overwrites passesA with passesC.
    */
    if (passesA != passesC) {
        cout << "Confirmed: the two loop types disagree when the condition starts false." << endl;
    }

    /*
      ================================================================
      TRACE TABLE - all four examples in one table
      ================================================================
      +---------+---------------+-----------------+--------+-----------+
      | Example | Test at start | Test at the end | Passes | Body ran? |
      +---------+---------------+-----------------+--------+-----------+
      | A       | 0 < 0 FALSE   | 1 < 0 FALSE     | 1      | YES       |
      | B       | 1 <= 3 TRUE   | 4 <= 3 FALSE    | 3      | YES       |
      | C       | 1 <= 0 FALSE  | (never tested)  | 0      | NO        |
      | D       | 0 < 0 FALSE   | 1 < 0 FALSE     | 1      | YES       |
      +---------+---------------+-----------------+--------+-----------+

      EXAMPLES A, B AND D ARE do...while LOOPS, so "Body ran?" says YES even
      though the starting test is FALSE. Example C is a plain while loop with
      the very same false test, and its body never ran. That one row is the
      entire lesson of this file.

      THE COMMON TRAP IN THIS FILE
        Reaching for a do...while "just in case", then being surprised when
        the body fires once with values you never wanted it to see. Choose:
          while       -> the test must pass first; 0 passes is fine.
          do...while  -> the body MUST happen at least once. Perfect for a
                        menu, a "press a key to continue" prompt, or a
                        countdown. Wrong for anything where a condition has
                        to be met before work starts.
        Forgetting the trailing semicolon also turns a five-line loop into
        a compile error.
    */

    return 0;
    /*
      `return 0;` ends main straight away and hands 0 back to the operating
      system. Zero is the conventional code for "success": the program ran to
      the end without error. Exams expect it, so it is always written last.
    */
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: How many times does the body of Example A run?  -> exactly 1, because the test comes after the body
  Q2: How many times does the body of Example C run, and why?  -> 0 times, because a while loop tests first and 1 <= 0 is false
  Q3: What is the minimum number of passes for each loop type?  -> while and for can run 0 times; do...while always runs at least 1
  Q4: Where does the compulsory semicolon go?  -> after the closing parenthesis: `while (condition);` - not after the brace
  Q5: What would `passesA = passesC` mean instead of `!=`?  -> it would ASSIGN passesC's value into passesA and ask no question at all
*/
