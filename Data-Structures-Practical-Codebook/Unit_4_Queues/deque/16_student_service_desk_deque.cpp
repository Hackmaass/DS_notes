/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit IV: Queues
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * ASSIGNMENT:    Group D - Assignment 16
 * TITLE:         Student Service Desk Using Double-Ended Queue (Deque)
 * 
 * PROBLEM STATEMENT (Official Curriculum):
 *   Student Service Desk Using Deque: Write a program using deque for student 
 *   service requests.
 *   a. Add emergency cases at front
 *   b. Add normal cases at rear
 *   c. Serve from front
 *   d. Display deque after each operation
 * 
 * ============================================================================
 * CONCEPT EXPLANATION: WHAT IS A DEQUE (DOUBLE-ENDED QUEUE)?
 * ============================================================================
 * A DEQUE (pronounced "deck", short for Double-Ended Queue) is a linear data 
 * structure in which insertions and deletions can be performed at BOTH ends:
 *   - FRONT end: `insertFront()`, `deleteFront()`, `getFront()`
 *   - REAR end:  `insertRear()`,  `deleteRear()`,  `getRear()`
 * 
 * In this real-world Student Service Desk scenario:
 *   1. Regular / Normal requests (e.g., standard bonafide certificate, transcript 
 *      inquiry, general form submission) join the queue at the REAR end (`insertRear`).
 *      This maintains standard fair First-Come-First-Served (FCFS) behavior.
 *   2. Urgent / Emergency requests (e.g., medical emergency leave, immediate hall-ticket
 *      error correction 10 minutes before an exam, urgent scholarship deadline)
 *      are inserted directly at the FRONT end (`insertFront`) to be attended to immediately.
 *   3. Service Point: The desk officer always serves requests from the FRONT end (`deleteFront`).
 * 
 * CLASSIFICATION OF DEQUES (Crucial for Viva):
 *   - Input-Restricted Deque: Insertion is allowed at only ONE end, but deletion is
 *     allowed at BOTH ends.
 *   - Output-Restricted Deque: Deletion is allowed at only ONE end, but insertion is
 *     allowed at BOTH ends.
 *   - NOTE: This Assignment acts as an Output-Restricted Deque (insert at both front
 *     and rear, delete primarily from front)!
 * ============================================================================
 * STEP-BY-STEP ALGORITHM (WHAT & WHY)
 * ============================================================================
 * 1. CIRCULAR ARRAY BUFFER:
 *    - Maintain array `arr[MAX]` with integer indices `front = -1` and `rear = -1`.
 *    - Full condition: `(rear + 1) % MAX == front` or `(front == 0 && rear == MAX - 1)`.
 *    - Empty condition: `front == -1`.
 * 
 * 2. INSERT FRONT (Emergency Case):
 *    - Step 2.1: If `isFull()`, report Overflow.
 *    - Step 2.2: If `isEmpty()`, set `front = 0`, `rear = 0`.
 *    - Step 2.3: Else if `front == 0`, wrap around: `front = MAX - 1`.
 *    - Step 2.4: Else, decrement `front = front - 1`.
 *    - Step 2.5: Store record at `arr[front]`.
 * 
 * 3. INSERT REAR (Normal Case):
 *    - Step 3.1: If `isFull()`, report Overflow.
 *    - Step 3.2: If `isEmpty()`, set `front = 0`, `rear = 0`.
 *    - Step 3.3: Else if `rear == MAX - 1`, wrap around: `rear = 0`.
 *    - Step 3.4: Else, increment `rear = rear + 1`.
 *    - Step 3.5: Store record at `arr[rear]`.
 * 
 * 4. SERVE FROM FRONT (Delete Front):
 *    - Step 4.1: If `isEmpty()`, report Underflow.
 *    - Step 4.2: Retrieve item `served = arr[front]`.
 *    - Step 4.3: If `front == rear` (last remaining item), reset `front = rear = -1`.
 *    - Step 4.4: Else if `front == MAX - 1`, wrap around: `front = 0`.
 *    - Step 4.5: Else, increment `front = front + 1`.
 *    - Step 4.6: Return `served`.
 * 
 * 5. DISPLAY DEQUE:
 *    - Traverse circularly from `front` to `rear` printing ticket ID, student name, 
 *      and case type (Emergency vs Normal).
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Maximum capacity for circular deque storage
const int MAX_REQUESTS = 6;

// Structure representing a student service request
struct ServiceRequest {
    int ticketId;
    string studentName;
    string requestReason;
    bool isEmergency; // true = Emergency (Front Insert), false = Normal (Rear Insert)
};

