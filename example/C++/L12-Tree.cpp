/* ============================================================
   Data Structure & Programming II
   Topic 12: Tree / Binary Search Tree (BST)

   What students learn here:
     1. Linear (array, list, stack, queue) vs NON-linear (tree)
     2. The words: root, parent, child, sibling, leaf,
        edge, depth, height, size
     3. Binary tree, and BINARY SEARCH TREE:
            everything smaller goes LEFT
            everything bigger  goes RIGHT
     4. insert() and search() - both recursive, both easy
     5. The three depth-first traversals:
            pre-order  (Data Left Right)
            in-order   (Left Data Right)  -> gives a SORTED list!
            post-order (Left Right Data)
     6. Breadth-first traversal (level by level, with a queue)
     7. min, max, height, size, count leaves
     8. delete a node: the 3 cases

   THE TREE WE BUILD (from the lecture)

                          F
                        /   \
                       D     J
                      / \   / \
                     B   E G   K
                    / \     \
                   A   C     I
                            /
                           H

   Compile:  g++ L12-Tree.cpp -o L12
   ============================================================ */

#include <iostream>
using namespace std;

/* ============================================================
   1. THE NODE
      Two pointers instead of one: left and right.
   ============================================================ */

struct Node {
    char  data;
    Node *left;
    Node *right;
};

/* ============================================================
   2. INSERT  (recursive - Topic 2 comes back!)

      - if we reach an empty place (NULL), we create the node
      - if the value is smaller than the current node -> go LEFT
      - if it is bigger                               -> go RIGHT
      - if it is equal, we ignore it (no duplicate in a BST)
   ============================================================ */
Node *insert(Node *root, char data)
{
    if (root == NULL) {                      // BASE CASE: the free place
        root = new Node;
        root->data  = data;
        root->left  = NULL;
        root->right = NULL;
    }
    else if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;                             // give the (new) root back
}

/* ============================================================
   3. SEARCH
      At every step we throw away HALF of the tree.
      That is why searching in a balanced BST costs O(log n).
   ============================================================ */
bool search(Node *root, char data)
{
    if (root == NULL)          return false;   // we reached the end
    if (data == root->data)    return true;    // found!
    if (data <  root->data)    return search(root->left,  data);
    else                       return search(root->right, data);
}

/* ============================================================
   4. THE THREE DEPTH-FIRST TRAVERSALS
      Only the POSITION of the cout changes. Nothing else!
   ============================================================ */

