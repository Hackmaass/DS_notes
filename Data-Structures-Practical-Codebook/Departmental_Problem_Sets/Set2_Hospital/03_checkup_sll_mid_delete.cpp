/**
 * ============================================================================
 * SET 2: HOSPITAL MANAGEMENT SYSTEM (Part A - Problem 3)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to manage the same patient check-up status list using
 *   Singly Linked List.
 *   Functions:
 *     a. Insert in middle (after specified day)
 *     b. Delete from front
 *     c. Calculate total missed check-ups ('M')
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

class DailyCheckupListMidDelete {
private:
    Node* head;

public:
    DailyCheckupListMidDelete() : head(nullptr) {}

    ~DailyCheckupListMidDelete() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    void append(int day, char status) {
        Node* newNode = new Node(day, status);
        if (head == nullptr) { head = newNode; return; }
        Node* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newNode;
    }

    // a. Insert in middle (after specified day)
    bool insertInMiddle(int afterDay, int newDay, char status) {
        Node* temp = head;
        while (temp != nullptr && temp->dayNumber != afterDay) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Day " << afterDay << " not found!\n";
            return false;
        }

        Node* newNode = new Node(newDay, status);
        newNode->next = temp->next;
        temp->next = newNode;
        cout << "Inserted Day " << newDay << " after Day " << afterDay << ".\n";
        return true;
    }

    // b. Delete from front
    bool deleteFromFront() {
        if (head == nullptr) {
            cout << "List is empty!\n";
            return false;
        }

        Node* temp = head;
        head = head->next;
        cout << "Deleted Day " << temp->dayNumber << " (Status: " << temp->status << ") from front.\n";
        delete temp;
        return true;
    }

    // c. Calculate total missed check-ups ('M')
    int countTotalMissed() {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->status == 'M' || temp->status == 'm') {
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
    cout << "  SET 2 (PART A - PROBLEM 3): CHECK-UP SLL (MID INSERT & FRONT DELETE)\n";
    cout << "==============================================================\n";

    DailyCheckupListMidDelete list;

    list.append(1, 'C');
    list.append(2, 'M');
    list.append(3, 'M');
    list.display();

    // a. Insert in middle
    list.insertInMiddle(2, 4, 'C');
    list.display();

    // c. Count total missed
    cout << "\nTotal missed check-ups ('M'): " << list.countTotalMissed() << "\n\n";

    // b. Delete from front
    list.deleteFromFront();
    list.display();

    return 0;
}
