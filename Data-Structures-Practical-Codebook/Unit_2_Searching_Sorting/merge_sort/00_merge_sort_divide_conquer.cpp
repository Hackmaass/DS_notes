/*
========================================================================================
PROGRAM HEADER:
- Program Number: 00-MS
- Program Title: Merge Sort (Divide and Conquer with Two-Way Merging)
- Unit: Unit II - Searching and Sorting Techniques
- Relevant Curriculum Topic: Merge Sort (Recursive Division, Two-Way Merge, Guaranteed O(N log N))
- Course Code: CE25PCC-202 (Theory Core) & CE25PCC-203 (Laboratory Foundation)
- Objective:
  Demonstrate recursive divide-and-conquer splitting, two-way merging using an auxiliary
  array, stable element ordering, and intermediate merged sub-array visualization.
- Data Structure Used: Array of Integers with Dynamic/Auxiliary Temporary Buffer
- What This Program Demonstrates:
  Guaranteed O(N log N) performance in all cases (worst, average, best), stable sorting,
  merging mechanics, and recursive call stack trees.
========================================================================================

CONCEPT: WHY USE MERGE SORT?
Unlike Quick Sort (which can degrade to O(N^2) on already sorted arrays) and Bubble/Selection
Sort (which are O(N^2)), Merge Sort GUARANTEES O(N log N) time complexity under ALL conditions!

HOW IT WORKS (DIVIDE AND CONQUER):
1. Divide: If the sub-array has more than 1 element, find the midpoint:
   `mid = left + (right - left) / 2`.
2. Conquer:
   - Recursively call `mergeSort(arr, left, mid)` on the left half.
   - Recursively call `mergeSort(arr, mid + 1, right)` on the right half.
3. Combine (Merge):
   - At this point, both the left half and right half are individually sorted!
   - Run the two-way merge procedure to zip the two sorted halves together into
     a single combined sorted sequence in an auxiliary buffer.
   - Copy the sorted elements back into the original array.

TRADE-OFF:
- Requires O(N) extra auxiliary memory for merging (unlike in-place Quick Sort).
- In return, it provides STABLE sorting and predictable O(N log N) runtime.
*/

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_SIZE = 100;

/*
ALGORITHM 1: TWO-WAY MERGE PROCEDURE
Input: `arr[]`, boundary indices `left`, `mid`, `right`.
1. Calculate sizes of two sub-arrays:
   `n1 = mid - left + 1` (left sub-array)
   `n2 = right - mid`     (right sub-array)
2. Create temporary arrays `L[n1]` and `R[n2]`.
3. Copy data from `arr[left .. mid]` into `L[]` and `arr[mid+1 .. right]` into `R[]`.
4. Initialize pointers: `i = 0` (for L), `j = 0` (for R), `k = left` (for original arr).
5. Compare elements from `L` and `R`:
   `while (i < n1 && j < n2)`:
       If `L[i] <= R[j]`:
           `arr[k] = L[i]; i++;`
       Else:
           `arr[k] = R[j]; j++;`
       `k++;`
   (WHY `<=` INSTEAD OF `<`? To guarantee STABILITY! If duplicate values exist, the element
    from the left sub-array is chosen first, preserving original relative order).
6. Copy any remaining elements of `L[]` (if `i < n1`).
7. Copy any remaining elements of `R[]` (if `j < n2`).
8. Display merged sub-array state.
*/
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary auxiliary arrays
    int L[MAX_SIZE];
    int R[MAX_SIZE];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // Merge the temp arrays back into arr[left..right]
    int i = 0;    // Initial index of first sub-array
    int j = 0;    // Initial index of second sub-array
    int k = left; // Initial index of merged sub-array

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Educational visualization of merged sub-array
    cout << "   Merged [idx " << left << ".." << mid << "] and [" 
         << (mid + 1) << ".." << right << "] -> Result: ";
    for (int p = left; p <= right; p++) {
        cout << arr[p] << " ";
    }
    cout << "\n";
}

/*
ALGORITHM 2: RECURSIVE MERGE SORT
Input: `arr[]`, `left`, `right`.
1. Base condition check:
   If `left < right`:
   a. Find midpoint: `mid = left + (right - left) / 2`.
   b. Recursively sort first half: `mergeSort(arr, left, mid);`
   c. Recursively sort second half: `mergeSort(arr, mid + 1, right);`
   d. Merge the two sorted halves: `merge(arr, left, mid, right);`
2. If `left >= right`, single element; return.
*/
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Safe midpoint calculation
        int mid = left + (right - left) / 2;

        // Sort first half
        mergeSort(arr, left, mid);

        // Sort second half
        mergeSort(arr, mid + 1, right);

        // Merge sorted halves
        merge(arr, left, mid, right);
    }
}

