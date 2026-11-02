/**
 * ============================================================================
 * Departmental Problem Set 4 (Bank) - Problem 10
 * Program: Bank Teller Counter Queue Simulation
 * ============================================================================
 * Problem Statement:
 *   Simulate bank teller counter token queue using a circular array of size 5:
 *   - Enqueue customer tokens (token_no, customer_name).
 *   - Dequeue customer token when teller is ready.
 *   - Display front and rear customer tokens.
 *   - Display all waiting customers in queue.
 *   - Handle queue overflow and underflow conditions.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

const int CAPACITY = 5;

struct CustomerToken {
    int tokenNo;
    string customerName;
};

class TellerQueue {
private:
    CustomerToken queue[CAPACITY];
    int front;
    int rear;
    int count;

public:
    TellerQueue() : front(0), rear(-1), count(0) {}

    bool isFull() const {
        return count == CAPACITY;
    }

    bool isEmpty() const {
        return count == 0;
    }

    void enqueue(int tokenNo, const string& customerName) {
        if (isFull()) {
            cout << "Queue Overflow: Waiting area full! Cannot issue Token #" << tokenNo 
                 << " to " << customerName << ".\n";
            return;
        }
        rear = (rear + 1) % CAPACITY;
        queue[rear].tokenNo = tokenNo;
        queue[rear].customerName = customerName;
        count++;
        cout << "Issued: Token #" << tokenNo << " to " << customerName << ".\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow: No customers waiting at teller counter.\n";
            return;
        }
        cout << "Called to Counter: Token #" << queue[front].tokenNo 
             << " (" << queue[front].customerName << ") serving now.\n";
        front = (front + 1) % CAPACITY;
        count--;
    }

    void displayFrontRear() const {
        if (isEmpty()) {
            cout << "Teller queue is empty. Front and Rear pointers inactive.\n";
            return;
        }
        cout << "Front Customer: Token #" << queue[front].tokenNo << " (" << queue[front].customerName << ")\n";
        cout << "Rear Customer : Token #" << queue[rear].tokenNo << " (" << queue[rear].customerName << ")\n";
    }

    void displayWaitingCustomers() const {
        if (isEmpty()) {
            cout << "Waiting Queue: [Empty]\n";
            return;
        }
        cout << "Waiting Customers (" << count << "/" << CAPACITY << "):\n";
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % CAPACITY;
            cout << "  " << (i + 1) << ". Token #" << queue[idx].tokenNo 
                 << " - " << queue[idx].customerName << "\n";
        }
    }
};

int main() {
    TellerQueue teller;

    cout << "=== Bank Teller Counter Queue Simulation ===\n\n";

    teller.enqueue(1, "Aarav Sharma");
    teller.enqueue(2, "Bhavna Patel");
    teller.enqueue(3, "Chetan Joshi");
    teller.enqueue(4, "Deepika Roy");

    cout << "\n";
    teller.displayWaitingCustomers();
    cout << "\n";
    teller.displayFrontRear();

    cout << "\n--- Teller Serves 2 Customers ---\n";
    teller.dequeue();
    teller.dequeue();

    cout << "\n--- New Customers Arrive (Testing Circular Index Wrap) ---\n";
    teller.enqueue(5, "Esha Deol");
    teller.enqueue(6, "Farhan Akhtar");
    teller.enqueue(7, "Gauri Shinde"); // Full test

    cout << "\n";
    teller.displayWaitingCustomers();
    cout << "\n";
    teller.displayFrontRear();

    return 0;
}
