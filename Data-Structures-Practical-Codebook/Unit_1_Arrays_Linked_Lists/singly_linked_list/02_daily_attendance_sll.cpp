/*
========================================================================================
PROGRAM HEADER:
- Program Number: 02
- Program Title: Student Daily Attendance Management using Singly Linked List (SLL)
- Unit: Unit I - Introduction to Data Structures and Memory Representation
- Relevant Curriculum Topic: Singly Linked List Operations (Append, Update, Count, Display)
- Course Code: CE25PCC-203 (Data Structures Laboratory) - Group A, Assignment 2
- Problem Statement:
  Create a program to maintain daily attendance of students using a singly linked list.
  Write functions to:
  a. Insert attendance (P/A) at the end of the list
  b. Update the attendance of a given day
  c. Calculate total number of Present and Absent days
  d. Display the complete attendance list
- Data Structure Used: Singly Linked List with Dynamic Node Allocation (`new`/`delete`)
- What This Program Demonstrates:
  Pointer chaining (`next`), heap memory management, linear traversal, non-contiguous
  node allocation, in-place data updates, and defensive null pointer checks.
========================================================================================

CONCEPT: WHY USE A SINGLY LINKED LIST INSTEAD OF AN ARRAY?
1. Dynamic Size: A semester's working days cannot always be determined ahead of time
   (e.g., unplanned holidays, extra remedial classes). An array requires pre-allocating
   fixed memory. A linked list grows day-by-day with zero wasted slots.
2. No Costly Shifts on Insertion: When appending or inserting, no existing elements
   need to move in physical RAM. We simply allocate a node anywhere in the heap and
   wire the previous node's `next` pointer to it.
3. Non-Contiguous Storage: Unlike arrays which need a single massive contiguous block
   of memory, linked list nodes can reside in scattered, fragmented heap blocks.

WHAT IS A NODE?
A Node is a self-referential structure containing:
- Data members: `dayNumber` (integer) and `status` ('P' for Present, 'A' for Absent).
- Pointer member: `next`, which stores the hexadecimal memory address of the next node.
- The final node's `next` pointer holds `nullptr` to mark the end of the list.
*/

#include <iostream>
#include <iomanip>

using namespace std;

// Definition of a Singly Linked List Node
struct AttendanceNode {
    int dayNumber;            // Day number (Day 1, Day 2, Day 3, ...)
    char status;              // 'P' for Present, 'A' for Absent
    AttendanceNode* next;     // Pointer to the next node in the chain

    // Constructor for clean, educational initialization
    AttendanceNode(int day, char stat) {
        dayNumber = day;
        status = stat;
        next = nullptr;       // Initially, a standalone node points to nothing
    }
};

/*
ALGORITHM 1: INSERT ATTENDANCE AT THE END (APPEND)
1. Allocate new node in heap memory: `newNode = new AttendanceNode(day, status)`.
2. Check if allocation was successful (standard C++ throws `std::bad_alloc` if RAM is full).
3. If the list is empty (`head == nullptr`):
   Set `head = newNode`.
   (The new node becomes the very first node).
4. Otherwise (`head != nullptr`):
   Start a temporary pointer `temp = head`.
   Traverse until the last node: `while (temp->next != nullptr) temp = temp->next;`
   Link the last node to the new node: `temp->next = newNode;`
5. Report successful append.

WHY DO WE CHECK `temp->next != nullptr` INSTEAD OF `temp != nullptr`?
Because we need to STOP at the last valid node so we can modify its `next` pointer!
If we checked `temp != nullptr`, `temp` would fall off the end and become `nullptr`,
and attempting `temp->next = newNode` would cause a fatal segmentation fault!
*/
void insertAttendance(AttendanceNode* &head, int day, char status) {
    // Validate attendance status character
    if (status != 'P' && status != 'p' && status != 'A' && status != 'a') {
        cout << "[ERROR] Invalid status '" << status << "'. Only 'P' (Present) or 'A' (Absent) allowed.\n";
        return;
    }

    char normalizedStatus = (status == 'p') ? 'P' : ((status == 'a') ? 'A' : status);

    // Create the new node on the heap
    AttendanceNode* newNode = new AttendanceNode(day, normalizedStatus);

    // Case 1: List is currently empty
    if (head == nullptr) {
        head = newNode; // Head now points directly to the newly created node
        cout << ">> Day " << day << " [" << normalizedStatus << "] inserted as the first node.\n";
        return;
    }

    // Case 2: List contains existing nodes; traverse to the tail node
    AttendanceNode* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next; // Advance to the adjacent linked node
    }

    // Link the last node's next pointer to our new node
    temp->next = newNode;
    cout << ">> Day " << day << " [" << normalizedStatus << "] appended to the end of the list.\n";
}

