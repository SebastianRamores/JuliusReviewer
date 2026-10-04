/*
  ============================================================
  PROGRAM: while Loop Accumulators - Adding and Multiplying
  TOPIC: while loops + the ACCUMULATOR variable pattern
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - The ACCUMULATOR pattern: one variable that carries a running answer
    from one pass of the loop to the next.
  - Why an accumulator MUST be initialised before the loop - add with 0
    and multiply with 1, for reasons explained inside.
  - How `sum = sum + i;` is read in two steps, right to left.
  - Printing the running value each pass so the pattern becomes visible.

  EXPECTED OUTPUT:
  === Part 1: adding up the numbers 1 to 10 ===
  After adding 1 the total is 1
  After adding 2 the total is 3
  After adding 3 the total is 6
  After adding 4 the total is 10
  After adding 5 the total is 15
  After adding 6 the total is 21
  After adding 7 the total is 28
  After adding 8 the total is 36
  After adding 9 the total is 45
  After adding 10 the total is 55
  Final total: 55
  === Part 2: multiplying up to 5! ===
  After multiplying by 1 the product is 1
  After multiplying by 2 the product is 2
  After multiplying by 3 the product is 6
  After multiplying by 4 the product is 24
  After multiplying by 5 the product is 120
  Final product: 120

  IMPORTANT SYNTAX:
  int sum = 0;            -> start a running total at zero
  int product = 1;        -> start a running product at one
  sum = sum + i;          -> add i into the total and store it back
  sum += i;               -> exactly the same thing, written shorter
  product = product * j;  -> multiply j into the product
  product *= j;           -> exactly the same thing, written shorter

  STEP-BY-STEP EXPLANATION:
  1. `int sum = 0;` creates the accumulator BEFORE the loop. Created inside
     the loop it would be thrown away and rebuilt on every pass, so nothing
     would ever be carried forward.
  2. `int i = 1;` creates the loop counter, also before the loop.
  3. `while (i <= 10)` asks "is i at most 10?". TRUE runs the body, FALSE
     leaves the loop and the program continues below the closing brace.
  4. `sum = sum + i;` is the heart of the pattern. Read it in two steps:
     work out the total of the old sum plus i, then store that back in sum.
  5. The print shows the total after each pass, so you can watch it grow.
  6. `i++` moves the counter on. Deleting it would loop for ever.
  7. Part 2 repeats the pattern with `*` instead of `+`, which is exactly
     why its accumulator starts at 1 instead of 0.
  ============================================================
*/

#include <iostream>
/*
  <iostream> is the header file that gives C++ its ability to talk to the
  terminal: it supplies `cout` for output, `cin` for input and `endl` for
  ending a line. The language itself can only calculate and compare, so every
  facility for showing a result is borrowed from a library - and this line
  invites that library in. Without it the compiler says cout is not declared.
*/

using namespace std;
/*
  A NAMESPACE is a labelled box that groups related names so two libraries
  cannot fight over the same word. `std` is the box belonging to the C++
  STANDARD library, where `cout` and `endl` live, so the full name of our
  printing command is `std::cout`. The `::` between them is the SCOPE
  RESOLUTION OPERATOR and means "inside". `using namespace std;` says "the
  names I write come from std", which is why plain `cout` works below.
*/

