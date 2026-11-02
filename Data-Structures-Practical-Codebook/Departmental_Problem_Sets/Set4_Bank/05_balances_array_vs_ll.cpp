/**
 * ============================================================================
 * Departmental Problem Set 4 (Bank) - Problem 5
 * Program: Customer Account Balances - Array vs Linked List Comparison
 * ============================================================================
 * Problem Statement:
 *   Store customer account balances (acc_no, balance):
 *   - Implement both Array and Singly Linked List representations.
 *   - Compare memory layout (contiguous addresses vs scattered heap nodes).
 *   - Count accounts with balance > Rs. 50,000 in both structures.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

// Representation 1: Array Element Structure
struct AccountBalance {
    int accountNumber;
    double balance;
};

// Representation 2: Singly Linked List Node
struct AccountNode {
    int accountNumber;
    double balance;
    AccountNode* next;

    AccountNode(int acc, double bal) : accountNumber(acc), balance(bal), next(nullptr) {}
};

int main() {
    cout << "=== Customer Account Balances: Array vs Linked List ===\n\n";

    // ----------------------------------------------------
    // 1. ARRAY IMPLEMENTATION
    // ----------------------------------------------------
    const int N = 5;
    AccountBalance accountsArray[N] = {
        {1001, 24500.00},
        {1002, 78200.50},
        {1003, 15000.00},
        {1004, 120500.00},
        {1005, 52000.00}
    };

    cout << "--- 1. Array Representation (Contiguous Memory) ---\n";
    int arrayHighBalCount = 0;
    for (int i = 0; i < N; i++) {
        cout << "  Index [" << i << "] Addr: " << (void*)&accountsArray[i]
             << " | Acc #" << accountsArray[i].accountNumber 
             << " | Balance: Rs. " << fixed << setprecision(2) << accountsArray[i].balance << "\n";
        if (accountsArray[i].balance > 50000.0) {
            arrayHighBalCount++;
        }
    }
    cout << "  Accounts with Balance > Rs. 50,000 (Array): " << arrayHighBalCount << "\n\n";

    // ----------------------------------------------------
    // 2. LINKED LIST IMPLEMENTATION
    // ----------------------------------------------------
    AccountNode* head = new AccountNode(1001, 24500.00);
    head->next = new AccountNode(1002, 78200.50);
    head->next->next = new AccountNode(1003, 15000.00);
    head->next->next->next = new AccountNode(1004, 120500.00);
    head->next->next->next->next = new AccountNode(1005, 52000.00);

    cout << "--- 2. Linked List Representation (Scattered Heap Nodes) ---\n";
    int llHighBalCount = 0;
    AccountNode* curr = head;
    int nodeIdx = 1;
    while (curr != nullptr) {
        cout << "  Node #" << nodeIdx++ << " Addr: " << (void*)curr 
             << " | Acc #" << curr->accountNumber 
             << " | Balance: Rs. " << fixed << setprecision(2) << curr->balance 
             << " | Next Addr: " << (void*)curr->next << "\n";
        if (curr->balance > 50000.0) {
            llHighBalCount++;
        }
        curr = curr->next;
    }
    cout << "  Accounts with Balance > Rs. 50,000 (Linked List): " << llHighBalCount << "\n\n";

    // ----------------------------------------------------
    // 3. COMPARATIVE ANALYSIS
    // ----------------------------------------------------
    cout << "=== Memory Layout & Architectural Comparison ===\n";
    cout << "1. Spatial Locality:\n";
    cout << "   - Array stores records consecutively, maximizing CPU L1/L2 cache hits.\n";
    cout << "   - Linked list scatters nodes across the heap, incurring pointer traversal overhead.\n";
    cout << "2. Memory Overhead:\n";
    cout << "   - Array: No extra per-element pointer overhead (" << sizeof(AccountBalance) << " bytes/element).\n";
    cout << "   - Linked List: Stores an 8-byte pointer with each record (" << sizeof(AccountNode) << " bytes/node).\n";
    cout << "3. Dynamic Growth:\n";
    cout << "   - Array: Fixed capacity; resizing requires O(N) reallocation and copying.\n";
    cout << "   - Linked List: Grows dynamically one node at a time without reallocation.\n";

    // Free Linked List
    curr = head;
    while (curr != nullptr) {
        AccountNode* temp = curr;
        curr = curr->next;
        delete temp;
    }

    return 0;
}
