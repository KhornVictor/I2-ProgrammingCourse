/* ============================================================
   Data Structure & Programming II
   Topic 6: Linked List (part 2) - the complete set of operations

   What students learn here:
     1. insertEnd()      add at the end       (uses tail)
     2. insertAt()       add at a position
     3. search()         find a value
     4. deleteBegin()    remove the first element
     5. deleteEnd()      remove the last element  (the hard one!)
     6. deleteValue()    remove a chosen value
     7. destroyList()    remove everything
     8. reverseList()    turn the chain around
     9. A menu to test everything

   THE RULE OF LINKED LISTS
       Before you write a single line of code, DRAW the list
       before and after. Then translate your drawing into
       pointer assignments. Never the other way around.

   Compile:  g++ L6-LinkedList2.cpp -o L6
   ============================================================ */

#include <iostream>
using namespace std;

struct Element {
    int      data;
    Element *next;
};

struct List {
    Element *head;
    Element *tail;
    int      n;
};

/* -------- prototypes -------- */
List *createList();
void  insertBegin (List *ls, int d);
void  insertEnd   (List *ls, int d);
void  insertAt    (List *ls, int d, int pos);
int   search      (List *ls, int d);
void  deleteBegin (List *ls);
void  deleteEnd   (List *ls);
void  deleteValue (List *ls, int d);
void  destroyList (List *ls);
void  reverseList (List *ls);
void  display     (List *ls);

