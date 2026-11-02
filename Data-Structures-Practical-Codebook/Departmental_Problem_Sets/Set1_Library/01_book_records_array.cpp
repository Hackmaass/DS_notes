/**
 * ============================================================================
 * SET 1: LIBRARY MANAGEMENT SYSTEM (Part A - Problem 1)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to maintain records of N books with attributes:
 *   Book ID, Title, and Price using an array.
 *   Perform operations:
 *     a. Insert at position
 *     b. Delete by Book ID
 *     c. Search by Book ID and display
 *     d. Display all books
 * ============================================================================
 * ALGORITHM:
 *   1. Insert at position (pos):
 *      - If size == MAX, print "Array Full".
 *      - Shift elements from index (size - 1) down to (pos - 1) one position right.
 *      - Place new book at books[pos - 1]. Increment size.
 *   2. Delete by Book ID:
 *      - Find index 'i' where books[i].bookId == targetId.
 *      - If found, shift elements from (i + 1) to (size - 1) one position left.
 *      - Decrement size.
 *   3. Search by Book ID:
 *      - Linearly check each book from index 0 to size - 1. Return index if found.
 *   4. Display:
 *      - Loop from 0 to size - 1 and print each book's ID, Title, and Price.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX = 50;

struct Book {
    int bookId;
    string title;
    float price;
};

class LibraryArray {
private:
    Book books[MAX];
    int size;

public:
    LibraryArray() {
        size = 0;
    }

    // a. Insert at position (1-based index)
    bool insertAtPosition(int pos, int id, string title, float price) {
        if (size >= MAX) {
            cout << "Error: Library catalog is full!\n";
            return false;
        }
        if (pos < 1 || pos > size + 1) {
            cout << "Error: Position must be between 1 and " << (size + 1) << ".\n";
            return false;
        }

        // Shift existing elements to the right to create an empty slot
        for (int i = size; i >= pos; --i) {
            books[i] = books[i - 1];
        }

        // Insert new book at pos - 1
        books[pos - 1].bookId = id;
        books[pos - 1].title = title;
        books[pos - 1].price = price;
        size++;

        cout << "Inserted '" << title << "' at position " << pos << ".\n";
        return true;
    }

    // b. Delete by Book ID
    bool deleteByBookId(int targetId) {
        int index = -1;
        for (int i = 0; i < size; ++i) {
            if (books[i].bookId == targetId) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Book ID " << targetId << " not found!\n";
            return false;
        }

        cout << "Deleting Book: " << books[index].title << " (ID: " << targetId << ")\n";

        // Shift elements left to fill the gap
        for (int i = index; i < size - 1; ++i) {
            books[i] = books[i + 1];
        }
        size--;
        return true;
    }

    // c. Search by Book ID and display
    int searchByBookId(int targetId) {
        for (int i = 0; i < size; ++i) {
            if (books[i].bookId == targetId) {
                cout << "\n[Found Book Details]:\n";
                cout << "  Book ID : " << books[i].bookId << "\n";
                cout << "  Title   : " << books[i].title << "\n";
                cout << "  Price   : Rs " << fixed << setprecision(2) << books[i].price << "\n";
                return i;
            }
        }
        cout << "Book ID " << targetId << " not found in library.\n";
        return -1;
    }

    // d. Display all books
    void displayAll() {
        if (size == 0) {
            cout << "Library catalogue is empty.\n";
            return;
        }

        cout << "\n--------------------------------------------------------------\n";
        cout << left << setw(6) << "Pos" << setw(10) << "Book ID" 
             << setw(30) << "Title" << "Price (Rs)\n";
        cout << "--------------------------------------------------------------\n";
        for (int i = 0; i < size; ++i) {
            cout << left << setw(6) << (i + 1)
                 << setw(10) << books[i].bookId
                 << setw(30) << books[i].title
                 << fixed << setprecision(2) << books[i].price << "\n";
        }
        cout << "--------------------------------------------------------------\n";
    }
};

int main() {
    cout << "==============================================================\n";
    cout << "  SET 1 (PART A - PROBLEM 1): BOOK RECORDS USING ARRAY\n";
    cout << "==============================================================\n";

    LibraryArray lib;

    // a. Insert books at positions
    lib.insertAtPosition(1, 101, "Data Structures in C++", 550.00);
    lib.insertAtPosition(2, 102, "Operating Systems", 620.00);
    lib.insertAtPosition(2, 103, "Database Systems", 480.00); // Insert at position 2
    lib.displayAll();

    // c. Search by Book ID
    lib.searchByBookId(103);

    // b. Delete by Book ID
    lib.deleteByBookId(102);
    lib.displayAll();

    return 0;
}