class StudentServiceDeskDeque {
private:
    ServiceRequest arr[MAX_REQUESTS]; // Fixed-size circular buffer
    int front;                        // Index of head element
    int rear;                         // Index of tail element
    int nextTicketId;                 // Auto-incrementing ticket ID generator

public:
    // Constructor: Initialize empty deque
    StudentServiceDeskDeque() {
        front = -1;
        rear = -1;
        nextTicketId = 1001;
    }

    // ------------------------------------------------------------------------
    // Utility: Check if Deque is Empty
    // ------------------------------------------------------------------------
    bool isEmpty() const {
        return (front == -1);
    }

    // ------------------------------------------------------------------------
    // Utility: Check if Deque is Full (Circular wrap-around check)
    // ------------------------------------------------------------------------
    bool isFull() const {
        return ((front == 0 && rear == MAX_REQUESTS - 1) || (front == rear + 1));
    }

    // ------------------------------------------------------------------------
    // OPERATION a: Add Emergency Case at FRONT
    // ------------------------------------------------------------------------
    bool addEmergencyCase(const string& name, const string& reason) {
        if (isFull()) {
            cout << "  [OVERFLOW] Service Desk queue is FULL! Cannot accept emergency ticket for " 
                 << name << ".\n";
            return false;
        }

        ServiceRequest req;
        req.ticketId = nextTicketId++;
        req.studentName = name;
        req.requestReason = reason;
        req.isEmergency = true;

        if (isEmpty()) {
            // Case 1: First item in deque
            front = 0;
            rear = 0;
        } else if (front == 0) {
            // Case 2: Wrap around to the end of circular array
            front = MAX_REQUESTS - 1;
        } else {
            // Case 3: Decrement front
            front = front - 1;
        }

        arr[front] = req;
        cout << "  [EMERGENCY ADDED AT FRONT] Ticket #" << req.ticketId 
             << " (" << name << " - " << reason << ") inserted at slot [" << front << "].\n";
        return true;
    }

    // ------------------------------------------------------------------------
    // OPERATION b: Add Normal Case at REAR
    // ------------------------------------------------------------------------
    bool addNormalCase(const string& name, const string& reason) {
        if (isFull()) {
            cout << "  [OVERFLOW] Service Desk queue is FULL! Cannot accept normal ticket for " 
                 << name << ".\n";
            return false;
        }

        ServiceRequest req;
        req.ticketId = nextTicketId++;
        req.studentName = name;
        req.requestReason = reason;
        req.isEmergency = false;

        if (isEmpty()) {
            // Case 1: First item in deque
            front = 0;
            rear = 0;
        } else if (rear == MAX_REQUESTS - 1) {
            // Case 2: Wrap around to beginning of circular array
            rear = 0;
        } else {
            // Case 3: Increment rear
            rear = rear + 1;
        }

        arr[rear] = req;
        cout << "  [NORMAL ADDED AT REAR] Ticket #" << req.ticketId 
             << " (" << name << " - " << reason << ") inserted at slot [" << rear << "].\n";
        return true;
    }

    // ------------------------------------------------------------------------
    // OPERATION c: Serve Student from FRONT (Delete Front)
    // ------------------------------------------------------------------------
    bool serveStudent(ServiceRequest& served) {
        if (isEmpty()) {
            cout << "  [UNDERFLOW] No service requests waiting at the desk!\n";
            return false;
        }

        // Retrieve front element
        served = arr[front];
        int vacatedSlot = front;

        // Update front pointer
        if (front == rear) {
            // Only one element was in deque, now becomes empty
            front = -1;
            rear = -1;
        } else if (front == MAX_REQUESTS - 1) {
            // Wrap around to index 0
            front = 0;
        } else {
            // Increment front
            front = front + 1;
        }

        cout << "  [SERVED FROM FRONT] Ticket #" << served.ticketId 
             << " | Student: " << served.studentName
             << " | Type: " << (served.isEmergency ? "EMERGENCY" : "NORMAL")
             << " | Reason: " << served.requestReason
             << " (Vacated Slot: " << vacatedSlot << ")\n";
        return true;
    }

