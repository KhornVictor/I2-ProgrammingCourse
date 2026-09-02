/* ============================================================
   Data Structure & Programming II
   Topic 1: Getting started with C++

   What students learn here:
     1. C vs C++ : what changes, what stays the same
     2. cout / cin instead of printf / scanf (no placeholders!)
     3. The type "string" and the type "bool"
     4. A quick review: function, loop, array, structure
     5. struct in C++ : no need for the "struct" keyword again

   File extension : .cpp        (in C it was .c)
   Library        : <iostream>  (in C it was <stdio.h>)

   Compile:  g++ L1-Introduction.cpp -o L1
   ============================================================ */

#include <iostream>
#include <string>          // the C++ type "string"
using namespace std;       // so we can write cout instead of std::cout

/* ============================================================
   A quick review of FUNCTIONS - the syntax is the same as in C
   ============================================================ */

int sum(int a, int b)
{
    return a + b;
}

void greet(string name)    // "string" as a parameter: much easier than char[]
{
    cout << "Hi, " << name << "! Welcome to C++." << endl;
}

/* ============================================================
   A quick review of STRUCTURES
   In C   : struct Student st;
   In C++ : Student st;          <- the keyword "struct" is optional
   ============================================================ */

struct Student {
    string name;
    int    age;
    float  gpa;
};

int main()
{
    /* ============================================================
       1. HELLO WORLD - C style vs C++ style

          C:      printf("Hello world!\n");
          C++:    cout << "Hello world!" << endl;

          <<  is the "put into the output" operator.
          endl means "end of line" (the same as "\n").
       ============================================================ */

    cout << "=== 1. Output with cout ===" << endl;
    cout << "Hello world!" << endl;
    cout << "One" << " and " << "two" << " on the same line." << endl;

    /* ============================================================
       2. INPUT with cin

          C:      scanf("%d", &n);        <- needs %d and &
          C++:    cin >> n;               <- needs neither
       ============================================================ */

    cout << "\n=== 2. Input with cin ===" << endl;

    string name;
    int    age;

    cout << "What is your name?: ";
    cin  >> name;                 // no & , and no %s

    cout << "How old are you?: ";
    cin  >> age;

    cout << "Hi " << name << ", you are " << age << " years old." << endl;

    /* NOTE: cin >> name stops at the first space.
       To read a whole line (with spaces) use:  getline(cin, name);  */

    /* ============================================================
       3. THE TYPES OF C++
          Same as C: int, float, double, char
          New      : string   (a real text type)
                     bool     (true / false)
       ============================================================ */

    cout << "\n=== 3. string and bool ===" << endl;

    string city = "Phnom Penh";      // no strcpy needed
    string full = city + ", Cambodia";   // + joins two strings!

    cout << "city   = " << city << endl;
    cout << "full   = " << full << endl;
    cout << "length = " << full.length() << endl;
    cout << "first character = " << full[0] << endl;

    bool isStudent = true;
    cout << "isStudent = " << isStudent << "  (1 = true, 0 = false)" << endl;
    cout << boolalpha << "isStudent = " << isStudent << endl;  // prints "true"
    cout << noboolalpha;

    /* ============================================================
       4. CONDITION AND LOOP - EXACTLY THE SAME AS IN C
       ============================================================ */

    cout << "\n=== 4. Condition and loop (unchanged) ===" << endl;

    if (age >= 18)
        cout << "You are allowed to vote." << endl;
    else
        cout << "You are not allowed to vote yet." << endl;

    cout << "1 to 10 : ";
    for (int i = 1; i <= 10; i++)     // we can declare i inside the for
        cout << i << " ";
    cout << endl;

    int k = 5;
    cout << "while   : ";
    while (k > 0) { cout << k << " "; k--; }
    cout << endl;

    cout << "do-while: ";
    k = 3;
    do { cout << k << " "; k--; } while (k > 0);
    cout << endl;

    /* ============================================================
       5. FUNCTIONS
       ============================================================ */

    cout << "\n=== 5. Functions ===" << endl;
    cout << "sum(3, 5) = " << sum(3, 5) << endl;
    greet(name);

    /* ============================================================
       6. ARRAY - the same as in C
       ============================================================ */

    cout << "\n=== 6. Array ===" << endl;

    int marks[5] = {80, 75, 90, 60, 100};
    int total = 0;

    cout << "marks: ";
    for (int i = 0; i < 5; i++) {
        cout << marks[i] << " ";
        total += marks[i];            // total = total + marks[i]
    }
    cout << endl;
    cout << "average = " << (float)total / 5 << endl;

    /* ============================================================
       7. STRUCTURE - now with string members and no "struct" keyword
       ============================================================ */

    cout << "\n=== 7. Structure ===" << endl;

    Student s1;                       // in C we had to write: struct Student s1;
    s1.name = "Dara";                 // simple = , no strcpy
    s1.age  = 20;
    s1.gpa  = 3.5f;

    cout << s1.name << ", " << s1.age << " years old, GPA " << s1.gpa << endl;

    /* ============================================================
       8. AN ARRAY OF STRUCTURES
       ============================================================ */

    cout << "\n=== 8. Array of structures ===" << endl;

    Student list[3] = {
        {"Sok",   19, 3.20f},
        {"Sao",   21, 3.75f},
        {"Seyha", 20, 2.90f}
    };

    int best = 0;
    for (int i = 0; i < 3; i++) {
        cout << "  " << list[i].name << "\t" << list[i].age
             << "\t" << list[i].gpa << endl;
        if (list[i].gpa > list[best].gpa) best = i;
    }
    cout << "Best GPA: " << list[best].name
         << " (" << list[best].gpa << ")" << endl;

    return 0;
}

/* ============================================================
   SUMMARY : C  ->  C++

     stdio.h            ->   iostream
     printf("%d", n)    ->   cout << n
     scanf("%d", &n)    ->   cin  >> n
     char name[20]      ->   string name
     strcpy(a, b)       ->   a = b
     strcat(a, b)       ->   a = a + b
     strlen(a)          ->   a.length()
     struct Student st  ->   Student st
     (no bool)          ->   bool b = true;

   Everything else (if, for, while, functions, arrays,
   structures) works exactly the same way.

   PRACTICE
   1. Rewrite in C++ the "grade of a score" program of Topic 3 (C).
   2. Rewrite in C++ the "array of 10 scores" program of Topic 8 (C).
   3. Read a full sentence with getline(cin, text) and count how
      many spaces it contains.
   ============================================================ */
