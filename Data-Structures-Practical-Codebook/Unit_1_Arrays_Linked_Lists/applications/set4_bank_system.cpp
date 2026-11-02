/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit I: Arrays & Linked Lists
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 4 - Bank Management System (Part A Suite)
 * TITLE:         Bank System: Arrays, SLL, Sorted DLL, and Memory Representation
 * 
 * PROBLEM STATEMENTS COVERED:
 *   1. Array: Maintain records of N customers (Account No, Name, Balance).
 *      a. Insert at position, b. Delete by Account No, c. Search by Account No, d. Display all.
 *   2. SLL: Daily EMI payment status (P=Paid / D=Due).
 *      a. Insert at end, b. Update given day, c. Calculate total paid EMIs, d. Display all.
 *   3. SLL: Same list.
 *      a. Insert in middle, b. Delete from front, c. Calculate total due EMIs, d. Display all.
 *   4. DLL: Loan applicants sorted by Application No.
 *      a. Sorted insert, b. Delete by Application No, c. Forward traversal, d. Backward traversal.
 *   5. Array vs LL: Account balances of N customers.
 *      a. Insert in both, b. Display memory representation, c. Count customers with balance > Rs 50,000.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// PART 1: ARRAY - CUSTOMERS (Problem 1)
struct Customer {
    int accountNo;
    string name;
    double balance;
};

class CustomerArraySystem {
private:
    Customer customers[50];
    int size;

public:
    CustomerArraySystem() : size(0) {}

    bool insertAtPosition(int pos, int acc, const string& name, double bal) {
        if (size >= 50 || pos < 1 || pos > size + 1) return false;
        for (int i = size; i >= pos; --i) customers[i] = customers[i - 1];
        customers[pos - 1] = {acc, name, bal};
        size++;
        return true;
    }

    bool deleteByAccountNo(int acc) {
        int idx = -1;
        for (int i = 0; i < size; ++i) {
            if (customers[i].accountNo == acc) { idx = i; break; }
        }
        if (idx == -1) return false;
        for (int i = idx; i < size - 1; ++i) customers[i] = customers[i + 1];
        size--;
        return true;
    }

    int searchByAccountNo(int acc) const {
        for (int i = 0; i < size; ++i) {
            if (customers[i].accountNo == acc) {
                cout << "  [FOUND] Account: " << customers[i].accountNo 
                     << " | Name: " << customers[i].name 
                     << " | Balance: Rs " << fixed << setprecision(2) << customers[i].balance << "\n";
                return i;
            }
        }
        return -1;
    }

    void displayAll() const {
        cout << "\n  --- BANK CUSTOMER REGISTRY (Array) ---\n";
        cout << "  " << left << setw(6) << "Pos" << setw(14) << "Account No" 
             << setw(25) << "Customer Name" << "Balance (Rs)\n";
        cout << "  ---------------------------------------------------------\n";
        for (int i = 0; i < size; ++i) {
            cout << "  " << left << setw(6) << (i + 1)
                 << setw(14) << customers[i].accountNo
                 << setw(25) << customers[i].name
                 << fixed << setprecision(2) << customers[i].balance << "\n";
        }
        cout << "\n";
    }
};

// PART 2: SLL - EMI PAYMENT STATUS (Problems 2 & 3)
struct EmiNode {
    int dayNumber;
    char status; // 'P' = Paid, 'D' = Due
    EmiNode* next;
    EmiNode(int d, char s) : dayNumber(d), status(s), next(nullptr) {}
};

class EmiStatusSLL {
private:
    EmiNode* head;

public:
    EmiStatusSLL() : head(nullptr) {}
    ~EmiStatusSLL() {
        while (head != nullptr) {
            EmiNode* t = head;
            head = head->next;
            delete t;
        }
    }

    void insertAtEnd(int day, char status) {
        EmiNode* nn = new EmiNode(day, status);
        if (head == nullptr) { head = nn; return; }
        EmiNode* t = head;
        while (t->next != nullptr) t = t->next;
        t->next = nn;
    }

