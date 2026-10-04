// ============================================================
// PROGRAM: Finding the Largest Value - the max idiom and its trap
// TOPIC: running maximum, and why the starting value must be real data
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - The max-finding idiom, in its correct form: start `largest` holding the
//   FIRST element, then walk the rest of the array keeping the better value.
// - WHY that is the correct starting point, and what breaks if you start at 0.
// - The negative-number trap, demonstrated as a running counterexample rather
//   than merely described - the wrong code gives a wrong answer, in view.
// - The one-line idea behind it: `largest` is only ever the best value seen SO
//   FAR, and at the end that is the best value in the whole array.
// - Why the loop starts at index 1 when `largest` is seeded from the array.
//
// EXPECTED OUTPUT:
// === Part 1: the correct idiom, largest seeded from the FIRST element ===
// start largest = values[0] = 17
// check -4: -4 is not bigger than 17, so 17 stays
// check 92: 92 is bigger than 17, so largest becomes 92
// check 8: 8 is not bigger than 92, so 92 stays
// check -31: -31 is not bigger than 92, so 92 stays
// check 45: 45 is not bigger than 92, so 92 stays
// check -12: -12 is not bigger than 92, so 92 stays
// check 60: 60 is not bigger than 92, so 92 stays
// check 9999 is the end marker, not a value, so it is never compared
// the largest is 92
//
// === Part 2: the same array, but largest started at 0 ===
// start largest = 0
// check 92: 92 is bigger than 0, so largest becomes 92
// the largest is 92
// On an array containing a positive value the mistake can hide.
//
// === Part 3: THE TRAP, on an array of all negative numbers ===
// values[0] = -5, so the correct start is -5
// -5 is not bigger than 0, so 0 stays
// -12 is not bigger than 0, so 0 stays
// -40 is not bigger than 0, so 0 stays
// -3 is not bigger than 0, so 0 stays
// -77 is not bigger than 0, so 0 stays
// -8 is not bigger than 0, so 0 stays
// from 0         : largest = 0   <- WRONG, not in the array
// from values[0] : largest = -3  <- RIGHT
// IMPORTANT SYNTAX:
// int largest = values[0];  -> seed from REAL DATA, before the loop starts
// for (int i = 1; i < n; i++) -> start at 1, because index 0 is already in
// if (values[i] > largest) { largest = values[i]; }
//                             -> keep whichever value is greater
//
// STEP-BY-STEP EXPLANATION:
// 1. Part 1 sets `largest` to values[0] BEFORE the loop, so it already holds a
//    value the loop has not had to compare yet.
// 2. `largest` then means "the best value seen so far". That is the whole
//    invariant, and the loop is simply: look at the next value, and if it
//    beats the best so far, replace the best.
// 3. The loop starts at index 1, because index 0 was used to seed `largest`.
//    Starting at 0 would compare values[0] with itself, which is harmless but
//    pointless - and it hides the real question, which is where the seed came
//    from.
// 4. Part 3 is the trap. Starting at 0 is a bug, not a shortcut: 0 is not
//    guaranteed to be smaller than the data. Every negative number loses to
//    it, so the loop never replaces it and reports a value that is not in the
//    array at all.
// 5. The lesson generalises: any "best so far" value must start as something
//    from the data, never a number guessed from outside it.
// ============================================================

#include <iostream>
// The only header this project uses. It supplies `cout` for printing and
// `endl` for ending a line. The C++ language can calculate, store and compare
// but it cannot talk to a screen, so all terminal output comes from this
// library, and this line is what makes it available.

using namespace std;
// A NAMESPACE is a labelled box grouping related names so two libraries cannot
// fight over the same word. `std` is the box holding the C++ STANDARD library,
// where `cout` and `endl` live. The `::` is the SCOPE RESOLUTION OPERATOR and
// means "inside", so `std::cout` reads "the cout inside std". This line tells
// the compiler to take bare names from that box, which is why `cout` needs no
// prefix in this file.

