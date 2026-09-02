/* ============================================================
   Data Structure & Programming I
   Topic 2: Variable, Basic Data Type, Operators and Statements

   What students learn here:
     1. Declaring variables and the rules for naming them
     2. Basic data types: int, float/double, char, string, bool
     3. Constants (#define and const)
     4. Operators  +  -  *  /  %  and relational operators
     5. ASCII code with characters
     6. String functions from <string.h>

   Compile:  gcc L2-Variable.c -o L2
   ============================================================ */

#include <stdio.h>
#include <string.h>   /* strlen, strcpy, strcat, strcmp, ... */

/* A CONSTANT never changes while the program runs.
   Naming convention: ALL CAPITAL LETTERS.
   Algorithm:  const(EXCHANGE_RATE : Integer) <- 4100          */
#define EXCHANGE_RATE 4100
#define TAX 3

int main()
{
    /* ============================================================
       1. DECLARING VARIABLES
       Algorithm syntax:   Var age, number : Integer
       C syntax        :   int age, number;
       ============================================================ */

    int    age;              /* whole number       : 5, 8, -19          */
    float  price;            /* real number        : 4.5, -0.25         */
    double surface;          /* real number, more precision            */
    char   gender;           /* ONE character, single quotes: 'M'      */
    char   name[30];         /* a string, double quotes: "Sok"         */

    /* GOOD names          BAD names (do not compile!)
         age                 7age      -> starts with a digit
         price               @price    -> starts with a symbol
         studentName         student Name -> contains a space
         work_position       int       -> reserved keyword
       Remember: age, Age and AGE are THREE DIFFERENT variables.   */

    /* ============================================================
       2. ASSIGNING VALUES
       Algorithm:  age <- 20        C:  age = 20;
       ============================================================ */

    age     = 20;
    price   = 12.5f;
    gender  = 'M';
    strcpy(name, "Sok");    /* for strings we must use strcpy, not =  */

    printf("=== 1. Variables ===\n");
    printf("name    = %s\n", name);
    printf("age     = %d\n", age);
    printf("price   = %.2f\n", price);   /* %.2f = 2 digits after the dot */
    printf("gender  = %c\n", gender);

    /* ============================================================
       3. INTEGER OPERATORS:  +  -  *  /  %
          In the algorithm course:  DIV = quotient, MOD = remainder.
          In C:  /  on two integers IS the quotient (DIV)
                 %  is the remainder (MOD)
       ============================================================ */

    printf("\n=== 2. Integer operators ===\n");

    int x = 10 + 2;          /* x = 12 */
    int y = x - 7;           /* y = 5  */

    printf("x = 10 + 2  -> %d\n", x);
    printf("y = x - 7   -> %d\n", y);
    printf("y / 2  (DIV, quotient ) -> %d\n", y / 2);      /* 2   */
    printf("y %% 2  (MOD, remainder) -> %d\n", y % 2);     /* 1   */
    printf("y / 2.0 (real division ) -> %.2f\n", y / 2.0); /* 2.50 */
    /* CAREFUL: 5 / 2 gives 2, not 2.5, because both are integers! */

    /* ============================================================
       4. RELATIONAL OPERATORS -> the answer is TRUE(1) or FALSE(0)
          ==   !=   >   <   >=   <=
          Logical operators:  &&  (AND)   ||  (OR)   !  (NOT)
       ============================================================ */

    printf("\n=== 3. Relational and logical operators ===\n");

    int a = 10, b = 20;
    printf("a = %d, b = %d\n", a, b);
    printf("a < 3            -> %d  (0 = false)\n", a < 3);
    printf("a == 10          -> %d  (1 = true )\n", a == 10);
    printf("a >= 10 && b<100 -> %d\n", a >= 10 && b < 100);
    printf("a > 10  && b<100 -> %d\n", a > 10  && b < 100);
    printf("!(a == 10)       -> %d\n", !(a == 10));

    /* ============================================================
       5. CHARACTER and ASCII CODE
          Every character has a number (its ASCII code).
              '0'..'9' = 48..57      'A'..'Z' = 65..90
              'a'..'z' = 97..122
       ============================================================ */

    printf("\n=== 4. Character and ASCII code ===\n");

    char c = 'A';
    printf("c            = %c\n", c);
    printf("ord(c)       = %d\n", c);        /* print the char as a number */
    printf("next(c)      = %c\n", c + 1);    /* 'B' */
    printf("prev(c)      = %c\n", c - 1);    /* '@' */
    printf("chr(65)      = %c\n", 65);       /* 'A' */

    /* ============================================================
       6. STRING FUNCTIONS  (need #include <string.h>)
       ============================================================ */

    printf("\n=== 5. String functions ===\n");

    char s1[50] = "Hello";
    char s2[50] = " world";

    printf("s1                 = \"%s\"\n", s1);
    printf("strlen(s1)         = %d\n", (int)strlen(s1));   /* 5 */
    printf("s1[0]              = %c\n", s1[0]);             /* 'H' */

    strcat(s1, s2);            /* concat: s1 becomes "Hello world" */
    printf("strcat(s1, s2)     = \"%s\"\n", s1);

    printf("strcmp(\"Hi\",\"Hi\") = %d  (0 means equal)\n", strcmp("Hi", "Hi"));

    char copy[50];
    strcpy(copy, s1);          /* copy s1 into copy */
    printf("strcpy -> copy     = \"%s\"\n", copy);

    /* strupr / strlwr exist only on some compilers (Code::Blocks/MinGW).
       The portable way is to loop and shift by the ASCII distance 32. */
    {
        int i;
        char word[50] = "Apple";
        for (i = 0; word[i] != '\0'; i++)
            if (word[i] >= 'a' && word[i] <= 'z')
                word[i] = word[i] - 32;      /* lowercase -> UPPERCASE */
        printf("uppercase(Apple)   = \"%s\"\n", word);
    }

    /* ============================================================
       7. COMPLETE EXAMPLE from the lecture:
          price + tax, and currency exchange USD -> Riel
       ============================================================ */

    printf("\n=== 6. Exercise: price with tax ===\n");

    float priceWithTax;
    printf("Give me the price exclude tax: ");
    scanf("%f", &price);

    priceWithTax = price + (price * TAX) / 100;
    printf("Result\n");
    printf("%.2f dollars exclude tax, %.2f dollars include tax\n",
           price, priceWithTax);

    printf("\n=== 7. Exercise: currency exchange ===\n");

    float amountUSD, amountRiel;
    printf("How much in US dollars do you want to exchange?: ");
    scanf("%f", &amountUSD);

    amountRiel = amountUSD * EXCHANGE_RATE;
    printf("Your exchange amount of %.2f dollars is equal to %.0f riels\n",
           amountUSD, amountRiel);
    printf("(exchange rate is 1 USD = %d riels)\n", EXCHANGE_RATE);

    return 0;
}

/* ============================================================
   PRACTICE

   1. Ask firstname and lastname, then build a username by joining
      firstname + "_" + lastname.   Jack + Rose -> Jack_Rose
   2. Ask for a word and print it in UPPERCASE and in lowercase.
   3. Ask for a word and print its length:
        The length of the word "Book" is 4.
   4. Ask for a word and print the first and the last character.
        In word "Banana", the first character is 'B'
        and the last character is 'a'
   5. Ask a user for the base and the height of a triangle,
      then compute and display its area.
   ============================================================ */
