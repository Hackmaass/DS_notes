/**
 * ============================================================================
 * Departmental Problem Set 4 (Bank) - Problem 6
 * Program: Netbanking Portal Navigation (Stack ADT using Array)
 * ============================================================================
 * Problem Statement:
 *   Simulate netbanking portal navigation using a Stack (LIFO):
 *   - Push visited portal page (e.g., Accounts, Funds Transfer, Payee).
 *   - Pop to navigate back to previous screen.
 *   - Peek to check active screen.
 *   - Display complete session navigation breadcrumbs.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

const int MAX_STACK = 10;

class NetbankingNavigationStack {
private:
    string stack[MAX_STACK];
    int top;

public:
    NetbankingNavigationStack() : top(-1) {}

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == MAX_STACK - 1;
    }

    void push(const string& page) {
        if (isFull()) {
            cout << "Stack Overflow: Navigation history limit reached.\n";
            return;
        }
        stack[++top] = page;
        cout << "Navigated to: " << page << "\n";
    }

    void pop() {
        if (isEmpty()) {
            cout << "Session Error: Cannot go back, at root screen.\n";
            return;
        }
        cout << "Navigating Back from: " << stack[top--] << "\n";
    }

    void peek() const {
        if (isEmpty()) {
            cout << "Current Screen: Logged Out\n";
            return;
        }
        cout << "Active Screen: " << stack[top] << "\n";
    }

    void displayHistory() const {
        if (isEmpty()) {
            cout << "Navigation History: [Empty]\n";
            return;
        }
        cout << "\nSession Breadcrumbs (Top/Current -> Root):\n";
        for (int i = top; i >= 0; i--) {
            cout << "  " << (top - i + 1) << ". " << stack[i];
            if (i == top) cout << "  <-- CURRENT VIEW";
            cout << "\n";
        }
    }
};

int main() {
    NetbankingNavigationStack session;

    cout << "=== Netbanking Portal Navigation System (Stack ADT) ===\n\n";

    session.push("Account Overview");
    session.push("Funds Transfer");
    session.push("NEFT / RTGS");
    session.push("Confirm Beneficiary OTP");

    session.displayHistory();

    cout << "\n--- Check Current Active Page ---\n";
    session.peek();

    cout << "\n--- User Clicks 'Back' Twice ---\n";
    session.pop();
    session.pop();

    session.displayHistory();

    cout << "\n--- User Selects 'Fixed Deposits' ---\n";
    session.push("Open New FD / RD");
    session.displayHistory();

    return 0;
}
