/*
  ============================================================
  PROGRAM: Adding Up the Even Numbers from 1 to 20, Two Ways
  TOPIC: accumulators + the modulo operator (%) to test for even numbers
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - How to recognise an EVEN number: divide by 2 and get no remainder.
  - The MODULO operator `%`, with worked examples and the rule that
    `n % 2 == 0` means even and `n % 2 == 1` means odd.
  - Two different programs that produce the same total - one that visits
    every number and tests it, one that steps straight to the even ones.
  - That visiting a number and printing a number are different actions.

  EXPECTED OUTPUT:
  === Method 1: visit every number and test it with % ===
  The even numbers are:
   2 4 6 8 10 12 14 16 18 20
  Their total is 110
  === Method 2: step by 2 and skip the test ===
  The even numbers are:
   2 4 6 8 10 12 14 16 18 20
  Their total is 110
  === Agreement ===
  Both methods give 110, so they agree.

  IMPORTANT SYNTAX:
  i % 2 == 0                 -> "dividing i by 2 leaves no remainder", i.e. even
  i % 2 != 0                 -> there IS a remainder, i.e. odd
  sumEven = sumEven + i;     -> fold i into the running total
  sumEven += i;              -> exactly the same, written shorter
  i += 2;                    -> skip the odd numbers entirely

  STEP-BY-STEP EXPLANATION:
  1. Method 1 walks through every number from 1 to 20, one at a time.
  2. For each number it asks `i % 2 == 0`. TRUE means even, so the number
     is printed and added to the accumulator; FALSE means odd, so the
     `if` body is skipped and the loop moves on to the next number.
  3. Method 2 starts at 2 and adds 2 each pass, so only even numbers are
     ever visited and no test is needed at all.
  4. Both totals come to 110, and `==` confirms it in the program.
  5. Method 2 is twice as fast in the sense of doing half the work: 10
     passes instead of 20, because it never looks at an odd number.
  ============================================================
*/

#include <iostream>
/*
  <iostream> is the header file that gives C++ its ability to talk to the
  terminal: it supplies `cout` for output, `cin` for input and `endl` for
  ending a line. The language itself can only calculate and compare, so every
  facility for showing a result comes from a library - and this line invites
  that library in. Without it the compiler says cout is not declared.
*/

