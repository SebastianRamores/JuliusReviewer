/*
  ============================================================
  PROGRAM: Factorials - the Multiplying Accumulator
  TOPIC: accumulators + the special cases 0! and 1! + overflow
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - Factorial as an accumulator that MULTIPLIES rather than adds, and why
    that accumulator must start at 1 instead of 0.
  - The two special cases, 0! and 1!, which are both 1 - and the loop
    reaches the right answer on its own, with no special coding.
  - Why an int cannot hold a large factorial, and what 13! actually is.

  EXPECTED OUTPUT:
  === Factorial of 5 using an accumulator ===
  After multiplying by 1 the product is 1
  After multiplying by 2 the product is 2
  After multiplying by 3 the product is 6
  After multiplying by 4 the product is 24
  After multiplying by 5 the product is 120
  5! is 120
  === The special cases 0! and 1! ===
  0! is 1
  1! is 1
  For 0! the loop body never runs, so the answer is just the starting 1.
  For 1! the body runs once and multiplies by 1, so the answer is 1 again.
  === How large can an int go? ===
  12! is 479001600, which still fits in an int.
  13! is 6227020800, which does NOT fit in an int, so never compute it in one.

  IMPORTANT SYNTAX:
  int product = 1;          -> a multiplying accumulator starts at ONE
  product = product * i;    -> fold i into the running product
  product *= i;             -> exactly the same thing, written shorter
  for (int i = 1; i <= n; i++) -> ten passes for n = 10, one for each factor
  0! = 1                   -> by definition, the product of NO numbers

  STEP-BY-STEP EXPLANATION:
  1. `int product = 1;` is the accumulator. 1 is the identity for `*`, so
     the first factor passes through untouched. Starting at 0 would give 0
     for ever, because anything multiplied by 0 is 0.
  2. The loop multiplies in every number from 1 up to n, one per pass, and
     for n = 5 the product finishes at 120.
  3. For n = 0 the test `1 <= 0` fails immediately, the body never runs, and
     the answer is the untouched starting value of 1 - exactly the
     mathematical definition of 0!.
  4. For n = 1 the body runs once and multiplies by 1, so the answer is 1
     again. Both special cases fall out of the loop for free.
  5. 12! still fits in an int; 13! does not, and trying it anyway is called
     OVERFLOW and produces a meaningless answer.
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
  A NAMESPACE is a labelled box grouping related names so two libraries
  cannot fight over the same word. `std` is the box belonging to the C++
  STANDARD library, where `cout` and `endl` live, so the full name of our
  printing command is `std::cout`. The `::` is the SCOPE RESOLUTION OPERATOR
  and means "inside". `using namespace std;` says the names I write come
  from std, which is why plain `cout` works below.
*/

