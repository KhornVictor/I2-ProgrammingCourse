/* ============================================================
   Data Structure & Programming II
   Topic 11: Hash Table

   What students learn here:
     1. The problem: searching in an array or a list costs O(n)
     2. The idea: COMPUTE the position instead of searching it
            index = hashFunction(key)          -> O(1)
     3. Hash table / hash function / hashing
     4. COLLISION: two keys land on the same index
     5. Two solutions:
            A) OPEN hashing  = chaining (an array of linked lists)
            B) CLOSED hashing = linear probing (stay in the array)
     6. Hashing a string (name of a student)

   THE SEARCH COST
        linked list        O(n)
        array (unsorted)   O(n)
        array (sorted)     O(log n)
        HASH TABLE         O(1)      <- the goal

   Compile:  g++ L11-HashTable.cpp -o L11
   ============================================================ */

#include <iostream>
#include <string>
using namespace std;

const int SIZE  = 7;        // the size of our table (a prime number is better)
const int EMPTY = -999;     // the mark for "this cell is free"

/* ============================================================
   THE HASH FUNCTION
      It transforms a key into an index of the array.
      A good hash function is:
          - easy and fast to compute
          - spreads the keys well (few collisions)
   ============================================================ */
int hashFunction(int key)
{
    return key % SIZE;      // the remainder is always between 0 and SIZE-1
}

/* ============================================================
   PART 1 - A NAIVE HASH TABLE (to SEE the collision problem)
   ============================================================ */

int ht[SIZE];

void initTable()
{
    for (int i = 0; i < SIZE; i++)
        ht[i] = EMPTY;
}

void insertNaive(int value)
{
    int index = hashFunction(value);
    if (ht[index] != EMPTY)
        cout << "   !! COLLISION: " << ht[index] << " and " << value
             << " both want the index " << index << endl;
    ht[index] = value;      // the old value is simply LOST
}

void displayNaive()
{
    for (int i = 0; i < SIZE; i++) {
        cout << "   " << i << "  --> ";
        if (ht[i] == EMPTY) cout << "(empty)";
        else                cout << ht[i];
        cout << endl;
    }
}

/* ============================================================
   PART 2 - OPEN HASHING (CHAINING)
      Each cell of the array is the HEAD of a linked list.
      Every value that hashes to i is added to the list number i.
      Nothing is ever lost.
   ============================================================ */

struct Element {
    int      value;
    Element *next;
};

struct List {
    Element *head;
    Element *tail;
    int      n;
};

List *chain[SIZE];          // an ARRAY of LINKED LISTS

List *createEmptyList()
{
    List *L = new List;
    L->head = NULL;
    L->tail = NULL;
    L->n    = 0;
    return L;
}

void createAllLists()
{
    for (int i = 0; i < SIZE; i++)
        chain[i] = createEmptyList();
}

/* add at the end of one list (the same insertEnd as Topic 6) */
void addEnd(List *ls, int value)
{
    Element *e = new Element;
    e->value = value;
    e->next  = NULL;

    if (ls->n == 0) {
        ls->head = e;
        ls->tail = e;
    } else {
        ls->tail->next = e;
        ls->tail = e;
    }
    ls->n++;
}

void insertChaining(int value)
{
    int index = hashFunction(value);
    addEnd(chain[index], value);
}

bool searchChaining(int value, int &steps)
{
    steps = 1;                              // 1 step: computing the index
    int index = hashFunction(value);

    Element *e = chain[index]->head;
    while (e != NULL) {
        steps++;
        if (e->value == value)
            return true;
        e = e->next;
    }
    return false;
}

void displayChaining()
{
    for (int i = 0; i < SIZE; i++) {
        cout << "   " << i << "  --> ";
        Element *e = chain[i]->head;
        if (e == NULL) cout << "(empty)";
        while (e != NULL) {
            cout << e->value;
            if (e->next != NULL) cout << " -> ";
            e = e->next;
        }
        cout << endl;
    }
}

/* ============================================================
   PART 3 - CLOSED HASHING (LINEAR PROBING)
      Everything stays inside the array.
      If the cell is taken, we simply try the next one,
      and the next one, until we find a free place.
   ============================================================ */

int ht2[SIZE];

void initTable2()
{
    for (int i = 0; i < SIZE; i++)
        ht2[i] = EMPTY;
}

void insertProbing(int value)
{
    int index = hashFunction(value);
    int start = index;

    while (ht2[index] != EMPTY) {           // the cell is taken
        index = (index + 1) % SIZE;         // try the next one (circular)
        if (index == start) {               // we came back: the table is full
            cout << "   Table is FULL, cannot insert " << value << endl;
            return;
        }
    }
    ht2[index] = value;
}

bool searchProbing(int value, int &steps)
{
    steps = 0;
    int index = hashFunction(value);
    int start = index;

    while (ht2[index] != EMPTY) {
        steps++;
        if (ht2[index] == value)
            return true;
        index = (index + 1) % SIZE;
        if (index == start) break;
    }
    return false;
}

