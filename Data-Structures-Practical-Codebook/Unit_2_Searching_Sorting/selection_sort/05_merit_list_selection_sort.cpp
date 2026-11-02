/*
========================================================================================
PROGRAM HEADER:
- Program Number: 05a
- Program Title: CGPA Merit List Preparation using Selection Sort (Descending Order)
- Unit: Unit II - Searching and Sorting Techniques
- Relevant Curriculum Topic: Selection Sort (Descending Order, Maximum Selection, Top-5 Display)
- Course Code: CE25PCC-203 (Data Structures Laboratory) - Group B, Assignment 5a
- Problem Statement:
  Write a program for preparing a merit list of students based on CGPA. Implement:
  a. Selection sort for descending CGPA
  b. Display the top 5 students
- Data Structure Used: Array of Structures (`struct StudentMerit`)
- What This Program Demonstrates:
  Iterative pass-by-pass maximum element selection, swap reduction (at most N-1 swaps),
  descending order sorting, unstable sorting behavior, and top-K extraction.
========================================================================================

CONCEPT: HOW DOES SELECTION SORT WORK?
Selection Sort divides the array into two logical parts:
1. The sorted sub-array at the left (starts empty).
2. The unsorted sub-array at the right (starts with all N elements).

For DESCENDING ORDER (Highest CGPA to Lowest):
In each pass `i` (from 0 to N-2):
1. Assume the element at index `i` is the maximum: `maxIndex = i`.
2. Scan the rest of the array from `j = i + 1` to `N - 1`.
3. If `arr[j].cgpa > arr[maxIndex].cgpa`, update `maxIndex = j`.
4. After completing the pass scan, if `maxIndex != i`, swap `arr[i]` with `arr[maxIndex]`.
5. Now, the `i`-th largest student is permanently locked in position `i`!

WHY IS IT CALLED SELECTION SORT?
Because in each pass, we actively "select" the extreme element (here, maximum CGPA)
and place it into its final resting position.

KEY ADVANTAGE:
It makes the absolute MINIMUM number of swaps among elementary sorting algorithms:
At most N-1 swaps total! (Crucial when writing to slow memory like Flash/EEPROM).
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
ALGORITHM: SELECTION SORT (DESCENDING CGPA)
1. Loop pass index `i` from `0` to `size - 2`:
   a. Assume current index `i` holds the highest CGPA: `maxIndex = i`.
   b. Inner loop `j` from `i + 1` to `size - 1`:
      - If `students[j].cgpa > students[maxIndex].cgpa`:
        Update `maxIndex = j`.
   c. If `maxIndex != i`:
      Swap `students[i]` and `students[maxIndex]`.
   d. Display intermediate array state after Pass `i + 1`.
2. Once outer loop completes, the entire array is sorted from highest to lowest CGPA.
*/
void selectionSortDescending(StudentMerit students[], int size) {
    cout << "\n================ EXECUTION TRACE: SELECTION SORT PASSES ================\n";

    for (int i = 0; i < size - 1; i++) {
        int maxIndex = i; // Index of student with highest CGPA in unsorted sub-array

        // Scan the unsorted portion
        for (int j = i + 1; j < size; j++) {
            if (students[j].cgpa > students[maxIndex].cgpa) {
                maxIndex = j; // Found a higher CGPA!
            }
        }

        // Swap only if a higher CGPA was found at a different index
        if (maxIndex != i) {
            StudentMerit temp = students[i];
            students[i] = students[maxIndex];
            students[maxIndex] = temp;
        }

        // Display state after each pass for educational clarity
        cout << "Pass " << (i + 1) << " (Locked Rank " << (i + 1) << ": " 
             << students[i].name << " [" << fixed << setprecision(2) << students[i].cgpa << "]): ";
        for (int k = 0; k < size; k++) {
            cout << students[k].cgpa << " ";
        }
        cout << "\n";
    }
    cout << "========================================================================\n\n";
}

