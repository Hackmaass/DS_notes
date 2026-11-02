/*
========================================================================================
PROGRAM HEADER:
- Program Number: 00-CLL
- Program Title: Circular Singly Linked List (Operations and Safe Traversal)
- Unit: Unit I - Introduction to Data Structures and Memory Representation
- Relevant Curriculum Topic: Circular Linked List: Types, Operations, and Memory Representation
- Course Code: CE25PCC-202 (Theory Core) & CE25PCC-203 (Laboratory Foundation)
- Objective:
  Demonstrate creation, insertion at beginning, insertion at end, deletion at beginning,
  deletion at end, and circular traversal without entering infinite loops.
- Data Structure Used: Circular Singly Linked List (CLL) where the last node's `next`
  pointer references `head` instead of `nullptr`.
- What This Program Demonstrates:
  Ring memory architecture, boundary detection using `do-while` loops, maintaining
  the ring invariant during insertion/deletion, and graceful memory deallocation.
========================================================================================

CONCEPT: WHY USE A CIRCULAR LINKED LIST?
In a standard linear singly linked list, the final node's `next` pointer is `nullptr`.
This marks a hard "dead end".
In a Circular Linked List (CLL):
1. The last node's `next` pointer wraps right back to the `head` node!
2. Any node can be a starting point for full-circle traversal.
3. System Applications:
   - Round-Robin CPU scheduling (each process gets a time slice in a repeating ring).
   - Multiplayer turn-based games (Player 1 -> Player 2 -> Player 3 -> back to Player 1).
   - Audio/video playlist repeat modes.

HOW DOES TRAVERSAL TERMINATE WITHOUT ENTERING AN INFINITE LOOP?
In a linear list, we stop when `temp == nullptr`.
In a circular list, `temp` will NEVER equal `nullptr`! If you write `while (temp != nullptr)`,
your program will run forever until your CPU overheats or the stack/RAM runs out.
TERMINATION RULE:
1. Remember the address of `head`.
2. Use a `do-while` loop or start `temp = head->next` and stop when `temp == head`.
*/

#include <iostream>
#include <iomanip>

using namespace std;

// Definition of a Circular Linked List Node
struct Node {
    int data;         // Stored integer value
    Node* next;       // Pointer to the next node in the ring

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

/*
ALGORITHM 1: INSERT AT BEGINNING (NEW HEAD)
1. Allocate new node: `newNode = new Node(value)`.
2. CASE 1: List is empty (`head == nullptr`):
   Set `head = newNode`.
   Point `newNode->next = head;` (self-loop: a 1-node ring points to itself).
   Return.
3. CASE 2: List contains one or more nodes:
   a. We must locate the LAST node (tail) in the ring, because its `next` pointer
      must be updated to point to the new head!
   b. Pointer `tail = head;`
   c. Loop while `tail->next != head`:
      `tail = tail->next;`
   d. Set `newNode->next = head;` (new node points to old head)
   e. Set `tail->next = newNode;` (last node now points to new node)
   f. Update `head = newNode;` (head now points to new node)
*/
void insertAtBeginning(Node* &head, int value) {
    Node* newNode = new Node(value);

    // Case 1: Empty list
    if (head == nullptr) {
        head = newNode;
        newNode->next = head; // Points to itself to form a closed ring
        cout << ">> Inserted [" << value << "] as the first node of circular ring.\n";
        return;
    }

    // Case 2: Multi-node list: find tail node
    Node* tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }

    newNode->next = head; // Step d: New node points to current head
    tail->next = newNode; // Step e: Tail re-routed to new node
    head = newNode;       // Step f: Head updated to new node
    cout << ">> Inserted [" << value << "] at beginning of circular list (New Head).\n";
}

/*
ALGORITHM 2: INSERT AT END
1. Allocate new node: `newNode = new Node(value)`.
2. CASE 1: Empty list (`head == nullptr`):
   `head = newNode; newNode->next = head; return;`
3. CASE 2: Existing nodes:
   a. Find tail: `tail = head; while (tail->next != head) tail = tail->next;`
   b. `tail->next = newNode;` (current tail links to new node)
   c. `newNode->next = head;` (new node closes the ring back to head)
   (Notice: `head` remains unchanged!)
*/
void insertAtEnd(Node* &head, int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = newNode;
        newNode->next = head;
        cout << ">> Inserted [" << value << "] as first node of circular ring.\n";
        return;
    }

    Node* tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }

    tail->next = newNode; // Tail points forward to new node
    newNode->next = head; // New node points back to head to close ring
    cout << ">> Inserted [" << value << "] at the end of circular list.\n";
}

