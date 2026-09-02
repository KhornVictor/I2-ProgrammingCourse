/* ============================================================
   Data Structure & Programming I
   Topic 4: Condition (part 2) - Nested condition

   What students learn here:
     1. What a NESTED condition is (an if inside another if)
     2. Nested if  vs.  else-if chain: when to use which
     3. Full exercise: is a date valid? (with leap years)
     4. Full exercise: even/odd AND positive/negative together

   Compile:  gcc L4-Condition2.c -o L4
   ============================================================ */

#include <stdio.h>

int main()
{
    /* ============================================================
       1. NESTED CONDITION
          A condition placed INSIDE the block of another condition.
          Use it when the second question only makes sense
          if the first answer was already known.
       ============================================================ */

    printf("=== 1. Nested condition ===\n");

    int x;
    printf("Enter a number: ");
    scanf("%d", &x);

    /* --- version A: NESTED --- */
    if (x < 0) {                          /* condition 1 */
        printf("[A] It is a negative number.\n");
    } else {                              /* condition 2 */
        if (x == 0) {                     /*   sub-condition 2.1 */
            printf("[A] It is zero.\n");
        } else {                          /*   sub-condition 2.2 */
            printf("[A] It is a positive number.\n");
        }
    }

    /* --- version B: else-if chain (shorter, same result) --- */
    if (x < 0) {
        printf("[B] It is a negative number.\n");
    } else if (x == 0) {
        printf("[B] It is zero.\n");
    } else {
        printf("[B] It is a positive number.\n");
    }

    printf("Quitting this part ...\n");

    /* ============================================================
       2. WHEN DO WE REALLY NEED NESTING?
          When the inner test depends on the outer one.
          Example: only a positive number can be checked for
          "even or odd" in our little report below.
       ============================================================ */

    printf("\n=== 2. Sign AND parity together ===\n");

    if (x > 0) {
        printf("%d is positive and ", x);
        if (x % 2 == 0)
            printf("even.\n");
        else
            printf("odd.\n");
    } else if (x < 0) {
        printf("%d is negative and ", x);
        if (x % 2 == 0)
            printf("even.\n");
        else
            printf("odd.\n");
    } else {
        printf("0 is neither positive nor negative (and it is even).\n");
    }

    /* ============================================================
       3. BIG EXERCISE: is the input date valid?

          Rules:
            - year  must be >= 0
            - month must be between 1 and 12
            - day depends on the month:
                months 1,3,5,7,8,10,12 -> 31 days
                months 4,6,9,11        -> 30 days
                month  2               -> 29 days if leap year
                                          28 days otherwise
            - leap year: divisible by 4 AND (not by 100 OR by 400)
       ============================================================ */

    printf("\n=== 3. Exercise: valid date ===\n");

    int y, m, d;
    int valid = 0;          /* 0 = false, 1 = true */

    printf("Input a date (yyyy mm dd): ");
    scanf("%d %d %d", &y, &m, &d);

    if (y < 0) {
        valid = 0;                                  /* bad year */
    } else if (m < 1 || m > 12) {
        valid = 0;                                  /* bad month */
    } else if (d < 1) {
        valid = 0;                                  /* bad day */
    } else {
        /* the month is correct, now the day depends on the month */
        if (m == 1 || m == 3 || m == 5 || m == 7 ||
            m == 8 || m == 10 || m == 12) {
            valid = (d <= 31);
        } else if (m == 4 || m == 6 || m == 9 || m == 11) {
            valid = (d <= 30);
        } else {                                    /* m == 2 */
            int leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
            if (leap)
                valid = (d <= 29);
            else
                valid = (d <= 28);
        }
    }

    if (valid)
        printf("The input date %04d-%02d-%02d is valid.\n", y, m, d);
    else
        printf("The input date %04d-%02d-%02d is invalid.\n", y, m, d);

    /* Test these values in class:
         2023-10-30 -> valid          2023-02-30 -> invalid
         2023-12-28 -> valid          2004-02-29 -> valid (leap year)
         1900-02-29 -> invalid (1900 is divisible by 100, not by 400)
         2000-02-29 -> valid   (2000 is divisible by 400)             */

    /* ============================================================
       4. MENU with a SUB-MENU (nested switch)
          This is the assignment of Topic 4.
       ============================================================ */

    printf("\n=== 4. Menu with sub-menu ===\n");
    printf("1- Temperature conversion\n");
    printf("2- Area of a rectangle\n");
    printf("Your choice: ");

    int choice, sub;
    float t, w, h;

    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("  a) Celsius to Fahrenheit\n");
            printf("  b) Fahrenheit to Celsius\n");
            printf("  Type 1 for a, 2 for b: ");
            scanf("%d", &sub);

            printf("  Temperature: ");
            scanf("%f", &t);

            if (sub == 1)
                printf("  %.2f C = %.2f F\n", t, t * 9 / 5 + 32);
            else if (sub == 2)
                printf("  %.2f F = %.2f C\n", t, (t - 32) * 5 / 9);
            else
                printf("  Wrong sub-choice.\n");
            break;

        case 2:
            printf("  Width  = ");  scanf("%f", &w);
            printf("  Height = ");  scanf("%f", &h);
            printf("  Area = %.2f\n", w * h);

            /* nested test: a square is a special rectangle */
            if (w == h)
                printf("  This shape is a square.\n");
            else
                printf("  This shape is a rectangle.\n");
            break;

        default:
            printf("There is no such choice in the menu.\n");
    }

    return 0;
}

/* ============================================================
   PRACTICE

   1. Rewrite the "valid date" program using only nested if
      (no else-if chain). Compare the two versions: which one
      is easier to read?
   2. Add options 3 and 4 to the menu:
        3- area of a triangle from a, b, c (Heron formula)
        4- area of a circle from the radius
   3. A shop gives a discount:
        - if the client is a member  : 10%
            and if the bill > 100$   : 15% instead
        - if the client is not member: 0%
      Read "member (1/0)" and the bill, then print the final price.
   ============================================================ */
