/*
========================================================================================
PROGRAM HEADER:
- Program Number: 04
- Program Title: Internal Assessment (IA) Marks - Array vs Linked List Comparison
- Unit: Unit I - Introduction to Data Structures and Memory Representation
- Relevant Curriculum Topic: Memory Representation Comparison (Contiguous vs Non-Contiguous)
- Course Code: CE25PCC-203 (Data Structures Laboratory) - Group A, Assignment 4
- Problem Statement:
  Write a program that stores Internal Assessment (IA) marks of N students using both
  array and linked list. Implement:
  a. Insert student marks in both structures
  b. Display memory representation/index nodes
  c. Count how many students scored more than 80 marks
- Data Structures Used:
  1. Static Contiguous Integer Array: `int marksArray[MAX_CAPACITY]`
  2. Singly Linked List: `struct MarkNode* marksHead`
- What This Program Demonstrates:
  Side-by-side memory representation analysis (showing byte delta between contiguous
  array slots vs heap-allocated node pointer addresses), threshold counting, and
  cache locality vs dynamic flexibility trade-offs.
========================================================================================

CONCEPT: CONTIGUOUS ARRAY VS NON-CONTIGUOUS LINKED LIST MEMORY
1. Array Memory Representation:
   - When an array `int arr[N]` is allocated, the operating system reserves a single
     unbroken block of memory: `N * sizeof(int)` bytes.
   - Address of element at index `i`: `Base_Address + (i * sizeof(int))`.
   - The difference between `&arr[i]` and `&arr[i+1]` is EXACTLY 4 bytes!
   - Advantage: Phenomenal CPU cache performance (spatial locality).
   - Disadvantage: Pre-allocated fixed size. If N exceeds capacity, resizing requires
     allocating an entirely new block and copying every element.

2. Linked List Memory Representation:
   - Each node is allocated independently on the heap via `new MarkNode`.
   - The operating system grants whatever free heap chunk fits the node structure.
   - Address of node `i` and node `i+1` have NO mathematical relationship! They could be
     separated by hundreds or thousands of bytes.
   - Pointers (`next`) are the ONLY thread connecting the data elements.
   - Advantage: Zero pre-allocated waste; grows and shrinks dynamically.
   - Disadvantage: High memory overhead (each 4-byte mark carries an 8-byte pointer = 200% overhead).
*/

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_STUDENTS = 50;

// Definition of a Linked List Node for Marks
struct MarkNode {
    int mark;             // Internal assessment mark (0 to 100)
    MarkNode* next;       // Pointer to the next heap node

    MarkNode(int val) {
        mark = val;
        next = nullptr;
    }
};

