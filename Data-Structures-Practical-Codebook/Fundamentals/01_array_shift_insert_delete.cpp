/**
 * ============================================================================
 * FUNDAMENTAL 01: ARRAY SHIFTING (INSERTION & DELETION)
 * ============================================================================
 * 👨‍🏫 PROFESSOR'S DEEP-DIVE CONCEPTUAL GUIDE:
 * 
 * 1. WHAT IS AN ARRAY IN MEMORY?
 *    An array is a contiguous block of physical RAM. If element 0 is at memory
 *    address 1000, and an integer is 4 bytes, then:
 *      - arr[0] is at 1000
 *      - arr[1] is at 1004
 *      - arr[2] is at 1008
 *    Because the addresses are glued together, you CANNOT simply "slide" a new
 *    number in without moving the existing neighbors!
 *
 * 2. THE INSERTION PROBLEM (SHIFT RIGHT / BACKWARDS):
 *    Suppose we have [ 10, 20, 30, 40 ] (size = 4, capacity = 10).
 *    We want to insert 25 at index 2 (between 20 and 30).
 *
 *    Initial State:
 *    Index:   0    1    2    3    4    5
 *    Value: [10] [20] [30] [40] [  ] [  ]
 *                       ^
 *                  Target index 2
 *
 *    Step 1: Move arr[3] (40) into arr[4].
 *            [10] [20] [30] [40] [40]
 *    Step 2: Move arr[2] (30) into arr[3].
 *            [10] [20] [30] [30] [40]
 *    Step 3: Now index 2 is safe to overwrite with 25!
 *            [10] [20] [25] [30] [40]
 *    Step 4: Update size from 4 to 5.
 *
 *    CRITICAL EXAM QUESTION: "Why loop BACKWARDS (from size-1 down to index)?"
 *    ANSWER: If you loop forwards (index up to size-1):
 *      - arr[3] = arr[2] (40 becomes 30) -> you just DESTROYED 40 forever!
 *      Shifting from the tail creates a domino effect into empty space.
 *
 * 3. THE DELETION PROBLEM (SHIFT LEFT / FORWARDS):
 *    Suppose we want to delete index 1 (value 20) from [ 10, 20, 25, 30, 40 ].
 *    To maintain contiguous order with NO gaps:
 *    Step 1: Overwrite index 1 with index 2 (25 pulls left into 20's spot).
 *    Step 2: Overwrite index 2 with index 3 (30 pulls left into 25's old spot).
 *    Step 3: Overwrite index 3 with index 4 (40 pulls left into 30's old spot).
 *    Step 4: Decrement size from 5 to 4.
 *
 *    CRITICAL EXAM QUESTION: "Why loop FORWARDS (from index up to size-2)?"
 *    ANSWER: Because the gap starts at `index`. We must pull each right neighbor
 *    leftwards to fill the hole immediately.
 * ============================================================================
 */

#include <iostream>

using namespace std;

// Maximum physical capacity allocated in memory
const int MAX_CAPACITY = 10;

/**
 * Helper function: Displays both indices and values in an ASCII diagram
 */
void displayArray(const int arr[], int size) {
    cout << "  Indices: ";
    for (int i = 0; i < size; i++) cout << " [" << i << "] ";
    cout << "\n  Values : ";
    for (int i = 0; i < size; i++) cout << "  " << arr[i] << "  ";
    cout << " (Current size: " << size << ")\n\n";
}

/**
 * ----------------------------------------------------------------------------
 * OPERATION 1: INSERT AT SPECIFIC INDEX
 * ----------------------------------------------------------------------------
 * @param arr[] : The array passed as a pointer (decays to int*)
 * @param &size : Pass-by-reference! Allows us to update the caller's size.
 * @param index : The exact slot where new value should reside (0 to size)
 * @param value : The integer number to insert
 * @return bool : true if successful, false if capacity full or invalid index
 */
bool insertAt(int arr[], int &size, int index, int value) {
    // ------------------------------------------------------------------------
    // GUARD CHECK 1: Overflow (Is physical array already completely full?)
    // ------------------------------------------------------------------------
    if (size >= MAX_CAPACITY) {
        cout << "  [ERROR] Array Overflow! Maximum capacity (" 
             << MAX_CAPACITY << ") reached.\n";
        return false;
    }

    // ------------------------------------------------------------------------
    // GUARD CHECK 2: Range Validity
    // Valid positions are:
    //   - index = 0 (insert at beginning)
    //   - index = size (insert at end / append)
    // Anything outside [0, size] is out of bounds.
    // ------------------------------------------------------------------------
    if (index < 0 || index > size) {
        cout << "  [ERROR] Invalid index " << index 
             << "! Must be between 0 and " << size << ".\n";
        return false;
    }

    // ------------------------------------------------------------------------
    // THE SHIFTING LOOP (Core Algorithm):
    // Start at the last valid element: `i = size - 1`
    // Stop after shifting the element at target index: `i >= index`
    // Move backwards towards the insertion point: `i--`
    // ------------------------------------------------------------------------
    for (int i = size - 1; i >= index; i--) {
        // Copy each element one position to its right
        arr[i + 1] = arr[i];
    }

    // ------------------------------------------------------------------------
    // PLACEMENT: Slot `arr[index]` is now free and safe to overwrite!
    // ------------------------------------------------------------------------
    arr[index] = value;

    // ------------------------------------------------------------------------
    // SIZE UPDATE: Logical count expands by 1
    // (Because `size` was passed by reference `&`, `main()` sees this update!)
    // ------------------------------------------------------------------------
    size++;
    return true;
}

