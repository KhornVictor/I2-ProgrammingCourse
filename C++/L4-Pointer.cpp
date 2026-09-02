/* ============================================================
   Data Structure & Programming II
   Topic 4: Pointer

   What students learn here:
     1. Memory, address, and the operator &
     2. What a pointer is: a variable that stores an ADDRESS
     3. The two operators:
            &  "address of"    (reference)
            *  "value at"      (dereference)
     4. Changing a value through a pointer
     5. Pointer and array (the array name IS an address)
     6. Pointer as a function parameter -> the function can
        really modify the caller's variable (swap!)
     7. new / delete : creating memory while the program runs
        (this is what makes linked lists possible)

   THIS TOPIC IS THE KEY TO ALL THE NEXT ONES:
   linked list, stack, queue, tree - all of them use pointers.

   Compile:  g++ L4-Pointer.cpp -o L4
   ============================================================ */

#include <iostream>
using namespace std;

/* -------- prototypes -------- */
void notSwap(int a, int b);        // does NOT work
void doSwap(int *a, int *b);       // works, thanks to pointers
void fillAndSum(int *t, int size, int *sum);

int main()
{
    /* ============================================================
       1. EVERY VARIABLE HAS AN ADDRESS
       ============================================================ */

    cout << "=== 1. Address of a variable ===" << endl;

    int num = 10;

    cout << "num                 = " << num  << endl;
    cout << "address of num (&num) = " << &num << endl;
    cout << "an int uses " << sizeof(int) << " bytes of memory" << endl;

    /* ============================================================
       2. A POINTER STORES AN ADDRESS

          int *ptr;      "ptr is a pointer to an int"
          ptr = &num;    "ptr now holds the address of num"
          *ptr           "the value stored at that address"
       ============================================================ */

    cout << "\n=== 2. A pointer ===" << endl;

    int *ptr;              // declaration: the * says "this is a pointer"
    ptr = &num;            // initialisation: it points to num

    cout << "ptr   (an address) = " << ptr   << endl;
    cout << "*ptr  (the value ) = " << *ptr  << endl;
    cout << "&ptr  (address of the pointer itself) = " << &ptr << endl;

    /* Picture it like this:

           num                      ptr
        +------+                 +------------+
        |  10  |  <------------- | 0x61fe14   |
        +------+                 +------------+
        at 0x61fe14              ptr contains the address of num       */

    /* ============================================================
       3. CHANGING A VALUE THROUGH A POINTER
       ============================================================ */

    cout << "\n=== 3. Changing the value through the pointer ===" << endl;

    cout << "before : num = " << num << endl;
    *ptr = 99;                       // write 99 AT the address ptr holds
    cout << "*ptr = 99 -> num = " << num << "   <- num really changed!"
         << endl;

    num = 7;                         // and the other way around
    cout << "num = 7   -> *ptr = " << *ptr << endl;

    /* ============================================================
       4. THE CLASSIC EXAMPLE: exchange two values
          Without pointers the function receives COPIES,
          so the originals stay unchanged.
       ============================================================ */

    cout << "\n=== 4. Swap two values ===" << endl;

    int a = 1, b = 2;

    cout << "Start      : a = " << a << ", b = " << b << endl;

    notSwap(a, b);
    cout << "notSwap()  : a = " << a << ", b = " << b
         << "   <- nothing changed" << endl;

    doSwap(&a, &b);                  // we send the ADDRESSES
    cout << "doSwap()   : a = " << a << ", b = " << b
         << "   <- it worked!" << endl;

    /* ============================================================
       5. POINTER AND ARRAY
          The name of an array IS the address of its first element:
                arr  ==  &arr[0]
          So a pointer can walk through an array.
       ============================================================ */

    cout << "\n=== 5. Pointer and array ===" << endl;

    int arr[5] = {10, 20, 30, 40, 50};
    int *p = arr;                    // no & needed: arr is already an address

    cout << "arr      = " << arr     << endl;
    cout << "&arr[0]  = " << &arr[0] << "   <- the same address" << endl;
    cout << "*p       = " << *p      << "   <- the first element" << endl;

    cout << "Walking with the pointer: ";
    for (int i = 0; i < 5; i++)
        cout << *(p + i) << " ";     // *(p+i) is the same as arr[i]
    cout << endl;

    cout << "Moving the pointer      : ";
    p = arr;
    for (int i = 0; i < 5; i++) {
        cout << *p << " ";
        p++;                         // p++ jumps to the NEXT int
    }
    cout << endl;

    /* ============================================================
       6. A FUNCTION THAT FILLS AN ARRAY AND RETURNS TWO THINGS
          A function returns only ONE value... unless we give it
          pointers to the variables it must fill.
       ============================================================ */

    cout << "\n=== 6. A function that gives back two results ===" << endl;

    int t[5];
    int sum;

    fillAndSum(t, 5, &sum);          // t is an address, &sum is an address

    cout << "The array : ";
    for (int i = 0; i < 5; i++) cout << t[i] << " ";
    cout << endl;
    cout << "Their sum : " << sum << endl;

    /* ============================================================
       7. new AND delete : ask for memory WHILE the program runs

          This is called DYNAMIC MEMORY ALLOCATION.
          In C we used malloc() / free().
          In C++ we use  new  /  delete.

          A normal array has a size fixed when we write the code.
          With "new" we can decide the size when the program runs.
       ============================================================ */

    cout << "\n=== 7. new and delete ===" << endl;

    int *pNumber = new int;          // ask for the room of ONE int
    *pNumber = 123;
    cout << "*pNumber = " << *pNumber << endl;
    delete pNumber;                  // give the memory back
    pNumber = NULL;                  // good habit: forget the old address

    int n;
    cout << "How many numbers do you want to store? ";
    cin  >> n;

    int *dyn = new int[n];           // an array of n int, decided NOW

    for (int i = 0; i < n; i++)
        dyn[i] = (i + 1) * (i + 1);  // 1, 4, 9, 16 ...

    cout << "The squares: ";
    for (int i = 0; i < n; i++)
        cout << dyn[i] << " ";
    cout << endl;

    delete[] dyn;                    // [] because it was an array
    dyn = NULL;

    /* RULE: every "new" must have its "delete".
       If you forget, the memory is lost until the program stops.
       This is called a MEMORY LEAK.                              */

    /* ============================================================
       8. WHY DOES THIS MATTER?
          Next topic: the LINKED LIST. Each element is created
          with "new" while the program runs, and each element
          holds a POINTER to the next one. Without pointers,
          a linked list simply cannot exist.
       ============================================================ */

    return 0;
}

