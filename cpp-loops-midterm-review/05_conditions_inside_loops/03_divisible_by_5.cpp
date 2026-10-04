// ============================================================
// PROGRAM: Divisible by 5 - the same test, and the last-digit shortcut
// TOPIC: the % operator applied to 5, counting and listing the matches
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - The identical divisibility test with a different divisor, so you can see
//   that nothing about `% 3` was a special case.
// - Why the test generalises: `n % d == 0` for ANY positive `d`.
// - The last-digit shortcut: a number ends in 0 or 5 if and only if it
//   divides evenly by 5.
// - The difference between `/` (integer division, which throws the remainder
//   away) and `%` (which keeps the remainder).
// - Counting and listing in one loop, with the separator placed before each
//   value so no line ever ends in a stray space.
//
// EXPECTED OUTPUT:
// === Part 1: the remainder table for division by 5 ===
// 0 % 5 = 0   <- divisible by 5
// 1 % 5 = 1
// 2 % 5 = 2
// 3 % 5 = 3
// 4 % 5 = 4
// 5 % 5 = 0   <- divisible by 5
// 6 % 5 = 1
// 7 % 5 = 2
// 8 % 5 = 3
// 9 % 5 = 4
// 10 % 5 = 0   <- divisible by 5
// 11 % 5 = 1
// 12 % 5 = 2
//
// === Part 2: which of 1 to 50 divide evenly by 5? ===
// They are: 5 10 15 20 25 30 35 40 45 50
// Count: 10
//
// === Part 3: the count and the check ===
// Every multiple of 5 ends in 0 or in 5.
// 50 tested, 10 kept - one value in every 5.
// 50 / 5 gives 10 by integer division, and the leftover 0 is exactly `50 % 5`.
//
// IMPORTANT SYNTAX:
// i % 5 == 0        -> true means "5 divides i evenly", so i is a multiple of 5
// i % 5 != 0        -> true means "5 does not divide i evenly"
// i / 5             -> integer division: the answer is truncated, no fraction
// i % 5             -> the REMAINDER that integer division threw away
// n % d == 0        -> the general test, for any positive divisor d
//
// STEP-BY-STEP EXPLANATION:
// 1. Part 1 repeats the pattern from the previous file with the divisor
//    changed to 5. The remainder column cycles 0, 1, 2, 3, 4 and then starts
//    over, because once 5 more would fit it is taken.
// 2. Only the 0 rows are multiples of 5: 0, 5, 10 - every fifth row. This is
//    the whole idea, printed out: `i % 5 == 0` is true on exactly those rows.
// 3. Part 2 walks 1 to 50 testing `i % 5 == 0`. Exactly 10 pass, and they are
//    listed in increasing order because the loop visits numbers in order.
// 4. Part 3 makes the shortcut explicit. Dividing a whole number by 5 leaves
//    a remainder of 0 or nothing else, and a remainder of 0 always means the
//    number ends in 0 or 5 - which is exactly the schoolbook rule.
// 5. `50 / 5` is 10 with the fraction discarded, and `50 % 5` is the part that
//    was discarded. Together they rebuild 50: 10 times 5 plus 0 is 50.
// ============================================================

#include <iostream>
// The only header this project needs. It provides `cout` for printing and
// `endl` for ending a line. The C++ language itself cannot talk to a screen -
// it can only calculate, store and compare - so all terminal output comes
// from this library, and this line is what invites it in.

using namespace std;
// A NAMESPACE is a labelled box grouping related names so that two libraries
// cannot both own the same word. `std` is the box holding the C++ STANDARD
// library, where `cout` and `endl` are kept. The `::` is the SCOPE RESOLUTION
// OPERATOR and means "inside", so `std::cout` means "the cout inside std".
// `using namespace std;` says "take bare names from that box", which is why
// `cout` can be written without any prefix below.

