/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit I: Arrays & Linked Lists
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 3 - Inventory & Warehouse Management System (Part A Suite)
 * TITLE:         Inventory System: Arrays, SLL, Sorted DLL, and Memory Representation
 * 
 * PROBLEM STATEMENTS COVERED:
 *   1. Array: Maintain records of N products (Product ID, Name, Quantity).
 *      a. Insert at position, b. Delete by ID, c. Search by ID, d. Display all.
 *   2. SLL: Daily stock status (A=Available / O=Out of stock).
 *      a. Insert at end, b. Update given day, c. Calculate total available days, d. Display all.
 *   3. SLL: Same list.
 *      a. Insert in middle, b. Delete from front, c. Calculate total out-of-stock days, d. Display all.
 *   4. DLL: Suppliers sorted by Supplier ID.
 *      a. Sorted insert, b. Delete by Supplier ID, c. Forward traversal, d. Backward traversal.
 *   5. Array vs LL: Monthly sales units of N products.
 *      a. Insert in both, b. Display memory representation, c. Count products sold > 500 units.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// PART 1: ARRAY - PRODUCTS SYSTEM (Problem 1)
struct Product {
    int productId;
    string productName;
    int quantity;
};

class ProductArraySystem {
private:
    Product products[50];
    int size;

public:
    ProductArraySystem() : size(0) {}

    bool insertAtPosition(int pos, int id, const string& name, int qty) {
        if (size >= 50 || pos < 1 || pos > size + 1) return false;
        for (int i = size; i >= pos; --i) products[i] = products[i - 1];
        products[pos - 1] = {id, name, qty};
        size++;
        return true;
    }

    bool deleteByProductId(int id) {
        int idx = -1;
        for (int i = 0; i < size; ++i) {
            if (products[i].productId == id) { idx = i; break; }
        }
        if (idx == -1) return false;
        for (int i = idx; i < size - 1; ++i) products[i] = products[i + 1];
        size--;
        return true;
    }

    int searchByProductId(int id) const {
        for (int i = 0; i < size; ++i) {
            if (products[i].productId == id) {
                cout << "  [FOUND] Product ID: " << products[i].productId 
                     << " | Name: " << products[i].productName 
                     << " | Qty: " << products[i].quantity << "\n";
                return i;
            }
        }
        return -1;
    }

    void displayAll() const {
        cout << "\n  --- WAREHOUSE PRODUCT INVENTORY (Array) ---\n";
        cout << "  " << left << setw(6) << "Pos" << setw(12) << "Product ID" 
             << setw(25) << "Product Name" << "Stock Qty\n";
        cout << "  --------------------------------------------------\n";
        for (int i = 0; i < size; ++i) {
            cout << "  " << left << setw(6) << (i + 1)
                 << setw(12) << products[i].productId
                 << setw(25) << products[i].productName
                 << products[i].quantity << "\n";
        }
        cout << "\n";
    }
};

// PART 2: SLL - STOCK STATUS (Problems 2 & 3)
struct StockNode {
    int dayNumber;
    char status; // 'A' = Available, 'O' = Out of stock
    StockNode* next;
    StockNode(int d, char s) : dayNumber(d), status(s), next(nullptr) {}
};

