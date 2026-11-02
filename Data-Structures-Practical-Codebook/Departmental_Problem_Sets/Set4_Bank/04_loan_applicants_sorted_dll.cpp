/**
 * ============================================================================
 * Departmental Problem Set 4 (Bank) - Problem 4
 * Program: Loan Applicants Management using Doubly Linked List (Sorted by ID)
 * ============================================================================
 * Problem Statement:
 *   Maintain loan applicants using a Doubly Linked List (DLL):
 *   - Nodes store applicantId, name, and creditScore (300 to 900).
 *   - Insert applicants in ascending sorted order of applicantId.
 *   - Delete applicant by ID.
 *   - Display applicants in both forward and backward directions.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

struct ApplicantNode {
    int applicantId;
    string name;
    int creditScore;
    ApplicantNode* prev;
    ApplicantNode* next;

    ApplicantNode(int id, const string& n, int score)
        : applicantId(id), name(n), creditScore(score), prev(nullptr), next(nullptr) {}
};

class LoanApplicantDLL {
private:
    ApplicantNode* head;
    ApplicantNode* tail;

public:
    LoanApplicantDLL() : head(nullptr), tail(nullptr) {}

    ~LoanApplicantDLL() {
        ApplicantNode* curr = head;
        while (curr != nullptr) {
            ApplicantNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    void insertSorted(int id, const string& name, int score) {
        ApplicantNode* newNode = new ApplicantNode(id, name, score);

        if (head == nullptr) {
            head = tail = newNode;
            cout << "Inserted Applicant ID " << id << " (" << name << ") as first applicant.\n";
            return;
        }

        // Insert at beginning
        if (id < head->applicantId) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            cout << "Inserted Applicant ID " << id << " (" << name << ") at head.\n";
            return;
        }

        // Insert at end
        if (id > tail->applicantId) {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
            cout << "Inserted Applicant ID " << id << " (" << name << ") at tail.\n";
            return;
        }

        // Insert in middle
        ApplicantNode* curr = head;
        while (curr != nullptr && curr->applicantId < id) {
            curr = curr->next;
        }

        newNode->next = curr;
        newNode->prev = curr->prev;
        curr->prev->next = newNode;
        curr->prev = newNode;
        cout << "Inserted Applicant ID " << id << " (" << name << ") in sorted position.\n";
    }

    void deleteById(int targetId) {
        if (head == nullptr) {
            cout << "Delete Failed: Applicant list is empty.\n";
            return;
        }

        ApplicantNode* curr = head;
        while (curr != nullptr && curr->applicantId != targetId) {
            curr = curr->next;
        }

        if (curr == nullptr) {
            cout << "Delete Failed: Applicant ID " << targetId << " not found.\n";
            return;
        }

        cout << "Deleted Applicant ID " << curr->applicantId << " (" << curr->name << ").\n";

        if (curr == head && curr == tail) {
            head = tail = nullptr;
        } else if (curr == head) {
            head = head->next;
            head->prev = nullptr;
        } else if (curr == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

        delete curr;
    }

    void displayForward() const {
        if (head == nullptr) {
            cout << "Loan Applicant List: [Empty]\n";
            return;
        }
        cout << "\nLoan Applicants (Forward: Head -> Tail):\n";
        ApplicantNode* curr = head;
        while (curr != nullptr) {
            cout << "  [ID: " << curr->applicantId << "] " << curr->name 
                 << " | CIBIL Score: " << curr->creditScore << "\n";
            curr = curr->next;
        }
    }

    void displayBackward() const {
        if (tail == nullptr) {
            cout << "Loan Applicant List: [Empty]\n";
            return;
        }
        cout << "\nLoan Applicants (Backward: Tail -> Head):\n";
        ApplicantNode* curr = tail;
        while (curr != nullptr) {
            cout << "  [ID: " << curr->applicantId << "] " << curr->name 
                 << " | CIBIL Score: " << curr->creditScore << "\n";
            curr = curr->prev;
        }
    }
};

int main() {
    LoanApplicantDLL registry;

    cout << "=== Loan Applicants Registry (Sorted Doubly Linked List) ===\n\n";

    registry.insertSorted(402, "Vikram Malhotra", 760);
    registry.insertSorted(105, "Ananya Sen", 810);
    registry.insertSorted(550, "Rohan Verma", 690);
    registry.insertSorted(230, "Pooja Hegde", 740);

    registry.displayForward();
    registry.displayBackward();

    cout << "\n--- Deleting Applicant ID 230 ---\n";
    registry.deleteById(230);

    registry.displayForward();

    return 0;
}