int main() {
/*
  `main` is the ENTRY POINT: the first function the operating system runs
  when the program starts. `int` is its RETURN TYPE, so when main finishes
  it hands a whole number back as an exit status. `()` is the parameter list
  and it is empty. The `{ }` braces are the BODY - run top to bottom.
*/

    /*
      ================================================================
      PART 1 - AN ACCUMULATOR THAT ADDS
      ================================================================
    */
    cout << "=== Part 1: adding up the numbers 1 to 10 ===" << endl;

    /*
      TWO variables are needed, and they do completely different jobs:

        i    is a COUNTER. It answers "how far through the numbers am I?".
              It changes by a fixed step each pass and the loop condition
              re-reads it every time.
        sum  is an ACCUMULATOR. It answers "what have I worked out so far?".
              It folds each new value into the answer it already holds, so
              that answer survives from one pass to the next.

      BOTH must be created and given a starting value BEFORE the loop.

      `int sum = 0;`
        int  whole numbers only - a decimal such as 2.5 could not be held.
        sum  the name, for the running total. `=` is ASSIGNMENT, meaning
             "store", not "equals"; `==` instead asks whether two things are
             the same. `;` ends the statement.
        0    THE STARTING VALUE, and the only sensible one: 0 is the
             identity for `+`, meaning 0 + 7 is 7, so starting at zero passes
             the first number through unchanged.
    */
    int sum = 0;

    int i = 1;   // the loop counter; its start value decides where the run begins

    /*
      `while (i <= 10)` reads as "is i less than or equal to 10?".
      TRUE -> run the body and test again. FALSE -> leave the loop.
      The test happens BEFORE the body, so the answer is never worked out
      with an i that is already out of range.
    */
    while (i <= 10) {

        /*
          THE ACCUMULATOR LINE, read in two steps:
            1. work out  sum + i  using the values both variables hold at
               this instant - on the first pass that is 0 + 1.
            2. store that answer back into sum. The old sum is then gone,
               which is fine: it has already been folded into the answer.
          `+` is ADDITION, so this is also written `sum += i;`. NEVER write
          `sum + i;` alone - that throws the value away and leaves sum as is.
        */
        sum = sum + i;

        /*
          Printing after the update shows the total as it stands at the END
          of each pass. `cout` sends text to the screen, `<<` is the stream
          insertion operator whose arrows point the way data travels (into
          cout), and `endl` ends the line.
        */
        cout << "After adding " << i << " the total is " << sum << endl;

        // `i++` is the INCREMENT operator, shorthand for `i = i + 1;`. It
        // moves i towards the value that makes the condition fail.
        i++;
    } // end of the loop body

    // sum survived the loop because it was created outside it, so the answer
    // can be inspected here. 55 = 1 + 2 + 3 + ... + 10.
    cout << "Final total: " << sum << endl;

    /*
      ================================================================
      PART 2 - AN ACCUMULATOR THAT MULTIPLIES (FACTORIAL)
      ================================================================
    */
    cout << "=== Part 2: multiplying up to 5! ===" << endl;

    // 5! - "five factorial" - is the product of every whole number from 1
    // up to 5: 1 * 2 * 3 * 4 * 5. The loop body does exactly one thing.
    int product = 1;
    /*
      THE STARTING VALUE IS 1 HERE, NOT 0, and that difference matters.
      1 is the identity for `*`: 1 * 7 is 7, so beginning at 1 lets the
      first real number through unchanged. Beginning at 0 would give 0 for
      ever, since anything times 0 is 0. The rule to memorise:
          add up -> start at 0      multiply -> start at 1
    */

    // n holds the number we factorial-ise. It never changes inside the loop,
    // so `j <= n` stays a constant limit and the loop is easy to retarget.
    int n = 5;
    int j = 1;

    while (j <= n) {
        // The same pattern, now with `*`, the MULTIPLICATION operator.
        // `product = product * j;` is shorthand for `product *= j;`.
        product = product * j;

        cout << "After multiplying by " << j << " the product is " << product << endl;

        // `j++` is the increment. A different variable from Part 1 keeps
        // the two loops independent - either order gives the same answers.
        j++;
    }

    // 120 = 1 * 2 * 3 * 4 * 5.
    cout << "Final product: " << product << endl;

    /*
      ================================================================
      TRACE TABLE - PART 1, the accumulator that adds
      ================================================================
      Each row shows the values BEFORE the body runs, then the total AFTER.
      Middle rows are elided with "..."; the first row and the last,
      failing, test are both shown in full.
      +-----------+------------+------------+----------------+--------+
      | Iteration | i at start | sum before | sum after      | Output |
      +-----------+------------+------------+----------------+--------+
      | 1         | 1          | 0          | 0 + 1 = 1      | 1      |
      | 2         | 2          | 1          | 1 + 2 = 3      | 3      |
      | 3         | 3          | 3          | 3 + 3 = 6      | 6      |
      | ...       | ...        | ...        | ...            | ...    |
      | 10        | 10         | 45         | 45 + 10 = 55   | 55     |
      | 11        | 11         | 55         | (body skipped) | (none) |
      +-----------+------------+------------+----------------+--------+

      The body ran 10 times. Row 11 is the failing test: 11 <= 10 is false,
      so the body is skipped and sum keeps its finished value of 55.

      ================================================================
      TRACE TABLE - PART 2, the accumulator that multiplies
      ================================================================
      +-----------+------------+-------------+----------------+--------+
      | Iteration | j at start | prod before | product after  | Output |
      +-----------+------------+-------------+----------------+--------+
      | 1         | 1          | 1           | 1 * 1 = 1      | 1      |
      | 2         | 2          | 1           | 1 * 2 = 2      | 2      |
      | 3         | 3          | 2           | 2 * 3 = 6      | 6      |
      | 4         | 4          | 6           | 6 * 4 = 24     | 24     |
      | 5         | 5          | 24          | 24 * 5 = 120   | 120    |
      | 6         | 6          | 120         | (body skipped) | (none) |
      +-----------+------------+-------------+----------------+--------+

      THE COMMON TRAP IN THIS FILE
        Writing `product = 0;` instead of `product = 1;`. The loop runs
        happily, prints every line, and gives the answer 0 - and on row 1
        the reason is invisible, because 0 * 1 really is 0. Ask instead
        "what is the identity for this operator?": 0 for + and -, 1 for *.
        A wrongly initialised accumulator gives a wrong answer silently.
        The second trap is putting the accumulator INSIDE the loop. C++
        would allow `while (...) { int sum = 0; sum = sum + i; }`, but sum
        would be destroyed and rebuilt every pass, so it would never grow.
    */

    return 0;
    /*
      `return 0;` ends main straight away and hands 0 back to the operating
      system. Zero is the conventional code for "success": the program ran
      to the end without an error. Exams expect to see it, so it is always
      written as the last statement of main.
    */
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: What are the running totals after adding 4 and after adding 5?  -> 10 and 15
  Q2: What final value does sum hold, and why?  -> 55, the total of every whole number from 1 to 10
  Q3: Why must an adding accumulator start at 0?  -> 0 is the identity for +, so 0 + first number passes it through unchanged
  Q4: Why must a multiplying accumulator start at 1 and not 0?  -> anything multiplied by 0 is 0, so starting at 0 would give 0 for ever
  Q5: Where must the accumulator be declared, and why?  -> before the loop, so it keeps its value from one pass to the next
*/
