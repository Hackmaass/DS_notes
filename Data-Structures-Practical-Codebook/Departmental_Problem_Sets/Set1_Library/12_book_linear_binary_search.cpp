/**
 * ============================================================================
 * SET 1: LIBRARY MANAGEMENT SYSTEM (Searching Problem 2)
 * SOURCE: Four Alternate Problem Sets Sorting and Searching.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to search a book record (Book ID, Title, Author).
 *   a. Linear Search by Title
 *   b. Binary Search by Book ID (array sorted by Book ID)
 *   c. Display comparison counts for both search methods
 * ============================================================================
 * ALGORITHM:
 *   1. Linear Search by Title:
 *      - Loop through array index 0 to n - 1. Increment comparisons.
 *      - If arr[i].title == targetTitle, return index. If not found, return -1.
 *   2. Binary Search by Book ID:
 *      - Array must be sorted by bookId. low = 0, high = n - 1.
 *      - While low <= high:
 *        mid = low + (high - low) / 2. Increment comparisons.
 *        If arr[mid].bookId == targetId, return mid.
 *        If arr[mid].bookId < targetId, low = mid + 1; else high = mid - 1.
 *      - If not found, return -1.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Book {
    int bookId;
    string title;
    string author;
};

// a. Linear Search by Title
int linearSearchByTitle(const Book arr[], int n, string targetTitle, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < n; ++i) {
        comparisons++;
        if (arr[i].title == targetTitle) {
            return i;
        }
    }
    return -1;
}

// b. Binary Search by Book ID (Sorted by Book ID)
int binarySearchByBookId(const Book arr[], int n, int targetId, int& comparisons) {
    comparisons = 0;
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;

        if (arr[mid].bookId == targetId) {
            return mid;
        }
        if (arr[mid].bookId < targetId) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    cout << "==============================================================\n";
    cout << "  SET 1 (SEARCHING PROBLEM 2): LINEAR VS BINARY SEARCH\n";
    cout << "==============================================================\n";

    const int N = 5;
    Book catalog[N] = {
        {101, "Artificial Intelligence", "Russell & Norvig"},
        {102, "Computer Networks", "Andrew Tanenbaum"},
        {103, "Data Structures in C++", "Sartaj Sahni"},
        {104, "Database Systems", "Korth & Silberschatz"},
        {105, "Operating Systems", "Silberschatz & Galvin"}
    };

    cout << "Library Catalogue Records (Sorted by Book ID):\n";
    for (int i = 0; i < N; ++i) {
        cout << "  ID: " << catalog[i].bookId << " | Title: " 
             << left << setw(26) << catalog[i].title 
             << " | Author: " << catalog[i].author << "\n";
    }

    int comps = 0;

    // a. Linear search by Title
    string searchTitle = "Data Structures in C++";
    int idx = linearSearchByTitle(catalog, N, searchTitle, comps);
    cout << "\n[Linear Search for Title: '" << searchTitle << "']:\n";
    if (idx != -1) {
        cout << "  -> Found at Index " << idx << " (Book ID: " << catalog[idx].bookId << ")\n";
    } else {
        cout << "  -> Book not found!\n";
    }
    cout << "  -> Total Comparisons Made: " << comps << "\n";

    // b. Binary search by Book ID
    int searchId = 104;
    idx = binarySearchByBookId(catalog, N, searchId, comps);
    cout << "\n[Binary Search for Book ID: " << searchId << "]:\n";
    if (idx != -1) {
        cout << "  -> Found at Index " << idx << " (Title: " << catalog[idx].title << ")\n";
    } else {
        cout << "  -> Book ID not found!\n";
    }
    cout << "  -> Total Comparisons Made: " << comps << "\n";

    return 0;
}