void displayProbing()
{
    for (int i = 0; i < SIZE; i++) {
        cout << "   " << i << "  --> ";
        if (ht2[i] == EMPTY) cout << "(empty)";
        else                 cout << ht2[i]
                                  << "   [its natural index was "
                                  << hashFunction(ht2[i]) << "]";
        cout << endl;
    }
}

/* ============================================================
   PART 4 - HASHING A STRING
      A name is not a number, so first we turn it into a number.
      Here: the sum of the ASCII codes of its letters.
   ============================================================ */

int hashString(string s, int tableSize)
{
    int sum = 0;
    for (int i = 0; i < (int)s.length(); i++)
        sum = sum + (int)s[i];              // add the ASCII code
    return sum % tableSize;
}

/* ============================================================
   MAIN
   ============================================================ */

int main()
{
    /* ------------------------------------------------------------
       0. WHY? Searching in a normal array
       ------------------------------------------------------------ */

    cout << "=== 0. Searching in a normal array ===" << endl;

    int a[] = {4, 7, 10, 0, 9, 100, 50, 80, 25, 56, 90, 17};
    int n   = 12;
    int target = 90;
    int count  = 0;

    for (int i = 0; i < n; i++) {
        count++;
        if (a[i] == target) break;
    }
    cout << "Looking for " << target << " needed " << count
         << " comparisons." << endl;
    cout << "Looking for a value that does NOT exist needs "
         << n << " comparisons (the whole array)." << endl;
    cout << "With a hash table we will need about 1." << endl;

    /* ------------------------------------------------------------
       1. THE NAIVE TABLE AND THE COLLISION
       ------------------------------------------------------------ */

    cout << "\n=== 1. A naive hash table (size " << SIZE << ") ===" << endl;

    initTable();
    cout << "Insert 7, 8, 25:" << endl;
    insertNaive(7);      // 7 % 7 = 0
    insertNaive(8);      // 8 % 7 = 1
    insertNaive(25);     // 25 % 7 = 4
    displayNaive();

    cout << "\nNow insert 15 and 22:" << endl;
    insertNaive(15);     // 15 % 7 = 1  -> the same cell as 8 !
    insertNaive(22);     // 22 % 7 = 1  -> again!
    displayNaive();

    cout << "\n   The values 8 and 15 are LOST. This is a COLLISION."
         << "\n   We need a strategy to solve it." << endl;

    /* ------------------------------------------------------------
       2. OPEN HASHING - CHAINING
       ------------------------------------------------------------ */

    cout << "\n=== 2. Open hashing (chaining) ===" << endl;

    createAllLists();
    insertChaining(7);
    insertChaining(8);
    insertChaining(15);
    insertChaining(22);
    insertChaining(25);
    displayChaining();

    int steps;
    cout << "\nsearch(22) -> " << (searchChaining(22, steps) ? "FOUND" : "not found")
         << " in " << steps << " step(s)" << endl;
    cout << "search(99) -> " << (searchChaining(99, steps) ? "FOUND" : "not found")
         << " in " << steps << " step(s)" << endl;

    /* ------------------------------------------------------------
       3. CLOSED HASHING - LINEAR PROBING
       ------------------------------------------------------------ */

    cout << "\n=== 3. Closed hashing (linear probing) ===" << endl;

    initTable2();
    insertProbing(7);
    insertProbing(8);
    insertProbing(15);
    insertProbing(22);
    insertProbing(25);
    displayProbing();

    cout << "\nsearch(22) -> " << (searchProbing(22, steps) ? "FOUND" : "not found")
         << " in " << steps << " step(s)" << endl;

    /* ------------------------------------------------------------
       4. A HASH TABLE OF NAMES
       ------------------------------------------------------------ */

    cout << "\n=== 4. Hashing student names ===" << endl;

    const int NAMESIZE = 11;
    string names[6] = {"Sok", "Dara", "Sao", "Seyha", "Vichea", "Bopha"};

    cout << "Table size = " << NAMESIZE << endl;
    for (int i = 0; i < 6; i++)
        cout << "   hash(\"" << names[i] << "\") = "
             << hashString(names[i], NAMESIZE) << endl;

    string myName;
    cout << "\nEnter a name to hash: ";
    cin  >> myName;
    cout << "hash(\"" << myName << "\") = "
         << hashString(myName, NAMESIZE) << endl;

    /* ------------------------------------------------------------
       5. WHAT MAKES A GOOD HASH FUNCTION?
            - fast to compute
            - spreads the keys everywhere (few collisions)
            - always gives the SAME index for the SAME key
          A PERFECT hash function has no collision at all,
          but it exists only when we know all the keys in advance.
       ------------------------------------------------------------ */

    return 0;
}

/* ============================================================
   PRACTICE

   1. Change SIZE to 10 and insert 10, 20, 30, 40. What happens?
      Explain why a PRIME number is a better table size.
   2. Add deleteValue() to the chaining version.
   3. Store a whole struct Student { id, name, gpa } in the hash
      table, using the id as the key.
   4. Build a hash table of 500 cells for student names and
      count the collisions with your class list.
   5. Implement QUADRATIC probing: instead of +1, +1, +1,
      try +1, +4, +9, +16 ... Does it spread better?
   6. Compare, on 1000 values, the number of steps needed by:
      a linear search in an array, and a search in your hash table.
   ============================================================ */
