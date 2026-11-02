/**
 * ============================================================================
 * EXAM PROGRAM 04: INSERTION SORT (CARD SHIFTS & COMPARISONS)
 * ============================================================================
 * 🧠 60-SECOND EXAM MEMORIZATION TECHNIQUE:
 * 
 * 1. THE 3-STEP "PLAYING CARDS" FORMULA:
 *    - Pick Card: `key = arr[i];` and `j = i - 1;`
 *    - Shift Bigger Cards Right:
 *        `while (j >= 0 && arr[j] > key) {`
 *            `arr[j + 1] = arr[j];`   // Shift right
 *            `j--;`                   // Move to previous card
 *        `}`
 *    - Drop Card: `arr[j + 1] = key;` (Drop into the opening!)
 * 
 * 2. WHY `arr[j + 1] = key` (NOT `arr[j] = key`)?
 *    Because `j` decremented (`j--`) right before the while loop terminated!
 *    So `j` is now pointing to the card BEFORE the opening.
 *    The opening is at `j + 1`!
 * 
 * 3. THE EXAM PANIC CHECKLIST (The 3 Bugs Examiners Catch):
 *    - TRAP 1: Forgetting `j >= 0`. If you only check `arr[j] > key`, `j` will
 *              become -1, leading to `arr[-1]` which corrupts memory or crashes!
 *    - TRAP 2: Starting outer loop at `i = 0`. An array of 1 element (`arr[0]`)
 *              is already sorted by definition. ALWAYS START AT `i = 1`.
 *    - TRAP 3: Forgetting to track shifts: Put `shifts++` right next to `arr[j + 1] = arr[j]`.
 * 
 * ============================================================================
 * EXPECTED TERMINAL OUTPUT SHOWN TO EXAMINER:
 * 
 * Original Array: 64 25 12 22 11 
 * Sorted Array  : 11 12 22 25 64 
 * Total Comparisons: 10
 * Total Element Shifts: 10
 * ============================================================================
 */

#include <iostream>

using namespace std;

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = 5;
    int shifts = 0, comps = 0;

    cout << "Original Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";

    // ------------------------------------------------------------------------
    // INSERTION SORT (Card-game Shift Mechanism)
    // ------------------------------------------------------------------------
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // The card to be inserted
        int j = i - 1;    // Index of the card to its left

        while (j >= 0) {
            comps++; // Track comparison
            if (arr[j] > key) {
                arr[j + 1] = arr[j]; // Shift larger card one slot to the right
                shifts++;            // Track shift
                j--;                 // Step left
            } else {
                break; // Found correct sorted location!
            }
        }
        arr[j + 1] = key; // Place key into its proper sorted opening
    }

    cout << "Sorted Array  : ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\nTotal Comparisons: " << comps 
         << "\nTotal Element Shifts: " << shifts << "\n";

    return 0;
}

/**
 * ============================================================================
 * 🎓 EXAMINER VIVA QUESTIONS & INSTANT ANSWERS:
 * Q: Why is Insertion Sort called "Adaptive"?
 * A: Because if the input array is already sorted, the `arr[j] > key` condition
 *    fails immediately on every pass. It completes in O(N) time with 0 element shifts.
 *
 * Q: Is Insertion Sort stable?
 * A: Yes, it is stable because it only shifts elements that are strictly greater
 *    than key (`arr[j] > key`), preserving the relative order of duplicate elements.
 *
 * Q: Compare Selection Sort and Insertion Sort:
 * A: Selection Sort minimizes swaps (at most N - 1 swaps). Insertion Sort minimizes
 *    comparisons and time on partially sorted data.
 * ============================================================================
 */
