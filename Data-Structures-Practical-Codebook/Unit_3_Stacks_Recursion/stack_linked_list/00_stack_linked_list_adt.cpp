/*
========================================================================================
PROGRAM HEADER:
- Program Number: 00-StackLL
- Program Title: Stack Abstract Data Type (ADT) using Singly Linked List
- Unit: Unit III - Stack and Recursion
- Relevant Curriculum Topic: Stack Definition, Operations, Linked List Implementation
- Course Code: CE25PCC-202 (Theory Core) & CE25PCC-203 (Laboratory Foundation)
- Objective:
  Implement a dynamic Stack ADT using a linked list with push, pop, peek, isEmpty,
  display, and safe destructor memory deallocation.
- Data Structure Used: Singly Linked List with `top` pointing to the head node.
- What This Program Demonstrates:
  Dynamic stack sizing (no arbitrary capacity ceiling), O(1) push and pop at list head,
  heap memory management, and pointer reassignment.
========================================================================================

CONCEPT: WHY USE A LINKED LIST FOR A STACK?
1. No Fixed Size Limit: An array-based stack has a fixed capacity (`MAX_STACK`).
   If the program pushes more elements than `MAX_STACK`, it crashes with Stack Overflow.
   A linked-list stack grows dynamically on demand as long as system RAM is available.
2. Zero Wasted Pre-Allocated Space: An array allocates all memory upfront.
   A linked stack only allocates memory when an item is actually pushed.

WHERE IS `top` LOCATED IN THE LINKED LIST?
In a linked stack, `top` ALWAYS points to the HEAD (first node) of the list:
- Push is an O(1) Insert at Beginning:
  `newNode->next = top; top = newNode;`
- Pop is an O(1) Delete from Beginning:
  `temp = top; top = top->next; delete temp;`

WHY NOT PUSH/POP AT THE TAIL?
Because in a singly linked list, deleting from the tail requires traversing from head
to the second-to-last node, taking O(N) time!
By pushing and popping at the HEAD, both operations execute in true O(1) constant time!
*/

#include <iostream>
#include <iomanip>

using namespace std;

// Node structure for linked stack
struct StackNode {
    int data;           // Element value
    StackNode* next;    // Pointer to node below in stack

    StackNode(int val) {
        data = val;
        next = nullptr;
    }
};

class LinkedListStack {
private:
    StackNode* top;     // Pointer to the topmost node in the stack
    int count;          // Track active element count

public:
    LinkedListStack() {
        top = nullptr;  // Empty stack has no nodes
        count = 0;
    }

    // Destructor to free all heap memory when stack object goes out of scope
    ~LinkedListStack() {
        clear();
    }

    /*
    ALGORITHM: IS EMPTY
    1. Check if `top == nullptr`.
    2. Return true if null, false otherwise.
    */
    bool isEmpty() const {
        return top == nullptr;
    }

    /*
    ALGORITHM: PUSH
    1. Allocate new node: `newNode = new StackNode(value)`.
    2. Point new node's next to the current top: `newNode->next = top;`
    3. Update top pointer to new node: `top = newNode;`
    4. Increment `count++`.
    */
    void push(int value) {
        StackNode* newNode = new StackNode(value);

        newNode->next = top; // New node points down to the previous top node
        top = newNode;       // Top pointer moves up to the new node
        count++;

        cout << ">> PUSH: [" << value << "] pushed onto linked stack (Addr: " << newNode << ").\n";
    }

    /*
    ALGORITHM: POP
    1. If `isEmpty()`:
       Print Stack Underflow error and return -1.
    2. Save address of top node: `temp = top;`
    3. Save return value: `poppedVal = temp->data;`
    4. Advance top pointer to next node below: `top = top->next;`
    5. Delete old top node: `delete temp;`
    6. Decrement `count--`.
    7. Return `poppedVal`.
    */
    int pop() {
        if (isEmpty()) {
            cout << "[ERROR] Stack Underflow! Linked stack has zero elements.\n";
            return -1;
        }

        StackNode* temp = top;        // Keep hold of the node being removed
        int poppedVal = temp->data;   // Extract value
        top = top->next;              // Top moves down to the underlying node
        delete temp;                  // Release heap memory
        count--;

        cout << ">> POP:  [" << poppedVal << "] popped from linked stack.\n";
        return poppedVal;
    }

