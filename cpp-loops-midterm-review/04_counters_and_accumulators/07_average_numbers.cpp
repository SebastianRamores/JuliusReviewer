/*
  ============================================================
  PROGRAM: Finding the Average - and Why Integer Division Loses It
  TOPIC: accumulators + counters + the double type and type conversion
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - An average is found in three steps: add everything up, count how many
    there were, then divide one by the other.
  - Why `sum / count` with two ints throws the fraction away - INTEGER
    DIVISION truncates rather than rounding.
  - The trap nobody expects: putting `double` on the LEFT of the division
    does not help, because the division already happened by then.
  - How to force a real division by converting one side with a cast.

  EXPECTED OUTPUT:
  === Step 1: sum and count ===
  Sum of the 10 numbers is 23
  Count is 10
  === Step 2: dividing two whole numbers ===
  23 / 10 as int division gives 2
  === Step 3: a double on the left does NOT help ===
  Declaring the answer as double still gives 2
  === Step 4: convert one side BEFORE dividing ===
  23 / 10 as a double gives 2.3
  That is the correct average.

  IMPORTANT SYNTAX:
  int sum = 0;              -> an accumulator, for the total
  int count = 0;            -> a counter, for how many there are
  sum / count               -> INTEGER division: the fraction is discarded
  double average = ...;     -> `double` stores numbers WITH decimal places
  (double) sum / count      -> a CAST: treat sum as a double before dividing

  STEP-BY-STEP EXPLANATION:
  1. One loop does both jobs: it adds each value into `sum` and raises
     `count` by 1, so the two always describe the same set of numbers.
  2. `int wrong = sum / count;` gives 2, because both sides are ints and
     the division throws away the 0.3.
  3. `double stillWrong = sum / count;` ALSO gives 2. The division is
     carried out in ints first, and only the finished 2 is turned into a
     double afterwards.
  4. `double average = (double) sum / count;` converts sum to a double
     BEFORE the division happens, so the answer keeps its fraction: 2.3.
  5. The mean of the list is therefore 2.3, not 2.
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
      THE DATA - THE SAME TEN FIXED NUMBERS AS FILE 06
      ================================================================
      An ARRAY is a fixed row of values, all of one type, each in its own
      numbered box. `int numbers[]` - `int` is the element type, `[]` after
      the name says the length is worked out from the values in `{ }`.
      INDEXING STARTS AT 0, so these ten values live at boxes 0 to 9.
      (File 06 counted how many of them are positive, negative and zero.)
    */
    int numbers[] = {5, -3, 0, 12, -7, 8, -1, 20, -15, 4};
    int howMany = 10;

    /*
      ================================================================
      STEP 1 - ADD EVERYTHING UP AND COUNT AT THE SAME TIME
      ================================================================
    */
    cout << "=== Step 1: sum and count ===" << endl;

    /*
      TWO VARIABLES, TWO DIFFERENT JOBS - this is the heart of the program.

        sum    is an ACCUMULATOR. It answers "HOW MUCH?" and moves by the
               value it is given: 0, then 5, then 5 + -3, and so on. It
               starts at 0 because 0 is the identity for `+`.
        count  is a COUNTER. It answers "HOW MANY?" and always moves by
               exactly 1, whatever the value is. It also starts at 0.

      BOTH MUST BE INITIALISED BEFORE THE LOOP. A variable created inside
      the braces is destroyed at the closing brace and rebuilt each pass,
      so it would never carry anything forward.
    */
    int sum = 0;
    int count = 0;

    for (int i = 0; i < howMany; i++) {
        /*
          The accumulator line: work out sum + numbers[i] using the values
          both hold at this instant, then store the answer back into sum.
          Note that a NEGATIVE number is added just like any other, which
          is exactly why the running total can go DOWN - from 5 to 2 after
          -3 is added on the second pass.
        */
        sum = sum + numbers[i];

        // The counter line: add 1, regardless of whether the value was
        // positive, negative or zero. Every value counts as exactly one.
        count++;
    }

    cout << "Sum of the " << count << " numbers is " << sum << endl;
    cout << "Count is " << count << endl;

    /*
      ================================================================
      STEP 2 - DIVIDING TWO WHOLE NUMBERS, AND LOSING THE FRACTION
      ================================================================
    */
    cout << "=== Step 2: dividing two whole numbers ===" << endl;

    /*
      INTEGER DIVISION. When BOTH operands are ints, `/` performs a whole
      number division and simply DISCARDS the remainder. It does not round
      to the nearest value, it chops:

           23 / 10  is really 2.3, but an int division gives 2
           47 / 10  is really 4.7, and an int division gives 4
           22 / 10  is really 2.2, and an int division gives 2

      Nothing is wrong with the arithmetic - the wrong answer comes purely
      from the TYPE of the two values being divided. This is the single
      most common numerical bug in beginner C++, and it is silent: no
      warning, no error, just a quietly wrong answer.
    */
    int wrong = sum / count;

    cout << sum << " / " << count << " as int division gives " << wrong << endl;

    /*
      ================================================================
      STEP 3 - THE TRAP: A double ON THE LEFT DOES NOT HELP
      ================================================================
    */
    cout << "=== Step 3: a double on the left does NOT help ===" << endl;

    /*
      It is tempting to write the variable as a double and expect that to
      be enough. It is NOT. Read this line strictly in order:

        1. `sum / count` is worked out first, and both sides are ints, so
           this produces the int 2 - the .3 has already been thrown away.
        2. only THEN is that finished 2 converted, so that it can be stored
           in a double.

      The conversion happens at the wrong moment. The fraction is gone
      before the double ever appears. Declaring the ANSWER as a double is
      not the same as doing the DIVISION as a double.
    */
    double stillWrong = sum / count;

    cout << "Declaring the answer as double still gives " << stillWrong << endl;

    /*
      ================================================================
      STEP 4 - THE FIX: CONVERT ONE SIDE BEFORE DIVIDING
      ================================================================
    */
    cout << "=== Step 4: convert one side BEFORE dividing ===" << endl;

    /*
      THE FIX: convert one of the two numbers into a double BEFORE the
      division happens, so the division itself is carried out in doubles.

      `(double) sum` is called a CAST. The brackets contain a type name, so
      the whole thing reads "treat this value as a double instead of an
      int". It does not change what sum holds afterwards - only how it is
      used in this one calculation.

      Two places would work equally well:
          double average = (double) sum / count;   <- convert the top
          double average = sum / (double) count;   <- convert the bottom
      Both leave one side as a double, and one double side is enough to make
      the whole expression a double calculation.
    */
    double average = (double) sum / count;

    /*
      Printing a double shows its decimal places, so 2.3 appears as 2.3
      and the finished int division of 2 appeared as 2. No special printing
      instructions are needed for that.
    */
    cout << sum << " / " << count << " as a double gives " << average << endl;
    cout << "That is the correct average." << endl;

    /*
      ================================================================
      TRACE TABLE - the one loop, doing both jobs
      ================================================================
      +-----------+----+------------+------------+----------------+-------+
      | Iteration | i  | numbers[i] | sum before | sum after      | count |
      +-----------+----+------------+------------+----------------+-------+
      | 1         | 0  | 5          | 0          | 0 + 5 = 5      | 1     |
      | 2         | 1  | -3         | 5          | 5 - 3 = 2      | 2     |
      | 3         | 2  | 0          | 2          | 2 + 0 = 2      | 3     |
      | 4         | 3  | 12         | 2          | 2 + 12 = 14    | 4     |
      | 5         | 4  | -7         | 14         | 14 - 7 = 7     | 5     |
      | 6         | 5  | 8          | 7          | 7 + 8 = 15     | 6     |
      | 7         | 6  | -1         | 15         | 15 - 1 = 14    | 7     |
      | 8         | 7  | 20         | 14         | 14 + 20 = 34   | 8     |
      | 9         | 8  | -15        | 34         | 34 - 15 = 19   | 9     |
      | 10        | 9  | 4          | 19         | 19 + 4 = 23    | 10    |
      | 11        | 10 | (no more)  | 23         | (body not run) | 10    |
      +-----------+----+------------+------------+----------------+-------+

      The two right-hand columns are the whole lesson. `sum` climbs and
      FALLS, because it is being fed the actual values, some of which are
      negative. `count` only ever climbs, by 1, because it is not looking
      at the values at all. They finish at 23 and 10, and 23 / 10 is the
      average we want.

      THE COMMON TRAP IN THIS FILE
        Stopping at Step 2 and printing `wrong`, which is 2 instead of 2.3.
        It is a perfectly reasonable-looking line of code and it compiles
        with no warning whatsoever. The habit that prevents it is to decide
        the type of the ANSWER before writing the division: if the answer
        might have a fraction anywhere in it, make sure a `double` is
        involved in the division, not merely in the variable that receives
        it. A good exam habit is to ask "could this ever be a half?" before
        dividing anything.
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
  Q1: What are the final values of sum and count?  -> 23 and 10
  Q2: What does `23 / 10` give when both sides are ints, and why?  -> 2, because integer division discards the .3 instead of rounding
  Q3: Why does `double stillWrong = sum / count;` still give 2?  -> the division is carried out in ints first; only the finished 2 is converted afterwards
  Q4: What is the correct average of the list, and how is it forced?  -> 2.3, by casting one side: (double) sum / count
  Q5: Why can the running total in this loop go DOWN?  -> sum is fed negative values as well as positive ones, such as -3 and -15
*/
