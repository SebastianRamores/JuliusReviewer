// ============================================================
// PROGRAM: Finding the Smallest Value - the min idiom and its trap
// TOPIC: running minimum, and why a guessed starting value can be too large
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - The min-finding idiom, correct form: seed `smallest` with the FIRST
//   element, then keep whichever value turns out to be smaller.
// - The comparison flips to `<`, and NOTHING else changes.
// - The mirror-image trap: guessing too LARGE a start, such as 1000000, and
//   what it does to an array that never contains a value that big.
// - Why the two idioms are the same sentence with the word "biggest" replaced
//   by "smallest", which is why learning one is learning both.
// - Why the same rule saves both: seed from real data, never from outside it.
//
// EXPECTED OUTPUT:
// === Part 1: the correct idiom, smallest seeded from the FIRST element ===
// start smallest = values[0] = 42
// check 17: 17 is smaller than 42, so smallest becomes 17
// check -8: -8 is smaller than 17, so smallest becomes -8
// check 99: 99 is not smaller than -8, so -8 stays
// check 3: 3 is not smaller than -8, so -8 stays
// check -25: -25 is smaller than -8, so smallest becomes -25
// check 60: 60 is not smaller than -25, so -25 stays
// the smallest is -25
//
// === Part 2: the same array, but smallest started at 1000000 ===
// start smallest = 1000000
// 42 is smaller than 1000000, so it becomes 42
// 17 is smaller than 42, so it becomes 17
// -8 is smaller than 17, so it becomes -8
// 99 is not smaller than -8, so -8 stays
// 3 is not smaller than -8, so -8 stays
// -25 is smaller than -8, so it becomes -25
// 60 is not smaller than -25, so -25 stays
// the smallest is -25
// The guess was too big, so the first value beat it at once.
//
// === Part 3: THE TRAP, when the guess is too big for the data ===
// every value really is above 1000000, so the guess wins
// from 1000000  : smallest = 1000000   <- WRONG, not in the array
// from values[0] : smallest = 2000000  <- RIGHT
// A start that is too LARGE survives only while it stays too large.
// With this array no value beat it, so the guess was reported unchanged.
// IMPORTANT SYNTAX:
// int smallest = values[0]; -> seed from REAL DATA, not from a guess
// if (values[i] < smallest) { smallest = values[i]; }
//                            -> keep whichever value is smaller
// for (int i = 1; i < n; i++) -> index 0 is already inside `smallest`
//
// STEP-BY-STEP EXPLANATION:
// 1. Part 1 is the max idiom with the comparison turned round: `v > largest`
//    becomes `v < smallest`, and "bigger" becomes "smaller". Nothing else.
// 2. `smallest` means "the smallest value seen SO FAR". Seed it with
//    values[0] so that claim is true before the loop even starts.
// 3. The loop starts at index 1, because values[0] is already inside the
//    variable. Each pass compares the next value against the best so far and
//    keeps the smaller of the two.
// 4. Part 2 seeds with 1000000, a number from nowhere. It works here, but
//    only because some value in the array was smaller than 1000000 and
//    knocked it out of the way on the very first pass.
// 5. Part 3 is the mirror image of the max trap. Here the guess is never
//    beaten, so it is reported as the answer - and 1000000 is not in the
//    array at all. Too small and too large are the same mistake: a starting
//    value that the data never justifies.
// ============================================================

#include <iostream>
// The only header this project needs. It provides `cout` for output and `endl`
// for a newline. The C++ language itself can calculate, store and compare but
// it cannot talk to a screen, so every piece of terminal output comes from
// this library, and this include line is what brings it in.

using namespace std;
// A NAMESPACE is a labelled box that groups related names so two libraries
// cannot both own the same word. `std` is the box belonging to the C++
// STANDARD library, where `cout` and `endl` live. The `::` is the SCOPE
// RESOLUTION OPERATOR and means "inside", so `std::cout` reads "the cout
// inside std". This line tells the compiler to take bare names from that box,
// which is why plain `cout` works in this file.

