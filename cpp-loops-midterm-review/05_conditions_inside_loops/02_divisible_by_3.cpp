// ============================================================
// PROGRAM: Divisible by 3 - the modulo operator and its remainder table
// TOPIC: the % operator, testing divisibility, and != as well as ==
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - The `%` operator properly: divide, then hand back what is LEFT OVER.
// - A full printed remainder table, so `n % d == 0` means "divides evenly by
//   d" is something you can see rather than something you have to trust.
// - How to COUNT the values that pass a test and how to LIST them.
// - `!=` - the not-equal comparison - which finds exactly the values that
//   fail the same test, so the two halves of a division always add up.
// - Why the separator is printed BEFORE each value, not after it.
//
// EXPECTED OUTPUT:
// === Part 1: the remainder table for 2, 3, 5 and 10 ===
// 0 % 2 = 0,  0 % 3 = 0,  0 % 5 = 0,  0 % 10 = 0
// 1 % 2 = 1,  1 % 3 = 1,  1 % 5 = 1,  1 % 10 = 1
// 2 % 2 = 0,  2 % 3 = 2,  2 % 5 = 2,  2 % 10 = 2
// 3 % 2 = 1,  3 % 3 = 0,  3 % 5 = 3,  3 % 10 = 3
// 4 % 2 = 0,  4 % 3 = 1,  4 % 5 = 4,  4 % 10 = 4
// 5 % 2 = 1,  5 % 3 = 2,  5 % 5 = 0,  5 % 10 = 5
// 6 % 2 = 0,  6 % 3 = 0,  6 % 5 = 1,  6 % 10 = 6
// 7 % 2 = 1,  7 % 3 = 1,  7 % 5 = 2,  7 % 10 = 7
// 8 % 2 = 0,  8 % 3 = 2,  8 % 5 = 3,  8 % 10 = 8
// 9 % 2 = 1,  9 % 3 = 0,  9 % 5 = 4,  9 % 10 = 9
// 10 % 2 = 0,  10 % 3 = 1,  10 % 5 = 0,  10 % 10 = 0
// 11 % 2 = 1,  11 % 3 = 2,  11 % 5 = 1,  11 % 10 = 1
// 12 % 2 = 0,  12 % 3 = 0,  12 % 5 = 2,  12 % 10 = 2
//
// === Part 2: which of 1 to 30 divide evenly by 3? ===
// They are: 3 6 9 12 15 18 21 24 27 30
// Count: 10
//
// === Part 3: which of 1 to 30 do NOT divide evenly by 3? ===
// They are: 1 2 4 5 7 8 10 11 13 14 16 17 19 20 22 23 25 26 28 29
// Count: 20
//
// The two lists hold 10 + 20 = 30 values, which is every number visited.
//
// IMPORTANT SYNTAX:
// n % d              -> divide n by d and hand back the REMAINDER, never a fraction
// n % 3 == 0         -> TRUE means "3 divides n evenly", so n is a multiple of 3
// n % 3 != 0         -> the exact opposite: TRUE means "3 does NOT divide n"
// n % d == 0         -> the general rule: a remainder of zero means even division
// cout << n << " ";  -> be careful, a space printed AFTER the last value is wasted
//
// STEP-BY-STEP EXPLANATION:
// 1. Part 1 prints a remainder table straight from the computer, so the rule
//    can be checked rather than believed. Read any row across: the value under
//    `% 3` is only 0 once every third row - 0, 3, 6, 9, 12.
// 2. Every remainder is smaller than the divisor and never negative. That is
//    why dividing by 3 can only ever leave 0, 1 or 2 behind, and a zero means
//    there was nothing left over at all.
// 3. Part 2 visits 1 to 30 and tests `i % 3 == 0` on each one. Ten numbers
//    pass: 3, 6, 9 up to 30. The counter is raised once per hit and never
//    otherwise, so it answers "how many", not "how much".
// 4. Part 3 flips the test to `i % 3 != 0`. `!=` is the NOT-EQUAL comparison
//    - an `=` that asks a question, with the `!` (bang, read "not") in front
//    of it. It catches the other 20 numbers.
// 5. 10 + 20 = 30 is the sanity check: the two tests are exact opposites and
//    between them they account for every pass the loop made.
// ============================================================