/**
 * ----------------------------------------------------------------------------
 * OPERATION 2: DELETE AT SPECIFIC INDEX
 * ----------------------------------------------------------------------------
 * @param arr[] : The target array
 * @param &size : Pass-by-reference to decrement caller's count
 * @param index : The slot to remove (0 to size - 1)
 * @return bool : true if deleted, false if array empty or index invalid
 */
bool deleteAt(int arr[], int &size, int index) {
    // ------------------------------------------------------------------------
    // GUARD CHECK 1: Underflow (Is there anything to delete?)
    // ------------------------------------------------------------------------
    if (size == 0) {
        cout << "  [ERROR] Array Underflow! Array is already empty.\n";
        return false;
    }

    // ------------------------------------------------------------------------
    // GUARD CHECK 2: Range Validity
    // For deletion, valid indices are strictly [0, size - 1].
    // Note: index = size is NOT valid because nothing exists there!
    // ------------------------------------------------------------------------
    if (index < 0 || index >= size) {
        cout << "  [ERROR] Invalid index " << index 
             << "! Must be between 0 and " << (size - 1) << ".\n";
        return false;
    }

    int removedValue = arr[index];

    // ------------------------------------------------------------------------
    // THE SHIFTING LOOP (Core Algorithm):
    // Start at the gap: `i = index`
    // Stop at the second-to-last item: `i < size - 1`
    // Move forwards pulling right neighbors left: `i++`
    // ------------------------------------------------------------------------
    for (int i = index; i < size - 1; i++) {
        // Overwrite current slot with the element immediately to its right
        arr[i] = arr[i + 1];
    }

    // ------------------------------------------------------------------------
    // SIZE UPDATE: Logical count contracts by 1
    // Note: The physical memory still holds the old data at the end, but because
    // `size` is smaller, that slot is officially ignored as "garbage".
    // ------------------------------------------------------------------------
    size--;
    cout << "  [SUCCESS] Deleted value " << removedValue << " from index " << index << ".\n";
    return true;
}

int main() {
    cout << "========================================================\n";
    cout << "  TEACHER DEMO: ARRAY INSERTION & DELETION MECHANICS\n";
    cout << "========================================================\n\n";

    int numbers[MAX_CAPACITY] = {10, 20, 30, 40};
    int size = 4; // We currently have 4 active elements

    cout << "1. INITIAL ARRAY STATE:\n";
    displayArray(numbers, size);

    // TEST CASE 1: Insert in the middle
    cout << "--------------------------------------------------------\n";
    cout << "2. INSERT VALUE 25 AT INDEX 2 (Between 20 and 30):\n";
    cout << "   -> Shifting 40 from [3] to [4]\n";
    cout << "   -> Shifting 30 from [2] to [3]\n";
    cout << "   -> Inserting 25 into vacated slot [2]\n";
    insertAt(numbers, size, 2, 25);
    displayArray(numbers, size);

    // TEST CASE 2: Insert at front (Worst-case shift: all N elements shift)
    cout << "--------------------------------------------------------\n";
    cout << "3. INSERT VALUE 5 AT FRONT (INDEX 0):\n";
    cout << "   -> Every single element shifts right by 1!\n";
    insertAt(numbers, size, 0, 5);
    displayArray(numbers, size);

    // TEST CASE 3: Delete from middle
    cout << "--------------------------------------------------------\n";
    cout << "4. DELETE ELEMENT AT INDEX 2 (Removes value 20):\n";
    cout << "   -> Overwriting [2] with [3] (25 pulls left)\n";
    cout << "   -> Overwriting [3] with [4] (30 pulls left)\n";
    cout << "   -> Overwriting [4] with [5] (40 pulls left)\n";
    deleteAt(numbers, size, 2);
    displayArray(numbers, size);

    // TEST CASE 4: Delete from front (Worst-case shift)
    cout << "--------------------------------------------------------\n";
    cout << "5. DELETE ELEMENT AT FRONT (INDEX 0 - Removes value 5):\n";
    deleteAt(numbers, size, 0);
    displayArray(numbers, size);

    return 0;
}

/**
 * ============================================================================
 * 🎓 VIVA QUESTIONS & ANSWERS FOR THIS CODE:
 * ============================================================================
 * Q1: What is the Time Complexity of Array Insertion & Deletion?
 * A1: - Best Case: O(1) when inserting or deleting at the end (`index = size`).
 *       No shifting is required!
 *     - Worst Case: O(N) when inserting or deleting at the beginning (`index = 0`).
 *       All N elements must be shifted.
 *     - Average Case: O(N) because on average, N/2 elements are shifted.
 *
 * Q2: What is the Auxiliary Space Complexity?
 * A2: O(1) Auxiliary Space. We perform the shifting in-place inside the existing
 *     array without allocating any extra data structures.
 *
 * Q3: Why is `size` passed as `int &size` instead of `int size`?
 * A3: In C++, primitives are passed by value (copy) by default. If we passed
 *     `int size`, the function would increment its own local copy, leaving the
 *     variable in `main()` unchanged. Passing by reference (`&`) ensures changes
 *     persist across function calls.
 * ============================================================================
 */
