/*
  ============================================================
  PROGRAM: Adding Up the Odd Numbers from 1 to 20, Two Ways
  TOPIC: accumulators + testing for ODD numbers with the modulo operator
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - How to recognise an ODD number: dividing by 2 always leaves exactly 1.
  - The two ways to write the odd test: `i % 2 == 1` and `i % 2 != 0`.
  - Method 2 needs no test at all: start at 1 and step by 2.
  - A third check using a fact instead of a loop: every number is either
    odd or even, so the grand total less the evens leaves the odds.

  EXPECTED OUTPUT:
  === Method 1: visit every number and test it with % ===
  The odd numbers are:
   1 3 5 7 9 11 13 15 17 19
  Their total is 100
  === Method 2: step by 2 from 1, no test needed ===
  The odd numbers are:
   1 3 5 7 9 11 13 15 17 19
  Their total is 100
  === Agreement ===
  Both methods give 100, so they agree.
  === A third check: the grand total minus the evens ===
  Grand total 1 to 20 is 210
  Even total from the previous program is 110
  210 - 110 = 100, which is exactly the odd total.

  IMPORTANT SYNTAX:
  i % 2 == 1                 -> "one left over", i.e. odd
  i % 2 != 0                 -> also odd; `!=` means "not equal to"
  sumOdd += i;               -> fold i into the running total; `-` subtracts

  STEP-BY-STEP EXPLANATION:
  1. Method 1 visits every number from 1 to 20 and keeps the odd ones.
  2. Method 2 starts at 1 and adds 2 each pass, landing on 1, 3, 5 ... 19.
     No `if` is needed.
  3. Both totals come to 100 and `==` confirms it.
  4. The third check uses a fact: every number is exactly one of odd or
     even, so odd-total = grand-total - even-total.
  ============================================================
*/

#include <iostream>
/*
  <iostream> is the header file that gives C++ its ability to talk to the
  terminal: it supplies `cout` for output, `cin` for input and `endl` for
  ending a line. The language itself can only calculate and compare, so every
  facility for showing a result comes from a library - and this line invites
  that library in. Without it the compiler cannot find `cout`.
*/

using namespace std;
/*
  A NAMESPACE is a labelled box that groups related names so two libraries
  cannot fight over the same word. `std` is the box belonging to the C++
  STANDARD library, where `cout` and `endl` live, so the full name of our
  printing command is `std::cout`. The `::` is the SCOPE RESOLUTION OPERATOR
  and means "inside". `using namespace std;` says the names I write come
  from std, which is why plain `cout` works below.
*/

