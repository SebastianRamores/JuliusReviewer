// ============================================================
// PROGRAM: Counting Values That Match Conditions - four tests, one loop
// TOPIC: several counters in one pass, and counting digits with a divide loop
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - How one pass over an array can feed SEVERAL counters at the same time,
//   which is the normal way to answer a question needing more than one count.
// - `&&` for "both conditions", so "divisible by 2 AND by 5" is found in a
//   single test instead of two loops compared afterwards.
// - The mathematical identity hiding inside that: divisible by 2 and by 5 is
//   the same set as divisible by 10, and the program proves it by counting.
// - Digit counting the beginner's way: divide by 10 repeatedly until nothing
//   is left, counting the divisions - no logarithms, no library.
// - Why 0 needs special care in a digit-counting loop, and what `do / while`
//   is for.
//
// EXPECTED OUTPUT:
// === Part 1: four counts from a single pass over the array ===
// 7: digit count = 1
// 12: divisible by 2
// 12: digit count = 2
// 25: divisible by 5
// 25: digit count = 2
// 4: divisible by 2
// 4: digit count = 1
// 100: divisible by both 2 and 5
// 100: divisible by 2
// 100: divisible by 5
// 100: digit count = 3
// 33: digit count = 2
// 8: divisible by 2
// 8: digit count = 1
// 15: divisible by 5
// 15: digit count = 2
// 0: divisible by both 2 and 5
// 0: divisible by 2
// 0: divisible by 5
// 0: digit count = 1
// 6: divisible by 2
// 6: digit count = 1
// 250: divisible by both 2 and 5
// 250: divisible by 2
// 250: divisible by 5
// 250: digit count = 3
// 9: digit count = 1
//
// Counts after one pass over 12 values:
//   divisible by 2          : 7
//   divisible by 5          : 5
//   divisible by both       : 3
//   total digits            : 20
//
// === Part 2: are "both" and "divisible by 10" the same set? ===
//   divisible by both 2 and 5 : 3
//   divisible by 10          : 3
//   The two counts agree, so the sets are the same for this data.
//
// === Part 3: how the digit counter works on one value ===
// counting the digits of 250 by dividing by 10
//   250 / 10 = 25, keep dividing, count now 1
//   25 / 10 = 2, keep dividing, count now 2
//   2 / 10 = 0, keep dividing, count now 3
// 250 has 3 digits, and it took 3 divisions
// IMPORTANT SYNTAX:
// i % 2 == 0 && i % 5 == 0 -> true when BOTH tests are true
// ||                          -> true when AT LEAST ONE test is true
// digits = digits + 1         -> a counter step, the same idea as digits++
// n = n / 10                  -> integer division: drops the final digit
// do { ... } while (n != 0);  -> the body runs at least ONCE, even for 0
//
// STEP-BY-STEP EXPLANATION:
// 1. One `for` loop walks the array once. Inside it, four separate `if`
//    statements each test the same value, so four counters are filled in a
//    single pass instead of four passes over the same data.
// 2. Each `if` is independent: a value may be counted twice on purpose, as
//    250 is - once as divisible by 5, once as divisible by both, and once for
//    its digits. Independent tests are not a mistake here.
// 3. "Divisible by both 2 and 5" needs `&&`, because both must hold. Writing
//    two separate counters and hoping they line up would not tell you which
//    values were in both sets.
// 4. Counting digits needs a SECOND loop inside the first one. Division by 10
//    removes exactly one digit each time, so the number of divisions needed
//    is the number of digits: 250 takes three of them.
// 5. The inner loop must run at least once even when the value is 0, which is
//    what `do / while` guarantees. A plain `while` would skip it entirely and
//    report 0 as having no digits, which is wrong: 0 has one.
// ============================================================

#include <iostream>
// The only header this project needs. It supplies `cout` for printing and
// `endl` for ending a line. The C++ language itself can calculate, store and
// compare but it cannot talk to a screen, so every piece of terminal output
// comes from this library, and this include line is what makes it available.

using namespace std;
// A NAMESPACE is a labelled box that groups related names so two libraries
// cannot fight over the same word. `std` is the box belonging to the C++
// STANDARD library, where `cout` and `endl` live. The `::` is the SCOPE
// RESOLUTION OPERATOR and means "inside", so `std::cout` reads "the cout
// inside std". This line tells the compiler to take bare names from that box,
// which is why plain `cout` works throughout this file.

