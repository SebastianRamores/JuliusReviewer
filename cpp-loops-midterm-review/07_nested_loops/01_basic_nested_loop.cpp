// ============================================================
// PROGRAM: Nested Loops - A Loop Inside a Loop
// TOPIC: the outer loop, the inner loop, and counting the total work
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - How to write one loop inside the body of another loop.
// - The two names you must use in an exam: the OUTER LOOP and the INNER LOOP.
// - That the inner loop is restarted FROM ITS VERY FIRST LINE every single time
//   the outer loop comes round again. It never carries on where it stopped.
// - How to PROVE how many times the inner body runs: multiply, do not add.
// - How to draw a trace grouped into one block of inner steps per outer value.
//
// EXPECTED OUTPUT:
// === Part 1: the OUTER loop drives the INNER loop ===
// i = 1   j = 1
// i = 1   j = 2
// i = 2   j = 1
// i = 2   j = 2
// i = 3   j = 1
// i = 3   j = 2
//
// === Part 2: proof - the inner body ran 6 times ===
// the outer loop ran 3 times, and the inner loop ran 2 times each time
// 3 x 2 = 6 executions of the inner body
// the proof is not a guess: the program counted all 6 of them
//
// === Part 3: the grouped trace, one full inner loop per outer pass ===
//   i = 1
//       j = 1
//       j = 2
//
//   i = 2
//       j = 1
//       j = 2
//
//   i = 3
//       j = 1
//       j = 2
//
// === Part 4: the total is a MULTIPLICATION, not an addition ===
// adding the passes:    2 + 2 + 2 = 6
// multiplying instead:  3 x 2     = 6
// both give the same answer, but only one of them keeps working when the
// numbers get bigger
//
// IMPORTANT SYNTAX:
// for (int i = 1; i <= 3; i++) {      -> the OUTER loop: it runs 3 times
//     for (int j = 1; j <= 2; j++) {  -> the INNER loop: 2 times PER outer pass
//         cout << ...;                -> the INNER BODY: runs 3 x 2 = 6 times
//     }                               -> ends the inner loop: back to its START
// }                                   -> ends the outer loop: back to i++
//
// THE FOUR PARTS OF EVERY for LOOP, READ LEFT TO RIGHT
//   for ( int i = 1 ; i <= 3 ; i++ )
//         \_______/   \____/    \___/
//          INITIALISE  TEST     UPDATE
//          run ONCE    ask      run after
//          before      EVERY    EVERY body
//          anything    pass     pass
// The inner loop is written the same way; it is only called "inner" because of
// WHERE it sits - inside another loop's body - not because of how it is built.
//
// STEP-BY-STEP EXPLANATION:
// 1. The outer loop starts i at 1 and runs while i is 3 or less: i = 1, 2, 3.
//    That is THREE passes.
// 2. The inner loop is written inside the outer body. Its own counter j starts at
//    1 and runs while j is 2 or less: j = 1, 2. That is TWO passes.
// 3. On the very first pass of the outer loop, i is 1, so the inner loop runs
//    j = 1 and j = 2 and prints two lines. Only then does i++ make i become 2.
// 4. The outer loop comes round again and runs the inner loop AGAIN, and the
//    inner loop starts again at j = 1. It has no memory of finishing at j = 2.
//    This reset is the single most important fact in this whole file.
// 5. Part 2 proves the count instead of trusting it: `executions++` sits inside
//    the inner body, and it ends at 6, which is 3 x 2.
// 6. Part 3 prints the same information as a GROUPED trace, where the outer
//    value is shown once and the inner values are listed underneath it.
// 7. Part 4 makes the point that a total of this shape is a multiplication.
//    Adding the inner passes also happens to work here (2 + 2 + 2), but adding
//    needs a separate thought for every outer value, while multiplying is the
//    same single calculation every time.
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

    cout << "=== Part 1: the OUTER loop drives the INNER loop ===" << endl;

    // THE OUTER LOOP.
    // It is the loop that is written FIRST and FURTHEST OUT. Its braces contain
    // a whole other loop, which is exactly what makes it the outer one.
    for (int i = 1; i <= 3; i++) {
        // `i` is the OUTER COUNTER. It counts outer passes: 1, 2, 3.
        // Nothing inside this body can make i jump back or skip a value, so the
        // outer loop always gets its full three passes.

        // THE INNER LOOP.
        // It sits inside the outer loop's body, so it is re-run from its first
        // statement every time the outer loop comes round again.
        for (int j = 1; j <= 2; j++) {
            // `j` is the INNER COUNTER. It counts inner passes: 1, then 2.
            // `j` is a SEPARATE variable with a SEPARATE value from `i`. The
            // two counters do not know about each other at all.
            //
            // THIS LINE IS THE INNER BODY. It is the part that gets repeated.
            cout << "i = " << i << "   j = " << j << endl;
            // The `<<` operator sends each value to the screen in order: the
            // text, then the number in i, then three spaces, then j. `endl`
            // ends the line AND flushes the buffer. Placing `endl` INSIDE the
            // inner loop would put every single pair on its own line, which is
            // what Part 1 wants; a grid pattern would instead put `endl` after
            // the inner loop so one whole row finishes before the line breaks.
        }

        // The inner loop's closing brace is reached. Control does NOT go back
        // to the top of the inner loop - it falls out of the inner loop here
        // and reaches the outer loop's closing brace, which runs `i++`.
    }

    cout << endl;
    cout << "=== Part 2: proof - the inner body ran 6 times ===" << endl;

    // THE COUNTER MUST BE DECLARED BEFORE BOTH LOOPS.
    // If `int executions = 0;` were written INSIDE either loop, it would be
    // thrown away and reset to 0 on every pass, and the count would finish at
    // 1 instead of 6. Declaring it here, once, is what lets it remember.
    int executions = 0;

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 2; j++) {
            // `executions++` means "add one to executions". It is placed inside
            // the INNER body because the thing being counted is executions of
            // the inner body - one per inner pass, and nothing at all on the
            // outer passes where the inner loop somehow did no work.
            executions++;
        }
    }

    cout << "the outer loop ran 3 times, and the inner loop ran 2 times each time" << endl;
    cout << "3 x 2 = " << executions << " executions of the inner body" << endl;
    cout << "the proof is not a guess: the program counted all 6 of them" << endl;

    cout << endl;
    cout << "=== Part 3: the grouped trace, one full inner loop per outer pass ===" << endl;

    for (int i = 1; i <= 3; i++) {
        // The outer value is printed ONCE, before the inner loop starts. On
        // paper this is how you group a nested trace: one heading, then every
        // value the inner loop takes underneath that heading.
        cout << "  i = " << i << endl;

        for (int j = 1; j <= 2; j++) {
            // Two extra spaces of indentation on top of nothing at all: the
            // indentation is not printed by C++, it is spaces typed inside the
            // string literal, and their only job is to show that j belongs to
            // the group above it.
            cout << "      j = " << j << endl;
        }

        // THE BLANK LINE IS DELIBERATE, and it is printed AFTER the inner loop,
        // never inside it. If `endl` were inside the inner loop you would get a
        // blank line between every single j, and the groups would fall apart.
        cout << endl;
    }

    cout << "=== Part 4: the total is a MULTIPLICATION, not an addition ===" << endl;
    cout << "adding the passes:    2 + 2 + 2 = " << (2 + 2 + 2) << endl;
    cout << "multiplying instead:  3 x 2     = " << (3 * 2) << endl;
    cout << "both give the same answer, but only one of them keeps working when the" << endl;
    cout << "numbers get bigger" << endl;

    // ------------------------------------------------------------
    // THE GROUPED TRACE, DRAWN BY HAND ON PAPER
    // ------------------------------------------------------------
    //   i = 1
    //       j = 1
    //       j = 2
    //
    //   i = 2
    //       j = 1
    //       j = 2
    //
    //   i = 3
    //       j = 1
    //       j = 2
    //
    // HOW TO READ IT: the outer value appears once and the inner values are
    // listed underneath it, indented. There are three groups because the outer
    // loop has three values, and each group has two lines because the inner
    // loop has two values. Count the lines: 3 groups x 2 lines = 6 lines.
    //
    // ------------------------------------------------------------
    // TRACE TABLE - every single execution of the inner body
    // ------------------------------------------------------------
    // +---------+-----+-----+------------------------+-----------------+
    // | Pass    | i   | j   | Output                  | Executions so   |
    // |         |     |     |                         | far             |
    // +---------+-----+-----+------------------------+-----------------+
    // |   1     |  1  |  1  | i = 1   j = 1          |       1         |
    // |   2     |  1  |  2  | i = 1   j = 2          |       2         |
    // |   3     |  2  |  1  | i = 2   j = 1          |       3         |
    // |   4     |  2  |  2  | i = 2   j = 2          |       4         |
    // |   5     |  3  |  1  | i = 3   j = 1          |       5         |
    // |   6     |  3  |  2  | i = 3   j = 2          |       6         |
    // +---------+-----+-----+------------------------+-----------------+
    //
    // THE "OUTER" AND "INNER" COLUMNS ARE BOTH NEEDED IN A NESTED TRACE.
    // One row per execution of the INNER body, never one row per execution of
    // the outer loop. A trace table with three rows for this program would be
    // wrong: the program prints six lines, so the table must have six rows.
    //
    // THE MULTIPLICATION
    //   outer passes x inner passes = total executions of the inner body
    //                      3     x      2        =          6
    // The formula is "outer x inner" and never "outer + inner". Adding would
    // give 5 here, which is not an answer the program can ever produce.
    //
    // WHY THE INNER LOOP RESTART - THE POINT OF THIS FILE
    //   The inner loop's `int j = 1;` is part of its HEADER, and a header is
    //   re-executed from the beginning on every pass of the loop that contains
    //   it. So on outer pass 2, `int j = 1;` runs again and j is 1 once more.
    //   If you want the inner loop to carry on counting instead of restarting,
    //   you have to move `j` out of the header and declare it before the outer
    //   loop - which is a different program, and produces different output.
    //
    // COMMON TRAP
    //   Thinking the inner loop runs ONCE in total, because it is written only
    //   once in the source. How many times a line is WRITTEN and how many times
    //   it RUNS are different questions. This line is written once and runs six
    //   times, which is the entire point of nested loops.
    //
    //   The second trap is forgetting that the inner loop resets, and expecting
    //   j to keep climbing: 1, 2, 3, 4... across the whole program. The trace
    //   table above is the fastest way to catch that mistake - if your own table
    //   says j = 3 anywhere, you have mis-read where j is declared.

    return 0;
    // Ends main at once and hands 0 back to the operating system. Zero is the
    // conventional code for "success": the program ran to its end without an
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: In a nested loop, which one is called the outer loop?  -> the loop that is written first and whose body contains the other loop
// Q2: How many times does the inner body of this program run, and how do you work it out?  -> 6 times, from outer passes x inner passes = 3 x 2 = 6
// Q3: On the third pass of the outer loop, what value does j start at?  -> 1 again, because the inner loop header including int j = 1 is re-run from the top every outer pass
// Q4: Where must a counter variable be declared so it can total up executions of the inner body?  -> before the outer loop, so neither loop can reset it
// Q5: Why is `cout << endl;` written after the inner loop rather than inside it in Part 3?  -> so the blank line comes once per whole group, after every j has been listed, instead of once per j
