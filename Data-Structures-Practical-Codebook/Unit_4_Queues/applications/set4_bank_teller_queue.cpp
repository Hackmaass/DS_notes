/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit IV: Queues
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 4 - Bank Management System
 * PROBLEM REF:   Part B - Problem 5
 * TITLE:         Bank Teller Counter Queue Simulation
 * 
 * PROBLEM STATEMENT (Departmental Alternate Problem Set):
 *   Write a program to simulate a bank teller counter queue where customers 
 *   are served for cash deposit/withdrawal.
 *   a. Enqueue customer token number
 *   b. Dequeue and display customer served
 *   c. Display front and rear token number
 *   d. Display complete queue
 * 
 * ============================================================================
 * CONCEPT EXPLANATION: FIFO BANK TELLER QUEUE
 * ============================================================================
 * In a retail banking branch:
 *   - Customers arriving for cash deposits or withdrawals take a queue token.
 *   - The bank teller serves customers strictly in the order they arrived (FIFO).
 *   - Using a circular array buffer guarantees maximum efficiency and avoids
 *     false overflow as served customer tokens are dequeued.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_CUSTOMERS = 6;

class BankTellerQueue {
private:
    int tellerQueue[MAX_CUSTOMERS];
    int front;
    int rear;

public:
    BankTellerQueue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() const {
        return (front == -1);
    }

    bool isFull() const {
        return ((rear + 1) % MAX_CUSTOMERS == front);
    }

    // OPERATION a: Enqueue customer token number
    bool enqueueCustomer(int token) {
        if (isFull()) {
            cout << "  [TELLER FULL] Token dispenser paused! Customer Token #" << token << " cannot be queued.\n";
            return false;
        }

        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % MAX_CUSTOMERS;
        }

        tellerQueue[rear] = token;
        cout << "  [CUSTOMER ARRIVED] Token #" << token << " queued at teller counter slot [" << rear << "].\n";
        return true;
    }

    // OPERATION b: Dequeue and display customer served
    int serveNextCustomer() {
        if (isEmpty()) {
            cout << "  [TELLER IDLE] No customers waiting at teller counter.\n";
            return -1;
        }

        int servedToken = tellerQueue[front];
        int vacated = front;

        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % MAX_CUSTOMERS;
        }

        cout << "  [TRANSACTION COMPLETE] Customer with Token #" << servedToken 
             << " served at Teller Counter 1! (Vacated Slot: " << vacated << ")\n";
        return servedToken;
    }

    // OPERATION c: Display front and rear token number
    void displayFrontRear() const {
        if (isEmpty()) {
            cout << "  [STATUS] Teller queue is empty.\n";
            return;
        }
        cout << "\n  --- Teller Display System Pointers ---\n";
        cout << "  Front Customer (Currently at Teller) : Token #" << tellerQueue[front] << " (Slot: " << front << ")\n";
        cout << "  Rear Customer  (Most Recent Arrival) : Token #" << tellerQueue[rear]  << " (Slot: " << rear  << ")\n\n";
    }

    // OPERATION d: Display complete queue
    void displayQueue() const {
        if (isEmpty()) {
            cout << "  [TELLER QUEUE] Empty.\n";
            return;
        }

        cout << "\n  [BANK TELLER WAITING QUEUE (Front -> Rear)]:\n  ";
        int i = front;
        while (true) {
            cout << "[Token #" << tellerQueue[i] << "]";
            if (i == rear) break;
            cout << " -> ";
            i = (i + 1) % MAX_CUSTOMERS;
        }
        cout << "\n\n";
    }
};

void runVerification() {
    cout << "====================================================================\n";
    cout << "  SET 4: BANK MANAGEMENT SYSTEM - TELLER COUNTER QUEUE DEMO\n";
    cout << "====================================================================\n";

    BankTellerQueue tellerQ;

    cout << "\n--- STEP 1: Verify Initial State ---\n";
    tellerQ.displayFrontRear();
    tellerQ.displayQueue();

    cout << "\n--- STEP 2: Customers Enter Bank (Tokens 701 to 704) ---\n";
    tellerQ.enqueueCustomer(701);
    tellerQ.enqueueCustomer(702);
    tellerQ.enqueueCustomer(703);
    tellerQ.enqueueCustomer(704);
    tellerQ.displayFrontRear();
    tellerQ.displayQueue();

    cout << "\n--- STEP 3: Teller Serves First 2 Customers ---\n";
    tellerQ.serveNextCustomer();
    tellerQ.serveNextCustomer();
    tellerQ.displayFrontRear();
    tellerQ.displayQueue();

    cout << "\n--- STEP 4: Wrap-Around Enqueue (Tokens 705 to 707) ---\n";
    tellerQ.enqueueCustomer(705);
    tellerQ.enqueueCustomer(706);
    tellerQ.enqueueCustomer(707);
    tellerQ.displayFrontRear();
    tellerQ.displayQueue();

    cout << "\n--- STEP 5: Serve All Remaining Customers ---\n";
    while (!tellerQ.isEmpty()) {
        tellerQ.serveNextCustomer();
    }
    tellerQ.displayQueue();
}

int main() {
    runVerification();
    return 0;
}
