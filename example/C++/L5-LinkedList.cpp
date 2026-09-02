/* ============================================================
   Data Structure & Programming II
   Topic 5: Linked List (part 1)

   What students learn here:
     1. Why an array is not always enough
     2. The two structures: Element (a node) and List
     3. head, tail, next, NULL, and n (the counter)
     4. Creating an empty list
     5. Creating ONE element with "new"
     6. insertBegin() - add at the beginning
     7. display()     - walk through the list until NULL
     8. Drawing what happens in memory at every step

   THE PICTURE TO KEEP IN MIND

        head                                        tail
         |                                            |
         v                                            v
      +------+----+   +------+----+   +------+------+
      |  5   | *--|-->|  8   | *--|-->|  12  | NULL |
      +------+----+   +------+----+   +------+------+
       data   next     data   next     data   next

   Compile:  g++ L5-LinkedList.cpp -o L5
   ============================================================ */

#include <iostream>
using namespace std;

/* ============================================================
   1. THE TWO STRUCTURES

      Element = one box of the chain: a value + the address of
                the next box.
      List    = the "manager": it remembers where the chain
                starts (head), where it ends (tail), and how
                many elements it contains (n).
   ============================================================ */

struct Element {
    int      data;        // the value we want to store
    Element *next;        // the ADDRESS of the next element
};

struct List {
    Element *head;        // the first element
    Element *tail;        // the last element
    int      n;           // how many elements
};

/* ============================================================
   2. ARRAY vs LINKED LIST

      ARRAY                        LINKED LIST
      -----                        -----------
      fixed size                   grows and shrinks at run time
      elements side by side        elements anywhere in memory
      arr[7] is immediate  O(1)    must walk from head       O(n)
      insert in the middle:        insert in the middle:
        move everything            just change 2 pointers
   ============================================================ */

/* -------- prototypes -------- */
List *createList();
void  insertBegin(List *ls, int d);
void  display(List *ls);
void  displayInfo(List *ls);

int main()
{
    /* ============================================================
       3. CREATE AN EMPTY LIST
       ============================================================ */

    cout << "=== 1. Create an empty list ===" << endl;

    List *ls = createList();
    displayInfo(ls);
    display(ls);

    /* ============================================================
       4. UNDERSTAND ONE SINGLE ELEMENT FIRST
          (before using the functions, let us do it by hand)
       ============================================================ */

    cout << "\n=== 2. One element, made by hand ===" << endl;

    Element *tmp = new Element;     // ask the memory for one box
    tmp->data = 5;                  // -> is the dot for POINTERS
    tmp->next = NULL;               // there is nothing after it

    cout << "tmp->data = " << tmp->data << endl;
    cout << "tmp->next = " << tmp->next << " (NULL = end of the chain)"
         << endl;

    delete tmp;                     // we free it, the real list follows

    /* REMEMBER:
           object.field       when we have the object itself
           pointer->field     when we have a POINTER to the object
       tmp->data is exactly the same as (*tmp).data                 */

    /* ============================================================
       5. INSERT AT THE BEGINNING, STEP BY STEP
       ============================================================ */

    cout << "\n=== 3. Insert at the beginning ===" << endl;

    insertBegin(ls, 12);   cout << "after insertBegin(12): "; display(ls);
    insertBegin(ls,  8);   cout << "after insertBegin(8) : "; display(ls);
    insertBegin(ls,  5);   cout << "after insertBegin(5) : "; display(ls);

    displayInfo(ls);

    /* Notice the ORDER: we inserted 12, then 8, then 5,
       and the list reads 5 -> 8 -> 12.
       Inserting at the beginning REVERSES the order of arrival. */

    /* ============================================================
       6. LET THE USER FILL THE LIST
       ============================================================ */

    cout << "\n=== 4. Fill a list from the keyboard ===" << endl;

    List *myList = createList();
    int howMany, value;

    cout << "How many numbers do you want to insert? ";
    cin  >> howMany;

    for (int i = 1; i <= howMany; i++) {
        cout << "Value #" << i << ": ";
        cin  >> value;
        insertBegin(myList, value);
    }

    cout << "Your list: ";
    display(myList);
    displayInfo(myList);

    /* ============================================================
       7. WALKING THROUGH A LIST - THE PATTERN TO MEMORISE

              Element *tmp = ls->head;      start at the first
              while (tmp != NULL) {         until the end
                  ... use tmp->data ...
                  tmp = tmp->next;          go one step forward
              }

          You will use this pattern in EVERY exercise:
          display, search, count, sum, delete ...
       ============================================================ */

    cout << "\n=== 5. Using the pattern: sum and maximum ===" << endl;

    int sum = 0, max = 0;
    Element *cur = myList->head;

    if (cur == NULL) {
        cout << "The list is empty." << endl;
    } else {
        max = cur->data;
        while (cur != NULL) {
            sum += cur->data;
            if (cur->data > max) max = cur->data;
            cur = cur->next;
        }
        cout << "Sum     = " << sum << endl;
        cout << "Maximum = " << max << endl;
        cout << "Average = " << (float)sum / myList->n << endl;
    }

    return 0;
}

/* ============================================================
   createList()
   Steps:
     1. ask the memory for a List
     2. n = 0 (it is empty)
     3. head points to nothing
     4. tail points to nothing
     5. give the list back
   ============================================================ */
List *createList()
{
    List *ls = new List;
    ls->n    = 0;
    ls->head = NULL;
    ls->tail = NULL;
    return ls;
}

/* ============================================================
   insertBegin(ls, d)
   Steps (follow them with a drawing!):
     1. create a new element E and put d inside
     2. E->next points to the OLD head
     3. the head of the list becomes E
     4. if the list was empty, E is also the tail
     5. n = n + 1
   ============================================================ */
void insertBegin(List *ls, int d)
{
    Element *E = new Element;      // 1
    E->data = d;

    E->next = ls->head;            // 2  (if the list was empty: E->next=NULL)
    ls->head = E;                  // 3

    if (ls->n == 0)                // 4
        ls->tail = E;

    ls->n = ls->n + 1;             // 5
}

/* ============================================================
   display(ls) : walk from head to NULL
   ============================================================ */
void display(List *ls)
{
    Element *tmp = ls->head;

    if (tmp == NULL) {
        cout << "(the list is empty)" << endl;
        return;
    }

    cout << "head -> ";
    while (tmp != NULL) {
        cout << tmp->data << " -> ";
        tmp = tmp->next;
    }
    cout << "NULL" << endl;
}

/* ============================================================
   displayInfo(ls) : show head, tail and n
   ============================================================ */
void displayInfo(List *ls)
{
    cout << "   n = " << ls->n;
    if (ls->head != NULL) cout << ", head->data = " << ls->head->data;
    if (ls->tail != NULL) cout << ", tail->data = " << ls->tail->data;
    cout << endl;
}

/* ============================================================
   PRACTICE

   1. Write countElements(List *ls) that walks the list and
      counts the elements WITHOUT using ls->n. Compare the
      two results.
   2. Write displayEven(List *ls) that shows only the even values.
   3. Change the type of "data" from int to float, then build a
      list of student scores and compute the average.
   4. Build a list with the numbers 1 to 10 using insertBegin().
      In which order do they appear? Why?
   5. (Next lesson) How would you add an element at the END
      instead of the beginning? Draw it first, then code it.
   ============================================================ */
