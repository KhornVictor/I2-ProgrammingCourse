/* ============================================================
   Data Structure & Programming I
   Topic 3: Condition (Decision Making)

   What students learn here:
     1. if
     2. if ... else
     3. if ... else if ... else
     4. switch ... case ... default
     5. Classic exercises: grade of a score, biggest number,
        type of a character (using ASCII code)

   Algorithm syntax          C syntax
   ------------------------  ------------------------
   if (condition) then       if (condition) {
       instructions              instructions
   end if                    }

   Compile:  gcc L3-Condtion.c -o L3
   ============================================================ */

#include <stdio.h>

int main()
{
    /* ============================================================
       1. SIMPLE IF
          The block runs ONLY when the condition is true.
       ============================================================ */

    printf("=== 1. Simple if ===\n");

    int a = 2, b = 3;

    if (3 < 2) {
        printf("This line never appears (3 < 2 is false)\n");
    }

    if (a < b) {
        printf("Hi, ");
        printf("Welcome back!\n");
    }
    printf("Hello\n");   /* outside the if -> always displayed */

    /* ============================================================
       2. IF ... ELSE
          true  -> block 1
          false -> block 2
       ============================================================ */

    printf("\n=== 2. if ... else ===\n");

    int n1, n2;
    printf("Enter two numbers: ");
    scanf("%d %d", &n1, &n2);

    if (n1 > n2) {
        printf("The greater value is: %d\n", n1);
    } else {
        printf("The greater value is: %d\n", n2);
    }

    /* ============================================================
       3. IF ... ELSE IF ... ELSE
          The conditions are tested FROM TOP TO BOTTOM.
          As soon as one is true, the others are skipped.
       ============================================================ */

    printf("\n=== 3. if ... else if ... else ===\n");

    int x;
    printf("Enter a number to compare with 100: ");
    scanf("%d", &x);

    if (x == 100) {
        printf("x is equal to 100\n");
    } else if (x > 100) {
        printf("x is greater than 100\n");
    } else {
        printf("x is less than 100\n");
    }

    /* ============================================================
       4. EXERCISE 1: grade of a score
          >= 90 -> A ,  >= 80 -> B ,  >= 70 -> C ,
          >= 60 -> D ,  otherwise -> F
       ============================================================ */

    printf("\n=== 4. Exercise: grade of a score ===\n");

    int score;
    printf("Enter your score to identify your grade: ");
    scanf("%d", &score);

    if (score >= 90) {
        printf("You got grade A.\n");
    } else if (score >= 80) {
        printf("You got grade B.\n");
    } else if (score >= 70) {
        printf("You got grade C.\n");
    } else if (score >= 60) {
        printf("You got grade D.\n");
    } else {
        printf("You got grade F.\n");
    }

    /* WHY does "score >= 80" work for a score of 95 too?
       It does not matter: 95 already matched "score >= 90" above,
       so the program never reaches the second test.
       ORDER IS IMPORTANT in an else-if chain.                   */

    /* ============================================================
       5. EXERCISE 2: the biggest of three numbers
          Two solutions are shown. The second one is better,
          because it can easily grow to 10 or 100 numbers.
       ============================================================ */

    printf("\n=== 5. Exercise: biggest of three numbers ===\n");

    int p, q, r, max;
    printf("Enter three integer numbers: ");
    scanf("%d %d %d", &p, &q, &r);

    /* solution A: compare everything with everything */
    if (p >= q && p >= r) {
        printf("[A] %d is the biggest number.\n", p);
    } else if (q >= p && q >= r) {
        printf("[A] %d is the biggest number.\n", q);
    } else {
        printf("[A] %d is the biggest number.\n", r);
    }

    /* solution B: keep the best value found so far */
    max = p;
    if (max < q) max = q;
    if (max < r) max = r;
    printf("[B] %d is the biggest number.\n", max);

    /* ============================================================
       6. EXERCISE 3: what kind of character is it?
          Hint from the lecture: use the ASCII code.
              '0'..'9' -> 48..57
              'A'..'Z' -> 65..90
              'a'..'z' -> 97..122
       ============================================================ */

    printf("\n=== 6. Exercise: type of a character ===\n");

    char ch;
    int  code;

    printf("Enter a character: ");
    scanf(" %c", &ch);     /* the space before %c skips the old Enter key */

    code = ch;             /* a char used as an int IS its ASCII code */

    if (code >= 48 && code <= 57) {
        printf("'%c' (ASCII %d) is a number.\n", ch, code);
    } else if (code >= 65 && code <= 90) {
        printf("'%c' (ASCII %d) is an uppercase letter.\n", ch, code);
    } else if (code >= 97 && code <= 122) {
        printf("'%c' (ASCII %d) is a lowercase letter.\n", ch, code);
    } else {
        printf("That is not a number nor a letter.\n");
    }

    /* ============================================================
       7. SWITCH ... CASE
          Use it when you compare ONE variable with several
          CONSTANT values. Do not forget "break;" !
          Without break, the program falls into the next case.
       ============================================================ */

    printf("\n=== 7. switch ... case ===\n");

    char sex;
    printf("Enter your sex (M/F): ");
    scanf(" %c", &sex);

    switch (sex) {
        case 'M':
        case 'm':
            printf("You are a male\n");
            break;
        case 'F':
        case 'f':
            printf("You are a female\n");
            break;
        default:
            printf("Wrong input\n");
    }

    /* ============================================================
       8. A MENU: temperature conversion (assignment of the lecture)
       ============================================================ */

    printf("\n=== 8. Menu: temperature conversion ===\n");
    printf("1- Celsius    to Fahrenheit\n");
    printf("2- Fahrenheit to Celsius\n");
    printf("Your choice: ");

    int choice;
    float t;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Temperature in Celsius: ");
            scanf("%f", &t);
            printf("%.2f C = %.2f F\n", t, t * 9 / 5 + 32);
            break;
        case 2:
            printf("Temperature in Fahrenheit: ");
            scanf("%f", &t);
            printf("%.2f F = %.2f C\n", t, (t - 32) * 5 / 9);
            break;
        default:
            printf("There is no such choice in the menu.\n");
    }

    return 0;
}

/* ============================================================
   PRACTICE

   1. Check whether a number entered by the user is even or odd.
      (hint:  n % 2 == 0  means even)
   2. Check whether a number is positive, negative or zero.
   3. Solve ax^2 + bx + c = 0. Read a, b, c, compute
      delta = b*b - 4*a*c, then display the roots according to
      the sign of delta.
   4. Read 8 numbers and display the maximum one.
   5. Write a menu that computes the area of a triangle
      (Heron formula), a circle and a rectangle.
   ============================================================ */
