/*
========================================================================================
PROGRAM HEADER:
- Program Number: 06
- Program Title: Academic Office Student Record Search (Linear vs Binary Search)
- Unit: Unit II - Searching and Sorting Techniques
- Relevant Curriculum Topic: Linear and Binary Search with Comparison Tracking
- Course Code: CE25PCC-203 (Data Structures Laboratory) - Group B, Assignment 6
- Problem Statement:
  Write a program for an academic office to search a student record (Roll No, Name, Division).
  Implement:
  a. Linear search by Name
  b. Binary search by Roll Number (use sorting)
  c. Display number of comparisons for each search
- Data Structure Used: Array of Structures (`struct StudentRecord`)
- What This Program Demonstrates:
  Sequential scanning vs divide-and-conquer searching, comparison tally metrics,
  sorting prerequisite for binary search, and mathematical proof of logarithmic efficiency.
========================================================================================

CONCEPT: LINEAR SEARCH VS BINARY SEARCH
1. Linear Search (Sequential Scan):
   - Starts at index 0 and inspects each element one by one until a match is found or
     the end of the array is reached.
   - Works on ANY dataset: unsorted, randomized, strings, numbers.
   - Performance: In the worst case, makes N comparisons (every element checked).

2. Binary Search (Divide and Conquer):
   - CRITICAL PREREQUISITE: The array MUST BE SORTED by the search key before searching!
     Applying binary search on an unsorted array produces completely invalid / missing results.
   - Mechanism: Repeatedly divides the search interval in half.
     * Computes `mid = low + (high - low) / 2`.
     * If `key == arr[mid]`, target found in 1 step!
     * If `key < arr[mid]`, target must be in the left half -> set `high = mid - 1`.
     * If `key > arr[mid]`, target must be in the right half -> set `low = mid + 1`.
   - Performance: Eliminates 50% of the remaining search space with every single comparison!
     Worst case comparisons: ceil(log2(N) + 1). For 1,000,000 records, binary search takes
     at most 20 comparisons, whereas linear search could take 1,000,000!
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_RECORDS = 50;

// Structure for student record in the academic office
struct StudentRecord {
    int rollNo;         // Key for binary search
    string name;        // Key for linear search
    char division;      // Division identifier ('A', 'B', etc.)
};

/*
ALGORITHM 1: LINEAR SEARCH BY NAME
1. Initialize comparison counter: `comparisons = 0`.
2. Loop index `i` from `0` to `size - 1`:
   a. Increment `comparisons++`.
   b. Compare `records[i].name == targetName`.
   c. If match found:
      Return index `i`.
3. If loop finishes without match:
   Return -1 (not found).
*/
int linearSearchByName(const StudentRecord records[], int size, const string &targetName, int &comparisons) {
    comparisons = 0;

    for (int i = 0; i < size; i++) {
        comparisons++; // Increment comparison tally for every name check
        if (records[i].name == targetName) {
            return i; // Target located at index i
        }
    }

    return -1; // Target does not exist in array
}

/*
ALGORITHM 2: BUBBLE SORT (SORTING BY ROLL NUMBER)
(Prerequisite to guarantee binary search correctness)
1. Loop pass from `0` to `size - 2`.
2. Inner loop from `0` to `size - 2 - pass`.
3. If `records[j].rollNo > records[j+1].rollNo`, swap them.
*/
void sortRecordsByRollNumber(StudentRecord records[], int size) {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - 1 - i; j++) {
            if (records[j].rollNo > records[j + 1].rollNo) {
                StudentRecord temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break; // Array is already sorted
    }
}

