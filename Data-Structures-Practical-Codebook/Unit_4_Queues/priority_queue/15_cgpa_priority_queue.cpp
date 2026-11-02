/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit IV: Queues
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * ASSIGNMENT:    Group D - Assignment 15
 * TITLE:         Student Processing Using Priority Queue (Higher CGPA = Highest Priority)
 * 
 * PROBLEM STATEMENT (Official Curriculum):
 *   Write a program using priority queue where priority = higher CGPA.
 *   a. Insert student with CGPA
 *   b. Delete the highest CGPA student
 *   c. Display queue after each operation
 *   d. Count students processed
 * 
 * ============================================================================
 * CONCEPT EXPLANATION: WHAT IS A PRIORITY QUEUE?
 * ============================================================================
 * In a standard First-In-First-Out (FIFO) queue, elements are served strictly
 * in the order they arrive, regardless of their urgency or importance.
 * 
 * A PRIORITY QUEUE is an abstract data type where:
 *   1. Every element has an associated "priority" value.
 *   2. An element with higher priority is dequeued/served before an element with
 *      lower priority.
 *   3. If two elements have identical priority, they are served in FIFO order
 *      (arrival stability).
 * 
 * In this college application:
 *   - Priority Attribute: Student CGPA (e.g., 9.8, 9.2, 8.4...).
 *   - Priority Rule: HIGHER CGPA = HIGHER PRIORITY (Max-Priority Queue).
 *   - Use Case: Merit scholarship counseling, honors lab seat allotment, or
 *     campus recruitment shortlist screening where top academic performers
 *     must be interviewed first.
 * 
 * IMPLEMENTATION CHOICE (FIRST PRINCIPLES - NO STL):
 *   We implement an Ordered Array Priority Queue:
 *   - On insertion, we find the correct position based on CGPA and shift
 *     elements to insert in descending order of CGPA (O(N) insertion).
 *   - On deletion, the student with the highest CGPA is always located at
 *     index 0, allowing straightforward retrieval and front deletion (O(N) shift,
 *     or O(1) if using front index pointer).
 * ============================================================================
 * STEP-BY-STEP ALGORITHM (WHAT & WHY)
 * ============================================================================
 * 1. DATA STRUCTURE:
 *    - Structure `Student`: `rollNo`, `name`, `cgpa`.
 *    - Priority Queue class containing:
 *      - Array `arr[MAX]` of `Student` records.
 *      - `size`: Current count of students waiting in the queue.
 *      - `processedCount`: Total count of students served so far.
 * 
 * 2. INSERTION WITH CGPA PRIORITY (Enqueue):
 *    - Step 2.1: Check if `size == MAX`. If true, print "Queue Overflow".
 *    - Step 2.2: If `size == 0`, place new student at `arr[0]`. Increment `size`.
 *    - Step 2.3: Otherwise, find the correct insertion position `i` from right to left
 *                such that `arr[i].cgpa < newStudent.cgpa`.
 *    - Step 2.4: Shift elements to the right to make space for the new record.
 *    - Step 2.5: Insert `newStudent` at the identified slot.
 *    - Step 2.6: Increment `size`.
 * 
 * 3. DELETION OF HIGHEST CGPA STUDENT (Dequeue):
 *    - Step 3.1: Check if `size == 0`. If true, print "Queue Underflow".
 *    - Step 3.2: The highest CGPA student is at `arr[0]`.
 *    - Step 3.3: Copy `arr[0]` to `servedStudent`.
 *    - Step 3.4: Shift all remaining elements left by 1 position (from index 1 to size - 1).
 *    - Step 3.5: Decrement `size`.
 *    - Step 3.6: Increment `processedCount`.
 *    - Step 3.7: Return `servedStudent`.
 * 
 * 4. DISPLAY QUEUE:
 *    - Traverse from `index 0` to `size - 1`. Print Roll, Name, CGPA, and Priority Rank.
 * 
 * 5. COUNT PROCESSED:
 *    - Return `processedCount`.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_CAPACITY = 20;

// Structure to encapsulate student credentials and priority metric
struct Student {
    int rollNo;
    string name;
    float cgpa; // Priority Key: Higher value = Higher priority
};

class StudentPriorityQueue {
private:
    Student queue[MAX_CAPACITY]; // Array storing students sorted in descending order of CGPA
    int currentSize;             // Number of active students waiting in queue
    int processedCount;          // Total number of students processed/served

public:
    // Constructor: Initialize empty queue and zero processed count
    StudentPriorityQueue() {
        currentSize = 0;
        processedCount = 0;
    }

