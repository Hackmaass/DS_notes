/**
 * ============================================================================
 * SET 2: HOSPITAL MANAGEMENT SYSTEM (Part A - Problem 4)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to maintain doctors sorted by Doctor ID using 
 *   Doubly Linked List.
 *   Functions:
 *     a. Insert doctor in sorted order
 *     b. Delete by Doctor ID
 *     c. Traverse forward
 *     d. Traverse backward
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

struct DoctorNode {
    int doctorId;
    string name;
    DoctorNode* prev;
    DoctorNode* next;

    DoctorNode(int id, string n) : doctorId(id), name(n), prev(nullptr), next(nullptr) {}
};

class SortedDoctorDLL {
private:
    DoctorNode* head;

public:
    SortedDoctorDLL() : head(nullptr) {}

    ~SortedDoctorDLL() {
        DoctorNode* curr = head;
        while (curr != nullptr) {
            DoctorNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    // a. Insert doctor in sorted order
    void sortedInsert(int id, string name) {
        DoctorNode* newNode = new DoctorNode(id, name);

        if (head == nullptr || id < head->doctorId) {
            newNode->next = head;
            if (head != nullptr) head->prev = newNode;
            head = newNode;
            cout << "Inserted Dr. " << name << " (ID: " << id << ") at head.\n";
            return;
        }

        DoctorNode* curr = head;
        while (curr->next != nullptr && curr->next->doctorId < id) {
            curr = curr->next;
        }

        newNode->next = curr->next;
        newNode->prev = curr;
        if (curr->next != nullptr) {
            curr->next->prev = newNode;
        }
        curr->next = newNode;

        cout << "Inserted Dr. " << name << " (ID: " << id << ") in sorted position.\n";
    }

    // b. Delete by Doctor ID
    bool deleteByDoctorId(int id) {
        if (head == nullptr) {
            cout << "Doctor registry is empty!\n";
            return false;
        }

        DoctorNode* curr = head;
        while (curr != nullptr && curr->doctorId != id) {
            curr = curr->next;
        }

        if (curr == nullptr) {
            cout << "Doctor ID " << id << " not found!\n";
            return false;
        }

        if (curr == head) {
            head = head->next;
            if (head != nullptr) head->prev = nullptr;
        } else {
            curr->prev->next = curr->next;
            if (curr->next != nullptr) {
                curr->next->prev = curr->prev;
            }
        }

        cout << "Deleted Doctor: " << curr->name << " (ID: " << id << ").\n";
        delete curr;
        return true;
    }

    // c. Traverse forward
    void traverseForward() {
        if (head == nullptr) {
            cout << "No doctors in registry.\n";
            return;
        }
        cout << "\nForward Traversal:  NULL <-> ";
        DoctorNode* temp = head;
        while (temp != nullptr) {
            cout << "[Dr. " << temp->doctorId << ": " << temp->name << "]";
            if (temp->next != nullptr) cout << " <-> ";
            temp = temp->next;
        }
        cout << " <-> NULL\n";
    }

    // d. Traverse backward
    void traverseBackward() {
        if (head == nullptr) {
            cout << "No doctors in registry.\n";
            return;
        }

        DoctorNode* tail = head;
        while (tail->next != nullptr) {
            tail = tail->next;
        }

        cout << "Backward Traversal: NULL <-> ";
        while (tail != nullptr) {
            cout << "[Dr. " << tail->doctorId << ": " << tail->name << "]";
            if (tail->prev != nullptr) cout << " <-> ";
            tail = tail->prev;
        }
        cout << " <-> NULL\n\n";
    }
};

int main() {
    cout << "==============================================================\n";
    cout << "  SET 2 (PART A - PROBLEM 4): SORTED DOCTORS (DOUBLY LINKED LIST)\n";
    cout << "==============================================================\n";

    SortedDoctorDLL dll;

    // a. Sorted insert
    dll.sortedInsert(503, "Mehta (Cardiology)");
    dll.sortedInsert(501, "Sharma (Neurology)");
    dll.sortedInsert(504, "Patil (Pediatrics)");
    dll.sortedInsert(502, "Joshi (Orthopedics)");

    // c & d. Forward and Backward
    dll.traverseForward();
    dll.traverseBackward();

    // b. Delete
    dll.deleteByDoctorId(503);
    dll.traverseForward();

    return 0;
}
