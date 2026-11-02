/*
========================================================================================
PROGRAM HEADER:
- Program Number: 05b
- Program Title: CGPA Merit List Preparation using Insertion Sort with Shift Counter
- Unit: Unit II - Searching and Sorting Techniques
- Relevant Curriculum Topic: Insertion Sort (Element Shifting Mechanism, Shift Counting, Top-5 Display)
- Course Code: CE25PCC-203 (Data Structures Laboratory) - Group B, Assignment 5b
- Problem Statement:
  Write a program for preparing a merit list of students based on CGPA. Implement:
  b. Insertion sort and count number of shifts
  c. Display the top 5 students
- Data Structure Used: Array of Structures (`struct StudentMerit`)
- What This Program Demonstrates:
  Playing-card insertion model, element shifting vs full swaps, shift tracking counter,
  stability preservation, and adaptive sorting behavior on partially sorted data.
========================================================================================

CONCEPT: HOW DOES INSERTION SORT WORK?
Think of how you sort playing cards in your hand:
1. You start with the first card (at index 0). A single card is always sorted by definition.
2. You pick up the next card (at index `i`, called the `key`).
3. You compare `key` backwards against the cards in your sorted hand (indices `i-1` down to 0).
4. For DESCENDING ORDER (Highest CGPA to Lowest):
   - Any card that has a SMALLER CGPA than `key` is shifted one spot to the right (`arr[j + 1] = arr[j]`).
   - Every time a card slides right, we increment our `totalShifts` counter!
5. As soon as you find a card with a CGPA >= `key` (or reach the start of the array),
   the vacant slot is found! You drop `key` into `arr[j + 1]`.
6. Repeat for all N cards.

WHY SHIFT INSTEAD OF SWAP?
A swap requires 3 data assignments (temp = a, a = b, b = temp).
A shift requires only 1 data assignment (`arr[j + 1] = arr[j]`).
Therefore, Insertion Sort is approximately 3 times faster in practice than Bubble Sort,
even though both have O(N^2) worst-case time complexity!

STABILITY:
Insertion sort is STABLE. If two students have identical CGPA, the strictly `<` condition
prevents shifting, ensuring their original relative order is preserved.
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_STUDENTS = 50;

// Student structure for merit list
struct StudentMerit {
    int rollNo;
    string name;
    float cgpa;
};

/*
ALGORITHM: INSERTION SORT (DESCENDING ORDER WITH SHIFT COUNTER)
1. Initialize `totalShifts = 0`.
2. Loop `i` from `1` to `size - 1` (element at index 0 is trivially sorted):
   a. Store the current record in a temporary variable: `key = students[i]`.
   b. Initialize `j = i - 1`.
   c. While `j >= 0` AND `students[j].cgpa < key.cgpa`:
      (In descending order, elements smaller than key must shift right!)
      - Shift element right: `students[j + 1] = students[j];`
      - Increment shift counter: `totalShifts++;`
      - Move pointer left: `j--;`
   d. Drop key into the freed slot: `students[j + 1] = key;`
   e. Print pass summary showing shifted elements and intermediate array.
3. Return `totalShifts`.
*/
int insertionSortDescending(StudentMerit students[], int size) {
    int totalShifts = 0;

    cout << "\n================ EXECUTION TRACE: INSERTION SORT PASSES ================\n";
    cout << "Initial sorted partition: [Index 0: " << students[0].name 
         << " (" << students[0].cgpa << ")]\n\n";

    for (int i = 1; i < size; i++) {
        StudentMerit key = students[i]; // The record to be placed into sorted partition
        int j = i - 1;
        int passShifts = 0;

        // Shift smaller elements right to make room for larger CGPA
        while (j >= 0 && students[j].cgpa < key.cgpa) {
            students[j + 1] = students[j]; // Shift right
            totalShifts++;
            passShifts++;
            j--; // Step backwards
        }

        // Insert key into correct position
        students[j + 1] = key;

        // Print pass details
        cout << "Pass " << i << " | Inserting [" << key.name << " : " << fixed << setprecision(2) << key.cgpa 
             << "] -> Position " << (j + 2) << " | Shifts in this pass: " << passShifts << "\n";
        cout << "   Current Array: ";
        for (int k = 0; k < size; k++) {
            cout << students[k].cgpa << " ";
        }
        cout << "\n";
    }

    cout << "========================================================================\n";
    cout << ">> Total Element Shifts Executed: " << totalShifts << "\n\n";
    return totalShifts;
}

