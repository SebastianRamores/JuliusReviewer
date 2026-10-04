// ============================================================
// PROGRAM: break as a Search - finding a value and stopping when it is found
// TOPIC: early exit with break, and the flag variable it replaces
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - The commonest use of `break`: searching an array and stopping the instant
//   the value is found, instead of looking at values that cannot help.
// - How to report "found at index N", and how to notice that the search
//   finished WITHOUT finding anything.
// - Why the found index is initialised to -1, and why -1 can never be a real
//   index, which is what makes it a safe "nothing found yet" marker.
// - The classic FLAG alternative, run here so the two can be compared, and the
//   reasons `break` is usually the better of the two.
//
// EXPECTED OUTPUT:
// === Part 1: search for 47, stopping as soon as it is found ===
// searching for 47
// checked index 0: 23 - not a match
// checked index 1: 91 - not a match
// checked index 2: 47 - MATCH, so break stops the search here
// found at index 2
//
// === Part 2: search for 50, which is not in the array ===
// searching for 50
// checked index 0: 23 - not a match
// checked index 1: 91 - not a match
// checked index 2: 47 - not a match
// checked index 3: 15 - not a match
// checked index 4: 68 - not a match
// not found - the loop finished without ever breaking
//
// === Part 3: the same search written with a flag instead ===
// searching for 47 using a flag
// found at index 2 (with a flag, not with break)
// Both searches agree. The flag version checked every value; the break version
// checked only the three up to and including the match.
//
// IMPORTANT SYNTAX:
// int foundAt = -1;        -> -1 means "not found yet", and can never be real
// if (values[i] == target) -> == asks "are these the same?"
// break;                   -> stop searching, the answer is already known
// if (foundAt != -1) { }   -> how the loop's result is read afterwards
//
// STEP-BY-STEP EXPLANATION:
// 1. Part 1 walks the array testing `values[i] == target`. On the third pass
//    both sides are 47, the test is true, and the `break` ends the search.
// 2. Three values were checked. Had there been no break, all five would have
//    been checked, and the answer could not have changed once 47 was found.
// 3. `foundAt` is set to 2 immediately BEFORE the break, so the index
//    survives the jump out of the loop. Setting it after the break would be a
//    bug: that line would never run.
// 4. Part 2 looks for a value that is not there. The loop runs to its natural
//    end, `foundAt` is still -1, and the `if` after the loop prints the
//    not-found message. Both outcomes are decided by the same variable.
// 5. Part 3 does the identical search with a flag instead of a break. It
//    reaches the same index 2, and prints it - the two versions are
//    interchangeable in their result and differ only in work done.
// ============================================================

