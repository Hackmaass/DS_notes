/**
 * ============================================================================
 * Departmental Problem Set 2 (Hospital) - Problem 11
 * Program: Patient Severity Score Ranking (Selection & Insertion Sort)
 * ============================================================================
 * Problem Statement:
 *   Manage an array of patient severity scores (1 to 100):
 *   - Sort severity scores in descending order using Selection Sort (highest first).
 *   - Sort using Insertion Sort and count total comparisons and shifts.
 *   - Display top 5 most critical patients.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

struct Patient {
    int id;
    string name;
    int severity; // 1 to 100 (higher = more critical)
};

void displayPatients(const Patient arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "  ID: " << arr[i].id << " | Name: " << arr[i].name 
             << " | Severity Score: " << arr[i].severity << "\n";
    }
}

// Selection Sort: Descending order (Find maximum and place at front)
void selectionSortDescending(Patient arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].severity > arr[maxIdx].severity) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            Patient temp = arr[i];
            arr[i] = arr[maxIdx];
            arr[maxIdx] = temp;
        }
    }
}

// Insertion Sort: Descending order (Tracks comparisons and shifts)
void insertionSortDescending(Patient arr[], int n, int& comparisons, int& shifts) {
    comparisons = 0;
    shifts = 0;

    for (int i = 1; i < n; i++) {
        Patient key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            comparisons++;
            if (arr[j].severity < key.severity) { // For descending, shift smaller items right
                arr[j + 1] = arr[j];
                shifts++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

void displayTop5Critical(const Patient arr[], int n) {
    int limit = (n < 5) ? n : 5;
    cout << "\n=== Top " << limit << " Most Critical Patients (Emergency Priority) ===\n";
    for (int i = 0; i < limit; i++) {
        cout << "  Rank " << (i + 1) << ": " << arr[i].name 
             << " (ID: " << arr[i].id << ") - Severity: " << arr[i].severity << "/100\n";
    }
}

int main() {
    const int N = 7;
    Patient original[N] = {
        {101, "Alice Green",  45},
        {102, "Bob White",    88},
        {103, "Charlie Blue", 62},
        {104, "David Brown",  95},
        {105, "Emma Davis",   30},
        {106, "Frank Miller", 91},
        {107, "Grace Hall",   74}
    };

    Patient arrSelection[N];
    Patient arrInsertion[N];
    for (int i = 0; i < N; i++) {
        arrSelection[i] = original[i];
        arrInsertion[i] = original[i];
    }

    cout << "=== Initial Patient Records ===\n";
    displayPatients(original, N);

    cout << "\n--- 1. Selection Sort (Descending by Severity) ---\n";
    selectionSortDescending(arrSelection, N);
    displayPatients(arrSelection, N);

    cout << "\n--- 2. Insertion Sort (Descending by Severity) ---\n";
    int comparisons = 0, shifts = 0;
    insertionSortDescending(arrInsertion, N, comparisons, shifts);
    displayPatients(arrInsertion, N);
    cout << "  Insertion Sort Metrics: Comparisons = " << comparisons 
         << ", Shifts = " << shifts << "\n";

    // Display Top 5 Most Critical
    displayTop5Critical(arrSelection, N);

    return 0;
}
