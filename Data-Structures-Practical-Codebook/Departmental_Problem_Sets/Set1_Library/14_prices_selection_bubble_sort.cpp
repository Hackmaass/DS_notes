/**
 * ============================================================================
 * SET 1: LIBRARY MANAGEMENT SYSTEM (Sorting Problem 4)
 * SOURCE: Four Alternate Problem Sets Sorting and Searching.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to store book prices in a floating-point array.
 *   a. Selection sort in ascending order
 *   b. Bubble sort in ascending order
 *   c. Display top 5 highest prices
 * ============================================================================
 * ALGORITHM:
 *   1. Selection Sort (Ascending):
 *      - Loop i from 0 to n - 2.
 *      - Find minIndex in arr[i..n-1]. Swap arr[i] with arr[minIndex].
 *   2. Bubble Sort (Ascending with early stop):
 *      - Loop i from 0 to n - 2.
 *      - For j from 0 to n - 2 - i: if arr[j] > arr[j+1], swap(arr[j], arr[j+1]).
 *   3. Top 5 Highest:
 *      - In an ascending array of size n, the 5 highest prices are at indices
 *        (n - 1) down to (n - 5).
 * ============================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

// a. Selection Sort in Ascending Order
void selectionSortAsc(float arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            float temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

// b. Bubble Sort in Ascending Order
void bubbleSortAsc(float arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Print array
void printArray(const float arr[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << "Rs " << fixed << setprecision(2) << arr[i] << "  ";
    }
    cout << "\n";
}

int main() {
    cout << "==============================================================\n";
    cout << "  SET 1 (SORTING PROBLEM 4): BOOK PRICES SELECTION & BUBBLE SORT\n";
    cout << "==============================================================\n";

    const int N = 7;
    float pricesSelection[N] = {650.0f, 420.5f, 890.0f, 310.0f, 740.0f, 950.0f, 520.0f};
    float pricesBubble[N]    = {650.0f, 420.5f, 890.0f, 310.0f, 740.0f, 950.0f, 520.0f};

    cout << "Original Book Prices:\n  ";
    printArray(pricesSelection, N);

    // a. Selection Sort
    selectionSortAsc(pricesSelection, N);
    cout << "\nAscending Prices (Selection Sort):\n  ";
    printArray(pricesSelection, N);

    // b. Bubble Sort
    bubbleSortAsc(pricesBubble, N);
    cout << "\nAscending Prices (Bubble Sort):\n  ";
    printArray(pricesBubble, N);

    // c. Display Top 5 Highest Prices (Last 5 elements of ascending array)
    cout << "\nTop 5 Highest Book Prices in Library:\n";
    int rank = 1;
    for (int i = N - 1; i >= N - 5 && i >= 0; --i) {
        cout << "  Rank #" << rank++ << ": Rs " << fixed << setprecision(2) << pricesBubble[i] << "\n";
    }

    return 0;
}
