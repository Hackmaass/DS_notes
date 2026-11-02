/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit IV: Queues
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 2 - Hospital Management System
 * PROBLEM REF:   Part B - Problem 5
 * TITLE:         Hospital OPD (Out-Patient Department) Queue Simulation
 * 
 * PROBLEM STATEMENT (Departmental Alternate Problem Set):
 *   Write a program to simulate an OPD queue where patients are called sequentially.
 *   a. Enqueue patient token number
 *   b. Dequeue and display patient called
 *   c. Display front and rear token number
 *   d. Display complete queue
 * 
 * ============================================================================
 * CONCEPT EXPLANATION: OPD PATIENT CONSULTATION QUEUE
 * ============================================================================
 * In a hospital Out-Patient Department (OPD):
 *   - Arriving patients register at the reception and receive a sequential consultation token.
 *   - Patients wait in the lobby and are called into the doctor's consultation chamber
 *     strictly in FIFO (First-In, First-Out) order.
 *   - Circular array queue eliminates memory wastage (False Overflow) as tokens wrap around.
 * ============================================================================
 * STEP-BY-STEP ALGORITHM (WHAT & WHY)
 * ============================================================================
 * 1. INITIALIZATION:
 *    - Array `opdQueue[MAX]`, `front = -1`, `rear = -1`.
 * 2. ENQUEUE PATIENT TOKEN:
 *    - If `(rear + 1) % MAX == front`, queue is full (Overflow).
 *    - If `front == -1`, set `front = rear = 0`.
 *    - Else `rear = (rear + 1) % MAX`.
 *    - `opdQueue[rear] = token`.
 * 3. DEQUEUE AND DISPLAY PATIENT CALLED:
 *    - If `front == -1`, queue is empty (Underflow).
 *    - Extract `token = opdQueue[front]`.
 *    - If `front == rear`, reset `front = rear = -1`.
 *    - Else `front = (front + 1) % MAX`.
 *    - Print consultation calling announcement.
 * 4. DISPLAY FRONT & REAR:
 *    - Inspect `opdQueue[front]` (now consulting) and `opdQueue[rear]` (last patient arrived).
 * 5. DISPLAY COMPLETE QUEUE:
 *    - Traverse circularly from `front` to `rear`.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_PATIENTS = 6;

class HospitalOPDQueue {
private:
    int opdQueue[MAX_PATIENTS];
    int front;
    int rear;

public:
    HospitalOPDQueue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() const {
        return (front == -1);
    }

    bool isFull() const {
        return ((rear + 1) % MAX_PATIENTS == front);
    }

    // OPERATION a: Enqueue patient token number
    bool enqueuePatient(int token) {
        if (isFull()) {
            cout << "  [OPD WAITING FULL] Waiting room at full capacity! Token #" << token << " must wait outside.\n";
            return false;
        }

        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % MAX_PATIENTS;
        }

        opdQueue[rear] = token;
        cout << "  [PATIENT REGISTERED] Patient Token #" << token << " enqueued for consultation at slot [" << rear << "].\n";
        return true;
    }

    // OPERATION b: Dequeue and display patient called
    int callNextPatient() {
        if (isEmpty()) {
            cout << "  [DOCTOR IDLE] No patients waiting in the OPD queue.\n";
            return -1;
        }

        int calledToken = opdQueue[front];
        int vacatedSlot = front;

        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % MAX_PATIENTS;
        }

        cout << "  [NOW CALLING] Patient Token #" << calledToken 
             << " please proceed to Doctor's Cabin 1! (Vacated Slot: " << vacatedSlot << ")\n";
        return calledToken;
    }

    // OPERATION c: Display front and rear token number
    void displayFrontRear() const {
        if (isEmpty()) {
            cout << "  [OPD STATUS] OPD Queue is empty.\n";
            return;
        }
        cout << "\n  --- OPD Display Board Pointers ---\n";
        cout << "  Next Patient to Enter (Front) : Token #" << opdQueue[front] << " (Slot: " << front << ")\n";
        cout << "  Latest Patient Joined (Rear)  : Token #" << opdQueue[rear]  << " (Slot: " << rear  << ")\n\n";
    }

    // OPERATION d: Display complete queue
    void displayQueue() const {
        if (isEmpty()) {
            cout << "  [OPD WAITING LIST] No patients currently waiting.\n";
            return;
        }

        cout << "\n  [OPD LOBBY WAITING LIST (Front -> Rear)]:\n  ";
        int i = front;
        while (true) {
            cout << "[Token #" << opdQueue[i] << "]";
            if (i == rear) break;
            cout << " -> ";
            i = (i + 1) % MAX_PATIENTS;
        }
        cout << "\n\n";
    }
};

void runVerification() {
    cout << "====================================================================\n";
    cout << "  SET 2: HOSPITAL MANAGEMENT SYSTEM - OPD QUEUE SIMULATION\n";
    cout << "====================================================================\n";

    HospitalOPDQueue opdQ;

    cout << "\n--- STEP 1: Verify Initial Empty State ---\n";
    opdQ.displayFrontRear();
    opdQ.displayQueue();

    cout << "\n--- STEP 2: Patients Arrive in Morning OPD (Tokens 101 to 104) ---\n";
    opdQ.enqueuePatient(101);
    opdQ.enqueuePatient(102);
    opdQ.enqueuePatient(103);
    opdQ.enqueuePatient(104);
    opdQ.displayFrontRear();
    opdQ.displayQueue();

    cout << "\n--- STEP 3: Doctor Consults First 2 Patients ---\n";
    opdQ.callNextPatient();
    opdQ.callNextPatient();
    opdQ.displayFrontRear();
    opdQ.displayQueue();

    cout << "\n--- STEP 4: More Patients Arrive (Wrap-Around Reusing Slots) ---\n";
    opdQ.enqueuePatient(105);
    opdQ.enqueuePatient(106);
    opdQ.enqueuePatient(107);
    opdQ.displayFrontRear();
    opdQ.displayQueue();

    cout << "\n--- STEP 5: Doctor Finishes Entire OPD Shift ---\n";
    while (!opdQ.isEmpty()) {
        opdQ.callNextPatient();
    }
    opdQ.displayQueue();
}

int main() {
    runVerification();
    return 0;
}

/*
 * ============================================================================
 * COMPLEXITY ANALYSIS
 * ============================================================================
 * Operation    | Time Complexity | Space Complexity | Description
 * -------------+-----------------+------------------+------------------------
 * Enqueue      | O(1)            | O(1)             | Modulo wrap-around array write.
 * Dequeue      | O(1)            | O(1)             | Modulo front pointer advance.
 * Front/Rear   | O(1)            | O(1)             | Direct array index peek.
 * Display      | O(N)            | O(1)             | Traversal across active elements.
 * Auxiliary Space: O(MAX) for array buffer.
 * ============================================================================
 */