int main() {
// `main` is the ENTRY POINT: the first function the operating system runs when
// the program starts. `int` is the RETURN TYPE, handing a whole number back
// as an exit status when main finishes. `()` is the parameter list and it is
// empty, since this program takes no arguments and needs no keyboard input.
// The `{ }` braces are the BODY, executed from top to bottom.

    int stopMarker = 9999;

    int values[] = {7, 12, 25, 4, 100, 33, 8, 15, 0, 6, 250, 9, 9999};
    // Twelve real values, then the marker. Three of them are deliberately
    // awkward: 0 (which is divisible by everything and has one digit), 100
    // and 250 (which are divisible by 2, by 5 and by both).

    cout << "=== Part 1: four counts from a single pass over the array ===" << endl;

    // COUNTING THE LENGTH WITH A LOOP. This project may not use sizeof, so a
    // marker value at the end tells the loop when to stop. 0 would be a
    // disastrous marker here, because 0 is one of the real values.
    int n = 0;
    while (values[n] != stopMarker) {
        n++;
    }

    // FOUR COUNTERS, ALL CREATED BEFORE THE LOOP. A variable made inside the
    // braces is destroyed at the closing brace and reset every pass, so it
    // could never climb past 1.
    int byTwo = 0;
    int byFive = 0;
    int byBoth = 0;
    int totalDigits = 0;

    for (int i = 0; i < n; i++) {
        int v = values[i];

        if (v % 2 == 0) {
            byTwo++;
        }

        if (v % 5 == 0) {
            byFive++;
        }

        if (v % 2 == 0 && v % 5 == 0) {
            // `&&` is the LOGICAL AND: the test is true only when BOTH sides
            // are true. Written this way, one `if` counts the intersection of
            // the two sets. Writing two separate counters and comparing them
            // afterwards would give 7 and 5 but could never say WHICH values
            // belonged to both - which is usually the whole question.
            byBoth++;
            cout << v << ": divisible by both 2 and 5" << endl;
        }

        // COUNTING DIGITS WITH A DIVIDE-BY-10 LOOP. Division by 10 throws the
        // last digit away, so the number of times you can do it before
        // reaching nothing is exactly the number of digits. No logarithm and
        // no library function is involved - just integer division.
        //
        // `do / while` is used rather than `while` for one specific reason:
        // the body must run at least ONCE. For v = 0 a plain `while (v != 0)`
        // would never start and 0 would be reported as having no digits at
        // all, when it plainly has one.
        int copy = v;
        if (copy < 0) {
            copy = -copy;
            // A minus sign is not a digit, so the sign is dropped first. None
            // of the values in this array are negative; the guard is here
            // because the digit count would otherwise be wrong on any that were.
        }

        int digits = 0;
        do {
            digits++;
            // `copy = copy / 10` is INTEGER DIVISION: the fractional part is
            // discarded, so 250 / 10 is 25, and 25 / 10 is 2, and 2 / 10 is 0.
            // The digits disappear one at a time, from the right.
            copy = copy / 10;
        } while (copy != 0);
        // The test sits at the BOTTOM, so it is checked after the body. That
        // is why `digits` is already 1 for a single-digit number, and why a
        // plain `while (copy != 0)` would report 0 as having no digits at all.

        totalDigits = totalDigits + digits;
        // An ACCUMULATOR rather than a counter: it moves by the VALUE being
        // processed, not by 1. `digits++` would answer a different question
        // entirely - it would report the number of values, not their digits.

        if (v % 2 == 0) {
            cout << v << ": divisible by 2" << endl;
        }
        if (v % 5 == 0) {
            cout << v << ": divisible by 5" << endl;
        }
        cout << v << ": digit count = " << digits << endl;
        // These are separate `if` statements, not one `else if / else` chain,
        // and that is what lets a value such as 250 satisfy three of them at
        // once. A chain would run only the FIRST matching branch and silently
        // drop the rest.
    }
    cout << endl;

    cout << "Counts after one pass over " << n << " values:" << endl;
    cout << "  divisible by 2          : " << byTwo << endl;
    cout << "  divisible by 5          : " << byFive << endl;
    cout << "  divisible by both       : " << byBoth << endl;
    cout << "  total digits            : " << totalDigits << endl;
    cout << endl;

    cout << "=== Part 2: are \"both\" and \"divisible by 10\" the same set? ===" << endl;

    // THE IDENTITY, CHECKED RATHER THAN BELIEVED. A number divisible by 2 and
    // by 5 is divisible by 10, because 2 and 5 are factors of 10. Counting
    // both ways and finding them equal is cheap proof on this data.
    int byTen = 0;
    for (int i = 0; i < n; i++) {
        if (values[i] % 10 == 0) {
            byTen++;
        }
    }

    cout << "  divisible by both 2 and 5 : " << byBoth << endl;
    cout << "  divisible by 10          : " << byTen << endl;

    if (byBoth == byTen) {
        cout << "  The two counts agree, so the sets are the same for this data."
             << endl;
    } else {
        cout << "  The counts differ, so at least one test is wrong." << endl;
    }
    cout << endl;

    cout << "=== Part 3: how the digit counter works on one value ===" << endl;

    // ONE VALUE, EVERY STEP. Watching the copy shrink is the fastest way to
    // see that each division by 10 removes exactly one digit.
    int step = 250;
    int original = step;
    // `original` keeps a copy because `step` is about to be consumed. When the
    // loop ends `step` is 0, so printing it would report the wrong number.
    int count = 0;

    cout << "counting the digits of " << original << " by dividing by 10" << endl;
    while (step != 0) {
        cout << "  " << step << " / 10 = " << step / 10
             << ", keep dividing, count now " << count + 1 << endl;
        step = step / 10;
        count++;
    }

    cout << original << " has " << count
         << " digits, and it took " << count << " divisions" << endl;
    // `step` is 0 at this point, and `count` remembers what the number was.
    // That is why the last line prints `original` and not `step`.

    // ------------------------------------------------------------
    // TRACE TABLE - Part 1, one pass and four independent counters
    // ------------------------------------------------------------
    // +-------+-------+-------+---------+---------+---------+-----------+
    // | Iter. |   v   | v%2=0 | v%5=0   | v%2&&v%5| digits | Running    |
    // |       |       | byTwo | byFive  | byBoth  |        | digitTotal |
    // +-------+-------+-------+---------+---------+---------+-----------+
    // |   1   |    7  |  -    |   -     |    -    |    1    | 1          |
    // |   2   |   12  | yes 1 |   -     |    -    |    2    | 3          |
    // |   3   |   25  |   -  | yes 1   |    -    |    2    | 5          |
    // |   4   |    4  | yes 2|   -     |    -    |    1    | 6          |
    // |   5   |  100  | yes 3| yes 2   | yes 1  |    3    | 9          |
    // |   6   |   33  |   -  |   -     |    -    |    2    | 11         |
    // |   7   |    8  | yes 4|   -     |    -    |    1    | 12         |
    // |   8   |   15  |   -  | yes 3   |    -    |    2    | 14         |
    // |   9   |    0  | yes 5| yes 4   | yes 2  |    1    | 15         |
    // |  10   |    6  | yes 6|   -     |    -    |    1    | 16         |
    // |  11   |  250  | yes 7| yes 5   | yes 3  |    3    | 19         |
    // |  12   |    9  |   -  |   -     |    -    |    1    | 20         |
    // |  13   |  (none)|  -   |    -    |    -    |   -    | loop ended |
    // +-------+-------+-------+---------+---------+---------+-----------+
    // WHY THE LOOP STOPPED: n is 12, so `i < n` fails on the 13th test and the
    // body never runs again. The marker at index 12 is never examined.
    //
    // THREE ROWS WORTH STUDYING IN THAT TABLE
    //   v = 0 (row 9): 0 % 2 and 0 % 5 are both 0, so it is counted in byTwo,
    //   in byFive AND in byBoth. Zero is divisible by every number, and it has
    //   exactly one digit - which is what the `do / while` is there to get right.
    //   v = 250 (row 11): divisible by 2, by 5 and by both, so it moves three
    //   counters at once. Separate `if` statements allow this; a chain would not.
    //   v = 7 (row 1): every test fails, and it still contributes 1 to the
    //   digit total. A value matching no condition is not skipped - it is
    //   visited, tested, found wanting, and carried on with.
    //
    // TRACE TABLE - Part 3, the digit counter against 250
    // +-------+-------+-------------------+--------------+------------------+
    // | Step  | step  | step / 10         | step after   | digits          |
    // +-------+-------+-------------------+--------------+------------------+
    // |   1   |  250  | 25 - last digit 0 | 25           | 1               |
    // |   2   |   25  | 2  - last digit 5 | 2            | 2               |
    // |   3   |    2  | 0  - last digit 2 | 0            | 3               |
    // |   4   |    0  | test 0 != 0 fails | (none)       | 3  <- stop      |
    // +-------+-------+-------------------+--------------+------------------+
    // The loop stopped because the test `step != 0` failed after three
    // divisions. Integer division always throws the remainder away, so
    // dividing by 10 is what removes the final digit: 250 / 10 is 25 because
    // the 0 in the units column cannot be expressed as a fraction of a
    // whole number and is discarded.
    //
    // COMMON TRAP IN THIS FILE
    //   Counting digits with a `while` loop instead of `do / while`, then
    //   being surprised that 0 comes out as having zero digits. The test runs
    //   FIRST in a `while` loop, and 0 fails it immediately, so the body never
    //   executes and the counter is never raised even once. 0 has one digit,
    //   and `do / while` is the construct that guarantees the body runs at
    //   least once.
    //
    //   The second trap is writing the three divisibility tests as one chain:
    //       if (v % 2 == 0) { ... }
    //       else if (v % 5 == 0) { ... }
    //       else if (v % 2 == 0 && v % 5 == 0) { ... }
    //   Only the first matching branch can ever run, so the third can never
    //   run at all and byBoth would stay 0. Separate `if` statements are what
    //   let one value satisfy several conditions - which is the entire point
    //   of this file.

    return 0;
    // Ends main immediately and hands 0 back to the operating system. Zero is
    // the conventional code for "success": the program ran to its end without
    // an error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: How many of the twelve values are divisible by 2?  -> 7
// Q2: What does `v % 2 == 0 && v % 5 == 0` mean, and why not two separate if statements?  -> it is true only when both hold, so one test counts the values in both sets at once
// Q3: How do you count the digits of a whole number without a library?  -> divide by 10 over and over, counting the divisions, until the value reaches 0
// Q4: Why is `do / while` used for the digit count instead of `while`?  -> so the body runs at least once, because 0 fails the test straight away and would otherwise be reported as having no digits
// Q5: How many digits do all twelve values have altogether?  -> 20, and the total is an accumulator rather than a counter because it moves by 1, 2 or 3 at a time