#include <iostream>
// The one header this project uses. It supplies `cout` for output and `endl`
// for ending a line. The C++ language on its own can calculate and compare but
// it cannot talk to a screen, so every printing command comes from this
// library - which is exactly why the include line must come first.

using namespace std;
// A NAMESPACE is a labelled box that groups related names so two libraries
// cannot fight over one word. `std` is the box belonging to the C++ STANDARD
// library, where `cout` lives. The `::` is the SCOPE RESOLUTION OPERATOR and
// means "inside", so `std::cout` reads "the cout inside std". This line tells
// the compiler to look for bare names such as `cout` in that box, which saves
// writing `std::` in front of every single print statement.

int main() {
// `main` is the ENTRY POINT: the first function the operating system runs when
// the program starts. `int` is the RETURN TYPE, so a whole number is handed
// back as an exit status when it finishes. `()` is the parameter list, and it
// is empty because this program needs no keyboard input. The `{ }` are the
// BODY, executed from top to bottom.

    cout << "=== Part 1: the remainder table for 2, 3, 5 and 10 ===" << endl;

    // `%` is the MODULO operator: divide the left value by the right value and
    // keep only the REMAINDER - what is left over. It never produces a
    // fraction, and that is what makes it so useful for spotting multiples.
    for (int n = 0; n <= 12; n++) {
        // Printing the four remainders side by side lets you SEE the pattern.
        // Column `% 2` is 0 on every even row, column `% 5` is 0 only on rows
        // 0, 5 and 10, and column `% 10` is 0 only on row 0 and row 10.
        cout << n << " % 2 = " << n % 2 << ",  "
             << n << " % 3 = " << n % 3 << ",  "
             << n << " % 5 = " << n % 5 << ",  "
             << n << " % 10 = " << n % 10 << endl;
        // Note the parentheses are not needed: `<<` and `%` are evaluated
        // right to left, so the remainder is worked out before the printing.
    }
    cout << endl;

    cout << "=== Part 2: which of 1 to 30 divide evenly by 3? ===" << endl;

    // THE COUNTER. It has to be created before the loop, because a variable
    // declared inside the braces is destroyed at the closing brace and would
    // start again from 0 on every single pass.
    int count = 0;

    cout << "They are: ";

    for (int i = 1; i <= 30; i++) {
        if (i % 3 == 0) {
            // THE WHOLE TEST, SPOKEN OUT LOUD: "when i is divided by 3, is
            // there anything left over?" If the answer is no, then 3 divides
            // i evenly and i is a multiple of 3.
            //
            // `==` asks the question and answers true or false. A single `=`
            // would be an ASSIGNMENT - it would store 0 into i and destroy
            // the loop counter, so the loop would never end.
            //
            // The counter answers HOW MANY, so it moves by exactly 1 per hit:
            //     count++;              shorthand for count = count + 1;
            // Writing `count = count + i;` here would add the values up
            // instead of counting them, and would answer a different question.
            count++;

            // THE SEPARATOR IS PRINTED BEFORE THE VALUE, NOT AFTER IT.
            // Printing a space after every number would leave the last line
            // with a trailing space - invisible on screen, but it makes the
            // expected output in this comment block impossible to match.
            // Testing `count > 1` puts the space in front of the 2nd, 3rd, 4th
            // ... value and leaves the first value with nothing in front of it.
            if (count > 1) {
                cout << " ";
            }
            cout << i;
        }
        // Numbers that fail the test are still VISITED - they are simply not
        // printed. Visiting, testing and printing are three separate actions.
    }
    cout << endl;
    cout << "Count: " << count << endl;
    cout << endl;

    cout << "=== Part 3: which of 1 to 30 do NOT divide evenly by 3? ===" << endl;

    // `!=` is the NOT-EQUAL comparison: the `!` (bang, read "not") in front of
    // the equal sign. It asks "are these two different?" It is the exact
    // opposite of `==`, so between them the two tests cover every pass.
    int otherCount = 0;

    cout << "They are: ";

    for (int i = 1; i <= 30; i++) {
        if (i % 3 != 0) {
            if (otherCount > 0) {
                cout << " ";
            }
            cout << i;
            otherCount++;
        }
    }
    cout << endl;
    cout << "Count: " << otherCount << endl;
    cout << endl;

    cout << "The two lists hold " << count << " + " << otherCount
         << " = " << count + otherCount << " values, which is every number visited."
         << endl;

    // ------------------------------------------------------------
    // TRACE TABLE - Part 2, testing `i % 3 == 0` over 1 to 30
    // ------------------------------------------------------------
    // The first few passes and the last few are shown; the rows between them
    // repeat the same three-pattern cycle over and over.
    // +---------+-------------+-----------+------------------+----------+---------------+
    // | Iteration| i at start | i % 3     | i % 3 == 0 ?     | count   | Output        |
    // +---------+-------------+-----------+------------------+----------+---------------+
    // |    1    |      1      |     1     | FALSE            |    0     | (none)        |
    // |    2    |      2      |     2     | FALSE            |    0     | (none)        |
    // |    3    |      3      |     0     | TRUE             | 0 -> 1  | 3             |
    // |    4    |      4      |     1     | FALSE            |    1     | (none)        |
    // |   ...   |     ...     |    ...    | ...              |   ...   | ...           |
    // |   28    |     28      |     1     | FALSE            |    9     | (none)        |
    // |   29    |     29      |     2     | FALSE            |    9     | (none)        |
    // |   30    |     30      |     0     | TRUE             | 9 -> 10 | 30            |
    // |   31    |      -      |  not run | 31 <= 30 is FALSE|   10    | (nothing)     |
    // +---------+-------------+-----------+------------------+----------+---------------+
    //
    // WHY THE LOOP STOPPED AFTER 30 PASSES: the condition `i <= 30` is tested
    // BEFORE each pass, not after. Once the update has made i equal to 31,
    // 31 <= 30 is false, so the body never runs again. The 31st row records
    // that final failed test, which produces no output of any kind.
    //
    // READ THE count COLUMN: it is flat on the 1s and the 2s and rises by one
    // on every 0. That flat-then-jump pattern is the fingerprint of a counter
    // working correctly, and it is exactly what a wrong counter such as
    // `count = count + i` would destroy.
    //
    // WHY A REMAINDER IS ALWAYS SMALLER THAN THE DIVISOR
    //   Dividing by 3 can only leave 0, 1 or 2 - never 3 and never a negative
    //   value, because as soon as 3 more fit they would have been taken. That
    //   single fact explains both halves of the table above: the column can
    //   only ever contain those three symbols, and a 0 there is unambiguous.
    //
    // COMMON TRAP IN THIS FILE
    //   Testing `i % 3` on its own, without `== 0`:
    //       if (i % 3) { ... }
    //   This is the trap that catches nearly everybody, because it looks
    //   almost right. A remainder of 0 is treated as FALSE, so the body runs
    //   on the 1s and the 2s - the block executes for numbers that are NOT
    //   multiples of 3, which is precisely backwards. Written the other way
    //   round, `if (i % 3 != 0)`, the test finally means what it looks like.
    //   `i % 3` is a NUMBER, and only 0 is false; `i % 3 == 0` is a
    //   QUESTION, and it asks the question you actually meant.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end with no
    // error. Anything after this line would never be reached.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: What does the `%` operator return when used on two whole numbers?  -> the remainder after dividing the left value by the right value
// Q2: How do you test whether a variable `n` is a multiple of 3?  -> with `n % 3 == 0`, which is true when nothing is left over
// Q3: Why does `if (i % 3)` without the `== 0` run for the wrong numbers?  -> a remainder of 0 counts as false, so the body runs on the 1s and 2s instead of the multiples
// Q4: How many of the numbers 1 to 30 divide evenly by 3?  -> 10, namely 3, 6, 9 up to 30
// Q5: What do `count++` and `count = count + i;` ask, and why must they not be swapped?  -> the first counts how many numbers passed the test, the second adds their values up, which is a different question
