/**
 * ============================================================================
 * Departmental Problem Set 4 (Bank) - Problem 1
 * Program: Customer Accounts Management using Array
 * ============================================================================
 * Problem Statement:
 *   Maintain bank customer accounts using an array (acc_no, name, balance, type):
 *   a. Insert account at a specific position
 *   b. Delete account by Account Number
 *   c. Search account by Account Number
 *   d. Display all accounts
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_ACCOUNTS = 50;

struct BankAccount {
    int accountNumber;
    string customerName;
    double balance;
    string accountType; // "Savings", "Current", etc.
};

class BankAccountArray {
private:
    BankAccount accounts[MAX_ACCOUNTS];
    int size;

public:
    BankAccountArray() : size(0) {}

    void insertAtPosition(int pos, int accNo, const string& name, double balance, const string& type) {
        if (size >= MAX_ACCOUNTS) {
            cout << "Error: Bank ledger capacity full.\n";
            return;
        }
        if (pos < 0 || pos > size) {
            cout << "Error: Invalid index " << pos << ". Valid: [0, " << size << "].\n";
            return;
        }
        // Shift elements right
        for (int i = size; i > pos; i--) {
            accounts[i] = accounts[i - 1];
        }
        accounts[pos] = {accNo, name, balance, type};
        size++;
        cout << "Inserted: Account [" << accNo << "] " << name << " at index " << pos << ".\n";
    }

    void deleteByAccNo(int targetAccNo) {
        int targetIndex = -1;
        for (int i = 0; i < size; i++) {
            if (accounts[i].accountNumber == targetAccNo) {
                targetIndex = i;
                break;
            }
        }
        if (targetIndex == -1) {
            cout << "Delete Failed: Account Number " << targetAccNo << " not found.\n";
            return;
        }
        cout << "Closed/Deleted: Account [" << accounts[targetIndex].accountNumber << "] " 
             << accounts[targetIndex].customerName << " from index " << targetIndex << ".\n";
        // Shift elements left
        for (int i = targetIndex; i < size - 1; i++) {
            accounts[i] = accounts[i + 1];
        }
        size--;
    }

    int searchByAccNo(int targetAccNo) const {
        for (int i = 0; i < size; i++) {
            if (accounts[i].accountNumber == targetAccNo) {
                return i;
            }
        }
        return -1;
    }

    void display() const {
        if (size == 0) {
            cout << "Ledger is empty.\n";
            return;
        }
        cout << "\n------------------ Active Customer Accounts (" << size << " accounts) ------------------\n";
        cout << left << setw(8) << "Index" << setw(12) << "Acc No" << setw(20) << "Customer Name" 
             << setw(16) << "Balance (Rs.)" << setw(12) << "Type" << "\n";
        cout << "------------------------------------------------------------------------\n";
        for (int i = 0; i < size; i++) {
            cout << left << setw(8) << i << setw(12) << accounts[i].accountNumber 
                 << setw(20) << accounts[i].customerName 
                 << fixed << setprecision(2) << setw(16) << accounts[i].balance 
                 << setw(12) << accounts[i].accountType << "\n";
        }
        cout << "------------------------------------------------------------------------\n";
    }
};

int main() {
    BankAccountArray bank;

    cout << "=== Bank Customer Accounts Management System ===\n\n";

    // Insert accounts
    bank.insertAtPosition(0, 1001, "Aarav Sharma", 45000.50, "Savings");
    bank.insertAtPosition(1, 1002, "Bhavna Patel", 125000.00, "Current");
    bank.insertAtPosition(2, 1003, "Chetan Joshi", 28000.75, "Savings");

    // Insert at specific middle position (index 1)
    bank.insertAtPosition(1, 1004, "Deepika Roy", 85000.00, "Savings");

    bank.display();

    // Search by Account Number
    cout << "\n--- Search Account by Account Number ---\n";
    int searchAcc = 1002;
    int idx = bank.searchByAccNo(searchAcc);
    if (idx != -1) {
        cout << "Found Account " << searchAcc << " at index " << idx << ".\n";
    } else {
        cout << "Account " << searchAcc << " not found.\n";
    }

    // Delete by Account Number
    cout << "\n--- Delete Account by Account Number ---\n";
    bank.deleteByAccNo(1004);

    bank.display();

    return 0;
}
