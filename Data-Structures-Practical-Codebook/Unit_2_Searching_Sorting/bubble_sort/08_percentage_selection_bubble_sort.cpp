/*
========================================================================================
PROGRAM HEADER:
- Program Number: 08
- Program Title: Student Percentages - Selection Sort vs Optimized Bubble Sort
- Unit: Unit II - Searching and Sorting Techniques
- Relevant Curriculum Topic: Selection Sort, Bubble Sort (Ascending Order), and Top-5 Scores Display
- Course Code: CE25PCC-203 (Data Structures Laboratory) - Group B, Assignment 8
- Problem Statement:
  Write a program to store the percentage of students in an array. Write function for
  sorting array of floating-point numbers in ascending order using:
  a. Selection Sort
  b. Bubble sort and display top five scores.
- Data Structure Used: Array of Floating-Point Percentages (`float percentages[]`)
- What This Program Demonstrates:
  Ascending order Selection Sort (minimum element selection) vs Bubble Sort (adjacent
  neighbor comparisons with early-termination flag), stability comparison, and
  top-5 highest score extraction.
========================================================================================

CONCEPT: BUBBLE SORT VS SELECTION SORT (ASCENDING ORDER)
1. Bubble Sort:
   - Compares ADJACENT pairs `(arr[j], arr[j+1])`.
   - If `arr[j] > arr[j+1]`, they are swapped!
   - Metaphor: Heavy elements "sink" to the bottom, and lighter elements "bubble" to the top.
   - At the end of Pass 1, the absolute LARGEST percentage in the array is guaranteed
     to have bubbled up to the final index (`size - 1`).
   - Optimization: A boolean `swapped` flag tracks whether any swap occurred during the pass.
     If an entire pass completes with ZERO swaps, the array is already sorted! We terminate
     early, giving an adaptive O(N) best-case time complexity.
   - Bubble Sort is STABLE (adjacent swaps never cross identical values).

2. Selection Sort (Ascending):
   - In each pass `i`, finds the index of the MINIMUM element in the unsorted region `[i .. N-1]`.
   - Swaps it with `arr[i]`.
   - Minimal swaps (at most N-1 swaps), but always O(N^2) comparisons (not adaptive).
*/

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_STUDENTS = 50;

// Swap helper
void swapValues(float &a, float &b) {
    float temp = a;
    a = b;
    b = temp;
}

/*
ALGORITHM 1: SELECTION SORT (ASCENDING ORDER)
1. Loop pass index `i` from `0` to `size - 2`:
   a. Assume `minIndex = i`.
   b. Scan unsorted partition `j` from `i + 1` to `size - 1`:
      - If `arr[j] < arr[minIndex]`:
        Update `minIndex = j`.
   c. If `minIndex != i`:
      Swap `arr[i]` with `arr[minIndex]`.
   d. Display intermediate array state after Pass `i + 1`.
2. Array is now sorted in ascending order.
*/
void selectionSortAscending(float arr[], int size) {
    cout << "\n================ SELECTION SORT TRACE (ASCENDING) ================\n";

    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;

        // Search for smallest element in unsorted partition
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Swap minimum into place
        if (minIndex != i) {
            swapValues(arr[i], arr[minIndex]);
        }

        // Educational pass print
        cout << "Pass " << (i + 1) << " [Minimum at Index " << i << " is " 
             << fixed << setprecision(2) << arr[i] << "]: ";
        for (int k = 0; k < size; k++) {
            cout << arr[k] << " ";
        }
        cout << "\n";
    }
    cout << "==================================================================\n\n";
}

