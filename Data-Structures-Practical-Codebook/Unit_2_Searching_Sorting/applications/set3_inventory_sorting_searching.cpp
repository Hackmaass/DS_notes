/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit II: Searching & Sorting
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 3 - Inventory & Warehouse System (Searching & Sorting Suite)
 * TITLE:         Inventory System: Sales Ranking, Product Search, Quick & Bubble Sort
 * 
 * PROBLEMS COVERED:
 *   1. Product sales ranking (Selection & Insertion Sort descending, Top 5).
 *   2. Search product records: Linear Search by Name vs Binary Search by Product ID.
 *   3. Arrange unit prices of products using Quick Sort.
 *   4. Stock quantities: Selection & Bubble Sort. Top 5 highest stocks.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// PROBLEM 1: SALES RANKING
struct ProductSalesRank {
    int productId;
    string name;
    int salesUnits;
};

void selectionSortSalesDesc(ProductSalesRank arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int maxIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j].salesUnits > arr[maxIdx].salesUnits) maxIdx = j;
        }
        if (maxIdx != i) {
            ProductSalesRank temp = arr[i];
            arr[i] = arr[maxIdx];
            arr[maxIdx] = temp;
        }
    }
}

int insertionSortSalesDesc(ProductSalesRank arr[], int n) {
    int shifts = 0;
    for (int i = 1; i < n; ++i) {
        ProductSalesRank key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].salesUnits < key.salesUnits) {
            arr[j + 1] = arr[j];
            shifts++;
            j--;
        }
        arr[j + 1] = key;
    }
    return shifts;
}

// PROBLEM 2: SEARCH PRODUCT
struct ProductSearchRecord {
    int productId;
    string name;
    string category;
};

int linearSearchByProductName(const ProductSearchRecord arr[], int n, const string& target, int& comps) {
    comps = 0;
    for (int i = 0; i < n; ++i) {
        comps++;
        if (arr[i].name == target) return i;
    }
    return -1;
}

int binarySearchByProductId(const ProductSearchRecord arr[], int n, int id, int& comps) {
    comps = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        comps++;
        int mid = low + (high - low) / 2;
        if (arr[mid].productId == id) return mid;
        if (arr[mid].productId < id) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// PROBLEM 3: QUICK SORT UNIT PRICES
int partitionPrices(float arr[], int low, int high) {
    float pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            float temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    float temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSortPrices(float arr[], int low, int high) {
    if (low < high) {
        int pi = partitionPrices(arr, low, high);
        quickSortPrices(arr, low, pi - 1);
        quickSortPrices(arr, pi + 1, high);
    }
}

// PROBLEM 4: STOCK QUANTITIES BUBBLE SORT
void bubbleSortStockAsc(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

int main() {
    cout << "====================================================================\n";
    cout << "  SET 3: INVENTORY SYSTEM - SEARCHING & SORTING SUITE\n";
    cout << "====================================================================\n";

    // 1. Sales Ranking
    ProductSalesRank products[6] = {
        {101, "Screws M4       ", 450},
        {102, "Hex Bolts M8    ", 890},
        {103, "Steel Washers   ", 1250},
        {104, "Copper Rivets   ", 320},
        {105, "Threaded Rods   ", 710},
        {106, "Lock Nuts M10   ", 980}
    };
    ProductSalesRank copyP[6];
    for (int i = 0; i < 6; ++i) copyP[i] = products[i];

    selectionSortSalesDesc(products, 6);
    cout << "\n>>> TOP 5 BEST-SELLING PRODUCTS <<<\n";
    for (int i = 0; i < 5; ++i) {
        cout << "  #" << (i + 1) << " Product ID: " << products[i].productId 
             << " | Name: " << products[i].name 
             << " | Sales: " << products[i].salesUnits << " units\n";
    }

    int shifts = insertionSortSalesDesc(copyP, 6);
    cout << "Insertion Sort executed with " << shifts << " data shifts.\n";

    // 2. Search
    ProductSearchRecord catalog[5] = {
        {301, "Copper Rivets   ", "Fasteners"},
        {302, "Hex Bolts M8    ", "Fasteners"},
        {303, "Lock Nuts M10   ", "Nuts"},
        {304, "Screws M4       ", "Screws"},
        {305, "Steel Washers   ", "Washers"}
    };
    int comps = 0;
    int idx = linearSearchByProductName(catalog, 5, "Hex Bolts M8    ", comps);
    cout << "\nLinear Search for 'Hex Bolts M8': Found at Index " << idx 
         << " (" << comps << " comparisons)\n";

    idx = binarySearchByProductId(catalog, 5, 304, comps);
    cout << "Binary Search for Product ID 304: Found at Index " << idx 
         << " (" << comps << " comparisons)\n";

    // 3. Quick Sort Unit Prices
    float prices[6] = {25.50f, 110.00f, 4.25f, 65.00f, 18.75f, 45.00f};
    quickSortPrices(prices, 0, 5);
    cout << "\nSorted Unit Prices (Quick Sort): ";
    for (int i = 0; i < 6; ++i) cout << "Rs " << fixed << setprecision(2) << prices[i] << "  ";
    cout << "\n";

    // 4. Stock quantities Bubble Sort
    int stock[7] = {1200, 450, 3200, 850, 2100, 5000, 1600};
    bubbleSortStockAsc(stock, 7);
    cout << "\nTop 5 Highest Stock Quantities (Ascending Bubble Sort tail):\n";
    for (int i = 6; i >= 2; --i) {
        cout << "  #" << (7 - i) << ": " << stock[i] << " units in stock\n";
    }

    return 0;
}
