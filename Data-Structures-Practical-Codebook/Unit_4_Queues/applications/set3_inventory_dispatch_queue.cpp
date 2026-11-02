/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit IV: Queues
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 3 - Inventory and Warehouse System
 * PROBLEM REF:   Part B - Problem 5
 * TITLE:         Warehouse Goods Dispatch Queue Simulation
 * 
 * PROBLEM STATEMENT (Departmental Alternate Problem Set):
 *   Write a program to simulate a warehouse dispatch queue where orders are packed 
 *   and shipped in order.
 *   a. Enqueue order number
 *   b. Dequeue and display order dispatched
 *   c. Display front and rear order number
 *   d. Display complete queue
 * 
 * ============================================================================
 * CONCEPT EXPLANATION: FIFO GOODS DISPATCH QUEUE
 * ============================================================================
 * In an automated warehouse fulfillment center:
 *   - Customer orders are placed online and assigned an Order Number.
 *   - Orders join the dispatch queue at the REAR.
 *   - Packing and shipping bays dequeue orders from the FRONT to maintain
 *     fair First-Come, First-Served fulfillment.
 *   - Modulo circular queue ensures optimal memory reuse in fixed-size buffers.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_ORDERS = 6;

class WarehouseDispatchQueue {
private:
    int orderQueue[MAX_ORDERS];
    int front;
    int rear;

public:
    WarehouseDispatchQueue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() const {
        return (front == -1);
    }

    bool isFull() const {
        return ((rear + 1) % MAX_ORDERS == front);
    }

    // OPERATION a: Enqueue order number
    bool enqueueOrder(int orderNo) {
        if (isFull()) {
            cout << "  [DISPATCH BUFFER FULL] Order #" << orderNo << " cannot be queued right now.\n";
            return false;
        }

        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % MAX_ORDERS;
        }

        orderQueue[rear] = orderNo;
        cout << "  [ORDER RECEIVED] Order #" << orderNo << " placed in dispatch queue at bay slot [" << rear << "].\n";
        return true;
    }

    // OPERATION b: Dequeue and display order dispatched
    int dispatchNextOrder() {
        if (isEmpty()) {
            cout << "  [DISPATCH DOCK IDLE] No orders pending dispatch.\n";
            return -1;
        }

        int dispatchedOrder = orderQueue[front];
        int vacated = front;

        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % MAX_ORDERS;
        }

        cout << "  [SHIPPED] Order #" << dispatchedOrder 
             << " has been packed and handed over to courier! (Vacated Slot: " << vacated << ")\n";
        return dispatchedOrder;
    }

    // OPERATION c: Display front and rear order number
    void displayFrontRear() const {
        if (isEmpty()) {
            cout << "  [DISPATCH STATUS] No orders in queue.\n";
            return;
        }
        cout << "\n  --- Dispatch Dock Pointers ---\n";
        cout << "  Front Order (Next to Ship)  : #" << orderQueue[front] << " (Slot: " << front << ")\n";
        cout << "  Rear Order  (Latest Placed) : #" << orderQueue[rear]  << " (Slot: " << rear  << ")\n\n";
    }

    // OPERATION d: Display complete queue
    void displayQueue() const {
        if (isEmpty()) {
            cout << "  [DISPATCH QUEUE] Empty.\n";
            return;
        }

        cout << "\n  [PENDING WAREHOUSE DISPATCH ORDERS (Front -> Rear)]:\n  ";
        int i = front;
        while (true) {
            cout << "[Order #" << orderQueue[i] << "]";
            if (i == rear) break;
            cout << " -> ";
            i = (i + 1) % MAX_ORDERS;
        }
        cout << "\n\n";
    }
};

void runVerification() {
    cout << "====================================================================\n";
    cout << "  SET 3: INVENTORY & WAREHOUSE SYSTEM - DISPATCH QUEUE DEMO\n";
    cout << "====================================================================\n";

    WarehouseDispatchQueue dispatchQ;

    cout << "\n--- STEP 1: Verify Initial State ---\n";
    dispatchQ.displayFrontRear();
    dispatchQ.displayQueue();

    cout << "\n--- STEP 2: Enqueue Customer Orders (Orders 9001 to 9004) ---\n";
    dispatchQ.enqueueOrder(9001);
    dispatchQ.enqueueOrder(9002);
    dispatchQ.enqueueOrder(9003);
    dispatchQ.enqueueOrder(9004);
    dispatchQ.displayFrontRear();
    dispatchQ.displayQueue();

    cout << "\n--- STEP 3: Ship First 2 Orders from Front ---\n";
    dispatchQ.dispatchNextOrder();
    dispatchQ.dispatchNextOrder();
    dispatchQ.displayFrontRear();
    dispatchQ.displayQueue();

    cout << "\n--- STEP 4: Wrap-Around Enqueue (Orders 9005 to 9007) ---\n";
    dispatchQ.enqueueOrder(9005);
    dispatchQ.enqueueOrder(9006);
    dispatchQ.enqueueOrder(9007);
    dispatchQ.displayFrontRear();
    dispatchQ.displayQueue();

    cout << "\n--- STEP 5: Dispatch All Remaining Orders ---\n";
    while (!dispatchQ.isEmpty()) {
        dispatchQ.dispatchNextOrder();
    }
    dispatchQ.displayQueue();
}

int main() {
    runVerification();
    return 0;
}