/*
ALGORITHM 2: BUBBLE SORT (ASCENDING ORDER WITH EARLY TERMINATION)
1. Loop pass index `i` from `0` to `size - 2`:
   a. Set `swapped = false`.
   b. Inner loop `j` from `0` to `size - 2 - i`:
      (WHY `size - 2 - i`? Because the last `i` elements are already permanently sorted!).
      - If `arr[j] > arr[j + 1]`:
        * Swap `arr[j]` and `arr[j + 1]`.
        * Set `swapped = true`.
   c. Display array state after Pass `i + 1`.
   d. If `swapped == false`:
      Array is already completely sorted! Break early to save CPU cycles.
*/
void bubbleSortAscending(float arr[], int size) {
    cout << "\n================ BUBBLE SORT TRACE (ASCENDING) ===================\n";

    for (int i = 0; i < size - 1; i++) {
        bool swapped = false; // Flag to detect early completion

        for (int j = 0; j < size - 1 - i; j++) {
            // Compare adjacent neighbors
            if (arr[j] > arr[j + 1]) {
                swapValues(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        cout << "Pass " << (i + 1) << " [Bubbled largest to Index " << (size - 1 - i) 
             << " (" << fixed << setprecision(2) << arr[size - 1 - i] << ")]: ";
        for (int k = 0; k < size; k++) {
            cout << arr[k] << " ";
        }
        cout << "\n";

        // Adaptive early exit
        if (!swapped) {
            cout << ">> Optimization triggered: No swaps occurred in Pass " 
                 << (i + 1) << ". Array is sorted!\n";
            break;
        }
    }
    cout << "==================================================================\n\n";
}

/*
ALGORITHM 3: DISPLAY TOP 5 HIGHEST SCORES
Prerequisite: Array must be sorted in ascending order.
1. In an ascending array of size N, the 5 highest scores are located at the END
   of the array (from index `size - 1` down to `size - 5`).
2. Loop `count` from 1 to `min(5, size)`:
   - Index: `size - count`.
   - Print Rank, Percentage score.
*/
void displayTopFiveScores(const float arr[], int size) {
    int limit = (size < 5) ? size : 5;

    cout << "******************************************************************\n";
    cout << "                TOP " << limit << " HIGHEST PERCENTAGE SCORES             \n";
    cout << "******************************************************************\n";
    cout << left << setw(10) << "Rank"
         << setw(16) << "Percentage (%)"
         << setw(16) << "Grade Remark" << "\n";
    cout << "------------------------------------------------------------------\n";

    for (int i = 1; i <= limit; i++) {
        int idx = size - i; // Read from the tail of the ascending array
        string remark = (arr[idx] >= 90.0f) ? "Outstanding" : ((arr[idx] >= 75.0f) ? "Distinction" : "First Class");

        cout << left << setw(10) << ("#" + to_string(i))
             << fixed << setprecision(2) << setw(16) << arr[idx]
             << setw(16) << remark << "\n";
    }
    cout << "******************************************************************\n\n";
}

void printArray(const float arr[], int size, const string &label) {
    cout << label << ": [ ";
    for (int i = 0; i < size; i++) {
        cout << fixed << setprecision(2) << arr[i] << (i < size - 1 ? ", " : " ");
    }
    cout << "]\n";
}

// Interactive demonstration runner
int main() {
    float rawScores[] = {74.20f, 91.50f, 62.80f, 88.40f, 95.10f, 81.60f, 69.30f, 93.00f};
    int n = sizeof(rawScores) / sizeof(rawScores[0]);

    // Create duplicate arrays to independently test Selection Sort and Bubble Sort
    float scoresForSelection[MAX_STUDENTS];
    float scoresForBubble[MAX_STUDENTS];
    for (int i = 0; i < n; i++) {
        scoresForSelection[i] = rawScores[i];
        scoresForBubble[i] = rawScores[i];
    }

    cout << "==============================================================\n";
    cout << "   STUDENT PERCENTAGE SORTING: SELECTION VS BUBBLE SORT       \n";
    cout << "==============================================================\n";

    printArray(rawScores, n, "Original Student Scores");

    // 1. Selection Sort Demonstration
    cout << "\n--- DEMO PART A: Sorting Ascending using Selection Sort ---";
    selectionSortAscending(scoresForSelection, n);
    printArray(scoresForSelection, n, "Selection Sorted Result");

    // 2. Bubble Sort Demonstration
    cout << "\n--- DEMO PART B: Sorting Ascending using Bubble Sort ---";
    bubbleSortAscending(scoresForBubble, n);
    printArray(scoresForBubble, n, "Bubble Sorted Result");

    // 3. Display Top 5 Highest Scores
    cout << "\n--- DEMO PART C: Extracting Top Five Scores ---";
    displayTopFiveScores(scoresForBubble, n);

    cout << "==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
Input Array (N = 8):
[74.20, 91.50, 62.80, 88.40, 95.10, 81.60, 69.30, 93.00]

Bubble Sort Pass 1:
- Adjacent pairs compared: (74.2, 91.5) ok, (91.5, 62.8) swap, (91.5, 88.4) swap,
  (91.5, 95.1) ok, (95.1, 81.6) swap, (95.1, 69.3) swap, (95.1, 93.0) swap.
- Largest score 95.10 is now at index 7!
Pass 2 sinks 93.00 to index 6.
Pass 3 sinks 91.50 to index 5.

Sorted Ascending:
[62.80, 69.30, 74.20, 81.60, 88.40, 91.50, 93.00, 95.10]

Top 5 Scores read from the right end:
#1: 95.10 (Index 7)
#2: 93.00 (Index 6)
#3: 91.50 (Index 5)
#4: 88.40 (Index 4)
#5: 81.60 (Index 3)

SAMPLE OUTPUT:
==============================================================
   STUDENT PERCENTAGE SORTING: SELECTION VS BUBBLE SORT       
==============================================================
Original Student Scores: [ 74.20, 91.50, 62.80, 88.40, 95.10, 81.60, 69.30, 93.00 ]

--- DEMO PART A: Sorting Ascending using Selection Sort ---
================ SELECTION SORT TRACE (ASCENDING) ================
Pass 1 [Minimum at Index 0 is 62.80]: 62.80 91.50 74.20 88.40 95.10 81.60 69.30 93.00 
Pass 2 [Minimum at Index 1 is 69.30]: 62.80 69.30 74.20 88.40 95.10 81.60 91.50 93.00 
Pass 3 [Minimum at Index 2 is 74.20]: 62.80 69.30 74.20 88.40 95.10 81.60 91.50 93.00 
Pass 4 [Minimum at Index 3 is 81.60]: 62.80 69.30 74.20 81.60 95.10 88.40 91.50 93.00 
Pass 5 [Minimum at Index 4 is 88.40]: 62.80 69.30 74.20 81.60 88.40 95.10 91.50 93.00 
Pass 6 [Minimum at Index 5 is 91.50]: 62.80 69.30 74.20 81.60 88.40 91.50 95.10 93.00 
Pass 7 [Minimum at Index 6 is 93.00]: 62.80 69.30 74.20 81.60 88.40 91.50 93.00 95.10 
==================================================================

Selection Sorted Result: [ 62.80, 69.30, 74.20, 81.60, 88.40, 91.50, 93.00, 95.10 ]

--- DEMO PART B: Sorting Ascending using Bubble Sort ---
================ BUBBLE SORT TRACE (ASCENDING) ===================
Pass 1 [Bubbled largest to Index 7 (95.10)]: 74.20 62.80 88.40 91.50 81.60 69.30 93.00 95.10 
Pass 2 [Bubbled largest to Index 6 (93.00)]: 62.80 74.20 88.40 81.60 69.30 91.50 93.00 95.10 
Pass 3 [Bubbled largest to Index 5 (91.50)]: 62.80 74.20 81.60 69.30 88.40 91.50 93.00 95.10 
Pass 4 [Bubbled largest to Index 4 (88.40)]: 62.80 74.20 69.30 81.60 88.40 91.50 93.00 95.10 
Pass 5 [Bubbled largest to Index 3 (81.60)]: 62.80 69.30 74.20 81.60 88.40 91.50 93.00 95.10 
Pass 6 [Bubbled largest to Index 2 (74.20)]: 62.80 69.30 74.20 81.60 88.40 91.50 93.00 95.10 
>> Optimization triggered: No swaps occurred in Pass 6. Array is sorted!
==================================================================

Bubble Sorted Result: [ 62.80, 69.30, 74.20, 81.60, 88.40, 91.50, 93.00, 95.10 ]

--- DEMO PART C: Extracting Top Five Scores ---
******************************************************************
                TOP 5 HIGHEST PERCENTAGE SCORES             
******************************************************************
Rank      Percentage (%)  Grade Remark    
------------------------------------------------------------------
#1        95.10           Outstanding     
#2        93.00           Outstanding     
#3        91.50           Outstanding     
#4        88.40           Distinction     
#5        81.60           Distinction     
******************************************************************

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

TIME COMPLEXITY:
- Selection Sort:
  * Best case: O(N^2)
  * Average case: O(N^2)
  * Worst case: O(N^2)
- Bubble Sort:
  * Best case: O(N) - when array is already sorted, `swapped` flag exits on Pass 1.
  * Average case: O(N^2)
  * Worst case: O(N^2) - reverse sorted array requires N*(N-1)/2 swaps.

SPACE COMPLEXITY:
- Auxiliary Space: O(1) in-place sorting for both.

STABILITY:
- Bubble Sort is STABLE (adjacent comparison `>` never swaps equal values).
- Selection Sort is UNSTABLE.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Inner Loop Boundary in Bubble Sort:
   - Writing `j < size - 1` instead of `j < size - 1 - i`.
   - While `j < size - 1` is correct, it wastefully re-compares elements that have
     already bubbled to their final positions.
2. Forgetting the `swapped` Flag Reset:
   - Forgetting to reset `swapped = false` at the START of each outer pass `i`.
3. Reading Top 5 from the Wrong End:
   - In an ASCENDING array, the highest scores are at `size - 1`, `size - 2`, etc.
     Reading from index `0` gives the lowest scores!
========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Selection sort: `int minIdx = i; for(int j=i+1; j<n; j++) if(arr[j]<arr[minIdx]) minIdx=j; swap(arr[i], arr[minIdx]);`
[ ] 2. Bubble sort: `for(int i=0; i<n-1; i++) { bool s=false; for(int j=0; j<n-1-i; j++) if(arr[j]>arr[j+1]) { swap(arr[j], arr[j+1]); s=true; } if(!s) break; }`
[ ] 3. Top-5 extraction from ascending array: loop `i = 1 to 5`, read `arr[n - i]`.
========================================================================================
*/
