/*
  ============================================================
  PROGRAM: while Loop Counting - Downwards, and in Steps
  TOPIC: while loops with different starting values and steps
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - A while loop that counts DOWNWARDS, and why its condition uses `>=`
    instead of the `<=` used for counting up.
  - A while loop that moves by 3 each pass instead of 1.
  - What happens to the counter once the loop ends: it always overshoots.
  - Why the counter must be declared ABOVE the loop if we want to read
    it after the loop has finished.

  EXPECTED OUTPUT:
  === Part 1: counting DOWN from 5 to 1 ===
  5
  4
  3
  2
  1
  The counter stopped at 0
  === Part 2: counting UP in steps of 3 ===
   1 4 7 10 13 16 19
  The counter overshot the limit to 22
  === Part 3: a counter declared ABOVE the loop ===
  Counter before the loop: 10
  Counter after the loop: 0

  IMPORTANT SYNTAX:
  int i = 5;                 -> create a whole-number variable i that holds 5
  while (i >= 1) { ... }     -> "while i is at least 1, keep going"
  i--                        -> subtract 1 from i (shorthand for i = i - 1)
  i += 3;                    -> add 3 to i, in one statement
  i -= 2;                    -> subtract 2 from i, in one statement
  cout << "text";            -> print text held in quotes

  STEP-BY-STEP EXPLANATION:
  1. Part 1 starts i at 5 and uses `i--`, so i travels 5, 4, 3, 2, 1, 0.
     The test `i >= 1` fails at 0, so the loop stops there - NOT at -1.
     That is why a descending loop must use `>= 1` and not `> 1`, or the
     number 1 itself would never be printed.
  2. Part 2 starts j at 1 and uses `j += 3`, so j visits 1, 4, 7, 10, 13,
     16, 19 and then jumps to 22, which is past the limit of 20.
  3. Part 3 prints nothing inside the loop at all. The loop exists purely to
     move the counter, and the counter is readable afterwards only because
     it was declared before the loop.
  ============================================================
*/

#include <iostream>
/*
  <iostream> is the header file that gives C++ its ability to talk to the
  terminal. It supplies `cout` for output, `cin` for input and `endl` for
  ending a line. The language on its own can only calculate and compare -
  every facility for showing a result on screen is borrowed from a library,
  and this one line invites that library in. Without it the compiler reports
  "cout was not declared in this scope".
*/


using namespace std;
/*
  A NAMESPACE is a labelled box that groups related names so two libraries
  cannot fight over the same word. `std` is the box belonging to the C++
  STANDARD library, where `cout` and `endl` live, so the real name of our
  printing command is `std::cout`. The `::` between them is the SCOPE
  RESOLUTION OPERATOR and means "inside": look inside the std box.
  `using namespace std;` says "assume the names I write come from std",
  which is why plain `cout` works below.
*/

