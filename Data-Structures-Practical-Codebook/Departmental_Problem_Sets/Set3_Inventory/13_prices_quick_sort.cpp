/**
 * ============================================================================
 * Departmental Problem Set 3 (Inventory) - Problem 13
 * Program: Product Unit Prices Quick Sort
 * ============================================================================
 * Problem Statement:
 *   Store unit prices (float) of N products:
 *   - Sort prices in ascending order using Quick Sort (Lomuto partition).
 *   - Display prices before and after sorting.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

void displayPrices(const float arr[], int n) {
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

// Lomuto Partition Scheme
int partition(float arr[], int low, int high) {
    float pivot = arr[high]; // Last element as pivot
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

        quickSort(arr, low, pi - 1);  // Sort left half
        quickSort(arr, pi + 1, high); // Sort right half
    }
}

int main() {
    const int N = 8;
    float unitPrices[N] = {1299.50f, 499.00f, 3499.00f, 150.00f, 850.75f, 5499.00f, 299.00f, 1899.25f};

    cout << "=== Product Unit Prices Quick Sort ===\n\n";

    cout << "Original Unsorted Unit Prices:\n  ";
    displayPrices(unitPrices, N);

    quickSort(unitPrices, 0, N - 1);

    cout << "\nSorted Unit Prices (Ascending Order - Quick Sort):\n  ";
    displayPrices(unitPrices, N);

    cout << "\nPricing Range Summary:\n";
    cout << "  Most Affordable Item: Rs. " << fixed << setprecision(2) << unitPrices[0] << "\n";
    cout << "  Most Premium Item   : Rs. " << fixed << setprecision(2) << unitPrices[N - 1] << "\n";

    return 0;
}
