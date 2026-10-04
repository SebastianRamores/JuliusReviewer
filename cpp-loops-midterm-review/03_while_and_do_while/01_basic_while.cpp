/*
  ============================================================
  PROGRAM: Basic while Loop - Counting from 1 to 5
  TOPIC: while loops
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - The three parts every working loop needs: a variable to steer the
    loop, a CONDITION that decides when to stop, and an UPDATE that
    eventually makes that condition false.
  - That a while loop tests its condition BEFORE the body runs, so a
    badly chosen starting value means the body runs ZERO times.
  - How to read `while (i <= 5)` out loud as an English sentence.
  - Why `int i = 1;` is written above the loop and not inside it.

  EXPECTED OUTPUT:
  Counting from 1 to 5 with a while loop:
  1
  2
  3
  4
  5
  The loop has finished.
  i is now 6

  IMPORTANT SYNTAX:
  while (condition) { body }  -> keep repeating the body while the condition is true
  int i = 1;                  -> create a whole-number variable i that holds 1
  i <= 5                      -> "is i less than or equal to 5?"
  i++                         -> add 1 to i (shorthand for i = i + 1)
  cout << i << endl;          -> print i, then move to the start of a new line
  ;                           -> finishes a statement

  STEP-BY-STEP EXPLANATION:
  1. `int i = 1;` runs once, before the loop starts. i holds 1.
  2. `while (i <= 5)` asks a yes/no question. If YES the body runs; if NO
     the program skips to the first line after the closing brace.
  3. The body prints i and then adds 1 to i, so i becomes 2.
  4. The test runs again using the new value of i. This repeats until i
     holds 6, at which point `6 <= 5` is false and the loop ends.
  5. Because i was declared ABOVE the loop it still exists here, so we can
     print where it finished up: 6.
  ============================================================
*/

#include <iostream>
/*
  <iostream> is a HEADER FILE supplied by the C++ standard library, and it
  is what gives us the tools for talking to the terminal: `cout` (console
  output), `endl` (end line) and `cin` (keyboard input).
  C++ itself is perfectly happy doing arithmetic and comparisons, but it has
  NO built-in way to show a result on the screen. That ability lives in the
  library, and this single line invites the library in. Leave it out and the
  compiler stops with "cout was not declared in this scope".
*/

using namespace std;
/*
  `std` is the name of the STANDARD library, and a NAMESPACE is simply a
  labelled box that groups names together so two different libraries cannot
  clash over the same word. Everything from the standard library sits inside
  the std box, so the full name of our printing command is `std::cout`.
  The `::` is called the SCOPE RESOLUTION OPERATOR and it means "inside", in
  the sense of "look inside the std box and fetch cout".
  `using namespace std;` tells the compiler "assume the names I use come
  from std", which is why plain `cout` is enough below. Beginners are
  expected to write this line; the stricter professional habit is to leave
  it out and type std:: yourself every single time.
*/

