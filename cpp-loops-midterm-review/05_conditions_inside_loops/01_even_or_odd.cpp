// ============================================================
// PROGRAM: Even or Odd - the two-way if and the three-way chain
// TOPIC: conditions inside loops - if, else, else if
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - `if (condition) { ... }` runs its block only when the condition is TRUE.
// - `if / else` is the two-way choice: exactly one of the two blocks runs.
// - `if / else if / else` is the three-way chain, and the rule that makes it
//   pick exactly ONE branch: the tests are read from top to bottom, the FIRST
//   true test wins, and everything below it is skipped completely.
// - All six comparison operators at once, and why a test needs `==` while a
//   lone `=` would only store a value instead of asking a question.
// - `i % 2 == 0` is not a trick - it is the DEFINITION of "even".
//
// EXPECTED OUTPUT:
// === Part 1: the two-way if / else, numbers 1 to 20 ===
// 1 is odd
// 2 is even
// 3 is odd
// 4 is even
// 5 is odd
// 6 is even
// 7 is odd
// 8 is even
// 9 is odd
// 10 is even
// 11 is odd
// 12 is even
// 13 is odd
// 14 is even
// 15 is odd
// 16 is even
// 17 is odd
// 18 is even
// 19 is odd
// 20 is even
//
// === Part 2: the same test written as a three-way chain ===
// first branch (even) taken: 10
// second branch (odd) taken: 10
// final else taken: 0
//
// === Part 3: positive, negative or zero ===
// -5 is negative
// -4 is negative
// -3 is negative
// -2 is negative
// -1 is negative
// 0 is zero
// 1 is positive
// 2 is positive
// 3 is positive
// 4 is positive
// 5 is positive
// positive = 5, negative = 5, zero = 1
//
// IMPORTANT SYNTAX:
// if (i % 2 == 0) { ... }  -> run the block only when i leaves NO remainder on division by 2
// else { ... }             -> the other case: run this when the test above was false
// else if (i % 2 == 1) { } -> a third test, reached only if every earlier test failed
// else { ... }             -> the last resort, run when nothing above matched
// i % 2 == 0                -> the `==` ASKS a question; a lone `=` would not ask one
//
// STEP-BY-STEP EXPLANATION:
// 1. The loop supplies a fresh value of `i` on every pass, and the `if` is
//    re-tested from the top each time - the test is not remembered.
// 2. In part 1 the test is true on the even passes, so those print "is even";
//    on the odd passes it is false, so the `else` prints "is odd".
// 3. In part 2 the chain has three tests instead of two. Only ONE of the
//    three can ever run per pass, because the moment a test succeeds the rest
//    of the chain is skipped, not merely unlikely.
// 4. The third test is `i % 2 == 1`, which catches every odd number, so the
//    final `else` can never be reached - its counter stays at 0. Dead code is
//    not an error, but it is a sign the chain has one test too many.
// 5. In part 3 the order of the tests matters: `i > 0` is checked first, then
//    `i < 0`. Because the first test already caught the positive numbers,
//    the second test never sees them.
// 6. `else` on its own must always be LAST - C++ has no "else if" keyword of
//    its own. It is literally `else` immediately followed by `if (...)`.
// ============================================================

#include <iostream>
// This is the ONLY header this project uses. It gives the program its link to
// the terminal: `cout` for printing, `endl` for ending a line. The C++ language
// itself can only calculate, store and compare - it cannot talk to a screen -
// so every printing command lives in this library. Without this line the
// compiler would report that `cout` does not exist.

using namespace std;
// A NAMESPACE is a labelled box that keeps related names from colliding, so
// two libraries cannot both own the bare word `count`. `std` is the box holding
// the C++ STANDARD library, where `cout` and `endl` live - so the full name of
// our printing command is `std::cout`. The `::` is the SCOPE RESOLUTION
// OPERATOR and means "inside". `using namespace std;` tells the compiler to
// look for every bare name in that box, which is why plain `cout` works below
// instead of `std::cout` on all 40-odd print statements.

