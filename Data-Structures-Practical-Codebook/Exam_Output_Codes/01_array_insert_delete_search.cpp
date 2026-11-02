/**
 * ============================================================================
 * EXAM PROGRAM 01: ARRAY (INSERT, DELETE, SEARCH, DISPLAY)
 * ============================================================================
 * 📝 STEP-BY-STEP ALGORITHMS (Copy these directly onto your exam answer sheet!):
 * 
 * ALGORITHM 1: INSERTION AT INDEX `k`
 *   Step 1: Start.
 *   Step 2: Check for overflow: If size >= MAX_CAPACITY, report error and exit.
 *   Step 3: Check boundary: If index `k` < 0 or `k` > size, report invalid index and exit.
 *   Step 4: Shift elements rightwards: Loop `i` from `size - 1` down to `k`:
 *             `arr[i + 1] = arr[i]`
 *   Step 5: Insert new element: `arr[k] = value`.
 *   Step 6: Increment size: `size = size + 1`.
 *   Step 7: Stop.
 * 
 * ALGORITHM 2: LINEAR SEARCH FOR `target`
 *   Step 1: Start.
 *   Step 2: Initialize `foundIndex = -1`.
 *   Step 3: Loop `i` from 0 to `size - 1`:
 *             If `arr[i] == target`:
 *               Set `foundIndex = i`, break loop.
 *   Step 4: If `foundIndex != -1`, report element found at `foundIndex`.
 *           Else, report element not found.
 *   Step 5: Stop.
 * 
 * ALGORITHM 3: DELETION AT INDEX `k`
 *   Step 1: Start.
 *   Step 2: Check for underflow: If size == 0, report empty array and exit.
 *   Step 3: Check boundary: If index `k` < 0 or `k` >= size, report invalid index and exit.
 *   Step 4: Shift elements leftwards: Loop `i` from `k` up to `size - 2`:
 *             `arr[i] = arr[i + 1]`
 *   Step 5: Decrement size: `size = size - 1`.
 *   Step 6: Stop.
 * 
 * ============================================================================
 * 🧠 60-SECOND EXAM MEMORIZATION TECHNIQUE:
 * 
 * 1. THE 3-WORD MNEMONIC FOR INSERTION: "TAIL SHIFTS RIGHT"
 *    - Start: `i = n - 1` (at the very tail)
 *    - Move:  `i >= insIdx` (backwards towards the target)
 *    - Shift: `arr[i + 1] = arr[i]` (push each number right into empty space)
 *    - Drop:  `arr[insIdx] = val`
 *    - Bump:  `n++`
 * 
 * 2. THE 3-WORD MNEMONIC FOR DELETION: "HOLE PULLS LEFT"
 *    - Start: `i = delIdx` (right at the hole you want to delete)
 *    - Move:  `i < n - 1` (forward towards the end)
 *    - Pull:  `arr[i] = arr[i + 1]` (pull right neighbor into current hole)
 *    - Drop:  `n--`
 * 
 * 3. THE EXAM PANIC CHECKLIST (The 3 Bugs Examiners Catch):
 *    - TRAP 1: Forgetting `n++` or `n--`. If you forget this, the array size
 *              never changes, and your display will look broken!
 *    - TRAP 2: In insertion, writing `i = insIdx` to `n - 1`. That overwrites
 *              all your data! Remember: INSERTION LOOPS BACKWARDS (`i--`).
 *    - TRAP 3: In deletion, writing `i < n`. That causes `arr[n - 1] = arr[n]`,
 *              which pulls uninitialized garbage into your array! Stop at `n - 1`.
 * 
 * ============================================================================
 * EXPECTED TERMINAL OUTPUT SHOWN TO EXAMINER:
 * 
 * Initial Array: 10 20 30 40 
 * After Insert 25 at index 2: 10 20 25 30 40 
 * Search 30: Found at index 3
 * After Delete at index 1: 10 25 30 40 
 * ============================================================================
 */

#include <iostream>

using namespace std;

// Display helper: prints all elements separated by a space
void display(int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";
}

int main() {
    // Capacity = 10, but logical size n = 4 active elements
    int arr[10] = {10, 20, 30, 40}, n = 4;

    cout << "Initial Array: ";
    display(arr, n);

    // ------------------------------------------------------------------------
    // 1. INSERTION (Target: Place value 25 at index 2)
    // ------------------------------------------------------------------------
    int insIdx = 2, val = 25;

    // STEP A: Shift right from the tail (n - 1 down to insIdx)
    for (int i = n - 1; i >= insIdx; i--) {
        arr[i + 1] = arr[i]; // Copy element into its right neighbor slot
    }
    // STEP B: Place new value into the cleared slot
    arr[insIdx] = val;
    // STEP C: Expand size
    n++;

    cout << "After Insert 25 at index 2: ";
    display(arr, n);

    // ------------------------------------------------------------------------
    // 2. LINEAR SEARCH (Target: Find index of value 30)
    // ------------------------------------------------------------------------
    int target = 30, foundIdx = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            foundIdx = i; // Save matching index
            break;        // Stop searching immediately
        }
    }
    cout << "Search " << target << ": Found at index " << foundIdx << "\n";

    // ------------------------------------------------------------------------
    // 3. DELETION (Target: Remove element at index 1, which is value 20)
    // ------------------------------------------------------------------------
    int delIdx = 1;

    // STEP A: Shift left to overwrite the hole (delIdx up to n - 2)
    for (int i = delIdx; i < n - 1; i++) {
        arr[i] = arr[i + 1]; // Pull right neighbor leftwards
    }
    // STEP B: Shrink size
    n--;

    cout << "After Delete at index 1: ";
    display(arr, n);

    return 0;
}

/**
 * ============================================================================
 * 🎓 EXAMINER VIVA QUESTIONS & INSTANT ANSWERS:
 * Q: Why do you loop backwards (i = n - 1 down to insIdx) for insertion?
 * A: Because shifting from left to right would overwrite and erase elements 
 *    before they are copied. Shifting from the tail moves items into empty slots.
 *
 * Q: What is the Time Complexity of insertion and deletion?
 * A: O(N) worst-case (at index 0, all elements shift) and O(1) best-case (at the end).
 * ============================================================================
 */
