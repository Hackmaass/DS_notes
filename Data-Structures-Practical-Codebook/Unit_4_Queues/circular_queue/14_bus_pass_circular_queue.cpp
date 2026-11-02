/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit IV: Queues
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * ASSIGNMENT:    Group D - Assignment 14
 * TITLE:         Bus Pass Distribution Using Circular Queue
 * 
 * PROBLEM STATEMENT (Official Curriculum):
 *   Write a program using circular queue for bus pass distribution.
 *   a. Insert student IDs in circular queue
 *   b. Delete student ID as pass is issued
 *   c. Detect queue full/empty conditions
 *   d. Display the circular queue
 * 
 * ============================================================================
 * CONCEPT EXPLANATION: WHY CIRCULAR QUEUE?
 * ============================================================================
 * In a standard Linear Queue implemented using a fixed-size array:
 *   - Enqueue increments 'rear'.
 *   - Dequeue increments 'front'.
 *   - When 'rear' reaches MAX - 1, no more elements can be inserted, even if
 *     spaces have been vacated at index 0, 1, 2... due to earlier dequeues.
 *   - This flaw is known as "FALSE OVERFLOW" or "Memory Underutilization".
 * 
 * The Circular Queue solves false overflow by conceptually wrapping the array
 * into a ring:
 *   - The index immediately following (MAX - 1) is 0.
 *   - Modulo arithmetic is used: next_index = (current_index + 1) % MAX.
 *   - Empty Condition:  front == -1 (and rear == -1)
 *   - Full Condition:   (rear + 1) % MAX == front
 *     (Meaning: the very next position to be written by rear is already occupied by front!)
 *   - Reset Condition:  When the last remaining element is deleted (front == rear),
 *                       reset front = rear = -1.
 * 
 * REAL-WORLD DOMAIN ANALOGY:
 *   Students queue up at the college transport counter for semester bus passes.
 *   Tokens (Student IDs) are issued in circular order. When a student receives
 *   their pass, they exit from 'front'. The vacated token slots can be immediately
 *   re-assigned to newly arriving students wrapping around from 'rear'.
 * ============================================================================
 * STEP-BY-STEP ALGORITHM (WHAT & WHY)
 * ============================================================================
 * 1. INITIALIZATION:
 *    - Initialize an array `queue[MAX]`.
 *    - Set `front = -1` and `rear = -1` to represent an empty queue.
 * 
 * 2. ENQUEUE (Insert Student ID):
 *    - Step 2.1: Check Full Condition: `if ((rear + 1) % MAX == front)`
 *                WHY: If true, every slot in the array is occupied. Output "Queue Overflow".
 *    - Step 2.2: Check First Insertion: `if (front == -1)`
 *                WHY: When inserting the first element, both front and rear must move from -1 to 0.
 *                Set `front = 0`, `rear = 0`.
 *    - Step 2.3: General Insertion:
 *                `rear = (rear + 1) % MAX`
 *                WHY: Wrap around if rear reaches MAX - 1 and slots are free at index 0.
 *    - Step 2.4: Store student ID at `queue[rear]`.
 * 
 * 3. DEQUEUE (Issue Bus Pass & Remove Student ID):
 *    - Step 3.1: Check Empty Condition: `if (front == -1)`
 *                WHY: Cannot serve if no student is waiting. Output "Queue Underflow".
 *    - Step 3.2: Retrieve served student ID: `id = queue[front]`.
 *    - Step 3.3: Check Single Element Case: `if (front == rear)`
 *                WHY: If only one element was left, removing it empties the queue.
 *                Reset `front = -1` and `rear = -1`.
 *    - Step 3.4: General Dequeue:
 *                `front = (front + 1) % MAX`
 *                WHY: Advance front pointer in circular fashion.
 *    - Step 3.5: Return served student ID.
 * 
 * 4. DISPLAY (Print Circular Queue):
 *    - Step 4.1: If `front == -1`, print "Queue is Empty".
 *    - Step 4.2: Start a pointer/index `i = front`.
 *    - Step 4.3: Loop:
 *                Print `queue[i]`.
 *                If `i == rear`, terminate loop (all active elements visited).
 *                Advance `i = (i + 1) % MAX`.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Maximum capacity for demonstration of wrap-around behavior
const int MAX_STUDENTS = 5;

class BusPassCircularQueue {
private:
    int queue[MAX_STUDENTS]; // Fixed-size storage buffer
    int front;               // Index of earliest student waiting
    int rear;                // Index of most recent student enrolled

public:
    // Constructor: Initialize pointers to indicate empty state
    BusPassCircularQueue() {
        front = -1;
        rear = -1;
    }

