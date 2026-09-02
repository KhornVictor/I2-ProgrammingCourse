/* ============================================================
   Data Structure & Programming I
   Topic 7: Loop  "do ... while"

   What students learn here:
     1. The do-while syntax (and its semicolon at the end!)
     2. The ONE real difference with while:
            while    -> test first,  then maybe run
            do while -> run first,   then test
        => a do-while block ALWAYS runs at least once
     3. The perfect use case: an input menu / input validation
     4. The same exercises, written with do-while

   Syntax:
        do {
            block of instructions
        } while ( condition );      <-- do not forget the ;

   Compile:  gcc L7-DoWhile.c -o L7
   ============================================================ */

#include <stdio.h>

int main()
{
    int n;

    /* ============================================================
       1. FIRST EXAMPLE
       ============================================================ */

    printf("=== 1. First example ===\n");

    n = 10;
    printf("n=10, do{print n; n=n-2}while(n>0) : ");
    do {
        printf("%d ", n);
        n = n - 2;
    } while (n > 0);
    printf("\n");                    /* 10 8 6 4 2 */

    /* ============================================================
       2. THE DIFFERENCE THAT MATTERS
          Both loops below have a condition that is FALSE
          from the very beginning.
       ============================================================ */

    printf("\n=== 2. while vs do-while when the condition is false ===\n");

    n = 100;
    printf("while(n<10)   : ");
    while (n < 10) {
        printf("%d ", n);
        n++;
    }
    printf("<- nothing was printed (0 turn)\n");

    n = 100;
    printf("do..while(n<10): ");
    do {
        printf("%d ", n);
        n++;
    } while (n < 10);
    printf("<- printed once (1 turn), THEN the test failed\n");

    /* ============================================================
       3. THE BEST USE CASE: ask again until the input is correct
          We must ask AT LEAST ONCE -> do while is natural here.
       ============================================================ */

    printf("\n=== 3. Input validation ===\n");

    int age;
    do {
        printf("Enter your age (1 to 120): ");
        scanf("%d", &age);

        if (age < 1 || age > 120)
            printf("  That is not a valid age, please try again.\n");

    } while (age < 1 || age > 120);

    printf("Thank you. Your age is %d.\n", age);

    /* ============================================================
       4. A MENU THAT REPEATS UNTIL THE USER QUITS
          This is the classic pattern of a real program.
       ============================================================ */

    printf("\n=== 4. A repeating menu ===\n");

    int choice;
    float a, b;

    do {
        printf("\n---------- MENU ----------\n");
        printf("1- Addition\n");
        printf("2- Subtraction\n");
        printf("3- Multiplication\n");
        printf("4- Division\n");
        printf("0- Quit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4) {
            printf("Enter two numbers: ");
            scanf("%f %f", &a, &b);
        }

        switch (choice) {
            case 1: printf("%.2f + %.2f = %.2f\n", a, b, a + b); break;
            case 2: printf("%.2f - %.2f = %.2f\n", a, b, a - b); break;
            case 3: printf("%.2f * %.2f = %.2f\n", a, b, a * b); break;
            case 4:
                if (b == 0)
                    printf("Error: cannot divide by zero.\n");
                else
                    printf("%.2f / %.2f = %.2f\n", a, b, a / b);
                break;
            case 0: printf("Bye!\n"); break;
            default: printf("There is no such choice.\n");
        }

    } while (choice != 0);

    /* ============================================================
       5. EXERCISE: prime numbers from 2 to n,
          and keep asking until the user enters a negative number.
          (assignment of Topic 7)
       ============================================================ */

    printf("\n=== 5. Prime numbers from 2 to n ===\n");

    int limit, num, i, isPrime;

    do {
        printf("\nEnter n (negative number to stop): ");
        scanf("%d", &limit);

        if (limit >= 2) {
            printf("Prime numbers from 2 to %d: ", limit);
            for (num = 2; num <= limit; num++) {
                isPrime = 1;
                for (i = 2; i <= num / 2; i++) {
                    if (num % i == 0) { isPrime = 0; break; }
                }
                if (isPrime) printf("%d ", num);
            }
            printf("\n");
        } else if (limit >= 0) {
            printf("There is no prime number below 2.\n");
        }

    } while (limit >= 0);

    printf("Program finished.\n");

    /* ============================================================
       6. SUMMARY TABLE

          for       : the number of turns is KNOWN
                      for (i = 0; i < 10; i++)

          while     : the number of turns is UNKNOWN, and the loop
                      may run ZERO time
                      while (!found) ...

          do while  : the number of turns is UNKNOWN, but the loop
                      must run AT LEAST ONE time
                      do { ask the user } while (input is wrong);
       ============================================================ */

    return 0;
}

/* ============================================================
   PRACTICE (use do-while for all of them)

   1. Display all numbers from 99 to 1.
   2. Sum all numbers from 1 to 100.
   3. Compute n^3 + (n-1)^3 + ... + 1^3 for an input n.
   4. Read 20 numbers and display the maximum one.
   5. Ask for a password until the user types "1234".
      Give the user only 3 attempts, then block the program.
   6. Rewrite the "guess my number" game of Topic 6 with do-while.
      Which version is cleaner? Why?
   ============================================================ */