/*
ALGORITHM 3: DELETE FROM BEGINNING (DELETE HEAD)
1. CASE 1: Empty list (`head == nullptr`):
   Report Underflow and return false.
2. CASE 2: Single-node list (`head->next == head`):
   `delete head; head = nullptr; return true;`
3. CASE 3: Multi-node list:
   a. Find tail node: `tail = head; while (tail->next != head) tail = tail->next;`
   b. Save target node: `Node* temp = head;`
   c. Re-route tail to skip old head: `tail->next = head->next;`
   d. Advance head: `head = head->next;`
   e. Delete old head: `delete temp;`
*/
bool deleteFromBeginning(Node* &head) {
    if (head == nullptr) {
        cout << "[ERROR] Cannot delete from an empty circular linked list!\n";
        return false;
    }

    // Case 2: Only one node in the ring
    if (head->next == head) {
        int val = head->data;
        delete head;
        head = nullptr;
        cout << ">> Deleted only remaining node [" << val << "]. List is now empty.\n";
        return true;
    }

    // Case 3: Multiple nodes
    Node* tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }

    Node* oldHead = head;
    int val = oldHead->data;

    tail->next = head->next; // Tail bypasses old head
    head = head->next;       // Head moves to next node
    delete oldHead;          // Free memory

    cout << ">> Deleted head node [" << val << "] from circular list.\n";
    return true;
}

/*
ALGORITHM 4: DELETE FROM END (DELETE TAIL)
1. CASE 1: Empty list (`head == nullptr`):
   Report underflow and return false.
2. CASE 2: Single-node list (`head->next == head`):
   `delete head; head = nullptr; return true;`
3. CASE 3: Multi-node list:
   a. We need to reach the second-to-last node (pre-tail) so we can update its `next`!
   b. Pointer `current = head;`
   c. Loop while `current->next->next != head`:
      `current = current->next;`
   d. The tail to be deleted is `Node* tail = current->next;`
   e. Connect second-to-last node to head: `current->next = head;`
   f. Delete tail: `delete tail;`
*/
bool deleteFromEnd(Node* &head) {
    if (head == nullptr) {
        cout << "[ERROR] Cannot delete from empty circular list!\n";
        return false;
    }

    if (head->next == head) {
        int val = head->data;
        delete head;
        head = nullptr;
        cout << ">> Deleted only remaining node [" << val << "]. List is now empty.\n";
        return true;
    }

    // Find node right before tail
    Node* current = head;
    while (current->next->next != head) {
        current = current->next;
    }

    Node* tailToDelete = current->next;
    int val = tailToDelete->data;

    current->next = head; // Predecessor links back to head, closing the ring
    delete tailToDelete;  // Free memory

    cout << ">> Deleted tail node [" << val << "] from end of circular list.\n";
    return true;
}

/*
ALGORITHM 5: SAFE CIRCULAR TRAVERSAL AND DISPLAY
1. If `head == nullptr`, print "[EMPTY]" and return.
2. Pointer `temp = head`.
3. Use a `do-while` loop:
   a. Print `temp->data` and memory addresses.
   b. Advance: `temp = temp->next`.
   c. Condition: `while (temp != head)`.
   WHY DO-WHILE?
   Because `temp` starts AT `head`!
   A standard `while (temp != head)` would evaluate to False immediately on step 1
   and print nothing! `do-while` ensures we process the head node first, step forward,
   and only stop when we loop completely back to `head`.
*/
void displayCircularList(const Node* head) {
    if (head == nullptr) {
        cout << "\n[INFO] Circular list is empty.\n";
        return;
    }

    cout << "\n--------------------------------------------------------------\n";
    cout << left << setw(18) << "Node Address"
         << setw(10) << "Value"
         << setw(18) << "Next Address"
         << setw(16) << "Ring Status" << "\n";
    cout << "--------------------------------------------------------------\n";

    const Node* temp = head;
    do {
        cout << left << setw(18) << temp
             << setw(10) << temp->data
             << setw(18) << temp->next;

        if (temp->next == head) {
            cout << "<-- WRAPS TO HEAD!\n";
        } else {
            cout << "--> Next In Ring\n";
        }

        temp = temp->next;
    } while (temp != head);

    cout << "--------------------------------------------------------------\n";

    // Visual ring trace
    cout << "Ring Trace: (HEAD) ";
    temp = head;
    do {
        cout << "[" << temp->data << "] -> ";
        temp = temp->next;
    } while (temp != head);
    cout << "(HEAD: " << head->data << ") [Loop Complete]\n\n";
}

