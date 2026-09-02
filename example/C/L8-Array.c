/* ============================================================
   Data Structure & Programming I
   Topic 8: Array

   What students learn here:
     1. The problem an array solves (100 variables -> 1 array)
     2. Declaring an array and initialising it
     3. The index: it starts at 0 and ends at size-1
     4. Filling and displaying an array with a for loop
     5. Sum, average, maximum, search, count
     6. Array of characters (string) and array of strings
     7. 2D array (a table / a matrix)

   Syntax:
        int   marks[5];          -> 5 integers
        char  animals[4][20];    -> 4 words of max 19 letters

   Compile:  gcc L8-Array.c -o L8
   ============================================================ */

#include <stdio.h>
#include <string.h>

#define SIZE 10        /* the size of an array must be a CONSTANT */

int main()
{
    int i, j;

    /* ============================================================
       1. THE PROBLEM
          To store the scores of 100 students without an array
          we would need 100 variables: score1, score2, ... score100.
          Impossible to manage. An array stores them all under
          ONE name, and we reach each one by its INDEX.
       ============================================================ */

    /* ============================================================
       2. DECLARATION AND INITIALISATION
       ============================================================ */

    printf("=== 1. Declaration and initialisation ===\n");

    int num[5] = {10, 20, 30, 40, 50};   /* initialise while creating */

    /* index :   0    1    2    3    4      <- ALWAYS starts at 0
       value :  10   20   30   40   50      <- last index = size - 1 */

    printf("num[0] = %d\n", num[0]);
    printf("num[4] = %d  (last one, index = size-1)\n", num[4]);

    num[2] = 99;                          /* change one element */
    printf("after num[2] = 99 : ");
    for (i = 0; i < 5; i++)
        printf("%d ", num[i]);
    printf("\n");

    /* WARNING: num[5] does NOT exist. Reading or writing it is a
       serious bug (the program may crash or give random values).  */

    /* ============================================================
       3. FILLING AN ARRAY FROM THE KEYBOARD
       ============================================================ */

    printf("\n=== 2. Fill an array of %d scores ===\n", SIZE);

    float scores[SIZE];

    for (i = 0; i < SIZE; i++) {
        printf("Input score #%d: ", i + 1);
        scanf("%f", &scores[i]);          /* do not forget the & */
    }

    printf("\nYou entered: ");
    for (i = 0; i < SIZE; i++)
        printf("%.1f ", scores[i]);
    printf("\n");

    /* ============================================================
       4. SUM, AVERAGE, MAX, MIN
          The pattern is always the same:
            - prepare a result variable
            - loop over every element
            - update the result
       ============================================================ */

    printf("\n=== 3. Sum, average, max, min ===\n");

    float sum = 0, average, max, min;

    for (i = 0; i < SIZE; i++)
        sum = sum + scores[i];

    average = sum / SIZE;

    max = scores[0];      /* start with the first element, NOT with 0 */
    min = scores[0];
    for (i = 1; i < SIZE; i++) {
        if (scores[i] > max) max = scores[i];
        if (scores[i] < min) min = scores[i];
    }

    printf("Sum     = %.2f\n", sum);
    printf("Average = %.2f\n", average);
    printf("Max     = %.2f\n", max);
    printf("Min     = %.2f\n", min);

    /* ============================================================
       5. COUNT and FILTER
          "Show the scores greater than the average, and count them"
       ============================================================ */

    printf("\n=== 4. Scores above the average ===\n");

    int countAbove = 0;
    printf("Above %.2f : ", average);
    for (i = 0; i < SIZE; i++) {
        if (scores[i] > average) {
            printf("%.1f ", scores[i]);
            countAbove++;
        }
    }
    printf("\n%d student(s) got more than the average.\n", countAbove);

    /* ============================================================
       6. SEARCH an element
       ============================================================ */

    printf("\n=== 5. Search ===\n");

    float target;
    int found = -1;              /* -1 means "not found yet" */

    printf("Which score do you look for? ");
    scanf("%f", &target);

    for (i = 0; i < SIZE; i++) {
        if (scores[i] == target) {
            found = i;
            break;               /* stop as soon as we found it */
        }
    }

    if (found >= 0)
        printf("%.1f was found at index %d (position %d).\n",
               target, found, found + 1);
    else
        printf("%.1f is not in the array.\n", target);

    /* ============================================================
       7. AN ARRAY OF CHARACTERS = A STRING
       ============================================================ */

    printf("\n=== 6. Array of characters ===\n");

    char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
    printf("The 5 English vowels: ");
    for (i = 0; i < 5; i++)
        printf("%c ", vowels[i]);
    printf("\n");

    printf("The alphabet A-Z    : ");
    for (i = 0; i < 26; i++)
        printf("%c ", 'A' + i);      /* ASCII: 'A'+0='A', 'A'+1='B', ... */
    printf("\n");

    /* ============================================================
       8. AN ARRAY OF STRINGS = A 2D ARRAY OF CHARACTERS
             names[4][20] = 4 names, each of maximum 19 letters
                            (1 place is kept for the end mark '\0')
       ============================================================ */

    printf("\n=== 7. Array of names ===\n");

    char names[4][20];

    for (i = 0; i < 4; i++) {
        printf("Input name #%d: ", i + 1);
        scanf("%s", names[i]);       /* no & for a string */
    }

    printf("\nThe list of names:\n");
    for (i = 0; i < 4; i++)
        printf("  %d. %s (%d letters)\n", i + 1, names[i],
               (int)strlen(names[i]));

    /* ============================================================
       9. A 2D ARRAY OF NUMBERS (a table)
             marks[3][4] = 3 students, 4 subjects each
       ============================================================ */

    printf("\n=== 8. A table (2D array) ===\n");

    int marks[3][4] = {
        {80, 75, 90, 60},      /* student 0 */
        {55, 65, 70, 85},      /* student 1 */
        {95, 88, 79, 91}       /* student 2 */
    };

    printf("       S1  S2  S3  S4   total\n");
    for (i = 0; i < 3; i++) {
        int total = 0;
        printf("Std %d ", i + 1);
        for (j = 0; j < 4; j++) {
            printf("%3d ", marks[i][j]);
            total = total + marks[i][j];
        }
        printf("   %3d\n", total);
    }

    return 0;
}

/* ============================================================
   PRACTICE

   1. Store the even numbers 2, 4, 6, ..., 100 in an array,
      then display them 10 per line.
   2. Read 10 numbers, then display them in REVERSE order.
   3. Read 10 numbers and count how many values appear more
      than once (duplicates) and how many appear only once.
   4. Read 10 numbers and print only the unique values.
   5. Read 2 arrays of 5 numbers and build a third array which
      is the sum, element by element, of the first two.
   6. Sort an array of 10 numbers from the smallest to the
      largest. (Hint: compare each pair and swap them.)
   ============================================================ */