    // ------------------------------------------------------------------------
    // OPERATION: Check if queue is completely empty
    // ------------------------------------------------------------------------
    bool isEmpty() const {
        return (front == -1);
    }

    // ------------------------------------------------------------------------
    // OPERATION: Check if queue has reached maximum capacity
    // KEY LOGIC: If (rear + 1) wrapped around equals front, no slots remain.
    // ------------------------------------------------------------------------
    bool isFull() const {
        return ((rear + 1) % MAX_STUDENTS == front);
    }

    // ------------------------------------------------------------------------
    // OPERATION a: Insert student ID into circular queue (Enqueue)
    // ------------------------------------------------------------------------
    bool enqueue(int studentId) {
        // Step 1: Guard against queue overflow
        if (isFull()) {
            cout << "  [OVERFLOW ERROR] Cannot register Student ID " << studentId 
                 << ". Circular Queue is FULL! (Capacity: " << MAX_STUDENTS << ")\n";
            return false;
        }

        // Step 2: Handle first element insertion
        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            // Step 3: Advance rear circularly using modulo
            rear = (rear + 1) % MAX_STUDENTS;
        }

        // Step 4: Place student ID at newly updated rear index
        queue[rear] = studentId;
        cout << "  [ENQUEUE SUCCESS] Student ID " << studentId 
             << " enrolled. (Slot: " << rear 
             << ", front=" << front << ", rear=" << rear << ")\n";
        return true;
    }

    // ------------------------------------------------------------------------
    // OPERATION b: Issue pass and remove student ID (Dequeue)
    // ------------------------------------------------------------------------
    int dequeue() {
        // Step 1: Guard against queue underflow
        if (isEmpty()) {
            cout << "  [UNDERFLOW ERROR] No students in queue! All bus passes issued.\n";
            return -1;
        }

        // Step 2: Extract student ID at front
        int servedId = queue[front];
        int servedIndex = front;

        // Step 3: Update front pointer
        if (front == rear) {
            // Case A: Last remaining element is being removed -> Reset to empty
            front = -1;
            rear = -1;
        } else {
            // Case B: Advance front circularly
            front = (front + 1) % MAX_STUDENTS;
        }

        cout << "  [DEQUEUE SUCCESS] Bus Pass ISSUED to Student ID: " << servedId
             << " (Vacated Slot: " << servedIndex 
             << ", new front=" << front << ", rear=" << rear << ")\n";
        return servedId;
    }

    // ------------------------------------------------------------------------
    // OPERATION c: Display status (Empty, Full, Current Pointers)
    // ------------------------------------------------------------------------
    void displayStatus() const {
        cout << "\n  --- Queue Status ---\n";
        cout << "  Front Index : " << front << "\n";
        cout << "  Rear Index  : " << rear << "\n";
        cout << "  Is Empty?   : " << (isEmpty() ? "YES" : "NO") << "\n";
        cout << "  Is Full?    : " << (isFull() ? "YES" : "NO") << "\n";
        cout << "  Capacity    : " << MAX_STUDENTS << "\n";
    }

    // ------------------------------------------------------------------------
    // OPERATION d: Display complete circular queue elements
    // ------------------------------------------------------------------------
    void display() const {
        if (isEmpty()) {
            cout << "  [QUEUE DISPLAY] Circular Queue is EMPTY (front = -1, rear = -1).\n";
            return;
        }

        cout << "\n  [CIRCULAR QUEUE STATE] (front=" << front << ", rear=" << rear << "):\n";
        cout << "  Logical Order (First in line -> Last in line):\n  ";

        int i = front;
        while (true) {
            cout << "[" << queue[i] << " (index " << i << ")]";
            if (i == rear) {
                break; // We have visited up to rear
            }
            cout << " -> ";
            i = (i + 1) % MAX_STUDENTS; // Advance circularly
        }
        cout << "\n";

        // Display physical underlying array storage representation
        cout << "  Physical Array Memory Dump [0.." << MAX_STUDENTS - 1 << "]:\n  | ";
        for (int idx = 0; idx < MAX_STUDENTS; ++idx) {
            // Determine if slot 'idx' is within the active logical range
            bool isActive = false;
            if (!isEmpty()) {
                if (front <= rear) {
                    isActive = (idx >= front && idx <= rear);
                } else {
                    // Wrapped around: active from front..MAX-1 and 0..rear
                    isActive = (idx >= front || idx <= rear);
                }
            }

            if (isActive) {
                cout << setw(5) << queue[idx];
                if (idx == front && idx == rear) cout << "(F,R)";
                else if (idx == front)           cout << "(F)  ";
                else if (idx == rear)            cout << "(R)  ";
                else                             cout << "     ";
            } else {
                cout << setw(5) << "FREE" << "     ";
            }
            cout << " | ";
        }
        cout << "\n\n";
    }
};