    // ------------------------------------------------------------------------
    // Utility: Check if queue is empty
    // ------------------------------------------------------------------------
    bool isEmpty() const {
        return (currentSize == 0);
    }

    // ------------------------------------------------------------------------
    // Utility: Check if queue is full
    // ------------------------------------------------------------------------
    bool isFull() const {
        return (currentSize == MAX_CAPACITY);
    }

    // ------------------------------------------------------------------------
    // OPERATION a: Insert student with CGPA (Priority Insertion)
    // ------------------------------------------------------------------------
    bool insertStudent(int roll, const string& name, float cgpa) {
        // Step 1: Guard against queue overflow
        if (isFull()) {
            cout << "  [OVERFLOW ERROR] Priority Queue is full! Cannot add " << name << ".\n";
            return false;
        }

        Student newStudent;
        newStudent.rollNo = roll;
        newStudent.name = name;
        newStudent.cgpa = cgpa;

        // Step 2: Insertion Sort logic to maintain descending order of CGPA
        // Traverse backwards from current end of queue
        int i = currentSize - 1;

        // Shift elements with LOWER CGPA to the right to make room
        // If CGPA is equal, keep earlier arrival ahead (stable FIFO order)
        while (i >= 0 && queue[i].cgpa < newStudent.cgpa) {
            queue[i + 1] = queue[i]; // Shift right
            i--;
        }

        // Step 3: Insert new student at vacated slot (i + 1)
        queue[i + 1] = newStudent;
        currentSize++;

        cout << "  [INSERT SUCCESS] Roll " << roll << " (" << name 
             << ", CGPA: " << fixed << setprecision(2) << cgpa 
             << ") inserted at Priority Rank #" << (i + 2) << ".\n";
        return true;
    }

    // ------------------------------------------------------------------------
    // OPERATION b: Delete the highest CGPA student (Highest Priority Dequeue)
    // ------------------------------------------------------------------------
    bool deleteHighest(Student& served) {
        // Step 1: Guard against queue underflow
        if (isEmpty()) {
            cout << "  [UNDERFLOW ERROR] Priority Queue is empty! No students to process.\n";
            return false;
        }

        // Step 2: Highest priority element is always at index 0 (descending order)
        served = queue[0];

        // Step 3: Shift remaining students left by 1 position
        for (int i = 0; i < currentSize - 1; ++i) {
            queue[i] = queue[i + 1];
        }

        // Step 4: Decrement active size and increment total processed count
        currentSize--;
        processedCount++;

        cout << "  [PROCESSED HIGHEST CGPA] Student Served:\n"
             << "    -> Roll No : " << served.rollNo << "\n"
             << "    -> Name    : " << served.name << "\n"
             << "    -> CGPA    : " << fixed << setprecision(2) << served.cgpa << " (Highest in Queue)\n";
        return true;
    }

    // ------------------------------------------------------------------------
    // OPERATION c: Display queue after each operation
    // ------------------------------------------------------------------------
    void displayQueue() const {
        if (isEmpty()) {
            cout << "  [QUEUE STATE] Priority Queue is currently EMPTY (0 students waiting).\n";
            return;
        }

        cout << "\n  +-------------------------------------------------------------------------+\n";
        cout << "  | PRIORITY QUEUE CURRENT STATE (Ordered by Descending CGPA)               |\n";
        cout << "  +-------+---------+---------------------------+---------+-----------------+\n";
        cout << "  | Rank  | Roll No | Student Name              | CGPA    | Priority Status |\n";
        cout << "  +-------+---------+---------------------------+---------+-----------------+\n";

        for (int i = 0; i < currentSize; ++i) {
            cout << "  | #" << setw(4) << left << (i + 1)
                 << " | " << setw(7) << left << queue[i].rollNo
                 << " | " << setw(25) << left << queue[i].name
                 << " | " << setw(7) << fixed << setprecision(2) << right << queue[i].cgpa
                 << " | " << setw(15) << left 
                 << (i == 0 ? "Next To Serve" : "Waiting") << " |\n";
        }
        cout << "  +-------+---------+---------------------------+---------+-----------------+\n";
        cout << "  Total Students Waiting: " << currentSize << " | Maximum Capacity: " << MAX_CAPACITY << "\n\n";
    }

    // ------------------------------------------------------------------------
    // OPERATION d: Count students processed
    // ------------------------------------------------------------------------
    int getProcessedCount() const {
        return processedCount;
    }
};

