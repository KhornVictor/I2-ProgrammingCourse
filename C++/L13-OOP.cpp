/* ============================================================
   Data Structure & Programming II
   Topic 13: Introduction to Object-Oriented Programming (OOP)

   What students learn here:
     1. struct vs class
     2. CLASS = the blueprint,  OBJECT = one real item
        properties (data) + methods (functions)
     3. ENCAPSULATION and the access modifiers:
            private   : only the class itself
            protected : the class and its children
            public    : everybody
        (getter and setter methods)
     4. The CONSTRUCTOR (and overloading it)
     5. INHERITANCE : a child class reuses a parent class
     6. OVERLOADING vs OVERRIDING
     7. POLYMORPHISM with virtual functions
     8. ABSTRACTION : a pure virtual function = an interface

   RULE OF THUMB
        the data       -> private   (protect it)
        the methods    -> public    (offer the service)

   Compile:  g++ L13-OOP.cpp -o L13
   ============================================================ */

#include <iostream>
#include <string>
using namespace std;

/* ============================================================
   1. FROM A STRUCTURE TO A CLASS

      A structure only groups data.
      A class groups data AND the functions that work on it,
      and it can PROTECT its data.
   ============================================================ */

struct StudentStruct {              // the old way (Topic 12 of C)
    string name;
    double gpa;
};

class Student {

    /* ---- the DATA is private: nobody can touch it directly ---- */
private:
    int    idNum;
    string lastName;
    double gpa;

    /* ---- the METHODS are public: this is the way in ---- */
public:

    /* ---------- CONSTRUCTORS ----------
       A constructor is a special method:
         - it has the SAME name as the class
         - it has NO return type
         - it runs automatically when an object is created  */

    Student()                              // constructor 1: no parameter
    {
        idNum    = 0;
        lastName = "unknown";
        gpa      = 0.0;
    }

    Student(string name, int id, double g) // constructor 2: with parameters
    {                                      // (this is OVERLOADING)
        lastName = name;
        idNum    = id;
        setGPA(g);                         // we reuse our own setter
    }

    /* ---------- SETTERS: control what goes IN ---------- */

    void setData(string name, int id, double g)
    {
        lastName = name;
        idNum    = id;
        setGPA(g);
    }

    void setGPA(double g)
    {
        if (g < 0)      gpa = 0;           // THIS is why gpa is private:
        else if (g > 4) gpa = 4;           // the class protects itself
        else            gpa = g;           // from a wrong value
    }

    /* ---------- GETTERS: control what goes OUT ---------- */

    double getGPA()      { return gpa;      }
    string getLastName() { return lastName; }
    int    getId()       { return idNum;    }

    /* ---------- A NORMAL METHOD ---------- */

    void displayStudentData()
    {
        cout << "   [" << idNum << "] " << lastName
             << "  GPA = " << gpa << endl;
    }

    /* "virtual" tells C++: a child class may replace this method.
       Look at part 5 to see why it matters.                      */
    virtual void role()
    {
        cout << "   I am a student." << endl;
    }
};

/* ============================================================
   2. INHERITANCE
      FirstYearStudent IS a Student, plus something more.
      It gets every property and method of Student for free.
   ============================================================ */

class FirstYearStudent : public Student {

private:
    string groupId;

public:
    FirstYearStudent(string name, int id, double g, string group)
        : Student(name, id, g)       // first, build the Student part
    {
        groupId = group;
    }

    void doOrientation()             // a NEW method, only for the child
    {
        cout << "   " << getLastName()
             << " is doing the orientation week (group "
             << groupId << ")." << endl;
    }

    /* OVERRIDING: the same method name as the parent,
       the same parameters, but a different behaviour.        */
    void role()
    {
        cout << "   I am a FIRST YEAR student, group "
             << groupId << "." << endl;
    }
};

/* ============================================================
   3. OVERLOADING
      Several functions with the SAME NAME but DIFFERENT
      parameters. C++ chooses the right one automatically.
   ============================================================ */

class Calculator {
public:
    int    add(int a, int b)                 { return a + b; }
    double add(double a, double b)           { return a + b; }
    int    add(int a, int b, int c)          { return a + b + c; }
    string add(string a, string b)           { return a + b; }
};

/* ============================================================
   4. ABSTRACTION
      A pure virtual method ( = 0 ) has no code at all.
      A class with one is ABSTRACT: we cannot create an object
      of it, only of its children. It defines a CONTRACT:
      "every shape must know how to compute its area".
   ============================================================ */

class Shape {
protected:                     // protected: the children can use it
    string name;

public:
    Shape(string n) { name = n; }

    virtual double area() = 0;              // pure virtual = no code here

    void describe()
    {
        cout << "   The " << name << " has an area of "
             << area() << endl;             // calls the CHILD's area()
    }
};

class Rectangle : public Shape {
private:
    double w, h;
public:
    Rectangle(double width, double height) : Shape("rectangle")
    { w = width; h = height; }

    double area() { return w * h; }
};

class Circle : public Shape {
private:
    double r;
public:
    Circle(double radius) : Shape("circle")
    { r = radius; }

    double area() { return 3.14159 * r * r; }
};

/* ============================================================
   MAIN
   ============================================================ */

