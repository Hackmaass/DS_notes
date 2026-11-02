/**
 * ============================================================================
 * Departmental Problem Set 3 (Inventory) - Problem 14
 * Program: Stock Quantities Selection and Bubble Sort
 * ============================================================================
 * Problem Statement:
 *   Store stock inventory quantities of N products:
 *   - Sort quantities in ascending order using Selection Sort.
 *   - Sort quantities in ascending order using Bubble Sort.
 *   - Display top 5 products with highest stock quantities.
 * ============================================================================
 */

#include <iostream>

using namespace std;

void displayQuantities(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " units";
        if (i < n - 1) cout << ", ";
    }
    cout << "]\n";
}

void swapElements(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Selection Sort: Finds minimum element in unsorted portion
void selectionSort(int arr[], int n) {
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

// Bubble Sort: Swaps adjacent elements if out of order
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swapElements(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void displayTop5HighestStock(const int arr[], int n) {
    int count = (n < 5) ? n : 5;
    cout << "\n=== Top " << count << " Highest Stock Quantities (Surplus Inventory) ===\n";
    for (int i = 0; i < count; i++) {
        int idx = n - 1 - i; // Elements at end of ascending sorted array
        cout << "  Rank " << (i + 1) << ": " << arr[idx] << " units in warehouse\n";
    }
}

int main() {
    const int N = 8;
    int originalStock[N] = {120, 45, 890, 310, 65, 1450, 240, 780};

    int stockSelection[N];
    int stockBubble[N];
    for (int i = 0; i < N; i++) {
        stockSelection[i] = originalStock[i];
        stockBubble[i] = originalStock[i];
    }

    cout << "=== Inventory Stock Quantities Sorting ===\n\n";

    cout << "Original Unsorted Stock Quantities:\n  ";
    displayQuantities(originalStock, N);

    cout << "\n--- 1. Selection Sort (Ascending Order) ---\n  ";
    selectionSort(stockSelection, N);
    displayQuantities(stockSelection, N);

    cout << "\n--- 2. Bubble Sort (Ascending Order) ---\n  ";
    bubbleSort(stockBubble, N);
    displayQuantities(stockBubble, N);

    // Display Top 5 Highest Stock Quantities
    displayTop5HighestStock(stockSelection, N);

    return 0;
}
