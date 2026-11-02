/**
 * ============================================================================
 * EXAM PROGRAM 05: QUICK SORT (LOMUTO PARTITIONING)
 * ============================================================================
 * 🧠 60-SECOND EXAM MEMORIZATION TECHNIQUE:
 * 
 * 1. THE LOMUTO PARTITION 4-LINE FORMULA:
 *    - `pivot = a[high]; i = low - 1;`
 *    - Loop `j` from `low` to `high - 1`:
 *        `if (a[j] <= pivot) { i++; swap(a[i], a[j]); }`
 *    - Place pivot: `swap(a[i + 1], a[high]);`
 *    - Return pivot index: `return i + 1;`
 * 
 * 2. THE RECURSIVE FUNCTION 3-LINE FORMULA:
 *    - Base condition: `if (low < high)`
 *    - Partition: `pi = partition(a, low, high);`
 *    - Recurse left & right (skipping pi!):
 *        `quickSort(a, low, pi - 1);`
 *        `quickSort(a, pi + 1, high);`
 * 
 * 3. THE EXAM PANIC CHECKLIST (The 3 Bugs Examiners Catch):
 *    - TRAP 1: Running the `j` loop up to `high`. Stop at `high - 1`!
 *              The element at `high` IS the pivot, do not compare it to itself!
 *    - TRAP 2: In recursive calls, writing `quickSort(a, low, pi)`. That causes
 *              an INFINITE RECURSIVE LOOP and Stack Overflow! Always use `pi - 1`
 *              and `pi + 1` because `pi` is already sorted!
 *    - TRAP 3: Forgetting the base check `if (low < high)`. Without this check,
 *              recursion runs forever until your program crashes.
 * 
 * ============================================================================
 * EXPECTED TERMINAL OUTPUT SHOWN TO EXAMINER:
 * 
 * Unsorted Array: 38 27 43 3 9 82 10 
 * Quick Sorted  : 3 9 10 27 38 43 82 
 * ============================================================================
 */

#include <iostream>

using namespace std;

// Lomuto Partition: Rearranges elements smaller than pivot to left, larger to right
int partition(int a[], int low, int high) {
    int pivot = a[high]; // 1. Pick last element as pivot
    int i = low - 1;     // 2. Boundary of elements <= pivot

    // 3. Scan from low to high - 1
    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++; // Expand boundary
            int temp = a[i]; a[i] = a[j]; a[j] = temp; // Swap smaller into boundary
        }
    }
    // 4. Put pivot directly after boundary
    int temp = a[i + 1]; a[i + 1] = a[high]; a[high] = temp;
    return i + 1; // Return pivot's permanent index
}

// Recursive Quick Sort
void quickSort(int a[], int low, int high) {
    if (low < high) { // Base condition
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);  // Recursively sort left subarray
        quickSort(a, pi + 1, high); // Recursively sort right subarray
    }
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = 7;

    cout << "Unsorted Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";

    quickSort(arr, 0, n - 1);

    cout << "Quick Sorted  : ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";

    return 0;
}

/**
 * ============================================================================
 * 🎓 EXAMINER VIVA QUESTIONS & INSTANT ANSWERS:
 * Q: What is the worst-case complexity of Quick Sort, and when does it occur?
 * A: O(N^2). It occurs when the array is already sorted (ascending or descending)
 *    and the last element is chosen as pivot, causing maximally unbalanced partitions.
 *
 * Q: What is the Average Case Time Complexity?
 * A: O(N log N) when the pivot divides the array into roughly equal halves.
 *
 * Q: Is Quick Sort an in-place sort?
 * A: Yes, it sorts the array in-place with O(1) auxiliary data memory. However,
 *    it requires O(log N) stack space for recursion.
 * ============================================================================
 */
