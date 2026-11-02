/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit II: Searching & Sorting
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 1 - Library Management System (Searching & Sorting Suite)
 * TITLE:         Library System: Selection, Insertion, Linear/Binary Search, Quick & Bubble Sort
 * 
 * PROBLEMS COVERED (Official Departmental Alternate Problem Set):
 *   1. Ranking Books by Issue Count: Selection Sort (desc) & Insertion Sort (with shift count). Top 5.
 *   2. Searching Book Records: Linear Search by Title vs Binary Search by Book ID (with comparison counts).
 *   3. Fine Amounts Collected: Quick Sort (recursive Lomuto partition).
 *   4. Book Prices: Ascending Selection Sort & Bubble Sort. Top 5 highest prices.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// ============================================================================
// PROBLEM 1: RANKING BY ISSUE COUNT (Selection Sort & Insertion Sort)
// ============================================================================
struct BookIssueRank {
    int bookId;
    string title;
    int issueCount;
};

void selectionSortBooksDesc(BookIssueRank arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int maxIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j].issueCount > arr[maxIdx].issueCount) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            BookIssueRank temp = arr[i];
            arr[i] = arr[maxIdx];
            arr[maxIdx] = temp;
        }
    }
}

int insertionSortBooksDesc(BookIssueRank arr[], int n) {
    int shifts = 0;
    for (int i = 1; i < n; ++i) {
        BookIssueRank key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].issueCount < key.issueCount) {
            arr[j + 1] = arr[j];
            shifts++;
            j--;
        }
        arr[j + 1] = key;
    }
    return shifts;
}

void displayTop5Books(const BookIssueRank arr[], int n) {
    int limit = (n < 5) ? n : 5;
    cout << "  " << left << setw(6) << "Rank" << setw(10) << "Book ID" 
         << setw(30) << "Title" << "Issue Count\n";
    cout << "  ---------------------------------------------------------\n";
    for (int i = 0; i < limit; ++i) {
        cout << "  #" << left << setw(5) << (i + 1)
             << setw(10) << arr[i].bookId
             << setw(30) << arr[i].title
             << arr[i].issueCount << " issues\n";
    }
    cout << "\n";
}

// ============================================================================
// PROBLEM 2: SEARCHING BOOK RECORDS (Linear vs Binary Search)
// ============================================================================
struct BookSearchRecord {
    int bookId;
    string title;
    string author;
};

int linearSearchByTitle(const BookSearchRecord arr[], int n, const string& targetTitle, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < n; ++i) {
        comparisons++;
        if (arr[i].title == targetTitle) return i;
    }
    return -1;
}

int binarySearchByBookId(const BookSearchRecord arr[], int n, int targetId, int& comparisons) {
    comparisons = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;
        if (arr[mid].bookId == targetId) return mid;
        if (arr[mid].bookId < targetId) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// ============================================================================
// PROBLEM 3: QUICK SORT ON FINE AMOUNTS
// ============================================================================
int partitionFines(float arr[], int low, int high) {
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

void quickSortFines(float arr[], int low, int high) {
    if (low < high) {
        int pi = partitionFines(arr, low, high);
        quickSortFines(arr, low, pi - 1);
        quickSortFines(arr, pi + 1, high);
    }
}

// ============================================================================
// PROBLEM 4: SELECTION & BUBBLE SORT ON BOOK PRICES
// ============================================================================
void selectionSortPricesAsc(float arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            float temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

void bubbleSortPricesAsc(float arr[], int n) {
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

// ============================================================================
// MASTER DEMO EXECUTION
// ============================================================================
int main() {
    cout << "====================================================================\n";
    cout << "  SET 1: LIBRARY SYSTEM - SEARCHING & SORTING SUITE\n";
    cout << "====================================================================\n";

    // 1. Ranking by Issue Count
    cout << "\n>>> PROBLEM 1: RANKING BOOKS BY ISSUE COUNT <<<\n";
    BookIssueRank books[6] = {
        {101, "Data Structures in C++", 145},
        {102, "Operating System Concepts", 88},
        {103, "Database System Concepts", 210},
        {104, "Computer Networks", 175},
        {105, "Discrete Mathematics", 62},
        {106, "Artificial Intelligence", 190}
    };
    BookIssueRank booksCopy[6];
    for (int i = 0; i < 6; ++i) booksCopy[i] = books[i];

    selectionSortBooksDesc(books, 6);
    cout << "Top 5 Most-Issued Books (Selection Sort Descending):\n";
    displayTop5Books(books, 6);

    int shifts = insertionSortBooksDesc(booksCopy, 6);
    cout << "Insertion Sort completed with " << shifts << " data element shifts.\n";

    // 2. Linear vs Binary Search
    cout << "\n>>> PROBLEM 2: SEARCHING BOOK RECORDS <<<\n";
    BookSearchRecord catalog[5] = {
        {101, "Artificial Intelligence", "Russell & Norvig"},
        {102, "Computer Networks", "Andrew Tanenbaum"},
        {103, "Data Structures in C++", "Sartaj Sahni"},
        {104, "Database Systems", "Korth & Silberschatz"},
        {105, "Operating Systems", "Silberschatz & Galvin"}
    };
    int comps = 0;
    int idx = linearSearchByTitle(catalog, 5, "Data Structures in C++", comps);
    cout << "Linear Search for 'Data Structures in C++': Found at Index " << idx 
         << " (" << comps << " comparisons)\n";

    idx = binarySearchByBookId(catalog, 5, 104, comps);
    cout << "Binary Search for Book ID 104: Found at Index " << idx 
         << " (" << comps << " comparisons)\n";

    // 3. Quick Sort Fines
    cout << "\n>>> PROBLEM 3: QUICK SORT ON LATE FINES <<<\n";
    float fines[6] = {45.50f, 120.00f, 15.00f, 85.50f, 250.00f, 30.00f};
    cout << "Unsorted Fines: ";
    for (int i = 0; i < 6; ++i) cout << "Rs " << fines[i] << "  ";
    cout << "\n";
    quickSortFines(fines, 0, 5);
    cout << "Sorted Fines  : ";
    for (int i = 0; i < 6; ++i) cout << "Rs " << fines[i] << "  ";
    cout << "\n";

    // 4. Prices Selection & Bubble Sort
    cout << "\n>>> PROBLEM 4: BOOK PRICES (Selection & Bubble Sort) <<<\n";
    float prices[7] = {650.0f, 420.5f, 890.0f, 310.0f, 740.0f, 950.0f, 520.0f};
    bubbleSortPricesAsc(prices, 7);
    cout << "Top 5 Highest Prices in Library (Ascending Bubble Sort tail):\n";
    for (int i = 6; i >= 2; --i) {
        cout << "  #" << (7 - i) << ": Rs " << fixed << setprecision(2) << prices[i] << "\n";
    }

    return 0;
}