int main() {
// `main` is the ENTRY POINT: the first function the operating system runs when
// the program starts. `int` is the RETURN TYPE, handing a whole number back
// as an exit status when main finishes. `()` is the parameter list, empty since
// this program takes no arguments and reads no input. The `{ }` are the BODY,
// executed from top to bottom.

    int stopMarker = 9999;

    int values[] = {17, -4, 92, 8, -31, 45, -12, 60, 9999};
    // Eight real values, then the marker. The array holds positive numbers and
    // negative numbers both, which is what makes part 1 a fair rehearsal for
    // the trap in part 3.

    cout << "=== Part 1: the correct idiom, largest seeded from the FIRST element ===" << endl;

    // COUNT THE LENGTH WITH A LOOP. This project does not use sizeof, so a
    // marker value at the end of the array tells the loop when to stop.
    int n = 0;
    while (values[n] != stopMarker) {
        n++;
    }

    // THE SEED, AND THE WHOLE POINT OF THE FILE.
    //     values[0]   indexing from 0, so this is the FIRST value.
    //     =           ASSIGNMENT: "put this value into largest". It does not
    //                  compare anything; the comparison comes later, inside
    //                  the loop.
    // Starting from real data is what makes the idiom correct for negatives.
    // Part 3 shows what happens if this line is replaced by `= 0`.
    int largest = values[0];
    cout << "start largest = values[0] = " << largest << endl;

    // The loop starts at index 1, because values[0] has already been used to
    // seed `largest`. Starting at 0 would compare values[0] against itself.
    for (int i = 1; i < n; i++) {
        int v = values[i];
        int was = largest;
        // `was` keeps a copy of the value BEFORE the assignment, so the
        // printed line can name both the old best and the new one. Printing
        // after the assignment would say "92 is bigger than 92", which is
        // true and useless to anyone following the logic.

        if (v > largest) {
            // THE COMPARISON THAT DOES THE WORK. `>` is GREATER THAN: true
            // only when the left side is strictly bigger than the right. `>=`
            // would also work here, because equal values are harmless.
            largest = v;
            cout << "check " << v << ": " << v
                 << " is bigger than " << was
                 << ", so largest becomes " << largest << endl;
        } else {
            cout << "check " << v << ": " << v
                 << " is not bigger than " << largest << ", so " << largest
                 << " stays" << endl;
        }
        // BOTH branches print, because both are part of the explanation. In
        // a real program you would keep only the `if` branch and drop this
        // one entirely.
        //
        // WHERE CONTROL GOES: if the test is true, the assignment runs and
        // `largest` changes. Either way, the pass finishes and the loop's
        // UPDATE `i++` runs next, so the loop carries on. Nothing here ends
        // the loop - see 06_break_and_continue for the keyword that does.
    }
    cout << "check " << stopMarker
         << " is the end marker, not a value, so it is never compared" << endl;
    cout << "the largest is " << largest << endl;
    cout << endl;

    cout << "=== Part 2: the same array, but largest started at 0 ===" << endl;

    // THE SAME LOOP, THE WRONG SEED. Part 2 exists to show that the mistake
    // can go completely unnoticed while the array happens to contain a
    // positive number - and that noticing it is luck, not understanding.
    int largestFromZero = 0;
    cout << "start largest = " << largestFromZero << endl;

    for (int i = 1; i < n; i++) {
        int v = values[i];
        int was = largestFromZero;
        if (v > largestFromZero) {
            largestFromZero = v;
            cout << "check " << v << ": " << v
                 << " is bigger than " << was
                 << ", so largest becomes " << largestFromZero << endl;
        }
    }

    cout << "the largest is " << largestFromZero << endl;
    cout << "On an array containing a positive value the mistake can hide."
         << endl;
    cout << endl;

    cout << "=== Part 3: THE TRAP, on an array of all negative numbers ===" << endl;

    int negatives[] = {-5, -12, -40, -3, -77, -8, 9999};
    // Every single value here is below zero. That is the whole point: the
    // wrong seed is beaten on the first comparison and then never beaten
    // again, so it survives to the end and is reported as the answer.

    int negCount = 0;
    while (negatives[negCount] != stopMarker) {
        negCount++;
    }

    int correctMax = negatives[0];
    cout << "values[0] = " << correctMax
         << ", so the correct start is " << correctMax << endl;

    // THE CORRECT RUN GOES FIRST, on purpose. `correctMax` must really hold
    // the answer by the time it is printed at the end of this part. Printing
    // a variable before the loop that updates it is a mistake worth naming:
    // the output looks plausible and is simply the starting value.
    for (int i = 1; i < negCount; i++) {
        if (negatives[i] > correctMax) {
            correctMax = negatives[i];
        }
    }

    // NOW THE WRONG SEED. This loop starts at index 0 rather than 1, because
    // the seed came from nowhere and no element has been looked at yet. That
    // makes the very first comparison the seed against the first real value,
    // which is where the bug shows itself most clearly.
    int wrongMax = 0;
    for (int i = 0; i < negCount; i++) {
        int v = negatives[i];
        if (v > wrongMax) {
            // This branch is NEVER taken. Every value is below 0, so the test
            // is false on every single pass and wrongMax is never replaced.
            wrongMax = v;
        } else {
            cout << v << " is not bigger than " << wrongMax
                 << ", so " << wrongMax << " stays" << endl;
        }
    }

    cout << "from 0         : largest = " << wrongMax
         << "   <- WRONG, not in the array" << endl;
    cout << "from values[0] : largest = " << correctMax
         << "  <- RIGHT" << endl;

    // ------------------------------------------------------------
    // TRACE TABLE - Part 3, the wrong seed, on all-negative data
    // ------------------------------------------------------------
    // +-------+-----------+-----------+------------------+--------------------+
    // | Iter. | negatives | wrongMax  | v > wrongMax ?   | wrongMax after     |
    // |       | at start  | at start  |                  |                    |
    // +-------+-----------+-----------+------------------+--------------------+
    // |   1   |    -12    |     0     | FALSE - -12 < 0  | 0                  |
    // |   2   |    -40    |     0     | FALSE - -40 < 0  | 0                  |
    // |   3   |    -3     |     0     | FALSE - -3 < 0   | 0                  |
    // |   4   |    -77    |     0     | FALSE - -77 < 0  | 0                  |
    // |   5   |    -8     |     0     | FALSE - -8 < 0   | 0                  |
    // |   6   |    --     |     0     | loop has ended   | 0  <- WRONG        |
    // +-------+-----------+-----------+------------------+--------------------+
    // Six passes, not five: this loop starts at index 0 because the seed came
    // from nowhere, so all six real values are compared against 0 and none of
    // them wins.
    //
    // WHY THE LOOP STOPPED: the condition `i < negCount` is tested before each pass.
    // negCount is 6, so once i reaches 6 the test fails and the body never
    // runs again. The marker at index 6 is never compared.
    //
    // THE last COLUMN IS THE WHOLE LESSON: it never changes. `wrongMax` is
    // asked to be greater than every value, and it is not greater than any of
    // them, so no candidate ever wins and the seed is reported unchanged.
    //
    // THE CORRECT SEED, same data, for comparison
    // +--------+-----------+------------+-------------------+----------------+
    // | Iter.  | negatives | correctMax | v > correctMax ?  | correctMax after|
    // +--------+-----------+------------+-------------------+----------------+
    // |   1    |    -12    |     -5     | FALSE - -12 < -5  | -5              |
    // |   2    |    -40    |     -5     | FALSE - -40 < -5  | -5              |
    // |   3    |    -3     |     -5     | TRUE  - -3 > -5   | -3              |
    // |   4    |    -77    |     -3     | FALSE - -77 < -3  | -3              |
    // |   5    |    -8     |     -3     | FALSE - -8 < -3   | -3              |
    // |   6    |    --     |     -3     | loop has ended    | -3  <- RIGHT    |
    // +--------+-----------+------------+-------------------+----------------+
    // Six passes here against five in the table above: this loop starts at
    // index 1, so six values were compared. The last column moves twice instead
    // of never - that gap is the whole difference between right and wrong.
    //
    // WHY THE SEED MUST COME FROM THE DATA, IN ONE SENTENCE
    //   `largest` claims to be the best value seen SO FAR, and the only thing
    //   that can make that claim true on the very first pass is a value that
    //   really has been seen - namely values[0]. Any number invented outside
    //   the array is a claim about the data that nobody has checked, and if it
    //   is the wrong size it silently wins or loses every comparison after it.
    //
    // COMMON TRAP IN THIS FILE
    //   Writing `int largest = 0;` because 0 "looks like a safe small start".
    //   It is only safe if the data is guaranteed non-negative, and that
    //   guarantee is exactly what you do not have. The program compiles, runs
    //   without a warning, and reports a number that is not in the array -
    //   the worst kind of bug, because the output still looks like an answer.
    //   Part 2 is the trap in disguise: on an array containing 92 the wrong
    //   seed still ends up reporting 92, so the mistake survives testing and
    //   then appears in production on the first all-negative input.
    //
    //   The related trap: starting the loop at index 0 when `largest` is
    //   already values[0]. Nothing breaks, but the first comparison is a value
    //   against itself, and a reader can no longer tell whether the seed was
    //   included. Start at 1 and the reasoning stays honest.
    //
    //   Third: `>=` instead of `>` in the max idiom. Both give the right final
    //   answer here, so the error is harmless in itself - but it is a habit
    //   that breaks the MINIMUM idiom, where `>=` lets an early equal value
    //   stop the search too early.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always written as the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: What must `largest` be set to before the max-finding loop begins?  -> to the first element of the array, values[0], so it starts as real data rather than a guess
// Q2: Why does the loop start at index 1 rather than index 0?  -> because values[0] has already been used to seed `largest`, so comparing it with itself adds nothing
// Q3: What does `largest` mean at any point inside the loop?  -> the biggest value seen SO FAR, which by the end of the loop is the biggest value in the whole array
// Q4: Why is starting `largest` at 0 wrong for an array of negative numbers?  -> 0 is bigger than every one of them, so no candidate ever beats it and it is reported as the answer even though it is not in the array
// Q5: When is starting `largest` at 0 actually safe?  -> only when the data is guaranteed to contain no negative values, and that guarantee is usually not available
