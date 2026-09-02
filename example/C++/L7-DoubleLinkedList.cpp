/* ============================================================
   Data Structure & Programming II
   Topic 7: Double Linked List (DLL)

   What students learn here:
     1. A node with THREE parts: previous | data | next
     2. Why it is better: we can walk FORWARD and BACKWARD
     3. insertBegin / insertEnd / insertAt
     4. deleteBegin / deleteEnd  (now deleteEnd is FAST!)
     5. displayForward / displayBackward
     6. The rule: when you touch one arrow, do not forget
        the arrow that comes back

   THE PICTURE

              head                                     tail
                |                                        |
                v                                        v
       NULL <--|A|--> <--|B|--> <--|C|--> NULL
             prev next  prev next  prev next

   Compile:  g++ L7-DoubleLinkedList.cpp -o L7
   ============================================================ */

#include <iostream>
using namespace std;

/* ============================================================
   1. THE STRUCTURES
      The only difference with Topic 5/6 is the extra pointer
      "previous". Everything else is the same idea.
   ============================================================ */

struct Element {
    int      data;
    Element *next;        // the element AFTER  me
    Element *previous;    // the element BEFORE me   <- the new one
};

struct List {
    Element *head;
    Element *tail;
    int      n;
};

/* -------- prototypes -------- */
List *createList();
void  insertBegin      (List *ls, int d);
void  insertEnd        (List *ls, int d);
void  insertAfterValue (List *ls, int target, int d);
void  deleteBegin      (List *ls);
void  deleteEnd        (List *ls);
void  displayForward   (List *ls);
void  displayBackward  (List *ls);
void  destroyList      (List *ls);

int main()
{
    /* ============================================================
       2. BUILD A LIST
       ============================================================ */

    cout << "=== 1. Build a double linked list ===" << endl;

    List *ls = createList();

    insertEnd(ls, 10);
    insertEnd(ls, 20);
    insertEnd(ls, 30);
    insertBegin(ls, 5);

    displayForward(ls);
    displayBackward(ls);

    /* ============================================================
       3. THE BIG ADVANTAGE: read the list in both directions
          In a SINGLE linked list, displayBackward() would be
          impossible without extra work: from an element we could
          never go back.
       ============================================================ */

    /* ============================================================
       4. INSERT AFTER A GIVEN VALUE
          This is where we must be careful with FOUR arrows.
       ============================================================ */

    cout << "\n=== 2. Insert 25 after the value 20 ===" << endl;

    insertAfterValue(ls, 20, 25);
    displayForward(ls);
    displayBackward(ls);

    /* ============================================================
       5. DELETIONS
       ============================================================ */

    cout << "\n=== 3. Deletions ===" << endl;

    deleteBegin(ls);
    cout << "after deleteBegin() : "; displayForward(ls);

    deleteEnd(ls);
    cout << "after deleteEnd()   : "; displayForward(ls);
    cout << "                      ";  displayBackward(ls);

    /* NOTE: here deleteEnd() is IMMEDIATE.
       We just do  tail = tail->previous  -  no walking!
       In a single linked list we had to walk the whole list. */

    /* ============================================================
       6. EXERCISE OF THE LECTURE:
          store the English alphabet A-Z and display it
          from A to Z and from Z to A.
       ============================================================ */

    cout << "\n=== 4. The alphabet, forward and backward ===" << endl;

    List *alpha = createList();
    for (int i = 0; i < 26; i++)
        insertEnd(alpha, 'A' + i);      // 65, 66, 67 ... (ASCII)

    cout << "A to Z : ";
    Element *tmp = alpha->head;
    while (tmp != NULL) { cout << (char)tmp->data; tmp = tmp->next; }
    cout << endl;

    cout << "Z to A : ";
    tmp = alpha->tail;
    while (tmp != NULL) { cout << (char)tmp->data; tmp = tmp->previous; }
    cout << endl;

    /* ============================================================
       7. LET THE USER PLAY
       ============================================================ */

    cout << "\n=== 5. Store scores of students ===" << endl;

    List *scores = createList();
    int howMany, value;

    cout << "How many scores? ";
    cin  >> howMany;

    for (int i = 1; i <= howMany; i++) {
        cout << "Score #" << i << ": ";
        cin  >> value;
        insertEnd(scores, value);
    }

    displayForward(scores);
    displayBackward(scores);

    int sum = 0;
    tmp = scores->head;
    while (tmp != NULL) { sum += tmp->data; tmp = tmp->next; }
    if (scores->n > 0)
        cout << "Average = " << (float)sum / scores->n << endl;

    /* ============================================================
       8. CLEAN UP
       ============================================================ */

    destroyList(ls);      delete ls;
    destroyList(alpha);   delete alpha;
    destroyList(scores);  delete scores;

    cout << "\nMemory cleaned." << endl;
    return 0;
}

/* ============================================================
   createList
   ============================================================ */
