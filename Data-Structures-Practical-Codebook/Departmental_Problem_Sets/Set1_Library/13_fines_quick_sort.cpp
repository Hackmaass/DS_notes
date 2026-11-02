/**
 * ============================================================================
 * SET 1: LIBRARY MANAGEMENT SYSTEM (Sorting Problem 3)
 * SOURCE: Four Alternate Problem Sets Sorting and Searching.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to arrange fine amounts collected using Quick Sort.
 *   a. Partition list (Lomuto partition)
 *   b. Recursive Quick Sort
 *   c. Display sorted fines
 * ============================================================================
 * ALGORITHM:
 *   1. Partition(arr, low, high):
 *      - Choose pivot = arr[high].
 *      - Pointer i = low - 1.
 *      - For j = low to high - 1:
 *        if arr[j] <= pivot, increment i and swap(arr[i], arr[j]).
 *      - Swap(arr[i + 1], arr[high]).
 *      - Return partition index (i + 1).
 *   2. QuickSort(arr, low, high):
 *      - If low < high:
 *        pi = Partition(arr, low, high).
 *        QuickSort(arr, low, pi - 1).
 *        QuickSort(arr, pi + 1, high).
 *   3. Display:
 *      - Print formatted sorted fine amounts.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

// a. Partition Function (Lomuto Partition Scheme)
int partition(float arr[], int low, int high) {
    float pivot = arr[high]; // Last element as pivot
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            // Swap arr[i] and arr[j]
            float temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Place pivot in its correct sorted position
    float temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

// b. Recursive Quick Sort Function
void quickSort(float arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Recursively sort left and right subarrays
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// c. Display Function
void displayFines(const float arr[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << "Rs " << fixed << setprecision(2) << arr[i];
        if (i < n - 1) cout << "  |  ";
    }
    cout << "\n";
}

int main() {
    cout << "==============================================================\n";
    cout << "  SET 1 (SORTING PROBLEM 3): QUICK SORT ON LATE FINES\n";
    cout << "==============================================================\n";

    const int N = 6;
    float fines[N] = {45.50f, 120.00f, 15.00f, 85.50f, 250.00f, 30.00f};

    cout << "Unsorted Late Fine Amounts:\n  ";
    displayFines(fines, N);

    // Perform Quick Sort
    quickSort(fines, 0, N - 1);

    cout << "\nSorted Late Fine Amounts (Ascending Order):\n  ";
    displayFines(fines, N);

    return 0;
}
