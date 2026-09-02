/* ============================================================
   Data Structure & Programming II
   Topic 10: Sorting Algorithms

   What students learn here:
     1. What sorting is, and why every algorithm shares the same
        two building blocks: COMPARE and SWAP
     2. Simple sorts   : Bubble, Selection, Insertion   -> O(n^2)
     3. Efficient sorts: Merge, Quick                   -> O(n log n)
     4. Time complexity and the Big-O notation
     5. Counting the real number of comparisons and swaps,
        so students SEE the difference

   THE DIFFERENCE TO REMEMBER
     Bubble    : the biggest value "sinks" to the END first
                 -> the array is filled correctly from the right
     Selection : we look for the smallest and put it in front
                 -> the array is filled correctly from the left

   Compile:  g++ L10-SortingAlgorithms.cpp -o L10
   ============================================================ */

#include <iostream>
#include <string>
#include <cstdlib>     // rand, srand
#include <ctime>       // time
using namespace std;

/* Global counters, only to show the cost of each algorithm. */
long comparisons = 0;
long swaps       = 0;

/* ============================================================
   A helper: exchange two values through pointers
   (Topic 4: without pointers we could not do this)
   ============================================================ */
void swapValues(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    swaps++;
}

void display(int t[], int size)
{
    for (int i = 0; i < size; i++)
        cout << t[i] << " ";
    cout << endl;
}

void copyArray(int src[], int dst[], int size)
{
    for (int i = 0; i < size; i++) dst[i] = src[i];
}

void resetCounters() { comparisons = 0; swaps = 0; }

void showCost(string name)
{
    cout << "   " << name << ": " << comparisons << " comparisons, "
         << swaps << " swaps" << endl;
}

/* ============================================================
   1. BUBBLE SORT                       complexity O(n^2)

      We compare each pair of NEIGHBOURS and we swap them if
      they are in the wrong order. After the first pass, the
      biggest value is at the end. After the second pass, the
      second biggest, and so on.

          3 0 8 1  ->  0 3 1 8  ->  0 1 3 8
   ============================================================ */
