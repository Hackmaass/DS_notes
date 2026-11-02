/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit II: Searching & Sorting
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 2 - Hospital Management System (Searching & Sorting Suite)
 * TITLE:         Hospital System: Severity Ranking, Patient Search, Quick & Bubble Sort
 * 
 * PROBLEMS COVERED:
 *   1. Priority list of patients based on severity score (Selection & Insertion Sort, Top 5).
 *   2. Search patient records: Linear Search by Name vs Binary Search by Patient ID.
 *   3. Arrange patient temperatures using Quick Sort.
 *   4. Hospital bill amounts: Selection & Bubble Sort. Top 5 highest bills.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// PROBLEM 1: SEVERITY SCORE RANKING
struct PatientSeverity {
    int patientId;
    string name;
    int severityScore; // Higher score = More critical
};

void selectionSortPatientsDesc(PatientSeverity arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int maxIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j].severityScore > arr[maxIdx].severityScore) maxIdx = j;
        }
        if (maxIdx != i) {
            PatientSeverity temp = arr[i];
            arr[i] = arr[maxIdx];
            arr[maxIdx] = temp;
        }
    }
}

int insertionSortPatientsDesc(PatientSeverity arr[], int n) {
    int shifts = 0;
    for (int i = 1; i < n; ++i) {
        PatientSeverity key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].severityScore < key.severityScore) {
            arr[j + 1] = arr[j];
            shifts++;
            j--;
        }
        arr[j + 1] = key;
    }
    return shifts;
}

// PROBLEM 2: SEARCH PATIENT
struct PatientSearchRecord {
    int patientId;
    string name;
    string disease;
};

int linearSearchByName(const PatientSearchRecord arr[], int n, const string& target, int& comps) {
    comps = 0;
    for (int i = 0; i < n; ++i) {
        comps++;
        if (arr[i].name == target) return i;
    }
    return -1;
}

int binarySearchByPatientId(const PatientSearchRecord arr[], int n, int id, int& comps) {
    comps = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        comps++;
        int mid = low + (high - low) / 2;
        if (arr[mid].patientId == id) return mid;
        if (arr[mid].patientId < id) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// PROBLEM 3: QUICK SORT TEMPERATURES
int partitionTemps(float arr[], int low, int high) {
    float pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            float temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    float temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSortTemps(float arr[], int low, int high) {
    if (low < high) {
        int pi = partitionTemps(arr, low, high);
        quickSortTemps(arr, low, pi - 1);
        quickSortTemps(arr, pi + 1, high);
    }
}

// PROBLEM 4: HOSPITAL BILLS BUBBLE SORT
void bubbleSortBillsAsc(float arr[], int n) {
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

int main() {
    cout << "====================================================================\n";
    cout << "  SET 2: HOSPITAL MANAGEMENT SYSTEM - SEARCHING & SORTING SUITE\n";
    cout << "====================================================================\n";

    // 1. Severity Ranking
    PatientSeverity patients[6] = {
        {201, "Ramesh Shinde", 78},
        {202, "Sunita Rao   ", 95},
        {203, "Vijay Kulkarni", 64},
        {204, "Aarti Patil  ", 88},
        {205, "Deepak Joshi ", 92},
        {206, "Pooja Verma  ", 55}
    };
    PatientSeverity copyP[6];
    for (int i = 0; i < 6; ++i) copyP[i] = patients[i];

    selectionSortPatientsDesc(patients, 6);
    cout << "\n>>> TOP 5 CRITICAL PATIENTS (By Severity Score) <<<\n";
    for (int i = 0; i < 5; ++i) {
        cout << "  #" << (i + 1) << " Patient ID: " << patients[i].patientId 
             << " | Name: " << patients[i].name 
             << " | Severity Score: " << patients[i].severityScore << " / 100\n";
    }

    int shifts = insertionSortPatientsDesc(copyP, 6);
    cout << "Insertion Sort executed with " << shifts << " data shifts.\n";

    // 2. Search
    PatientSearchRecord registry[5] = {
        {101, "Aarav Sharma", "Dengue"},
        {102, "Bhavna Patil", "Malaria"},
        {103, "Chetan More ", "Typhoid"},
        {104, "Divya Joshi ", "Viral Fever"},
        {105, "Eshan Kulkarni", "Pneumonia"}
    };
    int comps = 0;
    int idx = linearSearchByName(registry, 5, "Divya Joshi ", comps);
    cout << "\nLinear Search for 'Divya Joshi': Found at Index " << idx 
         << " (" << comps << " comparisons)\n";

    idx = binarySearchByPatientId(registry, 5, 103, comps);
    cout << "Binary Search for Patient ID 103: Found at Index " << idx 
         << " (" << comps << " comparisons)\n";

    // 3. Quick Sort Temperatures
    float temps[6] = {101.4f, 98.6f, 103.2f, 99.1f, 102.5f, 98.4f};
    quickSortTemps(temps, 0, 5);
    cout << "\nSorted Body Temperatures (Quick Sort): ";
    for (int i = 0; i < 6; ++i) cout << temps[i] << " F  ";
    cout << "\n";

    // 4. Bills
    float bills[7] = {15000.0f, 45000.0f, 12500.0f, 92000.0f, 38000.0f, 115000.0f, 62000.0f};
    bubbleSortBillsAsc(bills, 7);
    cout << "\nTop 5 Highest Hospital Bills (Ascending Bubble Sort tail):\n";
    for (int i = 6; i >= 2; --i) {
        cout << "  #" << (7 - i) << ": Rs " << fixed << setprecision(2) << bills[i] << "\n";
    }

    return 0;
}