    bool insertInMiddle(int afterDay, int newDay, char status) {
        EmiNode* t = head;
        while (t != nullptr && t->dayNumber != afterDay) t = t->next;
        if (t == nullptr) return false;
        EmiNode* nn = new EmiNode(newDay, status);
        nn->next = t->next;
        t->next = nn;
        return true;
    }

    bool deleteFromFront() {
        if (head == nullptr) return false;
        EmiNode* t = head;
        head = head->next;
        delete t;
        return true;
    }

    bool updateStatus(int day, char status) {
        EmiNode* t = head;
        while (t != nullptr) {
            if (t->dayNumber == day) { t->status = status; return true; }
            t = t->next;
        }
        return false;
    }

    int countPaid() const {
        int cnt = 0;
        EmiNode* t = head;
        while (t != nullptr) {
            if (t->status == 'P' || t->status == 'p') cnt++;
            t = t->next;
        }
        return cnt;
    }

    int countDue() const {
        int cnt = 0;
        EmiNode* t = head;
        while (t != nullptr) {
            if (t->status == 'D' || t->status == 'd') cnt++;
            t = t->next;
        }
        return cnt;
    }

    void displayList() const {
        cout << "  [EMI PAYMENT LOG]: ";
        EmiNode* t = head;
        while (t != nullptr) {
            cout << "[Day " << t->dayNumber << ": " << t->status << "]";
            if (t->next != nullptr) cout << " -> ";
            t = t->next;
        }
        cout << " -> NULL\n";
    }
};

// PART 3: DLL - SORTED LOAN APPLICANTS (Problem 4)
struct LoanApplicantNode {
    int applicationNo;
    string applicantName;
    LoanApplicantNode* prev;
    LoanApplicantNode* next;
    LoanApplicantNode(int app, const string& name) 
        : applicationNo(app), applicantName(name), prev(nullptr), next(nullptr) {}
};

class SortedLoanApplicantDLL {
private:
    LoanApplicantNode* head;

public:
    SortedLoanApplicantDLL() : head(nullptr) {}
    ~SortedLoanApplicantDLL() {
        while (head != nullptr) {
            LoanApplicantNode* t = head;
            head = head->next;
            delete t;
        }
    }

    void sortedInsert(int app, const string& name) {
        LoanApplicantNode* nn = new LoanApplicantNode(app, name);
        if (head == nullptr || app < head->applicationNo) {
            nn->next = head;
            if (head != nullptr) head->prev = nn;
            head = nn;
            return;
        }
        LoanApplicantNode* curr = head;
        while (curr->next != nullptr && curr->next->applicationNo < app) {
            curr = curr->next;
        }
        nn->next = curr->next;
        nn->prev = curr;
        if (curr->next != nullptr) curr->next->prev = nn;
        curr->next = nn;
    }

    bool deleteByApplicationNo(int app) {
        LoanApplicantNode* curr = head;
        while (curr != nullptr && curr->applicationNo != app) curr = curr->next;
        if (curr == nullptr) return false;
        if (curr == head) {
            head = head->next;
            if (head != nullptr) head->prev = nullptr;
        } else {
            curr->prev->next = curr->next;
            if (curr->next != nullptr) curr->next->prev = curr->prev;
        }
        delete curr;
        return true;
    }

    void displayForward() const {
        cout << "  [FORWARD LOAN APPLICANTS]  NULL <-> ";
        LoanApplicantNode* t = head;
        while (t != nullptr) {
            cout << "[App #" << t->applicationNo << ": " << t->applicantName << "]";
            if (t->next != nullptr) cout << " <-> ";
            t = t->next;
        }
        cout << " <-> NULL\n";
    }

    void displayBackward() const {
        LoanApplicantNode* tail = head;
        if (tail == nullptr) return;
        while (tail->next != nullptr) tail = tail->next;
        cout << "  [BACKWARD LOAN APPLICANTS] NULL <-> ";
        while (tail != nullptr) {
            cout << "[App #" << tail->applicationNo << ": " << tail->applicantName << "]";
            if (tail->prev != nullptr) cout << " <-> ";
            tail = tail->prev;
        }
        cout << " <-> NULL\n";
    }
};

