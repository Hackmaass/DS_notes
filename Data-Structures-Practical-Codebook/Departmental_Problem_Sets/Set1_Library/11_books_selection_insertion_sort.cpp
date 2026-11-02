/**
 * ============================================================================
 * SET 1: LIBRARY MANAGEMENT SYSTEM (Sorting Problem 1)
 * SOURCE: Four Alternate Problem Sets Sorting and Searching.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to generate a ranked list of most-issued books by issue count.
 *   a. Selection sort in descending order
 *   b. Insertion sort in descending order and count data element shifts
 *   c. Display top 5 most-issued books
 * ============================================================================
 * ALGORITHM:
 *   1. Selection Sort (Descending):
 *      - Loop i from 0 to n - 2.
 *      - Find index of maximum element in arr[i..n-1].
 *      - Swap arr[i] with arr[maxIndex].
 *   2. Insertion Sort (Descending with shifts):
 *      - Loop i from 1 to n - 1. Set key = arr[i].
 *      - While j >= 0 and arr[j].issueCount < key.issueCount:
 *        shift arr[j+1] = arr[j], increment shifts, decrement j.
 *      - Place key at arr[j+1].
 *   3. Display Top 5:
 *      - Print elements from rank 1 to min(n, 5).
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Book {
    int bookId;
    string title;
    int issueCount;
};

// a. Selection Sort in Descending Order
void selectionSortDesc(Book arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int maxIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j].issueCount > arr[maxIdx].issueCount) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            Book temp = arr[i];
            arr[i] = arr[maxIdx];
            arr[maxIdx] = temp;
        }
    }
}

// b. Insertion Sort in Descending Order with Shift Counting
int insertionSortDesc(Book arr[], int n) {
    int shiftCount = 0;
    for (int i = 1; i < n; ++i) {
        Book key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].issueCount < key.issueCount) {
            arr[j + 1] = arr[j]; // Shift right
            shiftCount++;
            j--;
        }
        arr[j + 1] = key;
    }
    return shiftCount;
}

// c. Display Top 5 Books
void displayTop5(const Book arr[], int n) {
    int count = (n < 5) ? n : 5;
    cout << "\n--------------------------------------------------------------\n";
    cout << left << setw(6) << "Rank" << setw(10) << "Book ID" 
         << setw(30) << "Title" << "Issue Count\n";
    cout << "--------------------------------------------------------------\n";
    for (int i = 0; i < count; ++i) {
        cout << "#" << left << setw(5) << (i + 1)
             << setw(10) << arr[i].bookId
             << setw(30) << arr[i].title
             << arr[i].issueCount << " issues\n";
    }
    cout << "--------------------------------------------------------------\n\n";
}

int main() {
    cout << "==============================================================\n";
    cout << "  SET 1 (SORTING PROBLEM 1): MOST-ISSUED BOOKS RANKING\n";
    cout << "==============================================================\n";

    const int N = 6;
    Book books[N] = {
        {101, "Data Structures in C++", 145},
        {102, "Operating System Concepts", 88},
        {103, "Database System Concepts", 210},
        {104, "Computer Networks", 175},
        {105, "Discrete Mathematics", 62},
        {106, "Artificial Intelligence", 190}
    };

    Book booksCopy[N];
    for (int i = 0; i < N; ++i) booksCopy[i] = books[i];

    // a & c. Selection Sort Descending & Top 5
    selectionSortDesc(books, N);
    cout << "\n[Selection Sort Result]: Top 5 Most-Issued Books:\n";
    displayTop5(books, N);

    // b. Insertion Sort with shift counting
    int shifts = insertionSortDesc(booksCopy, N);
    cout << "[Insertion Sort Result]: Completed with " << shifts << " data element shifts.\n";

    return 0;
}
