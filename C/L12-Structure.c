/* ============================================================
   Data Structure & Programming I
   Topic 12: Structure (struct)

   What students learn here:
     1. The problem: one student = 4 separate arrays. Bad!
     2. struct = a NEW data type made of other types
     3. Reaching a member with the dot  .
     4. typedef to get a short type name
     5. An ARRAY of structures (100 students)
     6. A NESTED structure (a date inside a student)
     7. A structure used with a function
     8. struct + enum together

   Syntax:
        struct Name {
            type member1;
            type member2;
        };
        struct Name myVariable;

   Compile:  gcc L12-Structure.c -o L12
   ============================================================ */

#include <stdio.h>
#include <string.h>

#define NB_STUDENTS 3

/* ============================================================
   1. A SIMPLE STRUCTURE
      Each variable inside is called a FIELD, an ATTRIBUTE
      or a MEMBER.
   ============================================================ */

struct Date {
    int day;
    int month;
    int year;
};

/* ============================================================
   2. A NESTED STRUCTURE
      "dob" (date of birth) is itself a struct Date.
      A structure can contain another structure.
   ============================================================ */

struct Student {
    char        name[30];
    char        surname[30];
    char        sex;             /* 'M' or 'F' */
    struct Date dob;             /* <- nested structure */
    float       gpa;
};

/* ============================================================
   3. TYPEDEF : a short name, no need to write "struct" again
   ============================================================ */

typedef struct {
    char  name[30];
    float price;
    int   quantity;
} Product;

/* ============================================================
   4. STRUCT + ENUM
   ============================================================ */

typedef enum { ELECTRONICS, FOOD, CLOTHES } Category;

typedef struct {
    char     label[30];
    Category category;
} Item;

/* ============================================================
   PROTOTYPES of functions that work on structures
   ============================================================ */

void  displayStudent(struct Student s);
int   diffAge(struct Student s1, struct Student s2);
float totalPrice(Product p);
void  displayDate(struct Date d);

int main()
{
    int i;

    /* ============================================================
       5. THE PROBLEM WITHOUT STRUCTURES

          char  name[100][30];
          char  surname[100][30];
          int   age[100];
          char  sex[100];

          The information about ONE student is scattered in
          4 different arrays. If we sort one array, all the
          other ones become wrong. A structure keeps the
          information of one student TOGETHER.
       ============================================================ */

    /* ============================================================
       6. CREATE AND FILL ONE STRUCTURE
       ============================================================ */

    printf("=== 1. One student ===\n");

    struct Student s;

    strcpy(s.name, "Dara");        /* a string: use strcpy */
    strcpy(s.surname, "Sok");
    s.sex       = 'M';
    s.gpa       = 3.45f;
    s.dob.day   = 12;              /* dot, then dot again for nested */
    s.dob.month = 7;
    s.dob.year  = 2004;

    displayStudent(s);

    s.gpa = s.gpa + 0.1f;          /* we can change a member */
    printf("After the bonus, GPA = %.2f\n", s.gpa);

    /* We can also fill everything while creating: */
    struct Student s2 = { "Sao", "Chan", 'F', {30, 11, 2002}, 3.80f };
    displayStudent(s2);

    printf("Age difference (in years of birth): %d\n", diffAge(s, s2));

    /* ============================================================
       7. AN ARRAY OF STRUCTURES
          This is how we really store 100 students.
       ============================================================ */

    printf("\n=== 2. An array of %d students ===\n", NB_STUDENTS);

    struct Student list[NB_STUDENTS];

    for (i = 0; i < NB_STUDENTS; i++) {
        printf("\n--- Student #%d ---\n", i + 1);
        printf("Surname : ");  scanf("%s", list[i].surname);
        printf("Name    : ");  scanf("%s", list[i].name);
        printf("Sex M/F : ");  scanf(" %c", &list[i].sex);
        printf("Birth (dd mm yyyy): ");
        scanf("%d %d %d", &list[i].dob.day,
                          &list[i].dob.month,
                          &list[i].dob.year);
        printf("GPA     : ");  scanf("%f", &list[i].gpa);
    }

    printf("\n--- The complete list ---\n");
    for (i = 0; i < NB_STUDENTS; i++)
        displayStudent(list[i]);

    /* The usual array work still applies: find the best GPA. */
    int best = 0;
    for (i = 1; i < NB_STUDENTS; i++)
        if (list[i].gpa > list[best].gpa)
            best = i;

    printf("\nThe best GPA is %.2f, obtained by %s %s\n",
           list[best].gpa, list[best].surname, list[best].name);

    /* ============================================================
       8. TYPEDEF STRUCTURE
       ============================================================ */

    printf("\n=== 3. typedef struct (Product) ===\n");

    Product p1 = { "Notebook", 1.50f, 12 };   /* no "struct" needed */
    Product p2;

    strcpy(p2.name, "Pen");
    p2.price    = 0.75f;
    p2.quantity = 40;

    printf("%-10s %6.2f x %3d = %7.2f\n",
           p1.name, p1.price, p1.quantity, totalPrice(p1));
    printf("%-10s %6.2f x %3d = %7.2f\n",
           p2.name, p2.price, p2.quantity, totalPrice(p2));
    printf("%-10s %19s %7.2f\n", "TOTAL", "", totalPrice(p1) + totalPrice(p2));

    /* ============================================================
       9. STRUCT + ENUM
       ============================================================ */

    printf("\n=== 4. struct + enum (Item) ===\n");

    Item items[3] = {
        { "Laptop", ELECTRONICS },
        { "Rice",   FOOD        },
        { "Shirt",  CLOTHES     }
    };

    for (i = 0; i < 3; i++) {
        printf("%-10s -> ", items[i].label);
        switch (items[i].category) {
            case ELECTRONICS: printf("Electronics\n"); break;
            case FOOD:        printf("Food\n");        break;
            case CLOTHES:     printf("Clothes\n");     break;
        }
    }

    return 0;
}

/* ============================================================
   FUNCTIONS THAT WORK ON STRUCTURES
   ============================================================ */

/* A structure can be a PARAMETER. It is copied into the
   function, so changing it here does NOT change the original. */
void displayStudent(struct Student s)
{
    printf("%s %s (%c), born on ", s.surname, s.name, s.sex);
    displayDate(s.dob);
    printf(", GPA = %.2f\n", s.gpa);
}

void displayDate(struct Date d)
{
    printf("%02d/%02d/%04d", d.day, d.month, d.year);
}

/* Two structures as parameters. */
int diffAge(struct Student s1, struct Student s2)
{
    int diff = s1.dob.year - s2.dob.year;
    if (diff < 0)
        diff = -diff;
    return diff;
}

float totalPrice(Product p)
{
    return p.price * p.quantity;
}

/* ============================================================
   PRACTICE

   1. Create struct Book { title, author, year, price } and store
      5 books in an array. Display the list and the total price.
   2. Add a function findByName() that searches a student by
      surname in the array and returns its index (-1 if absent).
   3. Create struct Time { h, m, s } and a function
      addSeconds(struct Time t, int n) that returns the new time.
   4. Create struct Address { street, city, country } and put it
      inside struct Student as a nested structure.
   5. Sort the array of students by GPA, from the best to the
      lowest. (Hint: swap two WHOLE structures:
          struct Student tmp = list[i];
          list[i] = list[j];
          list[j] = tmp;    )
   ============================================================ */