/*
ALGORITHM: DISPLAY TOP 5 STUDENTS
1. Limit = min(5, size).
2. Loop through 0 to limit - 1 and print formatted table.
*/
void displayTopStudents(const StudentMerit students[], int size, int topK = 5) {
    int limit = (size < topK) ? size : topK;

    cout << "************************************************************************\n";
    cout << "             OFFICIAL MERIT LIST: TOP " << limit << " STUDENTS (INSERTION SORT) \n";
    cout << "************************************************************************\n";
    cout << left << setw(8)  << "Rank"
         << setw(12) << "Roll No"
         << setw(24) << "Student Name"
         << setw(10) << "CGPA"
         << setw(16) << "Distinction" << "\n";
    cout << "------------------------------------------------------------------------\n";

    for (int i = 0; i < limit; i++) {
        string distinction = (students[i].cgpa >= 9.0f) ? "First Class with Distinction" : "First Class";
        cout << left << setw(8)  << ("#" + to_string(i + 1))
             << setw(12) << students[i].rollNo
             << setw(24) << students[i].name
             << fixed << setprecision(2) << setw(10) << students[i].cgpa
             << setw(16) << distinction << "\n";
    }
    cout << "************************************************************************\n\n";
}

void displayAllStudents(const StudentMerit students[], int size, const string &title) {
    cout << "\n--- " << title << " ---\n";
    cout << left << setw(10) << "Roll No"
         << setw(24) << "Name"
         << setw(10) << "CGPA" << "\n";
    cout << "----------------------------------------------\n";
    for (int i = 0; i < size; i++) {
        cout << left << setw(10) << students[i].rollNo
             << setw(24) << students[i].name
             << fixed << setprecision(2) << setw(10) << students[i].cgpa << "\n";
    }
    cout << "----------------------------------------------\n";
}

