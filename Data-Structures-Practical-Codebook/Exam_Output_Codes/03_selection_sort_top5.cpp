/**
 * ============================================================================
 * EXAM PROGRAM 03: SELECTION SORT & TOP 5 HIGHEST SCORES
 * ============================================================================
 * 📝 STEP-BY-STEP ALGORITHMS (Copy these directly onto your exam answer sheet!):
 * 
 * ALGORITHM: SELECTION SORT (Ascending Order) & TOP 5 EXTRACTION
 *   Step 1: Start.
 *   Step 2: Loop `i` from 0 to `n - 2`:
 *             a. Assume current index `i` holds the minimum: `minIdx = i`.
 *             b. Inner loop `j` from `i + 1` to `n - 1`:
 *                  If `arr[j] < arr[minIdx]`:
 *                    Update `minIdx = j`.
 *             c. If `minIdx != i`:
 *                  Swap `arr[i]` and `arr[minIdx]`.
 *   Step 3: Output the sorted array.
 *   Step 4: Extract Top 5 highest elements:
 *             Loop `k` from 0 to 4:
 *               Output `arr[n - 1 - k]` (read from the end of the ascending array).
 *   Step 5: Stop.
 * 
 * ============================================================================
 * 🧠 60-SECOND EXAM MEMORIZATION TECHNIQUE:
 * 
 * 1. THE 3-STEP FORMULA: "FIND MIN, SWAP ONCE"
 *    - Outer Loop: `i` from `0` to `n - 2`.
 *      Assume index `i` is the minimum: `minIdx = i;`
 *    - Inner Loop: `j` from `i + 1` to `n - 1`.
 *      If `arr[j] < arr[minIdx]`, update: `minIdx = j;`
 *    - Swap: Swap `arr[i]` with `arr[minIdx]`.
 * 
 * 2. TOP 5 RETRIEVAL TRICK:
 *    Because the array is sorted in ASCENDING order:
 *      - `arr[n - 1]` is the HIGHEST (Rank 1)
 *      - `arr[n - 2]` is the 2nd HIGHEST (Rank 2)
 *    Formula: `arr[n - 1 - i]` for `i` from `0` to `4`!
 * 
 * 3. THE EXAM PANIC CHECKLIST (The 3 Bugs Examiners Catch):
 *    - TRAP 1: Swapping inside the inner loop! In Selection Sort, you MUST only
 *              swap ONCE per pass, OUTSIDE the inner `j` loop!
 *    - TRAP 2: Starting inner loop at `j = 0` or `j = i`. Always start at `j = i + 1`,
 *              because everything before `i` is already sorted!
 *    - TRAP 3: Printing `arr[0]` to `arr[4]` as the top 5! That would print the
 *              5 LOWEST scores! Read backwards from `n - 1`.
 * 
 * ============================================================================
 * EXPECTED TERMINAL OUTPUT SHOWN TO EXAMINER:
 * 
 * Original Array: 78.5 92 65.4 88.2 95.5 71 84.6 
 * Sorted Array  : 65.4 71 78.5 84.6 88.2 92 95.5 
 * 
 * === TOP 5 HIGHEST SCORES ===
 * Rank 1: 95.5%
 * Rank 2: 92%
 * Rank 3: 88.2%
 * Rank 4: 84.6%
 * Rank 5: 78.5%
 * ============================================================================
 */

#include <iostream>

using namespace std;

int main() {
    float arr[] = {78.5f, 92.0f, 65.4f, 88.2f, 95.5f, 71.0f, 84.6f};
    int n = 7;

    cout << "Original Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";

    // ------------------------------------------------------------------------
    // SELECTION SORT (Ascending order)
    // ------------------------------------------------------------------------
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i; // 1. Assume current position holds the smallest value

        // 2. Scan remaining unsorted array to find the true minimum
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j; // Update index of minimum element
            }
        }

        // 3. Swap the true minimum into position i (Exactly 1 swap per pass!)
        float temp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = temp;
    }

    cout << "Sorted Array  : ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n\n=== TOP 5 HIGHEST SCORES ===\n";

    // ------------------------------------------------------------------------
    // TOP 5 DISPLAY: Read backwards from the end of the ascending array
    // ------------------------------------------------------------------------
    for (int i = 0; i < 5 && i < n; i++) {
        cout << "Rank " << (i + 1) << ": " << arr[n - 1 - i] << "%\n";
    }

    return 0;
}

/**
 * ============================================================================
 * 🎓 EXAMINER VIVA QUESTIONS & INSTANT ANSWERS:
 * Q: How many swaps does Selection Sort perform?
 * A: At most N - 1 swaps in total (exactly 1 swap per outer loop pass).
 *
 * Q: What is the Time Complexity of Selection Sort?
 * A: Always O(N^2) for Best, Average, and Worst cases, because it scans the
 *    entire remaining subarray regardless of initial ordering.
 *
 * Q: Is Selection Sort stable?
 * A: No, it is unstable because long-distance swaps can change the relative
 *    order of duplicate elements.
 * ============================================================================
 */
