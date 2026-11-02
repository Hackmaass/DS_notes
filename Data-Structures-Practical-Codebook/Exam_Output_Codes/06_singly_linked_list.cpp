/**
 * ============================================================================
 * EXAM PROGRAM 06: SINGLY LINKED LIST (APPEND & TRAVERSAL)
 * ============================================================================
 * 📝 STEP-BY-STEP ALGORITHMS (Copy these directly onto your exam answer sheet!):
 * 
 * ALGORITHM 1: APPEND NODE AT END (Tail Insertion)
 *   Step 1: Start.
 *   Step 2: Allocate memory dynamically for new node: `newNode = new Node(value)`.
 *   Step 3: If list is empty (`head == nullptr`):
 *             Set `head = newNode`, exit.
 *   Step 4: Initialize traversal pointer: `curr = head`.
 *   Step 5: While `curr->next != nullptr`:
 *             Advance pointer: `curr = curr->next`.
 *   Step 6: Attach new node to the last node: `curr->next = newNode`.
 *   Step 7: Stop.
 * 
 * ALGORITHM 2: DISPLAY / TRAVERSAL OF SLL
 *   Step 1: Start.
 *   Step 2: If list is empty (`head == nullptr`), print "List is empty" and exit.
 *   Step 3: Set traversal pointer: `curr = head`.
 *   Step 4: While `curr != nullptr`:
 *             Print `curr->data`.
 *             Advance pointer: `curr = curr->next`.
 *   Step 5: Print "NULL".
 *   Step 6: Stop.
 * 
 * ============================================================================
 * 🧠 60-SECOND EXAM MEMORIZATION TECHNIQUE:
 * 
 * 1. THE NODE BLUEPRINT (Always write this first!):
 *    `struct Node {`
 *        `int data;`
 *        `Node* next;`
 *        `Node(int val) : data(val), next(nullptr) {}`
 *    `};`
 * 
 * 2. THE APPEND FORMULA:
 *    - To attach a node at the tail, you must stop AT the last node:
 *        `Node* curr = head;`
 *        `while (curr->next != nullptr) curr = curr->next;`
 *        `curr->next = new Node(40);`
 * 
 * 3. THE DISPLAY / WALK FORMULA:
 *    - To visit every node including the last one:
 *        `Node* curr = head;`
 *        `while (curr != nullptr) {`
 *            `cout << "[" << curr->data << "] -> ";`
 *            `curr = curr->next;`
 *        `}`
 * 
 * 4. THE EXAM PANIC CHECKLIST (The 2 Bugs Examiners Catch):
 *    - TRAP 1 (The Segmentation Fault): In the append while loop, writing
 *              `while (curr != nullptr)` instead of `while (curr->next != nullptr)`.
 *              If you do that, `curr` becomes NULL, and `curr->next = ...` crashes!
 *    - TRAP 2: Forgetting `next(nullptr)` in the constructor. If `next` contains
 *              random memory garbage, your display loop runs forever and crashes!
 * 
 * ============================================================================
 * EXPECTED TERMINAL OUTPUT SHOWN TO EXAMINER:
 * 
 * SLL: [10] -> [20] -> [30] -> [40] -> NULL
 * ============================================================================
 */

#include <iostream>

using namespace std;

// The Node Structure: data compartment + next pointer compartment
struct Node {
    int data;
    Node* next;
    // Constructor initializes data and sets next safely to nullptr
    Node(int val) : data(val), next(nullptr) {}
};

int main() {
    // 1. CREATE INITIAL NODES
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);

    // 2. APPEND 40 TO THE TAIL (Walk to the last node)
    Node* curr = head;
    // Notice condition: `curr->next != nullptr` stops AT node 30!
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    // Link node 30 to new node 40
    curr->next = new Node(40);

    // 3. DISPLAY THE LINKED LIST (Traverse from head to NULL)
    cout << "SLL: ";
    curr = head;
    // Notice condition: `curr != nullptr` visits all nodes through the end
    while (curr != nullptr) {
        cout << "[" << curr->data << "] -> ";
        curr = curr->next; // Leap to next node in heap memory
    }
    cout << "NULL\n";

    return 0;
}

/**
 * ============================================================================
 * 🎓 EXAMINER VIVA QUESTIONS & INSTANT ANSWERS:
 * Q: How do arrays and linked lists differ in memory allocation?
 * A: Arrays use contiguous memory on the stack or heap with O(1) random access.
 *    Linked lists use scattered, dynamically allocated nodes on the heap connected
 *    by pointers, allowing dynamic resizing without reallocating.
 *
 * Q: Why does the append loop check `curr->next != nullptr` instead of `curr != nullptr`?
 * A: If we checked `curr != nullptr`, `curr` would end up as NULL (past the end
 *    of the list), and doing `curr->next = newNode` would crash the program.
 * ============================================================================
 */
