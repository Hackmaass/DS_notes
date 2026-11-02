/**
 * ============================================================================
 * SET 1: LIBRARY MANAGEMENT SYSTEM (Part A - Problem 5)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to store the number of books issued by N members using 
 *   both an Array and a Linked List.
 *   Functions:
 *     a. Insert count in both
 *     b. Display memory representation (indices and memory addresses)
 *     c. Calculate total members who have issued more than 5 books
 * ============================================================================
 * ALGORITHM:
 *   1. Array Insertion: Store values in contiguous stack memory arr[i] = count.
 *   2. Linked List Insertion: Dynamically allocate Node(count) on the heap.
 *   3. Memory Representation Display:
 *      - For Array: Print each element's index, value, and address `&arr[i]`.
 *        Observe that addresses differ by exactly sizeof(int) (4 bytes).
 *      - For Linked List: Print node number, value, node address, and `next` pointer.
 *        Observe that addresses are non-contiguous heap pointers.
 *   4. Count Members > 5 books:
 *      - Loop through array and count items > 5.
 *      - Traverse linked list and count nodes > 5. Compare both results.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

struct Node {
    int memberId;
    int booksIssued;
    Node* next;

    Node(int id, int count) : memberId(id), booksIssued(count), next(nullptr) {}
};

int main() {
    cout << "==============================================================\n";
    cout << "  SET 1 (PART A - PROBLEM 5): ARRAY VS LINKED LIST MEMORY\n";
    cout << "==============================================================\n";

    const int N = 5;
    int memberIds[N] = {101, 102, 103, 104, 105};
    int booksArray[N] = {3, 7, 2, 8, 4}; // Books issued count

    // Linked List creation
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < N; ++i) {
        Node* newNode = new Node(memberIds[i], booksArray[i]);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // b. Display memory representation of Array
    cout << "\n1. ARRAY MEMORY REPRESENTATION (Contiguous Stack Allocation):\n";
    cout << "   " << left << setw(8) << "Index" << setw(12) << "Member ID" 
         << setw(16) << "Books Issued" << "Memory Address (Hex)\n";
    cout << "   ---------------------------------------------------------\n";
    int arrayCount = 0;
    for (int i = 0; i < N; ++i) {
        cout << "   " << left << setw(8) << i 
             << setw(12) << memberIds[i] 
             << setw(16) << booksArray[i] 
             << &booksArray[i] << "\n";
        if (booksArray[i] > 5) arrayCount++;
    }

    // b. Display memory representation of Linked List
    cout << "\n2. LINKED LIST MEMORY REPRESENTATION (Non-Contiguous Heap Allocation):\n";
    cout << "   " << left << setw(8) << "Node" << setw(12) << "Member ID" 
         << setw(16) << "Books Issued" << setw(20) << "Node Address" << "Next Pointer\n";
    cout << "   -------------------------------------------------------------------------\n";
    int llCount = 0;
    int nodeNum = 1;
    Node* curr = head;
    while (curr != nullptr) {
        cout << "   " << left << setw(8) << nodeNum 
             << setw(12) << curr->memberId 
             << setw(16) << curr->booksIssued 
             << setw(20) << curr 
             << curr->next << "\n";
        if (curr->booksIssued > 5) llCount++;
        curr = curr->next;
        nodeNum++;
    }

    // c. Calculate total members who issued > 5 books
    cout << "\n3. RESULTS:\n";
    cout << "   -> Members issuing > 5 books (Array check)       : " << arrayCount << "\n";
    cout << "   -> Members issuing > 5 books (Linked List check) : " << llCount << "\n";

    // Clean up heap
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
