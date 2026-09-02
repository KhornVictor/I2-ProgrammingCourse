/* ============================================================
   Data Structure & Programming I
   Topic 10: Sub-program (Function)

   What students learn here:
     1. Why we cut a big program into small sub-programs
     2. FUNCTION  = returns a value       (int, float, char ...)
        PROCEDURE = returns nothing       (void)
     3. Prototype, definition, and call
     4. Parameters (inputs) and the return value (output)
     5. Local variable vs. global variable
     6. Passing an array to a function

   Syntax:
        returnType functionName ( type param1, type param2 ) {
            local variables
            instructions
            return value;
        }

   Compile:  gcc L10-Function.c -o L10
   ============================================================ */

#include <stdio.h>
#include <string.h>

/* ============================================================
   PROTOTYPES
   A prototype announces a function before main() so that the
   compiler already knows its name, its parameters and its
   return type. The parameter NAMES are optional here.
   ============================================================ */

int   max(int x, int y);
int   add(int a, int b);
float y_of_x(float x);
long  factorial(int n);
int   isPrime(int n);

void  greet(char name[]);
void  checkVote(int age);
void  drawLine(char c, int n);

float arrayAverage(int t[], int size);
void  fillArray(int t[], int size);

/* A GLOBAL variable: created outside every function.
   Every function can read and change it.
   Use them rarely - they make bugs hard to find.             */
int callCounter = 0;

/* ============================================================
   MAIN
   ============================================================ */

int main()
{
    /* -------- 1. Function WITH a return value -------- */

    printf("=== 1. Functions that return a value ===\n");

    int a1 = 5, a2 = 12;
    int biggest = max(a1, a2);          /* the result is stored */
    printf("max(%d, %d) = %d\n", a1, a2, biggest);

    printf("add(3, 5)   = %d\n", add(3, 5));   /* used directly  */
    printf("add(1, add(2,3)) = %d\n", add(1, add(2, 3)));
    /* A function can be used inside another function call.
       The inner one is computed first: add(2,3) -> 10,
       then add(1, 10) -> 22.  (our add returns (a+b)*2)        */

    /* -------- 2. Function WITHOUT a return value (void) -------- */

    printf("\n=== 2. Procedures (void) ===\n");

    drawLine('=', 30);
    greet("Dara");
    checkVote(15);
    checkVote(22);
    drawLine('=', 30);

    /* -------- 3. Reuse: the SAME function, many times -------- */

    printf("\n=== 3. Reuse ===\n");

    int b1 = 3,  b2 = 9;
    int c1 = 40, c2 = 20;
    printf("max of (%d,%d) = %d\n", a1, a2, max(a1, a2));
    printf("max of (%d,%d) = %d\n", b1, b2, max(b1, b2));
    printf("max of (%d,%d) = %d\n", c1, c2, max(c1, c2));
    printf("The function max() was called %d times so far.\n", callCounter);

    /* -------- 4. Formula y = 3x^2 - 2x -------- */

    printf("\n=== 4. y = 3x^2 - 2x ===\n");
    printf("x =  1 -> y = %.2f\n", y_of_x(1));
    printf("x =  5 -> y = %.2f\n", y_of_x(5));
    printf("x = 20 -> y = %.2f\n", y_of_x(20));

    /* -------- 5. Factorial and prime, now as functions -------- */

    printf("\n=== 5. factorial() and isPrime() ===\n");

    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    printf("%d! = %ld\n", n, factorial(n));

    if (isPrime(n))
        printf("%d is a prime number.\n", n);
    else
        printf("%d is NOT a prime number.\n", n);

    /* Look how SHORT main() is now. All the difficult work is
       hidden inside small functions that we can test one by one. */

    /* -------- 6. Passing an array to a function -------- */

    printf("\n=== 6. Arrays and functions ===\n");

    int marks[5];
    fillArray(marks, 5);
    printf("Average = %.2f\n", arrayAverage(marks, 5));

    return 0;
}

/* ============================================================
   DEFINITIONS  (the real code of each function)
   ============================================================ */

/* Returns the bigger of two integers. */
int max(int x, int y)
{
    int res;                 /* res is a LOCAL variable:
                                it exists only inside max(),
                                and it dies when max() finishes. */
    callCounter++;           /* callCounter is GLOBAL -> it survives */

    if (x > y)
        res = x;
    else
        res = y;

    return res;              /* send the answer back to the caller */
}

/* Returns the double of the sum. */
int add(int a, int b)
{
    return (a + b) * 2;
}

/* Computes y = 3x^2 - 2x. */
float y_of_x(float x)
{
    return 3 * x * x - 2 * x;
}

/* Computes n! = 1 * 2 * ... * n */
long factorial(int n)
{
    long result = 1;
    int i;
    for (i = 2; i <= n; i++)
        result = result * i;
    return result;           /* 0! and 1! both give 1 */
}

/* Returns 1 (true) if n is prime, 0 (false) otherwise. */
int isPrime(int n)
{
    int i;
    if (n < 2)
        return 0;            /* a function can return early */
    for (i = 2; i <= n / 2; i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

/* A PROCEDURE: it displays something, it returns nothing. */
void greet(char name[])
{
    printf("Hi, %s! Welcome back!\n", name);
}

/* Displays whether a person can vote. One parameter, no return. */
void checkVote(int age)
{
    if (age >= 18)
        printf("Age %d: You are allowed to vote.\n", age);
    else
        printf("Age %d: You are not allowed to vote.\n", age);
}

/* Draws a line of n times the character c. */
void drawLine(char c, int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%c", c);
    printf("\n");
}

/* Reads "size" numbers into the array t.
   NOTE: an array is NOT copied when passed to a function.
   The function works on the ORIGINAL array, so the values
   entered here are really kept in main().                    */
void fillArray(int t[], int size)
{
    int i;
    for (i = 0; i < size; i++) {
        printf("Input mark #%d: ", i + 1);
        scanf("%d", &t[i]);
    }
}

/* Returns the average of the "size" first elements of t. */
float arrayAverage(int t[], int size)
{
    int i, sum = 0;
    for (i = 0; i < size; i++)
        sum = sum + t[i];
    return (float)sum / size;
}

/* ============================================================
   PRACTICE

   1. Write a function surfaceTriangle(float b, float h) that
      returns the area of a triangle, and use it in main().
   2. Write a function celsiusToFahrenheit(float c).
   3. Write a procedure displayMenu() that prints the menu of
      Topic 4, and call it inside a do-while loop.
   4. Write a function countDigits(int n) that returns how many
      digits a number has.
   5. Write a function isLeapYear(int y) that returns 1 or 0,
      then use it in the "valid date" program of Topic 4.
   6. Write a function maxOfArray(int t[], int size).
   ============================================================ */