class StockStatusSLL {
private:
    StockNode* head;

public:
    StockStatusSLL() : head(nullptr) {}
    ~StockStatusSLL() {
        while (head != nullptr) {
            StockNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertAtEnd(int day, char status) {
        StockNode* nn = new StockNode(day, status);
        if (head == nullptr) { head = nn; return; }
        StockNode* t = head;
        while (t->next != nullptr) t = t->next;
        t->next = nn;
    }

    bool insertInMiddle(int afterDay, int newDay, char status) {
        StockNode* t = head;
        while (t != nullptr && t->dayNumber != afterDay) t = t->next;
        if (t == nullptr) return false;
        StockNode* nn = new StockNode(newDay, status);
        nn->next = t->next;
        t->next = nn;
        return true;
    }

    bool deleteFromFront() {
        if (head == nullptr) return false;
        StockNode* t = head;
        head = head->next;
        delete t;
        return true;
    }

    bool updateStatus(int day, char status) {
        StockNode* t = head;
        while (t != nullptr) {
            if (t->dayNumber == day) { t->status = status; return true; }
            t = t->next;
        }
        return false;
    }

    int countAvailable() const {
        int cnt = 0;
        StockNode* t = head;
        while (t != nullptr) {
            if (t->status == 'A' || t->status == 'a') cnt++;
            t = t->next;
        }
        return cnt;
    }

    int countOutOfStock() const {
        int cnt = 0;
        StockNode* t = head;
        while (t != nullptr) {
            if (t->status == 'O' || t->status == 'o') cnt++;
            t = t->next;
        }
        return cnt;
    }

    void displayList() const {
        cout << "  [STOCK LOG]: ";
        StockNode* t = head;
        while (t != nullptr) {
            cout << "[Day " << t->dayNumber << ": " << t->status << "]";
            if (t->next != nullptr) cout << " -> ";
            t = t->next;
        }
        cout << " -> NULL\n";
    }
};

// PART 3: DLL - SORTED SUPPLIERS (Problem 4)
struct SupplierNode {
    int supplierId;
    string supplierName;
    SupplierNode* prev;
    SupplierNode* next;
    SupplierNode(int id, const string& name) 
        : supplierId(id), supplierName(name), prev(nullptr), next(nullptr) {}
};

class SortedSupplierDLL {
private:
    SupplierNode* head;

public:
    SortedSupplierDLL() : head(nullptr) {}
    ~SortedSupplierDLL() {
        while (head != nullptr) {
            SupplierNode* t = head;
            head = head->next;
            delete t;
        }
    }

    void sortedInsert(int id, const string& name) {
        SupplierNode* nn = new SupplierNode(id, name);
        if (head == nullptr || id < head->supplierId) {
            nn->next = head;
            if (head != nullptr) head->prev = nn;
            head = nn;
            return;
        }
        SupplierNode* curr = head;
        while (curr->next != nullptr && curr->next->supplierId < id) {
            curr = curr->next;
        }
        nn->next = curr->next;
        nn->prev = curr;
        if (curr->next != nullptr) curr->next->prev = nn;
        curr->next = nn;
    }

    bool deleteBySupplierId(int id) {
        SupplierNode* curr = head;
        while (curr != nullptr && curr->supplierId != id) curr = curr->next;
        if (curr == nullptr) return false;
        if (curr == head) {
            head = head->next;
            if (head != nullptr) head->prev = nullptr;
        } else {
            curr->prev->next = curr->next;
            if (curr->next != nullptr) curr->next->prev = curr->prev;
        }
        delete curr;
        return true;
    }

    void displayForward() const {
        cout << "  [FORWARD SUPPLIER DLL]  NULL <-> ";
        SupplierNode* t = head;
        while (t != nullptr) {
            cout << "[" << t->supplierId << ": " << t->supplierName << "]";
            if (t->next != nullptr) cout << " <-> ";
            t = t->next;
        }
        cout << " <-> NULL\n";
    }

    void displayBackward() const {
        SupplierNode* tail = head;
        if (tail == nullptr) return;
        while (tail->next != nullptr) tail = tail->next;
        cout << "  [BACKWARD SUPPLIER DLL] NULL <-> ";
        while (tail != nullptr) {
            cout << "[" << tail->supplierId << ": " << tail->supplierName << "]";
            if (tail->prev != nullptr) cout << " <-> ";
            tail = tail->prev;
        }
        cout << " <-> NULL\n";
    }
};

// PART 4: ARRAY VS LINKED LIST - MONTHLY SALES (Problem 5)
struct SalesNode {
    int productId;
    int salesUnits;
    SalesNode* next;
    SalesNode(int id, int s) : productId(id), salesUnits(s), next(nullptr) {}
};

void runMemoryComparisonSales() {
    cout << "\n====================================================================\n";
    cout << "  PROBLEM 5: ARRAY VS LINKED LIST MEMORY (Product Sales Units)\n";
    cout << "====================================================================\n";

    const int N = 5;
    int ids[N] = {301, 302, 303, 304, 305};
    int sales[N] = {420, 780, 250, 910, 520};

    SalesNode* head = nullptr;
    SalesNode* tail = nullptr;
    for (int i = 0; i < N; ++i) {
        SalesNode* nn = new SalesNode(ids[i], sales[i]);
        if (head == nullptr) { head = tail = nn; }
        else { tail->next = nn; tail = nn; }
    }

    cout << "\n1. Array Contiguous Memory Addresses (Stack):\n";
    int highSalesArray = 0;
    for (int i = 0; i < N; ++i) {
        cout << "   Index " << i << " | Product " << ids[i] << " | Sales: " 
             << sales[i] << " units | Addr: " << &sales[i] << "\n";
        if (sales[i] > 500) highSalesArray++;
    }

    cout << "\n2. Linked List Heap Memory Addresses (Heap Nodes):\n";
    int highSalesLL = 0;
    SalesNode* curr = head;
    while (curr != nullptr) {
        cout << "   Product " << curr->productId << " | Sales: " << curr->salesUnits 
             << " units | Node Addr: " << curr << " | Next: " << curr->next << "\n";
        if (curr->salesUnits > 500) highSalesLL++;
        curr = curr->next;
    }

    cout << "\n3. Count of Products with Sales > 500 Units:\n";
    cout << "   -> From Array: " << highSalesArray << " | From LL: " << highSalesLL << "\n";

    while (head != nullptr) {
        SalesNode* t = head;
        head = head->next;
        delete t;
    }
}

int main() {
    cout << "====================================================================\n";
    cout << "  SET 3: INVENTORY & WAREHOUSE SYSTEM - COMPLETE UNIT 1 SUITE\n";
    cout << "====================================================================\n";

    // 1. Array
    ProductArraySystem pas;
    pas.insertAtPosition(1, 101, "Industrial Screws", 1500);
    pas.insertAtPosition(2, 102, "Hex Bolts M8", 850);
    pas.insertAtPosition(2, 103, "Steel Washers", 2400);
    pas.displayAll();
    pas.searchByProductId(103);
    pas.deleteByProductId(102);
    pas.displayAll();

    // 2. SLL
    StockStatusSLL sll;
    sll.insertAtEnd(1, 'A');
    sll.insertAtEnd(2, 'O');
    sll.insertAtEnd(3, 'A');
    sll.displayList();
    sll.insertInMiddle(2, 4, 'A');
    sll.displayList();
    sll.updateStatus(2, 'A');
    sll.displayList();
    cout << "Available Days: " << sll.countAvailable() << " | Out of Stock Days: " << sll.countOutOfStock() << "\n";
    sll.deleteFromFront();
    sll.displayList();

    // 3. DLL
    SortedSupplierDLL dll;
    dll.sortedInsert(403, "Tata Steel Logistics");
    dll.sortedInsert(401, "Bharat Forge Components");
    dll.sortedInsert(404, "Kirloskar Metals");
    dll.sortedInsert(402, "Mahindra Logistics");
    dll.displayForward();
    dll.displayBackward();
    dll.deleteBySupplierId(403);
    dll.displayForward();

    // 4. Memory comparison
    runMemoryComparisonSales();

    return 0;
}
