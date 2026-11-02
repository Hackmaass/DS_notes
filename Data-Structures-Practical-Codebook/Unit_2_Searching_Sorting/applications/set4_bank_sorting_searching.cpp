/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit II: Searching & Sorting
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 4 - Bank Management System (Searching & Sorting Suite)
 * TITLE:         Bank System: Balance Ranking, Account Search, Quick & Bubble Sort
 * 
 * PROBLEMS COVERED:
 *   1. Ranking customer accounts by balance (Selection & Insertion Sort descending, Top 5).
 *   2. Search customer records: Linear Search by Name vs Binary Search by Account No.
 *   3. Arrange loan interest rates using Quick Sort.
 *   4. Daily transaction amounts: Selection & Bubble Sort. Top 5 highest transactions.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// PROBLEM 1: BALANCE RANKING
struct CustomerBalanceRank {
    int accountNo;
    string name;
    double balance;
};

void selectionSortBalancesDesc(CustomerBalanceRank arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int maxIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j].balance > arr[maxIdx].balance) maxIdx = j;
        }
        if (maxIdx != i) {
            CustomerBalanceRank temp = arr[i];
            arr[i] = arr[maxIdx];
            arr[maxIdx] = temp;
        }
    }
}

int insertionSortBalancesDesc(CustomerBalanceRank arr[], int n) {
    int shifts = 0;
    for (int i = 1; i < n; ++i) {
        CustomerBalanceRank key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].balance < key.balance) {
            arr[j + 1] = arr[j];
            shifts++;
            j--;
        }
        arr[j + 1] = key;
    }
    return shifts;
}

// PROBLEM 2: SEARCH ACCOUNT
struct AccountSearchRecord {
    int accountNo;
    string name;
    string branch;
};

int linearSearchByCustomerName(const AccountSearchRecord arr[], int n, const string& target, int& comps) {
    comps = 0;
    for (int i = 0; i < n; ++i) {
        comps++;
        if (arr[i].name == target) return i;
    }
    return -1;
}

int binarySearchByAccountNo(const AccountSearchRecord arr[], int n, int acc, int& comps) {
    comps = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        comps++;
        int mid = low + (high - low) / 2;
        if (arr[mid].accountNo == acc) return mid;
        if (arr[mid].accountNo < acc) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// PROBLEM 3: QUICK SORT INTEREST RATES
int partitionInterest(float arr[], int low, int high) {
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

void quickSortInterest(float arr[], int low, int high) {
    if (low < high) {
        int pi = partitionInterest(arr, low, high);
        quickSortInterest(arr, low, pi - 1);
        quickSortInterest(arr, pi + 1, high);
    }
}

// PROBLEM 4: TRANSACTION AMOUNTS BUBBLE SORT
void bubbleSortTransactionsAsc(double arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
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
    cout << "  SET 4: BANK MANAGEMENT SYSTEM - SEARCHING & SORTING SUITE\n";
    cout << "====================================================================\n";

    // 1. Balance Ranking
    CustomerBalanceRank accounts[6] = {
        {1001, "Priya Sharma    ", 45000.0},
        {1002, "Nikhil Gaikwad  ", 185000.0},
        {1003, "Anjali Pawar    ", 92000.0},
        {1004, "Sanjay Kulkarni ", 240000.0},
        {1005, "Meera Deshmukh  ", 65000.0},
        {1006, "Rahul Shinde    ", 120000.0}
    };
    CustomerBalanceRank copyA[6];
    for (int i = 0; i < 6; ++i) copyA[i] = accounts[i];

    selectionSortBalancesDesc(accounts, 6);
    cout << "\n>>> TOP 5 HIGHEST BALANCE CUSTOMERS <<<\n";
    for (int i = 0; i < 5; ++i) {
        cout << "  #" << (i + 1) << " Account: " << accounts[i].accountNo 
             << " | Name: " << accounts[i].name 
             << " | Balance: Rs " << fixed << setprecision(2) << accounts[i].balance << "\n";
    }

    int shifts = insertionSortBalancesDesc(copyA, 6);
    cout << "Insertion Sort executed with " << shifts << " data shifts.\n";

    // 2. Search
    AccountSearchRecord branch[5] = {
        {1001, "Anjali Pawar    ", "Nigdi Branch"},
        {1002, "Meera Deshmukh  ", "Akurdi Branch"},
        {1003, "Nikhil Gaikwad  ", "Talegaon Branch"},
        {1004, "Priya Sharma    ", "Chinchwad Branch"},
        {1005, "Sanjay Kulkarni ", "Pimpri Branch"}
    };
    int comps = 0;
    int idx = linearSearchByCustomerName(branch, 5, "Nikhil Gaikwad  ", comps);
    cout << "\nLinear Search for 'Nikhil Gaikwad': Found at Index " << idx 
         << " (" << comps << " comparisons)\n";

    idx = binarySearchByAccountNo(branch, 5, 1004, comps);
    cout << "Binary Search for Account No 1004: Found at Index " << idx 
         << " (" << comps << " comparisons)\n";

    // 3. Quick Sort Interest Rates
    float rates[6] = {8.50f, 6.75f, 11.25f, 7.20f, 9.80f, 6.40f};
    quickSortInterest(rates, 0, 5);
    cout << "\nSorted Loan Interest Rates (Quick Sort): ";
    for (int i = 0; i < 6; ++i) cout << fixed << setprecision(2) << rates[i] << "%  ";
    cout << "\n";

    // 4. Daily Transactions Bubble Sort
    double txns[7] = {5000.0, 45000.0, 12000.0, 95000.0, 28000.0, 150000.0, 62000.0};
    bubbleSortTransactionsAsc(txns, 7);
    cout << "\nTop 5 Highest Daily Transactions (Ascending Bubble Sort tail):\n";
    for (int i = 6; i >= 2; --i) {
        cout << "  #" << (7 - i) << ": Rs " << fixed << setprecision(2) << txns[i] << "\n";
    }

    return 0;
}
