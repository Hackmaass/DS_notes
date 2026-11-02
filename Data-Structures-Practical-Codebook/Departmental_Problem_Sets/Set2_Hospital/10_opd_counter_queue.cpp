/**
 * ============================================================================
 * Departmental Problem Set 2 (Hospital) - Problem 10
 * Program: OPD Consultation Counter Circular Queue Simulation
 * ============================================================================
 * Problem Statement:
 *   Simulate an OPD consultation queue using a circular array of size 5:
 *   - Enqueue patient tokens (token number, patient name).
 *   - Dequeue patient when doctor calls the next patient.
 *   - Display front and rear tokens.
 *   - Display all waiting patient tokens.
 *   - Prevent overflow when full and underflow when empty.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

const int CAPACITY = 5;

struct PatientToken {
    int tokenNo;
    string patientName;
};

class OPDQueue {
private:
    PatientToken queue[CAPACITY];
    int front;
    int rear;
    int count;

public:
    OPDQueue() : front(0), rear(-1), count(0) {}

    bool isFull() const {
        return count == CAPACITY;
    }

    bool isEmpty() const {
        return count == 0;
    }

    void enqueue(int tokenNo, const string& patientName) {
        if (isFull()) {
            cout << "Queue Overflow: Cannot add Token #" << tokenNo 
                 << " (" << patientName << "). Waiting room is full!\n";
            return;
        }
        rear = (rear + 1) % CAPACITY;
        queue[rear].tokenNo = tokenNo;
        queue[rear].patientName = patientName;
        count++;
        cout << "Enqueued: Token #" << tokenNo << " (" << patientName << ") added to OPD queue.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow: No waiting patients in OPD queue.\n";
            return;
        }
        cout << "Called Doctor: Token #" << queue[front].tokenNo 
             << " (" << queue[front].patientName << ") entered consultation room.\n";
        front = (front + 1) % CAPACITY;
        count--;
    }

    void displayFrontRear() const {
        if (isEmpty()) {
            cout << "Queue is empty. Front and Rear do not point to any token.\n";
            return;
        }
        cout << "Front Patient: Token #" << queue[front].tokenNo << " (" << queue[front].patientName << ")\n";
        cout << "Rear Patient : Token #" << queue[rear].tokenNo << " (" << queue[rear].patientName << ")\n";
    }

    void displayWaitingPatients() const {
        if (isEmpty()) {
            cout << "OPD Waiting Queue: [Empty]\n";
            return;
        }
        cout << "OPD Waiting Queue (" << count << "/" << CAPACITY << "):\n";
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % CAPACITY;
            cout << "  " << (i + 1) << ". Token #" << queue[idx].tokenNo 
                 << " - " << queue[idx].patientName << "\n";
        }
    }
};

int main() {
    OPDQueue opd;

    cout << "=== OPD Consultation Counter Simulation ===\n\n";

    opd.enqueue(101, "Alice Smith");
    opd.enqueue(102, "Bob Jones");
    opd.enqueue(103, "Charlie Brown");
    opd.enqueue(104, "Diana Prince");
    cout << "\n";
    opd.displayWaitingPatients();
    cout << "\n";
    opd.displayFrontRear();

    cout << "\n--- Calling Next 2 Patients ---\n";
    opd.dequeue();
    opd.dequeue();

    cout << "\n--- Adding 2 More Patients (Testing Circular Wrap) ---\n";
    opd.enqueue(105, "Edward Norton");
    opd.enqueue(106, "Fiona Gallagher");
    opd.enqueue(107, "George Clark"); // Should trigger full

    cout << "\n";
    opd.displayWaitingPatients();
    cout << "\n";
    opd.displayFrontRear();

    return 0;
}