// ============================================================================
// DEMONSTRATION & VERIFICATION DRIVER
// ============================================================================
void runAutomatedCurriculumVerification() {
    cout << "====================================================================\n";
    cout << "  EXAM VERIFICATION DEMO: Bus Pass Circular Queue Simulation\n";
    cout << "  (Demonstrating Circular Wrap-Around & False Overflow Solution)\n";
    cout << "====================================================================\n";

    BusPassCircularQueue cq;

    cout << "\n--- STEP 1: Verify Empty Condition ---\n";
    cq.display();
    cout << "Is Empty: " << (cq.isEmpty() ? "TRUE" : "FALSE") << "\n";

    cout << "\n--- STEP 2: Enqueue 4 Students (ID: 101, 102, 103, 104) ---\n";
    cq.enqueue(101);
    cq.enqueue(102);
    cq.enqueue(103);
    cq.enqueue(104);
    cq.display();

    cout << "\n--- STEP 3: Enqueue 5th Student (ID: 105) -> Fills Capacity ---\n";
    cq.enqueue(105);
    cq.display();
    cout << "Is Full: " << (cq.isFull() ? "TRUE" : "FALSE") << "\n";

    cout << "\n--- STEP 4: Attempt Enqueue when Full (ID: 106) -> Expect Overflow ---\n";
    cq.enqueue(106);

    cout << "\n--- STEP 5: Issue Pass to First 2 Students (Dequeue 101, 102) ---\n";
    cout << "NOTE: In linear queue, slots 0 and 1 would now be permanently wasted.\n";
    cq.dequeue();
    cq.dequeue();
    cq.display();

    cout << "\n--- STEP 6: Wrap-Around Enqueue (Student ID: 106, 107) ---\n";
    cout << "REUSE VACATED SLOTS 0 and 1 via Modulo Arithmetic!\n";
    cq.enqueue(106); // Will occupy index 0
    cq.enqueue(107); // Will occupy index 1
    cq.display();

    cout << "\n--- STEP 7: Dequeue Remaining Students Until Empty ---\n";
    while (!cq.isEmpty()) {
        cq.dequeue();
    }
    cq.display();

    cout << "\n--- STEP 8: Attempt Dequeue on Empty Queue -> Expect Underflow ---\n";
    cq.dequeue();
}