#include <iostream>
// The only header this project needs. It provides `cout` for output and
// `endl` for ending a line. The C++ language can calculate, store and compare
// but it cannot talk to a screen, so every piece of terminal output comes
// from this library, and this include line is what brings it in.

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
// empty, since this program takes no arguments and needs no keyboard input.
// The `{ }` braces are the BODY, executed from top to bottom.

    int stopMarker = 9999;

    int values[] = {23, 91, 47, 15, 68, 9999};
    // Five real values, then the marker. The target 47 sits in the MIDDLE, so
    // the break saves real work - two values are never even looked at. If the
    // match had been the last value, break would have saved nothing and the
    // two versions below would behave identically.

    cout << "=== Part 1: search for 47, stopping as soon as it is found ===" << endl;

    // THE "NOT FOUND YET" MARKER. -1 is the right starting value for an index
    // because indices begin at 0, so -1 can never be one of them. That makes
    // it impossible to confuse "index -1" with "I found something at the
    // last position" - a mistake waiting to happen with a starting value of 0.
    int foundAt = -1;
    int target = 47;
    cout << "searching for " << target << endl;

    for (int i = 0; values[i] != stopMarker; i++) {
        // The loop condition is on the marker, not on `i < 5`, so no length
        // has to be counted and kept in step with the data.

        cout << "checked index " << i << ": " << values[i];

        if (values[i] == target) {
            // `==` ASKS "are these two the same?" and answers true or false.
            // A single `=` would be an ASSIGNMENT: it would store 47 into
            // values[i], destroying the element it was supposed to compare.
            cout << " - MATCH, so break stops the search here" << endl;

            // THE ORDER MATTERS ENORMOUSLY. The index is recorded FIRST, and
            // the `break` comes second. Written the other way round, with the
            // break above this line, the assignment would be skipped and
            // foundAt would still read -1 when the loop ended.
            foundAt = i;
            break;
            // `break;` leaves the loop at once. Control jumps to the first
            // statement after the closing brace - which is exactly where the
            // `if (foundAt != -1)` test below sits. That test is what makes
            // the answer survive the jump.
        }

        cout << " - not a match" << endl;
    }

    if (foundAt != -1) {
        cout << "found at index " << foundAt << endl;
    } else {
        cout << "not found - the loop finished without ever breaking" << endl;
    }
    cout << endl;

    cout << "=== Part 2: search for 50, which is not in the array ===" << endl;

    int foundAt2 = -1;
    int target2 = 50;
    cout << "searching for " << target2 << endl;

    for (int i = 0; values[i] != stopMarker; i++) {
        cout << "checked index " << i << ": " << values[i];
        if (values[i] == target2) {
            foundAt2 = i;
            break;
        }
        cout << " - not a match" << endl;
    }

    if (foundAt2 != -1) {
        cout << "found at index " << foundAt2 << endl;
    } else {
        cout << "not found - the loop finished without ever breaking" << endl;
        // NOTHING PRINTED "MATCH" ABOVE, so no break ever ran. The loop simply
        // reached the marker and stopped, which is the only way this loop can
        // end without a break. Reaching the end of the loop IS the "not
        // found" signal, and `foundAt2` is the record of it.
    }
    cout << endl;

    cout << "=== Part 3: the same search written with a flag instead ===" << endl;

    // THE FLAG ALTERNATIVE, and why it is usually the worse choice.
    //
    // A flag is an ordinary variable holding true or false - usually named
    // `found` or `isFound`. Instead of breaking out, the loop sets the flag
    // and keeps going to the very end. This version has three costs the break
    // version does not:
    //
    //   1. It must remember the index as well as the flag, so it needs two
    //      variables instead of one.
    //   2. Every element is examined, even after the answer is known. On a
    //      large array that is wasted time - and part 1 checked three values
    //      while this checks five.
    //   3. Nothing forces you to set the flag. Forget it on one branch and
    //      the program still compiles, still runs, and reports "not found"
    //      about a value that is sitting right there in the array.
    //
    // `break` costs one statement, cannot be forgotten, and stops the work.
    int found = false;
    int flagIndex = -1;

    cout << "searching for " << target << " using a flag" << endl;

    for (int i = 0; values[i] != stopMarker; i++) {
        if (values[i] == target) {
            found = true;
            flagIndex = i;
            // NO break HERE, and that is the whole difference. The loop
            // carries on through the remaining values, doing work whose
            // result cannot change anything.
        }
    }

    if (found) {
        cout << "found at index " << flagIndex
             << " (with a flag, not with break)" << endl;
    } else {
        cout << "not found" << endl;
    }

    cout << "Both searches agree. The flag version checked every value; the break version"
         << endl;
    cout << "checked only the three up to and including the match." << endl;

    // ------------------------------------------------------------
    // TRACE TABLE - Part 1, the search that stops early
    // ------------------------------------------------------------
    // +-------+----------+---------+----------------------+------------+-----------------+
    // | Pass  |    i     | values[i] | values[i] == 47 ? | foundAt    | Action         |
    // +-------+----------+---------+----------------------+------------+-----------------+
    // |   1   |     0    |    23    | FALSE               | -1         | keep searching |
    // |   2   |     1    |    91    | FALSE               | -1         | keep searching |
    // |   3   |     2    |    47    | TRUE                | -1 -> 2    | BREAK          |
    // |   4   |   (none) |  (none)  | never tested        | 2          | loop is over   |
    // +-------+----------+---------+----------------------+------------+-----------------+
    //
    // WHY THE LOOP STOPPED ON PASS 3: the `break` on pass 3 jumped past the
    // closing brace. The condition `values[i] != stopMarker` was NOT what
    // ended it - that test would have needed two more passes to reach the
    // marker. Indices 3 and 4 hold 15 and 68, and neither was ever examined.
    //
    // THE foundAt COLUMN IS THE PART THAT IS EASY TO GET WRONG. It stays at
    // -1 for two passes, changes to 2 on the pass that breaks, and is STILL 2
    // afterwards. The value outlives the loop because it was declared OUTSIDE
    // the braces - a variable declared inside would be gone by the time the
    // `if` after the loop needed to read it.
    //
    // PART 2, THE SAME LOOP AND A TARGET THAT NEVER APPEARS
    // +-------+----------+---------+----------------------+------------+-----------------+
    // | Pass  |    i     | values[i] | values[i] == 50 ? | foundAt2   | Action         |
    // +-------+----------+---------+----------------------+------------+-----------------+
    // |   1   |     0    |    23    | FALSE               | -1         | keep searching |
    // |   2   |     1    |    91    | FALSE               | -1         | keep searching |
    // |   3   |     2    |    47    | FALSE               | -1         | keep searching |
    // |   4   |     3    |    15    | FALSE               | -1         | keep searching |
    // |   5   |     4    |    68    | FALSE               | -1         | keep searching |
    // |   6   |     5    |   9999   | condition FALSE, so | -1         | loop ends here |
    // |       |          |          | the body never runs |            |                 |
    // +-------+----------+---------+----------------------+------------+-----------------+
    // All five real values were checked and `foundAt2` never moved, so the
    // `if` after the loop took the `else` branch and reported "not found".
    //
    // WHY "NOT FOUND" NEEDS NO SEPARATE MECHANISM
    //   Both answers come from one variable. The break sets it to a real
    //   index; the absence of a break leaves it at -1. The single test after
    //   the loop decides which message to print, so there is no way for the
    //   two messages to disagree with each other.
    //
    // COMMON TRAP IN THIS FILE
    //   Putting the `break` ABOVE the line that records the index:
    //       if (values[i] == target) {
    //           break;          // the loop jumps out here...
    //           foundAt = i;    // ...and this line never runs
    //       }
    //   The program compiles without a warning and then reports "not found"
    //   for a value that is plainly in the array. The rule that prevents it:
    //   the `break` is always the LAST statement inside its braces. Anything
    //   below a `break` is dead code.
    //
    //   The second trap is initialising the index to 0 instead of -1. Index 0
    //   is a perfectly real position, so "found at index 0" becomes
    //   indistinguishable from "never found", and a search that genuinely
    //   finds the first element is reported as a failure.

    return 0;
    // Ends main immediately and hands 0 back to the operating system. Zero is
    // the conventional code for "success": the program reached its end with no
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: Why does the search for 47 check only three values?  -> because the break on the third pass ends the loop as soon as the match is found
// Q2: What is the point of starting `foundAt` at -1 rather than 0?  -> indices start at 0, so -1 can never be a real position and cannot be mistaken for "found"
// Q3: How does the program know the value was NOT found?  -> `foundAt` is still -1 when the loop ends without breaking, and the `if` after the loop takes the else branch
// Q4: Why must the index be assigned before the `break`?  -> because the break skips everything below it, so an assignment written after it would never run
// Q5: What is wrong with the flag version, apart from doing more work?  -> nothing forces you to set the flag, so forgetting it on one branch compiles and runs but wrongly reports not found