// Memory cleanup utility for circular linked list
void freeCircularList(Node* &head) {
    if (head == nullptr) return;

    Node* current = head;
    Node* nextNode = nullptr;

    // First, break the cycle to prevent infinite cleanup loop
    Node* tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }
    tail->next = nullptr; // List is now a standard linear list!

    // Now delete linearly
    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    cout << ">> Memory cleanup: Circular ring safely broken and all nodes freed.\n";
}

// Interactive demonstration runner
int main() {
    Node* ringList = nullptr;

    cout << "==============================================================\n";
    cout << "   CIRCULAR SINGLY LINKED LIST: OPERATIONS & DEMO            \n";
    cout << "==============================================================\n";

    // 1. Insertion at End
    cout << "\n--- DEMO STEP 1: Inserting elements at End (10, 20, 30) ---\n";
    insertAtEnd(ringList, 10);
    insertAtEnd(ringList, 20);
    insertAtEnd(ringList, 30);
    displayCircularList(ringList);

    // 2. Insertion at Beginning
    cout << "--- DEMO STEP 2: Inserting elements at Beginning (5, 1) ---\n";
    insertAtBeginning(ringList, 5);
    insertAtBeginning(ringList, 1);
    displayCircularList(ringList);

    // 3. Deletion from Beginning
    cout << "--- DEMO STEP 3: Deleting Head Node (1) ---\n";
    deleteFromBeginning(ringList);
    displayCircularList(ringList);

    // 4. Deletion from End
    cout << "--- DEMO STEP 4: Deleting Tail Node (30) ---\n";
    deleteFromEnd(ringList);
    displayCircularList(ringList);

    // 5. Memory Cleanup
    cout << "--- DEMO STEP 5: Safe Ring Destruction and Memory Freeing ---\n";
    freeCircularList(ringList);

    cout << "\n==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
1. Insert at end: 10, 20, 30 -> Ring: 10 -> 20 -> 30 -> (10)
2. Insert at begin: 5, 1    -> Ring: 1 -> 5 -> 10 -> 20 -> 30 -> (1)
3. Delete head: 1            -> Ring: 5 -> 10 -> 20 -> 30 -> (5)
4. Delete tail: 30           -> Ring: 5 -> 10 -> 20 -> (5)
5. Cleanup memory

SAMPLE OUTPUT:
==============================================================
   CIRCULAR SINGLY LINKED LIST: OPERATIONS & DEMO            
==============================================================

--- DEMO STEP 1: Inserting elements at End (10, 20, 30) ---
>> Inserted [10] as first node of circular ring.
>> Inserted [20] at the end of circular list.
>> Inserted [30] at the end of circular list.

--------------------------------------------------------------
Node Address      Value     Next Address      Ring Status     
--------------------------------------------------------------
0x24d0840dc80     10        0x24d0840dc60     --> Next In Ring
0x24d0840dc60     20        0x24d0840dca0     --> Next In Ring
0x24d0840dca0     30        0x24d0840dc80     <-- WRAPS TO HEAD!
--------------------------------------------------------------
Ring Trace: (HEAD) [10] -> [20] -> [30] -> (HEAD: 10) [Loop Complete]

--- DEMO STEP 2: Inserting elements at Beginning (5, 1) ---
>> Inserted [5] at beginning of circular list (New Head).
>> Inserted [1] at beginning of circular list (New Head).

--------------------------------------------------------------
Node Address      Value     Next Address      Ring Status     
--------------------------------------------------------------
0x24d0840dce0     1         0x24d0840dcc0     --> Next In Ring
0x24d0840dcc0     5         0x24d0840dc80     --> Next In Ring
0x24d0840dc80     10        0x24d0840dc60     --> Next In Ring
0x24d0840dc60     20        0x24d0840dca0     --> Next In Ring
0x24d0840dca0     30        0x24d0840dce0     <-- WRAPS TO HEAD!
--------------------------------------------------------------
Ring Trace: (HEAD) [1] -> [5] -> [10] -> [20] -> [30] -> (HEAD: 1) [Loop Complete]

--- DEMO STEP 3: Deleting Head Node (1) ---
>> Deleted head node [1] from circular list.

--------------------------------------------------------------
Node Address      Value     Next Address      Ring Status     
--------------------------------------------------------------
0x24d0840dcc0     5         0x24d0840dc80     --> Next In Ring
0x24d0840dc80     10        0x24d0840dc60     --> Next In Ring
0x24d0840dc60     20        0x24d0840dca0     --> Next In Ring
0x24d0840dca0     30        0x24d0840dcc0     <-- WRAPS TO HEAD!
--------------------------------------------------------------
Ring Trace: (HEAD) [5] -> [10] -> [20] -> [30] -> (HEAD: 5) [Loop Complete]

--- DEMO STEP 4: Deleting Tail Node (30) ---
>> Deleted tail node [30] from end of circular list.

--------------------------------------------------------------
Node Address      Value     Next Address      Ring Status     
--------------------------------------------------------------
0x24d0840dcc0     5         0x24d0840dc80     --> Next In Ring
0x24d0840dc80     10        0x24d0840dc60     --> Next In Ring
0x24d0840dc60     20        0x24d0840dcc0     <-- WRAPS TO HEAD!
--------------------------------------------------------------
Ring Trace: (HEAD) [5] -> [10] -> [20] -> (HEAD: 5) [Loop Complete]

--- DEMO STEP 5: Safe Ring Destruction and Memory Freeing ---
>> Memory cleanup: Circular ring safely broken and all nodes freed.

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

STEP-BY-STEP DRY RUN: INSERT AT BEGINNING (INSERT 5 BEFORE 10)
List before:
[10 | next: 0x100] (single-node ring, head = 0x100)
newNode allocated at 0x200: [5 | next: nullptr]

1. Find tail:
   tail = head (0x100)
   tail->next == head (0x100 == 0x100), loop stops immediately.
2. newNode->next = head -> 0x200's next points to 0x100.
3. tail->next = newNode -> 0x100's next points to 0x200.
4. head = newNode -> head updated to 0x200.
List after:
[5 (0x200) | next: 0x100] -> [10 (0x100) | next: 0x200] -> wraps back to 5.

========================================================================================
TIME COMPLEXITY:
- Insert at Beginning: O(N) because we must traverse to tail to update its `next` pointer.
  *(Note: If a `tail` pointer is kept instead of `head`, this becomes O(1)).*
- Insert at End: O(N) to locate the tail.
- Delete from Beginning: O(N) to locate tail and update its `next` to the new head.
- Delete from End: O(N) to find the node before tail.
- Traversal: O(N) to visit each node exactly once.

SPACE COMPLEXITY:
- Auxiliary Space: O(1).
- Total Dynamic Memory: O(N) heap memory, where each node is 16 bytes.

WHY?
Because a singly linked circular list has no direct backward link from `head` to `tail`.
Finding the node that wraps to `head` requires circulating through all N nodes.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Infinite Loops in Traversal (CRITICAL):
   - Writing `while (temp != nullptr)` causes an infinite loop because a circular list
     NEVER ends in `nullptr`!
   - Writing `while (temp != head)` before advancing `temp` terminates before printing
     anything! Always use `do { ... temp = temp->next; } while (temp != head);`.
2. Forgetting to Update Tail on Head Deletion:
   - If you delete `head` and just do `head = head->next`, the old tail node STILL
     points to the deleted head address! You must update `tail->next = newHead`.
3. Memory Leak on Circular List Deletion:
   - Trying to free a circular list with a standard `while (current != nullptr)` will loop
     forever, repeatedly trying to free already freed memory (Double Free / Crash).
     Always break the cycle by setting `tail->next = nullptr` first!

========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Single node ring points to itself: `head->next = head;`
[ ] 2. Insert begin/end requires walking to tail: `while (tail->next != head) tail = tail->next;`
[ ] 3. Traversal MUST use `do-while`: `do { print; temp = temp->next; } while (temp != head);`
[ ] 4. Freeing circular list: set `tail->next = nullptr` first, then delete linearly.
========================================================================================
*/
