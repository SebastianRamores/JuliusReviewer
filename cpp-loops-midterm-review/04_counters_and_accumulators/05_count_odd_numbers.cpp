/*
  ============================================================
  PROGRAM: Counting How Many Odd Numbers Are in 1 to 50
  TOPIC: counters, the odd-number test, and a loop-free shortcut
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - The same COUNTER pattern applied to ODD numbers instead of even.
  - Doing the counting with a while loop, where the counter must be declared
    and incremented by hand inside the body.
  - The shortcut: the number of odd numbers in 1 to n is (n + 1) / 2, so a
    fixed range needs no loop at all - and why the truncating integer
    division still gives the right answer.

  EXPECTED OUTPUT:
  === Method 1: a while loop that tests every number ===
  Loop body ran 50 times.
  Odd numbers found: 25
  === Method 2: a while loop that steps by 2 ===
  Loop body ran 25 times.
  Odd numbers found: 25
  === Method 3: no loop at all, just the arithmetic ===
  (50 + 1) / 2 = 25, and that is how many odd numbers there are.
  === Cross-check ===
  25 odd + 25 even = 50, which is the whole list, so nothing is missing.

  IMPORTANT SYNTAX:
  int count = 0;         -> a counter, created before the loop
  while (i <= 50) { }    -> test at the top, so 0 passes is possible
  i++;                   -> add 1 to i by hand, there being no header slot
  i += 2;                -> add 2 to i, to visit odd numbers only
  count++;               -> one more odd number found
  (n + 1) / 2            -> integer division, which rounds DOWN

  STEP-BY-STEP EXPLANATION:
  1. `int i = 1;` sits ABOVE the loop, because a while header has room for
     the test only - unlike a for header, it cannot declare anything.
  2. The test `i <= 50` is asked before every pass; on the 51st, i is 51
     and the loop ends.
  3. `count++` fires only when `i % 2 == 1`, so count rises 25 times.
  4. Method 2 steps by 2 from 1, so every pass is a hit and the test can be
     deleted - 25 passes instead of 50.
  5. Method 3 uses arithmetic instead of looping; the cross-check proves the
     two counts add back up to the length of the list.
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
  A NAMESPACE is a labelled box grouping related names so two libraries cannot
  fight over the same word. `std` is the box belonging to the C++ STANDARD
  library, where `cout` and `endl` live, so the full name of our printing
  command is `std::cout`. The `::` is the SCOPE RESOLUTION OPERATOR and means
  "inside". `using namespace std;` says the names I write come from std.
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
      METHOD 1 - A while LOOP THAT TESTS EVERY NUMBER
      ================================================================
    */
    cout << "=== Method 1: a while loop that tests every number ===" << endl;

    /*
      `int count = 0;` - `int` holds whole numbers only, `=` is ASSIGNMENT
      ("store", not "equals"), and 0 is THE STARTING VALUE.

      A COUNTER answers "HOW MANY?" and always moves by exactly 1:
              count++;              shorthand for count = count + 1;
      An ACCUMULATOR answers "HOW MUCH?" and moves by the value seen:
              sum = sum + i;
      Choosing wrongly would not crash but give a wrong answer: the
      accumulator form reports 625, the sum of the odd numbers, not how many
      there are.

      THE STARTING VALUE MUST BE SET BEFORE THE LOOP: a variable declared
      inside the braces is destroyed at the closing brace and rebuilt every
      pass, so it would return to 0 and count would finish at 1.
    */
    int count = 0;

    int passes = 0;

    /*
      THE LOOP COUNTER MUST BE DECLARED OUT HERE TOO - the one real
      difference between a while loop and a for loop: a while header holds
      nothing but the condition, so it cannot declare anything.
    */
    int i = 1;

    /*
      `while (i <= 50)` asks "is i less than or equal to 50?" before every
      pass. TRUE runs the body then asks again; FALSE leaves the loop. The
      test coming first is why a bad start value runs the body ZERO times -
      the reason do...while exists.
    */
    while (i <= 50) {
        passes++;

        if (i % 2 == 1) {
        /*
          THE ODD TEST. `%` is the MODULO operator: divide, then hand back
          the LEFTOVER. `/` asks "how many times does it go in?", `%` asks
          "and what is left?". Dividing by 2 leaves only 0 or 1 behind:
              7 % 2 ->  1   one left over, so 7 is ODD
              8 % 2 ->  0   nothing left over, so 8 is EVEN
          `i % 2 == 1` reads "is the remainder one?" and `i % 2 != 0` reads
          "is the remainder NOT zero?" - the same test, since 0 and 1 are the
          only possible remainders. `!=` is NOT-EQUAL, the opposite of `==`.
        */
            /*
              `count++` is the INCREMENT operator: add 1 to count. The
              VALUE of i plays no part in it - a 1 and a 49 each count as
              exactly one hit, because we are counting, not adding.
            */
            count++;
        }
        /*
          Even numbers are still VISITED; they are simply not counted.
          `i++` is the increment. In a while loop it must be written inside
          the body by hand: there is no third header part to put it in. For-
          get it and `i <= 50` stays true for ever, so the loop never ends.
        */
        i++;
    }

    cout << "Loop body ran " << passes << " times." << endl;
    cout << "Odd numbers found: " << count << endl;

    /*
      ================================================================
      METHOD 2 - A while LOOP THAT STEPS BY 2
      ================================================================
    */
    cout << "=== Method 2: a while loop that steps by 2 ===" << endl;

    int count2 = 0;
    int passes2 = 0;

    /*
      Starting at 1 and adding 2 each pass lands only on odd numbers: 1, 3,
      5, ... 49, then 51, which fails the test and ends the loop. Every
      pass is a hit, so no `if` is needed - just raise the counter once.
    */
    int j = 1;
    while (j <= 50) {
        passes2++;
        count2++;

        // `j += 2` is compound addition, shorthand for `j = j + 2;`. It is
        // the line that eventually makes `j <= 50` false.
        j += 2;
    }

    cout << "Loop body ran " << passes2 << " times." << endl;
    cout << "Odd numbers found: " << count2 << endl;

    /*
      ================================================================
      METHOD 3 - NO LOOP AT ALL
      ================================================================
    */
    cout << "=== Method 3: no loop at all, just the arithmetic ===" << endl;

    /*
      THE SHORTCUT: in the run 1 to n the odd numbers take alternate slots,
      so there are half of them, rounded UP - that is (n + 1) / 2.

        n = 50:  (50 + 1) / 2  =  51 / 2
      `/` is INTEGER DIVISION when both sides are ints, and it does not round
      to nearest - it TRUNCATES, throwing the fraction away. So 51 / 2 is 25,
      not 25.5 and not 26. That is not an error: 25 is exactly the answer,
      because a count of numbers can never be a half. The same code is right
      at n = 49 too, where (49 + 1) / 2 is 25 exactly.

    */
    int n = 50;
    int byFormula = (n + 1) / 2;
    cout << "(" << n << " + 1) / 2 = " << byFormula
         << ", and that is how many odd numbers there are." << endl;

    /*
      ================================================================
      CROSS-CHECK
      ================================================================
    */
    cout << "=== Cross-check ===" << endl;

    /*
      Every whole number is either odd or even, never both and never
      neither, so odd count + even count must give back the length of the
      list. The even count of 25 was proved by a loop in file 04.
    */
    int evenCount = 25;

    if (count + evenCount == n) {
        cout << count << " odd + " << evenCount << " even = " << (count + evenCount)
             << ", which is the whole list, so nothing is missing." << endl;
    } else {
        cout << "Something is wrong: " << (count + evenCount) << " is not " << n << "." << endl;
    }

    /*
      ================================================================
      TRACE TABLE - METHOD 1, the pass counter against the hit counter
      ================================================================
      Rows 1 to 4 and 49 to 51 are shown; the rows between repeat the same
      two patterns, so they are elided with "...".
      +-----------+------------+-----------+--------+--------------------+--------+
      | Iteration | i at start | passes    | count  | i % 2 == 1 ?       | Output |
      +-----------+------------+-----------+--------+--------------------+--------+
      | 1         | 1          | 1         | 0      | TRUE  - odd        | (none) |
      | 2         | 2          | 2         | 0      | FALSE - even       | (none) |
      | 3         | 3          | 3         | 0 -> 1 | TRUE  - odd        | (none) |
      | 4         | 4          | 4         | 1      | FALSE - even       | (none) |
      | ...       | ...        | ...       | ...    | ...                | ...    |
      | 49        | 49         | 49        | 24     | TRUE  - odd        | (none) |
      | 50        | 50         | 50        | 24     | FALSE - even       | (none) |
      | 51        | 51         | (no more) | 25     | the loop has ended | (none) |
      +-----------+------------+-----------+--------+--------------------+--------+

      Compare the two counters: passes reaches 50 while count reaches only
      25, because passes rises every pass and count every other one. Row 51
      is the failing test: 51 is odd and would have been a hit, but
      `51 <= 50` is false, so the body is skipped. 50 itself is even.

      THE COMMON TRAP IN THIS FILE
        Forgetting `i++;` at the bottom of the body. A for loop has it in
        the header where it is hard to lose; a while loop puts it in the
        body, where it is easy to leave out. The result is an infinite loop
        printing the same line until you kill it - i stays 1, so `i <= 50`
        stays true. Method 2 hangs the same way without its `i += 2`.
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
  Q1: How many odd numbers are there between 1 and 50?  -> 25
  Q2: Why must `i` be declared above the while loop?  -> a while header holds only the condition, so there is nowhere inside it to declare anything
  Q3: What does integer division do with the 51 / 2 in Method 3?  -> it truncates, giving 25 and discarding the .5
  Q4: What would happen if `i++;` were deleted from Method 1?  -> an infinite loop, because i would stay 1 and the test would stay true
  Q5: What would count be if `count++` were replaced by `count = count + i`?  -> the sum of the odd numbers, 625, not the number of them
*/