int main() {
/*
  `main` is the ENTRY POINT of every C++ program: the first function the
  operating system calls once the program starts. It is the front door.
  `int` in front of `main` is the RETURN TYPE. When main finishes it hands
  a whole number back to the operating system as an exit status.
  The `()` are the PARAMETER LIST and here it is empty: main is given
  nothing at all when it is called.
  The `{ }` braces are the BODY. Every instruction between them is carried
  out top to bottom, one statement at a time.
*/

    /*
      ----------------------------------------------------------------
      STEP 1 - CREATE THE CONTROL VARIABLE, BEFORE THE LOOP
      ----------------------------------------------------------------
      `int` is the DATA TYPE. It holds only whole numbers such as 0, 1,
            -7 or 1000, and can never hold a decimal such as 2.5.
      `i`   is the VARIABLE NAME, and we choose that ourselves. `i` is short
            for "index", the traditional name for a loop counter. Other
            names work exactly as well: n, k, count, number, i.
      `=`   is the ASSIGNMENT OPERATOR. Read it as "store", never as
            "equals". `i = 1` means "put the value 1 into i". Compare with
            `i == 1`, which asks the question "is i equal to 1?".
      `1`   is the INITIAL VALUE - what i holds at the moment it is born.
      `;`   ends the statement. A forgotten semicolon is the single most
            common compile error a beginner makes.
      The declaration sits HERE, above the loop, on purpose: then i is still
      alive after the loop ends and we are able to print its final value.
    */
    int i = 1;

    /*
      `cout` is console output - it sends the text to the screen.
      `<<` is the STREAM INSERTION OPERATOR, and the arrows point the way
      the data travels: from the string, into cout. Several `<<` can be
      chained, meaning "send this, then that, then that".
      "Counting from 1 to 5..." is a STRING LITERAL: text wrapped in double
      quotation marks so the compiler knows it is text and not code.
      `endl` ends the line. It is a MANIPULATOR - a plain name rather than a
      function, which is why there are no parentheses after it. It writes a
      newline character and flushes the buffer so the text shows at once.
    */
    cout << "Counting from 1 to 5 with a while loop:" << endl;

    /*
      ----------------------------------------------------------------
      STEP 2 - THE while LOOP
      ----------------------------------------------------------------
      while (condition) { body }
      `while` is a KEYWORD - a word the language reserves for its own use,
      so you may never use `while` as a variable name.
      The ( ... ) is the loop HEADER. Whatever sits inside must be
      something the computer can call TRUE or FALSE.
      `i <= 5`, read aloud, is "is i less than OR EQUAL TO 5?". The `<=`
      operator means less than or equal to, so the value 5 itself is still
      let through. Using plain `<` instead would print only 1, 2, 3, 4.
        - TRUE  -> run the body once, then come back and ask again.
        - FALSE -> skip the body completely and carry on after the `}`.
      THE TEST HAPPENS FIRST. That single fact is what separates a while
      loop from a do...while loop, where the body is always done at least
      once even when the test is false from the very start.
    */
    while (i <= 5) {
        /*
          `i` is a variable, so the NUMBER it currently holds is sent, not
          the letter itself. `endl` then ends the line so the next print
          starts one row lower.
        */
        cout << i << endl;

        /*
          `i++` is the INCREMENT OPERATOR: add 1 to i. It means exactly the
          same as `i = i + 1;` or `i += 1;`.
          Without this line i would stay 1 for ever, the condition would
          stay true for ever, and the program would print 1 until you
          switched it off. This line is what allows the loop to finish.
        */
        i++;
    } // this closing brace is the end of the loop body

    /*
      ----------------------------------------------------------------
      STEP 3 - WHAT HAPPENS AFTERWARDS
      ----------------------------------------------------------------
      Getting here means the condition finally became false. i is still
      sitting in memory because we declared it above the loop, so we can
      show the value it reached - which is always one past the limit.
    */
    cout << "The loop has finished." << endl;
    cout << "i is now " << i << endl;

    /*
      ----------------------------------------------------------------
      TRACE TABLE - follow the loop with a pen on paper
      ----------------------------------------------------------------
      +-----------+------------+----------------+-----------+
      | Iteration | i at start | Test: i <= 5   | Output    |
      +-----------+------------+----------------+-----------+
      | 1         | 1          | 1 <= 5   TRUE  | 1         |
      +-----------+------------+----------------+-----------+
      | 2         | 2          | 2 <= 5   TRUE  | 2         |
      +-----------+------------+----------------+-----------+
      | 3         | 3          | 3 <= 5   TRUE  | 3         |
      +-----------+------------+----------------+-----------+
      | 4         | 4          | 4 <= 5   TRUE  | 4         |
      +-----------+------------+----------------+-----------+
      | 5         | 5          | 5 <= 5   TRUE  | 5         |
      +-----------+------------+----------------+-----------+
      | 6         | 6          | 6 <= 5   FALSE | (nothing) |
      +-----------+------------+----------------+-----------+

      Row 6 is where the loop dies. The body ran 5 times, not 6, because a
      failing test prints nothing. The final value of i is one MORE than the
      limit - a fact worth checking every single time you trace a while loop.

      THE 10-SECOND ITERATION COUNT
        Going UP:   (last - first) / step + 1  ->  (5 - 1) / 1 + 1 = 5
        Going DOWN: (first - last) / step + 1  ->  (5 - 1) / 1 + 1 = 5
      The "+ 1" is easy to forget: you count the starting value as well.

      THE COMMON TRAP IN THIS FILE
        Forgetting `i++;` inside the body. The test then never changes, so
        the loop spins for ever and the screen fills with 1. Every loop
        needs something inside it that moves the tested value toward the
        point where the condition fails.
        The second trap is writing `i < 5` instead of `i <= 5`: that prints
        1, 2, 3, 4 and stops, four passes instead of five. Read the symbol
        aloud as English - "less than 5" means 5 is not allowed in.
    */

    return 0;
    /*
      `return 0;` ends main immediately and hands the value 0 back to the
      operating system. Zero conventionally means "success" - the program
      did what it was asked to. The exact number hardly matters on a modern
      system, but every exam answer expects to see it, so always write it.
    */
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: How many times does the body run, and why?  -> 5 times, because i is tested before the body and 6 <= 5 fails
  Q2: What is the value of i the last time the condition is tested?  -> 6
  Q3: What happens if `i++;` is deleted?  -> infinite loop, i never changes so i <= 5 stays true forever
  Q4: Rewrite `i <= 5` using `<` only - what changes?  -> 4 iterations, prints 1 2 3 4, because `<` excludes 5
  Q5: Can i still be used after the closing brace, and if so why?  -> yes, because it was declared above the loop rather than inside the header
*/
