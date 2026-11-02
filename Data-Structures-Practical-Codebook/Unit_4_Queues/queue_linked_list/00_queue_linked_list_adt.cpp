/*
========================================================================================
PROGRAM HEADER:
- Program Number: 00-QueueLL
- Program Title: Queue Abstract Data Type (ADT) using Singly Linked List
- Unit: Unit IV - Queue
- Relevant Curriculum Topic: Queue Definition, Operations, Linked List Implementation
- Course Code: CE25PCC-202 (Theory Core) & CE25PCC-203 (Laboratory Foundation)
- Objective:
  Implement a dynamic FIFO Queue using a linked list with `front` and `rear` pointers,
  supporting enqueue, dequeue, peek, and dynamic memory deallocation.
- Data Structure Used: Singly Linked List with `front` pointing to the first node and
  `rear` pointing to the last node.
- What This Program Demonstrates:
  O(1) enqueue at rear, O(1) dequeue at front, elimination of false overflow,
  heap allocation, and pointer synchronization.
========================================================================================

CONCEPT: WHY USE A LINKED LIST FOR A QUEUE?
1. Solves the False Overflow Problem:
   - In a linear array queue, once `rear` hits `MAX - 1`, the queue claims it is full
     even if all front elements were dequeued!
   - In a linked queue, every new arrival is simply allocated a new node in the heap
     and appended to `rear`. There is NO false overflow and NO arbitrary size limit!
2. True O(1) Operations at Both Ends:
   - We maintain TWO pointers:
     * `front`: Points to the head of the list (where dequeue happens).
     * `rear`: Points to the tail of the list (where enqueue happens).
   - Dequeue from `front`: O(1) (head deletion).
   - Enqueue at `rear`: O(1) (tail append via `rear->next = newNode`).
*/

#include <iostream>
#include <iomanip>

using namespace std;

// Definition of a Queue Node
struct QueueNode {
    int data;
    QueueNode* next;

    QueueNode(int val) {
        data = val;
        next = nullptr;
    }
};