int main() {
// `main` is the ENTRY POINT: the first function the operating system runs when
// the program starts. `int` is the RETURN TYPE - a whole number handed back
// as an exit status when main finishes. `()` is the parameter list and it is
// empty, since this program takes no arguments and needs no keyboard input.
// The `{ }` braces are the BODY, run from top to bottom.

    cout << "=== Part 1: the remainder table for division by 5 ===" << endl;

    for (int n = 0; n <= 12; n++) {
        int remainder = n % 5;
        // `%` is the MODULO operator: divide, then hand back what is LEFT OVER.
        // The remainder is always smaller than the divisor, so it can only be
        // 0, 1, 2, 3 or 4 here - never 5, and never negative.

        cout << n << " % 5 = " << remainder;
        // Store the remainder in a named variable first. It costs one extra
        // line and buys two things: the test below reads like a sentence, and
        // the number cannot drift out of step with the value that was printed.

        if (remainder == 0) {
            cout << "   <- divisible by 5" << endl;
        } else {
            cout << endl;
        }
        // `==` ASKS "are these the same?" and answers true or false. A single
        // `=` here would be an ASSIGNMENT: it would store 0 into `remainder`
        // and the comment would claim everything is divisible by 5.
    }
    cout << endl;

    cout << "=== Part 2: which of 1 to 50 divide evenly by 5? ===" << endl;

    // The counter must be created BEFORE the loop. A variable declared inside
    // the braces is destroyed at the closing brace and rebuilt from scratch
    // every pass, so it could never get past 1.
    int count = 0;

    cout << "They are: ";

    for (int i = 1; i <= 50; i++) {
        if (i % 5 == 0) {
            // THE TEST. Read it inside out: `i % 5` divides i by 5 and keeps
            // the remainder; `== 0` asks whether the remainder is nothing.
            // Nothing left over means the division came out even, which is
            // what "5 divides i evenly" means in words.
            //
            // Nothing here is specific to 3. Swap the 5 for any positive
            // number and `n % d == 0` is the test for "d divides n evenly".
            count++;

            // The separator goes BEFORE the value, never after it. Printing a
            // space after every number would leave the line ending in a
            // stray space, which is invisible on screen but stops the output
            // from matching a written expected-output block exactly.
            if (count > 1) {
                cout << " ";
            }
            cout << i;
        }
    }
    cout << endl;
    cout << "Count: " << count << endl;
    cout << endl;

    cout << "=== Part 3: the count and the check ===" << endl;

    // THE LAST-DIGIT SHORTCUT, verified rather than asserted. If the test
    // `i % 5 == 0` is correct, then every value it accepts must end in 0 or 5
    // and no other value may do so. Counting both ways proves it.
    int endingInZeroOrFive = 0;
    for (int i = 1; i <= 50; i++) {
        int lastDigit = i % 10;
        // `% 10` is the classic way to peel off the final digit, for the same
        // reason `% 2` and `% 5` work: whatever is left over on division by 10
        // is by definition the ones column.
        if (lastDigit == 0 || lastDigit == 5) {
            // `||` is the LOGICAL OR: true when at least ONE of its two tests
            // is true. `&&` is the LOGICAL AND: true only when BOTH are true.
            // Neither is the same as the single `|` or `&` used on whole
            // numbers, which work on each bit rather than on true or false.
            endingInZeroOrFive++;
        }
    }

    if (count == endingInZeroOrFive) {
        cout << "Every multiple of 5 ends in 0 or in 5." << endl;
    } else {
        cout << "The two rules disagree, so one of them is wrong." << endl;
    }

    cout << 50 << " tested, " << count
         << " kept - one value in every 5." << endl;

    // `/` AND `%` ARE THE SAME DIVISION SPLIT IN TWO. `50 / 5` runs the
    // division and DISCARDS the remainder, giving exactly 10. `50 % 5` keeps
    // only the remainder, giving exactly 0. Put the two together and the
    // original number comes back: 10 lots of 5 plus 0 left over is 50.
    // This is why `n / d` never produces a decimal here - both operands are
    // whole numbers, so the fractional part is thrown away rather than kept.
    cout << 50 << " / 5 gives " << 50 / 5
         << " by integer division, and the leftover " << 50 % 5
         << " is exactly `50 % 5`." << endl;

    // ------------------------------------------------------------
    // TRACE TABLE - Part 2, testing `i % 5 == 0` over 1 to 50
    // ------------------------------------------------------------
    // The opening passes and the closing passes are shown; everything between
    // repeats the same five-row cycle.
    // +---------+-------------+-----------+-----------------+----------+------------------+
    // | Iteration| i at start | i % 5     | i % 5 == 0 ?    | count   | Output          |
    // +---------+-------------+-----------+-----------------+----------+------------------+
    // |    1    |      1      |     1     | FALSE           |    0     | (none)          |
    // |    2    |      2      |     2     | FALSE           |    0     | (none)          |
    // |    3    |      3      |     3     | FALSE           |    0     | (none)          |
    // |    4    |      4      |     4     | FALSE           |    0     | (none)          |
    // |    5    |      5      |     0     | TRUE            | 0 -> 1  | 5               |
    // |    6    |      6      |     1     | FALSE           |    1     | (none)          |
    // |   ...   |     ...     |    ...    | ...             |   ...   | ...             |
    // |   47    |     47      |     2     | FALSE           |    9     | (none)          |
    // |   48    |     48      |     3     | FALSE           |    9     | (none)          |
    // |   49    |     49      |     4     | FALSE           |    9     | (none)          |
    // |   50    |     50      |     0     | TRUE            | 9 -> 10 | 50              |
    // |   51    |    (none)   | not run  | 51 <= 50 FALSE  |   10    | (nothing)       |
    // +---------+-------------+-----------+-----------------+----------+------------------+
//
// WHY THE LOOP STOPPED AFTER 50 PASSES: the condition is checked BEFORE each
//     pass. Once the update makes i equal to 51, the test 51 <= 50 fails and
//     the body never runs again. Row 51 records that final failed test, which
//     is why no "55" appears anywhere in the output.
//
// THE COUNT COLUMN IS THE WHOLE STORY: flat on remainders 1 to 4, jumping by
//     one on remainder 0. It ends at 10 because one number in every five from
//     1 to 50 divides by 5 - and the loop confirms it rather than trusting it.
//
// PART 1 IN THE SAME FORM, for the record
//     +-------+-----------+-----------------------+
//     |   n   |  n % 5    | n % 5 == 0 ?          |
//     +-------+-----------+-----------------------+
//     |   0   |     0     | TRUE  - multiple of 5 |
//     |   1   |     1     | FALSE                 |
//     |   2   |     2     | FALSE                 |
//     |   3   |     3     | FALSE                 |
//     |   4   |     4     | FALSE                 |
//     |   5   |     0     | TRUE  - multiple of 5 |
//     |   6   |     1     | FALSE                 |
//     |   7   |     2     | FALSE                 |
//     |   8   |     3     | FALSE                 |
//     |   9   |     4     | FALSE                 |
//     |  10   |     0     | TRUE  - multiple of 5 |
//     +-------+-----------+-----------------------+
//     The column cycles 0, 1, 2, 3, 4 and then starts again from 0. A zero
//     appears only once in every five rows, which is the entire pattern the
//     divisibility test relies on.
//
// COMMON TRAP IN THIS FILE
//   Dividing by the number being tested instead of by the divisor, so writing
//       if (5 % i == 0) { ... }     // means "i divides 5 evenly"
//   The two operands are in the wrong order, and the test is not even false -
//   it is answering a different question. `5 % i == 0` is true only when i is
//   a FACTOR of 5, so it fires for 1 and 5 and stays silent for 10, 15 and 25.
//   The mnemonic that prevents it: the number you are testing comes FIRST, the
//   thing you are testing it for comes SECOND. Read `i % 5` aloud as "i
//   divided by 5", and the order stops being a matter of memory.
//   The second, quieter trap is `i % 5` on its own with no `== 0`, which
//   accepts the numbers that are NOT multiples of 5 - see the previous file.

    return 0;
    // Ends main and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran through to the end
    // without an error, so it is always written as the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: What does `n % 5 == 0` tell you about `n`?  -> that 5 divides n exactly, with nothing left over, so n is a multiple of 5
// Q2: Why can a remainder from dividing by 5 only ever be 0, 1, 2, 3 or 4?  -> a remainder is always strictly smaller than the divisor, because any more would have been taken
// Q3: How many of the numbers 1 to 50 divide evenly by 5?  -> 10, namely 5, 10, 15 up to 50
// Q4: What is the difference between `50 / 5` and `50 % 5`?  -> `/` runs the division and throws the remainder away giving 10, while `%` keeps only the remainder giving 0
// Q5: Why is `5 % i == 0` not a valid way to find multiples of 5?  -> the operands are reversed, so it asks whether i divides 5 evenly and is true only for 1 and 5
