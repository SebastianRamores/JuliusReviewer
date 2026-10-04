/*
  ============================================================
  PROGRAM: Stepping by 5 - Multiples of 5 and of 7
  TOPIC: for loops - using the update to walk a list of multiples
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - Printing the multiples of any number by starting at it and stepping
    by it.
  - The same idea applied to 7 instead of 5, with nothing else changed.
  - Walking DOWN a list of multiples with `i -= 5`.
  - The formula for how many multiples of n fit inside a range.

  EXPECTED OUTPUT:
  Multiples of 5 from 1 to 50: 5 10 15 20 25 30 35 40 45 50
  Multiples of 7 from 1 to 50: 7 14 21 28 35 42 49
  Multiples of 5 from 50 down to 5: 50 45 40 35 30 25 20 15 10 5
  How many multiples of 5 in 1 to 50: 10
  How many multiples of 7 in 1 to 50: 7

  IMPORTANT SYNTAX:
  for (int i = 5; i <= 50; i += 5)  -> walk the multiples of 5 upwards
  for (int i = 50; i >= 5; i -= 5)  -> walk the multiples of 5 downwards
  i += 5                            -> compound assignment: add 5
  i -= 5                            -> compound assignment: subtract 5
  count++                           -> add 1 to a counter, inside the loop

  STEP-BY-STEP EXPLANATION:
  1. The multiples of 5 are 5, 10, 15, 20 ... To print them, start the
     counter AT 5 and step it BY 5. Starting at 1 would print 1, 6, 11,
     which are not multiples of 5 at all.
  2. The second loop uses exactly the same shape with 7 in both places:
     the start is 7 and the step is 7. Nothing else changes.
  3. 50 is not a multiple of 7, so that loop simply ends earlier: the last
     multiple that fits is 49, then 56 fails the test.
  4. Counting downwards is the same idea with the direction flipped: start
     at 50, subtract 5, and use `>=` in the condition so that the last 5
     is still printed.
  5. Counting the multiples: the number of multiples of n up to limit is
     limit / n with the fraction thrown away. 50/5 = 10 and 50/7 = 7.
  ============================================================
*/

#include <iostream>
/*
  The only header this project needs. It gives us `cout` for output and
  `endl` for a newline. C++ has no printing of its own, so this line must
  come before any use of `cout`.
*/

using namespace std;
/*
  The standard library's names live in a namespace called `std`, and `::`
  means "inside", so `std::cout` reads "the cout inside std".
  `using namespace std;` is the shortcut that saves us typing `std::` in
  front of every name, which is why plain `cout` works below.
*/

