/**
 * ============================================================================
 * Departmental Problem Set 4 (Bank) - Problem 3
 * Program: Bank Transactions Queue SLL (Insert at Position & Delete Front)
 * ============================================================================
 * Problem Statement:
 *   Manage bank transaction approval queue using a Singly Linked List:
 *   - Insert transaction at a specified position (middle insertion for priority).
 *   - Delete transaction from front (processing oldest transaction in queue).
 *   - Count transactions marked 'D' (Due / Defaulted).
 *   - Display current pending transactions.
 * ============================================================================
 */

#include <iostream>

using namespace std;

struct TransactionNode {
    int accountNumber;
    char status; // 'P' = Processed/Paid, 'D' = Due/Pending
    TransactionNode* next;

    TransactionNode(int acc, char st) : accountNumber(acc), status(st), next(nullptr) {}
};

class TransactionQueueList {
private:
    TransactionNode* head;

public:
    TransactionQueueList() : head(nullptr) {}

    ~TransactionQueueList() {
        TransactionNode* curr = head;
        while (curr != nullptr) {
            TransactionNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    // Insert at specific 1-based position
    void insertAtPosition(int position, int accountNumber, char status) {
        if (position < 1) {
            cout << "Invalid position. Position must be >= 1.\n";
            return;
        }
        TransactionNode* newNode = new TransactionNode(accountNumber, status);

        if (position == 1) {
            newNode->next = head;
            head = newNode;
            cout << "Inserted at front (Pos 1): Account #" << accountNumber << "\n";
            return;
        }

        TransactionNode* curr = head;
        for (int i = 1; i < position - 1 && curr != nullptr; i++) {
            curr = curr->next;
        }

        if (curr == nullptr) {
            cout << "Position " << position << " is beyond list bounds. Insert cancelled.\n";
            delete newNode;
            return;
        }

        newNode->next = curr->next;
        curr->next = newNode;
        cout << "Inserted at Position " << position << ": Account #" << accountNumber << "\n";
    }

    // Delete from front (processing oldest transaction)
    void deleteFront() {
        if (head == nullptr) {
            cout << "Processing Failed: Transaction queue is empty.\n";
            return;
        }
        TransactionNode* temp = head;
        head = head->next;
        cout << "Processed (Deleted Front): Account #" << temp->accountNumber 
             << " [Status: " << temp->status << "]\n";
        delete temp;
    }

    // Count accounts with status 'D' (Due / Pending verification)
    int countDue() const {
        int count = 0;
        TransactionNode* curr = head;
        while (curr != nullptr) {
            if (curr->status == 'D') {
                count++;
            }
            curr = curr->next;
        }
        return count;
    }

    void display() const {
        if (head == nullptr) {
            cout << "Transaction Queue: [Empty]\n";
            return;
        }
        cout << "Bank Transaction Queue (Head -> Tail):\n  ";
        TransactionNode* curr = head;
        while (curr != nullptr) {
            cout << "[#" << curr->accountNumber << " | " << curr->status << "]";
            if (curr->next != nullptr) cout << " -> ";
            curr = curr->next;
        }
        cout << " -> NULL\n";
    }
};

int main() {
    TransactionQueueList queue;

    cout << "=== Bank Transaction Approval Queue (SLL) ===\n\n";

    // Insert initial transactions
    queue.insertAtPosition(1, 3001, 'P');
    queue.insertAtPosition(2, 3002, 'D');
    queue.insertAtPosition(3, 3003, 'D');

    queue.display();

    // Priority insertion at middle position (Pos 2)
    cout << "\n--- Priority Transaction Inserted at Middle (Pos 2) ---\n";
    queue.insertAtPosition(2, 3005, 'D');
    queue.display();

    cout << "\nTotal Due / Pending ('D') Transactions: " << queue.countDue() << "\n";

    // Process from front
    cout << "\n--- Clearing Oldest Transaction (Delete Front) ---\n";
    queue.deleteFront();
    queue.display();

    cout << "\nTotal Due / Pending ('D') Transactions Remaining: " << queue.countDue() << "\n";

    return 0;
}