/* ------------------------------------------------------------
   Receives COPIES: the exchange happens only inside the function.
   ------------------------------------------------------------ */
void notSwap(int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

/* ------------------------------------------------------------
   Receives ADDRESSES: it works on the real variables of main().
   ------------------------------------------------------------ */
void doSwap(int *a, int *b)
{
    int tmp = *a;      // read the value at address a
    *a = *b;           // write into the address a
    *b = tmp;
}

/* ------------------------------------------------------------
   t   : the address of the first element of the array
   sum : the address of the variable that must receive the total
   ------------------------------------------------------------ */
void fillAndSum(int *t, int size, int *sum)
{
    *sum = 0;
    for (int i = 0; i < size; i++) {
        t[i] = (i + 1) * 10;         // t[i] is the same as *(t+i)
        *sum = *sum + t[i];
    }
}

/* ============================================================
   SUMMARY

     int  n = 5;        a normal variable
     int *p;            a pointer to an int
     p = &n;            p receives the address of n
     *p                 the value stored at that address  (= 5)
     *p = 8;            changes n to 8

     new int            create one int in memory
     new int[10]        create an array of 10 int
     delete p           free one element
     delete[] p         free an array

   PRACTICE

   1. Write a function minMax(int t[], int size, int *min, int *max)
      that returns BOTH the minimum and the maximum.
   2. Write a function that reverses an array using two pointers,
      one at the beginning and one at the end.
   3. Ask the user for a size n, create an array with new,
      fill it from the keyboard, display the average, then delete it.
   4. What is the difference between  *p + 1  and  *(p + 1) ?
      Test both and explain.
   5. Write a function increment(int *n) that adds 1 to a variable
      of main().
   ============================================================ */
