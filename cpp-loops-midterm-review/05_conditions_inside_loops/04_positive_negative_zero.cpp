// ============================================================
// PROGRAM: Positive, Negative or Zero - an array with if / else if / else
// TOPIC: fixed-size arrays, indexing, and the three-way chain over data
// DIFFICULTY: Beginner
// ============================================================
//
// WHAT THIS PROGRAM TEACHES:
// - Declaring a fixed-size array: `int values[] = { ... };` and what the empty
//   `[ ]` means - "work the length out for me".
// - Indexing with `values[i]`, why the first element is index 0, and why the
//   LAST valid index is one less than the number of values.
// - Counting the array's length with a loop instead of `sizeof`.
// - The sentinel value: a marker stored at the end of the array so a loop can
//   count the real values without being told the length.
// - Classifying each element with the three-way `if / else if / else` chain.
// - `&&` (and) and `||` (or), and why two conditions are often needed at once.
//
// EXPECTED OUTPUT:
// === Part 1: how many values does the array hold? ===
// The array holds 10 values.
//
// === Part 2: classify every value ===
// index 0 holds 12 -> positive
// index 1 holds -7 -> negative
// index 2 holds 0 -> zero
// index 3 holds 25 -> positive
// index 4 holds -3 -> negative
// index 5 holds 8 -> positive
// index 6 holds -19 -> negative
// index 7 holds 0 -> zero
// index 8 holds 4 -> positive
// index 9 holds -6 -> negative
//
// === Part 3: the totals ===
// positive = 4, negative = 4, zero = 2, total = 10
//
// === Part 4: negative AND even ===
// They are: -6
// Count: 1
//
// === Part 5: negative OR bigger than 20 ===
// They are: -7 25 -3 -19 -6
// Count: 5
//
// IMPORTANT SYNTAX:
// int values[] = {1, 2, 3};  -> an ARRAY of whole numbers; the [ ] work out the length
// values[0]                   -> the FIRST element, not values[1]
// values[i]                   -> the element at position i, counting from 0
// values[i] < 0 && ...        -> BOTH tests must be true; `&&` is logical AND
// values[i] < 0 || ...        -> AT LEAST ONE test must be true; `||` is logical OR
//
// STEP-BY-STEP EXPLANATION:
// 1. `int values[] = { ... 9999 };` builds one row of whole numbers in memory.
//    The empty brackets tell the compiler to count the items itself.
// 2. The loop index runs 0, 1, 2 ... 9, so `values[i]` touches all ten real
//    values and never the marker, because the count stops at the marker.
// 3. The three-way chain asks `> 0` first, then `< 0`, and only falls through
//    to the final `else` when both have failed - which happens only for 0.
// 4. Each hit raises its own counter by 1, and 4 + 4 + 2 lands back on 10,
//    proving no element was counted twice or skipped.
// 5. Part 4 needs BOTH tests to hold, so it uses `&&`. Part 5 needs only one,
//    so it uses `||`. Choosing wrongly is the usual cause of a wrong count.
// ============================================================

#include <iostream>
// The only header this project uses. It provides `cout` for printing and
// `endl` for ending a line. The C++ language can calculate, store and compare
// but it cannot talk to a screen, so every piece of terminal output comes from
// this library and this include line is what brings it in.

using namespace std;
// A NAMESPACE is a labelled box that groups related names so two libraries
// cannot fight over the same word. `std` is the box belonging to the C++
// STANDARD library, where `cout` and `endl` live. The `::` is the SCOPE
// RESOLUTION OPERATOR and means "inside", so `std::cout` reads "the cout
// inside std". `using namespace std;` says to take bare names from that box,
// which is why `cout` needs no prefix in this file.