int main() {
/*
  `main` is the ENTRY POINT: the first function the operating system runs
  when the program starts. `int` is its RETURN TYPE, so when main finishes
  it hands a whole number back as an exit status. `()` is the parameter
  list and it is empty, meaning main is called with nothing. The `{ }`
  braces are the BODY - the instructions inside run top to bottom.
*/

    /*
      ================================================================
      PART 1 - COUNTING DOWNWARDS
      ================================================================
    */
    cout << "=== Part 1: counting DOWN from 5 to 1 ===" << endl;

    /*
      `int` whole numbers only, so 2.5 could never be stored in this.
      `i`   the variable name; short for "index", a loop counter.
      `=`   ASSIGNMENT: "store", not "equals". `==` asks "is i equal to 5?".
      `5`   the INITIAL VALUE i is born holding.  `;` ends the statement.
    */
    int i = 5;

    /*
      `while` is a KEYWORD, so it can never be a variable name.
      `i >= 1` reads aloud as "is i greater than or equal to 1?". The `>=`
      means greater than OR EQUAL TO, so the value 1 is still let in. A
      descending loop needs `>=`, because the loop must run while the counter
      has not yet fallen past 1.
        - TRUE  -> run the body, then test again.
        - FALSE -> leave the loop and carry on after the `}`.
    */
    while (i >= 1) {
        cout << i << endl;

        /*
          `i--` is the DECREMENT OPERATOR: subtract 1 from i. It is exactly
          the same as `i = i - 1;` or `i -= 1;`. It moves i towards the
          point where `i >= 1` becomes false.
        */
        i--;
    } // end of the loop body

    // i is now 0. Notice the loop stopped AT 0 rather than going on to -1:
    // the failing test stops the loop before the body can run again.
    cout << "The counter stopped at " << i << endl;

    /*
      ================================================================
      PART 2 - COUNTING UP IN STEPS OF 3
      ================================================================
    */
    cout << "=== Part 2: counting UP in steps of 3 ===" << endl;

    // The INITIAL VALUE decides where the run starts. Starting at 1 and
    // stepping by 3 reaches 1, 4, 7, 10, 13, 16, 19 - never 2 or 3.
    int j = 1;
    // The limit is 20, which is NOT a multiple of 3, so the run overshoots.
    while (j <= 20) {
        /*
          The space is printed BEFORE the number rather than after it. That
          way the line never ends in a stray space, and the numbers come out
          neatly separated: " 1 4 7 10 13 16 19".
        */
        cout << " " << j;

        /*
          `j += 3` is the COMPOUND ASSIGNMENT OPERATOR: add 3 to j. It is
          shorthand for `j = j + 3;`. The same family includes `+=`, `-=`,
          `*=` and `/=`, and using them avoids the slip of typing one `=`
          too few and accidentally overwriting j instead of adding to it.
        */
        j += 3;
    }

    cout << endl;   // closes the line that Part 2 started

    // j has jumped past the limit: 19 + 3 = 22, and 22 <= 20 is false.
    cout << "The counter overshot the limit to " << j << endl;

    /*
      ================================================================
      PART 3 - A COUNTER DECLARED ABOVE THE LOOP, READ BELOW IT
      ================================================================
    */
    cout << "=== Part 3: a counter declared ABOVE the loop ===" << endl;

    // Declared out here, NOT inside the loop. A variable created inside a
    // loop's braces dies at the closing brace; created out here it survives.
    int countdown = 10;
    cout << "Counter before the loop: " << countdown << endl;

    // No printing inside this loop at all. Its only job is to move the
    // counter, which makes the effect of `countdown -= 2` easy to see.
    while (countdown > 0) {
        // `countdown -= 2` is compound subtraction: take 2 away, i.e.
        // shorthand for `countdown = countdown - 2;`.
        countdown -= 2;
    }

    // Only possible because countdown was declared above the loop.
    cout << "Counter after the loop: " << countdown << endl;

    /*
      ================================================================
      TRACE TABLE - PART 1, counting DOWN from 5
      ================================================================
      +-----------+------------+----------------+-----------+
      | Iteration | i at start | Test: i >= 1   | Output    |
      +-----------+------------+----------------+-----------+
      | 1         | 5          | 5 >= 1   TRUE  | 5         |
      +-----------+------------+----------------+-----------+
      | 2         | 4          | 4 >= 1   TRUE  | 4         |
      +-----------+------------+----------------+-----------+
      | 3         | 3          | 3 >= 1   TRUE  | 3         |
      +-----------+------------+----------------+-----------+
      | 4         | 2          | 2 >= 1   TRUE  | 2         |
      +-----------+------------+----------------+-----------+
      | 5         | 1          | 1 >= 1   TRUE  | 1         |
      +-----------+------------+----------------+-----------+
      | 6         | 0          | 0 >= 1   FALSE | (nothing) |
      +-----------+------------+----------------+-----------+

      `i >= 1` matters on row 5: with `i > 1` the value 1 would be skipped
      and the loop would end one pass early printing only 5 4 3 2.

      ================================================================
      TRACE TABLE - PART 2, stepping by 3
      ================================================================
      +-----------+------------+----------------+--------+
      | Iteration | j at start | Test: j <= 20  | Output |
      +-----------+------------+----------------+--------+
      | 1         | 1          | 1 <= 20  TRUE  | 1      |
      +-----------+------------+----------------+--------+
      | 2         | 4          | 4 <= 20  TRUE  | 4      |
      +-----------+------------+----------------+--------+
      | 3         | 7          | 7 <= 20  TRUE  | 7      |
      +-----------+------------+----------------+--------+
      | 4         | 10         | 10 <= 20 TRUE  | 10     |
      +-----------+------------+----------------+--------+
      | 5         | 13         | 13 <= 20 TRUE  | 13     |
      +-----------+------------+----------------+--------+
      | 6         | 16         | 16 <= 20 TRUE  | 16     |
      +-----------+------------+----------------+--------+
      | 7         | 19         | 19 <= 20 TRUE  | 19     |
      +-----------+------------+----------------+--------+
      | 8         | 22         | 22 <= 20 FALSE | (none) |
      +-----------+------------+----------------+--------+

      Part 3 by hand, as a trace: 10>0 true so 10 becomes 8; 8>0 true so 8
      becomes 6; 6>0 true so 6 becomes 4; 4>0 true so 4 becomes 2; 2>0 true
      so 2 becomes 0; 0>0 is FALSE so the loop ends. The body ran 5 times and
      the counter finished at exactly 0, because 10 is an exact multiple of
      2. Had it started at 11 it would end at -1, overshooting downwards in
      the same way Part 2 overshoots upwards.

      THE COMMON TRAP IN THIS FILE
        Copying the `>=` from the down loop into the up loop, or writing
        `while (i <= 1)` when counting down. Both read fine in your head and
        both give the wrong answer. Decide first whether the counter is
        rising or falling, then pick the matching operator:
          rising  -> start low,  test i <= limit,  use i++  / i += step
          falling -> start high, test i >= limit,  use i--  / i -= step
        Remember `<=` and `>=` INCLUDE the limit while `<` and `>` exclude it.
    */

    return 0;
    /*
      `return 0;` ends main straight away and hands 0 back to the operating
      system. Zero is the conventional code for "success", meaning the
      program ran to the end without an error. The precise number is
      unimportant on a modern system, but exams expect to see it, so it is
      always written as the final statement of main.
    */
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: Why does the down loop use `i >= 1` and not `i > 1`?  -> `>=` includes 1 so it is still printed; `>` would stop at 2 and skip it
  Q2: How many times does the body of Part 2 run?  -> 7 times, for j = 1, 4, 7, 10, 13, 16, 19
  Q3: What is the value of j when the loop ends, and why?  -> 22, because 19 + 3 overshoots 20 before the test can fail
  Q4: `i += 3;` is shorthand for which statement?  -> i = i + 3;
  Q5: Why can Part 3 print countdown after the loop?  -> it was declared above the loop, so it survives the closing brace
*/
