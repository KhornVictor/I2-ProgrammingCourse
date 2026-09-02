/* ============================================================
   Data Structure & Programming I
   Topic 5: Loop  "for"

   What students learn here:
     1. Why we need a loop
     2. The three parts of a for loop
     3. Counting up, counting down, counting by steps
     4. Nested for loops (drawing a triangle of stars)
     5. break and continue
     6. Classic exercises: sum, factorial, prime number

   Syntax:
        for ( initialisation ; condition ; update ) {
            block of instructions
        }

     1) initialisation runs ONCE, before the loop
     2) condition is tested BEFORE each turn; false -> loop stops
     3) update runs at the END of each turn

   Compile:  gcc L5-ForLoop.c -o L5
   ============================================================ */

#include <stdio.h>

int main()
{
    int i, j, k, n;

    /* ============================================================
       1. WHY A LOOP?
          Without a loop we would copy the same 2 lines 100 times.
          With a loop we write them once.
       ============================================================ */

    printf("=== 1. Counting up: 1 to 10 ===\n");
    for (i = 1; i <= 10; i++) {     /* i++ is a short way to write i = i + 1 */
        printf("%d ", i);
    }
    printf("\n");

    /* ============================================================
       2. COUNTING DOWN and COUNTING BY STEPS
       ============================================================ */

    printf("\n=== 2. Counting down and by steps ===\n");

    printf("25 down to 5 by -5 : ");
    for (i = 25; i > 0; i = i - 5)
        printf("%d ", i);
    printf("\n");

    printf("1 to 7 by +2       : ");
    for (i = 1; i <= 7; i = i + 2)
        printf("%d ", i);
    printf("\n");

    /* A TRAP: this loop never runs, because 7 > 7 is false at once. */
    printf("for(i=7; i>7; i+=2): ");
    for (i = 7; i > 7; i = i + 2)
        printf("%d ", i);
    printf("(nothing - the condition is false from the start)\n");

    /* Another TRAP: for(i=25; i>0; i++) is an INFINITE loop,
       because i only grows and never becomes <= 0.
       Always check that the update moves TOWARDS the stop condition. */

    /* ============================================================
       3. NESTED LOOPS
          The inner loop finishes completely for EACH turn
          of the outer loop.
       ============================================================ */

    printf("\n=== 3. Nested loops ===\n");

    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 4; j++)
            printf("AB");
        printf(" ");
    }
    printf("\n");

    printf("\nA triangle of stars (n = 4):\n");
    n = 4;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n - i; j++)     /* the spaces on the left */
            printf(" ");
        for (k = 1; k <= 2 * i - 1; k++) /* the stars */
            printf("*");
        printf("\n");
    }

    /* ============================================================
       4. BREAK and CONTINUE
            break    -> leave the loop immediately
            continue -> skip the rest of THIS turn, go to the next
       ============================================================ */

    printf("\n=== 4. break and continue ===\n");

    printf("1..9 but skip 4 (continue): ");
    for (i = 1; i <= 9; i++) {
        if (i == 4)
            continue;          /* jump to the next value of i */
        printf("%d ", i);
    }
    printf("\n");

    printf("1..10, skip 3, stop at 8 : ");
    for (i = 1; i <= 10; i++) {
        if (i == 3) continue;
        if (i == 8) break;     /* leave the loop for good */
        printf("%d ", i);
    }
    printf("\n");

    /* ============================================================
       5. EXERCISE: sum of 1 to 99
       ============================================================ */

    printf("\n=== 5. Exercise: sum from 1 to 99 ===\n");

    int sum = 0;
    for (i = 1; i <= 99; i++)
        sum = sum + i;
    printf("1 + 2 + ... + 99 = %d\n", sum);

    /* ============================================================
       6. EXERCISE: factorial of n   (n! = 1*2*3*...*n)
       ============================================================ */

    printf("\n=== 6. Exercise: factorial ===\n");

    long fact = 1;
    printf("Enter a positive number n: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
        fact = fact * i;
    printf("%d! = %ld\n", n, fact);

    /* ============================================================
       7. EXERCISE: is the number prime?
          A prime number has exactly two divisors: 1 and itself.
          So we try every divider from 2 to n/2.
          As soon as we find one, we can STOP (break).
       ============================================================ */

    printf("\n=== 7. Exercise: prime number ===\n");

    int isPrime = 1;           /* we suppose "yes" until proven wrong */

    printf("Enter a number to test: ");
    scanf("%d", &n);

    if (n < 2) {
        isPrime = 0;           /* 0 and 1 are not prime */
    } else {
        for (i = 2; i <= n / 2; i++) {
            if (n % i == 0) {  /* i divides n -> not prime */
                isPrime = 0;
                break;
            }
        }
    }

    if (isPrime)
        printf("%d is a prime number.\n", n);
    else
        printf("%d is NOT a prime number.\n", n);

    /* ============================================================
       8. EXERCISE: all prime numbers between 2 and 100
       ============================================================ */

    printf("\n=== 8. Prime numbers between 2 and 100 ===\n");

    for (n = 2; n <= 100; n++) {
        isPrime = 1;
        for (i = 2; i <= n / 2; i++) {
            if (n % i == 0) { isPrime = 0; break; }
        }
        if (isPrime)
            printf("%d ", n);
    }
    printf("\n");

    /* ============================================================
       9. EXERCISE: read 5 numbers, find the maximum
       ============================================================ */

    printf("\n=== 9. Maximum of 5 input numbers ===\n");

    int value, max;
    for (i = 1; i <= 5; i++) {
        printf("Input number #%d: ", i);
        scanf("%d", &value);
        if (i == 1 || value > max)   /* the first one is the max so far */
            max = value;
    }
    printf("The max number is: %d\n", max);

    return 0;
}

/* ============================================================
   PRACTICE

   1. Display all numbers from 99 down to 1.
   2. Display 1 to 100 except the number 50.
   3. Display the odd numbers from 8 to 1000, except 11, 17 and 21.
   4. Display the numbers divisible by 3 between 1 and 100,
      except 30, 60 and 90.
   5. Compute 1^3 + 2^3 + ... + n^3 for an input n.
   6. Display the first n numbers of the Fibonacci sequence
      0 1 1 2 3 5 8 13 21 34 ...
   7. Draw this shape for an input n:
         *
         **
         ***
         ****
   ============================================================ */
