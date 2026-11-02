/**
 * ============================================================================
 * Departmental Problem Set 3 (Inventory) - Problem 12
 * Program: Product Record Search (Linear Search vs Binary Search)
 * ============================================================================
 * Problem Statement:
 *   Store an array of product records (Product ID, Name, Category):
 *   - Implement Linear Search to find a product by Name.
 *   - Implement Binary Search to find a product by Product ID (on sorted array).
 *   - Display comparison counts for both search methods.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

struct ProductItem {
    int productId;
    string name;
    string category;
};

void displayProducts(const ProductItem arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "  [" << i << "] ID: " << arr[i].productId 
             << " | Name: " << arr[i].name 
             << " | Category: " << arr[i].category << "\n";
    }
}

// Linear Search by Product Name
int linearSearchByName(const ProductItem arr[], int n, const string& targetName, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        if (arr[i].name == targetName) {
            return i;
        }
    }
    return -1;
}

// Binary Search by Product ID (Requires sorted array by productId)
int binarySearchById(const ProductItem arr[], int n, int targetId, int& comparisons) {
    comparisons = 0;
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;

        if (arr[mid].productId == targetId) {
            return mid;
        } else if (arr[mid].productId < targetId) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    const int N = 6;
    // Sorted by Product ID for Binary Search compatibility
    ProductItem catalog[N] = {
        {102, "USB-C Cable",     "Accessories"},
        {205, "Wireless Mouse",  "Peripherals"},
        {310, "Desk Lamp",       "Office Supply"},
        {420, "Webcam 1080p",    "Audio/Video"},
        {530, "Mechanical Keys", "Peripherals"},
        {640, "Monitor Arm",     "Furniture"}
    };

    cout << "=== Product Catalog Database ===\n";
    displayProducts(catalog, N);

    cout << "\n--- 1. Linear Search by Product Name ---\n";
    string searchName = "Webcam 1080p";
    int linearComparisons = 0;
    int indexName = linearSearchByName(catalog, N, searchName, linearComparisons);

    if (indexName != -1) {
        cout << "  Found '" << searchName << "' at index " << indexName << ".\n";
        cout << "  Category: " << catalog[indexName].category 
             << " | Product ID: " << catalog[indexName].productId << "\n";
    } else {
        cout << "  Product '" << searchName << "' not found.\n";
    }
    cout << "  Linear Search Total Comparisons: " << linearComparisons << " (O(N) time)\n";

    cout << "\n--- 2. Binary Search by Product ID ---\n";
    int searchId = 530;
    int binaryComparisons = 0;
    int indexId = binarySearchById(catalog, N, searchId, binaryComparisons);

    if (indexId != -1) {
        cout << "  Found Product ID " << searchId << " at index " << indexId << ".\n";
        cout << "  Name: " << catalog[indexId].name 
             << " | Category: " << catalog[indexId].category << "\n";
    } else {
        cout << "  Product ID " << searchId << " not found in catalog.\n";
    }
    cout << "  Binary Search Total Comparisons: " << binaryComparisons << " (O(log N) time)\n";

    return 0;
}
