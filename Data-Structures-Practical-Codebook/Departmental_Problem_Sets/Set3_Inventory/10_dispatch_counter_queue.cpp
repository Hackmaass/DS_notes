/**
 * ============================================================================
 * Departmental Problem Set 3 (Inventory) - Problem 10
 * Program: Warehouse Dispatch Counter Queue Simulation
 * ============================================================================
 * Problem Statement:
 *   Simulate warehouse goods dispatch queue using a circular array of size 5:
 *   - Enqueue dispatch orders (order_id, destination).
 *   - Dequeue order when truck arrives for dispatch.
 *   - Display front and rear orders.
 *   - Display all pending dispatch orders.
 *   - Handle queue overflow and underflow conditions.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

const int CAPACITY = 5;

struct DispatchOrder {
    int orderId;
    string destination;
};

class DispatchQueue {
private:
    DispatchOrder queue[CAPACITY];
    int front;
    int rear;
    int count;

public:
    DispatchQueue() : front(0), rear(-1), count(0) {}

    bool isFull() const {
        return count == CAPACITY;
    }

    bool isEmpty() const {
        return count == 0;
    }

    void enqueue(int orderId, const string& destination) {
        if (isFull()) {
            cout << "Queue Overflow: Dispatch Bay is full! Cannot queue Order #" << orderId << ".\n";
            return;
        }
        rear = (rear + 1) % CAPACITY;
        queue[rear].orderId = orderId;
        queue[rear].destination = destination;
        count++;
        cout << "Enqueued: Order #" << orderId << " (To: " << destination << ") placed in dispatch bay.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow: No pending orders in dispatch bay.\n";
            return;
        }
        cout << "Dispatched: Order #" << queue[front].orderId 
             << " loaded onto delivery truck for " << queue[front].destination << ".\n";
        front = (front + 1) % CAPACITY;
        count--;
    }

    void displayFrontRear() const {
        if (isEmpty()) {
            cout << "Dispatch queue is empty. Front and Rear pointers inactive.\n";
            return;
        }
        cout << "Front Order: #" << queue[front].orderId << " (" << queue[front].destination << ")\n";
        cout << "Rear Order : #" << queue[rear].orderId << " (" << queue[rear].destination << ")\n";
    }

    void displayPendingOrders() const {
        if (isEmpty()) {
            cout << "Pending Dispatches: [None]\n";
            return;
        }
        cout << "Pending Dispatches (" << count << "/" << CAPACITY << " in bay):\n";
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % CAPACITY;
            cout << "  " << (i + 1) << ". Order #" << queue[idx].orderId 
                 << " -> " << queue[idx].destination << "\n";
        }
    }
};

int main() {
    DispatchQueue bay;

    cout << "=== Warehouse Dispatch Counter Queue Simulation ===\n\n";

    bay.enqueue(801, "Pune Central Hub");
    bay.enqueue(802, "Mumbai Port Depot");
    bay.enqueue(803, "Nagpur Warehouse");
    bay.enqueue(804, "Nashik Retail Center");

    cout << "\n";
    bay.displayPendingOrders();
    cout << "\n";
    bay.displayFrontRear();

    cout << "\n--- Truck Loaded: Dispatching Oldest 2 Orders ---\n";
    bay.dequeue();
    bay.dequeue();

    cout << "\n--- Adding 3 New Incoming Orders (Circular Wrap) ---\n";
    bay.enqueue(805, "Kolhapur Hub");
    bay.enqueue(806, "Aurangabad Facility");
    bay.enqueue(807, "Solapur Terminal"); // Should fill bay or overflow appropriately

    cout << "\n";
    bay.displayPendingOrders();
    cout << "\n";
    bay.displayFrontRear();

    return 0;
}
