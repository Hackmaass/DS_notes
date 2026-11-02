/**
 * ============================================================================
 * Departmental Problem Set 2 (Hospital) - Problem 14
 * Program: Hospital Bills Selection and Bubble Sort
 * ============================================================================
 * Problem Statement:
 *   Store hospital bill amounts (float) of N patients:
 *   - Sort bills in ascending order using Selection Sort.
 *   - Sort bills in ascending order using Bubble Sort.
 *   - Display top 5 highest bills.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

void displayBills(const float arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(2) << "Rs." << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]\n";
}

void swapElements(float& a, float& b) {
    float temp = a;
    a = b;
    b = temp;
}

// Selection Sort: Repeatedly finds minimum element from unsorted part
void selectionSort(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swapElements(arr[i], arr[minIdx]);
        }
    }
}

// Bubble Sort: Repeatedly steps through list, swaps adjacent elements if out of order
void bubbleSort(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swapElements(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Optimization: early exit if already sorted
    }
}

// Display top 5 highest bills from sorted array (highest will be at the end)
void displayTop5Highest(const float arr[], int n) {
    int count = (n < 5) ? n : 5;
    cout << "\n=== Top " << count << " Highest Hospital Bills ===\n";
    for (int i = 0; i < count; i++) {
        // Since array is sorted in ascending order, highest values are from index n-1 backwards
        int idx = n - 1 - i;
        cout << "  Rank " << (i + 1) << ": Rs. " << fixed << setprecision(2) << arr[idx] << "\n";
    }
}

int main() {
    const int N = 8;
    float original[N] = {15200.50f, 4350.00f, 89200.75f, 12400.00f, 65000.25f, 3100.00f, 47800.00f, 95400.50f};

    float billsSelection[N];
    float billsBubble[N];
    for (int i = 0; i < N; i++) {
        billsSelection[i] = original[i];
        billsBubble[i] = original[i];
    }

    cout << "=== Hospital Patient Bills Sorting ===\n\n";

    cout << "Original Unsorted Bills:\n  ";
    displayBills(original, N);

    cout << "\n--- 1. Selection Sort (Ascending Order) ---\n  ";
    selectionSort(billsSelection, N);
    displayBills(billsSelection, N);

    cout << "\n--- 2. Bubble Sort (Ascending Order) ---\n  ";
    bubbleSort(billsBubble, N);
    displayBills(billsBubble, N);

    // Display Top 5 Highest Bills
    displayTop5Highest(billsSelection, N);

    return 0;
}
