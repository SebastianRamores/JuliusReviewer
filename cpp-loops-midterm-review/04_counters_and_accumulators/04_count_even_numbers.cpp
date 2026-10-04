/*
  ============================================================
  PROGRAM: Counting How Many Even Numbers Are in 1 to 50
  TOPIC: the COUNTER pattern, and how it differs from an ACCUMULATOR
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - The COUNTER: a variable that starts at 0 and goes up by 1 each time
    something happens. It answers "how many?", not "how much?".
  - The exact difference between a counter and an accumulator, in one
    comparison: `count++` against `sum = sum + i`.
  - Why a counter must also be initialised BEFORE the loop.
  - Two methods again - test every number, or step by 2 - plus how many
    passes each one costs.

  EXPECTED OUTPUT:
  === Part 1: visit every number and count the even ones ===
  Loop body ran 50 times.
  Even numbers found: 25
  === Part 2: step by 2 and count without testing ===
  Loop body ran 25 times.
  Even numbers found: 25
  === Which method is better here? ===
  Method 1 does 50 passes, Method 2 does 25 passes.
  Both methods find 25 even numbers, so they agree.

  IMPORTANT SYNTAX:
  int count = 0;          -> a counter starts at zero
  count++;                -> one more thing has been found
  count += 1;             -> exactly the same, written longer
  passes++;               -> a second counter, counting loop passes
  if (i % 2 == 0) { ... } -> only count when the number is even

  STEP-BY-STEP EXPLANATION:
  1. `int count = 0;` is the COUNTER, created before the loop.
  2. The loop visits every number from 1 to 50, so the body runs 50 times.
  3. `if (i % 2 == 0)` asks "is there no remainder when i is divided by 2?"
     TRUE means even, and only then does `count++;` fire.
  4. 25 of the 50 passes pass the test, so count ends at 25.
  5. Method 2 steps by 2, so every pass is a hit: the body runs 25 times
     and count still ends at 25 - half the work for the same answer.
  ============================================================
*/

#include <iostream>
/*
  <iostream> is the header file that gives C++ its ability to talk to the
  terminal: it supplies `cout` for output, `cin` for input and `endl` for
  ending a line. The language itself can only calculate and compare, so every
  facility for showing a result comes from a library - and this line invites
  that library in. Without it the compiler cannot find `cout`.
*/

