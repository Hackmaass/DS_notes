/**
 * ============================================================================
 * Departmental Problem Set 3 (Inventory) - Problem 4
 * Program: Supplier Management using Doubly Linked List (Sorted by ID)
 * ============================================================================
 * Problem Statement:
 *   Maintain suppliers using a Doubly Linked List (DLL):
 *   - Nodes store supplier_id, name, and rating (1.0 to 5.0).
 *   - Insert suppliers in ascending sorted order of supplier_id.
 *   - Delete supplier by ID.
 *   - Display suppliers in both forward and backward directions.
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct SupplierNode {
    int supplierId;
    string name;
    float rating;
    SupplierNode* prev;
    SupplierNode* next;

    SupplierNode(int id, const string& n, float r)
        : supplierId(id), name(n), rating(r), prev(nullptr), next(nullptr) {}
};

class SupplierDLL {
private:
    SupplierNode* head;
    SupplierNode* tail;

public:
    SupplierDLL() : head(nullptr), tail(nullptr) {}

    ~SupplierDLL() {
        SupplierNode* curr = head;
        while (curr != nullptr) {
            SupplierNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    void insertSorted(int id, const string& name, float rating) {
        SupplierNode* newNode = new SupplierNode(id, name, rating);

        if (head == nullptr) {
            head = tail = newNode;
            cout << "Inserted Supplier ID " << id << " (" << name << ") as first record.\n";
            return;
        }

        // Insert at beginning
        if (id < head->supplierId) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            cout << "Inserted Supplier ID " << id << " (" << name << ") at head.\n";
            return;
        }

        // Insert at end
        if (id > tail->supplierId) {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
            cout << "Inserted Supplier ID " << id << " (" << name << ") at tail.\n";
            return;
        }

        // Insert in middle
        SupplierNode* curr = head;
        while (curr != nullptr && curr->supplierId < id) {
            curr = curr->next;
        }

        newNode->next = curr;
        newNode->prev = curr->prev;
        curr->prev->next = newNode;
        curr->prev = newNode;
        cout << "Inserted Supplier ID " << id << " (" << name << ") in sorted position.\n";
    }

    void deleteById(int targetId) {
        if (head == nullptr) {
            cout << "Delete Failed: Supplier list is empty.\n";
            return;
        }

        SupplierNode* curr = head;
        while (curr != nullptr && curr->supplierId != targetId) {
            curr = curr->next;
        }

        if (curr == nullptr) {
            cout << "Delete Failed: Supplier ID " << targetId << " not found.\n";
            return;
        }

        cout << "Deleted Supplier ID " << curr->supplierId << " (" << curr->name << ").\n";

        if (curr == head && curr == tail) {
            head = tail = nullptr;
        } else if (curr == head) {
            head = head->next;
            head->prev = nullptr;
        } else if (curr == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

        delete curr;
    }

    void displayForward() const {
        if (head == nullptr) {
            cout << "Supplier List: [Empty]\n";
            return;
        }
        cout << "\nSuppliers Directory (Forward: Head -> Tail):\n";
        SupplierNode* curr = head;
        while (curr != nullptr) {
            cout << "  [ID: " << curr->supplierId << "] " << curr->name 
                 << " | Rating: " << fixed << setprecision(1) << curr->rating << "/5.0\n";
            curr = curr->next;
        }
    }

    void displayBackward() const {
        if (tail == nullptr) {
            cout << "Supplier List: [Empty]\n";
            return;
        }
        cout << "\nSuppliers Directory (Backward: Tail -> Head):\n";
        SupplierNode* curr = tail;
        while (curr != nullptr) {
            cout << "  [ID: " << curr->supplierId << "] " << curr->name 
                 << " | Rating: " << fixed << setprecision(1) << curr->rating << "/5.0\n";
            curr = curr->prev;
        }
    }
};

int main() {
    SupplierDLL registry;

    cout << "=== Supplier Management (Sorted Doubly Linked List) ===\n\n";

    registry.insertSorted(302, "Apex Logistics", 4.6f);
    registry.insertSorted(105, "Global Chipsets", 4.9f);
    registry.insertSorted(450, "Zenith Plastics", 4.2f);
    registry.insertSorted(210, "Metro Packaging", 3.8f);

    registry.displayForward();
    registry.displayBackward();

    cout << "\n--- Deleting Supplier ID 210 ---\n";
    registry.deleteById(210);

    registry.displayForward();

    return 0;
}
