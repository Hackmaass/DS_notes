/**
 * ============================================================================
 * SET 2: HOSPITAL MANAGEMENT SYSTEM (Part A - Problem 5)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to store patient body temperature readings of N patients 
 *   using both an Array and a Linked List.
 *   Functions:
 *     a. Insert readings in both
 *     b. Display memory representation (indices and memory addresses)
 *     c. Calculate total patients with temperature > 100.0 F
 * ============================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

struct Node {
    int patientId;
    float temperature;
    Node* next;

    Node(int id, float temp) : patientId(id), temperature(temp), next(nullptr) {}
};

int main() {
    cout << "==============================================================\n";
    cout << "  SET 2 (PART A - PROBLEM 5): ARRAY VS LINKED LIST MEMORY\n";
    cout << "==============================================================\n";

    const int N = 5;
    int patientIds[N] = {201, 202, 203, 204, 205};
    float tempsArray[N] = {98.6f, 101.4f, 99.1f, 102.5f, 98.4f};

    // Linked List creation
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < N; ++i) {
        Node* newNode = new Node(patientIds[i], tempsArray[i]);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // b. Array memory display
    cout << "\n1. ARRAY MEMORY (Contiguous Stack Allocation):\n";
    cout << "   " << left << setw(8) << "Index" << setw(14) << "Patient ID" 
         << setw(16) << "Temperature" << "Memory Address (Hex)\n";
    cout << "   ---------------------------------------------------------\n";
    int arrayFever = 0;
    for (int i = 0; i < N; ++i) {
        cout << "   " << left << setw(8) << i 
             << setw(14) << patientIds[i] 
             << fixed << setprecision(1) << setw(16) << tempsArray[i] 
             << &tempsArray[i] << "\n";
        if (tempsArray[i] > 100.0f) arrayFever++;
    }

    // b. Linked List memory display
    cout << "\n2. LINKED LIST MEMORY (Non-Contiguous Heap Allocation):\n";
    cout << "   " << left << setw(8) << "Node" << setw(14) << "Patient ID" 
         << setw(16) << "Temperature" << setw(20) << "Node Address" << "Next Pointer\n";
    cout << "   -------------------------------------------------------------------------\n";
    int llFever = 0;
    int nodeNum = 1;
    Node* curr = head;
    while (curr != nullptr) {
        cout << "   " << left << setw(8) << nodeNum 
             << setw(14) << curr->patientId 
             << fixed << setprecision(1) << setw(16) << curr->temperature 
             << setw(20) << curr 
             << curr->next << "\n";
        if (curr->temperature > 100.0f) llFever++;
        curr = curr->next;
        nodeNum++;
    }

    // c. Total patients with fever
    cout << "\n3. RESULTS:\n";
    cout << "   -> Patients with fever > 100.0 F (Array check)       : " << arrayFever << "\n";
    cout << "   -> Patients with fever > 100.0 F (Linked List check) : " << llFever << "\n";

    // Clean up
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
