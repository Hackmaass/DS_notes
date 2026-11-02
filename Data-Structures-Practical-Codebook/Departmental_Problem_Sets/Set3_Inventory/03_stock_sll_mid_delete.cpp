/**
 * ============================================================================
 * Departmental Problem Set 3 (Inventory) - Problem 3
 * Program: Stock Inward/Outward SLL (Insert at Position & Delete Front)
 * ============================================================================
 * Problem Statement:
 *   Manage warehouse stock flow using a Singly Linked List:
 *   - Insert product at a specified position (middle insertion).
 *   - Delete product from front (dispatching oldest stock item).
 *   - Count products marked 'O' (Out of Stock).
 *   - Display current warehouse stock queue.
 * ============================================================================
 */

#include <iostream>

using namespace std;

struct StockItemNode {
    int productId;
    char status; // 'A' = Available, 'O' = Out of Stock
    StockItemNode* next;

    StockItemNode(int id, char st) : productId(id), status(st), next(nullptr) {}
};

class WarehouseStockList {
private:
    StockItemNode* head;

public:
    WarehouseStockList() : head(nullptr) {}

    ~WarehouseStockList() {
        StockItemNode* curr = head;
        while (curr != nullptr) {
            StockItemNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    // Insert at specific 1-based position
    void insertAtPosition(int position, int productId, char status) {
        if (position < 1) {
            cout << "Invalid position. Position must be >= 1.\n";
            return;
        }
        StockItemNode* newNode = new StockItemNode(productId, status);

        if (position == 1) {
            newNode->next = head;
            head = newNode;
            cout << "Inserted at front (Pos 1): Product ID " << productId << "\n";
            return;
        }

        StockItemNode* curr = head;
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
        cout << "Inserted at Position " << position << ": Product ID " << productId << "\n";
    }

    // Delete from front (dispatching oldest arrival)
    void deleteFront() {
        if (head == nullptr) {
            cout << "Dispatch Failed: Warehouse stock list is empty.\n";
            return;
        }
        StockItemNode* temp = head;
        head = head->next;
        cout << "Dispatched (Deleted Front): Product ID " << temp->productId 
             << " [Status: " << temp->status << "]\n";
        delete temp;
    }

    // Count products out-of-stock ('O')
    int countOutOfStock() const {
        int count = 0;
        StockItemNode* curr = head;
        while (curr != nullptr) {
            if (curr->status == 'O') {
                count++;
            }
            curr = curr->next;
        }
        return count;
    }

    void display() const {
        if (head == nullptr) {
            cout << "Warehouse Stock List: [Empty]\n";
            return;
        }
        cout << "Warehouse Stock Pipeline (Head -> Tail):\n  ";
        StockItemNode* curr = head;
        while (curr != nullptr) {
            cout << "[" << curr->productId << " | " << curr->status << "]";
            if (curr->next != nullptr) cout << " -> ";
            curr = curr->next;
        }
        cout << " -> NULL\n";
    }
};

int main() {
    WarehouseStockList warehouse;

    cout << "=== Warehouse Stock Inward/Outward SLL ===\n\n";

    // Insert initial items
    warehouse.insertAtPosition(1, 701, 'A');
    warehouse.insertAtPosition(2, 702, 'O');
    warehouse.insertAtPosition(3, 703, 'O');

    warehouse.display();

    // Insert at middle position (Pos 2)
    cout << "\n--- Inward Rush Order (Insert at Middle Pos 2) ---\n";
    warehouse.insertAtPosition(2, 705, 'A');
    warehouse.display();

    cout << "\nTotal Out-of-Stock ('O') Items: " << warehouse.countOutOfStock() << "\n";

    // Delete from front (Dispatching oldest item)
    cout << "\n--- Dispatching Oldest Stock (Delete Front) ---\n";
    warehouse.deleteFront();
    warehouse.display();

    cout << "\nTotal Out-of-Stock ('O') Items After Dispatch: " << warehouse.countOutOfStock() << "\n";

    return 0;
}