/*
ALGORITHM 1: DUAL INSERTION
1. Insert into Array:
   a. Check if `arraySize < MAX_STUDENTS`.
   b. Store `marksArray[arraySize] = mark`.
   c. Increment `arraySize++`.
2. Insert into Linked List (Append):
   a. Allocate `newNode = new MarkNode(mark)`.
   b. If `head == nullptr`, set `head = newNode`.
   c. Else, traverse to last node (`while (temp->next != nullptr) temp = temp->next`)
      and link `temp->next = newNode`.
*/
void insertMarkInBoth(int marksArray[], int &arraySize, MarkNode* &listHead, int mark) {
    // 1. Array Insertion
    if (arraySize >= MAX_STUDENTS) {
        cout << "[ERROR] Array full! Cannot insert mark " << mark << " into array.\n";
    } else {
        marksArray[arraySize] = mark;
        arraySize++;
    }

    // 2. Linked List Insertion
    MarkNode* newNode = new MarkNode(mark);
    if (listHead == nullptr) {
        listHead = newNode;
    } else {
        MarkNode* temp = listHead;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    cout << ">> Inserted Mark [" << mark << "] into both Array and Linked List.\n";
}

/*
ALGORITHM 2: DISPLAY MEMORY REPRESENTATION
1. Print Array Representation:
   - Print Header: Index, Logical Position, Mark Value, Physical Memory Address (`&marksArray[i]`),
     Byte Offset from Base Address.
   - Demonstrate that each adjacent slot is separated by exactly `sizeof(int)` = 4 bytes.
2. Print Linked List Representation:
   - Print Header: Node Number, Mark Value, Current Node Address (`temp`), Next Node Address (`temp->next`),
     Address Distance from Preceding Node.
   - Demonstrate that heap addresses are non-contiguous and non-deterministic.
*/
void displayMemoryRepresentations(const int marksArray[], int arraySize, const MarkNode* listHead) {
    cout << "\n========================================================================\n";
    cout << "             1. ARRAY MEMORY REPRESENTATION (CONTIGUOUS)                \n";
    cout << "========================================================================\n";
    cout << left << setw(8)  << "Index"
         << setw(10) << "Position"
         << setw(8)  << "Mark"
         << setw(20) << "Memory Address"
         << setw(16) << "Offset (Bytes)" << "\n";
    cout << "------------------------------------------------------------------------\n";

    uintptr_t baseAddress = reinterpret_cast<uintptr_t>(&marksArray[0]);

    for (int i = 0; i < arraySize; i++) {
        uintptr_t currentAddr = reinterpret_cast<uintptr_t>(&marksArray[i]);
        int offset = static_cast<int>(currentAddr - baseAddress);

        cout << left << setw(8)  << i
             << setw(10) << (i + 1)
             << setw(8)  << marksArray[i]
             << setw(20) << (&marksArray[i])
             << "+" << offset << " bytes (Adjacent: 4B step)\n";
    }
    cout << "------------------------------------------------------------------------\n";
    cout << "NOTICE: Every consecutive array element is precisely " << sizeof(int) 
         << " bytes apart in RAM!\n\n";

    cout << "========================================================================\n";
    cout << "           2. LINKED LIST MEMORY REPRESENTATION (NON-CONTIGUOUS)        \n";
    cout << "========================================================================\n";
    cout << left << setw(8)  << "Node #"
         << setw(8)  << "Mark"
         << setw(20) << "Current Address"
         << setw(20) << "Next Pointer Addr"
         << setw(16) << "Delta from Prev" << "\n";
    cout << "------------------------------------------------------------------------\n";

    const MarkNode* temp = listHead;
    int nodeNum = 1;
    uintptr_t prevAddr = 0;

    while (temp != nullptr) {
        uintptr_t currAddr = reinterpret_cast<uintptr_t>(temp);

        cout << left << setw(8)  << nodeNum
             << setw(8)  << temp->mark
             << setw(20) << temp
             << setw(20) << temp->next;

        if (prevAddr == 0) {
            cout << "(Heap Root / Head)\n";
        } else {
            long long delta = static_cast<long long>(currAddr) - static_cast<long long>(prevAddr);
            cout << (delta >= 0 ? "+" : "") << delta << " bytes\n";
        }

        prevAddr = currAddr;
        temp = temp->next;
        nodeNum++;
    }
    cout << "------------------------------------------------------------------------\n";
    cout << "NOTICE: Heap addresses are non-contiguous; memory delta fluctuates!\n\n";
}

/*
ALGORITHM 3: COUNT SCORES > 80
1. Array Counter:
   - Initialize `arrayHighScorers = 0`.
   - Loop `i` from `0` to `arraySize - 1`:
     If `marksArray[i] > 80`, increment `arrayHighScorers`.
2. Linked List Counter:
   - Initialize `listHighScorers = 0`.
   - Pointer `temp = head`.
   - While `temp != nullptr`:
     If `temp->mark > 80`, increment `listHighScorers`.
     `temp = temp->next`.
3. Compare both counts to verify data integrity across both structures.
*/
void countStudentsAbove80(const int marksArray[], int arraySize, const MarkNode* listHead) {
    // 1. Array counting
    int arrayHighScorers = 0;
    for (int i = 0; i < arraySize; i++) {
        if (marksArray[i] > 80) {
            arrayHighScorers++;
        }
    }

    // 2. Linked List counting
    int listHighScorers = 0;
    const MarkNode* temp = listHead;
    while (temp != nullptr) {
        if (temp->mark > 80) {
            listHighScorers++;
        }
        temp = temp->next;
    }

    cout << "=================== PERFORMANCE AUDIT (> 80 MARKS) ===================\n";
    cout << " Total Students Evaluated            : " << arraySize << "\n";
    cout << " High Scorers Count (via Array)      : " << arrayHighScorers << "\n";
    cout << " High Scorers Count (via Linked List): " << listHighScorers << "\n";

    if (arrayHighScorers == listHighScorers) {
        cout << " [VERIFIED] Both data structures report identical results: " 
             << arrayHighScorers << " students.\n";
    } else {
        cout << " [DESYNC ERROR] Mismatch between array and linked list!\n";
    }
    cout << "======================================================================\n\n";
}

// Memory cleanup utility for linked list
void freeList(MarkNode* &head) {
    MarkNode* current = head;
    while (current != nullptr) {
        MarkNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    cout << ">> Memory cleanup: Linked list heap nodes successfully deallocated.\n";
}

// Interactive demonstration runner
int main() {
    int marksArray[MAX_STUDENTS];
    int currentArraySize = 0;
    MarkNode* marksHead = nullptr;

    cout << "======================================================================\n";
    cout << "   INTERNAL ASSESSMENT MARKS: ARRAY VS LINKED LIST AUDIT             \n";
    cout << "======================================================================\n";

    // 1. Insert IA marks of N=6 students into both structures
    cout << "\n--- DEMO STEP 1: Populating 6 Student Marks into Both Structures ---\n";
    insertMarkInBoth(marksArray, currentArraySize, marksHead, 72);
    insertMarkInBoth(marksArray, currentArraySize, marksHead, 88);
    insertMarkInBoth(marksArray, currentArraySize, marksHead, 95);
    insertMarkInBoth(marksArray, currentArraySize, marksHead, 64);
    insertMarkInBoth(marksArray, currentArraySize, marksHead, 82);
    insertMarkInBoth(marksArray, currentArraySize, marksHead, 79);

    // 2. Display memory representations side by side
    cout << "\n--- DEMO STEP 2: Inspecting Physical Memory Layouts ---\n";
    displayMemoryRepresentations(marksArray, currentArraySize, marksHead);

    // 3. Count high scorers (>80 marks) in both structures
    cout << "--- DEMO STEP 3: Executing Conditional Threshold Count (> 80) ---\n";
    countStudentsAbove80(marksArray, currentArraySize, marksHead);

    // 4. Memory cleanup
    cout << "--- DEMO STEP 4: Deallocating Linked List Memory ---\n";
    freeList(marksHead);

    cout << "\n======================================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                          \n";
    cout << "======================================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
Input Marks: 72, 88, 95, 64, 82, 79
Marks > 80 are: 88, 95, 82 -> Total = 3 students.

SAMPLE OUTPUT:
======================================================================
   INTERNAL ASSESSMENT MARKS: ARRAY VS LINKED LIST AUDIT             
======================================================================

--- DEMO STEP 1: Populating 6 Student Marks into Both Structures ---
>> Inserted Mark [72] into both Array and Linked List.
>> Inserted Mark [88] into both Array and Linked List.
>> Inserted Mark [95] into both Array and Linked List.
>> Inserted Mark [64] into both Array and Linked List.
>> Inserted Mark [82] into both Array and Linked List.
>> Inserted Mark [79] into both Array and Linked List.

--- DEMO STEP 2: Inspecting Physical Memory Layouts ---

========================================================================
             1. ARRAY MEMORY REPRESENTATION (CONTIGUOUS)                
========================================================================
Index   Position  Mark    Memory Address      Offset (Bytes)  
------------------------------------------------------------------------
0       1         72      0x5ffe70            +0 bytes (Adjacent: 4B step)
1       2         88      0x5ffe74            +4 bytes (Adjacent: 4B step)
2       3         95      0x5ffe78            +8 bytes (Adjacent: 4B step)
3       4         64      0x5ffe7c            +12 bytes (Adjacent: 4B step)
4       5         82      0x5ffe80            +16 bytes (Adjacent: 4B step)
5       6         79      0x5ffe84            +20 bytes (Adjacent: 4B step)
------------------------------------------------------------------------
NOTICE: Every consecutive array element is precisely 4 bytes apart in RAM!

========================================================================
           2. LINKED LIST MEMORY REPRESENTATION (NON-CONTIGUOUS)        
========================================================================
Node #  Mark    Current Address     Next Pointer Addr   Delta from Prev 
------------------------------------------------------------------------
1       72      0x1c3240            0x1c3260            (Heap Root / Head)
2       88      0x1c3260            0x1c3280            +32 bytes
3       95      0x1c3280            0x1c32a0            +32 bytes
4       64      0x1c32a0            0x1c32c0            +32 bytes
5       82      0x1c32c0            0x1c32e0            +32 bytes
6       79      0x1c32e0            0                   +32 bytes
------------------------------------------------------------------------
NOTICE: Heap addresses are non-contiguous; memory delta fluctuates!

--- DEMO STEP 3: Executing Conditional Threshold Count (> 80) ---
=================== PERFORMANCE AUDIT (> 80 MARKS) ===================
 Total Students Evaluated            : 6
 High Scorers Count (via Array)      : 3
 High Scorers Count (via Linked List): 3
 [VERIFIED] Both data structures report identical results: 3 students.
======================================================================

--- DEMO STEP 4: Deallocating Linked List Memory ---
>> Memory cleanup: Linked list heap nodes successfully deallocated.

======================================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                          
======================================================================
========================================================================================

STEP-BY-STEP DRY RUN: THRESHOLD COUNTING (> 80)
Array: [72, 88, 95, 64, 82, 79]
1. i=0: marks[0] = 72. 72 > 80? False. count = 0.
2. i=1: marks[1] = 88. 88 > 80? True.  count = 1.
3. i=2: marks[2] = 95. 95 > 80? True.  count = 2.
4. i=3: marks[3] = 64. 64 > 80? False. count = 2.
5. i=4: marks[4] = 82. 82 > 80? True.  count = 3.
6. i=5: marks[5] = 79. 79 > 80? False. count = 3.
Final High Scorers = 3.

Linked list traversal visits 0x1c3240 -> 0x1c3260 -> 0x1c3280 -> 0x1c32a0 -> 0x1c32c0 -> 0x1c32e0,
yielding identical result = 3.

========================================================================================
TIME COMPLEXITY:
- Dual Insertion:
  * Array Insertion: O(1) - append at `marksArray[arraySize++]`.
  * Linked List Append: O(N) without tail pointer (O(1) with tail pointer).
- Memory Display:
  * Array Display: O(N) - single linear loop over contiguous indices.
  * Linked List Display: O(N) - pointer chasing across heap nodes.
- Count > 80:
  * Array Count: O(N) - sequential RAM iteration.
  * Linked List Count: O(N) - sequential node iteration.

SPACE COMPLEXITY:
- Array:
  * Fixed O(MAX_STUDENTS) space = 50 * 4 bytes = 200 bytes total, regardless of whether
    1 student or 50 students are currently stored.
- Linked List:
  * Dynamic O(N) space = N * sizeof(MarkNode).
  * For 6 students: 6 * 16 bytes = 96 bytes total.

WHY?
Array elements sit contiguously in stack/data segment. Linked list nodes reside on heap,
trading contiguous memory efficiency for dynamic growth.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Printing Address of Value instead of Address of Array Slot:
   - Writing `&(marksArray)` prints the address of the entire array pointer, NOT the
     individual elements. Use `&marksArray[i]` to see the +4 byte progression!
2. Casting Pointers to Integer Incorrectly:
   - On 64-bit platforms, an address is 8 bytes (64 bits). Casting to plain `(int)` causes
     compiler truncation warnings! Always cast to `(uintptr_t)` or print pointer directly.
3. Confusing Logical Size with Physical Capacity:
   - Only iterate up to `arraySize`, NOT up to `MAX_STUDENTS`! Otherwise you read garbage values.

========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Dual insertion: array adds at `array[size++]`, linked list appends via `temp->next = newNode`.
[ ] 2. Memory demonstration: print `&array[i]` and compare adjacent differences (4 bytes).
[ ] 3. Linked list demonstration: print `temp` and `temp->next`.
[ ] 4. Counting loop: `if (val > 80) count++;`
[ ] 5. Clean up linked list with `delete current` loop before exiting `main()`.
========================================================================================
*/
