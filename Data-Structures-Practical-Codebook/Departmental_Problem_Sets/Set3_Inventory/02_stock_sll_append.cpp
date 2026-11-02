/**
 * ============================================================================
 * Departmental Problem Set 3 (Inventory) - Problem 2
 * Program: Daily Stock Status using Singly Linked List (Append & Update)
 * ============================================================================
 * Problem Statement:
 *   Store daily stock status using a Singly Linked List:
 *   - Nodes store product_id and status ('A' = Available, 'O' = Out of Stock).
 *   - Operations:
 *     1. Append new product stock status
 *     2. Update stock status of a product by ID
 *     3. Count products currently 'A' (Available)
 *     4. Display all stock status records
 * ============================================================================
 */

#include <iostream>

using namespace std;

struct StockNode {
    int productId;
    char status; // 'A' = Available, 'O' = Out of Stock
    StockNode* next;

    StockNode(int id, char st) : productId(id), status(st), next(nullptr) {}
};

class StockStatusList {
private:
    StockNode* head;

public:
    StockStatusList() : head(nullptr) {}

    ~StockStatusList() {
        StockNode* curr = head;
        while (curr != nullptr) {
            StockNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    void append(int productId, char status) {
        StockNode* newNode = new StockNode(productId, status);
        if (head == nullptr) {
            head = newNode;
        } else {
            StockNode* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = newNode;
        }
        cout << "Appended: Product ID " << productId 
             << " [Status: " << (status == 'A' ? "Available" : "Out of Stock") << "]\n";
    }

    bool updateStatus(int productId, char newStatus) {
        StockNode* curr = head;
        while (curr != nullptr) {
            if (curr->productId == productId) {
                curr->status = newStatus;
                cout << "Updated: Product ID " << productId 
                     << " new status -> " << (newStatus == 'A' ? "Available" : "Out of Stock") << "\n";
                return true;
            }
            curr = curr->next;
        }
        cout << "Update Failed: Product ID " << productId << " not found.\n";
        return false;
    }

    int countAvailable() const {
        int count = 0;
        StockNode* curr = head;
        while (curr != nullptr) {
            if (curr->status == 'A') {
                count++;
            }
            curr = curr->next;
        }
        return count;
    }

    void display() const {
        if (head == nullptr) {
            cout << "Stock List is empty.\n";
            return;
        }
        cout << "\nDaily Stock Status Overview:\n";
        StockNode* curr = head;
        int index = 1;
        while (curr != nullptr) {
            cout << "  " << index++ << ". Product ID: " << curr->productId 
                 << " | Status: [" << curr->status << "] " 
                 << (curr->status == 'A' ? "Available" : "Out of Stock") << "\n";
            curr = curr->next;
        }
    }
};

int main() {
    StockStatusList stock;

    cout << "=== Daily Stock Status Tracking (SLL) ===\n\n";

    stock.append(601, 'A');
    stock.append(602, 'O');
    stock.append(603, 'A');
    stock.append(604, 'O');
    stock.append(605, 'A');

    stock.display();

    cout << "\nTotal Products Currently Available ('A'): " << stock.countAvailable() << "\n";

    cout << "\n--- Updating Restocked Product Status ---\n";
    stock.updateStatus(602, 'A'); // Restocked
    stock.updateStatus(603, 'O'); // Sold out

    stock.display();

    cout << "\nTotal Products Available ('A') After Update: " << stock.countAvailable() << "\n";

    return 0;
}
