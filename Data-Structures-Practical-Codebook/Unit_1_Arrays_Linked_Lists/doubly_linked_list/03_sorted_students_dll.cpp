/*
========================================================================================
PROGRAM HEADER:
- Program Number: 03
- Program Title: Sorted Student Registry using Doubly Linked List (DLL)
- Unit: Unit I - Introduction to Data Structures and Memory Representation
- Relevant Curriculum Topic: Doubly Linked List Operations (Sorted Insert, Delete, Bidirectional Traversal)
- Course Code: CE25PCC-203 (Data Structures Laboratory) - Group A, Assignment 3
- Problem Statement:
  Write a program to maintain a list of students sorted by roll number using a doubly
  linked list. Implement functions to:
  a. Insert a student so that the list remains sorted
  b. Delete a student by roll number
  c. Traverse the list forward to display all students
  d. Traverse backward to display all students in reverse order
- Data Structure Used: Doubly Linked List with Two Pointers per Node (`prev` and `next`)
- What This Program Demonstrates:
  Bidirectional pointer manipulation, sorted linked list insertion (O(N) search + O(1) link),
  safe node detachment without memory leaks, forward and backward traversal.
========================================================================================

CONCEPT: WHY USE A DOUBLY LINKED LIST (DLL)?
In a Singly Linked List (SLL), every node only knows where the NEXT node is.
If you need to:
1. Traverse in reverse (e.g., display highest roll number first), SLL cannot do it
   without recursion or a separate stack.
2. Delete a node, SLL requires maintaining a `prev` pointer manually during traversal
   because a node cannot look backwards to fix the broken chain.

A Doubly Linked List gives every node TWO pointer links:
- `next`: Points to the successor node (or `nullptr` if it is the last node).
- `prev`: Points to the predecessor node (or `nullptr` if it is the first node).

TRADE-OFF:
- Extra 8 bytes of pointer memory per node on 64-bit architecture.
- Every insertion and deletion requires updating FOUR pointer connections instead of two.
  Order of pointer assignments is critical!
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Definition of a Doubly Linked List Node
struct StudentNode {
    int rollNo;               // Key used for sorting in ascending order
    string name;              // Student Name
    float cgpa;               // Student CGPA
    StudentNode* prev;        // Pointer to previous node in sequence
    StudentNode* next;        // Pointer to next node in sequence

    // Constructor to initialize a freshly allocated node
    StudentNode(int roll, string studentName, float grade) {
        rollNo = roll;
        name = studentName;
        cgpa = grade;
        prev = nullptr;       // Standalone node has no previous neighbor
        next = nullptr;       // Standalone node has no next neighbor
    }
};

/*
ALGORITHM 1: INSERT STUDENT IN SORTED ORDER
1. Allocate new node: `newNode = new StudentNode(roll, name, cgpa)`.
2. CASE 1: List is empty (`head == nullptr`):
   Set `head = newNode`.
   Return.
3. CASE 2: New node should be inserted before the current head (`newNode->rollNo < head->rollNo`):
   a. `newNode->next = head;`
   b. `head->prev = newNode;`
   c. `head = newNode;`
   Return.
4. CASE 3 & 4: Insert in middle or at end:
   a. Start pointer: `current = head`.
   b. Traverse forward while `current->next != nullptr` AND `current->next->rollNo < newNode->rollNo`:
      `current = current->next;`
   c. We now know `newNode` belongs immediately after `current`.
   d. Wire `newNode` forwards: `newNode->next = current->next;`
   e. Wire `newNode` backwards: `newNode->prev = current;`
   f. If `current->next != nullptr` (inserting in middle):
      `current->next->prev = newNode;`
   g. Wire `current` forward to `newNode`: `current->next = newNode;`

WHY IS THE ORDER OF STEPS (d, e, f, g) CRITICAL?
If we do `current->next = newNode` first, we overwrite the address of the next node!
We would permanently lose access to the remainder of the linked list!
Always link the new node to its neighbors before re-routing the neighbors to the new node.
*/
void insertSorted(StudentNode* &head, int roll, string name, float cgpa) {
    StudentNode* newNode = new StudentNode(roll, name, cgpa);

    // Case 1: Empty List
    if (head == nullptr) {
        head = newNode;
        cout << ">> Inserted Roll " << roll << " (" << name << ") as first/head node.\n";
        return;
    }

    // Case 2: Insert before current head (New smallest roll number)
    if (roll < head->rollNo) {
        newNode->next = head;       // New node points forward to current head
        head->prev = newNode;       // Old head points backward to new node
        head = newNode;             // Head pointer updated to new node
        cout << ">> Inserted Roll " << roll << " (" << name << ") at the beginning (New Head).\n";
        return;
    }

    // Case 3 & 4: Insert in middle or at the end
    StudentNode* current = head;
    // Walk through until current is the last node OR current->next has a larger roll number
    while (current->next != nullptr && current->next->rollNo < roll) {
        current = current->next;
    }

    // Connect newNode to its successor
    newNode->next = current->next;
    newNode->prev = current;

    // If there is a successor node (middle insertion), update its backward pointer
    if (current->next != nullptr) {
        current->next->prev = newNode;
        cout << ">> Inserted Roll " << roll << " (" << name << ") in middle between Roll " 
             << current->rollNo << " and Roll " << newNode->next->rollNo << ".\n";
    } else {
        // Tail insertion
        cout << ">> Inserted Roll " << roll << " (" << name << ") at the end of the list.\n";
    }

    // Connect current node to newNode
    current->next = newNode;
}

