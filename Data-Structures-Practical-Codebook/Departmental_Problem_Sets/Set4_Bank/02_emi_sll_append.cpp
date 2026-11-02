/**
 * ============================================================================
 * Departmental Problem Set 4 (Bank) - Problem 2
 * Program: Daily Loan EMI Payment Status using SLL (Append & Update)
 * ============================================================================
 * Problem Statement:
 *   Store daily loan EMI statuses using a Singly Linked List:
 *   - Nodes store accountNumber and emiStatus ('P' = Paid, 'D' = Due).
 *   - Operations:
 *     1. Append new loan EMI record
 *     2. Update EMI status of an account by accountNumber
 *     3. Count accounts currently 'P' (Paid)
 *     4. Display all EMI payment records
 * ============================================================================
 */

#include <iostream>

using namespace std;

struct EMIRecordNode {
    int accountNumber;
    char emiStatus; // 'P' = Paid, 'D' = Due/Pending
    EMIRecordNode* next;

    EMIRecordNode(int acc, char st) : accountNumber(acc), emiStatus(st), next(nullptr) {}
};

class EMITrackerList {
private:
    EMIRecordNode* head;

public:
    EMITrackerList() : head(nullptr) {}

    ~EMITrackerList() {
        EMIRecordNode* curr = head;
        while (curr != nullptr) {
            EMIRecordNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    void append(int accountNumber, char status) {
        EMIRecordNode* newNode = new EMIRecordNode(accountNumber, status);
        if (head == nullptr) {
            head = newNode;
        } else {
            EMIRecordNode* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = newNode;
        }
        cout << "Appended: Account #" << accountNumber 
             << " [EMI Status: " << (status == 'P' ? "Paid" : "Due") << "]\n";
    }

    bool updateStatus(int accountNumber, char newStatus) {
        EMIRecordNode* curr = head;
        while (curr != nullptr) {
            if (curr->accountNumber == accountNumber) {
                curr->emiStatus = newStatus;
                cout << "Updated: Account #" << accountNumber 
                     << " new EMI status -> " << (newStatus == 'P' ? "Paid" : "Due") << "\n";
                return true;
            }
            curr = curr->next;
        }
        cout << "Update Failed: Account #" << accountNumber << " not found in EMI records.\n";
        return false;
    }

    int countPaid() const {
        int count = 0;
        EMIRecordNode* curr = head;
        while (curr != nullptr) {
            if (curr->emiStatus == 'P') {
                count++;
            }
            curr = curr->next;
        }
        return count;
    }

    void display() const {
        if (head == nullptr) {
            cout << "EMI Tracking List is empty.\n";
            return;
        }
        cout << "\nDaily Loan EMI Status Summary:\n";
        EMIRecordNode* curr = head;
        int index = 1;
        while (curr != nullptr) {
            cout << "  " << index++ << ". Account #" << curr->accountNumber 
                 << " | EMI Status: [" << curr->emiStatus << "] " 
                 << (curr->emiStatus == 'P' ? "PAID" : "DUE / PENDING") << "\n";
            curr = curr->next;
        }
    }
};

int main() {
    EMITrackerList tracker;

    cout << "=== Daily Loan EMI Payment Tracking (SLL) ===\n\n";

    tracker.append(2001, 'P');
    tracker.append(2002, 'D');
    tracker.append(2003, 'P');
    tracker.append(2004, 'D');
    tracker.append(2005, 'D');

    tracker.display();

    cout << "\nTotal Accounts with EMI Paid ('P'): " << tracker.countPaid() << "\n";

    cout << "\n--- Customer Makes EMI Payment ---\n";
    tracker.updateStatus(2002, 'P'); // Settled payment
    tracker.updateStatus(2004, 'P'); // Settled payment

    tracker.display();

    cout << "\nTotal Accounts with EMI Paid ('P') After Updates: " << tracker.countPaid() << "\n";

    return 0;
}