/*
ALGORITHM 3: BINARY SEARCH BY ROLL NUMBER
1. Initialize search boundaries: `low = 0`, `high = size - 1`.
2. Initialize comparison counter: `comparisons = 0`.
3. Print tracing header.
4. While `low <= high`:
   a. Compute midpoint safely: `mid = low + (high - low) / 2;`
      (WHY `low + (high - low) / 2` INSTEAD OF `(low + high) / 2`?
       To prevent integer overflow when working with large indices!).
   b. Increment `comparisons++`.
   c. If `records[mid].rollNo == targetRoll`:
      Target found! Return index `mid`.
   d. If `records[mid].rollNo < targetRoll`:
      Target lies strictly in the right partition.
      Adjust left boundary: `low = mid + 1`.
   e. Else (`records[mid].rollNo > targetRoll`):
      Target lies strictly in the left partition.
      Adjust right boundary: `high = mid - 1`.
5. If loop terminates with `low > high`:
   Target is not present in the array. Return -1.
*/
int binarySearchByRollNo(const StudentRecord records[], int size, int targetRoll, int &comparisons) {
    comparisons = 0;
    int low = 0;
    int high = size - 1;

    cout << "\n   [Binary Search Execution Trace]\n";
    cout << "   " << left << setw(8) << "Step" 
         << setw(8) << "low" 
         << setw(8) << "high" 
         << setw(8) << "mid" 
         << setw(14) << "Roll at mid" 
         << "Action\n";
    cout << "   ------------------------------------------------------------\n";

    int step = 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        comparisons++;

        cout << "   " << left << setw(8) << step
             << setw(8) << low
             << setw(8) << high
             << setw(8) << mid
             << setw(14) << records[mid].rollNo;

        if (records[mid].rollNo == targetRoll) {
            cout << "EQUAL! Target Found.\n";
            cout << "   ------------------------------------------------------------\n";
            return mid;
        } else if (records[mid].rollNo < targetRoll) {
            cout << "Target > mid -> low = " << (mid + 1) << "\n";
            low = mid + 1; // Eliminate left half
        } else {
            cout << "Target < mid -> high = " << (mid - 1) << "\n";
            high = mid - 1; // Eliminate right half
        }
        step++;
    }

    cout << "   Target not found. Search interval exhausted.\n";
    cout << "   ------------------------------------------------------------\n";
    return -1;
}

// Display table of student records
void displayRecords(const StudentRecord records[], int size, const string &title) {
    cout << "\n================ " << title << " ================\n";
    cout << left << setw(8)  << "Index"
         << setw(12) << "Roll No"
         << setw(22) << "Name"
         << setw(10) << "Division" << "\n";
    cout << "--------------------------------------------------------\n";
    for (int i = 0; i < size; i++) {
        cout << left << setw(8)  << i
             << setw(12) << records[i].rollNo
             << setw(22) << records[i].name
             << setw(10) << records[i].division << "\n";
    }
    cout << "--------------------------------------------------------\n";
    cout << "Total Records: " << size << "\n\n";
}

