// ============================================================
// PROGRAM: break against continue - the same loop, two keywords, two answers
// TOPIC: the difference between break and continue, traced pass by pass
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - The two keywords side by side on ONE loop, so the difference is measured
//   rather than remembered.
// - Exactly where each one sends control, and exactly what it throws away.
// - Why they can print the same number of lines and still be completely
//   different programs - the difference is in the passes, not the output.
// - A summary table covering both keywords: what they do, where control jumps,
//   their effect on the loop, and their effect on the code after the loop.
//
// EXPECTED OUTPUT:
// === Version A: break when i reaches 6 ===
// i = 1 printed
// i = 2 printed
// i = 3 printed
// i = 4 printed
// i = 5 printed
// i = 6: break, the loop is over
// passes = 6, values printed = 5
//
// === Version B: continue when i is even ===
// i = 1 printed
// i = 2 skipped by continue
// i = 3 printed
// i = 4 skipped by continue
// i = 5 printed
// i = 6 skipped by continue
// i = 7 printed
// i = 8 skipped by continue
// i = 9 printed
// i = 10 skipped by continue
// passes = 10, values printed = 5
//
// === The trap: same output count, completely different loops ===
// Both printed 5 values, and it is a coincidence.
// A made 6 passes and can never see 7 to 10 at all.
// B made all 10 passes and chose to ignore half of them.
// A found the answer and left. B visited everything and chose what to keep.
// break and continue produce the same five numbers here BY ACCIDENT only.
//
// IMPORTANT SYNTAX:
// break;    -> leave the loop at once; jump to the statement after the brace
// continue; -> skip the rest of THIS pass; jump to the update such as i++
//
// STEP-BY-STEP EXPLANATION:
// 1. Version A prints 1 to 5, then hits 6 and breaks. Six passes happen, and
//    passes 7 to 10 never exist as far as the program is concerned.
// 2. Version B visits all ten values. On the even ones it executes `continue`,
//    which abandons the rest of that pass and goes on to `i++`.
// 3. Both printed five values, which is exactly the trap: equal output counts
//    hide completely different behaviour. Read the pass counts, not the
//    printed lines.
// 4. The difference in one sentence: `break` ends the loop, `continue` ends
//    the pass. Everything else follows from that.
// 5. Both versions run the code after the loop. Neither keyword can jump over
//    it - `break` lands ON it, and `continue` can never reach the end of the
//    loop without passing through it.
// ============================================================

#include <iostream>
// The only header this project uses. It supplies `cout` for printing and
// `endl` for ending a line. The C++ language can calculate, store and compare
// but it cannot talk to a screen, so every piece of terminal output comes from
// this library, and this include line is what makes it available.

using namespace std;
// A NAMESPACE is a labelled box that groups related names so two libraries
// cannot fight over the same word. `std` is the box holding the C++ STANDARD
// library, where `cout` and `endl` live. The `::` is the SCOPE RESOLUTION
// OPERATOR and means "inside", so `std::cout` reads "the cout inside std".
// This line tells the compiler to take bare names from that box, which is why
// plain `cout` works in this file.

