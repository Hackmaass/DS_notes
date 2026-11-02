/**
 * ============================================================================
 * Departmental Problem Set 4 (Bank) - Problem 13
 * Program: Loan Interest Rates Quick Sort
 * ============================================================================
 * Problem Statement:
 *   Store annual loan interest rates (float in %) of N loan schemes:
 *   - Sort interest rates in ascending order using Quick Sort (Lomuto partition).
 *   - Display interest rates before and after sorting.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

void displayRates(const float arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(2) << arr[i] << "%";
        if (i < n - 1) cout << ", ";
    }
    cout << "]\n";
}

void swapElements(float& a, float& b) {
    float temp = a;
    a = b;
    b = temp;
}

// Lomuto Partition Scheme
int partition(float arr[], int low, int high) {
    float pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swapElements(arr[i], arr[j]);
        }
    }
    swapElements(arr[i + 1], arr[high]);
    return i + 1;
}

// Recursive Quick Sort
void quickSort(float arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    const int N = 8;
    float interestRates[N] = {8.50f, 11.25f, 6.75f, 9.40f, 7.90f, 13.50f, 7.20f, 10.00f};

    cout << "=== Loan Scheme Interest Rates Quick Sort ===\n\n";

    cout << "Original Unsorted Loan Interest Rates:\n  ";
    displayRates(interestRates, N);

    quickSort(interestRates, 0, N - 1);

    cout << "\nSorted Loan Interest Rates (Ascending Order - Quick Sort):\n  ";
    displayRates(interestRates, N);

    cout << "\nInterest Rate Spread:\n";
    cout << "  Lowest Rate (e.g. Prime Home Loan): " << fixed << setprecision(2) << interestRates[0] << "%\n";
    cout << "  Highest Rate (e.g. Personal Unsecured Loan): " << fixed << setprecision(2) << interestRates[N - 1] << "%\n";

    return 0;
}
