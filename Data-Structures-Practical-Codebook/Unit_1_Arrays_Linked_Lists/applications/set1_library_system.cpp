/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit I: Arrays & Linked Lists
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 1 - Library Management System (Part A Suite)
 * TITLE:         Library System: Arrays, SLL, Sorted DLL, and Memory Representation
 * 
 * PROBLEM STATEMENTS COVERED (Official Departmental Problem Set):
 *   1. Array: Maintain records of N books (Book ID, Title, Price).
 *      a. Insert at position, b. Delete by Book ID, c. Search by Book ID, d. Display all.
 *   2. SLL: Daily return status of issued books (R/N).
 *      a. Insert at end, b. Update given day, c. Calculate total returned, d. Display all.
 *   3. SLL: Same list.
 *      a. Insert in middle, b. Delete from front, c. Calculate total not returned, d. Display all.
 *   4. DLL: Library members sorted by Member ID.
 *      a. Sorted insert, b. Delete by Member ID, c. Forward traversal, d. Backward traversal.
 *   5. Array vs LL: Books issued by N members.
 *      a. Insert count in both, b. Display memory representation, c. Count members > 5 books.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// ============================================================================
// PART 1: ARRAY - BOOK RECORDS SYSTEM (Problem 1)
// ============================================================================
struct Book {
    int bookId;
    string title;
    float price;
};

class BookArraySystem {
private:
    Book books[50];
    int size;

public:
    BookArraySystem() : size(0) {}

    // a. Insert at position (1-based index)
    bool insertAtPosition(int pos, int id, const string& title, float price) {
        if (size >= 50) {
            cout << "  [ERROR] Library catalogue full!\n";
            return false;
        }
        if (pos < 1 || pos > size + 1) {
            cout << "  [ERROR] Invalid position! Must be between 1 and " << size + 1 << ".\n";
            return false;
        }
        for (int i = size; i >= pos; --i) {
            books[i] = books[i - 1]; // Shift right
        }
        books[pos - 1] = {id, title, price};
        size++;
        cout << "  [INSERT] Book ID " << id << " inserted at position " << pos << ".\n";
        return true;
    }

    // b. Delete by Book ID
    bool deleteByBookId(int id) {
        int targetIdx = -1;
        for (int i = 0; i < size; ++i) {
            if (books[i].bookId == id) {
                targetIdx = i;
                break;
            }
        }
        if (targetIdx == -1) {
            cout << "  [NOT FOUND] Book ID " << id << " not found in catalogue.\n";
            return false;
        }
        for (int i = targetIdx; i < size - 1; ++i) {
            books[i] = books[i + 1]; // Shift left
        }
        size--;
        cout << "  [DELETED] Book ID " << id << " removed from library.\n";
        return true;
    }

    // c. Search by Book ID
    int searchByBookId(int id) const {
        for (int i = 0; i < size; ++i) {
            if (books[i].bookId == id) {
                cout << "  [FOUND] Book ID: " << books[i].bookId 
                     << " | Title: '" << books[i].title << "' | Price: Rs " 
                     << fixed << setprecision(2) << books[i].price 
                     << " (Found at Index " << i << ")\n";
                return i;
            }
        }
        cout << "  [NOT FOUND] Book ID " << id << " does not exist.\n";
        return -1;
    }

    // d. Display all books
    void displayAll() const {
        if (size == 0) {
            cout << "  [EMPTY] No books in library catalogue.\n";
            return;
        }
        cout << "\n  --- LIBRARY BOOK CATALOGUE (Array) ---\n";
        cout << "  " << left << setw(6) << "Pos" << setw(10) << "Book ID" 
             << setw(30) << "Title" << setw(10) << "Price (Rs)" << "\n";
        cout << "  --------------------------------------------------------\n";
        for (int i = 0; i < size; ++i) {
            cout << "  " << left << setw(6) << (i + 1)
                 << setw(10) << books[i].bookId
                 << setw(30) << books[i].title
                 << setw(10) << fixed << setprecision(2) << books[i].price << "\n";
        }
        cout << "\n";
    }
};

