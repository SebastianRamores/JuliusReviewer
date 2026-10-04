// ============================================================
// PROGRAM: continue - Skipping the Rest of One Pass
// TOPIC: the continue statement, and how it differs from break
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - `continue;` skips the REST OF THE CURRENT PASS only. The loop is not
//   finished; it goes straight on to the next value.
// - Exactly where control jumps: not out of the loop, but forward to the
//   loop's UPDATE - the `i++`.
// - That the counter must be placed BEFORE the `continue` if it is meant to
//   count every pass, because `continue` skips everything below it.
// - The same loop written three ways with `break`, with `continue` and with
//   neither, so the difference is visible rather than merely named.
//
// EXPECTED OUTPUT:
// === Part 1: print 1 to 10, skipping the multiples of 3 ===
// 1 2 4 5 7 8 10
// The loop made all 10 passes and skipped 3 of them.
// Skipping is not stopping: 8, 9 and 10 were still visited.
//
// === Part 2: the statement below continue never runs for 3 ===
// i = 1, this line runs after the if
// i = 2, this line runs after the if
// i = 4, this line runs after the if
// i = 5, this line runs after the if
// i = 6, this line runs after the if
//
// === Part 3: swap continue for break and everything changes ===
// 1 2
// break ended the loop at i = 3, so 4 to 10 were never visited
// continue ended the pass at i = 3 and the loop carried straight on
//
// IMPORTANT SYNTAX:
// continue;  -> skip the rest of THIS pass, then go to the loop's update
// if (i % 3 == 0) { continue; } -> the guard that chooses which passes to skip
// i++;        -> where continue lands: the update still happens
//
// STEP-BY-STEP EXPLANATION:
// 1. Part 1 visits every value from 1 to 10 and prints all but 3, 6 and 9.
// 2. `continue` throws away the rest of the pass - the printing statement is
//    never reached on those three passes - and jumps to `i++`.
// 3. The loop still made 10 passes, which the counter proves. Nothing about
//    `continue` ends a loop; only the condition failing or a `break` does that.
// 4. Part 2 shows the skipping directly: the marked line is missing for 3 and
//    for nothing else, so the omission is caused by `continue` and nothing else.
// 5. Part 3 puts `break` where `continue` was. The same three passes change
//    the whole loop: two numbers instead of seven, and no more passes at all.
// ============================================================

#include <iostream>
// The only header this project needs. It provides `cout` for output and
// `endl` for ending a line. The C++ language can calculate, store and compare
// but it cannot talk to a screen, so all terminal output comes from this
// library, and this include line is what brings it in.

using namespace std;
// A NAMESPACE is a labelled box grouping related names so two libraries cannot
// fight over the same word. `std` is the box holding the C++ STANDARD library,
// where `cout` and `endl` live. The `::` is the SCOPE RESOLUTION OPERATOR and
// means "inside", so `std::cout` reads "the cout inside std". This line tells
// the compiler to take bare names from that box, which is why plain `cout`
// works throughout this file.

