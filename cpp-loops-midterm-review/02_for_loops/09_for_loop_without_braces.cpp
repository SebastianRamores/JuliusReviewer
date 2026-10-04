/*
  ============================================================
  PROGRAM: For Loops Without Braces - the One Rule About { }
  TOPIC: for loops - when the braces around the body are optional
  DIFFICULTY: Beginner  (READ THIS ONE TWICE)
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - The ONE rule that decides whether braces are needed around a loop body.
  - A legal for loop whose body is a single statement with no braces.
  - What really happens when two statements are written with no braces.
  - Why `if` obeys exactly the same rule.
  - The compile errors you get from genuinely broken loop headers.

  EXPECTED OUTPUT:
  1) ONE statement, no braces  -> legal:
  1 2 3 4 5 | body ran 5 times
  2) SAME loop with braces     -> identical output:
  1 2 3 4 5 | body ran 5 times
  3) TWO statements, no braces -> BUG: only the first statement repeats:
  1 2 3 4 5 <extra printed once only>
  4) FIX: wrap both statements in braces:
  1 <extra printed 5 times>
  2 <extra printed 5 times>
  3 <extra printed 5 times>
  4 <extra printed 5 times>
  5 <extra printed 5 times>
  5) The body of the for is the WHOLE if statement, so all 5 were tested:
  3 tested
  4 tested
  5 tested
  6) The same rule applies to if without braces:
  135|

  IMPORTANT SYNTAX:
  for (int i = 1; i <= 5; i++) cout << i << " ";
      -> legal ONLY because the body is exactly ONE statement
  for (int i = 1; i <= 5; i++) { stmt1; stmt2; }
      -> braces MANDATORY as soon as there are two statements
  `;` -> a statement ENDS at its semicolon, regardless of indentation

  STEP-BY-STEP EXPLANATION:
  1. A loop body is made of STATEMENTS. A statement ends at its semicolon.
  2. So `for (...) A;` repeats A. That is legal and it is what part 1 does.
  3. But `for (...) A; B;` is TWO separate statements that merely sit next
     to each other. The loop repeats A only; B runs once, afterwards. This
     is the bug in part 3, and it compiles - which is what makes it so
     dangerous.
  4. The fix is to wrap both in { } so they form one BLOCK, and a block is
     a single statement as far as the loop is concerned.
  5. The same rule governs `if`, `while` and `else`. Every rule about loop
     braces you will ever be asked is this one rule.

  THE ONE RULE
    Braces are OPTIONAL when the body is exactly ONE statement.
    Braces are REQUIRED as soon as the body has TWO or more statements.
    ALWAYS use braces anyway. They cost nothing and they make the code
    readable, and every professional style guide demands them.
  ============================================================
*/

#include <iostream>
/*
  The only header this project needs. It provides `cout` for output and
  `endl` for a newline. C++ has no built-in printing, so this line must be
  present before any use of `cout`.
*/

using namespace std;
/*
  The standard tools are grouped in a namespace called `std`, and the `::`
  operator means "inside", so `std::cout` reads "the cout inside std".
  `using namespace std;` saves us typing `std::` before every name, which
  is why plain `cout` works throughout this file.
*/