int main() {
/*
  `main` is the ENTRY POINT: the first function the operating system runs when
  the program starts. `int` is its RETURN TYPE, so when main finishes it hands
  a whole number back as an exit status. `()` is the parameter list and it is
  empty. The `{ }` braces are the BODY, run top to bottom.
*/

    /*
      ================================================================
      PART 1 - 5! , THE MULTIPLYING ACCUMULATOR
      ================================================================
    */
    cout << "=== Factorial of 5 using an accumulator ===" << endl;

    /*
      "n factorial" is the product of every whole number from 1 up to n:
          5! = 1 * 2 * 3 * 4 * 5 = 120
          4! = 1 * 2 * 3 * 4     = 24
      The number being factorial-ed is given its own variable, so the loop
      never has it written twice and changing the problem is a one-place
      edit.
    */
    int n = 5;

    /*
      THE ACCUMULATOR, AND THE ONE PLACE BEGINNERS GO WRONG.

        int     whole numbers only, and only a limited range of them -
                see Part 3 for what "limited" means.
        product the name: it holds the running product.
        =       ASSIGNMENT - "store", not "equals".
        1       THE STARTING VALUE, and it must be 1, NOT 0.

      WHY 1 AND NOT 0? An accumulator has to start at the IDENTITY of its
      operator - the value that leaves the other value untouched:

          adding      -> identity 0, because 0 + 7 is 7
          multiplying  -> identity 1, because 1 * 7 is 7

      Starting at 0 would give the answer 0 for ever, because anything
      multiplied by 0 is 0. On the very first pass the mistake is invisible
      - 0 * 1 really is 0 - and only later does it become obvious. The
      accumulator MUST be created before the loop: inside the braces it
      would be destroyed and rebuilt on every pass, so nothing would carry
      forward and the answer would stay at 1.
    */
    int product = 1;

    // One pass per factor: 1, 2, 3, 4, 5, and then the test `6 <= 5` fails
    // and the loop ends.
    for (int i = 1; i <= n; i++) {
        /*
          THE ACCUMULATOR LINE. Work out product * i using the values both
          hold at this instant, then store the answer back into product.
          The old product is overwritten, but it has already been folded
          into the new value, so nothing is lost. Longhand this is
          `product = product * i;`; briefly `product *= i;`, where `*=` is
          the compound assignment operator, the multiplying relative of `+=`.
        */
        product = product * i;

        /*
          Printing after the update shows the product at the END of each
          pass. `cout` sends text to the screen, `<<` is the stream insertion
          operator whose arrows point the way data travels, and `endl` ends it.
        */
        cout << "After multiplying by " << i << " the product is " << product << endl;
    }

    cout << n << "! is " << product << endl;

    /*
      ================================================================
      PART 2 - THE TWO SPECIAL CASES, 0! AND 1!
      ================================================================
    */
    cout << "=== The special cases 0! and 1! ===" << endl;


    /*
      0! is the product of NO numbers at all, and maths defines the product
      of an empty set as 1. This loop agrees: i starts at 1, the test
      `1 <= 0` is false at once, so the body NEVER runs and product is
      still the untouched starting value of 1. Zero passes, answer 1.
    */
    int zeroFactorial = 1;
    for (int i = 1; i <= 0; i++) {
        zeroFactorial = zeroFactorial * i;
    }
    cout << "0! is " << zeroFactorial << endl;

    /*
      1! is just the number 1, so of course the answer is 1. This loop also
      agrees: the body runs exactly once, multiplying by 1, so the product
      stays at 1. Note this loop is NOT skipped - one pass really happens -
      so the two special cases reach the same answer by different routes.
    */
    int oneFactorial = 1;
    for (int i = 1; i <= 1; i++) {
        oneFactorial = oneFactorial * i;
    }
    cout << "1! is " << oneFactorial << endl;

    cout << "For 0! the loop body never runs, so the answer is just the starting 1." << endl;
    cout << "For 1! the body runs once and multiplies by 1, so the answer is 1 again." << endl;

    /*
      ================================================================
      PART 3 - WHERE AN int STOPS BEING BIG ENOUGH
      ================================================================
    */
    cout << "=== How large can an int go? ===" << endl;

    /*
      An `int` on an ordinary modern computer is 32 bits wide, so it can
      hold values from -2147483648 up to 2147483647. Factorials grow fast
      enough to run off the end of that range almost immediately:

          5!  =              120   easily inside
          10! =        3628800   easily inside
          12! =      479001600   still inside, just
          13! =     6227020800   TOO BIG - more than double 12!

      Carrying on past the limit is called OVERFLOW. The value has nowhere
      to go, so what comes out is meaningless: often the number wraps round
      to a negative value. Either way it is NOT the answer.

      12! is computed here to show the boundary being reached safely. 13! is
      deliberately NOT computed - only printed as literal text - because
      running that loop would overflow and any result would be junk.
    */
    int n12 = 12;
    int fact12 = 1;
    for (int i = 1; i <= n12; i++) {
        fact12 *= i;
    }
    cout << "12! is " << fact12 << ", which still fits in an int." << endl;
    cout << "13! is 6227020800, which does NOT fit in an int, so never compute it in one." << endl;

    /*
      ================================================================
      TRACE TABLE - PART 1, the multiplying accumulator
      ================================================================
      +-----------+------------+--------------+----------------+--------+
      | Iteration | i at start | product bef. | product after  | Output |
      +-----------+------------+--------------+----------------+--------+
      | 1         | 1          | 1            | 1 * 1 = 1      | 1      |
      | 2         | 2          | 1            | 1 * 2 = 2      | 2      |
      | 3         | 3          | 2            | 2 * 3 = 6      | 6      |
      | 4         | 4          | 6            | 6 * 4 = 24     | 24     |
      | 5         | 5          | 24           | 24 * 5 = 120   | 120    |
      | 6         | 6          | 120          | (body not run) | (none) |
      +-----------+------------+--------------+----------------+--------+

      The product-before column is the product-after of the row above. That
      hand-off between passes IS the accumulator, and the reason it must be
      declared outside the loop: a variable born inside the braces would
      restart at 1 on every pass and the product would never exceed 5.

      For 0! the table has a single row: i starts at 1, `1 <= 0` is FALSE
      straight away, and the body never runs at all.

      THE COMMON TRAP IN THIS FILE
        Writing `int product = 0;`. It compiles, it runs, it prints five
        lines, and it answers 0 - and on the first line the fault is
        invisible, because 0 * 1 does equal 0. Always ask "what is the
        identity for my operator?" before initialising an accumulator:
        0 for `+` and `-`, 1 for `*` and `/`. The second trap is forgetting
        that `i` must be initialised to 1 rather than 0: starting from 0
        would multiply by 0 first and give 0 for ever.
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
  Q1: What does this program compute for n = 5, and why?  -> 120, the product 1 * 2 * 3 * 4 * 5
  Q2: Why must a multiplying accumulator start at 1 rather than 0?  -> 1 is the identity for `*`, so the first factor passes through unchanged; 0 would give 0 for ever
  Q3: What is 0!, and why does this loop give it without any special code?  -> 1; the test `1 <= 0` fails at once so the body never runs and the starting 1 survives
  Q4: What is the largest factorial that still fits in an int?  -> 12! = 479001600, since 13! = 6227020800 is too big
  Q5: What is overflow, and what happens if you compute 13! in an int?  -> exceeding the type's range; the result is meaningless, often a wrapped negative number
*/
