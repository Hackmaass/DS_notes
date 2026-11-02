/**
 * ============================================================================
 * Departmental Problem Set 4 (Bank) - Problem 11
 * Program: Account Balance Ranking (Selection & Insertion Sort)
 * ============================================================================
 * Problem Statement:
 *   Manage an array of bank account balances:
 *   - Sort balances in descending order using Selection Sort (highest first).
 *   - Sort using Insertion Sort and count total comparisons and shifts.
 *   - Display top 5 highest balance accounts (HNI / Wealth Clients).
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct CustomerAccount {
    int accountNumber;
    string name;
    double balance;
};

void displayAccounts(const CustomerAccount arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "  Acc #" << arr[i].accountNumber << " | " << left << setw(18) << arr[i].name 
             << " | Balance: Rs. " << fixed << setprecision(2) << arr[i].balance << "\n";
    }
}

// Selection Sort: Descending (Largest element placed first)
void selectionSortDescending(CustomerAccount arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].balance > arr[maxIdx].balance) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            CustomerAccount temp = arr[i];
            arr[i] = arr[maxIdx];
            arr[maxIdx] = temp;
        }
    }
}

// Insertion Sort: Descending with metrics
void insertionSortDescending(CustomerAccount arr[], int n, int& comparisons, int& shifts) {
    comparisons = 0;
    shifts = 0;

    for (int i = 1; i < n; i++) {
        CustomerAccount key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            comparisons++;
            if (arr[j].balance < key.balance) {
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

void displayTop5HNI(const CustomerAccount arr[], int n) {
    int limit = (n < 5) ? n : 5;
    cout << "\n=== Top " << limit << " Highest Balance Accounts (HNI Privilege Tier) ===\n";
    for (int i = 0; i < limit; i++) {
        cout << "  Rank " << (i + 1) << ": " << left << setw(18) << arr[i].name 
             << " (Acc #" << arr[i].accountNumber << ") - Rs. " 
             << fixed << setprecision(2) << arr[i].balance << "\n";
    }
}

int main() {
    const int N = 7;
    CustomerAccount original[N] = {
        {1001, "Aarav Sharma",    45000.00},
        {1002, "Bhavna Patel",   185000.50},
        {1003, "Chetan Joshi",    28000.00},
        {1004, "Deepika Roy",    340000.00},
        {1005, "Esha Deol",       92000.75},
        {1006, "Farhan Akhtar",  510000.00},
        {1007, "Gauri Shinde",    64000.25}
    };

    CustomerAccount arrSelection[N];
    CustomerAccount arrInsertion[N];
    for (int i = 0; i < N; i++) {
        arrSelection[i] = original[i];
        arrInsertion[i] = original[i];
    }

    cout << "=== Initial Customer Account Records ===\n";
    displayAccounts(original, N);

    cout << "\n--- 1. Selection Sort (Descending Order by Balance) ---\n";
    selectionSortDescending(arrSelection, N);
    displayAccounts(arrSelection, N);

    cout << "\n--- 2. Insertion Sort (Descending Order by Balance) ---\n";
    int comparisons = 0, shifts = 0;
    insertionSortDescending(arrInsertion, N, comparisons, shifts);
    displayAccounts(arrInsertion, N);
    cout << "  Metrics: Comparisons = " << comparisons << ", Shifts = " << shifts << "\n";

    // Display Top 5 HNI Accounts
    displayTop5HNI(arrSelection, N);

    return 0;
}
