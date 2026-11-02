/**
 * ============================================================================
 * FUNDAMENTAL 06: QUICK SORT (PARTITIONING & RECURSION)
 * ============================================================================
 * 👨‍🏫 PROFESSOR'S DEEP-DIVE CONCEPTUAL GUIDE:
 * 
 * 1. THE PHILOSOPHY OF QUICK SORT:
 *    Quick Sort is a DIVIDE-AND-CONQUER algorithm created by Tony Hoare in 1959.
 *    Instead of comparing and shifting adjacent items like Bubble or Insertion sort,
 *    Quick Sort establishes a landmark called the "PIVOT".
 *
 * 2. HOW LOMUTO PARTITIONING WORKS (Step-by-Step Mental Picture):
 *    Choose the LAST element as the `pivot`: `pivot = arr[high]`.
 *    Our goal is to rearrange the array so it looks like this:
 *      [ All elements <= Pivot ]  -->  [ PIVOT ]  -->  [ All elements > Pivot ]
 *
 *    We maintain two pointers:
 *      - `i`: Marks the boundary of elements that are strictly <= pivot. Starts at `low - 1`.
 *      - `j`: The explorer/scout pointer. Walks from `low` up to `high - 1`.
 *
 *    Whenever `arr[j] <= pivot`:
 *      1. Advance boundary: `i++`
 *      2. Swap `arr[i]` and `arr[j]` (throw the small number into the small-zone!)
 *
 *    When `j` reaches the end:
 *      Swap `arr[i + 1]` with `arr[high]` (drop the pivot right at the border!).
 *    Now, the pivot is in its PERMANENT, FINAL SORTED SPOT!
 *
 * 3. THE RECURSIVE CALL:
 *    Once the pivot index `pi` is fixed, we NEVER touch it again!
 *    We simply recurse on:
 *      - Left subarray: `quickSort(arr, low, pi - 1);`
 *      - Right subarray: `quickSort(arr, pi + 1, high);`
 * ============================================================================
 */

#include <iostream>

using namespace std;

void printArray(const int arr[], int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "]\n";
}

void swapElements(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

/**
 * ----------------------------------------------------------------------------
 * THE LOMUTO PARTITION FUNCTION: The core engine of Quick Sort
 * ----------------------------------------------------------------------------
 */
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // 1. Pick last element as pivot
    int i = low - 1;       // 2. Index of smaller element boundary

    cout << "    [Partitioning Range " << low << " to " << high 
         << " with Pivot = " << pivot << "]\n";

    // Scout loop: scan through all elements except the pivot
    for (int j = low; j < high; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++; // Expand the "smaller-than-pivot" territory
            swapElements(arr[i], arr[j]); // Bring smaller element into territory
        }
    }

    // Place pivot in its correct sorted position (between small and large zones)
    swapElements(arr[i + 1], arr[high]);

    return (i + 1); // Return the final index of the pivot
}

/**
 * ----------------------------------------------------------------------------
 * RECURSIVE QUICK SORT
 * ----------------------------------------------------------------------------
 */
void quickSort(int arr[], int low, int high) {
    // BASE CONDITION: If low >= high, the subarray has 0 or 1 element,
    // which means it is already sorted! Stop recursion.
    if (low < high) {
        // Step 1: Partition array and receive pivot index
        int pi = partition(arr, low, high);

        // Step 2: Recursively sort elements before and after pivot
        quickSort(arr, low, pi - 1);  // Left subarray
        quickSort(arr, pi + 1, high); // Right subarray
    }
}

int main() {
    cout << "========================================================\n";
    cout << "  TEACHER DEMO: QUICK SORT (LOMUTO PARTITIONING)\n";
    cout << "========================================================\n\n";

    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Initial Unsorted Array: ";
    printArray(arr, n);
    cout << "\n--- Starting Recursive Quick Sort ---\n";

    quickSort(arr, 0, n - 1);

    cout << "\n--------------------------------------------------------\n";
    cout << "Final Sorted Result: ";
    printArray(arr, n);

    return 0;
}

/**
 * ============================================================================
 * 🎓 VIVA QUESTIONS & ANSWERS FOR THIS CODE:
 * ============================================================================
 * Q1: What is the Time Complexity of Quick Sort?
 * A1: - Best Case: O(N log N) when pivot divides array into two equal halves.
 *     - Average Case: O(N log N).
 *     - Worst Case: O(N^2) when array is already sorted (ascending or descending)
 *       and we pick the last element as pivot, resulting in completely unbalanced
 *       partitions of size 0 and N - 1!
 *
 * Q2: What is the Space Complexity of Quick Sort?
 * A2: - Auxiliary memory: O(1) in-place array swaps.
 *     - Call Stack memory: O(log N) average, O(N) worst case due to recursive frames.
 *
 * Q3: How do you prevent the O(N^2) worst-case in production?
 * A3: 1. Randomized Pivot Selection: Swap `arr[high]` with a random element first.
 *     2. Median-of-Three: Pick the median of `arr[low]`, `arr[mid]`, and `arr[high]`.
 * ============================================================================
 */
