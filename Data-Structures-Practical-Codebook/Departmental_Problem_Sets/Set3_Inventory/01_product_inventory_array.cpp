/**
 * ============================================================================
 * Departmental Problem Set 3 (Inventory) - Problem 1
 * Program: Product Inventory System using Array
 * ============================================================================
 * Problem Statement:
 *   Maintain product inventory using an array (id, name, quantity, price):
 *   a. Insert product at a specific position
 *   b. Delete product by ID
 *   c. Search product by ID
 *   d. Display all products
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_PRODUCTS = 50;

struct Product {
    int productId;
    string name;
    int quantity;
    double price;
};

class ProductInventory {
private:
    Product items[MAX_PRODUCTS];
    int size;

public:
    ProductInventory() : size(0) {}

    void insertAtPosition(int pos, int id, const string& name, int qty, double price) {
        if (size >= MAX_PRODUCTS) {
            cout << "Error: Inventory capacity reached.\n";
            return;
        }
        if (pos < 0 || pos > size) {
            cout << "Error: Invalid insertion position " << pos << ". Valid: [0, " << size << "].\n";
            return;
        }
        // Shift elements to right
        for (int i = size; i > pos; i--) {
            items[i] = items[i - 1];
        }
        items[pos] = {id, name, qty, price};
        size++;
        cout << "Inserted: Product [" << id << "] " << name << " at index " << pos << ".\n";
    }

    void deleteById(int targetId) {
        int targetIndex = -1;
        for (int i = 0; i < size; i++) {
            if (items[i].productId == targetId) {
                targetIndex = i;
                break;
            }
        }
        if (targetIndex == -1) {
            cout << "Delete Failed: Product ID " << targetId << " not found.\n";
            return;
        }
        cout << "Deleted: Product [" << items[targetIndex].productId << "] " 
             << items[targetIndex].name << " from index " << targetIndex << ".\n";
        // Shift left
        for (int i = targetIndex; i < size - 1; i++) {
            items[i] = items[i + 1];
        }
        size--;
    }

    int searchById(int targetId) const {
        for (int i = 0; i < size; i++) {
            if (items[i].productId == targetId) {
                return i;
            }
        }
        return -1;
    }

    void display() const {
        if (size == 0) {
            cout << "Inventory is empty.\n";
            return;
        }
        cout << "\n------------------ Current Product Inventory (" << size << " items) ------------------\n";
        cout << left << setw(8) << "Index" << setw(10) << "Prod ID" << setw(20) << "Product Name" 
             << setw(12) << "Quantity" << setw(12) << "Price (Rs.)" << "\n";
        cout << "----------------------------------------------------------------------\n";
        for (int i = 0; i < size; i++) {
            cout << left << setw(8) << i << setw(10) << items[i].productId 
                 << setw(20) << items[i].name << setw(12) << items[i].quantity 
                 << fixed << setprecision(2) << setw(12) << items[i].price << "\n";
        }
        cout << "----------------------------------------------------------------------\n";
    }
};

int main() {
    ProductInventory inventory;

    cout << "=== Inventory Management: Product Array System ===\n\n";

    // Insert initial products
    inventory.insertAtPosition(0, 501, "Wireless Mouse", 120, 799.00);
    inventory.insertAtPosition(1, 502, "Mechanical Keyboard", 45, 2499.00);
    inventory.insertAtPosition(2, 503, "USB-C Hub", 80, 1299.00);

    // Insert at specific position (pos = 1)
    inventory.insertAtPosition(1, 504, "Gaming Headset", 30, 3199.00);

    inventory.display();

    // Search by ID
    cout << "\n--- Search by Product ID ---\n";
    int searchId = 502;
    int idx = inventory.searchById(searchId);
    if (idx != -1) {
        cout << "Found Product ID " << searchId << " at index " << idx << ".\n";
    } else {
        cout << "Product ID " << searchId << " not found.\n";
    }

    // Delete by ID
    cout << "\n--- Delete Product by ID ---\n";
    inventory.deleteById(504);

    inventory.display();

    return 0;
}