int main() {
// `main` is the ENTRY POINT: the first function the operating system runs when
// the program starts. `int` is the RETURN TYPE, handing a whole number back
// as an exit status when main ends. `()` is the parameter list, empty because
// this program takes no arguments and reads no keyboard input. The `{ }` are
// the BODY, executed from top to bottom.

    // THE MARKER. A value chosen because it can never be real data, so the
    // counting loop below cannot stop one value short or run one too long.
    int stopMarker = 9999;

    // AN ARRAY DECLARATION.
    //   int      every item in the brackets is a whole number.
    //   values   the name the row of numbers will be known by.
    //   []       LEFT EMPTY ON PURPOSE. C++ counts the values between the
    //            braces itself and works out the size. (You may also write
    //            int values[10] with the length typed in, but leaving it out
    //            means the two cannot disagree.)
    //   = { }    the initialiser list - the actual numbers, in order.
    // The last value is the marker, so there are 11 items but only 10 real
    // ones. Writing 0 here instead would be a disaster: 0 is legitimate data
    // below, and the loop would stop on the first 0 it met.
    int values[] = {12, -7, 0, 25, -3, 8, -19, 0, 4, -6, 9999};

    cout << "=== Part 1: how many values does the array hold? ===" << endl;

    // COUNTING WITH A LOOP, NOT sizeof. The loop walks along the array and
    // stops the moment it reaches the marker. Each pass counts one value:
    //     n++    means "add 1 to n", shorthand for n = n + 1;
    // The test is on the LEFT of the loop body, so it runs before the body -
    // which is why `values[n]` is always in range while the test is made.
    int n = 0;
    while (values[n] != stopMarker) {
        n++;
    }

    cout << "The array holds " << n << " values." << endl;
    // n is 10, not 11, because the marker is never counted. The loop must
    // terminate, and it does: the marker is IN the array, so this is a
    // bounded loop and not a risk of running off the end forever.
    cout << endl;

    cout << "=== Part 2: classify every value ===" << endl;

    int positive = 0;
    int negative = 0;
    int zero = 0;

    for (int i = 0; i < n; i++) {
        // INDEXING. `values[i]` means "the item at position i". The first
        // item is index 0, the second index 1, and with n items the last
        // valid index is n - 1. Asking for values[n] would read the marker.
        int v = values[i];
        // Copying the element into a named variable first costs one line and
        // makes every line below shorter and easier to check against the
        // printed index, which is the single most useful thing when tracing.

        if (v > 0) {
            cout << "index " << i << " holds " << v << " -> positive" << endl;
            positive++;
        } else if (v < 0) {
            cout << "index " << i << " holds " << v << " -> negative" << endl;
            negative++;
        } else {
            cout << "index " << i << " holds " << v << " -> zero" << endl;
            zero++;
        }
        // HOW THE CHAIN PICKS ONE BRANCH. The tests are read from the top and
        // the first true one runs, and the rest of the chain is skipped
        // completely rather than merely unlikely to fire. So a positive value
        // never even gets tested against `< 0`. Reaching the final `else`
        // means every earlier test has been tried and every one failed.
    }
    cout << endl;

    cout << "=== Part 3: the totals ===" << endl;
    cout << "positive = " << positive
         << ", negative = " << negative
         << ", zero = " << zero
         << ", total = " << positive + negative + zero << endl;
    // 4 + 4 + 2 = 10 = n, which is the check that matters: every element went
    // into exactly one bucket, and no bucket was counted twice. A total
    // smaller than n means an element was skipped; larger means double
    // counting, usually from two branches that can both be true.
    cout << endl;

    cout << "=== Part 4: negative AND even ===" << endl;

    int bothCount = 0;

    cout << "They are: ";

    for (int i = 0; i < n; i++) {
        int v = values[i];
        // `&&` is the LOGICAL AND: the whole test is true only when BOTH sides
        // are true. Use it when a value must satisfy two requirements at once.
        // Here a value must be below zero AND leave no remainder on division
        // by 2. Only -6 manages both, which is why the count is 1.
        if (v < 0 && v % 2 == 0) {
            if (bothCount > 0) {
                cout << " ";
            }
            cout << v;
            bothCount++;
        }
    }
    cout << endl;
    cout << "Count: " << bothCount << endl;
    cout << endl;

    cout << "=== Part 5: negative OR bigger than 20 ===" << endl;

    int orCount = 0;

    cout << "They are: ";

    for (int i = 0; i < n; i++) {
        int v = values[i];
        // `||` is the LOGICAL OR: true when AT LEAST ONE side is true, and
        // that includes the case where both are. A value qualifies here if it
        // is below zero OR above 20, and -19 qualifies on the first test alone
        // while 25 qualifies on the second. Four negatives plus one big
        // positive makes five, and they come out in INDEX order rather than
        // in size order - a loop visits the array from front to back.
        if (v < 0 || v > 20) {
            if (orCount > 0) {
                cout << " ";
            }
            cout << v;
            orCount++;
        }
    }
    cout << endl;
    cout << "Count: " << orCount << endl;

    // ------------------------------------------------------------
    // TRACE TABLE - Part 2, the three-way chain over all ten elements
    // ------------------------------------------------------------
    // Every element is listed, because there are only ten of them.
    // +---------+-----------+-----------+----------+--------------+---------------+
    // | Iteration|     i     | values[i] | v > 0 ?  | Branch taken | Counters after|
    // +---------+-----------+-----------+----------+--------------+---------------+
    // |    1    |      0      |     12    | TRUE     | 1st positive | pos = 1       |
    // |    2    |      1      |     -7    | FALSE    | 2nd negative | neg = 1       |
    // |    3    |      2      |      0    | FALSE    | 3rd zero     | zero = 1      |
    // |    4    |      3      |     25    | TRUE     | 1st positive | pos = 2       |
    // |    5    |      4      |     -3    | FALSE    | 2nd negative | neg = 2       |
    // |    6    |      5      |      8    | TRUE     | 1st positive | pos = 3       |
    // |    7    |      6      |    -19    | FALSE    | 2nd negative | neg = 3       |
    // |    8    |      7      |      0    | FALSE    | 3rd zero     | zero = 2      |
    // |    9    |      8      |      4    | TRUE     | 1st positive | pos = 4       |
    // |   10    |      9      |     -6    | FALSE    | 2nd negative | neg = 4       |
    // |   11    |     (none)  | (not run) |   -      | 10 < 10 FALSE| final totals  |
    // +---------+-----------+-----------+----------+--------------+---------------+
    //
    // WHY THE LOOP STOPPED AFTER 10 PASSES: the condition `i < n` is tested
    // before each pass, and n is 10. On pass 11 the test would need i to be
    // 10 or more, so it fails and the body never runs. `values[10]` - the
    // marker - is therefore never even looked at by this loop.
    //
    // NOTE THE TWO ZEROS AT INDICES 2 AND 7. They are the reason the marker
    // cannot be 0. Both reach the final `else`, because `> 0` and `< 0` are
    // both false for 0, and each one raises the zero counter exactly once.
    //
    // PART 4 AND PART 5 SIDE BY SIDE, to show what the operators really do
    // +-------+------------+-----------+-------------------+-----------------------+
    // | value | v < 0      | v % 2 ==0| v < 0 && v%2 == 0 | v < 0 || v > 20      |
    // +-------+------------+-----------+-------------------+-----------------------+
    // |   12  | FALSE      | TRUE     | FALSE             | FALSE                 |
    // |   -7  | TRUE       | FALSE    | FALSE             | TRUE                  |
    // |    0  | FALSE      | TRUE     | FALSE             | FALSE                 |
    // |   25  | FALSE      | FALSE    | FALSE             | TRUE                  |
    // |   -3  | TRUE       | FALSE    | FALSE             | TRUE                  |
    // |    8  | FALSE      | TRUE     | FALSE             | FALSE                 |
    // |  -19  | TRUE       | FALSE    | FALSE             | TRUE                  |
    // |    0  | FALSE      | TRUE     | FALSE             | FALSE                 |
    // |    4  | FALSE      | TRUE     | FALSE             | FALSE                 |
    // |   -6  | TRUE       | TRUE     | TRUE              | TRUE                  |
    // +-------+------------+-----------+-------------------+-----------------------+
    // The `&&` column is true on one row only, because -6 is the only value
    // that is negative AND even. The `||` column is true on five rows, and
    // reading down it shows the two halves the loop actually counted.
    //
    // COMMON TRAP IN THIS FILE
    //   Counting the array with `sizeof`. It is the correct tool in C++, but
    //   it returns the number of BYTES, not the number of values - 11 ints is
    //   44 bytes, not 11 - so a loop bounded by it runs off the end of the
    //   row. This project is not allowed to use it, which is why the marker
    //   exists at all. The second trap is making the marker 0: the loop stops
    //   at the first 0 in the DATA, so a single legitimate zero early in the
    //   array silently cuts the counting short and every total comes out
    //   wrong with no error message anywhere.
    //
    //   Third trap, and it costs the most marks: indexing from 1. `values[1]`
    //   is the SECOND value, not the first, and `values[n]` is the marker, not
    //   the last real value. Run the loop from 0 to n - 1 and the answers come
    //   out shifted by one, which is usually still plausible enough to pass
    //   unnoticed.

    return 0;
    // Ends main immediately and hands 0 back to the operating system. Zero is
    // the conventional code for "success": the program reached its end with no
    // error, so it is always the last line of main.
}

// ============================================================
// EXAM QUESTIONS
// ============================================================
// Q1: Which element does `values[0]` hold, and what is the last valid index?  -> the first element, 12; the last valid index is 9 because there are 10 values numbered from 0
// Q2: Why is a value such as 9999 put at the end of the array?  -> it is a marker that cannot occur as real data, so the counting loop knows exactly when to stop without being told the length
// Q3: Why must the marker not be 0?  -> 0 is legitimate data here, so a loop testing for 0 would stop at the first zero in the values and count only part of the array
// Q4: What do `&&` and `||` mean, and which one finds values that are both negative and even?  -> `&&` requires both tests true and `||` requires at least one; the both-negative-and-even count needs `&&`
// Q5: How many values are negative in this array, and how does the `total` line prove the classification is right?  -> 4 negatives, and positive 4 plus negative 4 plus zero 2 comes back to 10, matching the length exactly
