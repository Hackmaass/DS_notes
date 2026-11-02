/**
 * ============================================================================
 * Departmental Problem Set 3 (Inventory) - Problem 5
 * Program: Monthly Sales Units - Array vs Linked List Comparison
 * ============================================================================
 * Problem Statement:
 *   Store monthly sales units of products (product_id, units_sold):
 *   - Implement both Array and Singly Linked List representations.
 *   - Compare memory layout (contiguous addresses vs scattered heap nodes).
 *   - Count products with monthly sales > 500 units in both structures.
 * ============================================================================
 */

#include <iostream>

using namespace std;

// Representation 1: Array Structure
struct ProductSale {
    int productId;
    int unitsSold;
};

// Representation 2: Singly Linked List Node
struct SaleNode {
    int productId;
    int unitsSold;
    SaleNode* next;

    SaleNode(int id, int units) : productId(id), unitsSold(units), next(nullptr) {}
};

int main() {
    cout << "=== Monthly Product Sales: Array vs Linked List ===\n\n";

    // ----------------------------------------------------
    // 1. ARRAY IMPLEMENTATION
    // ----------------------------------------------------
    const int N = 5;
    ProductSale salesArray[N] = {
        {101, 450},
        {102, 720},
        {103, 310},
        {104, 890},
        {105, 540}
    };

    cout << "--- 1. Array Representation (Contiguous Memory) ---\n";
    int arrayHighSalesCount = 0;
    for (int i = 0; i < N; i++) {
        cout << "  Index [" << i << "] Addr: " << (void*)&salesArray[i]
             << " | Prod ID: " << salesArray[i].productId 
             << " | Units: " << salesArray[i].unitsSold << "\n";
        if (salesArray[i].unitsSold > 500) {
            arrayHighSalesCount++;
        }
    }
    cout << "  Products with sales > 500 units (Array): " << arrayHighSalesCount << "\n\n";

    // ----------------------------------------------------
    // 2. LINKED LIST IMPLEMENTATION
    // ----------------------------------------------------
    SaleNode* head = new SaleNode(101, 450);
    head->next = new SaleNode(102, 720);
    head->next->next = new SaleNode(103, 310);
    head->next->next->next = new SaleNode(104, 890);
    head->next->next->next->next = new SaleNode(105, 540);

    cout << "--- 2. Linked List Representation (Scattered Heap Nodes) ---\n";
    int llHighSalesCount = 0;
    SaleNode* curr = head;
    int nodeIdx = 1;
    while (curr != nullptr) {
        cout << "  Node #" << nodeIdx++ << " Addr: " << (void*)curr 
             << " | Prod ID: " << curr->productId 
             << " | Units: " << curr->unitsSold 
             << " | Next Addr: " << (void*)curr->next << "\n";
        if (curr->unitsSold > 500) {
            llHighSalesCount++;
        }
        curr = curr->next;
    }
    cout << "  Products with sales > 500 units (Linked List): " << llHighSalesCount << "\n\n";

    // ----------------------------------------------------
    // 3. COMPARATIVE ANALYSIS
    // ----------------------------------------------------
    cout << "=== Memory Layout & Architectural Comparison ===\n";
    cout << "1. Memory Structure:\n";
    cout << "   - Array: Contiguous memory chunk (high cache locality, O(1) random access).\n";
    cout << "   - Linked List: Non-contiguous heap nodes connected by pointers (extra memory per pointer).\n";
    cout << "2. Insertion / Deletion:\n";
    cout << "   - Array: O(N) due to shifting elements.\n";
    cout << "   - Linked List: O(1) pointer updates if position is known.\n";
    cout << "3. Element Size:\n";
    cout << "   - Array element: " << sizeof(ProductSale) << " bytes.\n";
    cout << "   - Linked list node: " << sizeof(SaleNode) << " bytes (includes 8-byte pointer).\n";

    // Free Linked List memory
    curr = head;
    while (curr != nullptr) {
        SaleNode* temp = curr;
        curr = curr->next;
        delete temp;
    }

    return 0;
}