int main() {
// `main` is the ENTRY POINT: the first function the operating system runs when
// the program starts. `int` is the RETURN TYPE, handing a whole number back
// as an exit status when main finishes. `()` is the parameter list and it is
// empty, since this program takes no arguments and needs no keyboard input.
// The `{ }` braces are the BODY, executed from top to bottom.

    int stopMarker = 9999;

    int values[] = {42, 17, -8, 99, 3, -25, 60, 9999};
    // Seven real values, then the marker. Mixing positive and negative values
    // is deliberate: the smallest here is negative, so a start of 0 would be
    // obviously wrong on sight, which is not the interesting failure.

    cout << "=== Part 1: the correct idiom, smallest seeded from the FIRST element ===" << endl;

    // COUNTING WITH A LOOP RATHER THAN sizeof. This project may not use sizeof,
    // so a marker value at the end of the array tells the loop when to stop.
    int n = 0;
    while (values[n] != stopMarker) {
        n++;
    }

    int smallest = values[0];
    cout << "start smallest = values[0] = " << smallest << endl;

    for (int i = 1; i < n; i++) {
        int v = values[i];
        int was = smallest;

        if (v < smallest) {
            // THE ONLY LINE THAT CHANGES FROM THE MAX IDIOM. `<` is LESS THAN:
            // true when the left side is strictly smaller than the right.
            // `smallest` therefore keeps the better value and gives up the
            // worse one, exactly as `largest` did in the other direction.
            smallest = v;
            cout << "check " << v << ": " << v
                 << " is smaller than " << was
                 << ", so smallest becomes " << smallest << endl;
        } else {
            cout << "check " << v << ": " << v
                 << " is not smaller than " << smallest << ", so " << smallest
                 << " stays" << endl;
        }
    }
    cout << "the smallest is " << smallest << endl;
    cout << endl;

    cout << "=== Part 2: the same array, but smallest started at 1000000 ===" << endl;

    // 1000000 IS A GUESS, NOT A VALUE. It comes from outside the data, so
    // there is no reason at all to suppose the array goes that high - and no
    // reason to suppose it does not either. That is exactly what makes it a
    // bad seed: the answer should depend on the array alone.
    int guessed = 1000000;
    cout << "start smallest = " << guessed << endl;

    for (int i = 0; i < n; i++) {
        int v = values[i];
        int was = guessed;
        // `was` keeps a copy of the value BEFORE the assignment, so the line
        // below can name both the old value and the new one. Printing after
        // the assignment would say "42 is smaller than 42", which is true and
        // completely useless to a reader trying to follow the logic.
        if (v < guessed) {
            guessed = v;
            cout << v << " is smaller than " << was
                 << ", so it becomes " << guessed << endl;
        } else {
            cout << v << " is not smaller than " << was
                 << ", so " << guessed << " stays" << endl;
        }
    }

    cout << "the smallest is " << guessed << endl;
    cout << "The guess was too big, so the first value beat it at once." << endl;
    cout << endl;

    cout << "=== Part 3: THE TRAP, when the guess is too big for the data ===" << endl;

    int big[] = {2000000, 5000000, 3000000, 9999};
    // Every value is above the guessed start of 1000000, so the guess is never
    // beaten. This is the exact mirror of the max trap: there the start was
    // too SMALL, here it is too LARGE, and in both cases the start survives
    // all the way to the end and is reported as the answer.

    int bigCount = 0;
    while (big[bigCount] != stopMarker) {
        bigCount++;
    }

    int guessSurvives = 1000000;
    for (int i = 1; i < bigCount; i++) {
        if (big[i] < guessSurvives) {
            guessSurvives = big[i];
        }
    }

    int realSmallest = big[0];
    for (int i = 1; i < bigCount; i++) {
        if (big[i] < realSmallest) {
            realSmallest = big[i];
        }
    }

    cout << "every value really is above 1000000, so the guess wins" << endl;
    cout << "from 1000000  : smallest = " << guessSurvives
         << "   <- WRONG, not in the array" << endl;
    cout << "from values[0] : smallest = " << realSmallest
         << "  <- RIGHT" << endl;
    cout << "A start that is too LARGE survives only while it stays too large."
         << endl;
    cout << "With this array no value beat it, so the guess was reported unchanged."
         << endl;

    // ------------------------------------------------------------
    // TRACE TABLE - Part 1, the correct idiom over the whole array
    // ------------------------------------------------------------
    // Every pass is shown, because there are only seven.
    // +-------+-----------+------------+------------------+-----------------+
    // | Iter. |      i    | v          | v < smallest ?   | smallest after  |
    // |       |           |            |                  |                 |
    // +-------+-----------+------------+------------------+-----------------+
    // |  seed |     -     | values[0]  | not a comparison| 42              |
    // |   1   |      1    |     17     | TRUE  - 17 < 42  | 42 -> 17        |
    // |   2   |      2    |     -8     | TRUE  - -8 < 17  | 17 -> -8        |
    // |   3   |      3    |     99     | FALSE - 99 < -8? | -8              |
    // |   4   |      4    |      3     | FALSE - 3 < -8?  | -8              |
    // |   5   |      5    |    -25     | TRUE  - -25 < -8 | -8 -> -25       |
    // |   6   |      6    |     60     | FALSE - 60 < -25?| -25             |
    // |   7   |     (none)|  not run   | 7 < 7 is FALSE   | -25  <- answer  |
    // +-------+-----------+------------+------------------+-----------------+
    //
    // WHY THE LOOP STOPPED AFTER 6 PASSES: the condition `i < n` is tested
    // BEFORE each pass, and n is 7. On the seventh attempt i is already 7, so
    // 7 < 7 is false and the body never runs. The marker at index 7 is never
    // compared with anything, because the loop ends first.
    //
    // THE seed ROW IS NOT AN ITERATION - it is the assignment that happens
    // before the loop. Putting it in the table makes the one thing easy to
    // forget impossible to forget: `smallest` holds real data from the very
    // first row, so no comparison in the loop is ever against a made-up
    // number. That is precisely what part 3 gets wrong.
    //
    // TRACE TABLE - Part 2, where the guess happens to survive
    // +-------+------------+------------------+------------------+-------------+
    // | Iter. | v          | v < guess ?      | guess before     | guess after |
    // +-------+------------+------------------+------------------+-------------+
    // |   1   |     42     | TRUE  - 42 <1e6  | 1000000          | 42          |
    // |   2   |     17     | TRUE  - 17 < 42  | 42               | 17          |
    // |   3   |     -8     | TRUE  - -8 < 17  | 17               | -8          |
    // |   4   |     99     | FALSE            | -8               | -8          |
    // |   5   |      3     | FALSE            | -8               | -8          |
    // |   6   |    -25     | TRUE  - -25 < -8 | -8               | -25         |
    // |   7   |     60     | FALSE            | -25              | -25         |
    // |   8   |   (none)   | loop has ended   | -25              | -25         |
    // +-------+------------+------------------+------------------+-------------+
    // Note the loop here starts at index 0, one pass earlier than in part 1,
    // because nothing was seeded from the array. The first comparison throws
    // the guess away, which is why this version still gives the right answer.
    //
    // THE TWO TRAPS ARE THE SAME MISTAKE
    //   max idiom, too small a start : 0 beats every negative number, so the
    //                                  start survives and is reported.
    //   min idiom, too large a start: 1000000 loses to every value below a
    //                                  million, so if every value happens to
    //                                  be above it the guess survives and is
    //                                  reported as the smallest.
    //   In both cases the reported answer is a number that never appeared in
    //   the array. Seed from values[0] and the possibility disappears.
    //
    // COMMON TRAP IN THIS FILE
    //   Seeding the minimum with a "big enough" number, usually 1000 or
    //   1000000, and believing that being too large is harmless. It is only
    //   harmless while the data stays below the guess. The moment a value
    //   larger than the guess appears, the guess is beaten and the program
    //   looks correct again - which is worse, because the mistake has now
    //   survived a test and will surface later on different input.
    //
    //   The mirror mistake is starting the minimum at 0, which is the same
    //   error as starting the maximum at 0, just with the sign of the failure
    //   reversed. And the subtler one: using `>=` instead of `<`. Both give
    //   the right final minimum here, but `>=` makes the variable depend on
    //   where equal values sit, which breaks early-exit searches written later
    //   in 06_break_and_continue.

    return 0;
    // Ends main immediately and hands 0 back to the operating system. Zero is
    // the conventional code for "success": the program reached its end with no
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: How does the minimum idiom differ from the maximum idiom?  -> only the comparison changes: `v < smallest` replaces `v > largest`, with the same seeding and the same loop
// Q2: Why must `smallest` be initialised from values[0] rather than from 1000000?  -> 1000000 is not data, so if no value is smaller than it the guess is reported as the answer and the real minimum is lost
// Q3: What is the smallest value in the array used in part 1?  -> -25
// Q4: Why does the loop start at index 1 when the variable is seeded from values[0]?  -> because that value is already in the variable, so comparing it with itself would tell you nothing
// Q5: In part 3, why is the answer 1000000 wrong?  -> none of the values in that array is a million or more, so the starting guess was never replaced and is not even a member of the data
