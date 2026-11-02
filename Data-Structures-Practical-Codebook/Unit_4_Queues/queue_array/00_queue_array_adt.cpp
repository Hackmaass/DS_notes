/*
========================================================================================
PROGRAM HEADER:
- Program Number: 00-QueueArray
- Program Title: Linear Queue Abstract Data Type (ADT) using Contiguous Array
- Unit: Unit IV - Queue
- Relevant Curriculum Topic: Queue Definition, Operations, FIFO Principle, Linear Array Implementation
- Course Code: CE25PCC-202 (Theory Core) & CE25PCC-203 (Laboratory Foundation)
- Objective:
  Implement a linear queue using a fixed-size array with enqueue, dequeue, peek,
  isEmpty, isFull, and queue display operations, demonstrating FIFO and linear boundary states.
- Data Structure Used: Static Contiguous Array with `front` and `rear` index pointers.
- What This Program Demonstrates:
  FIFO (First-In, First-Out) discipline, enqueue at rear, dequeue from front,
  underflow/overflow conditions, and the "false overflow" space limitation of linear arrays.
========================================================================================

CONCEPT: WHAT IS A QUEUE AND WHY DO WE NEED IT?
A Queue is a linear data structure that follows the FIFO (First In, First Out) principle.
This means that elements are inserted at ONE END (called the `REAR` or TAIL)
and removed from the OPPOSITE END (called the `FRONT` or HEAD).

REAL-WORLD ANALOGY:
Think of people waiting in line at a movie ticket counter:
- The first person to arrive is served first and leaves from the front (`dequeue`).
- New arrivals must join the end of the line at the rear (`enqueue`).
- Cutting in line is forbidden!

WHY DO WE INITIALIZE `front = -1` AND `rear = -1`?
When the queue has zero elements, neither front nor rear refers to any valid array slot.
When the very first element is enqueued:
- Both `front` and `rear` become `0`!

THE "FALSE OVERFLOW" PROBLEM IN LINEAR QUEUES:
In a linear array queue:
- Every time we enqueue, `rear` moves right (`rear++`).
- Every time we dequeue, `front` moves right (`front++`).
- Eventually, `rear` reaches the end of the array (`rear == MAX - 1`).
- If elements were previously dequeued from the front, there are FREE EMPTY SLOTS at the beginning
  (indices 0, 1, 2...), yet the linear queue reports "Queue is Full"!
- This limitation directly motivates the CIRCULAR QUEUE (covered in Assignment 14).
*/

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_QUEUE = 5;

class LinearQueue {
private:
    int items[MAX_QUEUE];
    int front; // Index of the front element (served next)
    int rear;  // Index of the last inserted element

public:
    LinearQueue() {
        front = -1; // Empty queue indicator
        rear = -1;
    }

    bool isEmpty() const {
        return (front == -1 && rear == -1);
    }

    bool isFull() const {
        return (rear == MAX_QUEUE - 1);
    }

    /*
    ALGORITHM: ENQUEUE (INSERTION AT REAR)
    1. Check if queue is full: `if (isFull())`.
       If true, report Queue Overflow and return false.
    2. If queue is currently empty (`isEmpty()`):
       Set `front = 0;` (first element is now at index 0).
    3. Increment rear: `rear++;`
    4. Store value: `items[rear] = value;`
    5. Report success and return true.
    */
    bool enqueue(int value) {
        if (isFull()) {
            cout << "[ERROR] Queue Overflow! Rear has reached end of array (Index " 
                 << (MAX_QUEUE - 1) << "). Cannot enqueue " << value << ".\n";
            return false;
        }

        // If inserting the very first element
        if (isEmpty()) {
            front = 0;
        }

        rear++;
        items[rear] = value;
        cout << ">> ENQUEUE: [" << value << "] added at Rear (Index " << rear 
             << ") | Front is at Index " << front << ".\n";
        return true;
    }