void preorder(Node *root)          // Data - Left - Right
{
    if (root != NULL) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(Node *root)           // Left - Data - Right
{
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void postorder(Node *root)         // Left - Right - Data
{
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

/* ============================================================
   5. BREADTH-FIRST (level by level)
      We need a QUEUE (Topic 8): put the root inside, then
      repeat: take one node, print it, put its children in.
   ============================================================ */

struct QNode { Node *tree; QNode *next; };

void levelOrder(Node *root)
{
    if (root == NULL) return;

    QNode *front = new QNode;      // a very small queue
    front->tree = root;
    front->next = NULL;
    QNode *rear = front;

    while (front != NULL) {
        Node *cur = front->tree;
        cout << cur->data << " ";

        if (cur->left != NULL) {                 // enqueue the left child
            QNode *q = new QNode;
            q->tree = cur->left; q->next = NULL;
            rear->next = q; rear = q;
        }
        if (cur->right != NULL) {                // enqueue the right child
            QNode *q = new QNode;
            q->tree = cur->right; q->next = NULL;
            rear->next = q; rear = q;
        }

        QNode *tmp = front;                      // dequeue
        front = front->next;
        delete tmp;
    }
}

/* ============================================================
   6. USEFUL MEASURES
   ============================================================ */

int getSize(Node *root)                // how many nodes
{
    if (root == NULL) return 0;
    return 1 + getSize(root->left) + getSize(root->right);
}

int getHeight(Node *root)              // longest path to a leaf
{
    if (root == NULL) return -1;       // an empty tree has height -1
    int hl = getHeight(root->left);
    int hr = getHeight(root->right);
    return 1 + (hl > hr ? hl : hr);
}

int countLeaves(Node *root)            // nodes with no child
{
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

Node *findMin(Node *root)              // the smallest = the most LEFT
{
    if (root == NULL) return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}

Node *findMax(Node *root)              // the biggest = the most RIGHT
{
    if (root == NULL) return NULL;
    while (root->right != NULL)
        root = root->right;
    return root;
}

/* ============================================================
   7. DELETE A NODE - the three cases

      Case 1: no child      -> just remove it
      Case 2: one child     -> the child takes its place
      Case 3: two children  -> copy the SMALLEST value of the
                               right subtree into the node,
                               then delete that smallest node
                               (it has at most one child, so we
                                are back to case 1 or 2)
   ============================================================ */
Node *deleteNode(Node *root, char data)
{
    if (root == NULL) return NULL;

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    }
    else {                                   // this is the node to delete
        if (root->left == NULL && root->right == NULL) {      // case 1
            delete root;
            return NULL;
        }
        else if (root->left == NULL) {                        // case 2
            Node *child = root->right;
            delete root;
            return child;
        }
        else if (root->right == NULL) {                       // case 2
            Node *child = root->left;
            delete root;
            return child;
        }
        else {                                                // case 3
            Node *minRight = findMin(root->right);
            root->data  = minRight->data;                     // copy
            root->right = deleteNode(root->right, minRight->data);
        }
    }
    return root;
}

/* ============================================================
   8. DRAW THE TREE (rotated: the root is on the left)
   ============================================================ */
void drawTree(Node *root, int space)
{
    if (root == NULL) return;

    space += 5;
    drawTree(root->right, space);            // the right part goes up

    cout << endl;
    for (int i = 5; i < space; i++) cout << " ";
    cout << root->data << endl;

    drawTree(root->left, space);             // the left part goes down
}

void destroyTree(Node *root)
{
    if (root == NULL) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

/* ============================================================
   MAIN
   ============================================================ */

int main()
{
    /* ------------------------------------------------------------
       1. BUILD THE TREE OF THE LECTURE
       ------------------------------------------------------------ */

    cout << "=== 1. Build the BST ===" << endl;

    Node *root = NULL;              // an empty tree is just NULL

    char values[11] = {'F','D','J','B','E','G','K','A','C','I','H'};

    for (int i = 0; i < 11; i++) {
        root = insert(root, values[i]);
        cout << "insert " << values[i] << " ";
    }
    cout << endl;

    cout << "\nThe tree (turn your head to the left):";
    drawTree(root, 0);

    /* ------------------------------------------------------------
       2. THE TRAVERSALS
       ------------------------------------------------------------ */

    cout << "\n=== 2. Traversals ===" << endl;

    cout << "pre-order  (D L R): ";  preorder(root);   cout << endl;
    cout << "in-order   (L D R): ";  inorder(root);    cout << endl;
    cout << "post-order (L R D): ";  postorder(root);  cout << endl;
    cout << "level-order       : ";  levelOrder(root); cout << endl;

    cout << "\n   NOTICE: the IN-ORDER traversal of a BST always"
         << "\n   gives the values in SORTED order. A binary search"
         << "\n   tree is a sorting machine." << endl;

    /* ------------------------------------------------------------
       3. MEASURES
       ------------------------------------------------------------ */

    cout << "\n=== 3. Measures ===" << endl;

    cout << "size (number of nodes) = " << getSize(root)     << endl;
    cout << "height of the tree     = " << getHeight(root)   << endl;
    cout << "number of leaves       = " << countLeaves(root) << endl;
    cout << "number of edges        = " << getSize(root) - 1 << endl;
    cout << "minimum value          = " << findMin(root)->data << endl;
    cout << "maximum value          = " << findMax(root)->data << endl;

    /* ------------------------------------------------------------
       4. SEARCH (the exercise of the lecture)
       ------------------------------------------------------------ */

    cout << "\n=== 4. Search ===" << endl;

    char c;
    for (int k = 0; k < 3; k++) {
        cout << "Enter a letter to search (A-Z): ";
        cin  >> c;
        if (search(root, c))
            cout << "  This letter " << c << " is in the tree." << endl;
        else
            cout << "  " << c << " does not exist in the tree." << endl;
    }

    /* ------------------------------------------------------------
       5. DELETE
       ------------------------------------------------------------ */

    cout << "\n=== 5. Delete a node ===" << endl;

    cout << "before          : "; inorder(root); cout << endl;

    root = deleteNode(root, 'A');      // case 1: a leaf
    cout << "after delete A  : "; inorder(root); cout << endl;

    root = deleteNode(root, 'G');      // case 2: one child (I)
    cout << "after delete G  : "; inorder(root); cout << endl;

    root = deleteNode(root, 'D');      // case 3: two children
    cout << "after delete D  : "; inorder(root); cout << endl;

    cout << "\nThe tree is now:";
    drawTree(root, 0);

    /* ------------------------------------------------------------
       6. A TREE OF NUMBERS, BUILT BY THE USER
       ------------------------------------------------------------ */

    cout << "\n=== 6. Why is a BST fast? ===" << endl;
    cout << "In a balanced tree of 1 000 000 nodes, searching needs"
         << "\nabout 20 comparisons (log2 of 1 000 000), while a"
         << "\nlinked list would need up to 1 000 000." << endl;

    destroyTree(root);
    return 0;
}

/* ============================================================
   PRACTICE

   1. Change "char data" into "int data" and build a tree with
      50 17 76 9 23 54 72 12 19 67. Then give the three
      traversals (check on paper first, then run the program).
   2. Write a function sumTree(Node *root) that adds every value.
   3. Write countNodesWithTwoChildren(Node *root).
   4. Write isLeaf(Node *n) and display only the leaves.
   5. Write a function that builds a BST from an array, then
      prints it with in-order: you have just written a sorting
      algorithm. What is its complexity?
   6. What happens if you insert 1, 2, 3, 4, 5, 6 in that order?
      Draw the tree. Is it still fast? (this is why BALANCED
      trees such as AVL exist)
   ============================================================ */
