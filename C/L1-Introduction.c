/* ============================================================
   Data Structure & Programming I
   Topic 1: Introduction to Algorithm and C Programming

   What students learn here:
     1. What the structure of a C program looks like
     2. #include, main(), { }, and the semicolon ;
     3. printf() to display text
     4. Escape characters \n and \t
     5. Turning a written algorithm into real C code

   How to compile and run (Code::Blocks or command prompt):
     gcc L1-Introduction.c -o L1
     L1
   ============================================================ */

#include <stdio.h>   /* stdio = STandard Input Output library.
                        We need it because printf() lives inside it. */

int main()           /* main() is where the program starts running. */
{
    /* ---------- Part 1: our very first program ---------- */
    printf("Hello World!\n");
    printf("Welcome to C Programming.\n");

    /* Every statement ends with a semicolon ;   <-- do not forget it! */

    /* ---------- Part 2: special characters ---------- */
    printf("\n--- Special characters ---\n");
    printf("\\n makes a new line.\n");
    printf("Name:\tSok\n");        /* \t = one TAB */
    printf("Name:\tDara\n");
    printf("To print a real backslash we write two of them: \\\n");

    /* ---------- Part 3: from algorithm to C code ----------

       ALGORITHM (what we write on paper, in plain words):

           Var n1, n2, result : Number
           Begin
               Get n1, n2 from user
               Do operation result = n1 + n2
               Display result
           End

       The SAME algorithm written in the C language:
    */

    printf("\n--- Algorithm example: add two numbers ---\n");

    int n1, n2, result;            /* Var n1, n2, result : Number */

    printf("Enter the first number : ");
    scanf("%d", &n1);              /* read(n1)  -- %d means "an integer" */

    printf("Enter the second number: ");
    scanf("%d", &n2);              /* read(n2) */

    result = n1 + n2;              /* result <- n1 + n2 */

    printf("The sum of %d and %d is %d\n", n1, n2, result);
    /*                ^^   ^^   ^^
       These are PLACEHOLDERS. They are replaced, in order,
       by the values of n1, n2 and result.

       Placeholders you must remember:
           %d  integer          %f  float (real number)
           %c  one character    %s  string (many characters)
    */

    /* ---------- Part 4: a small greeting program ----------
       Algorithm:
           Var name : Sequence of character
           Begin
               write("Input name: ")
               read(name)
               write("Hi, ", name, "! Welcome to our department!")
           End
    */

    printf("\n--- Greeting program ---\n");

    char name[30];                 /* a string = an array of characters */

    printf("Input name: ");
    scanf("%s", name);             /* NOTE: no & for a string */

    printf("Hi, %s! Welcome to our department!\n", name);

    return 0;                      /* 0 means "the program ended fine" */
}

/* ============================================================
   PRACTICE (write the algorithm first, then the C code)

   1. Ask the user for a year of birth and tell his/her age.
        Input year of birth: 2000
        You were born in 2000 and you are 25 years old.

   2. Ask for two numbers and display + - * / of them.

   3. Ask for a name and print a welcome box:
        ****************
        *  Hi, Sok!    *
        ****************
   ============================================================ */
