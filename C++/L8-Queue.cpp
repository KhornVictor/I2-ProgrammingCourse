/* ============================================================
   Data Structure & Programming II
   Topic 8: Queue (FIFO)

   What students learn here:
     1. FIFO = First In, First Out
        (the queue at the bank: the first arrived is served first)
     2. The 5 operations:
            enqueue  add at the REAR
            dequeue  remove from the FRONT
            peek     look at the front without removing
            isEmpty  is it empty?
            size     how many elements
     3. Two implementations:
            A) as an ARRAY       (simple, but limited size)
            B) as a LINKED LIST  (grows as much as we want)
     4. The drawback of the array version (the wasted places)
     5. A real application: a waiting list of customers

     Choice used here (recommended in the lecture):
            enqueue -> insert at the END   of the list
            dequeue -> delete from the BEGINNING of the list

   Compile:  g++ L8-Queue.cpp -o L8
   ============================================================ */

#include <iostream>
#include <string>
using namespace std;

/* ============================================================
   PART A - QUEUE AS AN ARRAY
   ============================================================ */

const int MAXSIZE = 5;          // deliberately small, to show the problem

struct QueueArray {
    int data[MAXSIZE];
    int front;                  // index of the first element
    int rear;                   // index of the last element
};

void initQueueA(QueueArray &q)
{
    q.front = 0;
    q.rear  = -1;               // -1 means "nothing inside yet"
}

bool isEmptyA(QueueArray &q) { return q.rear < q.front; }
bool isFullA (QueueArray &q) { return q.rear == MAXSIZE - 1; }

void enqueueA(QueueArray &q, int value)
{
    if (isFullA(q)) {
        cout << "  Queue is FULL, cannot add " << value << endl;
        return;
    }
    q.rear++;
    q.data[q.rear] = value;
    cout << "  enqueue(" << value << ")" << endl;
}

int dequeueA(QueueArray &q)
{
    if (isEmptyA(q)) {
        cout << "  Queue is EMPTY, nothing to remove" << endl;
        return -1;
    }
    int value = q.data[q.front];
    q.front++;
    cout << "  dequeue() -> " << value << endl;
    return value;
}

void displayA(QueueArray &q)
{
    cout << "  Queue: front[ ";
    for (int i = q.front; i <= q.rear; i++)
        cout << q.data[i] << " ";
    cout << "]rear" << endl;
}

/* ============================================================
   PART B - QUEUE AS A LINKED LIST
      front = head of the list
      rear  = tail of the list
   ============================================================ */

struct Element {
    string   data;
    Element *next;
};

struct Queue {
    Element *front;
    Element *rear;
    int      n;
};

Queue *createQueue()
{
    Queue *q = new Queue;
    q->front = NULL;
    q->rear  = NULL;
    q->n     = 0;
    return q;
}

bool isEmpty(Queue *q) { return q->n == 0; }
int  size   (Queue *q) { return q->n;      }

/* enqueue = insert at the END of the list */
void enqueue(Queue *q, string value)
{
    Element *E = new Element;
    E->data = value;
    E->next = NULL;

    if (q->n == 0) {               // the queue was empty
        q->front = E;
        q->rear  = E;
    } else {
        q->rear->next = E;         // the old last points to E
        q->rear = E;               // E becomes the last
    }
    q->n++;
}

/* dequeue = delete from the BEGINNING of the list */
string dequeue(Queue *q)
{
    if (isEmpty(q)) {
        cout << "  The queue is empty!" << endl;
        return "";
    }

    Element *tmp = q->front;
    string value = tmp->data;

    q->front = q->front->next;
    if (q->front == NULL)          // the queue became empty
        q->rear = NULL;

    delete tmp;
    q->n--;
    return value;
}

/* peek = look at the front WITHOUT removing it */
string peek(Queue *q)
{
    if (isEmpty(q)) return "";
    return q->front->data;
}

void display(Queue *q)
{
    Element *tmp = q->front;

    cout << "  front[ ";
    while (tmp != NULL) {
        cout << tmp->data << " ";
        tmp = tmp->next;
    }
    cout << "]rear   (" << q->n << " waiting)" << endl;
}