int main() {
    runAutomatedCurriculumVerification();

    cout << "\n====================================================================\n";
    cout << "  INTERACTIVE MENU (For College Practical Viva & Lab Examination)\n";
    cout << "====================================================================\n";

    BusPassCircularQueue userQueue;
    int choice = 0;
    int studentId = 0;

    do {
        cout << "\n===== BUS PASS CIRCULAR QUEUE MENU =====\n";
        cout << "1. Enqueue Student (Register for Bus Pass)\n";
        cout << "2. Dequeue Student (Issue Bus Pass)\n";
        cout << "3. Check Empty / Full Conditions\n";
        cout << "4. Display Circular Queue\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";
        
        if (!(cin >> choice)) {
            cout << "Invalid input. Terminating interactive session.\n";
            break;
        }

        switch (choice) {
            case 1:
                cout << "Enter Student ID to enqueue: ";
                cin >> studentId;
                userQueue.enqueue(studentId);
                userQueue.display();
                break;
            case 2:
                userQueue.dequeue();
                userQueue.display();
                break;
            case 3:
                userQueue.displayStatus();
                break;
            case 4:
                userQueue.display();
                break;
            case 5:
                cout << "Exiting Bus Pass System. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please choose between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}

/*
 * ============================================================================
 * STEP-BY-STEP DRY RUN TRACE TABLE
 * ============================================================================
 * Initial: MAX = 5, front = -1, rear = -1, queue = [ ?, ?, ?, ?, ? ]
 * 
 * Step | Operation    | ID  | front | rear | (rear+1)%5 | Array Content [0..4]      | Action / Note
 * -----+--------------+-----+-------+------+------------+---------------------------+-------------------------------------
 *  1   | Enqueue(101) | 101 |   0   |  0   |     1      | [ 101,  ?,  ?,  ?,  ? ]   | First element: front=0, rear=0
 *  2   | Enqueue(102) | 102 |   0   |  1   |     2      | [ 101, 102, ?,  ?,  ? ]   | rear moves 0 -> 1
 *  3   | Enqueue(103) | 103 |   0   |  2   |     3      | [ 101, 102, 103, ?, ? ]   | rear moves 1 -> 2
 *  4   | Enqueue(104) | 104 |   0   |  3   |     4      | [ 101, 102, 103, 104, ? ] | rear moves 2 -> 3
 *  5   | Enqueue(105) | 105 |   0   |  4   |     0      | [ 101, 102, 103, 104, 105]| rear moves 3 -> 4. Queue is FULL!
 *  6   | Enqueue(106) | 106 |   0   |  4   |     0      | [ 101, 102, 103, 104, 105]| (rear+1)%5 == front (0==0) -> OVERFLOW
 *  7   | Dequeue()    |  -  |   1   |  4   |     0      | [   ?, 102, 103, 104, 105]| Removes 101. front moves 0 -> 1
 *  8   | Dequeue()    |  -  |   2   |  4   |     0      | [   ?,   ?, 103, 104, 105]| Removes 102. front moves 1 -> 2
 *  9   | Enqueue(106) | 106 |   2   |  0   |     1      | [ 106,   ?, 103, 104, 105]| WRAP AROUND! rear=(4+1)%5 = 0
 * 10   | Enqueue(107) | 107 |   2   |  1   |     2      | [ 106, 107, 103, 104, 105]| rear=(0+1)%5 = 1. FULL again!
 * ============================================================================
 * COMPLEXITY ANALYSIS
 * ============================================================================
 * Operation    | Time Complexity | Space Complexity | Explanation
 * -------------+-----------------+------------------+------------------------------------------------
 * Enqueue      | O(1)            | O(1)             | Simple modulo increment and direct array index write.
 * Dequeue      | O(1)            | O(1)             | Direct array index read and modulo increment.
 * isEmpty      | O(1)            | O(1)             | Single conditional check (front == -1).
 * isFull       | O(1)            | O(1)             | Single conditional check ((rear + 1) % MAX == front).
 * Display      | O(N)            | O(1)             | Iterates from front to rear visiting each item once.
 * Auxiliary Space: O(MAX) for fixed array buffer.
 * ============================================================================
 * COMMON EXAM PITFALLS & MISTAKES TO AVOID
 * ============================================================================
 * 1. Forgetting Modulo: Writing `rear++` instead of `rear = (rear + 1) % MAX`.
 *    This causes out-of-bounds array access and destroys circular behavior.
 * 2. Incorrect Full Condition: Writing `rear == MAX - 1`. That is the linear
 *    queue condition! The circular queue full condition is:
 *    `(rear + 1) % MAX == front`.
 * 3. Not Resetting on Empty: After deleting the last element (`front == rear`),
 *    forgetting to reset `front = -1; rear = -1;`. If omitted, the queue
 *    falsely thinks an element is still present.
 * 4. Display Traversal Termination: Using a standard `for (int i = front; i <= rear; i++)`
 *    fails when `rear < front` (wrap-around case). You MUST use a `do-while` or
 *    `while (true)` loop with modulo increment and break when `i == rear`.
 * ============================================================================
 * EXAM MEMORIZATION CHECKLIST
 * ============================================================================
 * [ ] Declare `int queue[MAX]`, `int front = -1`, `int rear = -1`.
 * [ ] isEmpty(): `return front == -1;`
 * [ ] isFull(): `return (rear + 1) % MAX == front;`
 * [ ] Enqueue():
 *     - If `isFull()`, print Overflow.
 *     - If `isEmpty()`, `front = 0; rear = 0;`
 *     - Else `rear = (rear + 1) % MAX;`
 *     - `queue[rear] = val;`
 * [ ] Dequeue():
 *     - If `isEmpty()`, print Underflow.
 *     - `val = queue[front];`
 *     - If `front == rear`, `front = -1; rear = -1;`
 *     - Else `front = (front + 1) % MAX;`
 *     - `return val;`
 * [ ] Display():
 *     - If `front == -1`, return.
 *     - `int i = front; while(true) { print queue[i]; if(i == rear) break; i = (i + 1) % MAX; }`
 * ============================================================================
 */