    /*
    ALGORITHM: DEQUEUE (DELETION FROM FRONT)
    1. Check if queue is empty: `if (isEmpty())`.
       If true, report Queue Underflow and return -1.
    2. Retrieve value at front: `dequeuedVal = items[front];`
    3. Check if queue had only ONE remaining element (`front == rear`):
       Reset queue to empty: `front = -1; rear = -1;`
    4. Else (multiple elements exist):
       Advance front pointer: `front++;`
    5. Return `dequeuedVal`.
    */
    int dequeue() {
        if (isEmpty()) {
            cout << "[ERROR] Queue Underflow! Queue is completely empty. Cannot dequeue.\n";
            return -1;
        }

        int dequeuedVal = items[front];

        // Case: Only one element was in the queue
        if (front == rear) {
            cout << ">> DEQUEUE: Last element [" << dequeuedVal << "] removed. Queue reset to empty (-1, -1).\n";
            front = -1;
            rear = -1;
        } else {
            cout << ">> DEQUEUE: [" << dequeuedVal << "] removed from Front (was Index " << front << "). ";
            front++;
            cout << "Front advanced to Index " << front << ".\n";
        }

        return dequeuedVal;
    }

    /*
    ALGORITHM: PEEK FRONT
    1. Check if empty. If so, return -1.
    2. Return `items[front]`.
    */
    int peekFront() const {
        if (isEmpty()) {
            cout << "[ERROR] Queue is empty.\n";
            return -1;
        }
        return items[front];
    }

    /*
    ALGORITHM: DISPLAY QUEUE
    1. If empty, print "[EMPTY]" and return.
    2. Loop from `front` to `rear`:
       Print each element.
    */
    void display() const {
        if (isEmpty()) {
            cout << "\n   [QUEUE STATUS: EMPTY]\n";
            return;
        }

        cout << "\n   --- CURRENT LINEAR QUEUE CONTENTS (FRONT TO REAR) ---\n";
        cout << "   Indices: ";
        for (int i = 0; i < MAX_QUEUE; i++) {
            cout << setw(6) << ("[" + to_string(i) + "]");
        }
        cout << "\n   Data:    ";
        for (int i = 0; i < MAX_QUEUE; i++) {
            if (i >= front && i <= rear && front != -1) {
                cout << setw(6) << items[i];
            } else {
                cout << setw(6) << "-";
            }
        }
        cout << "\n            ";
        for (int i = 0; i < MAX_QUEUE; i++) {
            if (i == front && i == rear) cout << setw(6) << "^F,R";
            else if (i == front) cout << setw(6) << "^F";
            else if (i == rear) cout << setw(6) << "^R";
            else cout << setw(6) << " ";
        }
        cout << "\n   Active Elements Count: " << (rear - front + 1) << " / " << MAX_QUEUE << "\n\n";
    }
};

