/*
  ============================================================
  PROGRAM: Adding Up 1 to N - the Accumulator and its Shortcut
  TOPIC: accumulators + the closed formula n * (n + 1) / 2
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - The classic ACCUMULATOR: `sum` is created as 0 BEFORE the loop and
    grows inside it, so its value survives from pass to pass.
  - WHY the accumulator must start at 0 rather than 1, in plain words.
  - The arithmetic-operator family `+ - * / %` and what each is for.
  - The 10-second formula n * (n + 1) / 2, and a loop that checks it.
  - Why `n * (n + 1) / 2` always divides exactly, for every whole n.

  EXPECTED OUTPUT:
  === Adding up 1 to 10 with a loop ===
  The loop total is 55
  === The 10-second formula n * (n + 1) / 2 ===
  For n = 10 the formula gives 55
  === Checking that the two agree ===
  55 == 55 - the loop matches the formula.

  IMPORTANT SYNTAX:
  int sum = 0;               -> an accumulator starts at zero
  sum = sum + i;             -> fold the new value into the running total
  sum += i;                  -> exactly the same thing, written shorter
  n * (n + 1) / 2            -> multiply, then add 1, then divide by 2
  sum == formula             -> "are these two the same?" (a question)

  STEP-BY-STEP EXPLANATION:
  1. `int n = 10;` is the upper limit, given a name so the loop and the
     formula can both use it and be changed in one place.
  2. `int sum = 0;` is the accumulator, created BEFORE the loop. This is
     the single most important line in the program.
  3. The loop adds i into sum for every i from 1 to n, then i++ moves on.
  4. After the loop sum holds the finished answer, 55.
  5. `n * (n + 1) / 2` computes the same answer with no loop at all: the
     maths has a shortcut that saves you writing the loop on an exam.
  6. `==` compares the two answers so the agreement is proven, not assumed.
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
      PART 1 - THE LOOP, WITH AN ACCUMULATOR
      ================================================================
    */
    cout << "=== Adding up 1 to 10 with a loop ===" << endl;

    /*
      `int n = 10;`
        int   the DATA TYPE: whole numbers only, never 2.5.
        n     the name; short for "n", the end of the range.
        =     ASSIGNMENT - "store this value", not "equals".
        10    the INITIAL VALUE.  `;` ends the statement.
      Naming the limit means the loop reads `i <= n` rather than `i <= 10`,
      so changing the problem means editing a single number.
    */
    int n = 10;

    /*
      THE ACCUMULATOR. Two separate jobs are going on in this program and
      they must not be confused:
        i    is the COUNTER. It asks "which number am I on?". It moves by a
              fixed step each pass and the loop condition reads it.
        sum  is the ACCUMULATOR. It asks "what have I worked out so far?".
              It takes the answer it already holds and folds in one more
              value, so the answer survives from pass to pass.

      WHY sum MUST START AT 0:
        Adding is done from nothing upwards. The total of a set of numbers
        begins at nothing, so the accumulator begins at nothing. In symbols,
        0 is the IDENTITY for `+`: 0 + anything = anything. That means the
        first number passes straight through untouched.
        Starting at 1 instead would be wrong by exactly 1: the answer would
        come out as 56 rather than 55. The compiler would not complain,
        because the code is perfectly legal - it is simply the wrong answer.
        (Multiply by a starting 0 and you get 0 for ever; see file 08.)
    */
    int sum = 0;

    /*
      The three header parts, always in this order, always split by two
      semicolons: INITIALISATION, CONDITION, UPDATE.
        int i = 1  runs once, ever
        i <= n     tested before every pass; FALSE leaves the loop
        i++        runs after every pass, so the test can eventually fail
    */
    for (int i = 1; i <= n; i++) {

        /*
          The accumulator line. Read it in two steps:
            1. work out sum + i using the values both hold right now - on
               the first pass that is 0 + 1.
            2. store the answer back into sum. The old sum is then gone,
               but it has already been folded into the new value, so
               nothing is lost.
        */
        sum = sum + i;
    }

    /*
      sum still exists here because it was created OUTSIDE the loop. A
      variable created inside a loop's braces is destroyed at the closing
      brace and could not be printed from here.
    */
    cout << "The loop total is " << sum << endl;

    /*
      ================================================================
      PART 2 - THE 10-SECOND FORMULA
      ================================================================
    */
    cout << "=== The 10-second formula n * (n + 1) / 2 ===" << endl;

    /*
      THE ARITHMETIC OPERATORS, all of them:
        +   addition        3 + 4   is 7
        -   subtraction     7 - 4   is 3
        *   multiplication  3 * 4   is 12
        /   division        12 / 4  is 3   (with two ints the answer is
                                           rounded DOWN - "truncated")
        %   modulo, the LEFTOVER after division: 12 % 4 is 0 and 13 % 4
            is 1. This is the operator that detects even and odd numbers.
    */

    /*
      The formula, using the same n as the loop:
        * first, giving 10 * 11 = 110
        / then, giving 110 / 2 = 55
      The parentheses around (n + 1) are ESSENTIAL. Without them C++ would
      follow a strict left-to-right order and calculate
        n * n + 1 / 2   =   10 * 10 + 0   =   100
      because division binds more tightly than multiplication, just as
      multiplication binds more tightly than addition. Brackets always win.

      WHY THE DIVISION IS ALWAYS EXACT: one of n and n+1 must be even, so
      n * (n + 1) is always a multiple of 2 and there is never a remainder
      to lose. Try n = 7: 7 * 8 = 56, and 56 / 2 = 28 exactly. This is
      what makes the shortcut safe for every whole number n.
    */
    int formula = n * (n + 1) / 2;

    cout << "For n = " << n << " the formula gives " << formula << endl;

    /*
      ================================================================
      PART 3 - PROVE THE TWO AGREE
      ================================================================
    */
    cout << "=== Checking that the two agree ===" << endl;

    /*
      `==` is the EQUALITY COMPARISON: "are these two numbers the same?".
      It answers true or false and changes nothing. Compare it with `=`,
      which is ASSIGNMENT and would overwrite sum with formula's value,
      destroying one of the two answers being compared.
    */
    if (sum == formula) {
        cout << sum << " == " << formula << " - the loop matches the formula." << endl;
    } else {
        /*
          The else runs only when the condition above is false. Keeping an
          else branch is good habit: a program that silently prints nothing
          on failure is much harder to debug than one that says so.
        */
        cout << "They disagree: the loop gave " << sum
             << " but the formula gave " << formula << "." << endl;
    }

    /*
      ================================================================
      TRACE TABLE - the accumulator, pass by pass
      ================================================================
      Every iteration is listed, and row 11 is the failing test that ends
      the loop. There is no output column because the program prints the
      total once, after the loop has finished.
      +-----------+------------+------------+----------------+------------+
      | Iteration | i at start | sum before | sum after      | Test: i<=n |
      +-----------+------------+------------+----------------+------------+
      | 1         | 1          | 0          | 0 + 1 = 1      | TRUE       |
      | 2         | 2          | 1          | 1 + 2 = 3      | TRUE       |
      | 3         | 3          | 3          | 3 + 3 = 6      | TRUE       |
      | 4         | 4          | 6          | 6 + 4 = 10     | TRUE       |
      | 5         | 5          | 10         | 10 + 5 = 15    | TRUE       |
      | 6         | 6          | 15         | 15 + 6 = 21    | TRUE       |
      | 7         | 7          | 21         | 21 + 7 = 28    | TRUE       |
      | 8         | 8          | 28         | 28 + 8 = 36    | TRUE       |
      | 9         | 9          | 36         | 36 + 9 = 45    | TRUE       |
      | 10        | 10         | 45         | 45 + 10 = 55   | TRUE       |
      | 11        | 11         | 55         | (body skipped) | FALSE      |
      +-----------+------------+------------+----------------+------------+

      Reading the sum-before column downwards gives 0, 1, 3, 6, 10, 15, 21,
      28, 36, 45, 55 - and each of those is the sum-after of the row above.
      That hand-off between rows IS the accumulator, and it is the thing an
      exam marker is looking for.

      THE COMMON TRAP IN THIS FILE
        Writing `int sum;` with no starting value, or `int sum = 1;`.
        With no value at all the program is illegal in C++ - the compiler
        refuses with "sum was not initialised" - because there would be no
        answer to add to on the first pass. With 1 it compiles perfectly and
        prints 56. Accumulators must be given a value BEFORE the loop, and
        that value must be the identity for the operator being used:
          adding      -> 0
          multiplying  -> 1
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
  Q1: What value must an adding accumulator start at, and why?  -> 0, because 0 is the identity for + so the first number passes through unchanged
  Q2: What does this loop produce for n = 10?  -> 55, from 1 + 2 + 3 + ... + 10
  Q3: Why are the brackets needed in n * (n + 1) / 2?  -> without them division happens before multiplication, giving 100 instead of 55
  Q4: Why does n * (n + 1) / 2 never lose a fraction?  -> one of n and n+1 is always even, so the product divides by 2 exactly
  Q5: What is the difference between `sum == formula` and `sum = formula`?  -> `==` compares them, while `=` overwrites sum and loses the loop answer
*/
