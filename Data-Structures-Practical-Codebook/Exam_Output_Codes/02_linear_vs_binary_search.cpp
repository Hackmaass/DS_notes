/**
 * ============================================================================
 * EXAM PROGRAM 02: SEARCHING (LINEAR SEARCH VS BINARY SEARCH)
 * ============================================================================
 * 📝 STEP-BY-STEP ALGORITHMS (Copy these directly onto your exam answer sheet!):
 * 
 * ALGORITHM 1: LINEAR SEARCH
 *   Step 1: Start.
 *   Step 2: Initialize `comparisons = 0`, `foundIndex = -1`.
 *   Step 3: Loop `i` from 0 to `n - 1`:
 *             Increment `comparisons`.
 *             If `arr[i] == target`:
 *               Set `foundIndex = i`, break loop.
 *   Step 4: Output `foundIndex` and `comparisons`.
 *   Step 5: Stop.
 * 
 * ALGORITHM 2: BINARY SEARCH (Divide and Conquer)
 *   Step 1: Start.
 *   Step 2: Ensure array `arr` is SORTED in ascending order.
 *   Step 3: Initialize `low = 0`, `high = n - 1`, `comparisons = 0`, `foundIndex = -1`.
 *   Step 4: While `low <= high`:
 *             a. Calculate midpoint: `mid = low + (high - low) / 2`.
 *             b. Increment `comparisons`.
 *             c. If `arr[mid] == target`:
 *                  Set `foundIndex = mid`, break loop.
 *             d. Else if `arr[mid] < target`:
 *                  Discard left half: `low = mid + 1`.
 *             e. Else:
 *                  Discard right half: `high = mid - 1`.
 *   Step 5: Output `foundIndex` and `comparisons`.
 *   Step 6: Stop.
 * 
 * ============================================================================
 * 🧠 60-SECOND EXAM MEMORIZATION TECHNIQUE:
 * 
 * 1. LINEAR SEARCH MEMORY ANCHOR:
 *    Just a simple `for` loop from `0` to `n - 1`. If `arr[i] == target`, record
 *    the index and `break`. Always count comparisons with `linComps++`.
 * 
 * 2. BINARY SEARCH 4-LINE FORMULA:
 *    - Initialize: `low = 0`, `high = n - 1`
 *    - Loop condition: `while (low <= high)`  <-- MUST BE `<=`, NOT `<`!
 *    - Midpoint: `mid = low + (high - low) / 2;`
 *    - The 3-way Branch:
 *        1. `arr[mid] == target` -> Found! `break;`
 *        2. `arr[mid] < target`  -> Target is to the right: `low = mid + 1;`
 *        3. Else                 -> Target is to the left : `high = mid - 1;`
 * 
 * 3. THE EXAM PANIC CHECKLIST (The 3 Bugs Examiners Catch):
 *    - TRAP 1: Forgetting `<=` in `while (low <= high)`. If you write `low < high`,
 *              the search FAILS when the target is at the very ends or single element!
 *    - TRAP 2: Writing `low = mid` instead of `low = mid + 1`. This causes an
 *              INFINITE LOOP where the program freezes forever! Always skip `mid`.
 *    - TRAP 3: Testing on an unsorted array! Binary search GIVES WRONG ANSWERS
 *              unless the numbers are already in ascending order.
 * 
 * ============================================================================
 * EXPECTED TERMINAL OUTPUT SHOWN TO EXAMINER:
 * 
 * Array: 12 24 36 48 60 72 84 96 
 * Target: 72
 * Linear Search: Found at index 5 with 6 comparisons
 * Binary Search: Found at index 5 with 3 comparisons
 * ============================================================================
 */

#include <iostream>

using namespace std;

int main() {
    // Array MUST be in ascending sorted order for Binary Search!
    int arr[] = {12, 24, 36, 48, 60, 72, 84, 96};
    int n = 8, target = 72;

    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\nTarget: " << target << "\n";

    // ------------------------------------------------------------------------
    // 1. LINEAR SEARCH (Sequential Scan)
    // ------------------------------------------------------------------------
    int linComps = 0, linIdx = -1;
    for (int i = 0; i < n; i++) {
        linComps++; // Count every equality check
        if (arr[i] == target) {
            linIdx = i; // Target found
            break;
        }
    }
    cout << "Linear Search: Found at index " << linIdx 
         << " with " << linComps << " comparisons\n";

    // ------------------------------------------------------------------------
    // 2. BINARY SEARCH (Logarithmic Halving)
    // ------------------------------------------------------------------------
    int binComps = 0, binIdx = -1;
    int low = 0, high = n - 1;

    // Boundary check: loop as long as the search window has at least 1 element
    while (low <= high) {
        binComps++; // Count midpoint comparison

        // Safe midpoint calculation (immune to integer overflow)
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            binIdx = mid; // Target found!
            break;
        } else if (arr[mid] < target) {
            low = mid + 1; // Discard left half, search right
        } else {
            high = mid - 1; // Discard right half, search left
        }
    }
    cout << "Binary Search: Found at index " << binIdx 
         << " with " << binComps << " comparisons\n";

    return 0;
}

/**
 * ============================================================================
 * 🎓 EXAMINER VIVA QUESTIONS & INSTANT ANSWERS:
 * Q: What is the strict prerequisite for Binary Search?
 * A: The array MUST BE SORTED. Binary search relies on sorted order to discard
 *    half of the search space at each comparison.
 *
 * Q: Why do you calculate mid as `low + (high - low) / 2` instead of `(low + high) / 2`?
 * A: To avoid 32-bit integer overflow. If `low + high` exceeds INT_MAX, it wraps
 *    around into a negative number and crashes the program.
 *
 * Q: What are the Time Complexities?
 * A: Linear Search is O(N). Binary Search is O(log2 N).
 * ============================================================================
 */