/* ============================================================
   MAIN
   ============================================================ */

int main()
{
    /* ------------------------------------------------------------
       1. THE ARRAY VERSION AND ITS PROBLEM
       ------------------------------------------------------------ */

    cout << "=== 1. Queue as an ARRAY (max " << MAXSIZE << ") ===" << endl;

    QueueArray qa;
    initQueueA(qa);

    enqueueA(qa, 10);
    enqueueA(qa, 20);
    enqueueA(qa, 30);
    displayA(qa);

    dequeueA(qa);
    dequeueA(qa);
    displayA(qa);

    enqueueA(qa, 40);
    enqueueA(qa, 50);
    enqueueA(qa, 60);
    displayA(qa);

    enqueueA(qa, 70);      // FULL, although two places are free!

    cout << "\n  THE PROBLEM: front is now at index 2, so the two"
         << "\n  first cells of the array are lost. The queue says"
         << "\n  'full' while the array is not really full."
         << "\n  (One fix is the CIRCULAR queue. The other fix is"
         << "\n   to use a linked list -> part 2.)" << endl;

    /* ------------------------------------------------------------
       2. THE LINKED LIST VERSION
       ------------------------------------------------------------ */

    cout << "\n=== 2. Queue as a LINKED LIST ===" << endl;

    Queue *q = createQueue();

    cout << "Three customers arrive:" << endl;
    enqueue(q, "Sok");
    enqueue(q, "Dara");
    enqueue(q, "Sao");
    display(q);

    cout << "Next to be served: " << peek(q) << " (peek: not removed)" << endl;
    display(q);

    cout << "\nServing: " << dequeue(q) << endl;
    display(q);

    cout << "A new customer arrives: Seyha" << endl;
    enqueue(q, "Seyha");
    display(q);

    cout << "\nServing everybody:" << endl;
    while (!isEmpty(q))
        cout << "  now serving " << dequeue(q) << endl;

    display(q);
    dequeue(q);                       // test on an empty queue

    /* ------------------------------------------------------------
       3. THE EXERCISE OF THE LECTURE
          Put every letter of a word into a queue, then compare
          with a second word, letter by letter, in the FIFO order.
       ------------------------------------------------------------ */

    cout << "\n=== 3. Compare two words with a queue ===" << endl;

    Queue *letters = createQueue();
    string word1, word2;

    cout << "First word : ";
    cin  >> word1;

    for (int i = 0; i < (int)word1.length(); i++)
        enqueue(letters, string(1, word1[i]));   // one letter -> a string

    display(letters);

    cout << "Second word: ";
    cin  >> word2;

    bool same = ((int)word2.length() == size(letters));
    int  i = 0;

    while (!isEmpty(letters)) {
        string c = dequeue(letters);             // FIFO: first letter first
        if (same && i < (int)word2.length() && c[0] != word2[i])
            same = false;
        i++;
    }

    if (same)
        cout << "The two words are the same." << endl;
    else
        cout << "The two words are different." << endl;

    delete letters;
    delete q;

    /* ------------------------------------------------------------
       4. WHERE ARE QUEUES USED?
            - printer job list
            - CPU scheduling of the operating system
            - messages in a network
            - customers at a counter, cars at a petrol pump
       ------------------------------------------------------------ */

    return 0;
}

/* ============================================================
   PRACTICE

   1. Write isFull() for the array queue and turn it into a
      CIRCULAR queue so that no place is wasted.
      (Hint: rear = (rear + 1) % MAXSIZE)
   2. Build a queue of struct Customer { name, ticketNumber }
      and simulate a bank counter with a menu:
         1- a customer arrives     2- serve the next customer
         3- show the waiting list  0- quit
   3. Write a function that counts the elements of a queue
      WITHOUT using q->n (and puts everything back afterwards).
   4. Use a queue to reverse... nothing. Try it and explain why
      a queue CANNOT reverse a sequence, but a stack can.
      (see Topic 9)
   ============================================================ */