using namespace std;
/*
  A NAMESPACE is a labelled box that groups related names so two libraries
  cannot fight over the same word. `std` is the box belonging to the C++
  STANDARD library, where `cout` and `endl` live, so the full name of our
  printing command is `std::cout`. The `::` is the SCOPE RESOLUTION OPERATOR
  and means "inside". `using namespace std;` says the names I write come
  from std, which is why plain `cout` works below.
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
      PART 1 - TEST EVERY NUMBER AND COUNT THE EVEN ONES
      ================================================================
    */
    cout << "=== Part 1: visit every number and count the even ones ===" << endl;

    /*
      THE COUNTER.
        int   whole numbers only; a decimal such as 2.5 could not be held.
        count the name; it is a very common choice of name for a counter.
        =     ASSIGNMENT - "store this value", NOT "equals".
        0     THE STARTING VALUE. `;` ends the statement.

      COUNTER OR ACCUMULATOR? THIS IS THE EXAM QUESTION, AND THE ANSWER IS:

        A COUNTER     answers "HOW MANY?"     It always moves by 1.
                      It ignores the size of the thing it is counting.
                      The line that changes it is `count++`.
                      Example: "how many even numbers are there?"

        An ACCUMULATOR answers "HOW MUCH?"     It moves by the value being
                      processed, so the steps are different sizes.
                      The line that changes it is `sum = sum + i;`
                      Example: "what is the total of them?"

      Put side by side, for i = 4:
        count++            count goes 3 -> 4      ONE more thing happened.
        sum = sum + i      sum    goes 36 -> 40    FOUR more was added.

      So in this program we write `count++` and never `count = count + i`.
      Writing the accumulator form here would answer a different question
      entirely, and would give 650 rather than 25.

      BOTH PATTERNS MUST BE INITIALISED BEFORE THE LOOP. A variable created
      inside the braces is destroyed at the closing brace and rebuilt on
      every pass, so it would always go back to its starting value and the
      answer would never build up.
    */
    int count = 0;

    // A second counter, this one counting how many times the body ran. It
    // needs to be outside the loop for the same reason.
    int passes = 0;

    // Step by 1, because `%` needs the number to actually be visited.
    for (int i = 1; i <= 50; i++) {

        // `passes++` is INSIDE the body, so it counts passes rather than
        // numbers - and it fires on all 50 of them.
        passes++;

        if (i % 2 == 0) {
        /*
          THE EVEN TEST, ONE MORE TIME

          `%` is the MODULO operator: divide, then hand back what is LEFT
          OVER. Dividing by 2 can only ever leave 0 behind or 1 behind:

          4 % 2  ->  0    nothing left over, so 4 is EVEN
          5 % 2  ->  1    one left over,      so 5 is ODD

          THE RULE:  `i % 2 == 0`  means "no remainder", i.e. even.
          `i % 2 != 0`  means "some remainder", i.e. odd.
          (`!=` is the NOT-EQUAL comparison, the opposite of `==`.)

          `==` asks the question "are these the same?" and answers true or
          false. `=` is ASSIGNMENT and stores a value instead - mixing them
          up is the single most common bug in this topic.
        */

            /*
              THE COUNTER LINE. `count++` is the INCREMENT operator, meaning
              "add 1 to count". It is shorthand for `count = count + 1;` and
              for `count += 1;`. Its whole purpose is to record "one more
              even number has been seen". Nothing about the VALUE of i
              enters into it: a 2 and a 50 each count as exactly one hit.
            */
            count++;
        }
        // Numbers failing the test are still VISITED, they are just not
        // counted. Visiting and counting are different actions.
    }

    cout << "Loop body ran " << passes << " times." << endl;
    cout << "Even numbers found: " << count << endl;

    /*
      ================================================================
      PART 2 - STEP BY 2 AND COUNT WITHOUT TESTING
      ================================================================
    */
    cout << "=== Part 2: step by 2 and count without testing ===" << endl;

    // Both counters start again at 0. Reusing count without resetting it
    // would be a trap: the answer would come out as 50, not 25.
    int count2 = 0;
    int passes2 = 0;

    /*
      Starting at 2 and stepping by 2 means every visit IS an even number,
      so the `if` can be deleted completely and the counter can simply be
      raised once per pass. This is the pattern to use whenever you are
      counting something that has a natural step.
    */
    for (int i = 2; i <= 50; i += 2) {
        passes2++;
        count2++;
    }

    cout << "Loop body ran " << passes2 << " times." << endl;
    cout << "Even numbers found: " << count2 << endl;

    /*
      ================================================================
      COMPARING THE TWO METHODS
      ================================================================
    */
    cout << "=== Which method is better here? ===" << endl;

    cout << "Method 1 does " << passes << " passes, Method 2 does " << passes2 << " passes." << endl;

    if (count == count2) {
        cout << "Both methods find " << count << " even numbers, so they agree." << endl;
    } else {
        cout << "They disagree: " << count << " against " << count2 << "." << endl;
    }

    /*
      ================================================================
      TRACE TABLE - PART 1, counting hits and misses
      ================================================================
      Rows 1 to 4 and 49 to 51 are shown; the rows in between repeat the
      same two patterns over and over, so they are elided with "...".
      +-----------+------------+-----------+----------+--------------------+--------+
      | Iteration | i at start | passes    | count    | i % 2 == 0 ?       | Output |
      +-----------+------------+-----------+----------+--------------------+--------+
      | 1         | 1          | 1         | 0        | FALSE - odd        | (none) |
      | 2         | 2          | 2         | 0 -> 1   | TRUE  - even       | (none) |
      | 3         | 3          | 3         | 1        | FALSE - odd        | (none) |
      | 4         | 4          | 4         | 1 -> 2   | TRUE  - even       | (none) |
      | ...       | ...        | ...       | ...      | ...                | ...    |
      | 49        | 49         | 49        | 24       | FALSE - odd        | (none) |
      | 50        | 50         | 50        | 24 -> 25 | TRUE  - even       | (none) |
      | 51        | 51         | (no more) | 25       | the loop has ended | (none) |
      +-----------+------------+-----------+----------+--------------------+--------+

      The two counter columns behave differently, and that is the lesson:
      passes climbs steadily to 50 because it rises on every single pass,
      while count climbs in jumps, staying flat on odd numbers and rising by
      exactly 1 on even ones. It finishes at 25 because half of 1 to 50 is
      even. The Output column is empty all the way down - this program
      reports only the totals.

      THE COMMON TRAP IN THIS FILE
        Writing `count = count + i;` where `count++` belongs. The program
        compiles, runs, and reports 650 - because 2 + 4 + 6 + ... + 50 adds
        the numbers instead of counting them. Nobody forgets an accumulator
        when they mean to use a counter. Ask the question first: "how many?"
        -> `count++`. "How much?" -> `sum = sum + i;`.

        The second trap is `int count;` with no starting value. C++ refuses
        to compile that inside a loop, because on the first pass there would
        be no value to add 1 to. Always give the starting value first.
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
  Q1: How many even numbers are there between 1 and 50?  -> 25
  Q2: How many times does the body of Part 1 run, and how many times does the body of Part 2 run?  -> 50 and then 25
  Q3: What does `count++` mean, and what would `count = count + i` mean?  -> one more hit; adding the value of i, which counts nothing usefully
  Q4: Why must `count` be declared before the loop?  -> inside the braces it would be destroyed and reset every pass
  Q5: Which method is faster here, and by how much?  -> Method 2, using 25 passes instead of 50
*/
