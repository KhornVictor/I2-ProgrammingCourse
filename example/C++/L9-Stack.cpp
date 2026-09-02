/* ============================================================
   Data Structure & Programming II
   Topic 9: Stack (LIFO)

   What students learn here:
     1. LIFO = Last In, First Out
        (a stack of plates: the last one put is the first taken)
     2. The 5 operations:
            push     add on the TOP
            pop      remove from the TOP
            peek     look at the top without removing
            isEmpty  is it empty?
            size     how many elements
     3. Two implementations: array and linked list
     4. Real applications:
            - reverse a text
            - check that brackets are balanced
            - convert a number into binary
            - undo in an editor, the "call stack" of functions

     Choice used here (recommended in the lecture):
            push -> insert at the BEGINNING of the list
            pop  -> delete from the BEGINNING of the list
            (both are O(1): the fastest possible)

   Compile:  g++ L9-Stack.cpp -o L9
   ============================================================ */

#include <iostream>
#include <string>
using namespace std;

/* ============================================================
   PART A - STACK AS AN ARRAY
      "top" is the index of the last element pushed.
      top = -1 means the stack is empty.
   ============================================================ */

const int MAXSIZE = 100;

struct StackArray {
    int data[MAXSIZE];
    int top;
};

void initStackA(StackArray &s) { s.top = -1; }
bool isEmptyA  (StackArray &s) { return s.top == -1; }
bool isFullA   (StackArray &s) { return s.top == MAXSIZE - 1; }

void pushA(StackArray &s, int value)
{
    if (isFullA(s)) { cout << "Stack overflow!" << endl; return; }
    s.top++;
    s.data[s.top] = value;
}

int popA(StackArray &s)
{
    if (isEmptyA(s)) { cout << "Stack underflow!" << endl; return -1; }
    int value = s.data[s.top];
    s.top--;
    return value;
}

int peekA(StackArray &s)
{
    if (isEmptyA(s)) return -1;
    return s.data[s.top];
}

/* ============================================================
   PART B - STACK AS A LINKED LIST
      top = head of the list
   ============================================================ */

struct Element {
    char     data;
    Element *next;
};

struct Stack {
    Element *top;
    int      n;
};

Stack *createStack()
{
    Stack *s = new Stack;
    s->top = NULL;
    s->n   = 0;
    return s;
}

bool isEmpty(Stack *s) { return s->n == 0; }
int  size   (Stack *s) { return s->n;      }

/* push = insert at the beginning of the list */
void push(Stack *s, char value)
{
    Element *E = new Element;
    E->data = value;
    E->next = s->top;        // the new element points to the old top
    s->top  = E;             // and becomes the new top
    s->n++;
}

/* pop = delete from the beginning of the list */
char pop(Stack *s)
{
    if (isEmpty(s)) {
        cout << "The stack is empty!" << endl;
        return '\0';
    }

    Element *tmp = s->top;
    char value   = tmp->data;

    s->top = s->top->next;
    delete tmp;
    s->n--;

    return value;
}

char peek(Stack *s)
{
    if (isEmpty(s)) return '\0';
    return s->top->data;
}

void display(Stack *s)
{
    Element *tmp = s->top;
    cout << "  top -> [ ";
    while (tmp != NULL) {
        cout << tmp->data << " ";
        tmp = tmp->next;
    }
    cout << "]   (" << s->n << " element(s))" << endl;
}

/* ============================================================
   MAIN
   ============================================================ */

