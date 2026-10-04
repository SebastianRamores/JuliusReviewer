// ============================================================
// PROGRAM: break - Leaving a Loop Early
// TOPIC: the break statement, and exactly where it sends control
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - `break;` ends the loop it sits in IMMEDIATELY. Everything after it in the
//   body is skipped, and the loop never comes back for another pass.
// - Where control actually jumps: not to the top of the loop, but to the first
//   statement AFTER the closing brace.
// - That the loop's UPDATE is skipped too, which is how a `break` can stop a
//   counter from ever reaching the number that would have ended the loop.
// - `break` nested inside an `if` inside a loop - the normal way to use it.
// - That `break` only ever leaves the INNERMOST loop around it, never the
//   outer one and never the program.
//
// EXPECTED OUTPUT:
// === Part 1: print 1 to 10, but stop at 7 ===
// 1 2 3 4 5 6 7
// The loop ran 7 passes, not 10.
// 8, 9 and 10 were never printed, because the loop was already finished.
//
// === Part 2: break living inside an if ===
// i = 1 keeping going
// i = 2 keeping going
// i = 3 keeping going
// i = 4 keeping going
// i = 5 keeping going
// i = 6 keeping going
// i = 7 breaking out now
// after the loop, and this line runs exactly once
//
// === Part 3: break inside a while loop ===
// counting down: 5
// counting down: 4
// counting down: 3
// down reached 2, so break
// after the loop, down = 2
// break ended the loop, not the program
//
// IMPORTANT SYNTAX:
// break;   -> leave the innermost loop around it, and skip to the line below
// if (i == 7) { break; } -> the normal home for a break: guarded by a test
//
// STEP-BY-STEP EXPLANATION:
// 1. The loop in part 1 would print 1 to 10. On the pass where i is 7 the
//    `break` runs, and the loop stops there and there.
// 2. The counter proved it: 7 passes, not 10. A loop that ran to its natural
//    end would have made 10.
// 3. The UPDATE never ran again either. If `i++` had been allowed to happen
//    once more, i would have become 8 and the loop would have carried on - so
//    the `break` skipped the very step that keeps a loop alive.
// 4. Part 2 puts the `break` inside an `if`. Without that test it would fire
//    on the first pass; the test is what makes it fire on the seventh.
// 5. Part 3 shows `break` in a `while` loop. The keyword behaves identically:
//    it stops the loop and the program carries on from the next line.
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
// the program starts. `int` is the RETURN TYPE, handing a whole number back
// as an exit status when main finishes. `()` is the parameter list and it is
// empty, since this program takes no arguments and reads no keyboard input.
// The `{ }` braces are the BODY, executed from top to bottom.

    cout << "=== Part 1: print 1 to 10, but stop at 7 ===" << endl;

    int passes = 0;

    for (int i = 1; i <= 10; i++) {
        // This loop would print 1 to 10 and stop by itself. The `break` below
        // will rob it of the last three numbers.

        if (passes > 0) {
            cout << " ";
        }
        cout << i;
        passes++;

        if (i == 7) {
            break;
              //
              // `break;` ENDS THE LOOP IMMEDIATELY. Three things happen at once:
              //
              // 1. Every statement below this one in the body is SKIPPED.
              // 2. The loop's UPDATE, the `i++`, is SKIPPED as well. This is
              // the part that surprises people: the loop is not paused and
              // it does not go back to the top with i unchanged - the
              // counter never becomes 8 at all.
              // 3. Control jumps to the FIRST STATEMENT AFTER the loop's
              // closing brace. Not to the top of the loop, and not to the
              // end of the program.
              //
              // `i == 7` uses `==` to ASK whether the two are the same. A single
              // `=` here would store 7 into i, and then the condition would be
              // asking "is i 7?" forever, with i stuck at 7 - an endless loop.
              //
        }
    }

    cout << endl;
    cout << "The loop ran " << passes << " passes, not 10." << endl;
    cout << "8, 9 and 10 were never printed, because the loop was already finished."
         << endl;
    cout << endl;

    cout << "=== Part 2: break living inside an if ===" << endl;

    for (int i = 1; i <= 10; i++) {
        // PART 2 IS THE ORDINARY WAY TO USE break. The `break` on its own
        // would fire on the very first pass and print a single number. The
        // `if` in front of it is the GUARD: it decides whether this pass is
        // the one that ends the loop.
        if (i == 7) {
            cout << "i = " << i << " breaking out now" << endl;
            break;
            // Nothing after this line in the braces would ever run, so there
            // is never any point in writing anything after a `break` - the
            // compiler does not even warn you, because it is legal.
        }

        cout << "i = " << i << " keeping going" << endl;
    }

    cout << "after the loop, and this line runs exactly once" << endl;
      //
      // PROOF THAT THE JUMP IS "AFTER THE LOOP" AND NOT "TO THE END OF main".
      // This statement sits below the closing brace. It ran once, which means
      // the break handed control to exactly here - not past the end of main,
      // and not back to the top of the loop.
      //
    cout << endl;

    cout << "=== Part 3: break inside a while loop ===" << endl;

    int down = 5;

    while (down > 0) {
        cout << "counting down: " << down << endl;
        down = down - 1;
        // The loop keeps going while this is above 0. Once `down` reaches 0
        // it would stop by itself, so the break is proving that it stops when
        // IT says so rather than when the condition does.
        if (down == 2) {
            cout << "down reached 2, so break" << endl;
            break;
        }
    }

    cout << "after the loop, down = " << down << endl;
    cout << "break ended the loop, not the program" << endl;
    // `down` is 2, not 0. The loop stopped early because of the break rather
    // than because the condition became false - and the program carried on
    // afterwards, printing both of the lines above.

    // ------------------------------------------------------------
    // TRACE TABLE - Part 1, showing the pass where everything stops
    // ------------------------------------------------------------
    // +-------+-------------+----------+---------------------+----------------+
    // | Pass  | i at start  | passes  | What happens        | Output         |
    // +-------+-------------+----------+---------------------+----------------+
    // |   1   |      1      |    0     | prints, i++ -> 2    | 1              |
    // |   2   |      2      |    1     | prints, i++ -> 3    | 2              |
    // |   3   |      3      |    2     | prints, i++ -> 4    | 3              |
    // |   ...  |     ...     |   ...   | ...                 | ...            |
    // |   6   |      6      |    5     | prints, i++ -> 7    | 6              |
    // |   7   |      7      |    6     | i == 7 TRUE, BREAK | 7              |
    // |   -    |    (none)   |  not run | the loop has ended  | nothing more   |
    // +-------+-------------+----------+---------------------+----------------+
    //
    // WHY THE LOOP STOPPED ON PASS 7: not because `i <= 10` became false -
    // that would have needed pass 11 - but because the `break` on pass 7
    // jumped straight past the loop's closing brace. Passes 8, 9 and 10 never
    // existed as far as the program is concerned.
    //
    // THE LAST ROW HAS NO `i`, BECAUSE `i` NEVER GOT PAST 7. If the break had
    // not fired, the update `i++` would have made i 8 on that pass and the
    // loop would have continued. Skipping the update is what makes the stop
    // permanent.
    //
    // PART 2, THE SAME IDEA WITH THE break INSIDE AN if
    // +-------+------------+---------------------------------+-------------------+
    // | Pass  | i at start | Branch taken                   | Output            |
    // +-------+------------+---------------------------------+-------------------+
    // |   1   |     1      | i == 7 false, so falls through | i = 1 keeping... |
    // |   2   |     2      | i == 7 false, so falls through | i = 2 keeping... |
    // |   3   |     3      | i == 7 false, so falls through | i = 3 keeping... |
    // |   4   |     4      | i == 7 false, so falls through | i = 4 keeping... |
    // |   5   |     5      | i == 7 false, so falls through | i = 5 keeping... |
    // |   6   |     6      | i == 7 false, so falls through | i = 6 keeping... |
    // |   7   |     7      | i == 7 TRUE, so break         | i = 7 breaking... |
    // |   8   |    (none)  | the loop has ended             | (nothing)         |
    // +-------+------------+---------------------------------+-------------------+
    //
    // WHERE `break` DOES NOT HELP YOU - MENTIONED, NOT DEMONSTRATED
    //   A `break` only ever leaves the INNERMOST loop that contains it. If one
    //   loop sits inside another, a `break` in the inner loop leaves the inner
    //   loop only; the outer loop carries straight on with its next value.
    //   That is deliberate, and it is what makes `break` useful for leaving
    //   one row of a grid while still working through every row.
    //
    //   A full example of that is deliberately NOT printed here, because the
    //   shape of nested loops is taught properly in 07_nested_loops. Written
    //   out badly, an example like that teaches the wrong lesson: the reader
    //   sees numbers appear to stop and concludes that break ended
    //   everything. The one-line rule to carry away is:
    //
    //       break leaves ONE loop - the innermost one it is written inside.
    //
    //   If you truly want to end an outer loop as well, C++ has no keyword for
    //   it. The honest answers are to wrap the pair in a function and `return`,
    //   or to arrange for the outer loop's condition to become false.
    //
    // COMMON TRAP IN THIS FILE
    //   Expecting `break` to act like "stop this iteration" - which is what
    //   `continue` does, not `break`. Reading a `break` as "skip the rest of
    //   this pass" is the single most common mix-up, and the two keywords have
    //   almost opposite jobs: `break` ends the loop, `continue` ends the pass
    //   while the loop carries on. See 03_basic_continue.cpp and, for the
    //   full side-by-side comparison, 05_break_vs_continue.cpp.
    //
    //   The second trap is writing statements after a `break` inside the same
    //   braces. They are dead code: legal, never executed, and no compiler
    //   complains. If code below a `break` never runs, the bug is almost
    //   always that the `break` should have been inside an `if`.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: What does `break;` do, and where exactly does control go next?  -> it ends the innermost loop at once, skipping the rest of the body and the update, and continues at the first statement after the closing brace
// Q2: Why did the loop in part 1 run 7 passes instead of 10?  -> because the break on pass 7 jumped straight out, so passes 8, 9 and 10 never happened
// Q3: Does the loop's `i++` run after a `break`?  -> no, which is why i never became 8 and the loop could not carry on
// Q4: Why is a `break` almost always placed inside an `if`?  -> unguarded it would fire on the very first pass; the test decides which single pass ends the loop
// Q5: In a loop inside a loop, what does a `break` in the inner loop leave?  -> only the inner loop - the outer loop still continues with its next value