/*
ALGORITHM 2: DELETE STUDENT BY ROLL NUMBER
1. If list is empty (`head == nullptr`), report underflow and return false.
2. Initialize `current = head`.
3. Search for the node with `current->rollNo == targetRoll`:
   `while (current != nullptr && current->rollNo != targetRoll) current = current->next;`
4. If `current == nullptr`, student was not found. Report error and return false.
5. If found:
   CASE A: Deleting the head node (`current == head`):
       `head = head->next;`
       If `head != nullptr` (list still has nodes):
           `head->prev = nullptr;`
   CASE B: Deleting a middle or tail node (`current != head`):
       `current->prev->next = current->next;` // Predecessor skips current
       If `current->next != nullptr` (middle node):
           `current->next->prev = current->prev;` // Successor skips current
6. Delete the detached node from heap: `delete current;`
7. Report success and return true.
*/
bool deleteStudent(StudentNode* &head, int targetRoll) {
    if (head == nullptr) {
        cout << "[ERROR] Cannot delete from an empty doubly linked list!\n";
        return false;
    }

    StudentNode* current = head;
    while (current != nullptr && current->rollNo != targetRoll) {
        current = current->next;
    }

    // If target was not found in the list
    if (current == nullptr) {
        cout << "[ERROR] Student with Roll No " << targetRoll << " not found!\n";
        return false;
    }

    string removedName = current->name;

    // Case A: Deleting the Head Node
    if (current == head) {
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr; // New head's previous pointer must be null
        }
    } 
    // Case B: Deleting an Internal or Tail Node
    else {
        current->prev->next = current->next; // Bypass current in forward direction
        if (current->next != nullptr) {
            current->next->prev = current->prev; // Bypass current in backward direction
        }
    }

    // Release dynamically allocated memory
    delete current;
    cout << ">> Success: Deleted Student " << removedName << " (Roll No " << targetRoll << ").\n";
    return true;
}

/*
ALGORITHM 3: FORWARD TRAVERSAL
1. Check if `head == nullptr`. If so, print "[EMPTY]" and return.
2. Initialize `temp = head`.
3. Print header.
4. While `temp != nullptr`:
   Print details (`prev` addr, `rollNo`, `name`, `cgpa`, `next` addr).
   Advance: `temp = temp->next`.
*/
void displayForward(const StudentNode* head) {
    if (head == nullptr) {
        cout << "\n[INFO] List is empty (Forward Traversal).\n";
        return;
    }

    cout << "\n=== FORWARD TRAVERSAL (Sorted Ascending by Roll Number) ===\n";
    cout << left << setw(16) << "Prev Addr"
         << setw(10) << "Roll"
         << setw(20) << "Name"
         << setw(8)  << "CGPA"
         << setw(16) << "Next Addr" << "\n";
    cout << "----------------------------------------------------------------------\n";

    const StudentNode* temp = head;
    while (temp != nullptr) {
        cout << left << setw(16) << temp->prev
             << setw(10) << temp->rollNo
             << setw(20) << temp->name
             << fixed << setprecision(2) << setw(8) << temp->cgpa
             << setw(16) << temp->next << "\n";
        temp = temp->next;
    }
    cout << "----------------------------------------------------------------------\n";
}

