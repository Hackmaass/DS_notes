/**
 * ============================================================================
 * Departmental Problem Set 2 (Hospital) - Problem 12
 * Program: Patient Record Search (Linear Search vs Binary Search)
 * ============================================================================
 * Problem Statement:
 *   Store an array of patient records (Patient ID, Name, Disease):
 *   - Implement Linear Search to find a patient by Name.
 *   - Implement Binary Search to find a patient by Patient ID (on sorted array).
 *   - Display comparison counts for both search methods.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

struct PatientRecord {
    int patientId;
    string name;
    string disease;
};

void displayRecords(const PatientRecord arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "  [" << i << "] ID: " << arr[i].patientId 
             << " | Name: " << arr[i].name 
             << " | Diagnosis: " << arr[i].disease << "\n";
    }
}

// Linear Search by Patient Name
int linearSearchByName(const PatientRecord arr[], int n, const string& targetName, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        if (arr[i].name == targetName) {
            return i; // Found at index i
        }
    }
    return -1; // Not found
}

// Binary Search by Patient ID (Assumes arr is sorted by patientId)
int binarySearchById(const PatientRecord arr[], int n, int targetId, int& comparisons) {
    comparisons = 0;
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;

        if (arr[mid].patientId == targetId) {
            return mid; // Found at index mid
        } else if (arr[mid].patientId < targetId) {
            low = mid + 1; // Search right half
        } else {
            high = mid - 1; // Search left half
        }
    }
    return -1; // Not found
}

int main() {
    const int N = 6;
    // Sorted by Patient ID for Binary Search compatibility
    PatientRecord database[N] = {
        {101, "Alice Green",  "Hypertension"},
        {104, "Bob White",    "Type 2 Diabetes"},
        {108, "Charlie Blue", "Asthma"},
        {112, "Diana Prince", "Pneumonia"},
        {115, "Edward Norton","Arthritis"},
        {120, "Fiona Hill",   "Migraine"}
    };

    cout << "=== Hospital Patient Records Database ===\n";
    displayRecords(database, N);

    cout << "\n--- 1. Linear Search by Name ---\n";
    string searchName = "Diana Prince";
    int linearComparisons = 0;
    int indexName = linearSearchByName(database, N, searchName, linearComparisons);

    if (indexName != -1) {
        cout << "  Found '" << searchName << "' at index " << indexName << ".\n";
        cout << "  Diagnosis: " << database[indexName].disease << "\n";
    } else {
        cout << "  Patient '" << searchName << "' not found.\n";
    }
    cout << "  Linear Search Total Comparisons: " << linearComparisons << " (O(N) time)\n";

    cout << "\n--- 2. Binary Search by Patient ID ---\n";
    int searchId = 115;
    int binaryComparisons = 0;
    int indexId = binarySearchById(database, N, searchId, binaryComparisons);

    if (indexId != -1) {
        cout << "  Found Patient ID " << searchId << " at index " << indexId << ".\n";
        cout << "  Name: " << database[indexId].name 
             << " | Diagnosis: " << database[indexId].disease << "\n";
    } else {
        cout << "  Patient ID " << searchId << " not found in database.\n";
    }
    cout << "  Binary Search Total Comparisons: " << binaryComparisons << " (O(log N) time)\n";

    return 0;
}
