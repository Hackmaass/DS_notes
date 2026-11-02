/*
========================================================================================
PROGRAM HEADER:
- Program Number: 07
- Program Title: Student Percentage Arrangement using Quick Sort (Divide and Conquer)
- Unit: Unit II - Searching and Sorting Techniques
- Relevant Curriculum Topic: Quick Sort (Partitioning, Pivot Placement, Recursive Sorting)
- Course Code: CE25PCC-203 (Data Structures Laboratory) - Group B, Assignment 7
- Problem Statement:
  Write a program to arrange student percentages using Quick Sort. Implement:
  a. Partition the list
  b. Recursively apply Quick Sort
  c. Display the sorted percentage list
- Data Structure Used: Array of Floating-Point Percentages (`float percentages[]`)
- What This Program Demonstrates:
  Lomuto partition scheme, pivot selection, recursive divide-and-conquer calls,
  in-place element rearrangement, and recursion tree visualization.
========================================================================================

CONCEPT: WHY IS QUICK SORT SO FAST?
Quick Sort is a Divide-and-Conquer algorithm:
1. Divide: Pick a "pivot" element (here, the last element in the partition).
   Reorganize the array so that:
   - All elements SMALLER than the pivot are moved to the left of the pivot.
   - All elements GREATER than the pivot are moved to the right of the pivot.
   - The pivot itself is placed into its FINAL, PERMANENT sorted index!
2. Conquer: Recursively sort the sub-array to the left of the pivot, and the
   sub-array to the right of the pivot.
3. Base Case: A sub-array with 0 or 1 element is already sorted!

WHY IS IT CALLED "QUICK" SORT?
Unlike Merge Sort, Quick Sort does NOT need an auxiliary temporary array!
Everything happens in-place in RAM, giving it phenomenal cache performance.
On average, it operates in O(N log N) time, making it one of the fastest general-purpose
sorting algorithms in computer science.
*/

#include <iostream>
#include <iomanip>

using namespace std;

// Function to swap two floating-point numbers
void swapValues(float &a, float &b) {
    float temp = a;
    a = b;
    b = temp;
}

/*
ALGORITHM 1: PARTITION (Lomuto Partition Scheme)
Input: array `arr[]`, boundary indices `low` and `high`.
1. Select the rightmost element as the pivot: `pivot = arr[high]`.
2. Initialize index of smaller element: `i = low - 1`.
   `i` tracks the boundary of elements that are strictly <= `pivot`.
3. Loop index `j` from `low` to `high - 1`:
   - If `arr[j] <= pivot`:
     a. Increment boundary: `i++`.
     b. Swap `arr[i]` and `arr[j]` (move the smaller element into the left partition).
4. After scanning, the pivot belongs at index `i + 1`.
   Swap `arr[i + 1]` with `arr[high]`.
5. Display intermediate partition state.
6. Return `i + 1` (the permanent pivot index).

WHY SWAP `arr[i + 1]` WITH `arr[high]`?
Because indices `low` through `i` are all <= pivot.
Index `i + 1` currently holds an element > pivot.
By swapping `arr[i + 1]` with `arr[high]` (the pivot), the pivot is correctly
sandwiched between the smaller and larger elements!
*/
int partition(float arr[], int low, int high) {
    float pivot = arr[high]; // Choosing the last element as pivot
    int i = low - 1;         // Index of smaller element

    cout << "   [Partitioning sub-array low=" << low << ", high=" << high 
         << " | Pivot = " << fixed << setprecision(2) << pivot << "]\n";

    for (int j = low; j < high; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++; // Advance boundary
            swapValues(arr[i], arr[j]);
        }
    }

    // Place pivot in its correct sorted position
    swapValues(arr[i + 1], arr[high]);
    int pivotIndex = i + 1;

    // Display state
    cout << "   --> Pivot locked at Index [" << pivotIndex << "]. Sub-array: ";
    for (int k = low; k <= high; k++) {
        if (k == pivotIndex) cout << "[" << arr[k] << "] ";
        else cout << arr[k] << " ";
    }
    cout << "\n";

    return pivotIndex;
}