void printArray(const int arr[], int size, const string &label) {
    cout << label << ": [ ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << (i < size - 1 ? ", " : " ");
    }
    cout << "]\n";
}

// Interactive demonstration runner
int main() {
    int dataset[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(dataset) / sizeof(dataset[0]);

    cout << "==============================================================\n";
    cout << "   MERGE SORT DEMONSTRATION (DIVIDE AND CONQUER)              \n";
    cout << "==============================================================\n";

    printArray(dataset, n, "Initial Unsorted Dataset");

    cout << "\n================ MERGE STEP-BY-STEP TRACE ====================\n";
    mergeSort(dataset, 0, n - 1);
    cout << "==============================================================\n";

    printArray(dataset, n, "\nFinal Sorted Dataset");

    cout << "\n==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
Input Array (N = 7):
[38, 27, 43, 3, 9, 82, 10]

Tree Decomposition:
[38, 27, 43, 3, 9, 82, 10]
├── Left: [38, 27, 43, 3]
│   ├── [38, 27] -> merges to [27, 38]
│   └── [43, 3]  -> merges to [3, 43]
│   └── Combined Merge -> [3, 27, 38, 43]
└── Right: [9, 82, 10]
    ├── [9, 82]  -> merges to [9, 82]
    └── [10]
    └── Combined Merge -> [9, 10, 82]
└── Final Combined Merge -> [3, 9, 10, 27, 38, 43, 82]

SAMPLE OUTPUT:
==============================================================
   MERGE SORT DEMONSTRATION (DIVIDE AND CONQUER)              
==============================================================
Initial Unsorted Dataset: [ 38, 27, 43, 3, 9, 82, 10 ]

================ MERGE STEP-BY-STEP TRACE ====================
   Merged [idx 0..0] and [1..1] -> Result: 27 38 
   Merged [idx 2..2] and [3..3] -> Result: 3 43 
   Merged [idx 0..1] and [2..3] -> Result: 3 27 38 43 
   Merged [idx 4..4] and [5..5] -> Result: 9 82 
   Merged [idx 4..5] and [6..6] -> Result: 9 10 82 
   Merged [idx 0..3] and [4..6] -> Result: 3 9 10 27 38 43 82 
==============================================================

Final Sorted Dataset: [ 3, 9, 10, 27, 38, 43, 82 ]

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

TIME COMPLEXITY:
- Best case: O(N log N)
- Average case: O(N log N)
- Worst case: O(N log N)

WHY GUARANTEED O(N log N)?
1. The array is always split exactly in half at each level of recursion:
   Depth of recursion tree = log2(N).
2. At each level of the tree, every element is merged exactly once:
   Work per level = O(N).
3. Total Time = (Work per level) * (Number of levels) = N * log2(N) = O(N log N).

SPACE COMPLEXITY:
- Auxiliary Space: O(N) extra space needed for temporary merge buffers (`L` and `R`).
- Call Stack Space: O(log N) stack frames.

STABILITY:
- Merge Sort is STABLE because the comparison condition `L[i] <= R[j]` ensures that
  elements from the left sub-array take priority over equal elements from the right sub-array.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Midpoint Calculation:
   - Use `mid = left + (right - left) / 2` to prevent overflow.
2. Forgetting Remaining Elements:
   - Forgetting the two cleanup `while (i < n1)` and `while (j < n2)` loops after the
     main merge loop! If one sub-array finishes before the other, remaining elements
     would be lost!
3. Stability Bug:
   - Writing `if (L[i] < R[j])` instead of `<=`. Strict `<` breaks stability!
========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Recursive function:
       - `if (left < right) { int mid = left + (right - left)/2; mergeSort(arr, left, mid); mergeSort(arr, mid+1, right); merge(arr, left, mid, right); }`
[ ] 2. Merge sizes: `n1 = mid - left + 1; n2 = right - mid;`
[ ] 3. Main merge loop: `while (i < n1 && j < n2) if (L[i] <= R[j]) arr[k++] = L[i++]; else arr[k++] = R[j++];`
[ ] 4. Two cleanup loops: `while (i < n1) arr[k++] = L[i++];` and `while (j < n2) arr[k++] = R[j++];`
========================================================================================
*/
