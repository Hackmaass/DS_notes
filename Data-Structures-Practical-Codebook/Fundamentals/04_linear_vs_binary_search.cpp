/**
 * ============================================================================
 * FUNDAMENTAL 04: SEARCHING (LINEAR SEARCH VS BINARY SEARCH)
 * ============================================================================
 * 👨‍🏫 PROFESSOR'S DEEP-DIVE CONCEPTUAL GUIDE:
 * 
 * 1. LINEAR SEARCH (The Brute-Force Detective):
 *    - Strategy: Start at index 0 and inspect every element until found or end.
 *    - Requirement: NONE. Works on ANY array (unsorted, sorted, random).
 *    - Efficiency: If target is at the end of 1,000,000 items, you must do
 *      1,000,000 comparisons! (O(N) Time).
 *
 * 2. BINARY SEARCH (The Phonebook Strategy):
 *    - Strategy: Look at the middle element (`mid`).
 *      - If target == mid: Bingo! Found.
 *      - If target > mid: Target CANNOT be in the left half! Discard it!
 *                         Set `low = mid + 1`.
 *      - If target < mid: Target CANNOT be in the right half! Discard it!
 *                         Set `high = mid - 1`.
 *    - STRICT REQUIREMENT: The array MUST BE SORTED!
 *    - Efficiency: Halves the search space each step.
 *      For 1,000,000 items, Binary Search takes at most 20 comparisons! (O(log N)).
 *
 * 3. CRITICAL INTERVIEW / VIVA BUG:
 *    Why do we write `mid = low + (high - low) / 2` instead of `(low + high) / 2`?
 *    ANSWER: Integer Overflow!
 *    In C++, if `low` and `high` are large positive integers (e.g., near 2 billion),
 *    `low + high` will exceed the maximum value of a 32-bit signed integer and
 *    roll over into a negative number, causing an invalid memory crash!
 *    `low + (high - low) / 2` is mathematically identical but immune to overflow.
 * ============================================================================
 */

#include <iostream>

using namespace std;

/**
 * ----------------------------------------------------------------------------
 * 1. LINEAR SEARCH
 * ----------------------------------------------------------------------------
 * @param arr[]        : Any array (does NOT have to be sorted)
 * @param n            : Number of elements in array
 * @param target       : Value to find
 * @param &comparisons : Tracks number of equality comparisons made
 * @return int         : Index if found, -1 if not found
 * ----------------------------------------------------------------------------
 */
int linearSearch(const int arr[], int n, int target, int &comparisons) {
    comparisons = 0;

    for (int i = 0; i < n; i++) {
        comparisons++; // Increment comparison counter

        // Element comparison
        if (arr[i] == target) {
            return i; // Found at index i!
        }
    }

    return -1; // Exhausted entire array without finding target
}

/**
 * ----------------------------------------------------------------------------
 * 2. BINARY SEARCH (Divide & Conquer)
 * ----------------------------------------------------------------------------
 * @param arr[]        : Array (MUST BE PRE-SORTED in ascending order)
 * @param n            : Number of elements
 * @param target       : Value to find
 * @param &comparisons : Tracks number of midpoint comparisons made
 * @return int         : Index if found, -1 if not found
 * ----------------------------------------------------------------------------
 */
int binarySearch(const int arr[], int n, int target, int &comparisons) {
    comparisons = 0;
    int low = 0;        // Left boundary of active search window
    int high = n - 1;   // Right boundary of active search window

    cout << "\n  --- Binary Search Step-by-Step Trace ---\n";
    cout << "  Pass | Low | High | Mid | arr[mid] | Action Taken\n";
    cout << "  --------------------------------------------------\n";

    int pass = 1;

    // Loop continues as long as search window is valid (low hasn't crossed high)
    while (low <= high) {
        comparisons++;

        // Calculate midpoint safely without integer overflow
        int mid = low + (high - low) / 2;

        cout << "   " << pass++ << "   |  " << low << "  |  " << high 
             << "   |  " << mid << "  |   " << arr[mid] << "    | ";

        // Case A: Target matches middle element exactly
        if (arr[mid] == target) {
            cout << "MATCH! Found target.\n";
            return mid;
        }
        // Case B: Target is greater than middle element -> search right half
        else if (arr[mid] < target) {
            cout << target << " > " << arr[mid] << " -> Discard left half (low = mid+1)\n";
            low = mid + 1;
        }
        // Case C: Target is smaller than middle element -> search left half
        else {
            cout << target << " < " << arr[mid] << " -> Discard right half (high = mid-1)\n";
            high = mid - 1;
        }
    }

    cout << "  Window collapsed (low > high). Target not in array.\n";
    return -1; // Not found
}

int main() {
    cout << "========================================================\n";
    cout << "  TEACHER DEMO: LINEAR SEARCH VS BINARY SEARCH\n";
    cout << "========================================================\n\n";

    // Sorted array of 8 numbers
    const int N = 8;
    int data[N] = {11, 22, 33, 44, 55, 66, 77, 88};

    cout << "Array: [ ";
    for (int i = 0; i < N; i++) cout << data[i] << " ";
    cout << "]\n";

    int target = 77;
    int linComps = 0, binComps = 0;

    // 1. RUN LINEAR SEARCH
    cout << "\n--------------------------------------------------------\n";
    cout << "1. RUNNING LINEAR SEARCH FOR TARGET " << target << ":\n";
    int linIdx = linearSearch(data, N, target, linComps);
    if (linIdx != -1) {
        cout << "  Result: Found at index " << linIdx << ".\n";
    }
    cout << "  Total Comparisons: " << linComps << " (Checks index 0, 1, 2... one by one)\n";

    // 2. RUN BINARY SEARCH
    cout << "\n--------------------------------------------------------\n";
    cout << "2. RUNNING BINARY SEARCH FOR TARGET " << target << ":\n";
    int binIdx = binarySearch(data, N, target, binComps);
    if (binIdx != -1) {
        cout << "  Result: Found at index " << binIdx << ".\n";
    }
    cout << "  Total Comparisons: " << binComps << " (Logarithmic halving!)\n";

    return 0;
}

/**
 * ============================================================================
 * 🎓 VIVA QUESTIONS & ANSWERS FOR THIS CODE:
 * ============================================================================
 * Q1: When would you ever prefer Linear Search over Binary Search?
 * A1: 1. When the dataset is completely unsorted and you only need to search once.
 *        Sorting takes O(N log N), which is slower than a single O(N) scan.
 *     2. When the data structure is a Linked List. Binary search requires
 *        O(1) random access to `mid`, which linked lists do not support.
 *
 * Q2: What is the Time Complexity comparison?
 * A2: - Linear Search:
 *       - Best: O(1) (found at index 0)
 *       - Worst: O(N) (found at last index or absent)
 *       - Average: O(N)
 *     - Binary Search:
 *       - Best: O(1) (found at first midpoint)
 *       - Worst: O(log2 N) (window repeatedly halved)
 *       - Average: O(log2 N)
 *
 * Q3: Can Binary Search be implemented using Recursion?
 * A3: Yes! Recursive binary search passes `(arr, low, mid - 1, target)` or
 *     `(arr, mid + 1, high, target)` as recursive calls. However, iterative
 *     Binary Search is preferred in exams because it uses O(1) auxiliary space,
 *     whereas recursion consumes O(log N) call stack memory.
 * ============================================================================
 */