int main() {
/*
  `main` is the ENTRY POINT of the program. `int` is the return type - a
  whole number handed back to the operating system on exit. `()` means no
  parameters are passed in. `{ }` is the BODY: the instructions.
*/

    /*
      ============================================================
      PART A - THE MULTIPLES OF 5
      ============================================================
    */
    cout << "Multiples of 5 from 1 to 50:";
    // Label without a newline, so the numbers appear on the same line.

    for (int i = 5; i <= 50; i += 5) {
    /*
          |        |        |
          |        |        +-- UPDATE: add 5, so the counter lands on
          |        |            5, 10, 15, 20 ... and never in between
          |        +----------- CONDITION: keep going while i <= 50
          +-------------------- START: begin ON a multiple, not on 1
    */
        /*
          THE ONE RULE FOR MULTIPLES: the start value and the step size
          must be THE SAME NUMBER.

          Starting at 5 and stepping by 5 is what makes every value a
          multiple of 5. If the loop had started at 1, the counter would
          visit 1, 6, 11, 16 - numbers with no connection to 5 at all.

          Trace: 5(T) 10(T) 15(T) 20(T) 25(T) 30(T) 35(T) 40(T) 45(T)
                 50(T) 55(55 <= 50 is FALSE -> stop)
          Ten values printed, then the loop ends on the failed test.
        */
        cout << " " << i;
        // A space before each number keeps the values separated without
        // needing a comma or a trailing space at the end of the row.
    }
    cout << endl;

    /*
      ============================================================
      PART B - THE MULTIPLES OF 7
      ============================================================
    */
    cout << "Multiples of 7 from 1 to 50:";
    // The same label width as above, so the two rows line up.

    for (int i = 7; i <= 50; i += 7) {
        /*
          Only the numbers 7 changed: the start became 7 and the step
          became 7. The condition still stops at 50.

          Because 50 is not a multiple of 7, the run finishes early:
              7 14 21 28 35 42 49   <- 49 is the last one that fits
              56 -> "56 <= 50" is FALSE, so the loop stops here.
          That is why this row is SHORTER than the row above it, even
          though both loops use the same limit of 50.
        */
        cout << " " << i;
    }
    cout << endl;

    /*
      ============================================================
      PART C - THE SAME MULTIPLES, WALKING DOWNWARDS
      ============================================================
    */
    cout << "Multiples of 5 from 50 down to 5:";
    // A third label, this time announcing a countdown.

    for (int i = 50; i >= 5; i -= 5) {
    /*
          |        |        |
          |        |        +-- UPDATE: subtract 5 instead of adding it
          |        +----------- CONDITION: `>=` because the counter falls
          +-------------------- START: 50, which is itself a multiple
    */
        /*
          A descending walk needs THREE changes, not one:
            1. the update becomes `i -= 5` so the counter shrinks;
            2. the condition becomes `>=` so the small end is allowed in;
            3. the start is the LARGEST multiple and the limit the SMALLEST.

          Trace: 50(T) 45(T) 40(T) 35(T) 30(T) 25(T) 20(T) 15(T) 10(T)
                 5(T) 0("0 >= 5" is FALSE -> stop)

          The order of the numbers is reversed, but the SET of numbers is
          exactly the same as in part A. Exams ask about this: the values
          are the same, only the sequence differs.
        */
        cout << " " << i;
    }
    cout << endl;

    /*
      ============================================================
      PART D - HOW MANY MULTIPLES FIT IN THE RANGE?
      ============================================================
      THE FORMULA, worth memorising:
          number of multiples of n from 1 to limit  =  limit / n
      with the fraction part thrown away. The programmer's word for
      throwing away the fraction is FLOOR.

          multiples of 5 up to 50:  50 / 5 = 10 exactly        -> 10
          multiples of 7 up to 50:  50 / 7 = 7.14... -> 7      -> 7
          multiples of 3 up to 10:  10 / 3 = 3.33... -> 3      -> 3

      Check the two answers by counting the values printed above:
      part A printed ten numbers, part B printed seven. The formula agrees
      with the output.
    */

    int count5 = 0;
    int count7 = 0;
    /*
      Two accumulators declared before their loops, which is the only way
      they can still be read AFTER the loop has ended. `int` means whole
      numbers, and `= 0` gives them a safe starting value.
    */

    for (int i = 5; i <= 50; i += 5) {
        /*
          Walk the multiples of 5 one more time, but this time count them
          instead of printing them. `count5` is declared OUTSIDE the loop,
          so it is still alive when the loop ends.
        */
        count5++;
        // Add one for every multiple visited. Nine increments would give
        // 9, which is exactly why the counter starts at 0 and not at 1.
    }

    for (int i = 7; i <= 50; i += 7) {
        // And the same again for 7.
        count7++;
        // Seven passes, so count7 ends up holding 7 - matching 50 / 7 = 7.
    }

    cout << "How many multiples of 5 in 1 to 50: " << count5 << endl;
    // Reading a variable declared before a loop is perfectly legal, and it
    // is the standard way to report a result computed inside a loop.

    cout << "How many multiples of 7 in 1 to 50: " << count7 << endl;
    // The second count, and the reason it is smaller than the first.

    /*
      ------------------------------------------------------------
      TRACE TABLE
      ------------------------------------------------------------
      TRACE TABLE
      Multiples of 5 upwards,  for (int i = 5; i <= 50; i += 5)
      +-----------+------------+-------------------+--------------+
      | Iteration | i at start | Update: i += 5    | i <= 50 ?    |
      +-----------+------------+-------------------+--------------+
      |     1     |     5      | 5 + 5 = 10       | true         |
      +-----------+------------+-------------------+--------------+
      |     2     |    10      | 10 + 5 = 15      | true         |
      +-----------+------------+-------------------+--------------+
      |     3     |    15      | 15 + 5 = 20      | true         |
      +-----------+------------+-------------------+--------------+
      |     4     |    20      | 20 + 5 = 25      | true         |
      +-----------+------------+-------------------+--------------+
      |     5     |    25      | 25 + 5 = 30      | true         |
      +-----------+------------+-------------------+--------------+
      |     6     |    30      | 30 + 5 = 35      | true         |
      +-----------+------------+-------------------+--------------+
      |     7     |    35      | 35 + 5 = 40      | true         |
      +-----------+------------+-------------------+--------------+
      |     8     |    40      | 40 + 5 = 45      | true         |
      +-----------+------------+-------------------+--------------+
      |     9     |    45      | 45 + 5 = 50      | true         |
      +-----------+------------+-------------------+--------------+
      |    10     |    50      | 50 + 5 = 55      | 55<=50 FALSE |
      +-----------+------------+-------------------+--------------+
      |    11     |    55      | (never reached)  |  STOP        |
      +-----------+------------+-------------------+--------------+

      Multiples of 7 upwards,  for (int i = 7; i <= 50; i += 7)
      +-----------+------------+-------------------+--------------+
      | Iteration | i at start | Update: i += 7    | i <= 50 ?    |
      +-----------+------------+-------------------+--------------+
      |     1     |     7      | 7 + 7 = 14       | true         |
      +-----------+------------+-------------------+--------------+
      |     2     |    14      | 14 + 7 = 21      | true         |
      +-----------+------------+-------------------+--------------+
      |     3     |    21      | 21 + 7 = 28      | true         |
      +-----------+------------+-------------------+--------------+
      |     4     |    28      | 28 + 7 = 35      | true         |
      +-----------+------------+-------------------+--------------+
      |     5     |    35      | 35 + 7 = 42      | true         |
      +-----------+------------+-------------------+--------------+
      |     6     |    42      | 42 + 7 = 49      | true         |
      +-----------+------------+-------------------+--------------+
      |     7     |    49      | 49 + 7 = 56      | 56<=50 FALSE |
      +-----------+------------+-------------------+--------------+
      |     8     |    56      | (never reached)  |  STOP        |
      +-----------+------------+-------------------+--------------+

      8 - 1 = 7 multiples, which is floor(50 / 7) = 7. The formula and the
      trace agree.

      THE 10-SECOND EXAM METHOD
        To count the multiples of n from 1 to limit, do not trace anything:
            divide limit by n and throw the fraction away.
        To write the loop itself, copy the same n into BOTH the start and
        the update:
            for (int i = n; i <= limit; i += n)
        That single pattern answers most "print the multiples" questions.

      THE COMMON TRAP IN THIS FILE
        Starting the loop at 1 and stepping by 5, which gives 1, 6, 11,
        16 - a sequence of numbers that have nothing to do with 5. The
        start value must be the step size. A second trap is forgetting to
        flip the direction of the condition when counting downwards: a
        decreasing counter tested with `<=` never ends. See
        ../12_common_mistakes/05_infinite_loop.cpp.
    */

    return 0;
    // Leaves main and hands 0 (success) back to the operating system. Any
    // code written after this line would never be reached.
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: What does `for (int i = 5; i <= 50; i += 5)` print?            -> 5 10 15 20 25 30 35 40 45 50  (ten values)
  Q2: What is the LAST multiple of 7 printed before the limit?       -> 49, because 56 > 50
  Q3: How many multiples of 7 are there from 1 to 50?                -> 7
  Q4: How do you calculate that count without tracing?               -> divide 50 by 7 and throw the fraction away: 50 / 7 = 7
  Q5: Why must the start value equal the step size?                  -> so that every value the counter lands on is a multiple of that number
  Q6: What is wrong with `for (int i = 1; i <= 50; i += 5)`?        -> it prints 1 6 11 16 ... which are not multiples of 5
  Q7: What three changes turn the upward loop into a downward one?   -> start at the largest multiple, use `i -= 5` in the update, and test with `i >= 5`
  Q8: Why must `count` be declared before the loop?                 -> a variable declared inside the header or inside the braces is destroyed when the loop ends
  ============================================================
*/