// PART 4: ARRAY VS LINKED LIST - ACCOUNT BALANCES (Problem 5)
struct BalanceNode {
    int accountNo;
    double balance;
    BalanceNode* next;
    BalanceNode(int acc, double bal) : accountNo(acc), balance(bal), next(nullptr) {}
};

void runMemoryComparisonBalances() {
    cout << "\n====================================================================\n";
    cout << "  PROBLEM 5: ARRAY VS LINKED LIST MEMORY (Account Balances)\n";
    cout << "====================================================================\n";

    const int N = 5;
    int accs[N] = {1001, 1002, 1003, 1004, 1005};
    double bals[N] = {25000.0, 75000.0, 48000.0, 120000.0, 62000.0};

    BalanceNode* head = nullptr;
    BalanceNode* tail = nullptr;
    for (int i = 0; i < N; ++i) {
        BalanceNode* nn = new BalanceNode(accs[i], bals[i]);
        if (head == nullptr) { head = tail = nn; }
        else { tail->next = nn; tail = nn; }
    }

    cout << "\n1. Array Contiguous Memory Addresses (Stack):\n";
    int highBalanceArray = 0;
    for (int i = 0; i < N; ++i) {
        cout << "   Index " << i << " | Acc " << accs[i] << " | Balance: Rs " 
             << fixed << setprecision(2) << bals[i] << " | Addr: " << &bals[i] << "\n";
        if (bals[i] > 50000.0) highBalanceArray++;
    }

    cout << "\n2. Linked List Heap Memory Addresses (Heap Nodes):\n";
    int highBalanceLL = 0;
    BalanceNode* curr = head;
    while (curr != nullptr) {
        cout << "   Acc " << curr->accountNo << " | Balance: Rs " << fixed << setprecision(2) 
             << curr->balance << " | Node Addr: " << curr << " | Next: " << curr->next << "\n";
        if (curr->balance > 50000.0) highBalanceLL++;
        curr = curr->next;
    }

    cout << "\n3. Count of Customers with Balance > Rs 50,000:\n";
    cout << "   -> From Array: " << highBalanceArray << " | From LL: " << highBalanceLL << "\n";

    while (head != nullptr) {
        BalanceNode* t = head;
        head = head->next;
        delete t;
    }
}

int main() {
    cout << "====================================================================\n";
    cout << "  SET 4: BANK MANAGEMENT SYSTEM - COMPLETE UNIT 1 SUITE\n";
    cout << "====================================================================\n";

    // 1. Array
    CustomerArraySystem cas;
    cas.insertAtPosition(1, 1001, "Priya Sharma", 45000.0);
    cas.insertAtPosition(2, 1002, "Nikhil Gaikwad", 85000.0);
    cas.insertAtPosition(2, 1003, "Anjali Pawar", 92000.0);
    cas.displayAll();
    cas.searchByAccountNo(1003);
    cas.deleteByAccountNo(1002);
    cas.displayAll();

    // 2. SLL
    EmiStatusSLL sll;
    sll.insertAtEnd(1, 'P');
    sll.insertAtEnd(2, 'D');
    sll.insertAtEnd(3, 'P');
    sll.displayList();
    sll.insertInMiddle(2, 4, 'P');
    sll.displayList();
    sll.updateStatus(2, 'P');
    sll.displayList();
    cout << "Paid EMIs: " << sll.countPaid() << " | Due EMIs: " << sll.countDue() << "\n";
    sll.deleteFromFront();
    sll.displayList();

    // 3. DLL
    SortedLoanApplicantDLL dll;
    dll.sortedInsert(803, "Rajendra Shinde (Home Loan)");
    dll.sortedInsert(801, "Meena Joshi (Education Loan)");
    dll.sortedInsert(804, "Vikram More (Auto Loan)");
    dll.sortedInsert(802, "Snehal Deshpande (Personal Loan)");
    dll.displayForward();
    dll.displayBackward();
    dll.deleteByApplicationNo(803);
    dll.displayForward();

    // 4. Memory comparison
    runMemoryComparisonBalances();

    return 0;
}
