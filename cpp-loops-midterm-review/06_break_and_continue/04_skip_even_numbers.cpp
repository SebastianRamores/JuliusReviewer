// ============================================================
// PROGRAM: Printing Only the Odd Numbers - Three Ways to Get One Output
// TOPIC: solving the same problem with continue, with if, and with a step
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - One job done three different ways, all producing identical output, so the
//   difference between the approaches is the only thing left to notice.
// - Solution 1: `continue` skips the even numbers and prints the rest.
// - Solution 2: no `continue` at all - the `if` simply wraps the printing, so
//   nothing is ever "skipped" because nothing has to be.
// - Solution 3: no test at all - the loop steps by 2, so every value it visits
//   is already odd and the `if` can be deleted completely.
// - Why solution 3 is the shortest and fastest, and when solutions 1 and 2 are
//   still the right choice.
//
// EXPECTED OUTPUT:
// === Solution 1: if with continue ===
// 1 3 5 7 9
// === Solution 2: a plain if around the printing, no continue ===
// 1 3 5 7 9
// === Solution 3: step the loop by 2 and test nothing ===
// 1 3 5 7 9
// All three solutions print exactly the same five numbers.
// Solution 3 made 5 passes; solutions 1 and 2 each made 10.
//
// IMPORTANT SYNTAX:
// for (int i = 1; i <= 10; i++)   -> visits every value and tests each one
// for (int i = 1; i <= 10; i += 2) -> visits only the values it cares about
// continue;    -> skip the rest of this pass, which is how solution 1 filters
// if (i % 2 != 0) { print }  -> simply choose whether to print, no skipping
//
// STEP-BY-STEP EXPLANATION:
// 1. All three loops start at 1 and are meant to print 1 to 10's odd numbers.
// 2. Solution 1 visits all ten values, tests each one, and `continue`s away
//    from the four even ones before reaching the printing.
// 3. Solution 2 visits all ten values too, but nothing is skipped - the `if`
//    simply decides whether to run the printing or not.
// 4. Solution 3 starts at 1, adds 2 each time, and never even sees an even
//    value. Five passes instead of ten, and no test inside the body.
// 5. The rules to take away: if the loop visits a value and does not want it,
//    use `continue` or an `if`. If the values you want form a regular step,
//    change the UPDATE instead and delete the test.
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
// empty, since this program takes no arguments and reads no keyboard input.
// The `{ }` braces are the BODY, executed from top to bottom.

    // ONE COUNTER, REUSED THREE TIMES. It counts what has been printed so far,
    // and that is all it is for: putting the separator BEFORE each number so
    // no line ends in a stray space. It has to be reset to 0 before each new
    // solution, or the first number of solution 2 would be preceded by a
    // space because solution 1 had already printed something.
    int printed = 0;

    cout << "=== Solution 1: if with continue ===" << endl;

    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            // THE EVEN NUMBERS ARE REFUSED HERE. `%` is the modulo operator:
            // divide i by 2 and keep the remainder. `i % 2 == 0` is true
            // exactly when the division came out even, which is what "even"
            // means.
            //
            // `continue` abandons the rest of this pass, so the printing two
            // lines below is never reached for 2, 4, 6, 8 or 10. The loop
            // still carries on and still visits them.
            continue;
        }

        if (printed > 0) {
            cout << " ";
        }
        cout << i;
        printed++;
    }
    cout << endl;

    // RESET THE COUNTER, because it must count this solution's output alone.
    printed = 0;

    cout << "=== Solution 2: a plain if around the printing, no continue ===" << endl;

    for (int i = 1; i <= 10; i++) {
        if (i % 2 != 0) {
            // `!=` is the NOT-EQUAL comparison - an `=` that asks a question,
            // with the `!` (bang, read "not") in front of it. So the test is
            // "is the remainder something OTHER than zero", which is true
            // exactly for the odd numbers. Swapping `== 0` for `!= 0` is the
            // only difference between the two tests.
            //
            // There is NO `continue` anywhere in this solution, and that is
            // the whole point of it. Nothing is "skipped": every value is
            // visited, tested, and either printed or quietly passed over.
            if (printed > 0) {
                cout << " ";
            }
            cout << i;
            printed++;
        }
    }
    cout << endl;

    printed = 0;

    cout << "=== Solution 3: step the loop by 2 and test nothing ===" << endl;

    int passes = 0;

    for (int i = 1; i <= 10; i += 2) {
        // THE ONLY CHANGE IS THE UPDATE. `i += 2` adds 2 each pass instead of
        // 1, so the loop visits 1, 3, 5, 7, 9 and then 11 - and 11 fails the
        // condition, so the loop ends. Every value it ever visits is odd, so
        // the test has been deleted completely. Nothing is skipped because
        // the loop never goes near an even number.
        passes++;

        if (printed > 0) {
            cout << " ";
        }
        cout << i;
        printed++;
    }
    cout << endl;

    cout << "All three solutions print exactly the same five numbers." << endl;
    cout << "Solution 3 made " << passes
         << " passes; solutions 1 and 2 each made 10." << endl;

    // ------------------------------------------------------------
    // TRACE TABLE - the three loops compared, pass by pass
    // ------------------------------------------------------------
    // +-------+-----------+------------------------+------------------------+--------------------+
    // | Pass  | i in      | Solution 1            | Solution 2            | Solution 3        |
    // |       | solutions | (continue)            | (plain if)            | (i += 2)          |
    // |       | 1 and 2   |                        |                       |                    |
    // +-------+-----------+------------------------+------------------------+--------------------+
    // |   1   |     1     | prints 1              | prints 1              | prints 1          |
    // |   2   |     2     | continue, nothing     | test fails, nothing   | i is now 3        |
    // |   3   |     3     | prints 3              | prints 3              | prints 3          |
    // |   4   |     4     | continue, nothing     | test fails, nothing   | i is now 5        |
    // |   5   |     5     | prints 5              | prints 5              | prints 5          |
    // |   6   |     6     | continue, nothing     | test fails, nothing   | i is now 7        |
    // |   7   |     7     | prints 7              | prints 7              | prints 7          |
    // |   8   |     8     | continue, nothing     | test fails, nothing   | i is now 9        |
    // |   9   |     9     | prints 9              | prints 9              | prints 9          |
    // |  10   |    10     | continue, nothing     | test fails, nothing   | i is 11, loop ends|
    // |  11   |    11     | 11 <= 10 FALSE, ends  | 11 <= 10 FALSE, ends  | (never happens)   |
    // +-------+-----------+------------------------+------------------------+--------------------+
    //
    // WHY THE LOOP STOPPED, IN EACH CASE. Solutions 1 and 2 ended on pass 11 the ordinary
    // way: the update made i equal to 11, the test 11 <= 10 failed, and the
    // body never ran again. Solution 3 ended on its tenth pass instead, and
    // for the same kind of reason - the update made i equal to 11 and the test
    // failed. It simply got there in 5 passes instead of 10, because each pass
    // added 2 rather than 1.
    //
    // READ THE "NOTHING" CELLS CAREFULLY, because they are not the same thing
    // in columns 2 and 3. In solution 1 something HAPPENED on the even
    // passes: `continue` executed and jumped forward to the update. In
    // solution 2 the `if` was simply false and the pass ran to its end like
    // any other. The output is identical either way, which is precisely why
    // `continue` is a convenience rather than a necessity - it flattens a
    // loop by removing one level of nesting.
    //
    // WHY SOLUTION 3 IS THE BEST OF THE THREE
    //   It makes half as many passes, so it does half the work. It contains
    //   no test at all, so there is nothing to get wrong. And it cannot fall
    //   out of step with the data, because there is no data and no condition
    //   to disagree with. Prefer it whenever the values you want form a
    //   regular step.
    //
    //   Solutions 1 and 2 remain correct - and necessary - when the rule is
    //   irregular. "Print the numbers with an even digit count" has no step
    //   to exploit, so the loop must visit everything and test each one.
    //
    // COMMON TRAP IN THIS FILE
    //   Using solution 3's update on an even starting value and expecting
    //   odd numbers: `for (int i = 2; i <= 10; i += 2)` prints 2, 4, 6, 8, 10
    //   - every EVEN number, because the step is even and the first value is
    //   even. The starting value must match the parity of the step. The second
    //   trap is forgetting that `i += 2` will overshoot the end: with a limit
    //   of 10 the loop visits 11 and stops, which is harmless, but with a
    //   limit of 11 it would print 11 as well, because 11 is odd and it sits
    //   exactly on the boundary.

    return 0;
    // Ends main immediately and hands 0 back to the operating system. Zero is
    // the conventional code for "success": the program ran to its end without
    // an error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: What do solutions 1 and 2 have in common?  -> both visit all ten values and test each one, differing only in whether `continue` skips the rest of the pass or the `if` guards the printing
// Q2: Why is solution 3 shorter than the other two?  -> the loop steps by 2, so it never visits an even value and the test can be deleted completely
// Q3: How many passes does each solution make?  -> solutions 1 and 2 make 10 each, while solution 3 makes only 5
// Q4: Why must the starting value in solution 3 be odd?  -> the step is also even, so starting at 2 would keep every value even and print 2, 4, 6, 8 and 10 instead
// Q5: When would solutions 1 and 2 be the better choice?  -> when the values to keep have no regular step, such as numbers with an even digit count, so every value must be visited and tested