int main() {
// `main` is the ENTRY POINT: the first thing the operating system runs when
// the program starts, so all the real work must live inside it. `int` is the
// RETURN TYPE, so when main finishes it hands a whole number back to the
// operating system as an exit status. `()` is the parameter list and it is
// empty, because this program needs no keyboard input and takes no arguments.
// The `{ }` braces are the BODY, and they are executed from top to bottom.

    cout << "=== Part 1: the two-way if / else, numbers 1 to 20 ===" << endl;

    for (int i = 1; i <= 20; i++) {
        // `i` counts 1, 2, 3 ... 20 and stops. The `if` below is re-tested
        // from scratch on every one of those 20 passes.

        if (i % 2 == 0) {
            // THE TEST. Read it inside out, in three pieces:
            //   i % 2   divide i by 2 and keep the REMAINDER - `%` is called
            //           the modulo operator. 4 % 2 leaves 0 behind, 5 % 2
            //           leaves 1 behind, and nothing else is ever possible.
            //   == 0    compare that remainder with zero. `==` is the EQUAL
            //           comparison: it asks "are these two the same?" and
            //           answers true or false. A single `=` here would be an
            //           ASSIGNMENT - it would store 0 into i, wiping the loop
            //           variable and starting an infinite loop. That one
            //           character is the single most common bug in this topic.
            //   if ( )  if the answer is true, run the braces; if false, jump
            //           straight past them without complaining.
            cout << i << " is even" << endl;
        } else {
            // The `else` runs when the test above was false, and ONLY then.
            // Together the `if` and the `else` are exclusive: exactly one of
            // the two runs on every single pass, never both and never neither.
            cout << i << " is odd" << endl;
        }
    }
    cout << endl;

    cout << "=== Part 2: the same test written as a three-way chain ===" << endl;

    // The three counters must exist BEFORE the loop. A counter created inside
    // the braces would be destroyed at the closing brace and rebuilt from
    // scratch on every pass, so it could never climb above 1.
    int evenCount = 0;
    int oddCount = 0;
    int deadCount = 0;

    for (int i = 1; i <= 20; i++) {
        if (i % 2 == 0) {
            evenCount++;
        } else if (i % 2 == 1) {
            // HOW A CHAIN PICKS EXACTLY ONE BRANCH. The tests are read top to
            // bottom. The first one that is true runs its block, and then the
            // REST OF THE CHAIN IS SKIPPED COMPLETELY - the later tests are
            // not merely unlikely to be wrong, they are never evaluated at all
            // on that pass. So `else if` is not a second independent if; it
            // means "otherwise, and only otherwise, try this".
            oddCount++;
        } else {
            // UNREACHABLE, and that is the point of printing this counter.
            // Dividing a whole number by 2 leaves either 0 or 1 behind, so one
            // of the first two tests always succeeds and this branch never
            // runs. The compiler is quite happy to keep it anyway: it checks
            // grammar, not intentions. Dead code still costs nothing to read.
            deadCount++;
        }
    }

    cout << "first branch (even) taken: " << evenCount << endl;
    cout << "second branch (odd) taken: " << oddCount << endl;
    cout << "final else taken: " << deadCount << endl;
    cout << endl;

    cout << "=== Part 3: positive, negative or zero ===" << endl;

    int positive = 0;
    int negative = 0;
    int zero = 0;

    // A starting value BELOW 1 this time. There is nothing special about 1 -
    // any two integers make a valid range, and -5 to 5 happens to put a zero
    // in the middle, which is what makes the third branch reachable.
    for (int i = -5; i <= 5; i++) {
        // THE ORDER OF THE TESTS IS PART OF THE ANSWER. `i > 0` is tried first.
        // On the passes where it succeeds, the other two tests are never even
        // looked at. On the passes where it fails, `i < 0` gets its turn.
        if (i > 0) {
            // `>` is the GREATER-THAN comparison: true when the left side is
            // strictly bigger than the right. Note it is not `>=`, which would
            // also accept 0 and so would make the "zero" branch unreachable.
            cout << i << " is positive" << endl;
            positive++;
        } else if (i < 0) {
            // `<` is the LESS-THAN comparison: true when the left side is
            // strictly smaller than the right.
            cout << i << " is negative" << endl;
            negative++;
        } else {
            // The last resort. Reaching this branch does NOT mean "positive
            // and not negative is false" in some clever way - it means every
            // test above it has already been tried and every one failed.
            cout << i << " is zero" << endl;
            zero++;
        }
    }

    cout << "positive = " << positive
         << ", negative = " << negative
         << ", zero = " << zero << endl;
    // All three counters are alive here because they were declared OUTSIDE
    // the loop. Their values survive the loop and can be printed afterwards -
    // that is the whole reason a counter lives outside the braces.

    // ------------------------------------------------------------
    // TRACE TABLE - Part 1, the two-way if / else
    // ------------------------------------------------------------
    // Iterations 1 to 4 are shown, then "...", then 19 to 21. The rows in
    // between repeat the same two patterns over and over.
    // +---------+-------------+-----------+--------------------+---------------+
    // | Iteration| i at start | i % 2     | i % 2 == 0 ?        | Output        |
    // +---------+-------------+-----------+--------------------+---------------+
    // |    1    |     1       |     1     | FALSE - odd number  | 1 is odd      |
    // |    2    |     2       |     0     | TRUE  - even number | 2 is even     |
    // |    3    |     3       |     1     | FALSE - odd number  | 3 is odd      |
    // |    4    |     4       |     0     | TRUE  - even number | 4 is even     |
    // |   ...   |    ...      |    ...    | ...                 | ...           |
    // |   19    |     19      |     1     | FALSE - odd number  | 19 is odd     |
    // |   20    |     20      |     0     | TRUE  - even number | 20 is even    |
    // |   21    |     21      |    (not   | FALSE, and the loop | (nothing -    |
    // |         |             |  reached) | has already ended   | loop is over) |
    // +---------+-------------+-----------+--------------------+---------------+
    //
    // WHY THE LOOP STOPPED AT 20 PASSES: the condition `i <= 20` is tested
    // BEFORE each pass. On pass 21 the update has made i equal to 21, so
    // 21 <= 20 is false and the loop ends WITHOUT running the body again.
    // The 21st row is drawn to make that missed final test visible - no
    // "21 is odd" line appears, and that absence is the proof.
    //
    // NOTE THE TWO OUTPUT COLUMNS AND THE TWO REMAINDERS AGREE: a remainder of
    // 0 always means even, and a remainder of 1 always means odd, so the
    // `else` block runs on exactly the rows where the remainder is 1.
    //
    // TRACE TABLE - Part 3, where the chain order decides the answer
    // +---------+-------------+----------+------------+--------------------+
    // | Iteration| i at start | i > 0 ?  | i < 0 ?    | Branch that ran    |
    // +---------+-------------+----------+------------+--------------------+
    // |    1    |     -5      | FALSE    | not tested | 2nd - negative     |
    // |    2    |     -4      | FALSE    | not tested | 2nd - negative     |
    // |   ...   |    ...      |   ...    |    ...     | ...                |
    // |    5    |     -1      | FALSE    | not tested | 2nd - negative     |
    // |    6    |      0      | FALSE    | TRUE       | 3rd - zero         |
    // |    7    |      1      | TRUE     | NOT TESTED | 1st - positive     |
    // |    8    |      2      | TRUE     | NOT TESTED | 1st - positive     |
    // |   ...   |    ...      |   ...    |     ...    | ...                |
    // |   11    |      5      | TRUE     | NOT TESTED | 1st - positive     |
    // |   12    |      6      | TRUE     | NOT TESTED | 1st - positive     |
    // +---------+-------------+----------+------------+--------------------+
    //
    // Two things to read off that table. First, the "not tested" entries: on
    // those passes the first test succeeded, so `i < 0` was never evaluated -
    // proof that a chain short-circuits instead of testing everything.
    // Second, on iteration 6 the value is 0, so `i > 0` is false AND `i < 0`
    // is false. Only when both have failed does control reach the final else.
    //
    // THE SIX COMPARISON OPERATORS, ALL TOGETHER
    //   i <  j     less than            i >= j    greater than or equal
    //   i >  j     greater than         i <= j    less than or equal
    //   i == j     equal  (two equals)  i != j    not equal (equals + bang)
    //   `==` ASKS, `=` STORES. `if (i == 0)` asks a question. `if (i = 0)`
    //   does not: it stores 0 into i, and a stored 0 is a false condition, so
    //   the branch never runs and the loop counter has just been destroyed.
    //   `<=` and `>=` include equality; `<` and `>` do not. That is why a
    //   loop running 1 to 20 needs `<=` and would print only 1 to 19 with `<`.
    //
    // COMMON TRAP IN THIS FILE
    //   Writing `if (i % 2 = 0)` instead of `==`. It compiles, it runs, and it
    //   prints the wrong thing: the single `=` quietly stores 0 into the loop
    //   variable `i` on every pass, so `i` never grows, the condition
    //   `i <= 20` stays true forever, and the program hangs with no error
    //   message at all. Your compiler can warn about it (-Wparentheses), which
    //   is why this project compiles with -Wall -Wextra. If a program with a
    //   loop suddenly prints forever, look for a single `=` in a condition
    //   before anything else.
    //
    //   The second trap: adding an `else` that can never run (part 2). It is
    //   not an error and it is not dangerous - but if a chain has three
    //   branches and one counter always ends at 0, that branch is dead code
    //   and the chain has one test too many.

    return 0;
    // `return 0;` ends main immediately and hands 0 back to the operating
    // system. Zero is the conventional code for "success": the program ran
    // all the way to the end without an error. Any other value is treated as
    // a failure, so exams expect 0 and it is always the last line.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: What does the expression `i % 2 == 0` mean?  -> i divides evenly by 2, which is the definition of even
// Q2: In an `if / else if / else` chain, how many branches can run on one pass of a loop?  -> exactly one; the first true test wins and the rest of the chain is skipped
// Q3: Why is `if (i % 2 = 0)` a bug while `if (i % 2 == 0)` is correct?  -> `=` stores 0 into i instead of comparing, so the loop counter is destroyed and the loop never ends
// Q4: How many times did the final `else` in part 2 run, and why?  -> never; a whole number always leaves remainder 0 or 1 on division by 2, so one of the first two tests always succeeds
// Q5: Why must the counters in part 3 be declared before the loop rather than inside it?  -> a variable made inside the braces is destroyed and reset to its start on every pass, so it could never climb