// Interactive demonstration runner
int main() {
    // Initial unsorted academic office dataset
    StudentRecord officeDB[MAX_RECORDS] = {
        {107, "Pooja Jadhav", 'B'},
        {102, "Bhavna Patil", 'A'},
        {109, "Rohan Shinde", 'B'},
        {101, "Aarav Sharma", 'A'},
        {105, "Divya Kulkarni", 'A'},
        {108, "Pranav Mehta", 'B'},
        {103, "Chetan Joshi", 'A'}
    };
    int count = 7;

    cout << "==============================================================\n";
    cout << "   ACADEMIC OFFICE SEARCH SYSTEM: LINEAR VS BINARY SEARCH     \n";
    cout << "==============================================================\n";

    // 1. Initial State Display (Unsorted)
    displayRecords(officeDB, count, "UNSORTED STUDENT DATABASE");

    // 2. Linear Search by Name (Does not require sorting!)
    cout << "--- DEMO STEP 1: Linear Search by Name ---\n";
    cout << "Searching for Student: 'Divya Kulkarni'...\n";
    int linComps = 0;
    int linIdx = linearSearchByName(officeDB, count, "Divya Kulkarni", linComps);
    if (linIdx != -1) {
        cout << ">> FOUND: Index [" << linIdx << "] | Roll: " << officeDB[linIdx].rollNo 
             << " | Div: " << officeDB[linIdx].division << "\n";
        cout << ">> Total Comparisons Made: " << linComps << " (out of " << count << " records)\n";
    }

    cout << "\nSearching for non-existent Student: 'Suresh Raina'...\n";
    int linComps2 = 0;
    int linIdx2 = linearSearchByName(officeDB, count, "Suresh Raina", linComps2);
    if (linIdx2 == -1) {
        cout << ">> NOT FOUND.\n";
        cout << ">> Total Comparisons Made: " << linComps2 << " (checked every single record)\n";
    }

    // 3. Sorting by Roll Number before Binary Search
    cout << "\n--- DEMO STEP 2: Sorting Records by Roll Number for Binary Search ---\n";
    sortRecordsByRollNumber(officeDB, count);
    displayRecords(officeDB, count, "DATABASE SORTED BY ROLL NUMBER");

    // 4. Binary Search by Roll Number
    cout << "--- DEMO STEP 3: Binary Search by Roll Number ---\n";
    cout << "Searching for Roll Number: 108...\n";
    int binComps = 0;
    int binIdx = binarySearchByRollNo(officeDB, count, 108, binComps);
    if (binIdx != -1) {
        cout << ">> FOUND: Index [" << binIdx << "] | Name: " << officeDB[binIdx].name 
             << " | Div: " << officeDB[binIdx].division << "\n";
        cout << ">> Total Comparisons Made: " << binComps << "\n";
    }

    cout << "\nSearching for non-existent Roll Number: 104...\n";
    int binComps2 = 0;
    int binIdx2 = binarySearchByRollNo(officeDB, count, 104, binComps2);
    if (binIdx2 == -1) {
        cout << ">> NOT FOUND.\n";
        cout << ">> Total Comparisons Made: " << binComps2 << "\n";
    }

    // 5. Comparison Summary Table
    cout << "\n==============================================================\n";
    cout << "                 ALGORITHM COMPARISON SUMMARY                 \n";
    cout << "==============================================================\n";
    cout << left << setw(20) << "Search Method"
         << setw(16) << "Target"
         << setw(14) << "Result"
         << setw(16) << "Comparisons" << "\n";
    cout << "--------------------------------------------------------------\n";
    cout << left << setw(20) << "Linear (by Name)"
         << setw(16) << "Divya Kulkarni"
         << setw(14) << "Found"
         << setw(16) << linComps << "\n";
    cout << left << setw(20) << "Linear (by Name)"
         << setw(16) << "Suresh Raina"
         << setw(14) << "Not Found"
         << setw(16) << linComps2 << "\n";
    cout << left << setw(20) << "Binary (by Roll)"
         << setw(16) << "108"
         << setw(14) << "Found"
         << setw(16) << binComps << "\n";
    cout << left << setw(20) << "Binary (by Roll)"
         << setw(16) << "104"
         << setw(14) << "Not Found"
         << setw(16) << binComps2 << "\n";
    cout << "--------------------------------------------------------------\n";

    cout << "\n==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
Dataset (N = 7):
Unsorted Rolls: 107, 102, 109, 101, 105, 108, 103
Sorted Rolls:   101, 102, 103, 105, 107, 108, 109

Trace for Binary Search (Target Roll = 108):
- Step 1: low = 0, high = 6, mid = 3. arr[3] = 105. 108 > 105 -> low = 4.
- Step 2: low = 4, high = 6, mid = 5. arr[5] = 108. 108 == 108 -> Found in 2 comparisons!

SAMPLE OUTPUT:
==============================================================
   ACADEMIC OFFICE SEARCH SYSTEM: LINEAR VS BINARY SEARCH     
==============================================================

================ UNSORTED STUDENT DATABASE ================
Index   Roll No     Name                  Division  
--------------------------------------------------------
0       107         Pooja Jadhav          B         
1       102         Bhavna Patil          A         
2       109         Rohan Shinde          B         
3       101         Aarav Sharma          A         
4       105         Divya Kulkarni        A         
5       108         Pranav Mehta          B         
6       103         Chetan Joshi          A         
--------------------------------------------------------
Total Records: 7

--- DEMO STEP 1: Linear Search by Name ---
Searching for Student: 'Divya Kulkarni'...
>> FOUND: Index [4] | Roll: 105 | Div: A
>> Total Comparisons Made: 5 (out of 7 records)

Searching for non-existent Student: 'Suresh Raina'...
>> NOT FOUND.
>> Total Comparisons Made: 7 (checked every single record)

--- DEMO STEP 2: Sorting Records by Roll Number for Binary Search ---

================ DATABASE SORTED BY ROLL NUMBER ================
Index   Roll No     Name                  Division  
--------------------------------------------------------
0       101         Aarav Sharma          A         
1       102         Bhavna Patil          A         
2       103         Chetan Joshi          A         
3       105         Divya Kulkarni        A         
4       107         Pooja Jadhav          B         
5       108         Pranav Mehta          B         
6       109         Rohan Shinde          B         
--------------------------------------------------------
Total Records: 7

--- DEMO STEP 3: Binary Search by Roll Number ---
Searching for Roll Number: 108...

   [Binary Search Execution Trace]
   Step    low     high    mid     Roll at mid   Action
   ------------------------------------------------------------
   1       0       6       3       105           Target > mid -> low = 4
   2       4       6       5       108           EQUAL! Target Found.
   ------------------------------------------------------------
>> FOUND: Index [5] | Name: Pranav Mehta | Div: B
>> Total Comparisons Made: 2

Searching for non-existent Roll Number: 104...

   [Binary Search Execution Trace]
   Step    low     high    mid     Roll at mid   Action
   ------------------------------------------------------------
   1       0       6       3       105           Target < mid -> high = 2
   2       0       2       1       102           Target > mid -> low = 2
   3       2       2       2       103           Target > mid -> low = 3
   Target not found. Search interval exhausted.
   ------------------------------------------------------------
>> NOT FOUND.
>> Total Comparisons Made: 3

==============================================================
                 ALGORITHM COMPARISON SUMMARY                 
==============================================================
Search Method       Target          Result        Comparisons     
--------------------------------------------------------------
Linear (by Name)    Divya Kulkarni  Found         5               
Linear (by Name)    Suresh Raina    Not Found     7               
Binary (by Roll)    108             Found         2               
Binary (by Roll)    104             Not Found     3               
--------------------------------------------------------------

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

DRY RUN TABLE: BINARY SEARCH FOR ROLL 104
Target = 104. Sorted Array: [101, 102, 103, 105, 107, 108, 109], N = 7.

| Step | low | high | mid | Value at mid | Condition | Action |
|---|---|---|---|---|---|---|
| 1 | 0 | 6 | 3 | 105 | 104 < 105 | high = mid - 1 = 2 |
| 2 | 0 | 2 | 1 | 102 | 104 > 102 | low = mid + 1 = 2 |
| 3 | 2 | 2 | 2 | 103 | 104 > 103 | low = mid + 1 = 3 |
| 4 | 3 | 2 | - | - | low > high (3 > 2) | Loop terminates! Element Absent. |

Total Comparisons = 3. Notice: ceil(log2(7) + 1) = ceil(2.8 + 1) = 3! Exactly matches theory!

========================================================================================
TIME COMPLEXITY:
- Linear Search:
  * Best case: O(1) - target is at index 0 (1 comparison).
  * Average case: O(N) - on average, checks N/2 records.
  * Worst case: O(N) - target is at the very end or absent (N comparisons).
- Binary Search:
  * Best case: O(1) - target is exactly at the initial midpoint.
  * Average case: O(log N) - eliminates half the dataset per iteration.
  * Worst case: O(log N) - search boundary shrinks until single element or empty.

SPACE COMPLEXITY:
- Auxiliary Space:
  * Linear Search: O(1) auxiliary space.
  * Iterative Binary Search: O(1) auxiliary space (only `low`, `high`, `mid` variables).

WHY?
Linear search checks linearly: 1, 2, ..., N.
Binary search divides space: N -> N/2 -> N/4 -> ... -> 1.
Number of steps k satisfies: N / (2^k) = 1  ==>  2^k = N  ==>  k = log2(N).

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Running Binary Search on Unsorted Data:
   - Forgetting to sort first! Binary search depends entirely on ordered keys.
2. Integer Overflow in Midpoint Calculation:
   - Writing `mid = (low + high) / 2;` can overflow 32-bit signed integer if `low + high > 2^31 - 1`.
     Always write `mid = low + (high - low) / 2;`.
3. Incorrect Loop Termination Condition:
   - Writing `while (low < high)` instead of `while (low <= high)`!
     If target is at the last single-element interval (`low == high`), `<` will exit
     WITHOUT checking the element, causing a false "Not Found" error!
4. Forgetting `mid + 1` or `mid - 1`:
   - Writing `low = mid;` or `high = mid;` causes an infinite loop when `low` and `high`
     differ by 1!

========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Binary search condition: `while (low <= high)` (with `< =`).
[ ] 2. Safe midpoint: `mid = low + (high - low) / 2;`
[ ] 3. Target smaller: `high = mid - 1;`
[ ] 4. Target greater: `low = mid + 1;`
[ ] 5. Count comparisons at every iteration step: `comparisons++;`
[ ] 6. Linear search: simple sequential loop from `0` to `size - 1`.
========================================================================================
*/