/*
ALGORITHM 2: UPDATE ATTENDANCE OF A GIVEN DAY
1. If list is empty (`head == nullptr`), report list is empty and exit.
2. Initialize `temp = head`.
3. Traverse the list:
   `while (temp != nullptr)`:
       If `temp->dayNumber == targetDay`:
           Update `temp->status = newStatus`.
           Display success message and return true.
       Advance: `temp = temp->next`.
4. If end of list reached without finding `targetDay`:
   Display error "Day not found" and return false.
*/
bool updateAttendance(AttendanceNode* head, int targetDay, char newStatus) {
    if (head == nullptr) {
        cout << "[ERROR] Attendance list is empty. Nothing to update.\n";
        return false;
    }

    if (newStatus != 'P' && newStatus != 'p' && newStatus != 'A' && newStatus != 'a') {
        cout << "[ERROR] Invalid status '" << newStatus << "'. Must be 'P' or 'A'.\n";
        return false;
    }

    char normalized = (newStatus == 'p') ? 'P' : ((newStatus == 'a') ? 'A' : newStatus);

    AttendanceNode* temp = head;
    while (temp != nullptr) {
        if (temp->dayNumber == targetDay) {
            char oldStatus = temp->status;
            temp->status = normalized; // Direct in-place mutation of the node's data
            cout << ">> Success: Day " << targetDay << " attendance updated from [" 
                 << oldStatus << "] to [" << normalized << "].\n";
            return true;
        }
        temp = temp->next;
    }

    cout << "[ERROR] Day " << targetDay << " not found in attendance records.\n";
    return false;
}

/*
ALGORITHM 3: CALCULATE TOTAL PRESENT AND ABSENT DAYS
1. Initialize counters: `presentCount = 0`, `absentCount = 0`.
2. Start traversal from `head`: `temp = head`.
3. Loop while `temp != nullptr`:
       If `temp->status == 'P'`, increment `presentCount`.
       Else if `temp->status == 'A'`, increment `absentCount`.
       Advance to next node: `temp = temp->next`.
4. Return results and display percentage attendance.
*/
void calculateAttendanceStats(const AttendanceNode* head, int &presentCount, int &absentCount) {
    presentCount = 0;
    absentCount = 0;

    const AttendanceNode* temp = head;
    while (temp != nullptr) {
        if (temp->status == 'P') {
            presentCount++;
        } else if (temp->status == 'A') {
            absentCount++;
        }
        temp = temp->next;
    }

    int totalDays = presentCount + absentCount;
    cout << "\n================ ATTENDANCE SUMMARY ================\n";
    cout << " Total Working Days Recorded : " << totalDays << "\n";
    cout << " Total Days Present (P)      : " << presentCount << "\n";
    cout << " Total Days Absent (A)       : " << absentCount << "\n";
    if (totalDays > 0) {
        float percentage = (static_cast<float>(presentCount) / totalDays) * 100.0f;
        cout << " Attendance Percentage       : " << fixed << setprecision(2) 
             << percentage << "%\n";
        if (percentage < 75.0f) {
            cout << " [WARNING] Attendance is below 75% mandatory threshold!\n";
        } else {
            cout << " [STATUS] Attendance criteria satisfied (>= 75%).\n";
        }
    }
    cout << "====================================================\n\n";
}

