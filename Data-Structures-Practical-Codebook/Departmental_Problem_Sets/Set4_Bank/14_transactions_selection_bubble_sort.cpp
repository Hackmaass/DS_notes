/**
 * ============================================================================
 * Departmental Problem Set 4 (Bank) - Problem 14
 * Program: Daily Transactions Selection and Bubble Sort
 * ============================================================================
 * Problem Statement:
 *   Store daily bank transaction amounts (float) of N customers:
 *   - Sort transactions in ascending order using Selection Sort.
 *   - Sort transactions in ascending order using Bubble Sort.
 *   - Display top 5 highest transactions.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

void displayTransactions(const float arr[], int n) {
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

// Selection Sort: Finds minimum element in unsorted portion
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

// Bubble Sort: Swaps adjacent elements if out of order
void bubbleSort(float arr[], int n) {
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

void displayTop5HighestTransactions(const float arr[], int n) {
    int count = (n < 5) ? n : 5;
    cout << "\n=== Top " << count << " Highest Daily Transactions ===\n";
    for (int i = 0; i < count; i++) {
        int idx = n - 1 - i; // Highest values at the end of ascending sorted array
        cout << "  Rank " << (i + 1) << ": Rs. " << fixed << setprecision(2) << arr[idx] << "\n";
    }
}

int main() {
    const int N = 8;
    float originalTransactions[N] = {2500.00f, 48000.50f, 1200.00f, 150000.00f, 8500.25f, 95000.00f, 32000.00f, 210000.75f};

    float txSelection[N];
    float txBubble[N];
    for (int i = 0; i < N; i++) {
        txSelection[i] = originalTransactions[i];
        txBubble[i] = originalTransactions[i];
    }

    cout << "=== Daily Bank Transactions Sorting ===\n\n";

    cout << "Original Unsorted Transaction Amounts:\n  ";
    displayTransactions(originalTransactions, N);

    cout << "\n--- 1. Selection Sort (Ascending Order) ---\n  ";
    selectionSort(txSelection, N);
    displayTransactions(txSelection, N);

    cout << "\n--- 2. Bubble Sort (Ascending Order) ---\n  ";
    bubbleSort(txBubble, N);
    displayTransactions(txBubble, N);

    // Display Top 5 Highest Transactions
    displayTop5HighestTransactions(txSelection, N);

    return 0;
}
