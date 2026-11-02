/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit I: Arrays & Linked Lists
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 2 - Hospital Management System (Part A Suite)
 * TITLE:         Hospital System: Arrays, SLL, Sorted DLL, and Memory Representation
 * 
 * PROBLEM STATEMENTS COVERED:
 *   1. Array: Maintain records of N patients (Patient ID, Name, Age).
 *      a. Insert at position, b. Delete by ID, c. Search by ID, d. Display all.
 *   2. SLL: Daily check-up status (C=Completed / M=Missed).
 *      a. Insert at end, b. Update given day, c. Calculate total completed, d. Display all.
 *   3. SLL: Same list.
 *      a. Insert in middle, b. Delete from front, c. Calculate total missed, d. Display all.
 *   4. DLL: Doctors sorted by Doctor ID.
 *      a. Sorted insert, b. Delete by Doctor ID, c. Forward traversal, d. Backward traversal.
 *   5. Array vs LL: Patient body temperature readings.
 *      a. Insert in both, b. Display memory representation, c. Count patients with temp > 100°F.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// ============================================================================
// PART 1: ARRAY - PATIENT RECORDS SYSTEM (Problem 1)
// ============================================================================
struct Patient {
    int patientId;
    string name;
    int age;
};

class PatientArraySystem {
private:
    Patient patients[50];
    int size;

public:
    PatientArraySystem() : size(0) {}

    bool insertAtPosition(int pos, int id, const string& name, int age) {
        if (size >= 50) return false;
        if (pos < 1 || pos > size + 1) return false;
        for (int i = size; i >= pos; --i) {
            patients[i] = patients[i - 1];
        }
        patients[pos - 1] = {id, name, age};
        size++;
        return true;
    }

    bool deleteByPatientId(int id) {
        int idx = -1;
        for (int i = 0; i < size; ++i) {
            if (patients[i].patientId == id) { idx = i; break; }
        }
        if (idx == -1) return false;
        for (int i = idx; i < size - 1; ++i) {
            patients[i] = patients[i + 1];
        }
        size--;
        return true;
    }

    int searchByPatientId(int id) const {
        for (int i = 0; i < size; ++i) {
            if (patients[i].patientId == id) {
                cout << "  [FOUND] ID: " << patients[i].patientId 
                     << " | Name: " << patients[i].name 
                     << " | Age: " << patients[i].age << "\n";
                return i;
            }
        }
        return -1;
    }

    void displayAll() const {
        cout << "\n  --- HOSPITAL PATIENT REGISTRY (Array) ---\n";
        cout << "  " << left << setw(6) << "Pos" << setw(12) << "Patient ID" 
             << setw(25) << "Patient Name" << "Age\n";
        cout << "  --------------------------------------------------\n";
        for (int i = 0; i < size; ++i) {
            cout << "  " << left << setw(6) << (i + 1)
                 << setw(12) << patients[i].patientId
                 << setw(25) << patients[i].name
                 << patients[i].age << "\n";
        }
        cout << "\n";
    }
};

// ============================================================================
// PART 2: SLL - CHECK-UP STATUS (Problems 2 & 3)
// ============================================================================
struct CheckupNode {
    int dayNumber;
    char status; // 'C' = Completed, 'M' = Missed
    CheckupNode* next;
    CheckupNode(int d, char s) : dayNumber(d), status(s), next(nullptr) {}
};