/*
ALGORITHM 2: RECURSIVE QUICK SORT
Input: array `arr[]`, indices `low` and `high`.
1. Base condition check:
   If `low < high`:
   a. Partition the array: `pivotIdx = partition(arr, low, high)`.
   b. Recursively sort elements BEFORE pivot:
      `quickSort(arr, low, pivotIdx - 1);`
   c. Recursively sort elements AFTER pivot:
      `quickSort(arr, pivotIdx + 1, high);`
2. If `low >= high`, sub-array has 0 or 1 element; return (base case).
*/
void quickSort(float arr[], int low, int high) {
    if (low < high) {
        // Step a: Find pivot index such that elements left of pivot are smaller,
        // and elements right of pivot are larger
        int pivotIndex = partition(arr, low, high);

        // Step b: Recursively sort left partition
        quickSort(arr, low, pivotIndex - 1);

        // Step c: Recursively sort right partition
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Display array of student percentages
void displayPercentages(const float arr[], int size, const string &title) {
    cout << "\n================ " << title << " ================\n";
    cout << left << setw(10) << "Index" << setw(16) << "Percentage (%)" << "\n";
    cout << "------------------------------------\n";
    for (int i = 0; i < size; i++) {
        cout << left << setw(10) << i 
             << fixed << setprecision(2) << setw(16) << arr[i] << "\n";
    }
    cout << "------------------------------------\n";
    cout << "Total Students: " << size << "\n\n";
}

// Interactive demonstration runner
int main() {
    // Unsorted student percentage records
    float studentPercentages[] = {78.50f, 92.40f, 65.20f, 88.90f, 54.00f, 95.80f, 81.30f, 72.10f};
    int n = sizeof(studentPercentages) / sizeof(studentPercentages[0]);

    cout << "==============================================================\n";
    cout << "   STUDENT PERCENTAGE ARRANGEMENT USING QUICK SORT           \n";
    cout << "==============================================================\n";

    // 1. Initial State
    displayPercentages(studentPercentages, n, "ORIGINAL UNORDERED PERCENTAGES");

    // 2. Perform Quick Sort
    cout << "================ QUICK SORT STEP-BY-STEP PARTITIONS ================\n";
    quickSort(studentPercentages, 0, n - 1);
    cout << "====================================================================\n";

    // 3. Display Final Sorted Percentages
    displayPercentages(studentPercentages, n, "FINAL SORTED PERCENTAGES (ASCENDING)");

    cout << "==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
Input Array (N = 8):
[78.50, 92.40, 65.20, 88.90, 54.00, 95.80, 81.30, 72.10]

Partition 1 (low = 0, high = 7, Pivot = 72.10):
- Elements <= 72.10: 65.20, 54.00.
- Pivot 72.10 placed at Index 2!
- Array becomes: [65.20, 54.00, [72.10], 88.90, 78.50, 95.80, 81.30, 92.40]

Subsequent recursive partitions break left [65.20, 54.00] and right [88.90..92.40].
Final Sorted Array:
[54.00, 65.20, 72.10, 78.50, 81.30, 88.90, 92.40, 95.80]

SAMPLE OUTPUT:
==============================================================
   STUDENT PERCENTAGE ARRANGEMENT USING QUICK SORT           
==============================================================

================ ORIGINAL UNORDERED PERCENTAGES ================
Index     Percentage (%)  
------------------------------------
0         78.50           
1         92.40           
2         65.20           
3         88.90           
4         54.00           
5         95.80           
6         81.30           
7         72.10           
------------------------------------
Total Students: 8

================ QUICK SORT STEP-BY-STEP PARTITIONS ================
   [Partitioning sub-array low=0, high=7 | Pivot = 72.10]
   --> Pivot locked at Index [2]. Sub-array: 65.20 54.00 [72.10] 88.90 78.50 95.80 81.30 92.40 
   [Partitioning sub-array low=0, high=1 | Pivot = 54.00]
   --> Pivot locked at Index [0]. Sub-array: [54.00] 65.20 
   [Partitioning sub-array low=3, high=7 | Pivot = 92.40]
   --> Pivot locked at Index [6]. Sub-array: 88.90 78.50 81.30 72.10 95.80 [92.40] 
   [Partitioning sub-array low=3, high=5 | Pivot = 81.30]
   --> Pivot locked at Index [4]. Sub-array: 78.50 [81.30] 88.90 
   [Partitioning sub-array low=6, high=7 | Pivot = 95.80]
   --> Pivot locked at Index [7]. Sub-array: 92.40 [95.80] 
====================================================================

================ FINAL SORTED PERCENTAGES (ASCENDING) ================
Index     Percentage (%)  
------------------------------------
0         54.00           
1         65.20           
2         72.10           
3         78.50           
4         81.30           
5         88.90           
6         92.40           
7         95.80           
------------------------------------
Total Students: 8

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

STEP-BY-STEP DRY RUN: PARTITION FUNCTION
Array: [78.50, 92.40, 65.20, 88.90, 54.00, 95.80, 81.30, 72.10], low = 0, high = 7.
pivot = 72.10. i = -1.

- j = 0: arr[0] = 78.50 <= 72.10? False. i remains -1.
- j = 1: arr[1] = 92.40 <= 72.10? False. i remains -1.
- j = 2: arr[2] = 65.20 <= 72.10? True!
  i becomes 0. Swap arr[0] (78.50) with arr[2] (65.20).
  Array: [65.20, 92.40, 78.50, 88.90, 54.00, 95.80, 81.30, 72.10]
- j = 3: arr[3] = 88.90 <= 72.10? False.
- j = 4: arr[4] = 54.00 <= 72.10? True!
  i becomes 1. Swap arr[1] (92.40) with arr[4] (54.00).
  Array: [65.20, 54.00, 78.50, 88.90, 92.40, 95.80, 81.30, 72.10]
- j = 5: arr[5] = 95.80 <= 72.10? False.
- j = 6: arr[6] = 81.30 <= 72.10? False.
End of j loop.
Swap pivot at arr[high] (72.10) with arr[i + 1] (arr[2] = 78.50).
Array: [65.20, 54.00, 72.10, 88.90, 92.40, 95.80, 81.30, 78.50]
Pivot 72.10 is now at index 2.
Left of index 2: [65.20, 54.00] (all < 72.10).
Right of index 2: [88.90, 92.40, 95.80, 81.30, 78.50] (all > 72.10).
Returns pivotIndex = 2.

========================================================================================
TIME COMPLEXITY:
- Best case: O(N log N) - occurs when the pivot always splits the array into two equal halves.
- Average case: O(N log N) - on arbitrary datasets with random pivots.
- Worst case: O(N^2) - occurs when the array is ALREADY SORTED (or reverse sorted) and
  we pick the extreme element as pivot (partition sizes are 0 and N - 1).

SPACE COMPLEXITY:
- Auxiliary Space (Call Stack):
  * Best case: O(log N) stack frames.
  * Worst case: O(N) stack frames (unbalanced recursion tree).
- In-place sorting: Uses O(1) extra array memory!

STABILITY:
- Quick Sort is UNSTABLE because swapping elements across the pivot can reorder duplicates.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Recursive Call with `pivot` Included:
   - Writing `quickSort(arr, low, pivotIndex)` or `quickSort(arr, pivotIndex, high)`!
   - This causes an INFINITE RECURSIVE LOOP.
   - The pivot is ALREADY in its correct position. The recursive calls MUST be:
     `quickSort(arr, low, pivotIndex - 1);` and `quickSort(arr, pivotIndex + 1, high);`.
2. Incorrect Boundary in Lomuto Partition:
   - Initializing `i = low` instead of `i = low - 1`.
   - Running `j <= high` instead of `j < high` (this would compare the pivot against itself!).
3. Missing Base Case:
   - Forgetting `if (low < high)` check before recursing leads to infinite stack overflow.

========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Partition: `float pivot = arr[high]; int i = low - 1;`
[ ] 2. For loop: `for (int j = low; j < high; j++) if (arr[j] <= pivot) { i++; swap(arr[i], arr[j]); }`
[ ] 3. Pivot swap: `swap(arr[i + 1], arr[high]); return i + 1;`
[ ] 4. Recursive calls:
       - `if (low < high) {`
       - `int p = partition(arr, low, high);`
       - `quickSort(arr, low, p - 1);`
       - `quickSort(arr, p + 1, high);`
       - `}`
========================================================================================
*/