// Interactive demonstration runner
int main() {
    LinearQueue q;

    cout << "==============================================================\n";
    cout << "   LINEAR QUEUE ADT (ARRAY IMPLEMENTATION)                   \n";
    cout << "==============================================================\n";

    // 1. Initial State
    cout << "\n--- DEMO STEP 1: Empty Queue Check ---\n";
    cout << "Is queue empty? " << (q.isEmpty() ? "YES" : "NO") << "\n";
    q.display();

    // 2. Testing Underflow
    cout << "--- DEMO STEP 2: Testing Underflow ---\n";
    q.dequeue();

    // 3. Enqueuing elements
    cout << "\n--- DEMO STEP 3: Enqueuing elements (10, 20, 30, 40) ---\n";
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.display();

    // 4. Peeking Front
    cout << "--- DEMO STEP 4: Peeking Front Element ---\n";
    cout << "Element at Front: [" << q.peekFront() << "]\n";

    // 5. Dequeuing elements (FIFO demonstration)
    cout << "\n--- DEMO STEP 5: Dequeuing two elements (FIFO Demonstration) ---\n";
    q.dequeue(); // 10 leaves
    q.dequeue(); // 20 leaves
    q.display();

    // 6. Enqueuing to fill the array to the end
    cout << "--- DEMO STEP 6: Enqueuing elements 50 and 60 ---\n";
    q.enqueue(50);
    q.enqueue(60); // rear reaches MAX_QUEUE - 1 (index 4)
    q.display();

    // 7. Demonstrating the "False Overflow" phenomenon
    cout << "--- DEMO STEP 7: Demonstrating FALSE OVERFLOW limitation ---\n";
    cout << "Notice that slots [0] and [1] are completely EMPTY, but rear is at index 4!\n";
    cout << "Attempting to enqueue 70 into linear queue:\n";
    q.enqueue(70); // Triggers overflow even though only 3 slots out of 5 are used!

    cout << "\n==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
1. Enqueue 10, 20, 30, 40 -> front=0, rear=3
2. Dequeue -> 10 removed, front becomes 1
3. Dequeue -> 20 removed, front becomes 2
4. Enqueue 50 (rear=4), Enqueue 60 (rejected, rear=4 is full)
5. False overflow demonstrated: indices 0 and 1 are empty, yet queue reports full!

SAMPLE OUTPUT:
==============================================================
   LINEAR QUEUE ADT (ARRAY IMPLEMENTATION)                   
==============================================================

--- DEMO STEP 1: Empty Queue Check ---
Is queue empty? YES

   [QUEUE STATUS: EMPTY]
--- DEMO STEP 2: Testing Underflow ---
[ERROR] Queue Underflow! Queue is completely empty. Cannot dequeue.

--- DEMO STEP 3: Enqueuing elements (10, 20, 30, 40) ---
>> ENQUEUE: [10] added at Rear (Index 0) | Front is at Index 0.
>> ENQUEUE: [20] added at Rear (Index 1) | Front is at Index 0.
>> ENQUEUE: [30] added at Rear (Index 2) | Front is at Index 0.
>> ENQUEUE: [40] added at Rear (Index 3) | Front is at Index 0.

   --- CURRENT LINEAR QUEUE CONTENTS (FRONT TO REAR) ---
   Indices:    [0]   [1]   [2]   [3]   [4]
   Data:        10    20    30    40     -
                ^F                ^R      
   Active Elements Count: 4 / 5

--- DEMO STEP 4: Peeking Front Element ---
Element at Front: [10]

--- DEMO STEP 5: Dequeuing two elements (FIFO Demonstration) ---
>> DEQUEUE: [10] removed from Front (was Index 0). Front advanced to Index 1.
>> DEQUEUE: [20] removed from Front (was Index 1). Front advanced to Index 2.

   --- CURRENT LINEAR QUEUE CONTENTS (FRONT TO REAR) ---
   Indices:    [0]   [1]   [2]   [3]   [4]
   Data:         -     -    30    40     -
                            ^F    ^R      
   Active Elements Count: 2 / 5

--- DEMO STEP 6: Enqueuing elements 50 and 60 ---
>> ENQUEUE: [50] added at Rear (Index 4) | Front is at Index 2.
[ERROR] Queue Overflow! Rear has reached end of array (Index 4). Cannot enqueue 60.

   --- CURRENT LINEAR QUEUE CONTENTS (FRONT TO REAR) ---
   Indices:    [0]   [1]   [2]   [3]   [4]
   Data:         -     -    30    40    50
                            ^F          ^R
   Active Elements Count: 3 / 5

--- DEMO STEP 7: Demonstrating FALSE OVERFLOW limitation ---
Notice that slots [0] and [1] are completely EMPTY, but rear is at index 4!
Attempting to enqueue 70 into linear queue:
[ERROR] Queue Overflow! Rear has reached end of array (Index 4). Cannot enqueue 70.

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

TIME COMPLEXITY:
- `enqueue()`: O(1) constant time index assignment `items[++rear] = val`.
- `dequeue()`: O(1) constant time index increment `front++`.
- `peekFront()`: O(1) constant time.
- `isEmpty()` / `isFull()`: O(1).
- `display()`: O(N).

SPACE COMPLEXITY:
- Total Space: O(MAX_QUEUE) contiguous memory.
- Auxiliary Space: O(1).

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Forgetting to Reset on Last Deletion:
   - When the last element is removed (`front == rear`), you MUST reset `front = -1; rear = -1;`!
     Otherwise, `front` walks past `rear` and the queue state becomes corrupted.
2. Forgetting to Set `front = 0` on First Enqueue:
   - If inserting into an empty queue, `front` was `-1`. You must update `front = 0`!
========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Initial state: `front = -1; rear = -1;`
[ ] 2. Empty check: `front == -1 && rear == -1`
[ ] 3. Full check: `rear == MAX - 1`
[ ] 4. Enqueue: `if (isEmpty()) front = 0; items[++rear] = val;`
[ ] 5. Dequeue: `val = items[front]; if (front == rear) { front = rear = -1; } else front++; return val;`
========================================================================================
*/