/*
ALGORITHM 4: DISPLAY COMPLETE ATTENDANCE LIST
1. If `head == nullptr`:
   Display "[EMPTY LIST]" and return.
2. Print tabular header.
3. Pointer `temp = head`.
4. While `temp != nullptr`:
   Print node's memory address, `dayNumber`, `status`, and address of `next`.
   Advance: `temp = temp->next`.
5. Print total node count.
*/
void displayAttendanceList(const AttendanceNode* head) {
    if (head == nullptr) {
        cout << "\n[INFO] Attendance records list is completely empty.\n";
        return;
    }

    cout << "\n--------------------------------------------------------------\n";
    cout << left << setw(18) << "Node Address" 
         << setw(10) << "Day" 
         << setw(10) << "Status" 
         << setw(18) << "Next Address" << "\n";
    cout << "--------------------------------------------------------------\n";

    const AttendanceNode* temp = head;
    while (temp != nullptr) {
        cout << left << setw(18) << temp
             << setw(10) << ("Day " + to_string(temp->dayNumber))
             << setw(10) << temp->status
             << setw(18) << temp->next << "\n";
        temp = temp->next;
    }
    cout << "--------------------------------------------------------------\n";

    // Visual pointer chain
    cout << "Pointer Chain Visualization:\nHEAD -> ";
    temp = head;
    while (temp != nullptr) {
        cout << "[Day " << temp->dayNumber << " : " << temp->status << "] -> ";
        temp = temp->next;
    }
    cout << "NULL\n\n";
}

// Function to free all dynamically allocated nodes on program termination.
// Essential practice in C++ to prevent memory leaks!
void freeAttendanceList(AttendanceNode* &head) {
    AttendanceNode* current = head;
    while (current != nullptr) {
        AttendanceNode* nextNode = current->next; // Save pointer to next before deleting current
        delete current;                           // Release memory of current node back to OS
        current = nextNode;                       // Move forward
    }
    head = nullptr; // Reset head pointer to indicate empty list
    cout << ">> Memory cleanup: All attendance nodes successfully freed.\n";
}

