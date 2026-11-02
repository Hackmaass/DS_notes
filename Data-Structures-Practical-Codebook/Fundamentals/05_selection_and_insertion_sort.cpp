/**
 * ============================================================================
 * FUNDAMENTAL 05: SORTING (SELECTION SORT VS INSERTION SORT)
 * ============================================================================
 * 👨‍🏫 PROFESSOR'S DEEP-DIVE CONCEPTUAL GUIDE:
 * 
 * 1. SELECTION SORT (The "Find the Minimum" Strategy):
 *    - Mental Model: Imagine lined-up students. You walk down the entire line,
 *      find the shortest student, and swap them with the student at position 0.
 *      Then you find the second shortest student, and swap them with position 1.
 *    - Key Characteristic: Exactly ONE SWAP per outer pass!
 *      Total swaps is at most N - 1. (Ideal when memory writes are costly).
 *    - Time Complexity: Always O(N^2), even if already sorted, because it
 *      blindly scans the remaining list every single time.
 *
 * 2. INSERTION SORT (The "Playing Cards in Hand" Strategy):
 *    - Mental Model: Imagine picking up playing cards one by one.
 *      You pick card `key`. You compare it with cards already sorted in your
 *      hand from right to left. As long as a card is larger than `key`, you
 *      shift it one slot right. When you find where `key` belongs, you drop it!
 *    - Key Characteristic: ADAPTIVE!
 *      If the array is already sorted, the `while` loop condition fails immediately.
 *      It finishes in O(N) time with ZERO shifts!
 *
 * 3. SUMMARY COMPARISON FOR VIVA:
 *    - Selection Sort: Minimizes Swaps (at most N swaps). Not adaptive.
 *    - Insertion Sort: Minimizes Comparisons on nearly sorted data. Adaptive!
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
 * 1. SELECTION SORT
 * ----------------------------------------------------------------------------
 * Steps:
 *   1. Outer loop `i` from 0 to n - 2:
 *      Assume index `i` holds the minimum element (`minIdx = i`).
 *   2. Inner loop `j` from `i + 1` to n - 1:
 *      If `arr[j] < arr[minIdx]`, update `minIdx = j`.
 *   3. After inner loop, swap `arr[i]` with `arr[minIdx]`.
 * ----------------------------------------------------------------------------
 */
void selectionSort(int arr[], int n) {
    cout << "\n  --- Selection Sort Step-by-Step Passes ---\n";

    // Loop runs (n - 1) times. The last remaining element is automatically in place.
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i; // Assume current slot has the smallest value

        // Search the unsorted subarray arr[i+1 .. n-1] for the real minimum
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j; // Found a smaller element, record its index
            }
        }

        // Swap the true minimum into position i (only if minIdx moved)
        if (minIdx != i) {
            swapElements(arr[i], arr[minIdx]);
        }

        cout << "  Pass " << (i + 1) << " (Placed min " << arr[i] << " at [" << i << "]): ";
        printArray(arr, n);
    }
}

/**
 * ----------------------------------------------------------------------------
 * 2. INSERTION SORT
 * ----------------------------------------------------------------------------
 * Steps:
 *   1. Outer loop `i` from 1 to n - 1:
 *      Pick card `key = arr[i]`.
 *   2. Inner while loop:
 *      Look at sorted cards to the left (`j = i - 1` down to 0).
 *      If `arr[j] > key`, shift `arr[j]` one slot to the right (`arr[j + 1] = arr[j]`).
 *   3. Drop `key` into the cleared slot (`arr[j + 1] = key`).
 * ----------------------------------------------------------------------------
 */
void insertionSort(int arr[], int n) {
    cout << "\n  --- Insertion Sort Step-by-Step Passes ---\n";

    // Element at index 0 is trivially sorted by itself. Start at index 1.
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // The item to be inserted into the sorted prefix
        int j = i - 1;

        // Shift elements greater than key to make room
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Shift element right
            j--;                 // Move one step left in sorted hand
        }

        // Insert key into its correct sorted position
        arr[j + 1] = key;

        cout << "  Pass " << i << " (Inserted key " << key << "): ";
        printArray(arr, n);
    }
}

int main() {
    cout << "========================================================\n";
    cout << "  TEACHER DEMO: SELECTION SORT VS INSERTION SORT\n";
    cout << "========================================================\n\n";

    int arr1[6] = {64, 25, 12, 22, 11, 90};
    int arr2[6] = {64, 25, 12, 22, 11, 90};
    int n = 6;

    cout << "Original Unsorted Array: ";
    printArray(arr1, n);

    // 1. SELECTION SORT DEMO
    cout << "\n--------------------------------------------------------\n";
    cout << "1. RUNNING SELECTION SORT:\n";
    selectionSort(arr1, n);

    // 2. INSERTION SORT DEMO
    cout << "\n--------------------------------------------------------\n";
    cout << "2. RUNNING INSERTION SORT:\n";
    insertionSort(arr2, n);

    return 0;
}

/**
 * ============================================================================
 * 🎓 VIVA QUESTIONS & ANSWERS FOR THIS CODE:
 * ============================================================================
 * Q1: Is Selection Sort stable? Is Insertion Sort stable?
 * A1: - Selection Sort is UNSTABLE by default. A long-distance swap can jump
 *       over duplicate elements, changing their relative order.
 *     - Insertion Sort is STABLE. Because the while loop checks `arr[j] > key`
 *       (strict greater than), equal keys are never shifted over each other!
 *
 * Q2: What are the Time Complexities?
 * A2: - Selection Sort:
 *       - Best: O(N^2)
 *       - Worst: O(N^2)
 *       - Average: O(N^2)
 *     - Insertion Sort:
 *       - Best: O(N) (when input is already sorted; while loop never runs!)
 *       - Worst: O(N^2) (when input is in reverse order)
 *       - Average: O(N^2)
 *
 * Q3: Why is Insertion Sort preferred for small arrays or nearly sorted data?
 * A3: Because of its adaptive O(N) best case and very low overhead (cache-friendly
 *     local memory shifts). In fact, standard library sort implementations like
 *     `std::sort` switch to Insertion Sort for subarrays smaller than 16 elements!
 * ============================================================================
 */