// ============================================================================
// DEMONSTRATION & CURRICULUM VERIFICATION SUITE
// ============================================================================
void runAutomatedCurriculumVerification() {
    cout << "====================================================================\n";
    cout << "  EXAM VERIFICATION DEMO: CGPA-Based Priority Queue Simulation\n";
    cout << "  (Course: CE25PCC-203 Group D Assignment 15)\n";
    cout << "====================================================================\n";

    StudentPriorityQueue pq;

    cout << "\n--- STEP 1: Verify Initial State and Empty Conditions ---\n";
    pq.displayQueue();
    cout << "Total Students Processed: " << pq.getProcessedCount() << "\n";

    cout << "\n--- STEP 2: Insert 5 Students with varying CGPAs in arbitrary order ---\n";
    // Student 1: CGPA 8.50
    pq.insertStudent(101, "Aarav Sharma", 8.50f);
    pq.displayQueue();

    // Student 2: CGPA 9.75 (Higher than Aarav -> Must jump to front Rank #1)
    pq.insertStudent(102, "Bhavna Patil", 9.75f);
    pq.displayQueue();

    // Student 3: CGPA 7.80 (Lower than both -> Placed at rear)
    pq.insertStudent(103, "Chetan Kulkarni", 7.80f);
    pq.displayQueue();

    // Student 4: CGPA 9.20 (Between Aarav 8.50 and Bhavna 9.75 -> Rank #2)
    pq.insertStudent(104, "Divya Deshmukh", 9.20f);
    pq.displayQueue();

    // Student 5: CGPA 8.50 (Equal to Aarav -> FIFO order: placed behind Aarav)
    pq.insertStudent(105, "Eshan Joshi", 8.50f);
    pq.displayQueue();

    cout << "\n--- STEP 3: Delete Highest CGPA Student (Operation b) ---\n";
    cout << "Expected: Bhavna Patil (CGPA 9.75) must be served first.\n";
    Student served;
    pq.deleteHighest(served);
    pq.displayQueue();
    cout << "Processed Count: " << pq.getProcessedCount() << "\n";

    cout << "\n--- STEP 4: Delete Next Highest CGPA Student ---\n";
    cout << "Expected: Divya Deshmukh (CGPA 9.20) must be served next.\n";
    pq.deleteHighest(served);
    pq.displayQueue();
    cout << "Processed Count: " << pq.getProcessedCount() << "\n";

    cout << "\n--- STEP 5: Insert High Performer Mid-Queue (CGPA 9.90) ---\n";
    cout << "A new student with CGPA 9.90 arrives late; must immediately become Rank #1!\n";
    pq.insertStudent(106, "Farhan Khan", 9.90f);
    pq.displayQueue();

    cout << "\n--- STEP 6: Serve Remaining Students Until Empty ---\n";
    while (!pq.isEmpty()) {
        pq.deleteHighest(served);
        cout << "  -> Queue size now: " << (pq.isEmpty() ? 0 : 1) << " | Processed so far: " 
             << pq.getProcessedCount() << "\n";
    }
    pq.displayQueue();

    cout << "\n--- STEP 7: Total Students Processed Count (Operation d) ---\n";
    cout << "FINAL TOTAL STUDENTS PROCESSED: " << pq.getProcessedCount() << "\n";

    cout << "\n--- STEP 8: Attempt Deletion on Empty Queue ---\n";
    pq.deleteHighest(served);
}