    // ------------------------------------------------------------------------
    // OPERATION d: Display Deque after each operation
    // ------------------------------------------------------------------------
    void displayDeque() const {
        if (isEmpty()) {
            cout << "  [DEQUE STATE] Student Service Desk is currently EMPTY (0 waiting).\n";
            return;
        }

        cout << "\n  +-----------------------------------------------------------------------------------+\n";
        cout << "  | STUDENT SERVICE DESK - ACTIVE REQUESTS IN DEQUE (Front -> Rear)                   |\n";
        cout << "  +-------+----------+----------------------+---------------------------+-------------+\n";
        cout << "  | Pos   | Ticket # | Student Name         | Request Reason            | Priority    |\n";
        cout << "  +-------+----------+----------------------+---------------------------+-------------+\n";

        int i = front;
        int pos = 1;
        while (true) {
            cout << "  | #" << setw(4) << left << pos
                 << " | " << setw(8) << left << arr[i].ticketId
                 << " | " << setw(20) << left << arr[i].studentName
                 << " | " << setw(25) << left << arr[i].requestReason
                 << " | " << setw(11) << left 
                 << (arr[i].isEmergency ? "EMERGENCY" : "Normal") << " |\n";

            if (i == rear) break;
            i = (i + 1) % MAX_REQUESTS;
            pos++;
        }
        cout << "  +-------+----------+----------------------+---------------------------+-------------+\n";
        cout << "  Front Index: " << front << " | Rear Index: " << rear 
             << " | Total Waiting: " << pos << " / " << MAX_REQUESTS << "\n\n";
    }
};

// ============================================================================
// DEMONSTRATION & VERIFICATION DRIVER
// ============================================================================
void runAutomatedCurriculumVerification() {
    cout << "====================================================================\n";
    cout << "  EXAM VERIFICATION DEMO: Student Service Desk Deque Simulation\n";
    cout << "  (Course: CE25PCC-203 Group D Assignment 16)\n";
    cout << "====================================================================\n";

    StudentServiceDeskDeque desk;

    cout << "\n--- STEP 1: Verify Initial Empty State ---\n";
    desk.displayDeque();

    cout << "\n--- STEP 2: Add Normal Cases at REAR (Operation b) ---\n";
    desk.addNormalCase("Omkar Shinde", "Bonafide Certificate");
    desk.displayDeque();

    desk.addNormalCase("Pooja Nair", "Transcript Verification");
    desk.displayDeque();

    desk.addNormalCase("Rahul Verma", "Library Card Renewal");
    desk.displayDeque();

    cout << "\n--- STEP 3: Add Emergency Cases at FRONT (Operation a) ---\n";
    cout << "SCENARIO: An urgent hall ticket error must be corrected immediately before exam!\n";
    desk.addEmergencyCase("Sneha Kulkarni", "Hall Ticket Error - Exam in 15 mins");
    desk.displayDeque();

    cout << "SCENARIO: A medical emergency leave application arrives!\n";
    desk.addEmergencyCase("Tanmay Joshi", "Medical Emergency Leave");
    desk.displayDeque();

    cout << "\n--- STEP 4: Add 6th Request to Fill Capacity ---\n";
    desk.addNormalCase("Vikas Mehta", "Fee Receipt Duplicate");
    desk.displayDeque();

    cout << "\n--- STEP 5: Attempt to Add when Full -> Expect Overflow ---\n";
    desk.addEmergencyCase("Aniket Deshmukh", "Urgent Clearance");

    cout << "\n--- STEP 6: Serve Requests from FRONT (Operation c) ---\n";
    ServiceRequest served;
    
    // First served must be Tanmay (Emergency 2)
    desk.serveStudent(served);
    desk.displayDeque();

    // Second served must be Sneha (Emergency 1)
    desk.serveStudent(served);
    desk.displayDeque();

    // Third served must be Omkar (First Normal case)
    desk.serveStudent(served);
    desk.displayDeque();

    cout << "\n--- STEP 7: Serve Remaining Students Until Empty ---\n";
    while (!desk.isEmpty()) {
        desk.serveStudent(served);
    }
    desk.displayDeque();

    cout << "\n--- STEP 8: Attempt to Serve on Empty Desk -> Expect Underflow ---\n";
    desk.serveStudent(served);
}

int main() {
    runAutomatedCurriculumVerification();

    cout << "\n====================================================================\n";
    cout << "  INTERACTIVE MENU (For College Practical Viva & Lab Examination)\n";
    cout << "====================================================================\n";

    StudentServiceDeskDeque userDesk;
    int choice = 0;
    string name = "";
    string reason = "";
    ServiceRequest served;

    do {
        cout << "\n===== STUDENT SERVICE DESK (DEQUE) MENU =====\n";
        cout << "1. Add Emergency Request at FRONT\n";
        cout << "2. Add Normal Request at REAR\n";
        cout << "3. Serve Next Request from FRONT\n";
        cout << "4. Display Current Deque State\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting session.\n";
            break;
        }
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter Student Name   : ";
                getline(cin, name);
                cout << "Enter Emergency Reason: ";
                getline(cin, reason);
                userDesk.addEmergencyCase(name, reason);
                userDesk.displayDeque();
                break;
            case 2:
                cout << "Enter Student Name: ";
                getline(cin, name);
                cout << "Enter Request Type: ";
                getline(cin, reason);
                userDesk.addNormalCase(name, reason);
                userDesk.displayDeque();
                break;
            case 3:
                userDesk.serveStudent(served);
                userDesk.displayDeque();
                break;
            case 4:
                userDesk.displayDeque();
                break;
            case 5:
                cout << "Exiting Student Service Desk. Have a nice day!\n";
                break;
            default:
                cout << "Invalid choice! Please select 1 through 5.\n";
        }
    } while (choice != 5);

    return 0;
}

