/**
 * ============================================================================
 * SET 1: LIBRARY MANAGEMENT SYSTEM (Part A - Problem 2)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program using Singly Linked List for daily return status of issued
 *   books where each node represents a day (R = Returned, N = Not Returned).
 *   Functions:
 *     a. Insert at end
 *     b. Update status of a given day
 *     c. Calculate total returned books ('R')
 *     d. Display complete list
 * ============================================================================
 * ALGORITHM:
 *   1. Node Definition: int dayNumber, char status ('R' or 'N'), Node* next.
 *   2. Insert at end:
 *      - Allocate new node. If head == NULL, set head = newNode.
 *      - Else traverse to tail node (temp->next == NULL), and set temp->next = newNode.
 *   3. Update status of given day:
 *      - Traverse list; if temp->dayNumber == targetDay, set temp->status = newStatus.
 *   4. Count Returned ('R'):
 *      - Traverse list; increment counter if temp->status == 'R' or 'r'.
 *   5. Display:
 *      - Traverse and print each node: [Day X: R] -> ... -> NULL.
 * ============================================================================
 */

#include <iostream>

using namespace std;

struct Node {
    int dayNumber;
    char status; // 'R' = Returned, 'N' = Not Returned
    Node* next;

    Node(int d, char s) : dayNumber(d), status(s), next(nullptr) {}
};

class DailyReturnList {
private:
    Node* head;

public:
    DailyReturnList() : head(nullptr) {}

    ~DailyReturnList() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    // a. Insert at end
    void insertAtEnd(int day, char status) {
        Node* newNode = new Node(day, status);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // b. Update given day status
    bool updateStatus(int day, char newStatus) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->dayNumber == day) {
                temp->status = newStatus;
                cout << "Updated Day " << day << " status to '" << newStatus << "'.\n";
                return true;
            }
            temp = temp->next;
        }
        cout << "Day " << day << " not found!\n";
        return false;
    }

    // c. Calculate total returned ('R')
    int countTotalReturned() {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->status == 'R' || temp->status == 'r') {
                count++;
            }
            temp = temp->next;
        }
        return count;
    }

    // d. Display complete list
    void display() {
        if (head == nullptr) {
            cout << "Return list is empty.\n";
            return;
        }
        cout << "Daily Return Log: ";
        Node* temp = head;
        while (temp != nullptr) {
            cout << "[Day " << temp->dayNumber << ": " << temp->status << "]";
            if (temp->next != nullptr) cout << " -> ";
            temp = temp->next;
        }
        cout << " -> NULL\n";
    }
};

int main() {
    cout << "==============================================================\n";
    cout << "  SET 1 (PART A - PROBLEM 2): RETURN STATUS SLL (INSERT AT END)\n";
    cout << "==============================================================\n";

    DailyReturnList list;

    // a. Insert at end
    list.insertAtEnd(1, 'R');
    list.insertAtEnd(2, 'N');
    list.insertAtEnd(3, 'R');
    list.insertAtEnd(4, 'N');
    list.display();

    // b. Update Day 2 from 'N' to 'R'
    list.updateStatus(2, 'R');
    list.display();

    // c. Count total returned
    cout << "\nTotal books returned ('R'): " << list.countTotalReturned() << "\n";

    return 0;
}