int main() {
    runAutomatedCurriculumVerification();

    cout << "\n====================================================================\n";
    cout << "  INTERACTIVE MENU (For College Practical Viva & Lab Examination)\n";
    cout << "====================================================================\n";

    StudentPriorityQueue userPQ;
    int choice = 0;
    int roll = 0;
    string name = "";
    float cgpa = 0.0f;
    Student served;

    do {
        cout << "\n===== CGPA PRIORITY QUEUE MENU =====\n";
        cout << "1. Insert Student with CGPA (Enqueue)\n";
        cout << "2. Delete Highest CGPA Student (Serve Next)\n";
        cout << "3. Display Queue\n";
        cout << "4. Display Count of Students Processed\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting interactive session.\n";
            break;
        }

        switch (choice) {
            case 1:
                cout << "Enter Roll Number : ";
                cin >> roll;
                cin.ignore();
                cout << "Enter Student Name: ";
                getline(cin, name);
                cout << "Enter CGPA (0.00 - 10.00): ";
                cin >> cgpa;
                userPQ.insertStudent(roll, name, cgpa);
                userPQ.displayQueue();
                break;
            case 2:
                if (userPQ.deleteHighest(served)) {
                    userPQ.displayQueue();
                }
                break;
            case 3:
                userPQ.displayQueue();
                break;
            case 4:
                cout << "\n>>> Total Students Processed So Far: " 
                     << userPQ.getProcessedCount() << " <<<\n";
                break;
            case 5:
                cout << "Exiting CGPA Priority Queue System. Thank you!\n";
                break;
            default:
                cout << "Invalid selection! Please enter a choice between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}

/*
 * ============================================================================
 * STEP-BY-STEP DRY RUN TRACE TABLE
 * ============================================================================
 * Insertions:
 *   1. Roll 101, Aarav, CGPA 8.50
 *   2. Roll 102, Bhavna, CGPA 9.75
 *   3. Roll 103, Chetan, CGPA 7.80
 *   4. Roll 104, Divya, CGPA 9.20
 * 
 * Step | Operation           | Roll | CGPA | Comparisons & Shifts                 | Resulting Queue [0..currentSize-1]
 * -----+---------------------+------+------+--------------------------------------+----------------------------------------------
 *  1   | Insert(101, 8.50)   | 101  | 8.50 | None (empty queue)                   | [ (101, 8.50) ]
 *  2   | Insert(102, 9.75)   | 102  | 9.75 | 8.50 < 9.75 -> Shift 101 right       | [ (102, 9.75), (101, 8.50) ]
 *  3   | Insert(103, 7.80)   | 103  | 7.80 | 8.50 > 7.80 -> No shift, append      | [ (102, 9.75), (101, 8.50), (103, 7.80) ]
 *  4   | Insert(104, 9.20)   | 104  | 9.20 | 7.80 < 9.20 (shift), 8.50 < 9.20 (sh)| [ (102, 9.75), (104, 9.20), (101, 8.50), (103, 7.80) ]
 *  5   | DeleteHighest()     | 102  | 9.75 | Served index 0; shift remaining left | [ (104, 9.20), (101, 8.50), (103, 7.80) ]
 * ============================================================================
 * COMPLEXITY ANALYSIS
 * ============================================================================
 * Operation       | Time Complexity | Space Complexity | Explanation
 * ----------------+-----------------+------------------+-------------------------------------------------------
 * Priority Insert | O(N)            | O(1)             | In worst case, scans N elements and shifts N elements.
 * Delete Highest  | O(N)            | O(1)             | Index 0 lookup is O(1); shifting N-1 elements is O(N).
 * Peek Highest    | O(1)            | O(1)             | Direct access to `queue[0]`.
 * Count Processed | O(1)            | O(1)             | Direct integer variable read.
 * Display Queue   | O(N)            | O(1)             | Single pass over `currentSize` active records.
 * Auxiliary Space : O(MAX) for the fixed-size student record array buffer.
 * ============================================================================
 * COMMON EXAM PITFALLS & MISTAKES TO AVOID
 * ============================================================================
 * 1. Forgetting Shifting on Insert: Simply putting the element at `queue[rear++]`
 *    turns the queue into a regular FIFO queue, completely ignoring CGPA priority!
 * 2. Unstable Tie-Breaking: When two students have identical CGPA, they should
 *    be ordered FIFO. Using `<` instead of `<=` in `queue[i].cgpa < newStudent.cgpa`
 *    ensures existing students with the same CGPA stay ahead (stability).
 * 3. Not Updating `processedCount`: Forgetting to increment the processed counter
 *    during `deleteHighest()`, causing question requirement (d) to fail.
 * 4. Failing to shift remaining elements left on deletion: Leaving an empty gap
 *    at index 0 breaks sequential display and index indexing.
 * ============================================================================
 * EXAM MEMORIZATION CHECKLIST
 * ============================================================================
 * [ ] Declare `struct Student { int rollNo; string name; float cgpa; };`
 * [ ] In `StudentPriorityQueue`: `Student queue[MAX]; int currentSize = 0; int processedCount = 0;`
 * [ ] `insertStudent(roll, name, cgpa)`:
 *     - If `currentSize == MAX`, return false.
 *     - `int i = currentSize - 1;`
 *     - `while (i >= 0 && queue[i].cgpa < cgpa) { queue[i+1] = queue[i]; i--; }`
 *     - `queue[i+1] = newStudent; currentSize++;`
 * [ ] `deleteHighest(served)`:
 *     - If `currentSize == 0`, return false.
 *     - `served = queue[0];`
 *     - `for (int i = 0; i < currentSize - 1; i++) queue[i] = queue[i+1];`
 *     - `currentSize--; processedCount++; return true;`
 * [ ] `getProcessedCount()`: `return processedCount;`
 * ============================================================================
 */
