// ============================================================
// PROGRAM: Nested Loops - Counting Things Inside Them
// TOPIC: where a counter must be declared, and what a break in the inner loop changes
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - How to count executions of the inner body, and how to check the count
//   against the multiplication.
// - How to count only the iterations that MATCH a condition, by guarding the
//   counter with an `if` placed inside the inner body.
// - Where a counter must be DECLARED, and what visibly goes wrong when it is
//   declared in the wrong place.
// - That `break` inside the INNER loop leaves only the inner loop: the outer
//   loop still gets every one of its passes, and the total changes anyway.
//
// EXPECTED OUTPUT:
// === the loops being counted: i is 1 to 3, j is 1 to 4 ===
// 3 x 4 = 12 possible executions of the inner body
//
// === (a) total inner executions ===
// the inner body ran 12 times, which matches 3 x 4 = 12
//
// === (b) iterations where i is the same as j ===
// (1,1)
// (2,2)
// (3,3)
// i == j happened 3 times
//
// === (c) iterations where i * j is even ===
// 1*2 (1,2)
// 1*4 (1,4)
// 2*1 (2,1)
// 2*2 (2,2)
// 2*3 (2,3)
// 2*4 (2,4)
// 3*2 (3,2)
// 3*4 (3,4)
// i * j is even 8 times out of 12
//
// === (d) the same loops, but with break in the INNER loop only ===
// the inner body now runs 6 times, not 12
// 1 + 2 + 3 = 6, because the inner loop stops once j passes i
// the outer loop still ran 3 times: break left the inner loop only
//
// === (e) the WRONG place to declare a counter ===
// a counter declared inside the outer loop is reset on every outer pass
// a correct counter would have printed 4, then 8, then 12
// outer pass 1 ended with the counter at 4
// outer pass 2 ended with the counter at 4
// outer pass 3 ended with the counter at 4
// it never reached 8 or 12, because it was thrown away at the start of
// each pass
// the real total across all three passes is 4 + 4 + 4 = 12, from handTotal
//
// IMPORTANT SYNTAX:
// int total = 0;                     -> DECLARE ONCE, before both loops
// total++;                            -> one more execution has happened
// if (i * j % 2 == 0) { total++; }   -> count only the matches, on purpose
// if (j > i) { break; }               -> leave the inner loop early; outer unaffected
//
// % IS THE REMAINDER OPERATOR, AND THAT IS HOW "EVEN" IS TESTED
//   i * j % 2      is the remainder after dividing by 2.
//   remainder 0    means the number divides evenly, i.e. it is EVEN.
//   remainder 1    means one is left over, i.e. it is ODD.
//   Note the two equals signs: `==` ASKS whether two things are equal and
//   produces true or false, while a single `=` STORES a value.
//
// THE ONE RULE THAT FIXES EVERY COUNTER BUG
//   DECLARE THE COUNTER BEFORE THE OUTER LOOP.  Never inside.  Never after.
//   Inside the outer loop it is destroyed and re-created at 0 on every pass,
//   so it can only ever report the work of the CURRENT pass.
//
// STEP-BY-STEP EXPLANATION:
// 1. The two loops are i = 1 to 3 and j = 1 to 4, so the inner body has
//    3 x 4 = 12 possible executions. Write that down first - every count in
//    this file is checked against it.
// 2. Part (a) counts all of them with `total++` and prints 12, matching the
//    multiplication. The count is a check on your reasoning, not a substitute.
// 3. Part (b) counts only the pairs where i equals j. There is exactly one
//    such pair per outer value, so 3. The counter goes INSIDE the `if`, which
//    is what makes it count matches instead of everything.
// 4. Part (c) counts even products. A product is even when either factor is
//    even, so all four pairs with i = 2 count, plus the even j values for the
//    odd i values: 4 + 2 + 2 = 8.
// 5. Part (d) puts a `break` in the inner loop only. The inner loop then stops
//    as soon as j passes i, so it runs 1, 2, 3, 4, 5... no: it runs 1 time on
//    row 1, 2 times on row 2 and 3 times on row 3, giving 1 + 2 + 3 = 6.
// 6. Part (e) is the counter bug, shown on purpose: it prints 4, 4, 4 where a
//    correct counter would print 4, 8, 12, because it is declared inside the
//    outer loop and so is rebuilt at 0 on every pass. The surviving counter
//    `handTotal` still reaches the right grand total of 12.
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

    cout << "=== the loops being counted: i is 1 to 3, j is 1 to 4 ===" << endl;
    cout << "3 x 4 = 12 possible executions of the inner body" << endl;

    cout << endl;
    cout << "=== (a) total inner executions ===" << endl;

    // THE COUNTER IS DECLARED HERE, OUTSIDE BOTH LOOPS. This single decision
    // is what makes every count in this file work. A variable declared inside a
    // loop is a brand new variable on every pass, starting again at its initial
    // value, so it can never remember anything from a previous pass.
    int total = 0;

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 4; j++) {
            // `total++` adds one. It is inside the INNER body, so it runs once
            // per execution of the inner body - which is exactly the thing
            // being counted. Nothing counts the outer passes, because the
            // question is not about them.
            total++;
        }
    }

    cout << "the inner body ran " << total << " times, which matches 3 x 4 = "
         << (3 * 4) << endl;
    // Printing the multiplication next to the counted result is the habit worth
    // building: if the two ever disagree, one of them is wrong, and now you
    // know which part of your reasoning to re-check.

    cout << endl;
    cout << "=== (b) iterations where i is the same as j ===" << endl;

    // A SECOND counter, also declared outside both loops, for a DIFFERENT
    // question. Two counters for two questions is normal and good practice -
    // it means neither count disturbs the other.
    int sameCount = 0;
    // THIS FLAG SOLVES A REAL PROBLEM: a gap is wanted BETWEEN matches but never
    // after the last one on a line, and printing `" "` after every match would
    // leave a trailing space at the end of each line. So instead of asking
    // "have I printed anything yet this line", the flag remembers whether
    // anything has EVER been printed, and only prints a gap from the second
    // match onwards.
    bool firstMatch = true;

    for (int i = 1; i <= 3; i++) {
        firstMatch = true;
        // THE FLAG MUST BE RESET AT THE START OF EVERY NEW LINE. A flag that is
        // never reset has forgotten the first line as well as this one, and
        // then the second line starts with a space where nothing should be.
        for (int j = 1; j <= 4; j++) {
            if (i == j) {
                if (firstMatch == false) {
                    cout << " ";
                }
                cout << "(" << i << "," << j << ")";
                firstMatch = false;
                sameCount++;
                // THE COUNTER GOES INSIDE THE `if`. That placement is the whole
                // difference between "count the matches" and "count
                // everything". Moving `sameCount++;` above the `if` would make
                // this part's answer 12 instead of 3.
            }
        }
        cout << endl;
    }

    cout << "i == j happened " << sameCount << " times" << endl;
    // One match per row, and each row prints only its own match. The three lines
    // above are produced by the single `cout << endl;` placed AFTER the inner
    // loop: one break per outer pass, never one per match.

    cout << endl;
    cout << "=== (c) iterations where i * j is even ===" << endl;

    int evenCount = 0;

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 4; j++) {
            // `i * j % 2 == 0` asks: after dividing i * j by 2, is the
            // remainder zero? The `%` operator is the MODULO, the remainder.
            // A zero remainder means the division comes out even, so this test
            // is the standard way of asking "is this number even?".
            if (i * j % 2 == 0) {
                cout << i << "*" << j << " (" << i << "," << j << ")" << endl;
                evenCount++;
                // Only the MATCHING pairs are printed, so the output itself is
                // the evidence for the count. Print the pairs and count them
                // and you can check the answer with your own eyes.
            }
        }
    }

    cout << "i * j is even " << evenCount << " times out of 12" << endl;
    // 8 out of 12. Reason it out before trusting the program: i = 1 is odd, so
    // only the even j values (2 and 4) give an even product - 2 of them. i = 2
    // is even, so every j gives an even product - 4 of them. i = 3 is odd, so
    // again only j = 2 and j = 4 count - 2 of them. 2 + 4 + 2 = 8.

    cout << endl;
    cout << "=== (d) the same loops, but with break in the INNER loop only ===" << endl;

    int breakTotal = 0;

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 4; j++) {
            if (j > i) {
                break;
                // `break` LEAVES THE INNERMOST LOOP THAT CONTAINS IT - which
                // here is the inner loop, and only that one. The outer loop
                // does not notice: control lands on the statement after the
                // inner loop's closing brace, the outer body's remaining lines
                // run, `i++` happens, and the outer loop carries on exactly as
                // before. So the outer loop still passes 3 times while the
                // inner loop does less work each time.
            }
            breakTotal++;
            // This line is only reached for j values that do NOT trigger the
            // break. That is why the total falls: the pairs that would have
            // triggered the break are never counted.
        }
    }

    cout << "the inner body now runs " << breakTotal << " times, not 12" << endl;
    cout << "1 + 2 + 3 = 6, because the inner loop stops once j passes i" << endl;
    cout << "the outer loop still ran 3 times: break left the inner loop only" << endl;
    // Worked out: on row i = 1 the inner loop gets j = 1 and then breaks, so 1
    // counted. On row 2 it gets j = 1, j = 2 and breaks, so 2 counted. On row 3
    // it gets j = 1, j = 2, j = 3 and breaks, so 3 counted. 1 + 2 + 3 = 6.

    cout << endl;
    cout << "=== (e) the WRONG place to declare a counter ===" << endl;
    cout << "a counter declared inside the outer loop is reset on every outer pass"
         << endl;
    cout << "a correct counter would have printed 4, then 8, then 12" << endl;

    int handTotal = 0;

    for (int i = 1; i <= 3; i++) {
        // THE BUG, WRITTEN ON PURPOSE SO YOU CAN SEE IT HAPPEN.
        // This counter is declared INSIDE the outer loop's body, so on each of
        // the three outer passes the compiler builds a fresh variable starting
        // at 0. It counts the CURRENT pass perfectly well, and then it is
        // destroyed, so the next pass starts from nothing again. The correct
        // sequence would be 4, 8, 12 - a running total. This one prints 4, 4, 4.
        int innerCount = 0;

        for (int j = 1; j <= 4; j++) {
            innerCount++;
            handTotal++;
            // `handTotal` is outside both loops and survives, which is why the
            // real total of 4 + 4 + 4 is still right even though the per-pass
            // figure printed below is useless.
        }

        cout << "outer pass " << i << " ended with the counter at " << innerCount << endl;
    }

    cout << "it never reached 8 or 12, because it was thrown away at the start of"
         << endl;
    cout << "each pass" << endl;
    cout << "the real total across all three passes is 4 + 4 + 4 = " << handTotal
         << ", from handTotal" << endl;
    // The symptom is unmistakable: the same number printed three times where a
    // rising sequence was expected. If a counter prints 4, 4, 4 in a loop whose
    // three passes clearly do more work than one pass, the declaration is in
    // the wrong place - move it above the outer loop and the 8 and the 12
    // appear on their own.

    // ------------------------------------------------------------
    // THE GROUPED TRACE OF PART (a) - the reference version to check
    // every other count in this file against
    // ------------------------------------------------------------
    //   i = 1
    //       j = 1
    //       j = 2
    //       j = 3
    //       j = 4
    //
    //   i = 2
    //       j = 1
    //       j = 2
    //       j = 3
    //       j = 4
    //
    //   i = 3
    //       j = 1
    //       j = 2
    //       j = 3
    //       j = 4
    //
    //   3 groups x 4 inner steps = 12 executions of the inner body
    //
    // ------------------------------------------------------------
    // TRACE TABLE - all 12 iterations, with all three counts side by side
    // +------+---------+---------+---------+-----------+----------+----------+
    // | Pass | Outer i | Inner j | i == j  | i * j % 2 | b) count | c) count |
    // +------+---------+---------+---------+-----------+----------+----------+
    // |   1  |    1    |    1    |   YES   |     1     |    1     |    0     |
    // |   2  |    1    |    2    |   no    |     0     |    0     |    1     |
    // |   3  |    1    |    3    |   no    |     1     |    0     |    0     |
    // |   4  |    1    |    4    |   no    |     0     |    0     |    1     |
    // |   5  |    2    |    1    |   no    |     0     |    0     |    1     |
    // |   6  |    2    |    2    |   YES   |     0     |    1     |    1     |
    // |   7  |    2    |    3    |   no    |     0     |    0     |    1     |
    // |   8  |    2    |    4    |   no    |     0     |    0     |    1     |
    // |   9  |    3    |    1    |   no    |     1     |    0     |    0     |
    // |  10  |    3    |    2    |   no    |     0     |    0     |    1     |
    // |  11  |    3    |    3    |   YES   |     1     |    1     |    0     |
    // |  12  |    3    |    4    |   no    |     0     |    0     |    1     |
    // +------+---------+---------+---------+-----------+----------+----------+
    // | TOT  | 3 rows  | 4 each  |  3 YES  |  8 zeroes |    3     |    8     |
    // +------+---------+---------+---------+-----------+----------+----------+
    //
    // Reading the table: 12 passes in total, which is the answer to (a). The
    // "i == j" column says YES three times, which is the answer to (b). The
    // remainder column says 0 eight times, and a remainder of 0 is an even
    // product, which is the answer to (c).
    //
    // WHERE EACH COUNTER MUST BE PLACED - THE WHOLE FILE IN ONE TABLE
    // +----------------------+---------------------+------------------------------+
    // | Counter              | Declared            | Why                          |
    // +----------------------+---------------------+------------------------------+
    // | (a) total            | before BOTH loops   | must survive all 12 passes    |
    // | (b) sameCount        | before BOTH loops   | one answer for the whole run  |
    // | (c) evenCount        | before BOTH loops   | one answer for the whole run  |
    // | breakTotal           | before BOTH loops   | adds up across many rows      |
    // | innerCount in (e)    | INSIDE outer loop   | the BUG: reset every pass    |
    // +----------------------+---------------------+------------------------------+
    //
    // WHAT A break IN THE INNER LOOP CHANGES, AND WHAT IT DOES NOT
    //   CHANGES: the number of executions of the inner body (12 becomes 6), and
    //            therefore any count taken from inside it.
    //   DOES NOT CHANGE: how many times the outer loop passes - still 3 - and
    //            the values of i, which still run 1, 2, 3 in order. A break in
    //            the inner loop has no way of touching the outer loop at all.
    //
    //   To end an OUTER loop early you need something else, because C++ has no
    //   keyword for it: put the test in the outer loop's own CONDITION, so the
    //   outer loop finishes by itself when the condition becomes false.
    //
    // COMMON TRAP
    //   Putting the counter's `++` OUTSIDE the `if` that checks the condition.
    //   Then the counter counts every iteration rather than the matching ones,
    //   and the answer comes out as 12 where 3 was wanted. The counter's job is
    //   to record the MATCH, so it has to live inside the test that decides
    //   what a match is.
    //
    //   The second trap is writing `if (i * j = 0)` with one equals sign. That
    //   does not ask a question: it STORES 0 into the expression i * j, which
    //   is not a variable, so the program will not even compile. Two equals
    //   signs ask, one equals sign stores.
    //
    //   The third trap is assuming `break` in the inner loop ends the outer one
    //   too. It does not, and part (d) proves it by printing that the outer
    //   loop still made all three passes.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: How many times does the inner body of these two loops run in total?  -> 12 times, from 3 outer passes x 4 inner passes
// Q2: Where must a counter be declared so it can total up all 12 iterations?  -> before the outer loop, so that neither loop destroys and resets it on every pass
// Q3: Why must the counter in part (c) be inside the `if`?  -> so it counts only the iterations where i * j is even, instead of counting all 12 of them
// Q4: With the `break` in the inner loop, how many iterations are counted, and why is it not 12?  -> 6, because the inner loop stops once j passes i, giving 1 + 2 + 3 instead of 4 + 4 + 4
// Q5: Does a `break` inside the inner loop reduce the number of outer passes?  -> no, it leaves only the innermost loop, so the outer loop still passes 3 times with i = 1, 2, 3
