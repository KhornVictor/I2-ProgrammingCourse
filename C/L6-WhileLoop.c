/* ============================================================
   Data Structure & Programming I
   Topic 6: Loop  "while"

   What students learn here:
     1. The while syntax and how it is executed
     2. for  vs.  while : the same loop written twice
     3. The infinite loop and how to avoid it
     4. Loops whose number of turns is NOT known in advance
        (read until the user types 0)
     5. Digit by digit: count / sum / multiply the digits
     6. The "guess my number" game

   Syntax:
        while ( condition ) {
            block of instructions
        }

     The condition is tested FIRST.
     If it is false at the very beginning, the block never runs.

   Compile:  gcc L6-WhileLoop.c -o L6
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>   /* rand, srand */
#include <time.h>     /* time        */

int main()
{
    int n;

    /* ============================================================
       1. FIRST EXAMPLES
       ============================================================ */

    printf("=== 1. First examples ===\n");

    n = 10;
    printf("n=10, while(n>0) print n then n=n-2 : ");
    while (n > 0) {
        printf("%d ", n);
        n = n - 2;
    }
    printf("\n");                 /* 10 8 6 4 2 */

    n = 10;
    printf("n=10, while(n-1>2) print n+1, n=n-2 : ");
    while (n - 1 > 2) {
        printf("%d ", n + 1);
        n = n - 2;
    }
    printf("\n");                 /* 11 9 7 5 */

    /* ============================================================
       2. THE SAME LOOP: for  vs.  while
          A "for" is just a "while" with its 3 parts written
          on one line. Use "for" when you know how many turns.
       ============================================================ */

    printf("\n=== 2. for and while side by side ===\n");

    int i;
    printf("for  : ");
    for (i = 1; i <= 5; i++)
        printf("%d ", i);
    printf("\n");

    printf("while: ");
    i = 1;                        /* initialisation */
    while (i <= 5) {              /* condition      */
        printf("%d ", i);
        i++;                      /* update         */
    }
    printf("\n");

    /* ============================================================
       3. THE INFINITE LOOP
          If nothing inside the block changes the condition,
          the loop never stops.

              n = 10;
              while (n > 0) {
                  printf("%d ", n);     <-- n never changes
              }                          -> 10 10 10 10 ... forever

          RULE: every while loop must contain an instruction
                that brings the condition closer to "false".
       ============================================================ */

    /* ============================================================
       4. WHEN WE DO NOT KNOW THE NUMBER OF TURNS
          "for" is not convenient here, "while" is perfect:
          keep reading numbers until the user types 0.
       ============================================================ */

    printf("\n=== 3. Sum numbers until the user types 0 ===\n");

    int value, sum = 0, count = 0;

    printf("Enter a number (0 to stop): ");
    scanf("%d", &value);

    while (value != 0) {
        sum = sum + value;
        count++;
        printf("Enter a number (0 to stop): ");
        scanf("%d", &value);
    }

    printf("You entered %d number(s). Their total is %d\n", count, sum);
    if (count > 0)
        printf("Their average is %.2f\n", (float)sum / count);

    /* ============================================================
       5. WORKING DIGIT BY DIGIT
          n % 10  -> the LAST digit
          n / 10  -> removes the last digit
          Repeat until n becomes 0.

          Example with 1234:
              1234 % 10 = 4   1234 / 10 = 123
               123 % 10 = 3    123 / 10 = 12
                12 % 10 = 2     12 / 10 = 1
                 1 % 10 = 1      1 / 10 = 0  -> stop
       ============================================================ */

    printf("\n=== 4. Count, sum and multiply the digits ===\n");

    int number, digits = 0, digitSum = 0;
    long digitProduct = 1;

    printf("Enter a positive number: ");
    scanf("%d", &number);

    n = number;
    if (n == 0) digits = 1;            /* the number 0 has 1 digit */

    while (n > 0) {
        int d = n % 10;                /* take the last digit  */
        digits++;
        digitSum = digitSum + d;
        digitProduct = digitProduct * d;
        n = n / 10;                    /* drop the last digit  */
    }

    printf("%d has %d digit(s)\n", number, digits);
    printf("Sum of its digits      = %d\n", digitSum);
    printf("Product of its digits  = %ld\n", digitProduct);

    /* ============================================================
       6. REVERSE A NUMBER (same technique)
       ============================================================ */

    printf("\n=== 5. Reverse a number ===\n");

    int reversed = 0;
    n = number;
    while (n > 0) {
        reversed = reversed * 10 + (n % 10);
        n = n / 10;
    }
    printf("%d reversed is %d\n", number, reversed);

    /* ============================================================
       7. THE GAME: guess the number
          The computer chooses a random number between 1 and 100.
          The user keeps guessing until it is correct.
          We do not know how many turns -> while is the right tool.
       ============================================================ */

    printf("\n=== 6. Guess my number (1..100) ===\n");

    srand(time(NULL));             /* start the random generator ONCE */
    int secret = rand() % 100 + 1; /* rand() % 100 gives 0..99, +1 -> 1..100 */
    int guess = -1;
    int attempts = 0;

    while (guess != secret) {
        printf("Your guess: ");
        scanf("%d", &guess);
        attempts++;

        if (guess > secret)
            printf("  Too big! Try a smaller number.\n");
        else if (guess < secret)
            printf("  Too small! Try a bigger number.\n");
    }

    printf("Congratulations! You guessed only %d time(s) to be correct.\n",
           attempts);

    return 0;
}

/* ============================================================
   PRACTICE (use while for all of them)

   1. Display all numbers from 99 to 1.
   2. Display 1 to 100 except 50.
   3. Sum all numbers from 1 to 100.
   4. Multiply all numbers from 1 to 10.
   5. Check whether an input number is prime. Then ask again,
      again and again, until the user enters a negative number.
   6. Display all prime numbers between 2 and 500.
   7. Read 20 numbers and display the maximum.
   8. Limit the guessing game to 3 attempts only.
   ============================================================ */