void bubbleSort(int t[], int size)
{
    for (int i = 0; i < size - 1; i++) {

        bool swapped = false;              // small improvement

        for (int j = 0; j < size - 1 - i; j++) {
            comparisons++;
            if (t[j] > t[j + 1]) {
                swapValues(&t[j], &t[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)                      // already sorted: stop
            break;
    }
}

/* ============================================================
   2. SELECTION SORT                    complexity O(n^2)

      At step i we look for the SMALLEST value in the rest of
      the array, and we put it at position i.
      The left part is always finished and correct.
   ============================================================ */
void selectionSort(int t[], int size)
{
    for (int i = 0; i < size - 1; i++) {

        int minIndex = i;                  // suppose t[i] is the smallest

        for (int j = i + 1; j < size; j++) {
            comparisons++;
            if (t[j] < t[minIndex])
                minIndex = j;              // we found a smaller one
        }

        if (minIndex != i)
            swapValues(&t[i], &t[minIndex]);
    }
}

/* ============================================================
   3. INSERTION SORT                    complexity O(n^2)
                                        but O(n) if already sorted!

      Like sorting playing cards in your hand: you take the next
      card and you slide it back until it is at the right place.
   ============================================================ */
void insertionSort(int t[], int size)
{
    for (int i = 1; i < size; i++) {

        int key = t[i];                    // the card we hold
        int j   = i - 1;

        while (j >= 0) {
            comparisons++;
            if (t[j] <= key)
                break;                     // the right place is found
            t[j + 1] = t[j];               // slide to the right
            j--;
            swaps++;
        }

        t[j + 1] = key;                    // drop the card here
    }
}

/* ============================================================
   4. MERGE SORT                        complexity O(n log n)

      DIVIDE AND CONQUER (and it uses recursion, Topic 2!)
        1. cut the array in two halves
        2. sort each half (by calling itself)
        3. MERGE the two sorted halves into one sorted array
   ============================================================ */
void merge(int t[], int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = t[left + i];
    for (int j = 0; j < n2; j++) R[j] = t[middle + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {             // take the smaller head
        comparisons++;
        if (L[i] <= R[j]) t[k++] = L[i++];
        else              t[k++] = R[j++];
    }
    while (i < n1) t[k++] = L[i++];        // the rest of L
    while (j < n2) t[k++] = R[j++];        // the rest of R

    delete[] L;
    delete[] R;
}

void mergeSort(int t[], int left, int right)
{
    if (left >= right)                     // BASE CASE: 0 or 1 element
        return;

    int middle = (left + right) / 2;

    mergeSort(t, left, middle);            // sort the left half
    mergeSort(t, middle + 1, right);       // sort the right half
    merge(t, left, middle, right);         // put them together
}

/* ============================================================
   5. QUICK SORT                        average O(n log n)

      1. choose a PIVOT (here: the last element)
      2. put every smaller value on its left, every bigger one
         on its right  -> the pivot is now at its final place
      3. do the same on the left part and on the right part
   ============================================================ */
int partition(int t[], int low, int high)
{
    int pivot = t[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (t[j] < pivot) {
            i++;
            swapValues(&t[i], &t[j]);
        }
    }
    swapValues(&t[i + 1], &t[high]);       // put the pivot in the middle
    return i + 1;                          // its final position
}

void quickSort(int t[], int low, int high)
{
    if (low >= high)
        return;

    int p = partition(t, low, high);

    quickSort(t, low, p - 1);
    quickSort(t, p + 1, high);
}

/* ============================================================
   MAIN
   ============================================================ */

int main()
{
    /* ------------------------------------------------------------
       1. SEE EACH ALGORITHM ON A SMALL ARRAY
       ------------------------------------------------------------ */

    const int SIZE = 8;
    int original[SIZE] = {3, 0, 8, 1, 9, 2, 7, 4};
    int t[SIZE];

    cout << "Original array : ";
    display(original, SIZE);

    cout << "\n=== 1. Bubble sort ===" << endl;
    copyArray(original, t, SIZE); resetCounters();
    bubbleSort(t, SIZE);
    cout << "   result: "; display(t, SIZE);
    showCost("bubble");

    cout << "\n=== 2. Selection sort ===" << endl;
    copyArray(original, t, SIZE); resetCounters();
    selectionSort(t, SIZE);
    cout << "   result: "; display(t, SIZE);
    showCost("selection");

    cout << "\n=== 3. Insertion sort ===" << endl;
    copyArray(original, t, SIZE); resetCounters();
    insertionSort(t, SIZE);
    cout << "   result: "; display(t, SIZE);
    showCost("insertion");

    cout << "\n=== 4. Merge sort ===" << endl;
    copyArray(original, t, SIZE); resetCounters();
    mergeSort(t, 0, SIZE - 1);
    cout << "   result: "; display(t, SIZE);
    showCost("merge");

    cout << "\n=== 5. Quick sort ===" << endl;
    copyArray(original, t, SIZE); resetCounters();
    quickSort(t, 0, SIZE - 1);
    cout << "   result: "; display(t, SIZE);
    showCost("quick");

    /* ------------------------------------------------------------
       2. WATCH BUBBLE SORT PASS BY PASS
       ------------------------------------------------------------ */

    cout << "\n=== 6. Bubble sort, step by step ===" << endl;

    int demo[6] = {5, 2, 9, 1, 7, 3};
    cout << "start : "; display(demo, 6);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5 - i; j++)
            if (demo[j] > demo[j + 1])
                swapValues(&demo[j], &demo[j + 1]);
        cout << "pass " << i + 1 << ": ";
        display(demo, 6);
    }

    /* ------------------------------------------------------------
       3. THE REAL LESSON: O(n^2) vs O(n log n)
       ------------------------------------------------------------ */

    cout << "\n=== 7. Big-O in real numbers ===" << endl;
    cout << "Number of comparisons on a random array:" << endl;
    cout << "  n        bubble/selection    merge/quick" << endl;
    cout << "  ---      ----------------    -----------" << endl;

    srand(time(NULL));
    int sizes[3] = {100, 1000, 4000};

    for (int k = 0; k < 3; k++) {
        int n = sizes[k];
        int *a = new int[n];
        int *b = new int[n];

        for (int i = 0; i < n; i++) a[i] = rand() % 10000;
        copyArray(a, b, n);

        resetCounters();
        selectionSort(a, n);
        long costSelection = comparisons;

        resetCounters();
        mergeSort(b, 0, n - 1);
        long costMerge = comparisons;

        cout << "  " << n << "\t     " << costSelection
             << "\t\t" << costMerge << endl;

        delete[] a;
        delete[] b;
    }

    cout << "\nWhen n is multiplied by 10, an O(n^2) algorithm needs"
         << "\n100 times more work, while an O(n log n) algorithm needs"
         << "\nonly about 10 times more. THAT is why complexity matters."
         << endl;

    /* ------------------------------------------------------------
       4. SUMMARY TABLE

         Algorithm    Best      Average   Worst     Method
         ---------    ----      -------   -----     ------
         Bubble       n         n^2       n^2       exchanging
         Selection    n^2       n^2       n^2       selection
         Insertion    n         n^2       n^2       insertion
         Merge        n log n   n log n   n log n   merging
         Quick        n log n   n log n   n^2       partitioning
       ------------------------------------------------------------ */

    return 0;
}

/* ============================================================
   PRACTICE

   1. Modify bubbleSort() so that it sorts from the biggest to
      the smallest.
   2. Sort an array of student names (string) alphabetically.
      (Hint: in C++ you can compare strings with < directly.)
   3. Sort an array of struct Student by GPA. Do not forget to
      swap the WHOLE structure, not only the gpa.
   4. Write binarySearch(int t[], int size, int value) which
      works only on a SORTED array, and count its comparisons.
      Compare with a simple linear search.
   5. Give bubbleSort() an array that is ALREADY sorted.
      Thanks to the "swapped" flag, how many passes does it need?
   6. Implement Heap sort or Shell sort and add it to the
      comparison table.
   ============================================================ */