    /*
    ALGORITHM: PEEK
    1. If `isEmpty()`, report error and return -1.
    2. Return `top->data` without modifying pointers.
    */
    int peek() const {
        if (isEmpty()) {
            cout << "[ERROR] Cannot peek into an empty linked stack.\n";
            return -1;
        }
        return top->data;
    }

    /*
    ALGORITHM: DISPLAY
    1. If empty, print "[EMPTY]" and return.
    2. Pointer `temp = top`.
    3. Loop while `temp != nullptr`:
       Print node value and its pointer address.
       Advance: `temp = temp->next`.
    */
    void display() const {
        if (isEmpty()) {
            cout << "\n   [LINKED STACK: EMPTY]\n";
            return;
        }

        cout << "\n   --- CURRENT LINKED STACK CONTENTS (TOP TO BOTTOM) ---\n";
        const StackNode* temp = top;

        while (temp != nullptr) {
            cout << "   | " << setw(5) << temp->data << " | (Addr: " << temp 
                 << ", Next: " << temp->next << ")";
            if (temp == top) {
                cout << " <-- TOP";
            }
            cout << "\n";
            temp = temp->next;
        }
        cout << "   +-------+\n";
        cout << "   Active Nodes: " << count << "\n\n";
    }

    // Free all remaining nodes in the stack
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

// Interactive demonstration runner
int main() {
    LinkedListStack dynamicStack;

    cout << "==============================================================\n";
    cout << "   DYNAMIC STACK ADT (LINKED LIST IMPLEMENTATION)            \n";
    cout << "==============================================================\n";

    // 1. Initial Empty Check
    cout << "\n--- DEMO STEP 1: Empty stack check ---\n";
    cout << "Is stack empty? " << (dynamicStack.isEmpty() ? "YES" : "NO") << "\n";
    dynamicStack.display();

    // 2. Testing Underflow
    cout << "--- DEMO STEP 2: Testing Underflow ---\n";
    dynamicStack.pop();

    // 3. Pushing Elements Dynamically
    cout << "\n--- DEMO STEP 3: Pushing Elements (100, 200, 300, 400) ---\n";
    dynamicStack.push(100);
    dynamicStack.push(200);
    dynamicStack.push(300);
    dynamicStack.push(400);
    dynamicStack.display();

    // 4. Peeking
    cout << "--- DEMO STEP 4: Peeking at Top Element ---\n";
    cout << "Top value via peek(): [" << dynamicStack.peek() << "]\n";

    // 5. Popping Elements (LIFO)
    cout << "\n--- DEMO STEP 5: Popping Two Elements ---\n";
    dynamicStack.pop();
    dynamicStack.pop();
    dynamicStack.display();

    // 6. Dynamic Push beyond array limits
    cout << "--- DEMO STEP 6: Pushing new elements (500, 600, 700) ---\n";
    cout << "(Notice: No overflow limit exists in a linked stack!)\n";
    dynamicStack.push(500);
    dynamicStack.push(600);
    dynamicStack.push(700);
    dynamicStack.display();

    cout << "==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
Push 100, 200, 300, 400
Peek -> 400
Pop -> 400, Pop -> 300
Push 500, 600, 700 -> Stack grows seamlessly.

SAMPLE OUTPUT:
==============================================================
   DYNAMIC STACK ADT (LINKED LIST IMPLEMENTATION)            
==============================================================

--- DEMO STEP 1: Empty stack check ---
Is stack empty? YES

   [LINKED STACK: EMPTY]
--- DEMO STEP 2: Testing Underflow ---
[ERROR] Stack Underflow! Linked stack has zero elements.

--- DEMO STEP 3: Pushing Elements (100, 200, 300, 400) ---
>> PUSH: [100] pushed onto linked stack (Addr: 0x1f4b00).
>> PUSH: [200] pushed onto linked stack (Addr: 0x1f4b20).
>> PUSH: [300] pushed onto linked stack (Addr: 0x1f4b40).
>> PUSH: [400] pushed onto linked stack (Addr: 0x1f4b60).

   --- CURRENT LINKED STACK CONTENTS (TOP TO BOTTOM) ---
   |   400 | (Addr: 0x1f4b60, Next: 0x1f4b40) <-- TOP
   |   300 | (Addr: 0x1f4b40, Next: 0x1f4b20)
   |   200 | (Addr: 0x1f4b20, Next: 0x1f4b00)
   |   100 | (Addr: 0x1f4b00, Next: 0)
   +-------+
   Active Nodes: 4

--- DEMO STEP 4: Peeking at Top Element ---
Top value via peek(): [400]

--- DEMO STEP 5: Popping Two Elements ---
>> POP:  [400] popped from linked stack.
>> POP:  [300] popped from linked stack.

   --- CURRENT LINKED STACK CONTENTS (TOP TO BOTTOM) ---
   |   200 | (Addr: 0x1f4b20, Next: 0x1f4b00) <-- TOP
   |   100 | (Addr: 0x1f4b00, Next: 0)
   +-------+
   Active Nodes: 2

--- DEMO STEP 6: Pushing new elements (500, 600, 700) ---
(Notice: No overflow limit exists in a linked stack!)
>> PUSH: [500] pushed onto linked stack (Addr: 0x1f4b80).
>> PUSH: [600] pushed onto linked stack (Addr: 0x1f4ba0).
>> PUSH: [700] pushed onto linked stack (Addr: 0x1f4bc0).

   --- CURRENT LINKED STACK CONTENTS (TOP TO BOTTOM) ---
   |   700 | (Addr: 0x1f4bc0, Next: 0x1f4ba0) <-- TOP
   |   600 | (Addr: 0x1f4ba0, Next: 0x1f4b80)
   |   500 | (Addr: 0x1f4b80, Next: 0x1f4b20)
   |   200 | (Addr: 0x1f4b20, Next: 0x1f4b00)
   |   100 | (Addr: 0x1f4b00, Next: 0)
   +-------+
   Active Nodes: 5

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

TIME COMPLEXITY:
- `push()`:    O(1) - creates node and links at head in constant pointer time.
- `pop()`:     O(1) - removes head node and updates `top = top->next` in constant time.
- `peek()`:    O(1) - reads `top->data` directly.
- `isEmpty()`: O(1) - checks `top == nullptr`.
- `display()`: O(N) - visits all N active nodes.
- `clear()`:   O(N) - deletes all N nodes individually.

SPACE COMPLEXITY:
- Auxiliary Space: O(1).
- Total Dynamic Memory: O(N) heap memory, where each node is 16 bytes.

WHY?
Because insertion and deletion happen strictly at the HEAD of the singly linked list,
which requires no traversal.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Pushing in Wrong Order:
   - Writing `top = newNode; newNode->next = top;` creates a circular reference where
     `newNode` points to itself, and all previous nodes are lost!
   - Correct order: `newNode->next = top; top = newNode;`.
2. Deleting Before Moving Top:
   - Writing `delete top; top = top->next; // CRASH! top was already deleted!`
   - Must save next address first: `StackNode* temp = top; top = top->next; delete temp;`.
3. Memory Leaks when Program Terminates:
   - Always implement a destructor or cleanup loop to free all remaining heap nodes.
========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Node struct: `struct StackNode { int data; StackNode* next; };`
[ ] 2. Push: `newNode->next = top; top = newNode;`
[ ] 3. Pop: `temp = top; val = temp->data; top = top->next; delete temp; return val;`
[ ] 4. Peek: `return top->data;`
[ ] 5. Empty check: `return top == nullptr;`
========================================================================================
*/
