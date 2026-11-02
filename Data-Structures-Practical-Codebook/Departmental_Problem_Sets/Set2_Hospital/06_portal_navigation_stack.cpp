/**
 * ============================================================================
 * SET 2: HOSPITAL MANAGEMENT SYSTEM (Part B - Problem 1)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to maintain the navigation history of a hospital patient
 *   portal using a Stack.
 *   Functions:
 *     a. Visit new URL (Push onto stack)
 *     b. Go back to previous URL (Pop from stack)
 *     c. Display current page
 *     d. Display complete history
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

const int MAX = 50;

class HospitalPortalStack {
private:
    string urls[MAX];
    int top;

public:
    HospitalPortalStack() : top(-1) {}

    bool isEmpty() { return (top == -1); }
    bool isFull()  { return (top == MAX - 1); }

    // a. Visit new URL
    void visitPage(string url) {
        if (isFull()) {
            cout << "Portal history is full (Stack Overflow)!\n";
            return;
        }
        urls[++top] = url;
        cout << "[Navigated]: " << url << "\n";
    }

    // b. Go back to previous URL
    void backPage() {
        if (isEmpty()) {
            cout << "Cannot go back: History is empty!\n";
            return;
        }
        cout << "[Back Button]: Leaving " << urls[top--] << "\n";
        displayCurrent();
    }

    // c. Display current page
    void displayCurrent() {
        if (isEmpty()) {
            cout << "Current Page: Hospital Home Dashboard\n";
        } else {
            cout << "Current Active Page: " << urls[top] << "\n";
        }
    }

    // d. Display complete history
    void displayHistory() {
        if (isEmpty()) {
            cout << "Navigation history is empty.\n";
            return;
        }
        cout << "\n--- Hospital Patient Portal Navigation History ---\n";
        for (int i = top; i >= 0; --i) {
            cout << "  [" << (i + 1) << "] " << urls[i];
            if (i == top) cout << "  <-- (Current View)";
            cout << "\n";
        }
        cout << "--------------------------------------------------\n\n";
    }
};

int main() {
    cout << "==============================================================\n";
    cout << "  SET 2 (PART B - PROBLEM 1): PATIENT PORTAL NAVIGATION STACK\n";
    cout << "==============================================================\n";

    HospitalPortalStack portal;

    portal.visitPage("hospital.org/portal");
    portal.visitPage("hospital.org/portal/lab-reports");
    portal.visitPage("hospital.org/portal/lab-reports/blood-test-302");
    portal.displayHistory();

    portal.backPage();
    portal.displayHistory();

    portal.displayCurrent();

    return 0;
}
