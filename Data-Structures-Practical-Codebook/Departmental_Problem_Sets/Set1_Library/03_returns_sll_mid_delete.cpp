/**
 * ============================================================================
 * SET 1: LIBRARY MANAGEMENT SYSTEM (Part A - Problem 3)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to manage the same list of books return status using 
 *   Singly Linked List.
 *   Functions:
 *     a. Insert in middle (after a specified day)
 *     b. Delete from front
 *     c. Calculate total not returned books ('N')
 *     d. Display complete list
 * ============================================================================
 * ALGORITHM:
 *   1. Insert in middle (afterDay, newDay, status):
 *      - Search node where temp->dayNumber == afterDay.
 *      - Allocate newNode(newDay, status).
 *      - Link: newNode->next = temp->next; temp->next = newNode.
 *   2. Delete from front:
 *      - If head == NULL, list is empty.
 *      - Save current head in 'temp'.
 *      - Move head forward: head = head->next.
 *      - Free memory: delete temp.
 *   3. Count Not Returned ('N'):
 *      - Traverse list; increment count if temp->status == 'N' or 'n'.
 *   4. Display:
 *      - Traverse and print each day node.
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

class DailyReturnListMidDelete {
private:
    Node* head;

public:
    DailyReturnListMidDelete() : head(nullptr) {}

    ~DailyReturnListMidDelete() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    // Helper to add initially
    void append(int day, char status) {
        Node* newNode = new Node(day, status);
        if (head == nullptr) { head = newNode; return; }
        Node* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newNode;
    }

    // a. Insert in middle (after a given day)
    bool insertInMiddle(int afterDay, int newDay, char status) {
        Node* temp = head;
        while (temp != nullptr && temp->dayNumber != afterDay) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Day " << afterDay << " not found in list!\n";
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
            cout << "List is empty! Cannot delete from front.\n";
            return false;
        }

        Node* temp = head;
        head = head->next;
        cout << "Deleted Day " << temp->dayNumber << " (Status: " << temp->status << ") from front.\n";
        delete temp;
        return true;
    }

    // c. Calculate total not returned ('N')
    int countTotalNotReturned() {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->status == 'N' || temp->status == 'n') {
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
    cout << "  SET 1 (PART A - PROBLEM 3): SLL (INSERT MID & DELETE FRONT)\n";
    cout << "==============================================================\n";

    DailyReturnListMidDelete list;

    list.append(1, 'R');
    list.append(2, 'N');
    list.append(3, 'N');
    list.display();

    // a. Insert in middle (Insert Day 4 after Day 2)
    list.insertInMiddle(2, 4, 'R');
    list.display();

    // c. Count total not returned
    cout << "\nTotal books NOT returned ('N'): " << list.countTotalNotReturned() << "\n\n";

    // b. Delete from front
    list.deleteFromFront();
    list.display();

    return 0;
}