/*
ALGORITHM: DISPLAY TOP 5 STUDENTS
1. Determine how many records to display: `topK = min(5, size)`.
2. Print tabular header.
3. Loop rank from `1` to `topK`:
   Print Rank, Roll No, Name, and CGPA.
4. Congratulate top rankers.
*/
void displayTopStudents(const StudentMerit students[], int size, int topK = 5) {
    int limit = (size < topK) ? size : topK;

    cout << "************************************************************************\n";
    cout << "                OFFICIAL MERIT LIST: TOP " << limit << " STUDENTS       \n";
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
    // Unsorted student dataset (N = 8)
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
    cout << "   CGPA MERIT LIST SYSTEM (SELECTION SORT - DESCENDING)       \n";
    cout << "==============================================================\n";

    // 1. Initial State
    displayAllStudents(batch, totalStudents, "ORIGINAL UNRANKED DATASET");

    // 2. Perform Selection Sort
    selectionSortDescending(batch, totalStudents);

    // 3. Display Full Sorted Merit List
    displayAllStudents(batch, totalStudents, "FULL MERIT LIST (SORTED DESCENDING)");

    // 4. Extract and Display Top 5 Students
    displayTopStudents(batch, totalStudents, 5);

    cout << "==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
Dataset (N = 8):
Aarav (8.45), Bhavna (9.60), Chetan (7.80), Divya (9.15),
Esha (8.90), Farhan (6.75), Gaurav (9.85), Harita (9.30)

Selection Sort Pass Trace:
- Pass 1: Max is Gaurav (9.85). Swaps with Aarav (index 0).
- Pass 2: Max in remaining is Bhavna (9.60). Already at index 1.
- Pass 3: Max in remaining is Harita (9.30). Swaps with Chetan (index 2).
- Pass 4: Max in remaining is Divya (9.15). Already at index 3.
- Pass 5: Max in remaining is Esha (8.90). Already at index 4.
- Pass 6: Max in remaining is Aarav (8.45). Swaps with Farhan (index 5).
- Pass 7: Max in remaining is Chetan (7.80). Already at index 6.

Top 5 Rankers:
#1: Gaurav Shinde (9.85)
#2: Bhavna Patil (9.60)
#3: Harita Nair (9.30)
#4: Divya Kulkarni (9.15)
#5: Esha Verma (8.90)

SAMPLE OUTPUT:
==============================================================
   CGPA MERIT LIST SYSTEM (SELECTION SORT - DESCENDING)       
==============================================================

--- ORIGINAL UNRANKED DATASET ---
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

================ EXECUTION TRACE: SELECTION SORT PASSES ================
Pass 1 (Locked Rank 1: Gaurav Shinde [9.85]): 9.85 9.60 7.80 9.15 8.90 6.75 8.45 9.30 
Pass 2 (Locked Rank 2: Bhavna Patil [9.60]): 9.85 9.60 7.80 9.15 8.90 6.75 8.45 9.30 
Pass 3 (Locked Rank 3: Harita Nair [9.30]): 9.85 9.60 9.30 9.15 8.90 6.75 8.45 7.80 
Pass 4 (Locked Rank 4: Divya Kulkarni [9.15]): 9.85 9.60 9.30 9.15 8.90 6.75 8.45 7.80 
Pass 5 (Locked Rank 5: Esha Verma [8.90]): 9.85 9.60 9.30 9.15 8.90 6.75 8.45 7.80 
Pass 6 (Locked Rank 6: Aarav Sharma [8.45]): 9.85 9.60 9.30 9.15 8.90 8.45 6.75 7.80 
Pass 7 (Locked Rank 7: Chetan Joshi [7.80]): 9.85 9.60 9.30 9.15 8.90 8.45 7.80 6.75 
========================================================================

--- FULL MERIT LIST (SORTED DESCENDING) ---
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
                OFFICIAL MERIT LIST: TOP 5 STUDENTS       
************************************************************************
Rank    Roll No     Student Name            CGPA      Distinction     
------------------------------------------------------------------------
#1      107         Gaurav Shinde           9.85      First Class with Distinction
#2      102         Bhavna Patil            9.60      First Class with Distinction
#3      108         Harita Nair             9.30      First Class with Distinction
#4      104         Divya Kulkarni          9.15      First Class with Distinction
#5      105         Esha Verma              8.90      First Class     
************************************************************************

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

STEP-BY-STEP DRY RUN: SELECTION SORT (FIRST 3 PASSES)
Initial: [8.45, 9.60, 7.80, 9.15, 8.90, 6.75, 9.85, 9.30]

Pass 1 (i = 0):
- maxIndex starts at 0 (8.45).
- j = 1: 9.60 > 8.45 -> maxIndex = 1.
- j = 2: 7.80 < 9.60 -> maxIndex = 1.
- j = 3: 9.15 < 9.60 -> maxIndex = 1.
- j = 4: 8.90 < 9.60 -> maxIndex = 1.
- j = 5: 6.75 < 9.60 -> maxIndex = 1.
- j = 6: 9.85 > 9.60 -> maxIndex = 6.
- j = 7: 9.30 < 9.85 -> maxIndex = 6.
End of scan: maxIndex = 6 (9.85).
Swap arr[0] with arr[6] (Aarav and Gaurav swap).
Array after Pass 1: [9.85, 9.60, 7.80, 9.15, 8.90, 6.75, 8.45, 9.30]. Rank 1 locked!

Pass 2 (i = 1):
- maxIndex starts at 1 (9.60).
- Scan j = 2..7: No element exceeds 9.60.
- maxIndex remains 1. No swap needed!
Array after Pass 2: [9.85, 9.60, 7.80, 9.15, 8.90, 6.75, 8.45, 9.30]. Rank 2 locked!

Pass 3 (i = 2):
- maxIndex starts at 2 (7.80).
- Scan j = 3..7 finds 9.30 at index 7.
- Swap arr[2] with arr[7].
Array after Pass 3: [9.85, 9.60, 9.30, 9.15, 8.90, 6.75, 8.45, 7.80]. Rank 3 locked!

========================================================================================
TIME COMPLEXITY:
- Total Comparisons: Always N*(N - 1) / 2 comparisons:
  * Best case: O(N^2)
  * Average case: O(N^2)
  * Worst case: O(N^2)
- Total Swaps: At most N - 1 swaps (O(N) swaps).
  * Best case: 0 swaps (already sorted).
  * Worst case: N - 1 swaps.

SPACE COMPLEXITY:
- Auxiliary Space: O(1) in-place sorting algorithm.

STABILITY:
- Selection Sort is inherently UNSTABLE because long-distance swaps can reorder
  two elements with equal CGPA.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Confusing Ascending vs Descending:
   - In ascending order: we look for the MINIMUM (`arr[j] < arr[minIndex]`).
   - In descending order: we look for the MAXIMUM (`arr[j] > arr[maxIndex]`).
2. Swapping inside the inner loop:
   - NEVER swap inside the `j` loop! The swap must happen ONCE per pass, after the inner
     loop finishes scanning the unsorted region.
3. Looping `i` up to `size - 1`:
   - Outer loop only needs to go to `size - 2`, because when N-1 elements are in place,
     the last remaining element is guaranteed to be in its correct position.

========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Outer loop: `for (int i = 0; i < size - 1; i++)`
[ ] 2. Assume max: `int maxIndex = i;`
[ ] 3. Inner loop: `for (int j = i + 1; j < size; j++)`
[ ] 4. Compare condition: `if (arr[j].cgpa > arr[maxIndex].cgpa) maxIndex = j;`
[ ] 5. Single swap after inner loop: `if (maxIndex != i) swap(arr[i], arr[maxIndex]);`
[ ] 6. Top-5 extraction: loop `min(5, size)` from index 0 to 4.
========================================================================================
*/