List *createList()
{
    List *ls = new List;
    ls->head = NULL;
    ls->tail = NULL;
    ls->n    = 0;
    return ls;
}

/* ============================================================
   insertBegin
        Before : NULL <- [10] <-> [20] -> NULL
        After  : NULL <- [5] <-> [10] <-> [20] -> NULL

        Arrows to set:
           E->previous = NULL         (E is the first now)
           E->next     = old head
           old head->previous = E     <- DO NOT FORGET THIS ONE
           head = E
   ============================================================ */
void insertBegin(List *ls, int d)
{
    Element *E  = new Element;
    E->data     = d;
    E->previous = NULL;
    E->next     = ls->head;

    if (ls->head != NULL)
        ls->head->previous = E;        // the old first looks back at E
    else
        ls->tail = E;                  // the list was empty

    ls->head = E;
    ls->n++;
}

/* ============================================================
   insertEnd
        Symmetric of insertBegin:
           E->next     = NULL
           E->previous = old tail
           old tail->next = E
           tail = E
   ============================================================ */
void insertEnd(List *ls, int d)
{
    Element *E  = new Element;
    E->data     = d;
    E->next     = NULL;
    E->previous = ls->tail;

    if (ls->tail != NULL)
        ls->tail->next = E;
    else
        ls->head = E;                  // the list was empty

    ls->tail = E;
    ls->n++;
}

/* ============================================================
   insertAfterValue : put d just after the first element == target

        Before :  ... <-> [P] <-> [Q] <-> ...
        After  :  ... <-> [P] <-> [E] <-> [Q] <-> ...

        FOUR arrows change:
           E->previous = P        E->next = Q
           P->next     = E        Q->previous = E
   ============================================================ */
void insertAfterValue(List *ls, int target, int d)
{
    Element *P = ls->head;
    while (P != NULL && P->data != target)
        P = P->next;

    if (P == NULL) {
        cout << "Value " << target << " not found." << endl;
        return;
    }

    if (P == ls->tail) {               // insert after the last one
        insertEnd(ls, d);
        return;
    }

    Element *Q = P->next;
    Element *E = new Element;
    E->data = d;

    E->previous = P;
    E->next     = Q;
    P->next     = E;
    Q->previous = E;

    ls->n++;
}

/* ============================================================
   deleteBegin
        head moves to the second element,
        and that second element must forget its "previous".
   ============================================================ */
void deleteBegin(List *ls)
{
    if (ls->n == 0) { cout << "(empty list) "; return; }

    Element *tmp = ls->head;
    ls->head = tmp->next;

    if (ls->head != NULL)
        ls->head->previous = NULL;
    else
        ls->tail = NULL;               // the list became empty

    delete tmp;
    ls->n--;
}

/* ============================================================
   deleteEnd - FAST here, thanks to "previous"
   ============================================================ */
void deleteEnd(List *ls)
{
    if (ls->n == 0) { cout << "(empty list) "; return; }

    Element *tmp = ls->tail;
    ls->tail = tmp->previous;          // ONE step back, no walking

    if (ls->tail != NULL)
        ls->tail->next = NULL;
    else
        ls->head = NULL;

    delete tmp;
    ls->n--;
}

/* ============================================================
   displayForward : start at head, follow "next"
   ============================================================ */
void displayForward(List *ls)
{
    Element *tmp = ls->head;

    if (tmp == NULL) { cout << "(empty list)" << endl; return; }

    cout << "forward  : NULL <-> ";
    while (tmp != NULL) {
        cout << tmp->data << " <-> ";
        tmp = tmp->next;
    }
    cout << "NULL   [n = " << ls->n << "]" << endl;
}

/* ============================================================
   displayBackward : start at tail, follow "previous"
   ============================================================ */
void displayBackward(List *ls)
{
    Element *tmp = ls->tail;

    if (tmp == NULL) { cout << "(empty list)" << endl; return; }

    cout << "backward : NULL <-> ";
    while (tmp != NULL) {
        cout << tmp->data << " <-> ";
        tmp = tmp->previous;
    }
    cout << "NULL" << endl;
}

/* ============================================================
   destroyList
   ============================================================ */
void destroyList(List *ls)
{
    while (ls->n > 0)
        deleteBegin(ls);
}

/* ============================================================
   SINGLE vs DOUBLE linked list

     memory     : DLL uses one more pointer per element
     backward   : SLL impossible        DLL easy
     deleteEnd  : SLL O(n) (walk)       DLL O(1) (one step)
     code       : SLL simpler           DLL more arrows to manage

   PRACTICE

   1. Write deleteValue(List *ls, int d) for a double linked list.
   2. Write a function that says whether the list is a palindrome
      (the same read forward and backward). Use head and tail
      moving towards each other.
   3. Store 5 students (name, age) in a double linked list and
      display them from the first to the last, then backward.
   4. Write insertSorted() so that the list is always sorted.
   5. Make the list CIRCULAR: tail->next = head and
      head->previous = tail. What has to change in display()?
   ============================================================ */