int main() {
/*
  `main` is the ENTRY POINT: the first function the operating system runs.
  `int` is the return type - a whole number handed back on exit. `()` means
  no parameters. `{ }` delimits the BODY of the function.
*/

    /*
      ============================================================
      PART 1 - A LOOP WHOSE BODY IS ONE STATEMENT AND HAS NO BRACES
      ============================================================
    */
    cout << "1) ONE statement, no braces  -> legal:" << endl;
    // Label on its own line, so the result below is easy to find.

    for (int i = 1; i <= 5; i++) cout << i << " ";
    /*
      |       |        |  |   |  |  |
      |       |        |  |   |  |  +-- the ONE statement that is the
      |       |        |  |   |  |      body; it repeats five times
      |       |        |  |   |  +----- ) closes the header
      |       |        |  |   +-------- UPDATE
      |       |        |  +------------ CONDITION
      |       |        +--------------- START
      |       +------------------------ the `for` keyword
      +-------------------------------- this line ENDS the statement

      READ THE LAST CHARACTER OF THE LINE: the `;`.
      C++ does not care about indentation, line breaks, or how far the code
      is indented. A statement finishes at its semicolon, and everything
      between the closing `)` and that `;` is the loop's single statement.
      So this line repeats `cout << i << " ";` and nothing else.
    */

    cout << "| body ran 5 times" << endl;
    /*
      This statement is OUTSIDE the loop, so it runs exactly once, after
      the loop has finished. The pipe character makes the end of the
      repeated line easy to see, and shows where the five numbers stop.
    */

    /*
      ============================================================
      PART 2 - THE SAME LOOP WITH BRACES
      ============================================================
    */
    cout << "2) SAME loop with braces     -> identical output:" << endl;
    // A second label, to prove the two versions agree exactly.

    for (int i = 1; i <= 5; i++) {
        /*
          Everything between the braces is the body, and a BLOCK is always
          treated as a single statement - even when it holds many. That
          is why braces make the two-or-more-statement case legal.
        */
        cout << i << " ";
        // The same one statement as in part 1, now safely inside the block.
    }
    cout << "| body ran 5 times" << endl;
    /*
      Identical to part 1, character for character. Braces changed the
      style, not the behaviour, because there was only one statement
      either way.
    */

    /*
      ============================================================
      PART 3 - THE BUG: TWO STATEMENTS WITH NO BRACES
      ============================================================
      *** THIS IS THE MOST IMPORTANT SECTION IN THE FILE. ***

      A CORRECTION TO A COMMON BELIEF: many books and websites say that
      two statements without braces "will not compile". That is wrong, and
      believing it is dangerous. The code below DOES compile, the compiler
      prints no warning at all, and the program runs. The damage is
      SILENT - it shows up only as the wrong output, which is why it costs
      marks in an exam and hours in real programming.
    */

    cout << "3) TWO statements, no braces -> BUG: only the first statement repeats:" << endl;
    // The label announces the bug before the reader sees it happen.

    for (int i = 1; i <= 5; i++) cout << i << " ";
    //                          ^^^^^^^^^^^^^^^^^^^^^ this is the body
    cout << "<extra printed once only>" << endl;
    /*
      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ this is NOT

      Think of it as two sentences:
          Sentence 1:  for (...) cout << i << " ";
          Sentence 2:  cout << "<extra printed once only>" << endl;
      Sentence 2 is not indented under the loop, not joined to it by
      anything, and not part of its body. It simply follows it. So the loop
      prints 1 2 3 4 5 and stops, and then sentence 2 runs a single time.

      THE COMPILER IS RIGHT TO ACCEPT IT. Each statement on its own is
      perfectly legal; the programmer simply meant something different.
      A compiler checks grammar, not intentions.

      IF YOU REALLY WANT TWO STATEMENTS TO REPEAT, YOU MUST USE BRACES:

          for (int i = 1; i <= 5; i++)
              cout << i << " ";
              cout << "x" << endl;      // this one would run only once

      Because the semicolon after `" "` ends the first statement, the
      second statement sits outside the loop.
    */

    /*
      ============================================================
      PART 4 - THE FIX: BRACES AROUND BOTH STATEMENTS
      ============================================================
    */
    cout << "4) FIX: wrap both statements in braces:" << endl;
    // Now the real working version is shown, so the correction is not
    // merely asserted.

    for (int i = 1; i <= 5; i++) {
        cout << i << " ";
        cout << "<extra printed 5 times>" << endl;
        /*
          BOTH statements are inside the { }, so BOTH repeat. Compare the
          output above: this marker appears five times instead of once.
          That difference is the entire practical lesson of this file.
        */
    }

    /*
      ============================================================
      PART 5 - A `for` WITH NO BRACES WHOSE BODY IS AN `if`
      ============================================================
    */
    cout << "5) The body of the for is the WHOLE if statement, so all 5 were tested:" << endl;
    // This is the case students most often get wrong, so it is spelled out.

    for (int i = 1; i <= 5; i++)
        if (i > 2)
            cout << i << " tested" << endl;
    /*
      |                |  |
      |                |  +---- the ONE statement that is the for's body
      |                +------- an if, which is a statement in its own
      |                        right, so it counts as ONE
      +------------------------ UPDATE, so the if is part of the loop

      HOW MANY STATEMENTS IS THE BODY?  Exactly one: the `if`.
      `if (i > 2) cout << ... ;` is itself a complete statement, made of a
      condition and a single statement inside it. Nesting it inside the for
      changes nothing about how many statements the for body has.

      So the loop DOES run five times, and the if is TESTED on all five
      values. It prints only for 3, 4 and 5 because the test `i > 2` fails
      for 1 and 2 - and a failed if simply skips its own body, which is
      NOT the same thing as leaving the loop.

      Note there are THREE nested levels here: the for, the if, and the
      cout. Indentation is only a reading aid, but in this case it is also
      the only thing that tells a human which statement belongs where.
    */

    /*
      ============================================================
      PART 6 - THE SAME RULE APPLIES TO `if`
      ============================================================
    */
    cout << "6) The same rule applies to if without braces:" << endl;
    // Final confirmation that this is a general C++ rule, not a for-loop
    // quirk.

    for (int i = 1; i <= 5; i++)
        if (i % 2 == 1)
            cout << i;
    /*
      |               |   |  |
      |               |   |  +-- ONE statement, so the if needs no braces
      |               |   +----- `%` is modulo: the remainder after
      |               |         dividing. Odd numbers leave remainder 1.
      |               +--------- ONE statement (the if), so the for needs
      |                         no braces either
      +------------------------- UPDATE

      `i % 2 == 1` is true only for odd numbers, so 1, 3 and 5 are printed
      with no spaces between them. The `cout << "|"` after the loop proves
      the loop stopped after printing 5 and not one character more.
    */

    cout << "|" << endl;
    // Runs once, after the loop. The pipe marks exactly where the loop's
    // output ended.

    /*
      ============================================================
      PART 7 - MISTAKES THAT REALLY DO STOP THE COMPILER
      ============================================================
      Unlike the mistake in part 3, the following are genuine syntax
      errors. They are left as comments so this program still compiles and
      runs, but each one shows the message the compiler produces.
    */

    /*
      (a) A MISSING SEMICOLON IN THE HEADER.

          for (int i = 1; i <= 5 i++) {
              cout << i << endl;
          }
          error: expected ';' before ')' token

      The header needs TWO semicolons: one after the start, one after the
      condition. Without the second, the compiler reads `5 i++` as a
      malformed expression and stops. This is the single most common
      typo in every loop ever written.
    */

    /*
      (b) A MISSING CLOSING BRACE.

          for (int i = 1; i <= 5; i++) {
              cout << i << endl;
          // the } that closes the loop is simply absent

          return 0;
          }
          error: expected '}' before 'return' token

      Every `{` needs a matching `}`. While the compiler is still looking
      for the brace that closes the loop, it treats `return 0;` as part of
      the loop body, so the error is reported against the return statement
      and can look very confusing. Count your braces.
    */

    /*
      (c) USING THE LOOP VARIABLE AFTER THE LOOP.

          for (int i = 1; i <= 5; i++) {
              cout << i << endl;
          }
          cout << i << endl;      // i no longer exists
          error: 'i' was not declared in this scope

      The braces are the reason: `i` was declared inside the loop, so its
      lifetime ended at the closing `}`. See 08_multiple_variables.cpp.
    */

    /*
      (d) A DANGLING ELSE, which braces prevent.

          if (i > 2)
              if (i > 10)
                  cout << "A" << endl;
              else
                  cout << "B" << endl;
          An else ALWAYS attaches to the NEAREST unmatched if. The reading
          above is therefore "if (i > 2) { if (i > 10) { A } else { B } }",
          which is probably NOT what the programmer intended. Writing the
          braces explicitly removes the ambiguity completely.
    */

    /*
      ------------------------------------------------------------
      TRACE TABLE
      ------------------------------------------------------------
      TRACE TABLE
      Comparing part 1 (one statement, no braces) with part 3 (two, no braces)
      +-----------+------------+-----------------+---------------------------+
      | Iteration | i at start | Statement 1     | Statement 2               |
      |           |            | cout << i << " ";| inside the loop?         |
      +-----------+------------+-----------------+---------------------------+
      |     1     |     1      | prints 1        | NO - it cannot be         |
      +-----------+------------+-----------------+---------------------------+
      |     2     |     2      | prints 2        |                           |
      +-----------+------------+-----------------+---------------------------+
      |     3     |     3      | prints 3        |                           |
      +-----------+------------+-----------------+---------------------------+
      |     4     |     4      | prints 4        |                           |
      +-----------+------------+-----------------+---------------------------+
      |     5     |     5      | prints 5        |                           |
      +-----------+------------+-----------------+---------------------------+
      |     6     |     6      | 6 <= 5 FALSE    |                           |
      +-----------+------------+-----------------+---------------------------+
      |  after    |     6      | loop finished   | runs ONCE, prints marker  |
      +-----------+------------+-----------------+---------------------------+

      Part 4, the fixed version, differs in exactly one cell: statement 2 is
      now inside the loop, so it repeats five times instead of once.

      THE 10-SECOND EXAM METHOD
        Count the statements, not the lines.
        1. Put a finger on the character just after the loop's `)`.
        2. Scan to the FIRST semicolon. Everything in between is the body.
        3. One statement before the first `;`? Braces are optional.
           Anything more? Braces are MANDATORY.
        Indentation, blank lines and comment blocks all count as NOTHING -
        the semicolon is the only thing that decides.

      THE COMMON TRAP IN THIS FILE
        Believing that two statements without braces fail to compile. They
        compile silently and print the wrong thing, which is far harder to
        spot. The habit that prevents it: always type the braces, then put
        the statements inside them. Never delete the braces to tidy up
        code. If you want a single-statement loop on one line for an exam,
        write it that way on purpose and never add a second statement.
    */

    return 0;
    // Leaves main and hands 0 (success) back to the operating system. Any
    // code after this line would never be reached.
}

/*
  ============================================================
  EXAM QUESTIONS
  ============================================================
  Q1: Is `for (int i = 1; i <= 5; i++) cout << i;` legal C++?        -> Yes, because the body is exactly ONE statement
  Q2: What decides where the body ends when there are no braces?       -> the first semicolon after the loop's closing parenthesis
  Q3: Do indentation or line breaks affect which statements a loop repeats? -> No, only the semicolons and the braces do; the compiler ignores layout
  Q4: In part 3, how many times does the second statement run?        -> exactly once, after the loop, which is the bug
  Q5: Does that two-statement no-brace version compile?                -> Yes, and with no warning; the compiler checks grammar, not intentions
  Q6: How do you make two statements both repeat?                     -> wrap them in { } so they form one block, and one block is one statement
  Q7: In part 5, how many statements form the body of the for?        -> one - the whole `if` statement counts as a single statement
  Q8: When are braces mandatory?                                       -> whenever the body contains two or more statements
  Q9: What is the practical advice for every loop you write?          -> always use the braces, even for one statement
  Q10: Name one compile error caused by a broken loop header.          -> a missing semicolon: error: expected ';' before ')' token
  ============================================================
*/