class LinkedListQueue {
private:
    QueueNode* front; // Pointer to head of queue (next item to dequeue)
    QueueNode* rear;  // Pointer to tail of queue (most recently enqueued item)
    int count;

public:
    LinkedListQueue() {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    ~LinkedListQueue() {
        clear();
    }

    bool isEmpty() const {
        return (front == nullptr);
    }

    /*
    ALGORITHM: ENQUEUE (INSERT AT REAR)
    1. Allocate new node: `newNode = new QueueNode(val)`.
    2. CASE 1: Queue is empty (`isEmpty()`):
       Set BOTH `front = newNode;` and `rear = newNode;`
    3. CASE 2: Queue contains existing nodes:
       a. Link current rear to new node: `rear->next = newNode;`
       b. Advance rear pointer: `rear = newNode;`
    4. Increment `count++`.
    */
    void enqueue(int value) {
        QueueNode* newNode = new QueueNode(value);

        if (isEmpty()) {
            front = newNode;
            rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;

        cout << ">> ENQUEUE: [" << value << "] added at Rear (Node Addr: " << newNode << ").\n";
    }

    /*
    ALGORITHM: DEQUEUE (DELETE FROM FRONT)
    1. If `isEmpty()`, report Queue Underflow and return -1.
    2. Save address of front node: `temp = front;`
    3. Extract data: `dequeuedVal = temp->data;`
    4. Advance front: `front = front->next;`
    5. If front became `nullptr` (queue was emptied):
       Set `rear = nullptr;` as well!
       (WHY? Because if front is null but rear still holds the old node's address,
        rear becomes a dangling pointer!).
    6. Delete old front node: `delete temp;`
    7. Decrement `count--`.
    8. Return `dequeuedVal`.
    */
    int dequeue() {
        if (isEmpty()) {
            cout << "[ERROR] Queue Underflow! Linked queue is completely empty.\n";
            return -1;
        }

        QueueNode* temp = front;
        int dequeuedVal = temp->data;

        front = front->next; // Move front to successor node

        // If queue is now empty, synchronize rear pointer to null
        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp; // Release heap memory
        count--;

        cout << ">> DEQUEUE: [" << dequeuedVal << "] removed from Front.\n";
        return dequeuedVal;
    }

    /*
    ALGORITHM: PEEK FRONT
    1. If empty, report error and return -1.
    2. Return `front->data`.
    */
    int peekFront() const {
        if (isEmpty()) {
            cout << "[ERROR] Queue is empty.\n";
            return -1;
        }
        return front->data;
    }

    /*
    ALGORITHM: DISPLAY QUEUE
    1. If empty, print "[EMPTY]" and return.
    2. Pointer `temp = front`.
    3. Loop while `temp != nullptr`:
       Print node data and link address.
       Advance: `temp = temp->next`.
    */
    void display() const {
        if (isEmpty()) {
            cout << "\n   [LINKED QUEUE: EMPTY]\n";
            return;
        }

        cout << "\n   --- CURRENT LINKED QUEUE CONTENTS (FRONT TO REAR) ---\n";
        cout << "   (FRONT: " << front->data << ") ---> ";

        const QueueNode* temp = front;
        while (temp != nullptr) {
            cout << "[" << temp->data << "] -> ";
            temp = temp->next;
        }
        cout << "NULL (REAR: " << rear->data << ")\n";
        cout << "   Total Active Nodes in Queue: " << count << "\n\n";
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

// Interactive demonstration runner
int main() {
    LinkedListQueue dynamicQueue;

    cout << "==============================================================\n";
    cout << "   DYNAMIC QUEUE ADT (LINKED LIST IMPLEMENTATION)            \n";
    cout << "==============================================================\n";

    // 1. Initial State
    cout << "\n--- DEMO STEP 1: Empty Queue Inspection ---\n";
    cout << "Is queue empty? " << (dynamicQueue.isEmpty() ? "YES" : "NO") << "\n";
    dynamicQueue.display();

    // 2. Underflow Check
    cout << "--- DEMO STEP 2: Testing Underflow ---\n";
    dynamicQueue.dequeue();

    // 3. Enqueuing elements
    cout << "\n--- DEMO STEP 3: Enqueuing elements (10, 20, 30, 40) ---\n";
    dynamicQueue.enqueue(10);
    dynamicQueue.enqueue(20);
    dynamicQueue.enqueue(30);
    dynamicQueue.enqueue(40);
    dynamicQueue.display();

    // 4. Peeking
    cout << "--- DEMO STEP 4: Peeking at Front ---\n";
    cout << "Front element: [" << dynamicQueue.peekFront() << "]\n";

    // 5. Dequeuing elements (FIFO)
    cout << "\n--- DEMO STEP 5: Dequeuing two elements (FIFO) ---\n";
    dynamicQueue.dequeue(); // 10 leaves
    dynamicQueue.dequeue(); // 20 leaves
    dynamicQueue.display();

    // 6. Enqueuing more elements seamlessly (No False Overflow!)
    cout << "--- DEMO STEP 6: Enqueuing new elements (50, 60, 70, 80) ---\n";
    cout << "(Notice: No overflow occurs, heap memory expands dynamically!)\n";
    dynamicQueue.enqueue(50);
    dynamicQueue.enqueue(60);
    dynamicQueue.enqueue(70);
    dynamicQueue.enqueue(80);
    dynamicQueue.display();

    cout << "==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
1. Enqueue 10, 20, 30, 40 -> Front: 10, Rear: 40
2. Peek Front -> 10
3. Dequeue -> 10 leaves (Front becomes 20)
4. Dequeue -> 20 leaves (Front becomes 30)
5. Enqueue 50, 60, 70, 80 -> Linked list grows dynamically.

SAMPLE OUTPUT:
==============================================================
   DYNAMIC QUEUE ADT (LINKED LIST IMPLEMENTATION)            
==============================================================

--- DEMO STEP 1: Empty Queue Inspection ---
Is queue empty? YES

   [LINKED QUEUE: EMPTY]
--- DEMO STEP 2: Testing Underflow ---
[ERROR] Queue Underflow! Linked queue is completely empty.

--- DEMO STEP 3: Enqueuing elements (10, 20, 30, 40) ---
>> ENQUEUE: [10] added at Rear (Node Addr: 0x1f5c20).
>> ENQUEUE: [20] added at Rear (Node Addr: 0x1f5c40).
>> ENQUEUE: [30] added at Rear (Node Addr: 0x1f5c60).
>> ENQUEUE: [40] added at Rear (Node Addr: 0x1f5c80).

   --- CURRENT LINKED QUEUE CONTENTS (FRONT TO REAR) ---
   (FRONT: 10) ---> [10] -> [20] -> [30] -> [40] -> NULL (REAR: 40)
   Total Active Nodes in Queue: 4

--- DEMO STEP 4: Peeking at Front ---
Front element: [10]

--- DEMO STEP 5: Dequeuing two elements (FIFO) ---
>> DEQUEUE: [10] removed from Front.
>> DEQUEUE: [20] removed from Front.

   --- CURRENT LINKED QUEUE CONTENTS (FRONT TO REAR) ---
   (FRONT: 30) ---> [30] -> [40] -> NULL (REAR: 40)
   Total Active Nodes in Queue: 2

--- DEMO STEP 6: Enqueuing new elements (50, 60, 70, 80) ---
(Notice: No overflow occurs, heap memory expands dynamically!)
>> ENQUEUE: [50] added at Rear (Node Addr: 0x1f5ca0).
>> ENQUEUE: [60] added at Rear (Node Addr: 0x1f5cc0).
>> ENQUEUE: [70] added at Rear (Node Addr: 0x1f5ce0).
>> ENQUEUE: [80] added at Rear (Node Addr: 0x1f5d00).

   --- CURRENT LINKED QUEUE CONTENTS (FRONT TO REAR) ---
   (FRONT: 30) ---> [30] -> [40] -> [50] -> [60] -> [70] -> [80] -> NULL (REAR: 80)
   Total Active Nodes in Queue: 6

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
>> DEQUEUE: [30] removed from Front.
>> DEQUEUE: [40] removed from Front.
>> DEQUEUE: [50] removed from Front.
>> DEQUEUE: [60] removed from Front.
>> DEQUEUE: [70] removed from Front.
>> DEQUEUE: [80] removed from Front.
========================================================================================

TIME COMPLEXITY:
- `enqueue()`:  O(1) - appends at `rear` via direct pointer link.
- `dequeue()`:  O(1) - removes head node via `front = front->next`.
- `peekFront()`: O(1).
- `isEmpty()`:  O(1).
- `display()`:  O(N).
- `clear()`:    O(N).

SPACE COMPLEXITY:
- Auxiliary Space: O(1).
- Total Dynamic Memory: O(N) heap memory (16 bytes per node).

WHY?
Because having both `front` and `rear` pointers allows instant access to both ends
without ever traversing the list for insertion or deletion.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Dangling Pointer on Last Dequeue:
   - When the last node is dequeued (`front == nullptr`), if you forget `rear = nullptr;`,
     `rear` still holds the address of the deleted node!
   - Next enqueue will try `rear->next = newNode`, causing undefined memory corruption!
2. First Enqueue Case:
   - When enqueuing the first node, you MUST set both `front = newNode;` and `rear = newNode;`.
========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Two pointers: `QueueNode *front, *rear;`
[ ] 2. Enqueue: `if (isEmpty()) front = rear = newNode; else { rear->next = newNode; rear = newNode; }`
[ ] 3. Dequeue: `temp = front; front = front->next; if (front == nullptr) rear = nullptr; delete temp;`
[ ] 4. Empty check: `return front == nullptr;`
========================================================================================
*/
