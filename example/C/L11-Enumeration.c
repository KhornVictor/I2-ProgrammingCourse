/* ============================================================
   Data Structure & Programming I
   Topic 11: Enumeration (enum)

   What students learn here:
     1. Creating a NEW data type whose values are names
     2. Behind the names there are integers: 0, 1, 2, ...
     3. Choosing your own numbers (DELIVERED = 1, ...)
     4. Using typedef to get a short type name
     5. enum + switch : very readable code
     6. Looping over an enumeration

   Syntax:
        enum name { VALUE1, VALUE2, ..., VALUEN };
        enum name  myVariable;

   Why? Compare these two lines:
        if (status == 3)              <- 3 means... what?
        if (status == CANCELED)       <- everybody understands

   Compile:  gcc L11-Enumeration.c -o L11
   ============================================================ */

#include <stdio.h>

/* ============================================================
   1. A SIMPLE ENUMERATION
      The values are numbered automatically, starting at 0.
         Monday = 0, Tuesday = 1, ... Sunday = 6
   ============================================================ */

enum Day { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

/* ============================================================
   2. AN ENUMERATION WITH CHOSEN NUMBERS
      Here we decide the number of each value ourselves.
   ============================================================ */

enum Status { DELIVERED = 1, PENDING = 2, CANCELED = 3, SUCCESS = 4 };

/* ============================================================
   3. WITH typedef : we can drop the word "enum" afterwards
   ============================================================ */

typedef enum { BLACK, WHITE, RED, YELLOW, BLUE } Color;
typedef enum { SUMMER, AUTUMN, WINTER, SPRING } Season;

/* A procedure that takes an enumerated value as a parameter. */
void displayColor(Color c)
{
    switch (c) {
        case BLACK:  printf("Black color\n");  break;
        case WHITE:  printf("White color\n");  break;
        case RED:    printf("Red color\n");    break;
        case YELLOW: printf("Yellow color\n"); break;
        case BLUE:   printf("Blue color\n");   break;
        default:     printf("Unknown color\n");
    }
}

int main()
{
    /* ============================================================
       4. DECLARING AND USING A VARIABLE OF AN ENUM TYPE
       ============================================================ */

    printf("=== 1. enum Day ===\n");

    enum Day d;              /* with "enum" because we did not typedef it */

    d = Wednesday;
    printf("d = Wednesday, and its number is %d\n", d);   /* 2 */

    if (d == Wednesday)
        printf("Today we have the Programming course.\n");

    /* ============================================================
       5. AN ENUM IS REALLY AN INTEGER
          So we can compare it, add to it, and loop on it.
       ============================================================ */

    printf("\n=== 2. The numbers behind the names ===\n");

    printf("Monday=%d Tuesday=%d Wednesday=%d Thursday=%d\n",
           Monday, Tuesday, Wednesday, Thursday);
    printf("Friday=%d Saturday=%d Sunday=%d\n",
           Friday, Saturday, Sunday);

    printf("\nLoop from Monday to Sunday: ");
    for (d = Monday; d <= Sunday; d = d + 1)
        printf("%d ", d);
    printf("\n");

    /* IMPORTANT: printf CANNOT print the NAME "Monday".
       It only knows the number. If we want the name, we must
       write a switch (or an array of strings) ourselves.       */

    printf("\nThe same loop, but with real names:\n");
    for (d = Monday; d <= Sunday; d = d + 1) {
        switch (d) {
            case Monday:    printf("  Monday\n");    break;
            case Tuesday:   printf("  Tuesday\n");   break;
            case Wednesday: printf("  Wednesday\n"); break;
            case Thursday:  printf("  Thursday\n");  break;
            case Friday:    printf("  Friday\n");    break;
            case Saturday:  printf("  Saturday (weekend)\n"); break;
            case Sunday:    printf("  Sunday (weekend)\n");   break;
        }
    }

    /* A shorter way: an array of strings in the SAME order. */
    char *dayName[7] = { "Monday", "Tuesday", "Wednesday", "Thursday",
                         "Friday", "Saturday", "Sunday" };
    printf("\nWith an array of names: %s and %s are the weekend.\n",
           dayName[Saturday], dayName[Sunday]);

    /* ============================================================
       6. ENUM WITH CHOSEN NUMBERS
       ============================================================ */

    printf("\n=== 3. enum Status ===\n");

    enum Status orderStatus;
    int choice;

    printf("Order status (1=DELIVERED, 2=PENDING, 3=CANCELED, 4=SUCCESS): ");
    scanf("%d", &choice);

    orderStatus = choice;

    switch (orderStatus) {
        case DELIVERED: printf("The order has been delivered.\n"); break;
        case PENDING:   printf("The order is still pending.\n");   break;
        case CANCELED:  printf("The order was canceled.\n");       break;
        case SUCCESS:   printf("The order is complete.\n");        break;
        default:        printf("Unknown status.\n");
    }

    /* ============================================================
       7. TYPEDEF : no need for the word "enum"
       ============================================================ */

    printf("\n=== 4. typedef enum ===\n");

    Color myColor = RED;         /* short and clean */
    Season s = WINTER;

    printf("myColor -> ");
    displayColor(myColor);

    printf("Season WINTER has the number %d\n", s);

    printf("\nAll the colors:\n");
    Color c;
    for (c = BLACK; c <= BLUE; c = c + 1) {
        printf("  %d -> ", c);
        displayColor(c);
    }

    /* ============================================================
       8. A REAL LITTLE PROGRAM: marital status
       ============================================================ */

    printf("\n=== 5. A small application ===\n");

    typedef enum { SINGLE, MARRIED, DIVORCED, WIDOWED } MaritalStatus;

    MaritalStatus ms;
    int input;

    printf("Marital status (0=Single 1=Married 2=Divorced 3=Widowed): ");
    scanf("%d", &input);

    if (input < SINGLE || input > WIDOWED) {
        printf("This value does not exist in the list.\n");
    } else {
        ms = input;
        printf("You chose number %d which means: ", ms);
        switch (ms) {
            case SINGLE:   printf("Single\n");   break;
            case MARRIED:  printf("Married\n");  break;
            case DIVORCED: printf("Divorced\n"); break;
            case WIDOWED:  printf("Widowed\n");  break;
        }
    }

    return 0;
}

/* ============================================================
   PRACTICE

   1. Create enum Month { JANUARY = 1, ..., DECEMBER };
      Ask the user for a month number and display its name
      and how many days it has.
   2. Create enum Grade { A, B, C, D, F }. Read a score, compute
      the grade of Topic 3, store it in a Grade variable, then
      display it with a switch.
   3. Create enum Level { BEGINNER, INTERMEDIATE, ADVANCED } and
      use it in a small quiz menu.
   4. Create enum Direction { NORTH, EAST, SOUTH, WEST } and write
      a function turnRight(Direction d) that returns the next
      direction. (Hint: (d + 1) % 4)
   ============================================================ */
