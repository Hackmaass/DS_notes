/**
 * ============================================================================
 * SET 2: HOSPITAL MANAGEMENT SYSTEM (Part A - Problem 2)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program using Singly Linked List for daily check-up status of 
 *   admitted patients (C = Completed, M = Missed).
 *   Functions:
 *     a. Insert at end
 *     b. Update status of a given day
 *     c. Calculate total completed check-ups ('C')
 *     d. Display complete list
 * ============================================================================
 */

#include <iostream>

using namespace std;

struct Node {
    int dayNumber;
    char status; // 'C' = Completed, 'M' = Missed
    Node* next;

    Node(int d, char s) : dayNumber(d), status(s), next(nullptr) {}
};

class DailyCheckupList {
private:
    Node* head;

public:
    DailyCheckupList() : head(nullptr) {}

    ~DailyCheckupList() {
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
                cout << "Updated Day " << day << " check-up status to '" << newStatus << "'.\n";
                return true;
            }
            temp = temp->next;
        }
        cout << "Day " << day << " record not found!\n";
        return false;
    }

    // c. Calculate total completed ('C')
    int countTotalCompleted() {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->status == 'C' || temp->status == 'c') {
                count++;
            }
            temp = temp->next;
        }
        return count;
    }

    // d. Display complete list
    void display() {
        if (head == nullptr) {
            cout << "Check-up list is empty.\n";
            return;
        }
        cout << "Patient Check-up Log: ";
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
    cout << "  SET 2 (PART A - PROBLEM 2): CHECK-UP SLL (INSERT AT END)\n";
    cout << "==============================================================\n";

    DailyCheckupList list;

    // a. Insert at end
    list.insertAtEnd(1, 'C');
    list.insertAtEnd(2, 'M');
    list.insertAtEnd(3, 'C');
    list.insertAtEnd(4, 'M');
    list.display();

    // b. Update Day 2 from 'M' to 'C'
    list.updateStatus(2, 'C');
    list.display();

    // c. Count total completed
    cout << "\nTotal completed check-ups ('C'): " << list.countTotalCompleted() << "\n";

    return 0;
}