using namespace std;
/*
  A NAMESPACE is a labelled box that groups related names so two libraries
  cannot fight over the same word. `std` is the box belonging to the C++
  STANDARD library, where `cout` and `endl` live, so the full name of our
  printing command is `std::cout`. The `::` is the SCOPE RESOLUTION OPERATOR
  and means "inside". `using namespace std;` says "the names I write come
  from std", which is why plain `cout` works below.
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
      The ACCUMULATOR, created before the loop and set to 0 because 0 is
      the identity for `+`: 0 + anything = anything, so the first even
      number passes through unchanged. Starting at 1 gives 111 not 110.
    */
    int sumEven = 0;

    cout << "The even numbers are:" << endl;
    for (int i = 1; i <= 20; i++) {
        // The step is 1, NOT 2: to use `%` we must LOOK at each number. Every
        // number from 1 to 20 is visited; the odd ones are rejected later.

        if (i % 2 == 0) {
        /*
          THE MODULO OPERATOR, `%`

          `%` divides and then hands back what is LEFT OVER. It is the
          opposite question from `/`: `/` asks "how many times does it go
          into?", `%` asks "and what is left?"

          10 / 2  ->  5      (2 fits into 10 exactly five times)
          10 % 2  ->  0      (nothing left over)
          9 / 2  ->  4      (2 fits into 9 four times...)
          9 % 2  ->  1      (...with one left over)

          THE RULE FOR EVEN AND ODD
          i % 2 == 0   -> nothing left over   -> the number is EVEN
          i % 2 == 1   -> exactly one left over -> the number is ODD

          It is worth noticing that `i % 2` can only ever BE 0 or 1 when
          dividing by 2, because you cannot leave 2 or 3 or more behind when
          dividing by 2. So the test could equally be written `i % 2 != 0`
          for "odd", or the whole thing could be written as
          `if (i % 2 == 0)`.

          ZERO IS EVEN.  0 % 2 is 0, so the test says even. Every maths
          teacher agrees: zero is divisible by every number, because
          0 = 2 * 0 with nothing left over. Loops in this project start at
          1 only so that the beginner can see the numbers climb.

          WHAT IS `==`?
          `==` is the EQUALITY COMPARISON and it asks a question:
          "is the left side equal to the right side?" It answers true or
          false and changes nothing at all.

          *** `=` VERSUS `==` - THE MOST COMMON BUG IN THIS COURSE ***
          `=`   (one equals sign)   ASSIGNMENT. It STORES a value.
          sumEven = 0;      means "put 0 into sumEven".
          `==`  (two equals signs) COMPARISON. It CHECKS a value.
          i % 2 == 0        means "is the remainder zero?"
          Writing `if (i % 2 = 0)` tries to ASSIGN 0 to the calculation
          i % 2, which is nonsense, and the compiler rejects it.
        */

            /*
              A SPACE IS PRINTED BEFORE EACH NUMBER rather than after it.
              That way the line never ends in a stray space, and the numbers
              come out neatly separated: " 2 4 6 8 10".
            */
            cout << " " << i;

            /*
              The accumulator line. Two steps: work out sumEven + i using
              the values both hold now, then store the answer back into
              sumEven. The old total is overwritten, but it has already
              been folded into the new value, so nothing is lost.
              `sumEven = sumEven + i;` is also written `sumEven += i;`.
            */
            sumEven = sumEven + i;
        }
        /*
          Anything that fails the test falls straight past the closing brace
          here. VISITING a number is not the same as PRINTING one: the loop
          really did visit 1, 3, 5, 7 and so on, and the `if` decided that
          they were not wanted in the output.
        */

    } // end of the loop body

    cout << endl;   // closes the line the numbers were printed on
    cout << "Their total is " << sumEven << endl;

    /*
      ================================================================
      METHOD 2 - STEP STRAIGHT TO THE EVEN NUMBERS
      ================================================================
    */
    cout << "=== Method 2: step by 2 and skip the test ===" << endl;

    // A SECOND accumulator, also starting at 0. It must be a fresh variable:
    // reusing sumEven would restart the total from 110 and give 220.
    int sumStep = 0;
    cout << "The even numbers are:" << endl;

    /*
      Two changes turn Method 1 into Method 2:
        the start value is 2, not 1, because 1 is odd and would pollute
          the answer;
        the update is `i += 2`, not `i++`, so only even numbers are ever
          visited and no `if` is needed.
      2, 4, 6, 8, 10, 12, 14, 16, 18, 20 - ten passes instead of twenty.
    */
    for (int i = 2; i <= 20; i += 2) {
        cout << " " << i;

        /*
          `i += 2` is compound addition: add 2 to i. It is shorthand for
          `i = i + 2;`. It is what lets the loop finish, since it is what
          eventually makes `i <= 20` false.
        */
        sumStep += i;
    }

    cout << endl;
    cout << "Their total is " << sumStep << endl;

    /*
      ================================================================
      AGREEMENT CHECK
      ================================================================
    */
    cout << "=== Agreement ===" << endl;

    if (sumEven == sumStep) {
        cout << "Both methods give " << sumEven << ", so they agree." << endl;
    } else {
        cout << "They disagree: " << sumEven << " against " << sumStep << "." << endl;
    }

    /*
      ================================================================
      TRACE TABLE - METHOD 1, showing that odd numbers are visited too
      ================================================================
      Rows 1, 2, 3, 19 and 20 are shown in full so the rejections are
      visible; the middle rows are elided with "..." and every one of them
      behaves exactly like its neighbours.
      +-----------+------------+--------------+----------------+--------+
      | Iteration | i at start | i % 2        | i % 2 == 0 ?   | Output |
      +-----------+------------+--------------+----------------+--------+
      | 1         | 1          | 1 % 2 = 1    | FALSE - odd    | (none) |
      | 2         | 2          | 2 % 2 = 0    | TRUE  - even   | 2      |
      | 3         | 3          | 3 % 2 = 1    | FALSE - odd    | (none) |
      | ...       | ...        | ...          | ...            | ...    |
      | 19        | 19         | 19 % 2 = 1   | FALSE - odd    | (none) |
      | 20        | 20         | 20 % 2 = 0   | TRUE  - even   | 20     |
      | 21        | 21         | (not tested) | loop has ended | (none) |
      +-----------+------------+--------------+----------------+--------+

      Only 10 of the 20 passes print anything. The accumulator column, not
      the output column, is the one to watch:
        0 -> 2 -> 6 -> 12 -> 20 -> 30 -> ... -> 110
      and that finished value of 110 is what the program prints.

      THE COMMON TRAP IN THIS FILE
        Stepping by 2 AND keeping the `%` test at the same time, as in
        `for (int i = 2; i <= 20; i += 2) { if (i % 2 == 0) { ... } }`.
        That code is correct but wasteful, and it hides which idea you meant.
        Also beware starting Method 2 at 1: the first pass would add the
        odd number 1 straight into the total with no test to stop it, giving
        111 instead of 110. Choose deliberately between "look at everything
        and reject some" and "go straight to the ones you want".
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
  Q1: What does `i % 2` evaluate to for i = 7, and what does that make 7?  -> 1, and a remainder of 1 means 7 is odd
  Q2: What is the total of the even numbers from 1 to 20?  -> 110
  Q3: Why does Method 1 step by 1 rather than by 2?  -> it has to visit every number to be able to test it with %
  Q4: How many times does each loop body run?  -> Method 1 runs 20 times, Method 2 runs 10 times
  Q5: Is 0 even, and what does the test say?  -> yes, 0 is even; 0 % 2 is 0 so `i % 2 == 0` is true for it
*/