// Interactive demonstration runner
int main() {
    StudentMerit batch[MAX_STUDENTS] = {
        {101, "Aarav Sharma", 8.45f},
        {102, "Bhavna Patil", 9.60f},
        {103, "Chetan Joshi", 7.80f},
        {104, "Divya Kulkarni", 9.15f},
        {105, "Esha Verma", 8.90f},
        {106, "Farhan Khan", 6.75f},
        {107, "Gaurav Shinde", 9.85f},
        {108, "Harita Nair", 9.30f}
    };
    int totalStudents = 8;

    cout << "==============================================================\n";
    cout << "   CGPA MERIT LIST SYSTEM (INSERTION SORT & SHIFT COUNT)      \n";
    cout << "==============================================================\n";

    displayAllStudents(batch, totalStudents, "UNSORTED STUDENT RECORDS");

    // Perform Insertion Sort and track shift operations
    int shifts = insertionSortDescending(batch, totalStudents);

    displayAllStudents(batch, totalStudents, "SORTED MERIT LIST");

    displayTopStudents(batch, totalStudents, 5);

    cout << "Performance Metric: Insertion Sort completed with " << shifts 
         << " total element shifts.\n";
    cout << "==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
Dataset (N = 8):
[8.45, 9.60, 7.80, 9.15, 8.90, 6.75, 9.85, 9.30]

Pass 1 (i = 1, key = 9.60):
- Compare 9.60 with 8.45. 8.45 < 9.60 -> Shift 8.45 right to index 1.
- Drop 9.60 into index 0. Shifts = 1.
- Array: [9.60, 8.45, 7.80, ...]

Pass 2 (i = 2, key = 7.80):
- Compare 7.80 with 8.45. 8.45 >= 7.80 -> Loop stops immediately! Shifts = 0.
- Array: [9.60, 8.45, 7.80, ...]

Pass 3 (i = 3, key = 9.15):
- 7.80 < 9.15 -> shift right.
- 8.45 < 9.15 -> shift right.
- 9.60 > 9.15 -> stop. Drop 9.15 at index 1. Shifts = 2.
- Array: [9.60, 9.15, 8.45, 7.80, ...]

SAMPLE OUTPUT:
==============================================================
   CGPA MERIT LIST SYSTEM (INSERTION SORT & SHIFT COUNT)      
==============================================================

--- UNSORTED STUDENT RECORDS ---
Roll No   Name                    CGPA      
----------------------------------------------
101       Aarav Sharma            8.45      
102       Bhavna Patil            9.60      
103       Chetan Joshi            7.80      
104       Divya Kulkarni          9.15      
105       Esha Verma              8.90      
106       Farhan Khan             6.75      
107       Gaurav Shinde           9.85      
108       Harita Nair             9.30      
----------------------------------------------

================ EXECUTION TRACE: INSERTION SORT PASSES ================
Initial sorted partition: [Index 0: Aarav Sharma (8.45)]

Pass 1 | Inserting [Bhavna Patil : 9.60] -> Position 1 | Shifts in this pass: 1
   Current Array: 9.60 8.45 7.80 9.15 8.90 6.75 9.85 9.30 
Pass 2 | Inserting [Chetan Joshi : 7.80] -> Position 3 | Shifts in this pass: 0
   Current Array: 9.60 8.45 7.80 9.15 8.90 6.75 9.85 9.30 
Pass 3 | Inserting [Divya Kulkarni : 9.15] -> Position 2 | Shifts in this pass: 2
   Current Array: 9.60 9.15 8.45 7.80 8.90 6.75 9.85 9.30 
Pass 4 | Inserting [Esha Verma : 8.90] -> Position 3 | Shifts in this pass: 2
   Current Array: 9.60 9.15 8.90 8.45 7.80 6.75 9.85 9.30 
Pass 5 | Inserting [Farhan Khan : 6.75] -> Position 6 | Shifts in this pass: 0
   Current Array: 9.60 9.15 8.90 8.45 7.80 6.75 9.85 9.30 
Pass 6 | Inserting [Gaurav Shinde : 9.85] -> Position 1 | Shifts in this pass: 6
   Current Array: 9.85 9.60 9.15 8.90 8.45 7.80 6.75 9.30 
Pass 7 | Inserting [Harita Nair : 9.30] -> Position 3 | Shifts in this pass: 4
   Current Array: 9.85 9.60 9.30 9.15 8.90 8.45 7.80 6.75 
========================================================================
>> Total Element Shifts Executed: 15

--- SORTED MERIT LIST ---
Roll No   Name                    CGPA      
----------------------------------------------
107       Gaurav Shinde           9.85      
102       Bhavna Patil            9.60      
108       Harita Nair             9.30      
104       Divya Kulkarni          9.15      
105       Esha Verma              8.90      
101       Aarav Sharma            8.45      
103       Chetan Joshi            7.80      
106       Farhan Khan             6.75      
----------------------------------------------
************************************************************************
             OFFICIAL MERIT LIST: TOP 5 STUDENTS (INSERTION SORT) 
************************************************************************
Rank    Roll No     Student Name            CGPA      Distinction     
------------------------------------------------------------------------
#1      107         Gaurav Shinde           9.85      First Class with Distinction
#2      102         Bhavna Patil            9.60      First Class with Distinction
#3      108         Harita Nair             9.30      First Class with Distinction
#4      104         Divya Kulkarni          9.15      First Class with Distinction
#5      105         Esha Verma              8.90      First Class     
************************************************************************

Performance Metric: Insertion Sort completed with 15 total element shifts.
==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

STEP-BY-STEP DRY RUN: PASS 6 (INSERTING GAURAV 9.85)
Array before pass: [9.60, 9.15, 8.90, 8.45, 7.80, 6.75, 9.85, 9.30]
i = 6, key = Gaurav (9.85).
j starts at 5:
- j = 5 (6.75): 6.75 < 9.85 -> arr[6] = arr[5] (6.75 shifts right). shifts = 1. j = 4.
- j = 4 (7.80): 7.80 < 9.85 -> arr[5] = arr[4] (7.80 shifts right). shifts = 2. j = 3.
- j = 3 (8.45): 8.45 < 9.85 -> arr[4] = arr[3] (8.45 shifts right). shifts = 3. j = 2.
- j = 2 (8.90): 8.90 < 9.85 -> arr[3] = arr[2] (8.90 shifts right). shifts = 4. j = 1.
- j = 1 (9.15): 9.15 < 9.85 -> arr[2] = arr[1] (9.15 shifts right). shifts = 5. j = 0.
- j = 0 (9.60): 9.60 < 9.85 -> arr[1] = arr[0] (9.60 shifts right). shifts = 6. j = -1.
Loop ends because j = -1.
Drop key into arr[j + 1] -> arr[0] = 9.85.
Array after: [9.85, 9.60, 9.15, 8.90, 8.45, 7.80, 6.75, 9.30].
Shifts in this pass = 6!

========================================================================================
TIME COMPLEXITY:
- Best case: O(N) when array is ALREADY sorted.
  * In every pass, `students[j].cgpa < key.cgpa` is false on the first comparison!
  * 0 shifts occur! Only N-1 comparisons are made.
- Worst case: O(N^2) when array is sorted in the REVERSE order.
  * Every single element in the sorted partition must shift right on every pass.
  * Total shifts = 1 + 2 + 3 + ... + (N-1) = N*(N-1)/2 shifts!
- Average case: O(N^2) - on average, each key shifts through half the sorted partition (N^2 / 4 shifts).

SPACE COMPLEXITY:
- Auxiliary Space: O(1) in-place sorting algorithm.

WHY?
Because each new element is inserted sequentially into an already sorted subarray,
shifting elements only as far as necessary until its proper place is found.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Forgetting to Save `key` in a Temporary Variable:
   - Writing `students[j + 1] = students[j]` without first copying `key = students[i]`
     will permanently erase the value of `students[i]`!
2. Shifting Condition Bug:
   - For descending order, shift when `students[j].cgpa < key.cgpa`.
   - If you write `>` you will sort ascending instead of descending!
3. Dropping into Wrong Slot:
   - When the while loop finishes, `j` has stepped one past the target slot.
     You MUST drop into `students[j + 1] = key;`, NOT `students[j] = key;`!
4. Counting Shifts Incorrectly:
   - Increment `totalShifts++` inside the while loop body, because that is where
     physical data movement occurs.

========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Outer loop starts at 1: `for (int i = 1; i < size; i++)`
[ ] 2. Save key: `StudentMerit key = arr[i]; int j = i - 1;`
[ ] 3. While condition: `while (j >= 0 && arr[j].cgpa < key.cgpa)`
[ ] 4. Shift: `arr[j + 1] = arr[j]; totalShifts++; j--;`
[ ] 5. Place key: `arr[j + 1] = key;`
[ ] 6. Top-5 extraction from index 0 to 4.
========================================================================================
*/