class HospitalCheckupSLL {
private:
    CheckupNode* head;

public:
    HospitalCheckupSLL() : head(nullptr) {}
    ~HospitalCheckupSLL() {
        while (head != nullptr) {
            CheckupNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertAtEnd(int day, char status) {
        CheckupNode* newNode = new CheckupNode(day, status);
        if (head == nullptr) { head = newNode; return; }
        CheckupNode* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newNode;
    }

    bool insertInMiddle(int afterDay, int newDay, char status) {
        CheckupNode* temp = head;
        while (temp != nullptr && temp->dayNumber != afterDay) temp = temp->next;
        if (temp == nullptr) return false;
        CheckupNode* newNode = new CheckupNode(newDay, status);
        newNode->next = temp->next;
        temp->next = newNode;
        return true;
    }

    bool deleteFromFront() {
        if (head == nullptr) return false;
        CheckupNode* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    bool updateStatus(int day, char status) {
        CheckupNode* temp = head;
        while (temp != nullptr) {
            if (temp->dayNumber == day) { temp->status = status; return true; }
            temp = temp->next;
        }
        return false;
    }

    int countCompleted() const {
        int cnt = 0;
        CheckupNode* t = head;
        while (t != nullptr) {
            if (t->status == 'C' || t->status == 'c') cnt++;
            t = t->next;
        }
        return cnt;
    }

    int countMissed() const {
        int cnt = 0;
        CheckupNode* t = head;
        while (t != nullptr) {
            if (t->status == 'M' || t->status == 'm') cnt++;
            t = t->next;
        }
        return cnt;
    }

    void displayList() const {
        cout << "  [CHECKUP LOG]: ";
        CheckupNode* t = head;
        while (t != nullptr) {
            cout << "[Day " << t->dayNumber << ": " << t->status << "]";
            if (t->next != nullptr) cout << " -> ";
            t = t->next;
        }
        cout << " -> NULL\n";
    }
};

// ============================================================================
// PART 3: DLL - SORTED DOCTORS REGISTRY (Problem 4)
// ============================================================================
struct DoctorNode {
    int doctorId;
    string doctorName;
    DoctorNode* prev;
    DoctorNode* next;
    DoctorNode(int id, const string& name) 
        : doctorId(id), doctorName(name), prev(nullptr), next(nullptr) {}
};

class SortedDoctorDLL {
private:
    DoctorNode* head;

public:
    SortedDoctorDLL() : head(nullptr) {}
    ~SortedDoctorDLL() {
        while (head != nullptr) {
            DoctorNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void sortedInsert(int id, const string& name) {
        DoctorNode* newNode = new DoctorNode(id, name);
        if (head == nullptr || id < head->doctorId) {
            newNode->next = head;
            if (head != nullptr) head->prev = newNode;
            head = newNode;
            return;
        }
        DoctorNode* curr = head;
        while (curr->next != nullptr && curr->next->doctorId < id) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        newNode->prev = curr;
        if (curr->next != nullptr) curr->next->prev = newNode;
        curr->next = newNode;
    }

    bool deleteByDoctorId(int id) {
        DoctorNode* curr = head;
        while (curr != nullptr && curr->doctorId != id) curr = curr->next;
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
        cout << "  [FORWARD DOCTOR DLL]  NULL <-> ";
        DoctorNode* t = head;
        while (t != nullptr) {
            cout << "[Dr. " << t->doctorId << ": " << t->doctorName << "]";
            if (t->next != nullptr) cout << " <-> ";
            t = t->next;
        }
        cout << " <-> NULL\n";
    }

    void displayBackward() const {
        DoctorNode* tail = head;
        if (tail == nullptr) return;
        while (tail->next != nullptr) tail = tail->next;
        cout << "  [BACKWARD DOCTOR DLL] NULL <-> ";
        while (tail != nullptr) {
            cout << "[Dr. " << tail->doctorId << ": " << tail->doctorName << "]";
            if (tail->prev != nullptr) cout << " <-> ";
            tail = tail->prev;
        }
        cout << " <-> NULL\n";
    }
};

// ============================================================================
// PART 4: ARRAY VS LINKED LIST - BODY TEMPERATURE (Problem 5)
// ============================================================================
struct TempNode {
    int patientId;
    float temperature;
    TempNode* next;
    TempNode(int id, float t) : patientId(id), temperature(t), next(nullptr) {}
};

void runMemoryComparisonTemperatures() {
    cout << "\n====================================================================\n";
    cout << "  PROBLEM 5: ARRAY VS LINKED LIST MEMORY (Patient Temperatures)\n";
    cout << "====================================================================\n";

    const int N = 5;
    int pids[N] = {201, 202, 203, 204, 205};
    float temps[N] = {98.6f, 101.4f, 99.1f, 102.5f, 98.4f};

    TempNode* head = nullptr;
    TempNode* tail = nullptr;
    for (int i = 0; i < N; ++i) {
        TempNode* nn = new TempNode(pids[i], temps[i]);
        if (head == nullptr) { head = tail = nn; }
        else { tail->next = nn; tail = nn; }
    }

    cout << "\n1. Array Contiguous Memory Addresses (Stack):\n";
    int highTempArray = 0;
    for (int i = 0; i < N; ++i) {
        cout << "   Index " << i << " | Patient " << pids[i] << " | Temp: " 
             << fixed << setprecision(1) << temps[i] << " F | Addr: " << &temps[i] << "\n";
        if (temps[i] > 100.0f) highTempArray++;
    }

    cout << "\n2. Linked List Heap Memory Addresses (Heap Nodes):\n";
    int highTempLL = 0;
    TempNode* curr = head;
    while (curr != nullptr) {
        cout << "   Patient " << curr->patientId << " | Temp: " << fixed << setprecision(1) 
             << curr->temperature << " F | Node Addr: " << curr << " | Next: " << curr->next << "\n";
        if (curr->temperature > 100.0f) highTempLL++;
        curr = curr->next;
    }

    cout << "\n3. Count of Patients with Fever (Temp > 100.0 F):\n";
    cout << "   -> From Array: " << highTempArray << " | From LL: " << highTempLL << "\n";

    while (head != nullptr) {
        TempNode* t = head;
        head = head->next;
        delete t;
    }
}

int main() {
    cout << "====================================================================\n";
    cout << "  SET 2: HOSPITAL MANAGEMENT SYSTEM - COMPLETE UNIT 1 SUITE\n";
    cout << "====================================================================\n";

    // 1. Array
    PatientArraySystem pas;
    pas.insertAtPosition(1, 101, "Ramesh Shinde", 45);
    pas.insertAtPosition(2, 102, "Sunita Rao", 32);
    pas.insertAtPosition(2, 103, "Vijay Kulkarni", 58);
    pas.displayAll();
    pas.searchByPatientId(103);
    pas.deleteByPatientId(102);
    pas.displayAll();

    // 2. SLL
    HospitalCheckupSLL sll;
    sll.insertAtEnd(1, 'C');
    sll.insertAtEnd(2, 'M');
    sll.insertAtEnd(3, 'C');
    sll.displayList();
    sll.insertInMiddle(2, 4, 'C');
    sll.displayList();
    sll.updateStatus(2, 'C');
    sll.displayList();
    cout << "Completed: " << sll.countCompleted() << " | Missed: " << sll.countMissed() << "\n";
    sll.deleteFromFront();
    sll.displayList();

    // 3. DLL
    SortedDoctorDLL dll;
    dll.sortedInsert(503, "Dr. Mehta (Cardiology)");
    dll.sortedInsert(501, "Dr. Sharma (Neurology)");
    dll.sortedInsert(504, "Dr. Patil (Pediatrics)");
    dll.sortedInsert(502, "Dr. Joshi (Orthopedics)");
    dll.displayForward();
    dll.displayBackward();
    dll.deleteByDoctorId(503);
    dll.displayForward();

    // 4. Memory comparison
    runMemoryComparisonTemperatures();

    return 0;
}