/*
ALGORITHM 4: BACKWARD TRAVERSAL
1. Check if `head == nullptr`. If so, print "[EMPTY]" and return.
2. Traverse forward to locate the last (tail) node:
   `tail = head; while (tail->next != nullptr) tail = tail->next;`
3. Traverse backward using `prev` links:
   `temp = tail; while (temp != nullptr) { print temp; temp = temp->prev; }`
*/
void displayBackward(const StudentNode* head) {
    if (head == nullptr) {
        cout << "\n[INFO] List is empty (Backward Traversal).\n";
        return;
    }

    // Step 2: Navigate to tail node
    const StudentNode* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    cout << "\n=== BACKWARD TRAVERSAL (Reverse Order via 'prev' Pointers) ===\n";
    cout << left << setw(16) << "Current Addr"
         << setw(10) << "Roll"
         << setw(20) << "Name"
         << setw(8)  << "CGPA"
         << setw(16) << "Prev Addr" << "\n";
    cout << "----------------------------------------------------------------------\n";

    // Step 3: Traverse backwards from tail to head
    const StudentNode* temp = tail;
    while (temp != nullptr) {
        cout << left << setw(16) << temp
             << setw(10) << temp->rollNo
             << setw(20) << temp->name
             << fixed << setprecision(2) << setw(8) << temp->cgpa
             << setw(16) << temp->prev << "\n";
        temp = temp->prev; // Step backwards!
    }
    cout << "----------------------------------------------------------------------\n\n";
}

