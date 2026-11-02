/**
 * ============================================================================
 * Departmental Problem Set 3 (Inventory) - Problem 6
 * Program: Warehouse Portal Navigation (Stack ADT using Array)
 * ============================================================================
 * Problem Statement:
 *   Simulate warehouse system navigation using a Stack (LIFO):
 *   - Push visited warehouse portal screen / bin location onto stack.
 *   - Pop to navigate back to previous screen.
 *   - Peek to check current active screen.
 *   - Display complete navigation breadcrumb history.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

const int MAX_STACK = 10;

class WarehouseNavigationStack {
private:
    string stack[MAX_STACK];
    int top;

public:
    WarehouseNavigationStack() : top(-1) {}

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == MAX_STACK - 1;
    }

    void push(const string& screen) {
        if (isFull()) {
            cout << "Stack Overflow: Navigation history full.\n";
            return;
        }
        stack[++top] = screen;
        cout << "Navigated to: " << screen << "\n";
    }

    void pop() {
        if (isEmpty()) {
            cout << "Navigation History Empty: Cannot go back.\n";
            return;
        }
        cout << "Navigating Back from: " << stack[top--] << "\n";
    }

    void peek() const {
        if (isEmpty()) {
            cout << "Current Screen: None (Portal closed)\n";
            return;
        }
        cout << "Active Screen: " << stack[top] << "\n";
    }

    void displayHistory() const {
        if (isEmpty()) {
            cout << "Navigation History: [Empty]\n";
            return;
        }
        cout << "\nNavigation Breadcrumbs (Top/Current -> Root):\n";
        for (int i = top; i >= 0; i--) {
            cout << "  " << (top - i + 1) << ". " << stack[i];
            if (i == top) cout << "  <-- CURRENT";
            cout << "\n";
        }
    }
};

int main() {
    WarehouseNavigationStack portal;

    cout << "=== Warehouse Portal Navigation System (Stack ADT) ===\n\n";

    portal.push("Warehouse Dashboard");
    portal.push("Inventory Section: Electronics");
    portal.push("Aisle 4: Peripherals");
    portal.push("Bin 12: Mechanical Keyboards");

    portal.displayHistory();

    cout << "\n--- Check Current Location ---\n";
    portal.peek();

    cout << "\n--- Back Navigation (Pop 2 Locations) ---\n";
    portal.pop();
    portal.pop();

    portal.displayHistory();

    cout << "\n--- Visit Alternate Aisle ---\n";
    portal.push("Aisle 7: Gaming Mice");
    portal.displayHistory();

    return 0;
}
