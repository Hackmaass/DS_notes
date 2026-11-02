/**
 * ============================================================================
 * SET 1: LIBRARY MANAGEMENT SYSTEM (Part B - Problem 1)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to maintain the navigation history of an online library
 *   catalogue using a Stack (LIFO: Last-In, First-Out).
 *   Functions:
 *     a. Visit new URL (Push onto stack)
 *     b. Go back to previous URL (Pop from stack)
 *     c. Display current page
 *     d. Display complete history
 * ============================================================================
 * ALGORITHM:
 *   1. Stack Initialization: array history[MAX], top = -1.
 *   2. Visit URL:
 *      - If top == MAX - 1, stack overflow.
 *      - Increment top and store URL: history[++top] = url.
 *   3. Back URL:
 *      - If top == -1, stack underflow (no previous page).
 *      - Decrement top: history[top--]. Active page becomes history[top].
 *   4. Display Current Page:
 *      - If top == -1, report empty stack. Else print history[top].
 *   5. Display History:
 *      - Loop backwards from top down to 0, printing each URL.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

const int MAX = 50;

class CatalogueNavigationStack {
private:
    string urls[MAX];
    int top;

public:
    CatalogueNavigationStack() : top(-1) {}

    bool isEmpty() { return (top == -1); }
    bool isFull()  { return (top == MAX - 1); }

    // a. Visit new URL
    void visitPage(string url) {
        if (isFull()) {
            cout << "Navigation history is full (Stack Overflow)!\n";
            return;
        }
        urls[++top] = url;
        cout << "[Navigated]: " << url << "\n";
    }

    // b. Go back to previous URL
    void backPage() {
        if (isEmpty()) {
            cout << "Cannot go back: Navigation history is empty (Stack Underflow)!\n";
            return;
        }
        cout << "[Back Button]: Leaving " << urls[top--] << "\n";
        displayCurrent();
    }

    // c. Display current active page
    void displayCurrent() {
        if (isEmpty()) {
            cout << "Current Page: Library Home Portal (History Empty)\n";
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
        cout << "\n--- Library Catalogue Navigation History (Top to Bottom) ---\n";
        for (int i = top; i >= 0; --i) {
            cout << "  [" << (i + 1) << "] " << urls[i];
            if (i == top) cout << "  <-- (Current View)";
            cout << "\n";
        }
        cout << "------------------------------------------------------------\n\n";
    }
};

int main() {
    cout << "==============================================================\n";
    cout << "  SET 1 (PART B - PROBLEM 1): CATALOGUE NAVIGATION STACK\n";
    cout << "==============================================================\n";

    CatalogueNavigationStack nav;

    // a. Visit URLs
    nav.visitPage("library.nmiet.edu.in");
    nav.visitPage("library.nmiet.edu.in/search?q=DataStructures");
    nav.visitPage("library.nmiet.edu.in/books/DS-101/details");
    nav.displayHistory();

    // b. Back to previous page
    nav.backPage();
    nav.displayHistory();

    // c. Current page
    nav.displayCurrent();

    return 0;
}