/*
 * ============================================================================
 * STEP-BY-STEP DRY RUN TRACE TABLE
 * ============================================================================
 * Initial: MAX = 6, front = -1, rear = -1
 * 
 * Step | Operation              | Type      | front | rear | Deque Contents (Front to Rear)
 * -----+------------------------+-----------+-------+------+-------------------------------------------------------------
 *  1   | addNormal("Omkar")     | Normal    |   0   |  0   | [ 0: Omkar(F,R) ]
 *  2   | addNormal("Pooja")     | Normal    |   0   |  1   | [ 0: Omkar(F), 1: Pooja(R) ]
 *  3   | addNormal("Rahul")     | Normal    |   0   |  2   | [ 0: Omkar(F), 1: Pooja, 2: Rahul(R) ]
 *  4   | addEmergency("Sneha")  | Emergency |   5   |  2   | [ 5: Sneha(F), 0: Omkar, 1: Pooja, 2: Rahul(R) ] (wrap front!)
 *  5   | addEmergency("Tanmay") | Emergency |   4   |  2   | [ 4: Tanmay(F), 5: Sneha, 0: Omkar, 1: Pooja, 2: Rahul(R) ]
 *  6   | serveStudent()         | Dequeue   |   5   |  2   | Tanmay served. Front moves 4 -> 5.
 *  7   | serveStudent()         | Dequeue   |   0   |  2   | Sneha served. Front wraps 5 -> 0.
 *  8   | serveStudent()         | Dequeue   |   1   |  2   | Omkar served. Front moves 0 -> 1.
 * ============================================================================
 * COMPLEXITY ANALYSIS
 * ============================================================================
 * Operation    | Time Complexity | Space Complexity | Explanation
 * -------------+-----------------+------------------+-------------------------------------------------------
 * insertFront  | O(1)            | O(1)             | Direct array index calculation via circular decrement.
 * insertRear   | O(1)            | O(1)             | Direct array index calculation via circular increment.
 * deleteFront  | O(1)            | O(1)             | Direct array index access and circular front advance.
 * deleteRear   | O(1)            | O(1)             | Direct array index access and circular rear decrement.
 * displayDeque | O(N)            | O(1)             | Linear scan from front to rear across active slots.
 * Auxiliary Space: O(MAX) for the circular array buffer.
 * ============================================================================
 * COMMON EXAM PITFALLS & MISTAKES TO AVOID
 * ============================================================================
 * 1. Decrementing Front without Wrap-Around: Writing `front--` when `front == 0`
 *    causes negative array indexing (`arr[-1]`), crashing the program.
 *    Correct formula: `if (front == 0) front = MAX - 1; else front--;`
 * 2. Decrementing Rear without Wrap-Around: In `deleteRear()`, if `rear == 0`,
 *    it must wrap around to `MAX - 1`.
 * 3. Failing to Handle the Single Element Transition: When `front == rear`,
 *    deleting the element MUST reset `front = -1; rear = -1;`.
 * 4. Confusing Deque Types in Viva:
 *    - Input-Restricted: Insert at ONE end, Delete at BOTH ends.
 *    - Output-Restricted: Insert at BOTH ends, Delete at ONE end.
 * ============================================================================
 * EXAM MEMORIZATION CHECKLIST
 * ============================================================================
 * [ ] isEmpty(): `return front == -1;`
 * [ ] isFull(): `return ((front == 0 && rear == MAX-1) || (front == rear + 1));`
 * [ ] insertFront(val):
 *     - If `isFull()`, return false.
 *     - If `isEmpty()`, `front = rear = 0;`
 *     - Else if `front == 0`, `front = MAX - 1;`
 *     - Else `front = front - 1;`
 *     - `arr[front] = val;`
 * [ ] insertRear(val):
 *     - If `isFull()`, return false.
 *     - If `isEmpty()`, `front = rear = 0;`
 *     - Else if `rear == MAX - 1`, `rear = 0;`
 *     - Else `rear = rear + 1;`
 *     - `arr[rear] = val;`
 * [ ] deleteFront():
 *     - If `isEmpty()`, return false.
 *     - `val = arr[front];`
 *     - If `front == rear`, `front = rear = -1;`
 *     - Else if `front == MAX - 1`, `front = 0;`
 *     - Else `front = front + 1;`
 * ============================================================================
 */
