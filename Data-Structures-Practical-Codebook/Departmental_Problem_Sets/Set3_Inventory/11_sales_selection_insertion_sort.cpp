/**
 * ============================================================================
 * Departmental Problem Set 3 (Inventory) - Problem 11
 * Program: Best-Seller Ranking by Sales Units (Selection & Insertion Sort)
 * ============================================================================
 * Problem Statement:
 *   Manage an array of product sales units:
 *   - Sort sales units in descending order using Selection Sort (highest first).
 *   - Sort using Insertion Sort and count total comparisons and shifts.
 *   - Display top 5 best-selling products.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

struct ProductSalesRecord {
    int productId;
    string name;
    int unitsSold;
};

void displayProducts(const ProductSalesRecord arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "  ID: " << arr[i].productId << " | " << arr[i].name 
             << " | Units Sold: " << arr[i].unitsSold << "\n";
    }
}

// Selection Sort: Descending (Largest element moved to front)
void selectionSortDescending(ProductSalesRecord arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].unitsSold > arr[maxIdx].unitsSold) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            ProductSalesRecord temp = arr[i];
            arr[i] = arr[maxIdx];
            arr[maxIdx] = temp;
        }
    }
}

// Insertion Sort: Descending with metrics
void insertionSortDescending(ProductSalesRecord arr[], int n, int& comparisons, int& shifts) {
    comparisons = 0;
    shifts = 0;

    for (int i = 1; i < n; i++) {
        ProductSalesRecord key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            comparisons++;
            if (arr[j].unitsSold < key.unitsSold) {
                arr[j + 1] = arr[j];
                shifts++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

void displayTop5BestSellers(const ProductSalesRecord arr[], int n) {
    int limit = (n < 5) ? n : 5;
    cout << "\n=== Top " << limit << " Best-Selling Products ===\n";
    for (int i = 0; i < limit; i++) {
        cout << "  Rank " << (i + 1) << ": " << arr[i].name 
             << " (ID: " << arr[i].productId << ") - " << arr[i].unitsSold << " units sold\n";
    }
}

int main() {
    const int N = 7;
    ProductSalesRecord original[N] = {
        {101, "Wireless Mouse",     450},
        {102, "Mechanical Keyboard", 820},
        {103, "USB-C Cable",        1200},
        {104, "Gaming Headset",     310},
        {105, "Monitor Stand",      640},
        {106, "Webcam 1080p",       950},
        {107, "Laptop Sleeve",      180}
    };

    ProductSalesRecord arrSelection[N];
    ProductSalesRecord arrInsertion[N];
    for (int i = 0; i < N; i++) {
        arrSelection[i] = original[i];
        arrInsertion[i] = original[i];
    }

    cout << "=== Initial Product Sales Records ===\n";
    displayProducts(original, N);

    cout << "\n--- 1. Selection Sort (Descending Order by Units Sold) ---\n";
    selectionSortDescending(arrSelection, N);
    displayProducts(arrSelection, N);

    cout << "\n--- 2. Insertion Sort (Descending Order by Units Sold) ---\n";
    int comparisons = 0, shifts = 0;
    insertionSortDescending(arrInsertion, N, comparisons, shifts);
    displayProducts(arrInsertion, N);
    cout << "  Metrics: Comparisons = " << comparisons << ", Shifts = " << shifts << "\n";

    // Display Top 5 Best Sellers
    displayTop5BestSellers(arrSelection, N);

    return 0;
}