// Memory cleanup utility to prevent leaks
void freeDoublyList(StudentNode* &head) {
    StudentNode* current = head;
    while (current != nullptr) {
        StudentNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    cout << ">> Memory cleanup: All doubly linked list nodes successfully freed.\n";
}

// Interactive demonstration runner
int main() {
    StudentNode* studentDLL = nullptr;

    cout << "==============================================================\n";
    cout << "   SORTED STUDENT REGISTRY (DOUBLY LINKED LIST)              \n";
    cout << "==============================================================\n";

    // 1. Inserting nodes in arbitrary order to prove automatic sorted placement
    cout << "\n--- DEMO STEP 1: Inserting records in arbitrary order ---\n";
    cout << "1. Inserting Roll 104 (Head):\n";
    insertSorted(studentDLL, 104, "Chetan Joshi", 8.20f);

    cout << "2. Inserting Roll 102 (Smaller than Head -> Becomes New Head):\n";
    insertSorted(studentDLL, 102, "Bhavna Patil", 9.15f);

    cout << "3. Inserting Roll 106 (Greater than all -> Appended at End):\n";
    insertSorted(studentDLL, 106, "Esha Verma", 7.80f);

    cout << "4. Inserting Roll 103 (Middle insertion between 102 and 104):\n";
    insertSorted(studentDLL, 103, "Aditya Deshmukh", 9.40f);

    cout << "5. Inserting Roll 101 (Smaller than all -> New Head):\n";
    insertSorted(studentDLL, 101, "Aarav Sharma", 8.90f);

    cout << "6. Inserting Roll 105 (Middle insertion between 104 and 106):\n";
    insertSorted(studentDLL, 105, "Divya Kulkarni", 8.65f);

    // 2. Traversal demonstrations
    displayForward(studentDLL);
    displayBackward(studentDLL);

    // 3. Deletion demonstrations across all boundary cases:
    cout << "--- DEMO STEP 2: Deleting Head Node (Roll 101) ---\n";
    deleteStudent(studentDLL, 101);
    displayForward(studentDLL);

    cout << "--- DEMO STEP 3: Deleting Middle Node (Roll 104) ---\n";
    deleteStudent(studentDLL, 104);
    displayForward(studentDLL);

    cout << "--- DEMO STEP 4: Deleting Tail Node (Roll 106) ---\n";
    deleteStudent(studentDLL, 106);
    displayForward(studentDLL);
    displayBackward(studentDLL);

    // 4. Boundary Error Testing
    cout << "--- DEMO STEP 5: Testing deletion of non-existent Roll 999 ---\n";
    deleteStudent(studentDLL, 999);

    // 5. Memory Cleanup
    cout << "\n--- DEMO STEP 6: Memory Cleanup ---\n";
    freeDoublyList(studentDLL);

    cout << "\n==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
Input stream of students inserted out of order:
1. Roll 104
2. Roll 102
3. Roll 106
4. Roll 103
5. Roll 101
6. Roll 105
Final Expected Forward Sorted Order: 101 <-> 102 <-> 103 <-> 104 <-> 105 <-> 106
Reverse Expected Backward Order:     106 <-> 105 <-> 104 <-> 103 <-> 102 <-> 101

SAMPLE OUTPUT:
==============================================================
   SORTED STUDENT REGISTRY (DOUBLY LINKED LIST)              
==============================================================

--- DEMO STEP 1: Inserting records in arbitrary order ---
1. Inserting Roll 104 (Head):
>> Inserted Roll 104 (Chetan Joshi) as first/head node.
2. Inserting Roll 102 (Smaller than Head -> Becomes New Head):
>> Inserted Roll 102 (Bhavna Patil) at the beginning (New Head).
3. Inserting Roll 106 (Greater than all -> Appended at End):
>> Inserted Roll 106 (Esha Verma) at the end of the list.
4. Inserting Roll 103 (Middle insertion between 102 and 104):
>> Inserted Roll 103 (Aditya Deshmukh) in middle between Roll 102 and Roll 104.
5. Inserting Roll 101 (Smaller than all -> New Head):
>> Inserted Roll 101 (Aarav Sharma) at the beginning (New Head).
6. Inserting Roll 105 (Middle insertion between 104 and 106):
>> Inserted Roll 105 (Divya Kulkarni) in middle between Roll 104 and Roll 106.

=== FORWARD TRAVERSAL (Sorted Ascending by Roll Number) ===
Prev Addr       Roll      Name                CGPA    Next Addr       
----------------------------------------------------------------------
0               101       Aarav Sharma        8.90    0x1c3040        
0x1c3000        102       Bhavna Patil        9.15    0x1c3080        
0x1c3040        103       Aditya Deshmukh     9.40    0x1c2f80        
0x1c3080        104       Chetan Joshi        8.20    0x1c30c0        
0x1c2f80        105       Divya Kulkarni      8.65    0x1c2fc0        
0x1c30c0        106       Esha Verma          7.80    0               
----------------------------------------------------------------------

=== BACKWARD TRAVERSAL (Reverse Order via 'prev' Pointers) ===
Current Addr    Roll      Name                CGPA    Prev Addr       
----------------------------------------------------------------------
0x1c2fc0        106       Esha Verma          7.80    0x1c30c0        
0x1c30c0        105       Divya Kulkarni      8.65    0x1c2f80        
0x1c2f80        104       Chetan Joshi        8.20    0x1c3080        
0x1c3080        103       Aditya Deshmukh     9.40    0x1c3040        
0x1c3040        102       Bhavna Patil        9.15    0x1c3000        
0x1c3000        101       Aarav Sharma        8.90    0               
----------------------------------------------------------------------

--- DEMO STEP 2: Deleting Head Node (Roll 101) ---
>> Success: Deleted Student Aarav Sharma (Roll No 101).

=== FORWARD TRAVERSAL (Sorted Ascending by Roll Number) ===
Prev Addr       Roll      Name                CGPA    Next Addr       
----------------------------------------------------------------------
0               102       Bhavna Patil        9.15    0x1c3080        
0x1c3040        103       Aditya Deshmukh     9.40    0x1c2f80        
0x1c3080        104       Chetan Joshi        8.20    0x1c30c0        
0x1c2f80        105       Divya Kulkarni      8.65    0x1c2fc0        
0x1c30c0        106       Esha Verma          7.80    0               
----------------------------------------------------------------------

--- DEMO STEP 3: Deleting Middle Node (Roll 104) ---
>> Success: Deleted Student Chetan Joshi (Roll No 104).

=== FORWARD TRAVERSAL (Sorted Ascending by Roll Number) ===
Prev Addr       Roll      Name                CGPA    Next Addr       
----------------------------------------------------------------------
0               102       Bhavna Patil        9.15    0x1c3080        
0x1c3040        103       Aditya Deshmukh     9.40    0x1c30c0        
0x1c3080        105       Divya Kulkarni      8.65    0x1c2fc0        
0x1c30c0        106       Esha Verma          7.80    0               
----------------------------------------------------------------------

--- DEMO STEP 4: Deleting Tail Node (Roll 106) ---
>> Success: Deleted Student Esha Verma (Roll No 106).

=== FORWARD TRAVERSAL (Sorted Ascending by Roll Number) ===
Prev Addr       Roll      Name                CGPA    Next Addr       
----------------------------------------------------------------------
0               102       Bhavna Patil        9.15    0x1c3080        
0x1c3040        103       Aditya Deshmukh     9.40    0x1c30c0        
0x1c3080        105       Divya Kulkarni      8.65    0               
----------------------------------------------------------------------

=== BACKWARD TRAVERSAL (Reverse Order via 'prev' Pointers) ===
Current Addr    Roll      Name                CGPA    Prev Addr       
----------------------------------------------------------------------
0x1c30c0        105       Divya Kulkarni      8.65    0x1c3080        
0x1c3080        103       Aditya Deshmukh     9.40    0x1c3040        
0x1c3040        102       Bhavna Patil        9.15    0               
----------------------------------------------------------------------

--- DEMO STEP 5: Testing deletion of non-existent Roll 999 ---
[ERROR] Student with Roll No 999 not found!

--- DEMO STEP 6: Memory Cleanup ---
>> Memory cleanup: All doubly linked list nodes successfully freed.

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

STEP-BY-STEP DRY RUN: INSERTING ROLL 103 (BETWEEN 102 AND 104)
Existing Sub-chain:
[Roll 102 | prev: null | next: 0x400] <=====> [Roll 104 | prev: 0x200 | next: null]
Current points to Node 102 (0x200).
newNode allocated at 0x300: [Roll 103 | prev: null | next: null]

Step 1: newNode->next = current->next;
        newNode->next = 0x400 (points to 104)
Step 2: newNode->prev = current;
        newNode->prev = 0x200 (points back to 102)
Step 3: current->next->prev = newNode;
        Node 104's prev field updated from 0x200 to 0x300 (points back to 103)
Step 4: current->next = newNode;
        Node 102's next field updated from 0x400 to 0x300 (points forward to 103)

Final 4-link verified connection:
Node 102 (next -> 103)
Node 103 (prev -> 102, next -> 104)
Node 104 (prev -> 103)
Sorted sequence preserved: 102 <-> 103 <-> 104.

========================================================================================
TIME COMPLEXITY:
- Sorted Insertion:
  * Best case: O(1) if new node becomes head immediately (`newNode->rollNo < head->rollNo`).
  * Worst case: O(N) if inserted at tail or near end (walks through N nodes).
  * Average case: O(N).
- Deletion by Roll:
  * Best case: O(1) if head node is deleted.
  * Worst case: O(N) if node is at tail or absent.
  * Average case: O(N).
- Forward Traversal: O(N) - visits every node once.
- Backward Traversal: O(N) - finds tail in O(N) + traverses back in O(N) = O(N).

SPACE COMPLEXITY:
- Auxiliary Space: O(1).
- Total Dynamic Memory: O(N) heap memory.
  Each node consumes: 4 bytes (int) + 32 bytes (string) + 4 bytes (float) + 16 bytes (two 8-byte pointers) + padding.

WHY?
Even though insertion and deletion of links takes O(1) time once the position is known,
locating the sorted position in a doubly linked list requires linear scanning from `head`
because there is no O(1) random index access.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Forgetting to Update BOTH `prev` and `next`:
   - Beginners often update `newNode->next` and `current->next`, but forget `current->next->prev`
     and `newNode->prev`. This leaves backward traversal broken or causes segmentation faults!
2. Deleting Head Node without Updating `head->prev`:
   - When deleting the head node (`head = head->next`), if the list now contains at least
     one node, you MUST set `head->prev = nullptr`! Otherwise, the new head still points
     to the deleted memory block.
3. Order of Operations when Linking:
   - Always connect the new node's outgoing links FIRST (`newNode->next = ...`, `newNode->prev = ...`)
     before severing existing connections.
4. Memory Leak on Deletion:
   - Forgetting `delete current;` after re-linking neighbors leaks heap memory.

========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Define `struct StudentNode { int rollNo; string name; float cgpa; StudentNode* prev; StudentNode* next; };`
[ ] 2. Sorted Insert - 4 Pointer Rewiring Rule:
       - `newNode->next = current->next;`
       - `newNode->prev = current;`
       - `if (current->next != nullptr) current->next->prev = newNode;`
       - `current->next = newNode;`
[ ] 3. New Head Insert: `newNode->next = head; head->prev = newNode; head = newNode;`
[ ] 4. Deletion Bypass Rule:
       - `current->prev->next = current->next;`
       - `if (current->next != nullptr) current->next->prev = current->prev;`
[ ] 5. Backward traversal: loop `tail = tail->next` to reach end, then `temp = temp->prev`.
========================================================================================
*/
