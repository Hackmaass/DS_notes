/**
 * ============================================================================
 * FUNDAMENTAL 08: CIRCULAR QUEUE (FIFO & MODULO ARITHMETIC)
 * ============================================================================
 * 👨‍🏫 PROFESSOR'S DEEP-DIVE CONCEPTUAL GUIDE:
 * 
 * 1. THE FIFO PRINCIPLE (FIRST-IN, FIRST-OUT):
 *    - Mental Model: Standing in line at a movie ticket counter.
 *      - New people join at the back (`rear` / `enqueue`).
 *      - People are served and leave from the front (`front` / `dequeue`).
 *      - The person who arrived first is served first!
 *
 * 2. THE INFAMOUS "FALSE OVERFLOW" BUG IN LINEAR QUEUES:
 *    Suppose an array has size 5:
 *      Step 1: Enqueue 5 items. (Indices 0, 1, 2, 3, 4 are filled. `rear = 4`).
 *      Step 2: Dequeue 3 items. (Indices 0, 1, 2 are now FREE and empty!).
 *      Step 3: Try to enqueue a new item.
 *              A linear queue checks: `if (rear == MAX - 1)` -> TRUE!
 *              The linear queue rejects the item saying "Queue Full!", EVEN THOUGH
 *              SLOTS 0, 1, 2 ARE COMPLETELY EMPTY! This is "False Overflow"!
 *
 * 3. THE CIRCULAR QUEUE SOLUTION (MODULO ARITHMETIC):
 *    Instead of a straight line, bend the array into a CIRCLE like a clock face!
 *    When `rear` reaches the end of the array (index 4 in size 5):
 *      `(4 + 1) % 5 = 0` -> The next index automatically wraps back to 0!
 *    This allows freed space at the beginning to be reused over and over!
 *
 * 4. KEEPING TRACK OF FULL VS EMPTY:
 *    Using an explicit `count` variable makes this crystal clear:
 *      - `isEmpty()`: `count == 0`
 *      - `isFull()` : `count == CAPACITY`
 * ============================================================================
 */

#include <iostream>

using namespace std;

const int CAPACITY = 5;

/**
 * ----------------------------------------------------------------------------
 * THE CIRCULAR QUEUE CLASS
 * ----------------------------------------------------------------------------
 */
class CircularQueue {
private:
    int queue[CAPACITY]; // Circular array buffer
    int front;           // Index of element to be served next
    int rear;            // Index of most recently arrived element
    int count;           // Exact number of active items in queue

public:
    // Constructor: Queue starts empty
    CircularQueue() : front(0), rear(-1), count(0) {}

    // Queue is full when active elements equal maximum physical capacity
    bool isFull() const { return count == CAPACITY; }

    // Queue is empty when active element count is 0
    bool isEmpty() const { return count == 0; }

    /**
     * ------------------------------------------------------------------------
     * ENQUEUE: Insert at the Rear
     * ------------------------------------------------------------------------
     */
    void enqueue(int val) {
        if (isFull()) {
            cout << "  [OVERFLOW] Cannot enqueue " << val << ". Queue is 100% full!\n";
            return;
        }

        // Circular Index Math: If rear was 4, (4 + 1) % 5 wraps rear to 0!
        rear = (rear + 1) % CAPACITY;
        queue[rear] = val;
        count++;

        cout << "  Enqueued [" << val << "] -> Placed at physical index [" 
             << rear << "]. (Active items: " << count << "/" << CAPACITY << ")\n";
    }

    /**
     * ------------------------------------------------------------------------
     * DEQUEUE: Remove from the Front
     * ------------------------------------------------------------------------
     */
    int dequeue() {
        if (isEmpty()) {
            cout << "  [UNDERFLOW] Cannot dequeue. Queue is empty!\n";
            return -1;
        }

        int removedValue = queue[front];

        // Circular Index Math: Advance front cyclically
        front = (front + 1) % CAPACITY;
        count--;

        cout << "  Dequeued [" << removedValue << "] -> Next front is now index [" 
             << front << "]. (Active items: " << count << "/" << CAPACITY << ")\n";
        return removedValue;
    }

    /**
     * ------------------------------------------------------------------------
     * DISPLAY: Traversal from Front to Rear using Modulo
     * ------------------------------------------------------------------------
     */
    void display() const {
        if (isEmpty()) {
            cout << "  Current Queue: [Empty]\n\n";
            return;
        }

        cout << "  Current Queue (" << count << " items): [ ";
        // Walk 'count' times starting from 'front'
        for (int i = 0; i < count; i++) {
            int circularIndex = (front + i) % CAPACITY;
            cout << queue[circularIndex] << " ";
        }
        cout << "]  (Front is at [" << front << "], Rear is at [" << rear << "])\n\n";
    }
};

int main() {
    cout << "========================================================\n";
    cout << "  TEACHER DEMO: CIRCULAR QUEUE (MODULO WRAP-AROUND)\n";
    cout << "========================================================\n\n";

    CircularQueue cq;

    // STEP 1: Fill queue to capacity (5 elements)
    cout << "--- 1. FILLING QUEUE TO FULL CAPACITY (5 Items) ---\n";
    cq.enqueue(10);
    cq.enqueue(20);
    cq.enqueue(30);
    cq.enqueue(40);
    cq.enqueue(50);
    cq.display();

    // Verify overflow rejection
    cout << "--- 2. ATTEMPTING ENQUEUE ON FULL QUEUE ---\n";
    cq.enqueue(999);
    cout << "\n";

    // STEP 2: Dequeue 2 items (frees index 0 and index 1)
    cout << "--- 3. DEQUEUEING 2 ITEMS FROM FRONT ---\n";
    cq.dequeue(); // Frees slot [0]
    cq.dequeue(); // Frees slot [1]
    cq.display();

    // STEP 3: Enqueue 2 new items (DEMONSTRATING CIRCULAR WRAP-AROUND!)
    cout << "--- 4. ENQUEUEING NEW ITEMS (REUSING FREED SLOTS) ---\n";
    cout << "Notice where 60 and 70 land in memory:\n";
    cq.enqueue(60); // Wraps around to physical index 0!
    cq.enqueue(70); // Wraps around to physical index 1!
    cq.display();

    return 0;
}

/**
 * ============================================================================
 * 🎓 VIVA QUESTIONS & ANSWERS FOR THIS CODE:
 * ============================================================================
 * Q1: What is the main advantage of a Circular Queue over a Linear Queue?
 * A1: Memory utilization. In a linear queue, elements dequeued from the front leave
 *     dead, unusable space ("False Overflow"). A circular queue reclaims this space
 *     by wrapping indices back to 0 using modulo arithmetic.
 *
 * Q2: What is the formula for circular wrap-around?
 * A2: - For Enqueue: `rear = (rear + 1) % CAPACITY;`
 *     - For Dequeue: `front = (front + 1) % CAPACITY;`
 *
 * Q3: What is the Time Complexity of Enqueue and Dequeue?
 * A3: O(1) instantaneous time for both operations. No elements are ever shifted!
 *     Only index pointers and counts are updated.
 *
 * Q4: What are real-world applications of Circular Queues?
 * A4: 1. Round-Robin CPU process scheduling in operating systems.
 *     2. Circular memory buffers in audio/video streaming and network routers.
 *     3. Memory ring buffers for keyboard keystrokes and hardware interrupts.
 * ============================================================================
 */