int main() {
// `main` is the ENTRY POINT: the first function the operating system runs when
// the program starts. `int` is the RETURN TYPE, handing a whole number back as
// an exit status when main finishes. `()` is the parameter list and it is
// empty, since this program takes no arguments and needs no keyboard input.
// The `{ }` braces are the BODY, executed from top to bottom.

    cout << "=== Version A: break when i reaches 6 ===" << endl;

    int passesA = 0;
    int printedA = 0;

    for (int i = 1; i <= 10; i++) {
        passesA++;

        if (i == 6) {
            cout << "i = " << i << ": break, the loop is over" << endl;
            break;
              //
              // `break;` LEAVES THE LOOP ENTIRELY. Three things are abandoned:
              //
              // - the rest of this pass, including the printing below;
              // - the loop's UPDATE, the `i++`, so i never becomes 7;
              // - every future pass, for good.
              //
              // Control lands on the first statement AFTER the closing brace -
              // which is the `cout` reporting the pass count. That is why the
              // numbers after the loop still print: the break jumps to them, it
              // does not jump over them.
              //
        }

        cout << "i = " << i << " printed" << endl;
        printedA++;
        // Five lines reach here: i = 1, 2, 3, 4 and 5. The sixth pass never
        // gets this far.
    }

    cout << "passes = " << passesA << ", values printed = " << printedA << endl;
    cout << endl;

    cout << "=== Version B: continue when i is even ===" << endl;

    int passesB = 0;
    int printedB = 0;

    for (int i = 1; i <= 10; i++) {
        passesB++;

        if (i % 2 == 0) {
            cout << "i = " << i << " skipped by continue" << endl;
            continue;
              //
              // `continue;` SKIPS THE REST OF THIS PASS AND NOTHING MORE.
              //
              // Control does NOT go to the statement after the loop. It goes
              // forward to the loop's UPDATE, the `i++` just above, and then the
              // next pass starts normally. That is why all ten values are
              // visited here, while version A stopped after six passes.
              //
              // The `% 2 == 0` test is the EVEN test: divide i by 2 and keep the
              // remainder, then ask whether anything was left over. True means
              // even, so 2, 4, 6, 8 and 10 all take this branch.
              //
        }

        cout << "i = " << i << " printed" << endl;
        printedB++;
        // Five lines reach here: i = 1, 3, 5, 7 and 9 - the same five VALUES
        // version A printed, arrived at by the opposite mechanism.
    }

    cout << "passes = " << passesB << ", values printed = " << printedB << endl;
    cout << endl;

    cout << "=== The trap: same output count, completely different loops ===" << endl;
    cout << "Both printed " << printedA << " values, and it is a coincidence."
         << endl;
    cout << "A made " << passesA
         << " passes and can never see 7 to 10 at all." << endl;
    cout << "B made all " << passesB << " passes and chose to ignore half of them."
         << endl;
    cout << "A found the answer and left. B visited everything and chose what to keep."
         << endl;
    cout << "break and continue produce the same five numbers here BY ACCIDENT only."
         << endl;
    // This is the sentence worth remembering. Two loops that print the same
    // five numbers can still be doing completely different work, and only the
    // pass counts tell them apart. Counting OUTPUT lines is how the mix-up
    // stays hidden; counting PASSES is how it gets caught.

    // ------------------------------------------------------------
    // TRACE TABLE - the two versions pass by pass, the whole point
    // ------------------------------------------------------------
    // +-------+---------+---------------------------+----------------------------+
    // | Pass  |    i    | VERSION A (break at 6)    | VERSION B (continue on    |
    // |       |         |                           | even numbers)             |
    // +-------+---------+---------------------------+----------------------------+
    // |   1   |    1    | prints 1                  | prints 1                   |
    // |   2   |    2    | prints 2                  | prints "skipped", continue|
    // |   3   |    3    | prints 3                  | prints 3                   |
    // |   4   |    4    | prints 4                  | prints "skipped", continue|
    // |   5   |    5    | prints 5                  | prints 5                   |
    // |   6   |    6    | BREAKS - loop over        | prints "skipped", continue|
    // |   7   |    7    | NEVER HAPPENS            | prints 7                   |
    // |   8   |    8    | NEVER HAPPENS            | prints "skipped", continue|
    // |   9   |    9    | NEVER HAPPENS            | prints 9                   |
    // |  10   |   10    | NEVER HAPPENS            | prints "skipped", continue|
    // |  11   |    -    | not reached               | 11 <= 10 FALSE, loop ends |
    // +-------+---------+---------------------------+----------------------------+
    //
    // WHERE THE TWO LOOPS DIVERGE: pass 6, and only pass 6. Up to pass 5 both
    // print every value they reach. On pass 6 version A executes `break` and
    // version B executes `continue`, and after that single line the two loops
    // have nothing in common - one of them no longer exists.
    //
    // WHY THE LOOP STOPPED, IN EACH CASE. Version A ended on pass 6 by command;
// Version B ended on pass 11 by exhaustion.
    // WHY VERSION A STOPPED: the break on pass 6 jumped straight past the
    // closing brace. The condition `i <= 10` was NEVER TESTED AGAIN, and the
    // update never ran again, so i never reached 7. Version A ended at pass 6
    // by command, not by exhaustion.
    //
    // WHY VERSION B STOPPED: the ordinary way. The update made i equal to 11,
    // the condition 11 <= 10 failed, and the loop ended. Every one of the ten
    // passes ran, and five of them ended early at the `continue`.
    //
    // BOTH RAN THE CODE AFTER THE LOOP. Version A's break LANDED on the
    // `cout` that printed "passes = 6", and version B reached the same sort
    // of line by finishing normally. Neither keyword skips the code below the
    // loop, which is why the results can be reported at all.
    //
    // THE SUMMARY TABLE - THE TWO KEYWORDS SIDE BY SIDE
    // +------------+---------------------+------------------------+-------------------------+------------------------------+
    // | Keyword    | What it does        | Where control jumps    | Effect on the loop      | Effect on the code after    |
    // |            |                     | to                     |                         | the loop                   |
    // +------------+---------------------+------------------------+-------------------------+------------------------------+
    // | break;     | Ends the loop       | The first statement    | The loop STOPS for      | Runs. Control lands        |
    // |            | completely and at    | AFTER the loop's       | good. No further        | ON it, so it always        |
    // |            | once                | closing brace          | passes, and the         | runs exactly once.         |
    // |            |                     |                        | update never runs       |                             |
    // |            |                     |                        | again                   |                             |
    // +------------+---------------------+------------------------+-------------------------+------------------------------+
    // | continue;  | Ends only the        | The loop's UPDATE -     | The loop CARRIES ON.    | Runs, but only once the    |
    // |            | current pass; the    | the i++ - and then the | The update still runs   | loop has ended normally.   |
    // |            | loop continues       | next pass starts       | and there is another    | It cannot be jumped        |
    // |            | normally             |                        | pass after this one     | over by a `continue`.      |
    // +------------+---------------------+------------------------+-------------------------+------------------------------+
    //
    // THREE QUESTIONS THAT SETTLE ANY ARGUMENT ABOUT THE PAIR
    //   1. Did the loop stop? `break` yes, `continue` no.
    //   2. Did the update `i++` run? Neither, on the pass where the keyword
    //      fired - but with `break` there is no later pass on which it could.
    //   3. Could the loop ever see a later value? `break` no, `continue` yes.
    // Ask question 3 whenever a loop with `break` seems to be "still going".
    //
    // COMMON TRAP IN THIS FILE
    //   Reaching for `break` when `continue` was wanted, because both are
    //   "jump out of here" in a vague sense. The symptom is always the same
    //   shape: the output stops early and is missing values you expected.
    //   Version A in this file is exactly that symptom made visible - it
    //   printed 1 to 5 and nothing else.
    //
    //   The reverse mistake is just as common and just as damaging: using
    //   `continue` when `break` was wanted. Then the loop runs every pass and
    //   tests every value, which is correct but slower, and - much worse - the
    //   early-exit version of the same search in 02_break_search.cpp turns
    //   into a full-length scan that nobody notices until the array is large.
    //
    //   The habit that prevents both: before writing either keyword, finish
    //   the sentence "I want to stop ______ ." Stop the whole loop, or stop
    //   this one value? The blank decides the keyword.

    return 0;
    // Ends main immediately and hands 0 back to the operating system. Zero is
    // the conventional code for "success": the program ran to its end without
    // an error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: On which pass do the two versions in this program behave differently?  -> pass 6, where version A breaks and version B continues; before that they are identical
// Q2: How many passes did each version make?  -> version A made 6 and version B made 10
// Q3: Where does control go when `break` runs, and where when `continue` runs?  -> break jumps to the first statement after the loop's closing brace, while continue jumps forward to the loop's update and then on to the next pass
// Q4: Does the code after the loop still run if the loop was left with `break`?  -> yes, and it always runs exactly once, because that is exactly where the break lands
// Q5: Both versions printed five values. Why is that a trap rather than proof they are the same?  -> the equal count is a coincidence; one loop stopped after 6 passes while the other ran all 10 and discarded half, so only the pass counts reveal the difference
