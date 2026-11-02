/**
 * ============================================================================
 * Departmental Problem Set 2 (Hospital) - Problem 13
 * Program: Patient Body Temperatures Quick Sort
 * ============================================================================
 * Problem Statement:
 *   Store body temperatures (float in °F) of N patients:
 *   - Sort temperatures in ascending order using Quick Sort (Lomuto partition).
 *   - Display temperatures before and after sorting.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

void displayTemperatures(const float arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(1) << arr[i] << "°F";
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
// Chooses the last element as pivot, places smaller elements to left
int partition(float arr[], int low, int high) {
    float pivot = arr[high];
    int i = low - 1; // Index of smaller element

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swapElements(arr[i], arr[j]);
        }
    }
    // Place pivot in correct sorted position
    swapElements(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort recursive routine
void quickSort(float arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);  // Recursively sort left of pivot
        quickSort(arr, pi + 1, high); // Recursively sort right of pivot
    }
}

int main() {
    const int N = 8;
    float temperatures[N] = {98.6f, 102.4f, 97.8f, 101.1f, 99.0f, 103.5f, 98.2f, 100.4f};

    cout << "=== Hospital Patient Temperatures Quick Sort ===\n\n";

    cout << "Original Recorded Temperatures:\n  ";
    displayTemperatures(temperatures, N);

    quickSort(temperatures, 0, N - 1);

    cout << "\nSorted Temperatures (Ascending Order - Quick Sort):\n  ";
    displayTemperatures(temperatures, N);

    cout << "\nClinical Observation Summary:\n";
    cout << "  Lowest Temperature (Hypothermia risk): " << temperatures[0] << "°F\n";
    cout << "  Highest Temperature (High Fever):      " << temperatures[N - 1] << "°F\n";

    return 0;
}
