/**
 * ============================================================================
 * SET 2: HOSPITAL MANAGEMENT SYSTEM (Part A - Problem 1)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to maintain records of N patients with attributes:
 *   Patient ID, Name, and Age using an array.
 *   Perform operations:
 *     a. Insert at position
 *     b. Delete by Patient ID
 *     c. Search by Patient ID and display
 *     d. Display all patients
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX = 50;

struct Patient {
    int patientId;
    string name;
    int age;
};

class HospitalPatientArray {
private:
    Patient patients[MAX];
    int size;

public:
    HospitalPatientArray() : size(0) {}

    // a. Insert at position (1-based index)
    bool insertAtPosition(int pos, int id, string name, int age) {
        if (size >= MAX) {
            cout << "Error: Patient registry is full!\n";
            return false;
        }
        if (pos < 1 || pos > size + 1) {
            cout << "Error: Position must be between 1 and " << (size + 1) << ".\n";
            return false;
        }

        for (int i = size; i >= pos; --i) {
            patients[i] = patients[i - 1]; // Shift right
        }

        patients[pos - 1].patientId = id;
        patients[pos - 1].name = name;
        patients[pos - 1].age = age;
        size++;

        cout << "Inserted patient '" << name << "' at position " << pos << ".\n";
        return true;
    }

    // b. Delete by Patient ID
    bool deleteByPatientId(int targetId) {
        int index = -1;
        for (int i = 0; i < size; ++i) {
            if (patients[i].patientId == targetId) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Patient ID " << targetId << " not found!\n";
            return false;
        }

        cout << "Deleted Patient: " << patients[index].name << " (ID: " << targetId << ")\n";

        for (int i = index; i < size - 1; ++i) {
            patients[i] = patients[i + 1]; // Shift left
        }
        size--;
        return true;
    }

    // c. Search by Patient ID and display
    int searchByPatientId(int targetId) {
        for (int i = 0; i < size; ++i) {
            if (patients[i].patientId == targetId) {
                cout << "\n[Found Patient Record]:\n";
                cout << "  Patient ID : " << patients[i].patientId << "\n";
                cout << "  Name       : " << patients[i].name << "\n";
                cout << "  Age        : " << patients[i].age << " years\n";
                return i;
            }
        }
        cout << "Patient ID " << targetId << " not found!\n";
        return -1;
    }

    // d. Display all patients
    void displayAll() {
        if (size == 0) {
            cout << "Patient registry is empty.\n";
            return;
        }

        cout << "\n--------------------------------------------------------------\n";
        cout << left << setw(6) << "Pos" << setw(14) << "Patient ID" 
             << setw(25) << "Patient Name" << "Age\n";
        cout << "--------------------------------------------------------------\n";
        for (int i = 0; i < size; ++i) {
            cout << left << setw(6) << (i + 1)
                 << setw(14) << patients[i].patientId
                 << setw(25) << patients[i].name
                 << patients[i].age << "\n";
        }
        cout << "--------------------------------------------------------------\n";
    }
};

int main() {
    cout << "==============================================================\n";
    cout << "  SET 2 (PART A - PROBLEM 1): PATIENT RECORDS USING ARRAY\n";
    cout << "==============================================================\n";

    HospitalPatientArray hosp;

    // a. Insert patients
    hosp.insertAtPosition(1, 201, "Ramesh Shinde", 45);
    hosp.insertAtPosition(2, 202, "Sunita Rao", 32);
    hosp.insertAtPosition(2, 203, "Vijay Kulkarni", 58); // Insert at position 2
    hosp.displayAll();

    // c. Search by Patient ID
    hosp.searchByPatientId(203);

    // b. Delete by Patient ID
    hosp.deleteByPatientId(202);
    hosp.displayAll();

    return 0;
}
