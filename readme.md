# I2 — Data Structure & Programming

Example source code for the **I2 Programming** course
(Vacation Training Class at **ITC-PP**, 2026).

Every lesson of the course has **one example file**. Each file is a complete,
runnable program, commented step by step, and ends with a **PRACTICE** section
containing the exercises of that lesson.

---

## Class schedule

Vacation Training Class at ITC-PP — 2026

| Time | Monday | Tuesday | Wednesday | Thursday | Friday | **Saturday** |
|---|---|---|---|---|---|---|
| 11:00 – 13:00 | Electricity | Mechanic II | Linear Algebra | Calculus III | Chemistry | **Programming** |

> Our session is on **Saturday, 11:00 – 13:00**.

---

## What is inside

```
I2-Programming/
├── C/            Semester 1 — Data Structure & Programming I   (language C)
├── C++/          Semester 2 — Data Structure & Programming II  (language C++)
└── readme.md     this file
```

The slides (PDF) of each lesson are in the `Documents/` folder of the course.
The file names here follow the names of the slides, so `L5-ForLoop.c` goes with
`L5-ForLoop.pdf`.

---

## Part 1 — C  (`C/`)

| File | Lesson | What you learn |
|---|---|---|
| `L1-Introduction.c` | Introduction | structure of a C program, `printf`, `\n` and `\t`, turning an algorithm into code |
| `L2-Variable.c` | Variable & data type | `int` `float` `char` `string`, naming rules, constants, `+ - * / %`, relational & logical operators, ASCII, `<string.h>` |
| `L3-Condtion.c` | Condition | `if` / `else if` / `else`, `switch … case`, grade of a score, biggest of 3, type of a character, menu |
| `L4-Condition2.c` | Condition (part 2) | nested conditions, valid date with leap years, menu with a sub-menu |
| `L5-ForLoop.c` | Loop `for` | the 3 parts of `for`, counting up / down / by steps, nested loops, `break` & `continue`, factorial, prime numbers |
| `L6-WhileLoop.c` | Loop `while` | `while`, the infinite-loop trap, reading until the user types 0, working digit by digit, guess-the-number game |
| `L7-DoWhile.c` | Loop `do … while` | `do … while`, input validation, a menu that repeats, when to use each of the three loops |
| `L8-Array.c` | Array | index from `0` to `size-1`, filling and displaying, sum / average / max / min, search, array of strings, 2D table |
| `L10-Function.c` | Sub-program | function vs procedure, prototypes, parameters and `return`, local vs global variables, passing an array |
| `L11-Enumeration.c` | Enumeration | `enum`, the numbers hidden behind the names, `typedef`, `enum` with `switch` |
| `L12-Structure.c` | Structure | `struct`, the dot `.`, `typedef`, array of structures, nested structure, structure as a parameter |

> There is no `L9` — the course slides go directly from **L8 Array** to
> **L10 Function**.

## Part 2 — C++  (`C++/`)

| File | Lesson | What you learn |
|---|---|---|
| `L1-Introduction.cpp` | Getting started with C++ | C vs C++, `cout` / `cin`, the types `string` and `bool`, review of function / loop / array / structure |
| `L2-Recursive.cpp` | Recursive function | base case & general case, factorial, Fibonacci, sum, digits, direct vs indirect recursion, recursion vs loop |
| `L3-FileIO.cpp` | File IO | `ofstream` / `ifstream` / `fstream`, modes `ios::in` `ios::out` `ios::app`, reading word / line / character, reading a CSV file |
| `L4-Pointer.cpp` | Pointer | address `&` and value `*`, changing a value through a pointer, the real `swap()`, pointer and array, `new` / `delete` |
| `L5-LinkedList.cpp` | Linked list (1) | `Element` and `List`, `head` `tail` `next` `NULL`, create a list, insert at the beginning, walk through the list |
| `L6-LinkedList2.cpp` | Linked list (2) | insert at the end / at a position, search, delete first / last / by value, reverse, destroy, interactive menu |
| `L7-DoubleLinkedList.cpp` | Double linked list | the `previous` pointer, walking forward **and** backward, why `deleteEnd()` becomes fast |
| `L8-Queue.cpp` | Queue (FIFO) | `enqueue` `dequeue` `peek`, as an array (and its wasted places) and as a linked list |
| `L9-Stack.cpp` | Stack (LIFO) | `push` `pop` `peek`, reverse a word, check that brackets are balanced, decimal → binary |
| `L10-SortingAlgorithms.cpp` | Sorting algorithms | bubble, selection, insertion, merge, quick — with a counter that **shows** the difference between O(n²) and O(n log n) |
| `L11-HashTable.cpp` | Hash table | hash function, collision, open hashing (chaining), closed hashing (linear probing), hashing a name |
| `L12-Tree.cpp` | Tree / BST | root, leaf, depth, height, `insert` and `search`, pre-order / in-order / post-order / level-order, deleting a node (3 cases) |
| `L13-OOP.cpp` | Object-oriented programming | class & object, encapsulation (`private` / `public`), constructor, inheritance, overloading vs overriding, polymorphism, abstraction |

---

## How to run a program

### With Code::Blocks (recommended in class)

1. `File → Open…` and choose the `.c` or `.cpp` file
2. Press **F9** (*Build and run*)

### With the command prompt

For a C file:

```bash
gcc L5-ForLoop.c -o L5
L5
```

For a C++ file:

```bash
g++ L12-Tree.cpp -o L12
L12
```

On Linux or macOS, run the program with `./L5` instead of `L5`.

> `L3-FileIO.cpp` creates two files (`StudentList.txt` and `MyData.csv`) in the
> folder where you run it. This is normal — open them to see the result.

---

## How to use these files to study

1. **Read the slides first.** The code follows the slides, not the opposite.
2. **Run the program**, and compare its output with what you expected.
3. **Read the comments.** They explain *why*, not only *what*.
4. **Break the program on purpose.** Remove a `break;` in a `switch`, remove the
   base case of a recursion, write `num[5]` in an array of 5 elements. You learn
   more from a bug you created yourself than from a program that always works.
5. **Do the PRACTICE section** at the end of each file. Write the algorithm on
   paper before you write a single line of code — especially for the linked
   list, the stack, the queue and the tree.

---

## The order of the topics

The course is built one block on top of the other. If a lesson is difficult,
go back to the one before it:

```
variable → condition → loop → array → function → structure        (C)
                                        ↓
        recursion → pointer → linked list → stack / queue
                                        ↓
              sorting → hash table → tree → OOP                   (C++)
```

**Pointers (C++ L4) are the key.** Linked lists, stacks, queues, hash tables and
trees are all impossible without them. If pointers are not clear, stop and
redo `L4-Pointer.cpp` before going further.

---

## Rules for your own code

- Indent your code. One `{` opens a block, one `}` closes it, aligned.
- Give real names to your variables: `studentAge`, not `a`.
- One task = one function.
- Test with the normal case, then with the limit cases (0, negative, empty).
- Comment *why* you do something, not *what* the line says.

---

*ITC-PP — Vacation Training Class 2026 — I2 Programming*