int main()
{
    List *ls = createList();

    /* ============================================================
       1. BUILD A LIST WITH insertEnd()
          This time the order of arrival is KEPT.
       ============================================================ */

    cout << "=== 1. insertEnd keeps the order ===" << endl;

    insertEnd(ls, 10);
    insertEnd(ls, 20);
    insertEnd(ls, 30);
    insertEnd(ls, 40);
    display(ls);

    /* ============================================================
       2. insertBegin() and insertAt()
       ============================================================ */

    cout << "\n=== 2. insertBegin and insertAt ===" << endl;

    insertBegin(ls, 5);
    cout << "insertBegin(5)   : "; display(ls);

    insertAt(ls, 25, 4);            // put 25 at position 4 (1 = first)
    cout << "insertAt(25, 4)  : "; display(ls);

    /* ============================================================
       3. SEARCH
       ============================================================ */

    cout << "\n=== 3. Search ===" << endl;

    int target;
    cout << "Which value do you look for? ";
    cin  >> target;

    int pos = search(ls, target);
    if (pos > 0)
        cout << target << " was found at position " << pos << endl;
    else
        cout << target << " is not in the list." << endl;

    /* ============================================================
       4. DELETIONS
       ============================================================ */

    cout << "\n=== 4. Deletions ===" << endl;

    cout << "start            : "; display(ls);

    deleteBegin(ls);
    cout << "deleteBegin()    : "; display(ls);

    deleteEnd(ls);
    cout << "deleteEnd()      : "; display(ls);

    deleteValue(ls, 25);
    cout << "deleteValue(25)  : "; display(ls);

    /* ============================================================
       5. REVERSE
       ============================================================ */

    cout << "\n=== 5. Reverse the list ===" << endl;

    insertEnd(ls, 50);
    insertEnd(ls, 60);
    cout << "before  : "; display(ls);
    reverseList(ls);
    cout << "after   : "; display(ls);

    /* ============================================================
       6. AN INTERACTIVE MENU
       ============================================================ */

    cout << "\n=== 6. Try it yourself ===" << endl;

    List *my = createList();
    int choice, value, position;

    do {
        cout << "\n--------- LINKED LIST MENU ---------" << endl;
        cout << "1- Insert at the beginning" << endl;
        cout << "2- Insert at the end" << endl;
        cout << "3- Insert at a position" << endl;
        cout << "4- Search a value" << endl;
        cout << "5- Delete the first" << endl;
        cout << "6- Delete the last" << endl;
        cout << "7- Delete a value" << endl;
        cout << "8- Reverse" << endl;
        cout << "9- Display" << endl;
        cout << "0- Quit" << endl;
        cout << "Your choice: ";
        cin  >> choice;

        switch (choice) {
            case 1:
                cout << "Value: "; cin >> value;
                insertBegin(my, value); display(my); break;
            case 2:
                cout << "Value: "; cin >> value;
                insertEnd(my, value); display(my); break;
            case 3:
                cout << "Value: ";    cin >> value;
                cout << "Position: "; cin >> position;
                insertAt(my, value, position); display(my); break;
            case 4:
                cout << "Value: "; cin >> value;
                position = search(my, value);
                if (position > 0) cout << "Found at position " << position << endl;
                else              cout << "Not found." << endl;
                break;
            case 5: deleteBegin(my); display(my); break;
            case 6: deleteEnd(my);   display(my); break;
            case 7:
                cout << "Value: "; cin >> value;
                deleteValue(my, value); display(my); break;
            case 8: reverseList(my); display(my); break;
            case 9: display(my); break;
            case 0: break;
            default: cout << "No such choice." << endl;
        }

    } while (choice != 0);

    /* ============================================================
       7. CLEAN THE MEMORY BEFORE LEAVING
          Every "new" must have its "delete".
       ============================================================ */

    destroyList(ls);
    destroyList(my);
    delete ls;
    delete my;
    cout << "\nMemory cleaned. Bye!" << endl;

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
        head -> [5] -> [8] -> NULL
        we add E:   E->next = head ;  head = E
   ============================================================ */
void insertBegin(List *ls, int d)
{
    Element *E = new Element;
    E->data = d;
    E->next = ls->head;
    ls->head = E;

    if (ls->n == 0) ls->tail = E;
    ls->n++;
}

/* ============================================================
   insertEnd
        Before : ... -> [30] -> NULL       (tail points to 30)
        After  : ... -> [30] -> [40] -> NULL

        1. if the list is empty -> it is the same as insertBegin
        2. create E, E->next = NULL
        3. the old tail must point to E
        4. E becomes the new tail
   ============================================================ */
void insertEnd(List *ls, int d)
{
    if (ls->n == 0) {              // 1
        insertBegin(ls, d);
        return;
    }

    Element *E = new Element;      // 2
    E->data = d;
    E->next = NULL;

    ls->tail->next = E;            // 3
    ls->tail = E;                  // 4
    ls->n++;
}

/* ============================================================
   insertAt : position 1 = the first element
        We stop on the element JUST BEFORE the wanted position,
        then we hook the new element between the two.
   ============================================================ */
void insertAt(List *ls, int d, int pos)
{
    if (pos <= 1)          { insertBegin(ls, d); return; }
    if (pos >  ls->n)      { insertEnd(ls, d);   return; }

    Element *prev = ls->head;
    for (int i = 1; i < pos - 1; i++)     // walk to the (pos-1)th element
        prev = prev->next;

    Element *E = new Element;
    E->data = d;
    E->next = prev->next;      // E points to what came after prev
    prev->next = E;            // prev now points to E
    ls->n++;
}

/* ============================================================
   search : returns the position (1, 2, 3 ...) or -1
   ============================================================ */
int search(List *ls, int d)
{
    Element *tmp = ls->head;
    int pos = 1;

    while (tmp != NULL) {
        if (tmp->data == d)
            return pos;
        tmp = tmp->next;
        pos++;
    }
    return -1;                 // walked everything, not found
}

/* ============================================================
   deleteBegin
        Before : head -> [5] -> [8] -> ...
        1. keep the address of the first element in tmp
        2. head jumps to the second element
        3. free tmp
   ============================================================ */
void deleteBegin(List *ls)
{
    if (ls->n == 0) { cout << "(list already empty) "; return; }

    Element *tmp = ls->head;       // 1
    ls->head = ls->head->next;     // 2
    delete tmp;                    // 3
    ls->n--;

    if (ls->n == 0) ls->tail = NULL;   // the list became empty
}

/* ============================================================
   deleteEnd  - the difficult one!
        In a SINGLE linked list we cannot go backwards.
        So to delete the last element we must walk to the
        element BEFORE the last one (position n-1).
   ============================================================ */
void deleteEnd(List *ls)
{
    if (ls->n == 0) { cout << "(list already empty) "; return; }

    if (ls->n == 1) {              // only one element
        deleteBegin(ls);
        return;
    }

    Element *tmp = ls->head;
    for (int i = 1; i <= ls->n - 2; i++)   // stop on the 2nd last
        tmp = tmp->next;

    delete ls->tail;               // free the old last element
    ls->tail = tmp;                // the 2nd last becomes the last
    ls->tail->next = NULL;         // and it points to nothing
    ls->n--;
}

/* ============================================================
   deleteValue : delete the FIRST element that holds d
   ============================================================ */
void deleteValue(List *ls, int d)
{
    if (ls->n == 0) { cout << "(list empty) "; return; }

    if (ls->head->data == d) {     // special case: it is the first one
        deleteBegin(ls);
        return;
    }

    Element *prev = ls->head;
    while (prev->next != NULL && prev->next->data != d)
        prev = prev->next;

    if (prev->next == NULL) {      // walked everything
        cout << "(value " << d << " not found) ";
        return;
    }

    Element *target = prev->next;
    prev->next = target->next;     // jump over the target
    if (target == ls->tail)        // we removed the last one
        ls->tail = prev;
    delete target;
    ls->n--;
}

/* ============================================================
   destroyList : delete every element, one by one
   ============================================================ */
void destroyList(List *ls)
{
    while (ls->n > 0)
        deleteBegin(ls);
}

/* ============================================================
   reverseList
        We walk the list and turn every arrow around.
        We need THREE pointers: previous, current, next.

        before : head -> [1] -> [2] -> [3] -> NULL
        after  : head -> [3] -> [2] -> [1] -> NULL
   ============================================================ */
void reverseList(List *ls)
{
    Element *prev = NULL;
    Element *cur  = ls->head;
    Element *nxt  = NULL;

    ls->tail = ls->head;           // the old first becomes the last

    while (cur != NULL) {
        nxt = cur->next;           // remember where we were going
        cur->next = prev;          // turn the arrow around
        prev = cur;                // move both pointers forward
        cur  = nxt;
    }

    ls->head = prev;               // the old last becomes the first
}

/* ============================================================
   display
   ============================================================ */
void display(List *ls)
{
    Element *tmp = ls->head;

    if (tmp == NULL) { cout << "(empty list)" << endl; return; }

    cout << "head -> ";
    while (tmp != NULL) {
        cout << tmp->data << " -> ";
        tmp = tmp->next;
    }
    cout << "NULL   [n = " << ls->n << "]" << endl;
}

/* ============================================================
   PRACTICE

   1. Write sumList(List *ls) and maxList(List *ls).
   2. Write insertSorted(List *ls, int d) that inserts a value
      at the right place so that the list stays sorted.
   3. Write deleteAll(List *ls, int d) that deletes EVERY element
      holding the value d (not only the first one).
   4. Write concat(List *a, List *b) that puts the list b at the
      end of the list a.
   5. Change "int data" into "struct Student data" and store
      real students (name, age, gpa) in the list.
   6. Why is deleteEnd() slow (O(n)) while deleteBegin() is
      fast (O(1))? Which structure would fix that? (Topic 7!)
   ============================================================ */
