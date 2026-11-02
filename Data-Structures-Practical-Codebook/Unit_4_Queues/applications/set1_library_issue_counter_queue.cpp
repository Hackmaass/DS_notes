/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit IV: Queues
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 1 - Library Management System
 * PROBLEM REF:   Part B - Problem 5
 * TITLE:         Library Book Issue Counter Queue Simulation
 * 
 * PROBLEM STATEMENT (Departmental Alternate Problem Set):
 *   Write a program to simulate a book issue counter queue where students queue 
 *   up to get books issued.
 *   a. Enqueue student token number
 *   b. Dequeue and display student processed
 *   c. Display front and rear token number
 *   d. Display complete queue
 * 
 * ============================================================================
 * CONCEPT EXPLANATION: FIFO QUEUE AT LIBRARY ISSUE COUNTER
 * ============================================================================
 * In a university library circulation desk:
 *   - Students arrive to borrow books and are assigned a sequential token number.
 *   - The service follows First-In, First-Out (FIFO) discipline.
 *   - New students join at the REAR of the queue.
 *   - The librarian serves and issues books to the student waiting at the FRONT.
 *   - We implement a robust circular array queue to prevent False Overflow.
 * ============================================================================
 * STEP-BY-STEP ALGORITHM (WHAT & WHY)
 * ============================================================================
 * 1. INITIALIZATION:
 *    - Maintain array `tokenQueue[MAX]`.
 *    - Initialize `front = -1`, `rear = -1`.
 * 
 * 2. ENQUEUE TOKEN:
 *    - If `(rear + 1) % MAX == front`, queue is full (Overflow).
 *    - If `front == -1`, set `front = rear = 0`.
 *    - Else `rear = (rear + 1) % MAX`.
 *    - Store token at `tokenQueue[rear]`.
 * 
 * 3. DEQUEUE AND DISPLAY PROCESSED:
 *    - If `front == -1`, queue is empty (Underflow).
 *    - Extract served token: `token = tokenQueue[front]`.
 *    - If `front == rear`, reset `front = rear = -1`.
 *    - Else `front = (front + 1) % MAX`.
 *    - Display: "Student with Token <token> processed and book issued."
 * 
 * 4. DISPLAY FRONT AND REAR TOKEN:
 *    - If empty, display message.
 *    - Else print `tokenQueue[front]` and `tokenQueue[rear]`.
 * 
 * 5. DISPLAY COMPLETE QUEUE:
 *    - Circularly traverse from `front` to `rear` printing all active tokens.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_TOKENS = 6;

class LibraryIssueQueue {
private:
    int tokenQueue[MAX_TOKENS];
    int front;
    int rear;

public:
    LibraryIssueQueue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() const {
        return (front == -1);
    }

    bool isFull() const {
        return ((rear + 1) % MAX_TOKENS == front);
    }

    // OPERATION a: Enqueue student token number
    bool enqueueToken(int token) {
        if (isFull()) {
            cout << "  [COUNTER FULL] Queue is full! Token #" << token << " cannot be issued right now.\n";
            return false;
        }

        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % MAX_TOKENS;
        }

        tokenQueue[rear] = token;
        cout << "  [TOKEN ISSUED] Token #" << token << " added to issue counter queue at slot [" << rear << "].\n";
        return true;
    }

    // OPERATION b: Dequeue and display student processed
    int dequeueServed() {
        if (isEmpty()) {
            cout << "  [COUNTER IDLE] No students waiting at book issue counter.\n";
            return -1;
        }

        int servedToken = tokenQueue[front];
        int vacated = front;

        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % MAX_TOKENS;
        }

        cout << "  [BOOK ISSUED] Student with Token #" << servedToken 
             << " has been served! (Vacated Slot: " << vacated << ")\n";
        return servedToken;
    }

    // OPERATION c: Display front and rear token number
    void displayFrontRear() const {
        if (isEmpty()) {
            cout << "  [STATUS] Counter queue is empty. Front and Rear are inactive (-1).\n";
            return;
        }
        cout << "\n  --- Counter Pointer Inspection ---\n";
        cout << "  Front Token (Next to be served) : #" << tokenQueue[front] << " (Index: " << front << ")\n";
        cout << "  Rear Token  (Last student arrived): #" << tokenQueue[rear]  << " (Index: " << rear  << ")\n\n";
    }

    // OPERATION d: Display complete queue
    void displayQueue() const {
        if (isEmpty()) {
            cout << "  [QUEUE STATE] Library Issue Counter is EMPTY.\n";
            return;
        }

        cout << "\n  [BOOK ISSUE COUNTER QUEUE (Front -> Rear)]:\n  ";
        int i = front;
        while (true) {
            cout << "[Token #" << tokenQueue[i] << "]";
            if (i == rear) break;
            cout << " -> ";
            i = (i + 1) % MAX_TOKENS;
        }
        cout << "\n\n";
    }
};

void runVerification() {
    cout << "====================================================================\n";
    cout << "  SET 1: LIBRARY MANAGEMENT SYSTEM - ISSUE COUNTER QUEUE DEMO\n";
    cout << "====================================================================\n";

    LibraryIssueQueue libQ;

    cout << "\n--- STEP 1: Verify Initial State ---\n";
    libQ.displayFrontRear();
    libQ.displayQueue();

    cout << "\n--- STEP 2: Students Arrive at Library Counter (Enqueue Tokens) ---\n";
    libQ.enqueueToken(501);
    libQ.enqueueToken(502);
    libQ.enqueueToken(503);
    libQ.enqueueToken(504);
    libQ.displayFrontRear();
    libQ.displayQueue();

    cout << "\n--- STEP 3: Librarian Issues Books to First 2 Students (Dequeue) ---\n";
    libQ.dequeueServed();
    libQ.dequeueServed();
    libQ.displayFrontRear();
    libQ.displayQueue();

    cout << "\n--- STEP 4: More Students Arrive (Wrap-Around Demonstration) ---\n";
    libQ.enqueueToken(505);
    libQ.enqueueToken(506);
    libQ.enqueueToken(507);
    libQ.displayFrontRear();
    libQ.displayQueue();

    cout << "\n--- STEP 5: Attempt Enqueue when Full ---\n";
    libQ.enqueueToken(508);

    cout << "\n--- STEP 6: Serve All Remaining Students ---\n";
    while (!libQ.isEmpty()) {
        libQ.dequeueServed();
    }
    libQ.displayQueue();
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
 * Enqueue      | O(1)            | O(1)             | Direct array index write via modulo.
 * Dequeue      | O(1)            | O(1)             | Direct array index read and modulo increment.
 * Front/Rear   | O(1)            | O(1)             | Direct index inspection.
 * Display      | O(N)            | O(1)             | Single pass from front to rear.
 * Auxiliary Space: O(MAX) for array buffer.
 * ============================================================================
 * EXAM RECALL CHECKLIST
 * ============================================================================
 * [ ] Circular increment: `rear = (rear + 1) % MAX;`
 * [ ] Circular dequeue: `front = (front + 1) % MAX;`
 * [ ] Full condition: `(rear + 1) % MAX == front`
 * [ ] Empty condition: `front == -1`
 * ============================================================================
 */