// Interactive demonstration runner
int main() {
    AttendanceNode* attendanceHead = nullptr; // Start with an empty list

    cout << "==============================================================\n";
    cout << "   DAILY ATTENDANCE SYSTEM (SINGLY LINKED LIST)              \n";
    cout << "==============================================================\n";

    // 1. Appending initial attendance records
    cout << "\n--- DEMO STEP 1: Recording 6 Days of Initial Attendance ---\n";
    insertAttendance(attendanceHead, 1, 'P');
    insertAttendance(attendanceHead, 2, 'P');
    insertAttendance(attendanceHead, 3, 'A');
    insertAttendance(attendanceHead, 4, 'P');
    insertAttendance(attendanceHead, 5, 'A');
    insertAttendance(attendanceHead, 6, 'P');

    displayAttendanceList(attendanceHead);

    // 2. Updating attendance for a previously absent day (e.g. medical leave approved)
    cout << "--- DEMO STEP 2: Updating Day 3 from 'A' to 'P' (Leave Approved) ---\n";
    updateAttendance(attendanceHead, 3, 'P');
    displayAttendanceList(attendanceHead);

    // 3. Calculating attendance statistics
    cout << "--- DEMO STEP 3: Calculating Total Present and Absent Days ---\n";
    int pDays = 0, aDays = 0;
    calculateAttendanceStats(attendanceHead, pDays, aDays);

    // 4. Boundary Testing: Updating non-existent day
    cout << "--- DEMO STEP 4: Attempting to update non-existent Day 99 ---\n";
    updateAttendance(attendanceHead, 99, 'P');

    // 5. Boundary Testing: Invalid status character
    cout << "\n--- DEMO STEP 5: Attempting to insert invalid status 'X' ---\n";
    insertAttendance(attendanceHead, 7, 'X');

    // 6. Memory deallocation
    cout << "\n--- DEMO STEP 6: Freeing all heap memory ---\n";
    freeAttendanceList(attendanceHead);

    cout << "\n==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
(Automatic interactive demonstration executed by main):
1. Insert Day 1 'P' (Head creation)
2. Append Day 2 'P', Day 3 'A', Day 4 'P', Day 5 'A', Day 6 'P'
3. Display list and pointer chain
4. Update Day 3 to 'P'
5. Compute statistics: Total = 6, Present = 5, Absent = 1, Percentage = 83.33%
6. Attempt invalid day update (Day 99) and invalid status character ('X')
7. Free linked list

SAMPLE OUTPUT:
==============================================================
   DAILY ATTENDANCE SYSTEM (SINGLY LINKED LIST)              
==============================================================

--- DEMO STEP 1: Recording 6 Days of Initial Attendance ---
>> Day 1 [P] inserted as the first node.
>> Day 2 [P] appended to the end of the list.
>> Day 3 [A] appended to the end of the list.
>> Day 4 [P] appended to the end of the list.
>> Day 5 [A] appended to the end of the list.
>> Day 6 [P] appended to the end of the list.

--------------------------------------------------------------
Node Address      Day       Status    Next Address      
--------------------------------------------------------------
0x1d5f20          Day 1     P         0x1d5f50          
0x1d5f50          Day 2     P         0x1d5f80          
0x1d5f80          Day 3     A         0x1d5fb0          
0x1d5fb0          Day 4     P         0x1d5fe0          
0x1d5fe0          Day 5     A         0x1d6010          
0x1d6010          Day 6     P         0                 
--------------------------------------------------------------
Pointer Chain Visualization:
HEAD -> [Day 1 : P] -> [Day 2 : P] -> [Day 3 : A] -> [Day 4 : P] -> [Day 5 : A] -> [Day 6 : P] -> NULL

--- DEMO STEP 2: Updating Day 3 from 'A' to 'P' (Leave Approved) ---
>> Success: Day 3 attendance updated from [A] to [P].

--------------------------------------------------------------
Node Address      Day       Status    Next Address      
--------------------------------------------------------------
0x1d5f20          Day 1     P         0x1d5f50          
0x1d5f50          Day 2     P         0x1d5f80          
0x1d5f80          Day 3     P         0x1d5fb0          
0x1d5fb0          Day 4     P         0x1d5fe0          
0x1d5fe0          Day 5     A         0x1d6010          
0x1d6010          Day 6     P         0                 
--------------------------------------------------------------
Pointer Chain Visualization:
HEAD -> [Day 1 : P] -> [Day 2 : P] -> [Day 3 : P] -> [Day 4 : P] -> [Day 5 : A] -> [Day 6 : P] -> NULL

--- DEMO STEP 3: Calculating Total Present and Absent Days ---

================ ATTENDANCE SUMMARY ================
 Total Working Days Recorded : 6
 Total Days Present (P)      : 5
 Total Days Absent (A)       : 1
 Attendance Percentage       : 83.33%
 [STATUS] Attendance criteria satisfied (>= 75%).
====================================================

--- DEMO STEP 4: Attempting to update non-existent Day 99 ---
[ERROR] Day 99 not found in attendance records.

--- DEMO STEP 5: Attempting to insert invalid status 'X' ---
[ERROR] Invalid status 'X'. Only 'P' (Present) or 'A' (Absent) allowed.

--- DEMO STEP 6: Freeing all heap memory ---
>> Memory cleanup: All attendance nodes successfully freed.

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

STEP-BY-STEP DRY RUN: APPENDING A NODE
Initial List:
HEAD -> [Day 1: P | next: 0x200] -> [Day 2: P | next: nullptr]
New Node created at address 0x300: [Day 3: A | next: nullptr]

Step 1: Check `head == nullptr`. False (head points to 0x100).
Step 2: Initialize `temp = head` (temp points to 0x100).
Step 3: Check `temp->next != nullptr`:
        - At 0x100: temp->next is 0x200 (not null). Advance `temp = temp->next` (temp is now 0x200).
        - At 0x200: temp->next is nullptr. Loop terminates!
Step 4: Execute link: `temp->next = newNode;`
        - Memory at 0x200 now has its `next` field set to 0x300.
Resulting List:
HEAD -> [Day 1: P] -> [Day 2: P] -> [Day 3: A] -> nullptr.

----------------------------------------------------------------------------------------
STEP-BY-STEP DRY RUN: UPDATING ATTENDANCE (DAY 3 TO 'P')
List: [Day 1: P] -> [Day 2: P] -> [Day 3: A] -> [Day 4: P]
Target: Day 3.
- temp = Day 1: temp->dayNumber (1) != 3. temp = temp->next.
- temp = Day 2: temp->dayNumber (2) != 3. temp = temp->next.
- temp = Day 3: temp->dayNumber (3) == 3. MATCH FOUND!
  Action: temp->status = 'P'.
  Return true.

========================================================================================
TIME COMPLEXITY:
- Append (`insertAttendance`):
  * Best case: O(1) when list is empty (direct head assignment).
  * Worst case: O(N) when list has N nodes (must traverse all N-1 links to find the tail).
  * Average case: O(N).
  *(Note: If a `tail` pointer is maintained, append becomes O(1) always).*
- Update Attendance:
  * Best case: O(1) if target day is at head.
  * Worst case: O(N) if target day is at tail or absent.
  * Average case: O(N).
- Calculate Statistics:
  * O(N) always, because every node must be visited to tally counts.
- Display List:
  * O(N) always, to print each node.
- Free List:
  * O(N) always, to delete each allocated node individually.

SPACE COMPLEXITY:
- Auxiliary Space: O(1) (only uses temporary pointer variables `temp` and `newNode`).
- Total Dynamic Memory: O(N) heap memory, where each node consumes:
  `sizeof(AttendanceNode)` = 4 bytes (int) + 1 byte (char) + 3 bytes padding + 8 bytes (pointer) = 16 bytes.

WHY?
Because nodes are linked linearly and can only be accessed by sequential pointer
chasing from `head` through each successive `next` address.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Forgetting to Pass `head` by Reference (`AttendanceNode* &head`) in Insertion:
   - If passed by value (`AttendanceNode* head`), modifying `head = newNode` only
     changes a local copy! When the function returns, `head` in `main()` remains NULL,
     causing an immediate memory leak and crash.
2. Dereferencing Null Pointer (Segmentation Fault):
   - Writing `while (temp->next != nullptr)` when `head` is NULL will immediately crash.
     Always handle `head == nullptr` as a separate special case!
3. Losing Next Pointer during Deletion / Cleanup:
   - Writing:
     `delete current;`
     `current = current->next; // CRASH! current was already destroyed!`
     Always save the next address FIRST:
     `AttendanceNode* nextNode = current->next; delete current; current = nextNode;`
4. Forgetting `next = nullptr` when Creating New Node:
   - An uninitialized pointer contains random garbage memory addresses. Attempting to
     traverse it later leads to undefined behaviour and segmentation faults.

========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Define `struct AttendanceNode { int dayNumber; char status; AttendanceNode* next; };`
[ ] 2. Signature: `void insertAttendance(AttendanceNode* &head, int day, char status)` (Reference to pointer!).
[ ] 3. Handle empty list: `if (head == nullptr) { head = newNode; return; }`
[ ] 4. Find tail loop: `while (temp->next != nullptr) temp = temp->next;`
[ ] 5. Link tail to new node: `temp->next = newNode;`
[ ] 6. Update loop: `while (temp != nullptr) { if (temp->day == target) temp->status = newStatus; temp = temp->next; }`
[ ] 7. Free memory using temporary `nextNode` holder before `delete current`.
========================================================================================
*/
