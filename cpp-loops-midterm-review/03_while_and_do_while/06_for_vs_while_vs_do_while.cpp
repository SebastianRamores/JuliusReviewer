/*
  ============================================================
  PROGRAM: for vs while vs do...while - One Task, Three Answers
  TOPIC: choosing the right loop type
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - The SAME job - adding up 1 to 10 - written correctly three times.
  - All three programs must produce the same answer, and the program
    checks that with `==` and `&&` rather than asking you to trust it.
  - Where each loop type tests its condition, and what that decides.
  - How to pick the right loop for a new question on an exam.

  EXPECTED OUTPUT:
  === Version 1: for loop ===
  Sum using for = 55
  === Version 2: while loop ===
  Sum using while = 55
  === Version 3: do...while loop ===
  Sum using do...while = 55
  === Agreement check ===
  All three methods produce the same answer: 55

  IMPORTANT SYNTAX:
  for (int i = 1; i <= 10; i++) { sumFor += i; }
                              ^ start, then test, then update - all in one header
  while (w <= 10)  { sumWhile += w; w++; }
                  ^ test first, so the body may run zero times
  do { sumDo += d; d++; } while (d <= 10);
                              ^ test last, so the body always runs once
  sumFor += i;     -> add i into the running total and store it back
  &&              -> "AND": true only when BOTH sides are true

  STEP-BY-STEP EXPLANATION:
  1. Version 1 packs the start value, the test and the update into the for
     header, so the loop counter `i` lives and dies with the loop.
  2. Version 2 does the same work with the counter declared beforehand, and
     `w++` written at the bottom of the body instead of in a header.
  3. Version 3 uses the same counter and the same test, but the test comes
     after the body. With these starting values the result is identical.
  4. The three totals are compared with `==`, joined by `&&`. Because both
     comparisons hold, the program reports that all three agree.
  5. Note what would NOT agree: a do...while whose counter starts already
     beyond the limit, because it would add one number too many.
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
      VERSION 1 - THE for LOOP
      ================================================================
    */
    cout << "=== Version 1: for loop ===" << endl;

    /*
      The ACCUMULATOR, created before the loop and set to 0 because 0 is
      the identity for `+`: adding 0 changes nothing, so the first real
      number passes through untouched.
    */
    int sumFor = 0;

    /*
      The three header parts, always in this order and always separated by
      two semicolons:
        1. int i = 1  - INITIALISATION, run exactly once ever
        2. i <= 10    - CONDITION, tested before every pass
        3. i++        - UPDATE, run after every pass
      `sumFor += i` is compound addition: add i into the total.
      `i++` is the increment, shorthand for `i = i + 1;`.
    */
    for (int i = 1; i <= 10; i++) {
        sumFor += i;
    }

    cout << "Sum using for = " << sumFor << endl;

    /*
      ================================================================
      VERSION 2 - THE while LOOP
      ================================================================
    */
    cout << "=== Version 2: while loop ===" << endl;

    int sumWhile = 0;

    /*
      The counter must be declared ABOVE the loop. A while header has room
      for the test only, so unlike a for loop there is nowhere inside it to
      declare anything.
    */
    int w = 1;

    /*
      `w <= 10` reads as "is w less than or equal to 10?". TRUE runs the
      body then tests again; FALSE leaves the loop entirely. The test comes
      FIRST, so if w had started at 20 the body would never run at all.
    */
    while (w <= 10) {
        sumWhile += w;
        w++;   // the update lives inside the body here, not in a header
    }

    cout << "Sum using while = " << sumWhile << endl;

    /*
      ================================================================
      VERSION 3 - THE do...while LOOP
      ================================================================
    */
    cout << "=== Version 3: do...while loop ===" << endl;

    int sumDo = 0;
    int d = 1;

    /*
      Identical work. The only difference is that the test sits BELOW the
      body, so the body is guaranteed one pass. With d starting at 1 the
      answer matches the other two; had d started at 20 this version would
      have added 20 once and given 20, where the others gave 0.
    */
    do {
        sumDo += d;
        d++;
    } while (d <= 10);   // the semicolon after `)` is compulsory

    cout << "Sum using do...while = " << sumDo << endl;

    /*
      ================================================================
      THE AGREEMENT CHECK
      ================================================================
    */
    cout << "=== Agreement check ===" << endl;

    /*
      `==` is the EQUAL comparison: "are these two numbers the same?". It is
      completely different from `=`, which is ASSIGNMENT and would destroy
      the answer by overwriting one total with the other.
      `&&` is the AND operator. It joins two tests and is true only when
      BOTH are true. Written out in full it reads:
          if ( (sumFor == sumWhile) && (sumWhile == sumDo) ) { ... }
    */
    if (sumFor == sumWhile && sumWhile == sumDo) {
        cout << "All three methods produce the same answer: " << sumFor << endl;
    } else {
        cout << "The three methods disagree - check the starting values." << endl;
    }

    /*
      ================================================================
      TRACE TABLE - all three versions run side by side
      ================================================================
      The three counters i, w and d take identical values, so one table can
      show all three runs. There is no per-pass printing in this program -
      the totals are printed once at the end - so the last column records
      what the passing test was instead of any screen output.
      +-----------+-----------+--------+----------+-------+-------------+
      | Iteration | i / w / d | sumFor | sumWhile | sumDo | Test: i<=10 |
      +-----------+-----------+--------+----------+-------+-------------+
      | 1         | 1         | 1      | 1        | 1     | TRUE        |
      | 2         | 2         | 3      | 3        | 3     | TRUE        |
      | 3         | 3         | 6      | 6        | 6     | TRUE        |
      | 4         | 4         | 10     | 10       | 10    | TRUE        |
      | 5         | 5         | 15     | 15       | 15    | TRUE        |
      | 6         | 6         | 21     | 21       | 21    | TRUE        |
      | 7         | 7         | 28     | 28       | 28    | TRUE        |
      | 8         | 8         | 36     | 36       | 36    | TRUE        |
      | 9         | 9         | 45     | 45       | 45    | TRUE        |
      | 10        | 10        | 55     | 55       | 55    | TRUE        |
      | 11        | 11        | 55     | 55       | 55    | FALSE       |
      +-----------+-----------+--------+----------+-------+-------------+

      Each body ran 10 times. Row 11 is the failing test for all three: the
      counter is 11, 11 <= 10 is false, and the totals simply stay at 55.

      ================================================================
      COMPARISON TABLE - the five things the exam asks about
      ================================================================
      +--------------------+----------------+----------------+-----------------+
      | Feature            | for            | while          | do...while      |
      +--------------------+----------------+----------------+-----------------+
      | Syntax             | for (a;b;c) {} | while (b) {}   | do{} while (b); |
      +--------------------+----------------+----------------+-----------------+
      | Condition checked  | before body    | before body    | AFTER the body  |
      +--------------------+----------------+----------------+-----------------+
      | Minimum executions | 0              | 0              | 1               |
      +--------------------+----------------+----------------+-----------------+
      | Best used when     | count known    | passes unknown | must run once   |
      +--------------------+----------------+----------------+-----------------+
      | Infinite-loop risk | update missing | update missing | test stays true |
      +--------------------+----------------+----------------+-----------------+

      INFINITE-LOOP RISK, EXPLAINED: all three can spin for ever, and all
      three for the same underlying reason - whatever the condition tests
      never changes. In a for loop the update is easy to forget because it
      sits inside the header; in a while loop it is easy to forget because
      it sits inside the body; in a do...while the risk is highest of all,
      because the body has already run before the test is even reached.

      THE COMMON TRAP IN THIS FILE
        Writing `if (sumFor = sumWhile)` with one equals sign. That does not
        compare anything: it throws sumWhile's value into sumFor and then
        treats the result as true whenever sumWhile is not zero. The program
        would print "they agree" even when they did not. Compare with `==`,
        assign with `=`, and never mix them up.
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
  Q1: What answer do all three versions produce, and why?  -> 55, because 1 + 2 + ... + 10 = 55 in every case
  Q2: Which of the three types tests its condition after the body?  -> do...while, so it can never run fewer than one time
  Q3: Why can sumFor be declared inside the loop header instead of above it?  -> the for header creates it, which keeps it out of the rest of main
  Q4: What would the do...while version give if d started at 20?  -> 20, not 0, because its body runs once before any test is made
  Q5: What is wrong with `if (sumFor = sumWhile)`?  -> `=` assigns instead of comparing, so no real test is performed
*/
