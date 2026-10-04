/*
  ============================================================
  PROGRAM: Hello, Loop!
  TOPIC: Loops - fundamentals / first program with a loop
  DIFFICULTY: Beginner
  ============================================================

  WHAT THIS PROGRAM TEACHES:
  - What a "loop" is in plain English: repeating something.
  - The 4 parts every C++ program needs: include, namespace, main, return.
  - How a `for` loop repeats a block of code.
  - How the loop variable changes from one repetition to the next.

  EXPECTED OUTPUT:
    Hello!
    Hello!
    Hello!
    Hello!
    Hello!

  IMPORTANT SYNTAX:
    for (int i = 1; i <= 5; i++) { ... }
    cout << "text" << endl;

  STEP-BY-STEP EXPLANATION:
    1) The `for` loop starts with i = 1.
    2) It checks "is i <= 5?"
    3) If yes, it runs the body: print "Hello!".
    4) It adds 1 to i.
    5) It goes back to step 2 and repeats.
    6) When i becomes 6, the condition is false and the loop stops.
    So the body runs 5 times: i = 1, 2, 3, 4, 5.
  ============================================================
*/

#include <iostream>
/*
  WHAT IS THIS LINE?
    #include <iostream> tells the compiler: "I need the standard input/output
    tools." It literally means "include the standard header file called iostream".

  WHAT DOES IT GIVE US?
    Two objects (named tools) that every beginner C++ program needs:
      - cout  = "console output"  -> prints text to the screen
      - cin   = "console input"   -> reads typed input from the keyboard
    It also gives us the stream operators << and >>.

  WHY IS IT NEEDED?
    Without this line, `cout` and `cin` would be unknown words and the compiler
    would report an error like: "'cout' was not declared in this scope".

  NOTE: <iostream> uses angle brackets < >, NOT quotes " ".
    Quotes are used for your own text files, e.g. #include "myheader.h".
    There is no semicolon after #include lines.
*/

using namespace std;
/*
  WHAT IS A NAMESPACE?
    A namespace is just a "grouping" of names. All the standard C++ tools
    (cout, cin, endl, string, ...) live inside a namespace called `std`,
    which is short for "standard".

  WHY DOES `std` EXIST?
    So that the huge collection of standard names cannot clash with names you
    create yourself. It keeps the library tidy and prevents collisions.

  WHAT DOES THIS LINE CHANGE?
    Without it you must write the full name every time:
        std::cout << "Hello" << std::endl;
    With it you can drop the `std::` prefix:
        cout << "Hello" << endl;

  WHAT IS `::`?
    It is called the "scope resolution operator". It means "look inside this
    namespace for this name". So `std::cout` = "the cout inside namespace std".

  EXAM NOTE: always write `using namespace std;` after the #include line(s)
    and before main().
*/

int main() {
/*
  WHAT IS main()?
    main() is the function where program execution STARTS. When you run the
    program, the computer begins at the first line inside main().

  WHY THE `int`?
    `int` is the RETURN TYPE. It means: "when main() finishes, it will hand
    back a whole number to the operating system." That number is an exit code.
    Returning 0 means "everything finished normally / no errors".

  WHY THE EMPTY parentheses `()`?
    A function can take inputs (parameters). main() takes none, so the list
    is empty. The `()` is still required.

  WHY THE CURLY BRACES { }?
    { } is the function BODY: the actual block of instructions. Everything
    between the braces belongs to main. This is true for functions AND loops.

  IS main() SPECIAL?
    Yes. You never CALL main yourself - the operating system calls it for you.
    But you DO have to write it, with exactly this lowercase spelling.
*/

    /*
      ------------------------------------------------------------
      THE LOOP
      ------------------------------------------------------------
    */
    for (int i = 1; i <= 5; i++) {
    /*
       ^^^ the `for` keyword starts a for loop.
           It repeats the block of code in its braces.

           ( ... ) is the loop HEADER. It holds exactly three parts,
           separated by SEMICOLONS, in this order:

           PART 1 - INITIALIZATION:   int i = 1
               Creates a NEW variable named i.
               `int` = data type (whole number, no decimal point).
               `i`   = the name we choose for the variable.
               `=`   = assignment operator: "put the value on the right into
                        the variable on the left". It does NOT mean "equals".
               `1`   = the starting value.
               This part runs EXACTLY ONCE, before the loop starts.

           PART 2 - CONDITION:        i <= 5
               This is a yes/no question checked BEFORE every repetition.
               `<=` means "less than or equal to".
               It reads as English: "is i less than or equal to 5?"
               If the answer is TRUE  -> run the body once.
               If the answer is FALSE -> skip the body and leave the loop.

           PART 3 - UPDATE:            i++
               `i++` is shorthand for "add 1 to i".
               (Full form: i = i + 1;  or  i += 1;)
               This runs AFTER the body has finished, once per repetition.

           {} is the loop BODY - the work that gets repeated.
    */

        cout << "Hello!" << endl;
        /*
          `cout` sends text to the screen (console output).
          `<<` is the stream insertion operator. It means "send / push this
          into the output stream". You chain them: "send THIS, then THIS".
          "Hello!" is a STRING LITERAL - text between double quotes.
            Text in quotes is printed exactly as typed, spaces included.
          `endl` (end line) prints a newline and flushes the buffer.
            It moves the cursor to the start of the next line, so the next
            cout starts on a fresh line.

          This single line runs 5 times, once per iteration of the loop.
        */
    }

    /*
      ------------------------------------------------------------
      LET'S TRACE IT (this is the exam skill: manual tracing)
      ------------------------------------------------------------
        Start:        i = 1
        Check i<=5?   1<=5  true   -> print "Hello!"   -> i becomes 2
        Check i<=5?   2<=5  true   -> print "Hello!"   -> i becomes 3
        Check i<=5?   3<=5  true   -> print "Hello!"   -> i becomes 4
        Check i<=5?   4<=5  true   -> print "Hello!"   -> i becomes 5
        Check i<=5?   5<=5  true   -> print "Hello!"   -> i becomes 6
        Check i<=5?   6<=5  FALSE  -> stop.

        Total body executions (ITERATIONS) = 5.
    */

    return 0;
    /*
      Ends the main() function and sends the value 0 back to the operating
      system. 0 is the universal "success / no error" code.
      The `return` keyword ends a function immediately - nothing after it runs.
      Reaching the end of main would also work, but `return 0;` is the habit
      exam markers expect to see.
    */
}

/*
  ============================================================
  EXAM QUESTIONS THIS FILE PREPARES YOU FOR
  ============================================================
  Q1: How many times does the loop body run?          -> 5
  Q2: What is the value of i when the loop ends?     -> 6
  Q3: What if the condition were i < 5 instead?      -> body runs 4 times
  Q4: What if the update were i += 2?                -> i = 1,3,5 -> 3 times
  Q5: What if the update were i--?                   -> INFINITE LOOP (see 12_common_mistakes)
  ============================================================
*/