int main() {
// `main` is the ENTRY POINT: the first function the operating system runs when
// the program starts. `int` is the RETURN TYPE, handing a whole number back as
// an exit status when main finishes. `()` is the parameter list and it is
// empty, since this program takes no arguments and needs no keyboard input.
// The `{ }` braces are the BODY, executed from top to bottom.

    cout << "=== Part 1: print 1 to 10, skipping the multiples of 3 ===" << endl;

    int passes = 0;
    int skipped = 0;
    int printed = 0;

    for (int i = 1; i <= 10; i++) {
        passes++;
        // THE COUNTER COMES FIRST, DELIBERATELY. `continue` skips everything
        // below it in this pass, so a counter written under the `continue`
        // would only ever count the passes that were NOT skipped - it would
        // report 7 instead of 10. Order inside the body is everything here.

        if (i % 3 == 0) {
            // `%` is the modulo operator: divide i by 3 and keep the
            // remainder. `i % 3 == 0` asks whether anything was left over,
            // which is true exactly for the multiples of 3.
            skipped++;
            continue;
              //
              // `continue;` SKIPS THE REST OF THIS PASS. Control does NOT leave
              // the loop - it jumps forward to the loop's UPDATE, the `i++`, and
              // then the next pass begins normally.
              //
              // Put the two keywords side by side:
              //
              // break;     -> leaves the loop entirely. No more passes, ever.
              // continue;  -> abandons THIS pass only. The update still runs
              // and there is another pass after it.
              //
              // So `continue` is not a weaker `break`. It is a different job:
              // break is for "the answer is known, stop looking", continue is
              // for "this value is of no interest, move on".
              //
        }

        if (printed > 0) {
            cout << " ";
        }
        cout << i;
        printed++;
        // The separator is printed BEFORE each value rather than after it, so
        // no line ever ends in a stray space.
    }

    cout << endl;
    cout << "The loop made all " << passes << " passes and skipped " << skipped
         << " of them." << endl;
    cout << "Skipping is not stopping: 8, 9 and 10 were still visited." << endl;
    cout << endl;

    cout << "=== Part 2: the statement below continue never runs for 3 ===" << endl;

    // PART 2 PROVES THE SKIPPING DIRECTLY. The `if` below is identical in
    // shape to the one in part 1, and the marked line afterwards is the thing
    // being skipped. Only i = 3 is missing from the output, and nothing else
    // in the loop could possibly cause that.
    for (int i = 1; i <= 6; i++) {
        if (i == 3) {
            continue;
        }
        cout << "i = " << i << ", this line runs after the if" << endl;
    }
    cout << endl;

    cout << "=== Part 3: swap continue for break and everything changes ===" << endl;

    int printedA = 0;

    // THE SAME LOOP, THE SAME TEST, ONE KEYWORD CHANGED. Compare the two
    // halves of the output: the break version printed two numbers, while the
    // continue version in part 1 printed seven. Nothing else was altered.
    for (int i = 1; i <= 10; i++) {
        if (i == 3) {
            break;
        }
        if (printedA > 0) {
            cout << " ";
        }
        cout << i;
        printedA++;
    }
    cout << endl;
    cout << "break ended the loop at i = 3, so 4 to 10 were never visited" << endl;
    cout << "continue ended the pass at i = 3 and the loop carried straight on"
         << endl;

    // ------------------------------------------------------------
    // TRACE TABLE - Part 1, all ten passes, showing which are skipped
    // ------------------------------------------------------------
    // +-------+----------+----------+----------+------------------+----------+------------------+
    // | Pass  | i at start| passes  | skipped | i % 3 == 0 ?      | printed  | Output          |
    // +-------+----------+----------+----------+------------------+----------+------------------+
    // |   1   |     1     |    1     |    0    | FALSE             | 1        | 1               |
    // |   2   |     2     |    2     |    0    | FALSE             | 2        | 2               |
    // |   3   |     3     |    3     |    1    | TRUE -> continue  | 2        | (none)          |
    // |   4   |     4     |    4     |    1    | FALSE             | 3        | 4               |
    // |   5   |     5     |    5     |    1    | FALSE             | 4        | 5               |
    // |   6   |     6     |    6     |    2    | TRUE -> continue  | 4        | (none)          |
    // |   7   |     7     |    7     |    2    | FALSE             | 5        | 7               |
    // |   8   |     8     |    8     |    2    | FALSE             | 6        | 8               |
    // |   9   |     9     |    9     |    3    | TRUE -> continue  | 6        | (none)          |
    // |  10   |    10     |   10     |    3    | FALSE             | 7        | 10              |
    // |  11   |   (none)  | not run  |    3    | 11 <= 10 is FALSE | 7        | (nothing)       |
    // +-------+----------+----------+----------+------------------+----------+------------------+
    //
    // WHY THE LOOP STOPPED ON PASS 10: the condition `i <= 10` was tested and
    // failed, exactly as it would have without any `continue`. The condition
    // was never tested on passes 3, 6 or 9, because `continue` jumped straight
    // past the body to the update. Nothing about `continue` changed WHEN the
    // loop ends - it only changed what the body did on three passes.
    //
    // THE passes COLUMN IS THE PROOF THAT continue IS NOT break. It reaches
    // 10, which is what a `break` version could never manage: if a `break`
    // had stood where the `continue` is, this column would have stopped at 3.
    //
    // PART 3 COMPARED WITH PART 1, THE ONLY DIFFERENCE BEING THE KEYWORD
    // +---------+---------------------+---------------------+--------------------+
    // | Pass    | Part 1 (continue)   | Part 3 (break)      | Same code, so the |
    // |         |                     |                     | difference is the |
    // |         |                     |                     | keyword alone     |
    // +---------+---------------------+---------------------+--------------------+
    // |  1, 2   | prints 1, then 2    | prints 1, then 2    | identical         |
    // |  3      | skipped, carries on| BREAKS the loop     | diverges here     |
    // |  4 to 9 | 4, 5, 7, 8 printed | never reached       | diverges for ever |
    // |  10     | prints 10           | never reached       | diverges          |
    // +---------+---------------------+---------------------+--------------------+
    // The two loops are identical until pass 3. There the `continue` sends
    // control forward to the update and the `break` sends it out past the
    // closing brace, and from that moment the two are not comparable at all.
    //
    // COMMON TRAP IN THIS FILE
    //   Putting the counter or any bookkeeping AFTER the `continue`. It is the
    //   same class of mistake as writing a statement after a `break`: the code
    //   is legal, it compiles, and it never runs. In part 1 the `passes++`
    //   sits above the `continue` for exactly this reason, and moving it one
    //   line down would change the reported total from 10 to 7 while still
    //   printing the same seven numbers. Always put work you want done on
    //   EVERY pass before the `continue`.
    //
    //   The second trap is writing an empty `continue` at the end of a loop
    //   body. It is legal and it does nothing except skip whatever follows it,
    //   which is usually nothing. A `continue` is only worth having when there
    //   are statements below it that must be avoided.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: Where exactly does control go when `continue` runs?  -> forward to the loop's update such as `i++`, skipping whatever is left of the current pass
// Q2: How many passes did the loop in part 1 make, and how many values did it skip?  -> 10 passes, skipping 3 of them
// Q3: Why must `passes++` appear before the `continue`?  -> because continue skips everything below it in the pass, so a counter underneath would only count the passes that were not skipped
// Q4: Why is `continue` not simply a weaker `break`?  -> they do different jobs - break ends the loop for good, while continue abandons only the current pass and the update still runs
// Q5: What does part 3 show when the same loop uses `break` instead?  -> it prints only 1 and 2, because the loop ends at i = 3 and never reaches 4 to 10