int main()
{
    /* ------------------------------------------------------------
       1. CREATE OBJECTS
       ------------------------------------------------------------ */

    cout << "=== 1. Objects of the class Student ===" << endl;

    Student s1;                                  // uses constructor 1
    Student s2("Dara", 2, 3.75);                 // uses constructor 2
    Student s3("Sao",  3, 3.00);

    s1.setData("Sok", 1, 3.50);                  // fill it afterwards

    s1.displayStudentData();
    s2.displayStudentData();
    s3.displayStudentData();

    /* ------------------------------------------------------------
       2. ENCAPSULATION IN ACTION
       ------------------------------------------------------------ */

    cout << "\n=== 2. Encapsulation ===" << endl;

    // s1.gpa = 99;          <-- ERROR! gpa is private. Try to uncomment it.

    s1.setGPA(99);                               // the class says no
    cout << "   after setGPA(99), the GPA is " << s1.getGPA()
         << " (the class refused a wrong value)" << endl;

    s1.setGPA(3.9);
    cout << "   after setGPA(3.9), the GPA is " << s1.getGPA() << endl;

    /* With the old struct there was no protection at all: */
    StudentStruct old;
    old.name = "Nobody";
    old.gpa  = 99;                               // nothing stops us
    cout << "   with a plain struct: gpa = " << old.gpa
         << "  <- impossible value accepted!" << endl;

    /* ------------------------------------------------------------
       3. AN ARRAY OF OBJECTS
       ------------------------------------------------------------ */

    cout << "\n=== 3. An array of objects ===" << endl;

    Student classroom[3] = {
        Student("Seyha",  4, 2.80),
        Student("Vichea", 5, 3.95),
        Student("Bopha",  6, 3.10)
    };

    int best = 0;
    for (int i = 0; i < 3; i++) {
        classroom[i].displayStudentData();
        if (classroom[i].getGPA() > classroom[best].getGPA())
            best = i;
    }
    cout << "   Best GPA: " << classroom[best].getLastName() << endl;

    /* ------------------------------------------------------------
       4. INHERITANCE
       ------------------------------------------------------------ */

    cout << "\n=== 4. Inheritance ===" << endl;

    FirstYearStudent f1("Chan", 7, 3.20, "I2-A");

    f1.displayStudentData();     // inherited from Student
    f1.doOrientation();          // its own method
    cout << "   getGPA() also works: " << f1.getGPA() << endl;

    /* ------------------------------------------------------------
       5. POLYMORPHISM
          The SAME line of code, a DIFFERENT behaviour, depending
          on the real type of the object behind the pointer.
       ------------------------------------------------------------ */

    cout << "\n=== 5. Polymorphism ===" << endl;

    Student *people[2];
    people[0] = &s2;             // a Student
    people[1] = &f1;             // a FirstYearStudent

    for (int i = 0; i < 2; i++)
        people[i]->role();       // the same call, two different answers

    cout << "   (this works because role() is declared virtual)" << endl;

    /* ------------------------------------------------------------
       6. OVERLOADING
       ------------------------------------------------------------ */

    cout << "\n=== 6. Overloading ===" << endl;

    Calculator calc;
    cout << "   add(2, 3)          = " << calc.add(2, 3)           << endl;
    cout << "   add(2.5, 3.1)      = " << calc.add(2.5, 3.1)       << endl;
    cout << "   add(1, 2, 3)       = " << calc.add(1, 2, 3)        << endl;
    cout << "   add(\"Hello \",\"OOP\") = " << calc.add("Hello ", "OOP") << endl;

    /* ------------------------------------------------------------
       7. ABSTRACTION
       ------------------------------------------------------------ */

    cout << "\n=== 7. Abstraction ===" << endl;

    // Shape s("test");          <-- ERROR: Shape is abstract

    Rectangle r(4, 5);
    Circle    c(3);

    r.describe();
    c.describe();

    Shape *shapes[2] = { &r, &c };
    double total = 0;
    for (int i = 0; i < 2; i++)
        total += shapes[i]->area();      // each one uses its own formula
    cout << "   Total area = " << total << endl;

    /* ------------------------------------------------------------
       8. THE FOUR PILLARS - SUMMARY

          ENCAPSULATION  hide the data, offer methods
          INHERITANCE    reuse an existing class
          POLYMORPHISM   one call, many behaviours
          ABSTRACTION    show WHAT, hide HOW
       ------------------------------------------------------------ */

    return 0;
}

/* ============================================================
   PRACTICE

   1. (exercise of the lecture) Write a class Customer with the
      properties id (private), name, sex, phone (public) and
      the methods setCustomerData(...) and displayACustomerInfo().
      Create 5 objects and display the 1st, the 3rd and the 5th.
   2. Write a class BankAccount with a private balance and the
      methods deposit(), withdraw() and getBalance().
      withdraw() must refuse to take more money than available.
      This is encapsulation doing real work.
   3. Write a class Person, then Student and Teacher which both
      inherit from it. Give each one its own displayInfo().
   4. Add a class Triangle to the Shape family.
   5. Turn the LinkedList of Topic 6 into a class List with
      private head/tail/n and public insert/delete/display.
      Compare the two versions: which one is safer to use?
   6. What is the difference between OVERLOADING and OVERRIDING?
      Give one example of each from this file.
   ============================================================ */
