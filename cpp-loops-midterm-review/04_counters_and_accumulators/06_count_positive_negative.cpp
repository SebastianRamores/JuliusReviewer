/*
  ============================================================
  PROGRAM: Counting Positives, Negatives and Zeros in a List
  TOPIC: three counters + if / else if / else, and reading an array
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - How to store a fixed list of numbers in an ARRAY and walk through it
    with an index, and that array counting starts at 0, not 1.
  - Using THREE separate counters at the same time, one for each category.
  - `if / else if / else`: testing several possibilities in order, and
    why only ONE branch can run for any single number.
  - `> 0`, `< 0` and "neither", which together cover every whole number.

  EXPECTED OUTPUT:
  === Counting positives, negatives and zeros ===
  The list holds 10 numbers.
  Positives: 5
  Negatives: 4
  Zeros: 1
  === Check ===
  5 + 4 + 1 = 10, which matches the length of the list.

  IMPORTANT SYNTAX:
  int numbers[] = {5, -3, 0, ...};  -> an ARRAY: a fixed row of int values
  numbers[i]                       -> the value stored at position i
  int howMany = 10;                -> how many values the array holds
  if (numbers[i] > 0) { } else if (numbers[i] < 0) { } else { }
                                  -> only ONE of these three branches runs
  positives++;                     -> raise one counter by 1

  STEP-BY-STEP EXPLANATION:
  1. The array holds the ten fixed values. An array is a row of boxes, all
     of the same type, and every box has a NUMBER called an index.
  2. Indexing starts at 0, so the values live at 0 to 9. `numbers[0]` is
     5 and `numbers[9]` is 4. Position 10 would be past the end.
  3. All three counters are set to 0 BEFORE the loop, since each starts by
     finding nothing.
  4. The loop visits every box once. For each value exactly one of the
     three branches runs and raises its counter by 1.
  5. The final check adds the three counters and finds 10, which is the
     length of the list - proof that every value was counted exactly once.
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
      THE DATA - A FIXED LIST, GIVEN AS AN ARRAY
      ================================================================
      An ARRAY is a fixed row of values, all of the same type, where each
      value sits in its own numbered box. The position number is called an
      INDEX. Three things to notice in this one line:
        numbers  is the name of the row.
        []       after the name means "this is an array of unknown length".
        { }      the values themselves, separated by commas. The length is
                 worked out from the values, so there is no number to keep
                 in step with them by hand.
      Arrays are allowed from this lesson onwards. Nothing else new is
      introduced: the loop is an ordinary `for` loop with an ordinary counter.
    */
    int numbers[] = {5, -3, 0, 12, -7, 8, -1, 20, -15, 4};

    /*
      THE LENGTH. Ten values were listed, so the valid indexes run 0 to 9.
      INDEXING STARTS AT 0, not at 1 - this catches everybody at first. The
      last value is at numbers[9], and numbers[10] would be past the end of
      the row, which is a serious error rather than a tidy mistake.
    */
    int howMany = 10;

    /*
      ================================================================
      THREE COUNTERS, ALL STARTING AT 0
      ================================================================
      Every counter here answers "HOW MANY?", so every one of them moves by
      exactly 1 each time it fires - `count++`. That is what makes a variable
      a COUNTER rather than an ACCUMULATOR: an accumulator answers "how
      much?" and moves by the value it is given, as in `sum = sum + i;`.

      All three are created BEFORE the loop. A variable declared inside the
      braces would be destroyed at the closing brace and rebuilt on every
      pass, so it would always go back to 0 and the counts would never build.
    */
    int positives = 0;
    int negatives = 0;
    int zeros = 0;

    /*
      ================================================================
      THE LOOP - ONE PASS PER VALUE, THREE POSSIBLE OUTCOMES
      ================================================================
      Stepping by 1 from 0 visits boxes 0, 1, 2 ... 9 - every single value,
      because this time there is no way to skip ahead.
    */
    for (int i = 0; i < howMany; i++) {
        /*
          `numbers[i]` reads the value stored in box i. It can be used
          anywhere a number can: compared, printed or added. Here it is
          compared three times, and each time the value is fetched afresh.
        */

        // `if (numbers[i] > 0)` asks "is the value greater than zero?". `>` is
        // the "greater than" comparison: TRUE means positive.
        if (numbers[i] > 0) {
            positives++;

        /*
          `else if` means "otherwise, but check this next thing". It is only
          looked at when the `if` above was false, so for any single value
          exactly ONE branch in the whole chain ever runs. Testing the signs
          in the order above - positive, then negative, then "neither" -
          leaves no value uncategorised and no value counted twice.
        */
        } else if (numbers[i] < 0) {
            // `<` is the "less than" comparison: TRUE means negative, i.e.
            // below zero.
            negatives++;

        /*
          `else` has NO condition of its own. It means "and if none of the
          above was true". Reaching here means the value was not above 0
          and not below 0, and the only whole number that is neither is 0
          itself.
        */
        } else {
            zeros++;
        }
    }

    /*
      ================================================================
      REPORTING
      ================================================================
    */
    cout << "=== Counting positives, negatives and zeros ===" << endl;
    cout << "The list holds " << howMany << " numbers." << endl;
    cout << "Positives: " << positives << endl;
    cout << "Negatives: " << negatives << endl;
    cout << "Zeros: " << zeros << endl;

    cout << "=== Check ===" << endl;

    /*
      The three categories must cover the whole list exactly once, so their
      total has to equal the length. If it does not, a value has been missed
      or counted twice - which is a bug worth catching in the program rather
      than in a marked answer.
    */
    cout << positives << " + " << negatives << " + " << zeros
         << " = " << (positives + negatives + zeros)
         << ", which matches the length of the list." << endl;

    /*
      ================================================================
      TRACE TABLE - all ten values, then the failing test
      ================================================================
      +-----------+----+------------+--------------+--------------+-------------+------------------+
      | Iteration | i  | numbers[i] | > 0 ?        | < 0 ?        | Branch      | Counts P / N / Z |
      +-----------+----+------------+--------------+--------------+-------------+------------------+
      | 1         | 0  | 5          | TRUE         | FALSE        | positives++ | 1 / 0 / 0        |
      | 2         | 1  | -3         | FALSE        | TRUE         | negatives++ | 1 / 1 / 0        |
      | 3         | 2  | 0          | FALSE        | FALSE        | zeros++     | 1 / 1 / 1        |
      | 4         | 3  | 12         | TRUE         | FALSE        | positives++ | 2 / 1 / 1        |
      | 5         | 4  | -7         | FALSE        | TRUE         | negatives++ | 2 / 2 / 1        |
      | 6         | 5  | 8          | TRUE         | FALSE        | positives++ | 3 / 2 / 1        |
      | 7         | 6  | -1         | FALSE        | TRUE         | negatives++ | 3 / 3 / 1        |
      | 8         | 7  | 20         | TRUE         | FALSE        | positives++ | 4 / 3 / 1        |
      | 9         | 8  | -15        | FALSE        | TRUE         | negatives++ | 4 / 4 / 1        |
      | 10        | 9  | 4          | TRUE         | FALSE        | positives++ | 5 / 4 / 1        |
      | 11        | 10 | (no more)  | (not tested) | (not tested) | loop ended  | 5 / 4 / 1        |
      +-----------+----+------------+--------------+--------------+-------------+------------------+

      Row 3 is the interesting one: for a value of 0 the test `0 > 0` is
      false AND the test `0 < 0` is false, so control falls through both
      branches to the bare `else`. That is why the last branch needs no
      condition at all - it catches whatever the others rejected.

      THE COMMON TRAP IN THIS FILE
        Writing the loop as `for (int i = 1; i <= howMany; i++)`. Starting
        at 1 SKIPS the first value and reading numbers[10] runs off the end
        of the row entirely. The loop must be `i = 0; i < howMany;`. Array
        indexes run 0 to howMany - 1, which is why the test uses `<` and not
        `<=`. The check at the bottom is what makes the mistake visible: the
        counts would add up to 9 instead of 10.
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
  Q1: How many positives, negatives and zeros are in the list?  -> 5 positives, 4 negatives and 1 zero
  Q2: Which indexes does the array actually use?  -> 0 to 9, because indexing starts at 0 for ten values
  Q3: Why does the `else` branch not need a condition?  -> a value that is neither above 0 nor below 0 can only be 0
  Q4: What is wrong with `for (int i = 1; i <= howMany; i++)` here?  -> it skips box 0 and reads past the end at numbers[10]
  Q5: What would the total check print if one value had been missed?  -> the sum would be 9 rather than 10, showing a value was uncounted
*/