int main()
{
    /* ------------------------------------------------------------
       1. STACK AS AN ARRAY
       ------------------------------------------------------------ */

    cout << "=== 1. Stack as an ARRAY ===" << endl;

    StackArray sa;
    initStackA(sa);

    cout << "push 10, push 5, push 16" << endl;
    pushA(sa, 10);
    pushA(sa,  5);
    pushA(sa, 16);

    cout << "peek -> " << peekA(sa) << "  (the last one pushed)" << endl;
    cout << "pop  -> " << popA(sa)  << endl;
    cout << "pop  -> " << popA(sa)  << endl;
    cout << "pop  -> " << popA(sa)  << endl;
    popA(sa);                          // one pop too many

    /* ------------------------------------------------------------
       2. STACK AS A LINKED LIST
       ------------------------------------------------------------ */

    cout << "\n=== 2. Stack as a LINKED LIST ===" << endl;

    Stack *s = createStack();

    push(s, 'A');  cout << "push('A') "; display(s);
    push(s, 'B');  cout << "push('B') "; display(s);
    push(s, 'C');  cout << "push('C') "; display(s);

    cout << "peek()    -> " << peek(s) << endl;
    cout << "pop()     -> " << pop(s)  << endl;
    display(s);

    /* ------------------------------------------------------------
       3. APPLICATION 1: reverse a word
          Push every letter, then pop them: they come out
          in the opposite order. THIS is what a stack does best.
       ------------------------------------------------------------ */

    cout << "\n=== 3. Reverse a word with a stack ===" << endl;

    Stack *rev = createStack();
    string word;

    cout << "Enter a word: ";
    cin  >> word;

    for (int i = 0; i < (int)word.length(); i++)
        push(rev, word[i]);

    cout << "Reversed    : ";
    while (!isEmpty(rev))
        cout << pop(rev);
    cout << endl;

    /* ------------------------------------------------------------
       4. APPLICATION 2: are the brackets balanced?
          Every opening bracket is pushed.
          Every closing bracket must match the top of the stack.
          At the end the stack must be empty.
       ------------------------------------------------------------ */

    cout << "\n=== 4. Check the brackets ===" << endl;

    Stack *br = createStack();
    string expr;

    cout << "Enter an expression, e.g. { a[ i ] + ( b * 2 ) } : ";
    cin.ignore();                     // clear the Enter left by cin >>
    getline(cin, expr);

    bool ok = true;

    for (int i = 0; i < (int)expr.length() && ok; i++) {
        char c = expr[i];

        if (c == '(' || c == '[' || c == '{') {
            push(br, c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (isEmpty(br)) {
                ok = false;                 // a closing one with no opening
            } else {
                char open = pop(br);
                if ((c == ')' && open != '(') ||
                    (c == ']' && open != '[') ||
                    (c == '}' && open != '{'))
                    ok = false;             // wrong kind of bracket
            }
        }
    }

    if (!isEmpty(br)) ok = false;           // some brackets were never closed

    if (ok) cout << "The brackets are balanced. OK" << endl;
    else    cout << "The brackets are NOT balanced. ERROR" << endl;

    /* ------------------------------------------------------------
       5. APPLICATION 3: decimal -> binary
          We compute the remainders, but they come in the WRONG
          order. A stack puts them back in the right order.
       ------------------------------------------------------------ */

    cout << "\n=== 5. Convert a number into binary ===" << endl;

    Stack *bin = createStack();
    int n;

    cout << "Enter a positive number: ";
    cin  >> n;

    int copy = n;
    if (n == 0) push(bin, '0');

    while (n > 0) {
        push(bin, (char)('0' + n % 2));    // push the remainder
        n = n / 2;
    }

    cout << copy << " in binary is ";
    while (!isEmpty(bin))
        cout << pop(bin);
    cout << endl;

    /* ------------------------------------------------------------
       6. STACK vs QUEUE - the one thing to remember

              STACK (LIFO)              QUEUE (FIFO)
              push on the top           enqueue at the rear
              pop from the top          dequeue from the front
              REVERSES the order        KEEPS the order
              undo, back button         printer, waiting line
       ------------------------------------------------------------ */

    delete s; delete rev; delete br; delete bin;
    return 0;
}

/* ============================================================
   PRACTICE

   1. Write a function that says whether a word is a PALINDROME
      (madam, level, radar) using a stack.
   2. Convert a decimal number into hexadecimal with a stack.
   3. Build a stack of struct Action { string name; } and write
      a small "undo" system: do / do / do / undo / undo.
   4. Use a stack to reverse the elements of a QUEUE.
   5. Why is a stack the perfect structure to remember the
      pages visited in a web browser (the "back" button)?
   6. Look at the recursion of Topic 2 again: the computer uses
      a stack to remember every call. Draw the stack of
      factorial(4).
   ============================================================ */
