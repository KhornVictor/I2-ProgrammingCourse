/* ============================================================
   Data Structure & Programming II
   Topic 2: Recursive function

   What students learn here:
     1. Review: function with / without a return value,
        local vs global variable
     2. What recursion is: a function that calls ITSELF
     3. The 2 compulsory parts:
            - the BASE CASE   (when we stop)
            - the GENERAL CASE (when we call again, but SMALLER)
     4. Classic examples: factorial, Fibonacci, sum, digits
     5. Direct vs indirect recursion
     6. Recursion vs loop: same result, different thinking

   THE GOLDEN RULE
     Every recursive call must get CLOSER to the base case.
     If it does not, the program crashes (stack overflow).

   Compile:  g++ L2-Recursive.cpp -o L2
   ============================================================ */

#include <iostream>
using namespace std;

int callCount = 0;      // a GLOBAL variable, to count the calls

/* ============================================================
   1. FACTORIAL
        n! = 1                    if n <= 1     <- BASE CASE
        n! = n * (n-1)!           if n >  1     <- GENERAL CASE
   ============================================================ */

long factorial(int n)
{
    if (n <= 1)
        return 1;                      // BASE CASE: stop here
    else
        return n * factorial(n - 1);   // GENERAL CASE: call itself
}

/* How does factorial(4) work?

     factorial(4) = 4 * factorial(3)
                        factorial(3) = 3 * factorial(2)
                                           factorial(2) = 2 * factorial(1)
                                                              factorial(1) = 1
     Then everything comes back:
                                           factorial(2) = 2 * 1 = 2
                        factorial(3) = 3 * 2 = 6
     factorial(4) = 4 * 6 = 24                                            */

/* ============================================================
   2. FIBONACCI
        U(n) = 1                       if n = 1 or n = 2
        U(n) = U(n-1) + U(n-2)         if n >= 3
        0, 1, 1, 2, 3, 5, 8, 13, 21, 34 ...
   ============================================================ */

long fibo(int n)
{
    callCount++;                       // to show how many calls are made
    if (n == 1 || n == 2)
        return 1;
    return fibo(n - 1) + fibo(n - 2);  // TWO recursive calls
}

/* ============================================================
   3. SUM 1 + 2 + ... + n
        S(n) = 1                if n = 1
        S(n) = n + S(n-1)       if n > 1
   ============================================================ */

int sumTo(int n)
{
    if (n <= 1)
        return 1;
    return n + sumTo(n - 1);
}

/* ============================================================
   4. SUM 2 + 4 + 6 + ... + n     (practice of the lecture)
   ============================================================ */

int sumEven(int n)
{
    if (n <= 0)
        return 0;
    if (n % 2 != 0)
        n = n - 1;                     // make sure n is even
    return n + sumEven(n - 2);
}

/* ============================================================
   5. COUNT THE DIGITS of a number
        1 digit                 if n < 10
        1 + digits(n / 10)      otherwise
   ============================================================ */

int countDigits(int n)
{
    if (n < 0) n = -n;
    if (n < 10)
        return 1;
    return 1 + countDigits(n / 10);
}

/* ============================================================
   6. DISPLAY "Hello 1 ... Hello n"   (a recursive PROCEDURE:
      it returns nothing, it just does something)
   ============================================================ */

void sayHello(int n)
{
    if (n <= 0)
        return;                        // base case: do nothing, go back
    sayHello(n - 1);                   // first the smaller ones ...
    cout << "Hello " << n << endl;     // ... then me
}

/* Try to move the cout BEFORE the call: the order is reversed!
   That is the whole difference between doing the work on the
   way DOWN or on the way BACK UP.                              */

/* ============================================================
   7. POWER  x^n
   ============================================================ */

double power(double x, int n)
{
    if (n == 0)
        return 1;
    return x * power(x, n - 1);
}

/* ============================================================
   8. REVERSE A STRING (recursion on text)
   ============================================================ */

void printReverse(string s, int i)
{
    if (i < 0)
        return;
    cout << s[i];
    printReverse(s, i - 1);
}

/* ============================================================
   9. DIRECT vs INDIRECT recursion
        Direct   : f calls f
        Indirect : f calls g, and g calls f
   ============================================================ */

int g_func(int x);                     // prototype needed: f uses g

int f_func(int x)                      // f(x) = 1 if x = 1, else g(x)+2
{
    if (x <= 1) return 1;
    return g_func(x) + 2;
}

int g_func(int x)                      // g(x) = 0 if x = 2, else f(x-1)-1
{
    if (x <= 2) return 0;
    return f_func(x - 1) - 1;
}

/* ============================================================
   MAIN
   ============================================================ */

int main()
{
    cout << "=== 1. Factorial ===" << endl;
    for (int i = 1; i <= 8; i++)
        cout << i << "! = " << factorial(i) << endl;

    cout << "\n=== 2. Fibonacci ===" << endl;
    cout << "The first 10 terms: ";
    for (int i = 1; i <= 10; i++)
        cout << fibo(i) << " ";
    cout << endl;

    callCount = 0;
    cout << "fibo(20) = " << fibo(20)
         << " and it needed " << callCount << " calls!" << endl;
    cout << "(recursion is elegant, but here it is very slow:"
         << " it computes the same values again and again)" << endl;

    cout << "\n=== 3. Summations ===" << endl;
    cout << "1+2+...+10       = " << sumTo(10)   << endl;
    cout << "2+4+...+10       = " << sumEven(10) << endl;

    cout << "\n=== 4. Count digits ===" << endl;
    int n;
    cout << "Enter a number: ";
    cin  >> n;
    cout << n << " has " << countDigits(n) << " digit(s)" << endl;

    cout << "\n=== 5. A recursive procedure ===" << endl;
    sayHello(5);

    cout << "\n=== 6. Power ===" << endl;
    cout << "2^10 = " << power(2, 10) << endl;
    cout << "3^4  = " << power(3, 4)  << endl;

    cout << "\n=== 7. Reverse a word ===" << endl;
    string word;
    cout << "Enter a word: ";
    cin  >> word;
    cout << "Reversed: ";
    printReverse(word, word.length() - 1);
    cout << endl;

    cout << "\n=== 8. Indirect recursion ===" << endl;
    for (int i = 1; i <= 5; i++)
        cout << "f(" << i << ") = " << f_func(i) << endl;

    cout << "\n=== 9. Recursion vs loop ===" << endl;

    // the same factorial written with a loop
    long f = 1;
    for (int i = 2; i <= 8; i++) f *= i;
    cout << "8! with a loop      = " << f << endl;
    cout << "8! with recursion   = " << factorial(8) << endl;
    cout << "Same answer. The loop is faster, the recursion is"
         << " often shorter and closer to the mathematical formula."
         << endl;

    return 0;
}

/* ============================================================
   PRACTICE

   1. Write a recursive function that computes (2+4+6+...+n)/n.
   2. Write a recursive function sumDigits(int n) that adds all
      the digits of a number.   sumDigits(1234) -> 10
   3. Write a recursive function that displays a number in
      reverse order.           reverse(1234) -> 4321
   4. Write a recursive function gcd(a, b) (greatest common
      divisor):  gcd(a, 0) = a  and  gcd(a, b) = gcd(b, a % b)
   5. Write a recursive function that counts how many times a
      character c appears inside a string s.
   6. What happens if you remove the base case from factorial()?
      Try it and explain the error message.
   ============================================================ */