// ============================================================================
// PART 2: SINGLY LINKED LIST - DAILY RETURN STATUS (Problems 2 & 3)
// ============================================================================
struct ReturnNode {
    int dayNumber;
    char status; // 'R' = Returned, 'N' = Not Returned
    ReturnNode* next;

    ReturnNode(int day, char stat) : dayNumber(day), status(stat), next(nullptr) {}
};

class DailyReturnSLL {
private:
    ReturnNode* head;

public:
    DailyReturnSLL() : head(nullptr) {}

    ~DailyReturnSLL() {
        ReturnNode* curr = head;
        while (curr != nullptr) {
            ReturnNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    // Prob 2a: Insert at end
    void insertAtEnd(int day, char status) {
        ReturnNode* newNode = new ReturnNode(day, status);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        ReturnNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Prob 3a: Insert in middle (after specified day)
    bool insertInMiddle(int afterDay, int newDay, char status) {
        ReturnNode* temp = head;
        while (temp != nullptr && temp->dayNumber != afterDay) {
            temp = temp->next;
        }
        if (temp == nullptr) {
            cout << "  [ERROR] Day " << afterDay << " not found in return list.\n";
            return false;
        }
        ReturnNode* newNode = new ReturnNode(newDay, status);
        newNode->next = temp->next;
        temp->next = newNode;
        cout << "  [INSERT MID] Inserted Day " << newDay << " after Day " << afterDay << ".\n";
        return true;
    }

    // Prob 3b: Delete from front
    bool deleteFromFront() {
        if (head == nullptr) {
            cout << "  [ERROR] Return list is empty!\n";
            return false;
        }
        ReturnNode* temp = head;
        head = head->next;
        cout << "  [DELETED FRONT] Removed Day " << temp->dayNumber 
             << " (Status: " << temp->status << ") from front.\n";
        delete temp;
        return true;
    }

    // Prob 2b: Update return status of a given day
    bool updateStatus(int day, char newStatus) {
        ReturnNode* temp = head;
        while (temp != nullptr) {
            if (temp->dayNumber == day) {
                temp->status = newStatus;
                cout << "  [UPDATED] Day " << day << " status updated to '" << newStatus << "'.\n";
                return true;
            }
            temp = temp->next;
        }
        cout << "  [NOT FOUND] Day " << day << " not in record.\n";
        return false;
    }

    // Prob 2c: Calculate total returned ('R')
    int countTotalReturned() const {
        int count = 0;
        ReturnNode* temp = head;
        while (temp != nullptr) {
            if (temp->status == 'R' || temp->status == 'r') count++;
            temp = temp->next;
        }
        return count;
    }

    // Prob 3c: Calculate total not returned ('N')
    int countTotalNotReturned() const {
        int count = 0;
        ReturnNode* temp = head;
        while (temp != nullptr) {
            if (temp->status == 'N' || temp->status == 'n') count++;
            temp = temp->next;
        }
        return count;
    }

    // Prob 2d & 3d: Display complete list
    void displayList() const {
        if (head == nullptr) {
            cout << "  [EMPTY] Return log is empty.\n";
            return;
        }
        cout << "  [RETURN LOG]: ";
        ReturnNode* temp = head;
        while (temp != nullptr) {
            cout << "[Day " << temp->dayNumber << ": " << temp->status << "]";
            if (temp->next != nullptr) cout << " -> ";
            temp = temp->next;
        }
        cout << " -> NULL\n";
    }
};

// ============================================================================
// PART 3: DOUBLY LINKED LIST - SORTED LIBRARY MEMBERS (Problem 4)
// ============================================================================
struct MemberNode {
    int memberId;
    string memberName;
    MemberNode* prev;
    MemberNode* next;

    MemberNode(int id, const string& name) 
        : memberId(id), memberName(name), prev(nullptr), next(nullptr) {}
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

    // a. Sorted Insert (ascending by memberId)
    void sortedInsert(int id, const string& name) {
        MemberNode* newNode = new MemberNode(id, name);
        if (head == nullptr || id < head->memberId) {
            newNode->next = head;
            if (head != nullptr) head->prev = newNode;
            head = newNode;
            cout << "  [DLL INSERT] Member ID " << id << " inserted at head.\n";
            return;
        }
        MemberNode* curr = head;
        while (curr->next != nullptr && curr->next->memberId < id) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        newNode->prev = curr;
        if (curr->next != nullptr) {
            curr->next->prev = newNode;
        }
        curr->next = newNode;
        cout << "  [DLL INSERT] Member ID " << id << " inserted in sorted order.\n";
    }

    // b. Delete by Member ID
    bool deleteByMemberId(int id) {
        if (head == nullptr) {
            cout << "  [ERROR] Member list is empty.\n";
            return false;
        }
        MemberNode* curr = head;
        while (curr != nullptr && curr->memberId != id) {
            curr = curr->next;
        }
        if (curr == nullptr) {
            cout << "  [NOT FOUND] Member ID " << id << " not found in DLL.\n";
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
        cout << "  [DLL DELETED] Member ID " << id << " (" << curr->memberName << ") deleted.\n";
        delete curr;
        return true;
    }

    // c. Forward Traversal
    void displayForward() const {
        if (head == nullptr) {
            cout << "  [EMPTY DLL] No members.\n";
            return;
        }
        cout << "  [FORWARD DLL]  NULL <-> ";
        MemberNode* temp = head;
        while (temp != nullptr) {
            cout << "[" << temp->memberId << ": " << temp->memberName << "]";
            if (temp->next != nullptr) cout << " <-> ";
            temp = temp->next;
        }
        cout << " <-> NULL\n";
    }

    // d. Backward Traversal
    void displayBackward() const {
        if (head == nullptr) {
            cout << "  [EMPTY DLL] No members.\n";
            return;
        }
        MemberNode* tail = head;
        while (tail->next != nullptr) {
            tail = tail->next;
        }
        cout << "  [BACKWARD DLL] NULL <-> ";
        while (tail != nullptr) {
            cout << "[" << tail->memberId << ": " << tail->memberName << "]";
            if (tail->prev != nullptr) cout << " <-> ";
            tail = tail->prev;
        }
        cout << " <-> NULL\n";
    }
};

// ============================================================================
// PART 4: ARRAY VS LINKED LIST - BOOKS ISSUED MEMORY COMPARISON (Problem 5)
// ============================================================================
struct IssuedNode {
    int memberId;
    int booksIssued;
    IssuedNode* next;
    IssuedNode(int id, int count) : memberId(id), booksIssued(count), next(nullptr) {}
};

void runMemoryComparisonBooksIssued() {
    cout << "\n====================================================================\n";
    cout << "  PROBLEM 5: ARRAY VS LINKED LIST MEMORY COMPARISON (Books Issued)\n";
    cout << "====================================================================\n";

    const int N = 5;
    int memberIds[N] = {101, 102, 103, 104, 105};
    int booksIssuedArr[N] = {3, 7, 2, 8, 4};

    IssuedNode* llHead = nullptr;
    IssuedNode* tail = nullptr;

    for (int i = 0; i < N; ++i) {
        IssuedNode* newNode = new IssuedNode(memberIds[i], booksIssuedArr[i]);
        if (llHead == nullptr) {
            llHead = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    cout << "\n1. Array Memory Representation (Contiguous Allocation in Stack):\n";
    cout << "   " << left << setw(8) << "Index" << setw(12) << "Member ID" 
         << setw(16) << "Books Issued" << "Memory Address (Hex)\n";
    cout << "   ---------------------------------------------------------\n";
    int arrayAbove5 = 0;
    for (int i = 0; i < N; ++i) {
        cout << "   " << left << setw(8) << i << setw(12) << memberIds[i] 
             << setw(16) << booksIssuedArr[i] << &booksIssuedArr[i] << "\n";
        if (booksIssuedArr[i] > 5) arrayAbove5++;
    }

    cout << "\n2. Linked List Memory Representation (Non-Contiguous in Heap):\n";
    cout << "   " << left << setw(8) << "Node" << setw(12) << "Member ID" 
         << setw(16) << "Books Issued" << setw(20) << "Node Address" << "Next Pointer\n";
    cout << "   -------------------------------------------------------------------------\n";
    int llAbove5 = 0;
    int nodeIdx = 1;
    IssuedNode* curr = llHead;
    while (curr != nullptr) {
        cout << "   " << left << setw(8) << nodeIdx << setw(12) << curr->memberId 
             << setw(16) << curr->booksIssued << setw(20) << curr << curr->next << "\n";
        if (curr->booksIssued > 5) llAbove5++;
        curr = curr->next;
        nodeIdx++;
    }

    cout << "\n3. Count of members who issued MORE THAN 5 books:\n";
    cout << "   -> Count from Array       : " << arrayAbove5 << " members\n";
    cout << "   -> Count from Linked List : " << llAbove5 << " members\n";

    // Clean up heap
    while (llHead != nullptr) {
        IssuedNode* temp = llHead;
        llHead = llHead->next;
        delete temp;
    }
}

// ============================================================================
// MASTER DEMO EXECUTION
// ============================================================================
int main() {
    cout << "====================================================================\n";
    cout << "  SET 1: LIBRARY MANAGEMENT SYSTEM - COMPLETE UNIT 1 SUITE\n";
    cout << "====================================================================\n";

    // 1. Array Book Catalogue Demo
    cout << "\n>>> EXECUTING PROBLEM 1: ARRAY BOOK CATALOGUE <<<\n";
    BookArraySystem bookLib;
    bookLib.insertAtPosition(1, 101, "Data Structures in C++", 550.00f);
    bookLib.insertAtPosition(2, 102, "Operating Systems", 620.00f);
    bookLib.insertAtPosition(2, 103, "Database Systems", 480.00f); // Insert in middle
    bookLib.displayAll();
    bookLib.searchByBookId(103);
    bookLib.deleteByBookId(102);
    bookLib.displayAll();

    // 2. SLL Daily Returns Demo (Problems 2 & 3)
    cout << "\n>>> EXECUTING PROBLEMS 2 & 3: SLL DAILY RETURN STATUS <<<\n";
    DailyReturnSLL returnList;
    returnList.insertAtEnd(1, 'R');
    returnList.insertAtEnd(2, 'N');
    returnList.insertAtEnd(3, 'R');
    returnList.displayList();
    returnList.insertInMiddle(2, 4, 'R'); // Insert Day 4 after Day 2
    returnList.displayList();
    returnList.updateStatus(2, 'R');
    returnList.displayList();
    cout << "Total Books Returned ('R')     : " << returnList.countTotalReturned() << "\n";
    cout << "Total Books Not Returned ('N') : " << returnList.countTotalNotReturned() << "\n";
    returnList.deleteFromFront();
    returnList.displayList();

    // 3. DLL Sorted Members Demo (Problem 4)
    cout << "\n>>> EXECUTING PROBLEM 4: SORTED DLL LIBRARY MEMBERS <<<\n";
    SortedMemberDLL memberDLL;
    memberDLL.sortedInsert(302, "Pooja Patil");
    memberDLL.sortedInsert(105, "Amit Deshmukh");
    memberDLL.sortedInsert(401, "Sneha Joshi");
    memberDLL.sortedInsert(210, "Karan Rao");
    memberDLL.displayForward();
    memberDLL.displayBackward();
    memberDLL.deleteByMemberId(302);
    memberDLL.displayForward();

    // 4. Memory Representation Demo (Problem 5)
    runMemoryComparisonBooksIssued();

    return 0;
}
