/**
 * ============================================================================
 * SET 1: LIBRARY MANAGEMENT SYSTEM (Part A - Problem 4)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to maintain library members sorted by Member ID using
 *   Doubly Linked List.
 *   Functions:
 *     a. Insert member in sorted order
 *     b. Delete by Member ID
 *     c. Traverse forward
 *     d. Traverse backward
 * ============================================================================
 * ALGORITHM:
 *   1. Node: int memberId, string name, Node* prev, Node* next.
 *   2. Sorted Insert:
 *      - If head == NULL or id < head->memberId, insert at head (update head->prev).
 *      - Else traverse until curr->next == NULL or curr->next->memberId > id.
 *      - Splice newNode between curr and curr->next.
 *   3. Delete by Member ID:
 *      - Find node with matching memberId.
 *      - If at head, advance head and set head->prev = NULL.
 *      - Else update curr->prev->next and curr->next->prev. Free node.
 *   4. Traverse Forward:
 *      - Start from head, follow next pointers to tail.
 *   5. Traverse Backward:
 *      - Move to tail, follow prev pointers back to head.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

struct MemberNode {
    int memberId;
    string name;
    MemberNode* prev;
    MemberNode* next;

    MemberNode(int id, string n) : memberId(id), name(n), prev(nullptr), next(nullptr) {}
};

class SortedMemberDLL {
private:
    MemberNode* head;

public:
    SortedMemberDLL() : head(nullptr) {}

    ~SortedMemberDLL() {
        MemberNode* curr = head;
        while (curr != nullptr) {
            MemberNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    // a. Insert member in sorted order of Member ID
    void sortedInsert(int id, string name) {
        MemberNode* newNode = new MemberNode(id, name);

        // Case 1: Empty list OR insert before head
        if (head == nullptr || id < head->memberId) {
            newNode->next = head;
            if (head != nullptr) {
                head->prev = newNode;
            }
            head = newNode;
            cout << "Inserted Member #" << id << " (" << name << ") at head.\n";
            return;
        }

        // Case 2: Traverse to find correct position
        MemberNode* curr = head;
        while (curr->next != nullptr && curr->next->memberId < id) {
            curr = curr->next;
        }

        // Splice newNode after curr
        newNode->next = curr->next;
        newNode->prev = curr;
        if (curr->next != nullptr) {
            curr->next->prev = newNode;
        }
        curr->next = newNode;

        cout << "Inserted Member #" << id << " (" << name << ") in sorted position.\n";
    }

    // b. Delete by Member ID
    bool deleteByMemberId(int id) {
        if (head == nullptr) {
            cout << "Member list is empty!\n";
            return false;
        }

        MemberNode* curr = head;
        while (curr != nullptr && curr->memberId != id) {
            curr = curr->next;
        }

        if (curr == nullptr) {
            cout << "Member ID " << id << " not found!\n";
            return false;
        }

        // If deleting head
        if (curr == head) {
            head = head->next;
            if (head != nullptr) head->prev = nullptr;
        } else {
            curr->prev->next = curr->next;
            if (curr->next != nullptr) {
                curr->next->prev = curr->prev;
            }
        }

        cout << "Deleted Member #" << id << " (" << curr->name << ").\n";
        delete curr;
        return true;
    }

    // c. Traverse forward
    void traverseForward() {
        if (head == nullptr) {
            cout << "No members in registry.\n";
            return;
        }
        cout << "\nForward Traversal:  NULL <-> ";
        MemberNode* temp = head;
        while (temp != nullptr) {
            cout << "[" << temp->memberId << ": " << temp->name << "]";
            if (temp->next != nullptr) cout << " <-> ";
            temp = temp->next;
        }
        cout << " <-> NULL\n";
    }

    // d. Traverse backward
    void traverseBackward() {
        if (head == nullptr) {
            cout << "No members in registry.\n";
            return;
        }

        // Go to tail
        MemberNode* tail = head;
        while (tail->next != nullptr) {
            tail = tail->next;
        }

        cout << "Backward Traversal: NULL <-> ";
        while (tail != nullptr) {
            cout << "[" << tail->memberId << ": " << tail->name << "]";
            if (tail->prev != nullptr) cout << " <-> ";
            tail = tail->prev;
        }
        cout << " <-> NULL\n\n";
    }
};

int main() {
    cout << "==============================================================\n";
    cout << "  SET 1 (PART A - PROBLEM 4): SORTED MEMBERS (DOUBLY LINKED LIST)\n";
    cout << "==============================================================\n";

    SortedMemberDLL dll;

    // a. Sorted Insert
    dll.sortedInsert(302, "Pooja Patil");
    dll.sortedInsert(105, "Amit Deshmukh");
    dll.sortedInsert(401, "Sneha Joshi");
    dll.sortedInsert(210, "Karan Rao");

    // c & d. Bidirectional traversals
    dll.traverseForward();
    dll.traverseBackward();

    // b. Delete by Member ID
    dll.deleteByMemberId(302);
    dll.traverseForward();

    return 0;
}