int main() {
/*
  `main` is the ENTRY POINT: the first function the operating system runs
  when the program starts. `int` is its RETURN TYPE, so when main finishes
  it hands a whole number back as an exit status. `()` is the parameter list
  and it is empty. The `{ }` braces are the BODY, run top to bottom.
*/

    /*
      ================================================================
      METHOD 1 - VISIT EVERY NUMBER AND TEST IT
      ================================================================
    */
    cout << "=== Method 1: visit every number and test it with % ===" << endl;

    /*
      The ACCUMULATOR. Created before the loop and set to 0, the identity
      for `+`, so the first odd number is added onto nothing and passes
      straight through. A separate variable from every other total here:
      each running answer needs its own home, or the values overwrite each
      other and the results become meaningless.
    */
    int sumOdd = 0;
    cout << "The odd numbers are:" << endl;

    // Step by 1, because to test a number with `%` we have to visit it.
    for (int i = 1; i <= 20; i++) {
        if (i % 2 != 0) {
        /*
          THE ODD TEST, WRITTEN TWO WAYS

          `%` is the MODULO operator: it divides and hands back what is LEFT
          OVER. `/` asks "how many times does it go in?", `%` asks "and what
          is left?". Dividing any number by 2 leaves either nothing or
          exactly one behind, and never more:

          7 % 2  ->  1     (one left over)     -> 7 is ODD
          8 % 2  ->  0     (nothing left over) -> 8 is EVEN

          So these two tests mean EXACTLY the same thing:

          i % 2 == 1      "is the remainder one?"
          i % 2 != 0      "is the remainder NOT zero?"

          WHAT IS `!=`?
          `!=` is the NOT-EQUAL comparison operator, the opposite of
          `==`. It reads aloud as "is not equal to" and answers true or
          false. There are only two possible remainders when dividing by
          2, so "equals 1" and "not equals 0" are the same statement -
          which is why both forms appear in exam answers.
          THE SIX COMPARISONS, all taking this form:
          <  less than            >  greater than
          <= less than or equal   >= greater than or equal
          == equal to             != not equal to
          `<` and `>` EXCLUDE the value at that end; `<=` and `>=`
          INCLUDE it, and `!=` is the mirror image of `==`.
        */

            // A SPACE BEFORE EACH NUMBER rather than after it, so the line
            // never ends in a stray space.
            cout << " " << i;

            /*
              THE ACCUMULATOR LINE. Two steps: work out sumOdd + i using
              the values both variables hold at this instant, then store
              the answer back into sumOdd. The old total is overwritten, but
              it has already been folded into the new value. Longhand this
              is `sumOdd = sumOdd + i;`; briefly `sumOdd += i;`.
            */
            sumOdd += i;
        }
        /*
          Numbers failing the test fall past this brace unprinted. VISITING
          a number and PRINTING a number are separate decisions: the loop
          really did reach 2, 4, 6 and so on, and the `if` said no thanks.
        */
    }

    cout << endl;   // closes the line the numbers were printed on
    cout << "Their total is " << sumOdd << endl;

    /*
      ================================================================
      METHOD 2 - STEP STRAIGHT TO THE ODD NUMBERS
      ================================================================
    */
    cout << "=== Method 2: step by 2 from 1, no test needed ===" << endl;

    // A SECOND accumulator, again starting at 0.
    int sumStep = 0;
    cout << "The odd numbers are:" << endl;

    /*
      Two changes turn Method 1 into Method 2: the start value is 1, the
      first odd number, and the update is `i += 2` rather than `i++`, so the
      counter only ever lands on odd numbers and the `if` can be deleted.
      1, 3, 5, ... 19 - ten passes, then the update jumps to 21, which
      fails `i <= 20` and ends the loop.
    */
    for (int i = 1; i <= 20; i += 2) {
        cout << " " << i;
        sumStep += i;
    }

    cout << endl;
    cout << "Their total is " << sumStep << endl;

    /*
      ================================================================
      AGREEMENT BETWEEN THE TWO METHODS
      ================================================================
    */
    cout << "=== Agreement ===" << endl;
    /*
      `==` asks "are these two the same?" and changes nothing. `=` would be
      a different statement entirely: it would copy sumStep into sumOdd and
      destroy the first answer.
    */
    if (sumOdd == sumStep) {
        cout << "Both methods give " << sumOdd << ", so they agree." << endl;
    } else {
        cout << "They disagree: " << sumOdd << " against " << sumStep << "." << endl;
    }

    /*
      ================================================================
      A THIRD CHECK - A FACT INSTEAD OF A LOOP
      ================================================================
    */
    cout << "=== A third check: the grand total minus the evens ===" << endl;

    /*
      Every number from 1 to 20 is either odd or even - never both, never
      neither - so the odd total must be the grand total less the even total.
      This checks the answer with a FACT rather than a loop. The grand total
      comes from the 10-second formula n * (n + 1) / 2 with n = 20:
      20 * 21 = 420, and 420 / 2 = 210.
    */
    int n = 20;
    int grandTotal = n * (n + 1) / 2;
    cout << "Grand total 1 to 20 is " << grandTotal << endl;

    // The even total, taken from 02_sum_even_numbers.cpp where a loop proved
    // it. Hard-coding it is fine for a check, but on an exam you would loop.
    int evenTotal = 110;
    cout << "Even total from the previous program is " << evenTotal << endl;

    // `-` is the SUBTRACTION operator: 210 - 110 leaves the odd 100.
    int oddBySubtraction = grandTotal - evenTotal;
    cout << grandTotal << " - " << evenTotal << " = " << oddBySubtraction
         << ", which is exactly the odd total." << endl;

    /*
      ================================================================
      TRACE TABLE - METHOD 1, showing the rejections
      ================================================================
      Rows 1 to 3 and 19 to 21 are shown; rows between behave like their
      neighbours, so they are elided with "...".
      +-----------+------------+--------------+--------------------+--------+
      | Iteration | i at start | i % 2        | i % 2 != 0 ?       | Output |
      +-----------+------------+--------------+--------------------+--------+
      | 1         | 1          | 1 % 2 = 1    | TRUE  - odd        | 1      |
      | 2         | 2          | 2 % 2 = 0    | FALSE - even       | (none) |
      | 3         | 3          | 3 % 2 = 1    | TRUE  - odd        | 3      |
      | 4         | 4          | 4 % 2 = 0    | FALSE - even       | (none) |
      | ...       | ...        | ...          | ...                | ...    |
      | 19        | 19         | 19 % 2 = 1   | TRUE  - odd        | 19     |
      | 20        | 20         | 20 % 2 = 0   | FALSE - even       | (none) |
      | 21        | 21         | (not tested) | the loop has ended | (none) |
      +-----------+------------+--------------+--------------------+--------+

      The accumulator moves 0 -> 1 -> 4 -> 9 -> ... -> 100, and 100 is what
      the program prints. The pass with i = 19 is the one that completes it.

      THE COMMON TRAP IN THIS FILE
        Writing the odd test as `i % 2 == 2`. It compiles and is always
        false, because dividing by 2 can never leave 2 behind. The loop then
        prints nothing and the total stays 0, with no error message to
        explain why. The only possible remainders are 0 and 1, so the test
        is `== 1` or `!= 0` and never anything else. When a program prints
        nothing at all, suspect the condition before the accumulator.
    */

    return 0;
    /*
      `return 0;` ends main straight away and hands 0 back to the operating
      system. Zero is the conventional code for "success": the program ran to
      the end without error. Exams expect it, so it is always written last.
    */
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: What does `i % 2` equal for i = 9, and what does that make 9?  -> 1, and a remainder of 1 means 9 is odd
  Q2: What is the total of the odd numbers from 1 to 20?  -> 100
  Q3: Why does Method 2 not need an `if` at all?  -> starting at 1 and stepping by 2 only ever lands on odd numbers
  Q4: How is the third check stated in one line?  -> odd total = grand total - even total, since every number is one or the other
  Q5: What happens if the odd test is written `i % 2 == 2`?  -> it is always false, so nothing prints and the total stays 0
*/
