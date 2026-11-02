/**
 * ============================================================================
 * Departmental Problem Set 4 (Bank) - Problem 12
 * Program: Account Record Search (Linear Search vs Binary Search)
 * ============================================================================
 * Problem Statement:
 *   Store an array of account records (Account No, Customer Name, Branch):
 *   - Implement Linear Search to find an account by Customer Name.
 *   - Implement Binary Search to find an account by Account Number (on sorted array).
 *   - Display comparison counts for both search methods.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

struct BankCustomer {
    int accountNumber;
    string name;
    string branch;
};

void displayCustomers(const BankCustomer arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "  [" << i << "] Acc #" << arr[i].accountNumber 
             << " | Name: " << arr[i].name 
             << " | Branch: " << arr[i].branch << "\n";
    }
}

// Linear Search by Customer Name
int linearSearchByName(const BankCustomer arr[], int n, const string& targetName, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        if (arr[i].name == targetName) {
            return i;
        }
    }
    return -1;
}

// Binary Search by Account Number (Requires sorted array by accountNumber)
int binarySearchByAccNo(const BankCustomer arr[], int n, int targetAccNo, int& comparisons) {
    comparisons = 0;
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;

        if (arr[mid].accountNumber == targetAccNo) {
            return mid;
        } else if (arr[mid].accountNumber < targetAccNo) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    const int N = 6;
    // Sorted by Account Number for Binary Search compatibility
    BankCustomer bankDB[N] = {
        {1002, "Aarav Sharma",   "Pune Main"},
        {1009, "Bhavna Patel",   "Kothrud Branch"},
        {1015, "Chetan Joshi",   "Shivajinagar Branch"},
        {1024, "Deepika Roy",    "Hinjawadi Branch"},
        {1031, "Esha Deol",      "Aundh Branch"},
        {1045, "Farhan Akhtar",  "Viman Nagar Branch"}
    };

    cout << "=== Bank Customer Directory ===\n";
    displayCustomers(bankDB, N);

    cout << "\n--- 1. Linear Search by Customer Name ---\n";
    string searchName = "Deepika Roy";
    int linearComparisons = 0;
    int indexName = linearSearchByName(bankDB, N, searchName, linearComparisons);

    if (indexName != -1) {
        cout << "  Found '" << searchName << "' at index " << indexName << ".\n";
        cout << "  Account #" << bankDB[indexName].accountNumber 
             << " | Branch: " << bankDB[indexName].branch << "\n";
    } else {
        cout << "  Customer '" << searchName << "' not found.\n";
    }
    cout << "  Linear Search Total Comparisons: " << linearComparisons << " (O(N) time)\n";

    cout << "\n--- 2. Binary Search by Account Number ---\n";
    int searchAcc = 1031;
    int binaryComparisons = 0;
    int indexAcc = binarySearchByAccNo(bankDB, N, searchAcc, binaryComparisons);

    if (indexAcc != -1) {
        cout << "  Found Account #" << searchAcc << " at index " << indexAcc << ".\n";
        cout << "  Customer Name: " << bankDB[indexAcc].name 
             << " | Branch: " << bankDB[indexAcc].branch << "\n";
    } else {
        cout << "  Account #" << searchAcc << " not found in directory.\n";
    }
    cout << "  Binary Search Total Comparisons: " << binaryComparisons << " (O(log N) time)\n";

    return 0;
}
