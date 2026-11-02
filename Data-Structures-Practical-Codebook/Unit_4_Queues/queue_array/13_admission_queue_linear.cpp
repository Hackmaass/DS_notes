/*
========================================================================================
PROGRAM HEADER:
- Program Number: 13
- Program Title: Student Admission Token Queue Simulator (Linear Queue)
- Unit: Unit IV - Queue
- Relevant Curriculum Topic: Linear Queue Operations and Admission Token Processing
- Course Code: CE25PCC-203 (Data Structures Laboratory) - Group D, Assignment 13
- Problem Statement:
  Write a program to simulate the admission queue of students.
  a. Enqueue student token number
  b. Dequeue and display student processed
  c. Display front and rear token number
  d. Display complete queue
- Data Structure Used: Linear Array Queue of Student Tokens
- What This Program Demonstrates:
  FIFO service order at university admission counters, token lifecycle management,
  front and rear boundary tracking, and queue state inspection.
========================================================================================

CONCEPT: WHY IS A QUEUE USED FOR STUDENT ADMISSIONS?
In university admissions (e.g. NMIET admissions desk):
1. Fairness (First-Come, First-Served):
   - The student who takes Token 101 arrives before Token 102.
   - It is strictly unfair to serve Token 102 before Token 101.
2. FIFO Guarantee:
   - Elements leave in the exact order they entered.
   - Enqueue happens at `rear` (new student arrives).
   - Dequeue happens at `front` (desk officer calls the next token).
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_ADMISSIONS = 50;

struct StudentToken {
    int tokenNumber;       // Token number (e.g. 101, 102)
    string studentName;    // Applicant's full name
    string department;     // Applied course (e.g., "Computer Engineering")
};

class AdmissionQueue {
private:
    StudentToken queue[MAX_ADMISSIONS];
    int front;
    int rear;

public:
    AdmissionQueue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() const {
        return (front == -1 && rear == -1);
    }

    bool isFull() const {
        return (rear == MAX_ADMISSIONS - 1);
    }

    /*
    ALGORITHM: a. ENQUEUE STUDENT TOKEN NUMBER
    1. If `isFull()`, report Overflow and return false.
    2. If `isEmpty()`, set `front = 0`.
    3. `rear++`.
    4. Store `queue[rear] = token`.
    5. Print confirmation.
    */
    bool enqueueToken(int tokenNum, const string &name, const string &dept) {
        if (isFull()) {
            cout << "[ERROR] Admission counter queue is full! Please wait in waiting hall.\n";
            return false;
        }

        if (isEmpty()) {
            front = 0;
        }

        rear++;
        queue[rear].tokenNumber = tokenNum;
        queue[rear].studentName = name;
        queue[rear].department = dept;

        cout << ">> ISSUED: Token #" << tokenNum << " issued to " << name 
             << " (" << dept << ") | Added at Queue Position " << (rear + 1) << ".\n";
        return true;
    }

    /*
    ALGORITHM: b. DEQUEUE AND DISPLAY STUDENT PROCESSED
    1. If `isEmpty()`, report Underflow and return false.
    2. Read student at `front`: `processed = queue[front];`
    3. If `front == rear`:
       Queue is now empty, reset `front = -1; rear = -1;`
    4. Else:
       Advance `front++`.
    5. Print processed student information.
    */
    bool dequeueAndProcess() {
        if (isEmpty()) {
            cout << "[ERROR] Admission Queue is empty. No students waiting to be served.\n";
            return false;
        }

        StudentToken processed = queue[front];

        cout << "\n**************************************************************\n";
        cout << "   [DESK OFFICER CALLING] Token #" << processed.tokenNumber << "\n";
        cout << "   Applicant Name : " << processed.studentName << "\n";
        cout << "   Department     : " << processed.department << "\n";
        cout << "   Status         : Verification Complete & Admission Finalized.\n";
        cout << "**************************************************************\n";

        if (front == rear) {
            front = -1;
            rear = -1;
            cout << ">> Notice: All waiting applicants have been processed. Queue is now idle.\n";
        } else {
            front++;
        }

        return true;
    }

    /*
    ALGORITHM: c. DISPLAY FRONT AND REAR TOKEN NUMBERS
    1. Check if empty.
    2. Display `queue[front].tokenNumber` and `queue[rear].tokenNumber`.
    */
    void displayFrontAndRearTokens() const {
        if (isEmpty()) {
            cout << "\n[INFO] Queue is currently idle (No front or rear tokens).\n";
            return;
        }

        cout << "\n--- ADMISSION COUNTER BOUNDARY STATUS ---\n";
        cout << " FRONT TOKEN (Currently being called / next in line) : Token #" 
             << queue[front].tokenNumber << " (" << queue[front].studentName << ")\n";
        cout << " REAR TOKEN  (Most recently issued token)            : Token #" 
             << queue[rear].tokenNumber << " (" << queue[rear].studentName << ")\n";
        cout << " Total Students Waiting in Line                      : " 
             << (rear - front + 1) << "\n-----------------------------------------\n\n";
    }

    /*
    ALGORITHM: d. DISPLAY COMPLETE QUEUE
    1. If empty, print "[QUEUE EMPTY]" and return.
    2. Print formatted table from `front` to `rear`.
    */
    void displayCompleteQueue() const {
        if (isEmpty()) {
            cout << "\n[INFO] Complete admission queue is empty.\n";
            return;
        }

        cout << "\n================ CURRENT WAITING ADMISSION QUEUE ================\n";
        cout << left << setw(8)  << "QueuePos"
             << setw(10) << "Token #"
             << setw(24) << "Applicant Name"
             << setw(22) << "Department"
             << "Desk Note\n";
        cout << "-----------------------------------------------------------------\n";

        int pos = 1;
        for (int i = front; i <= rear; i++) {
            cout << left << setw(8)  << ("#" + to_string(pos))
                 << setw(10) << queue[i].tokenNumber
                 << setw(24) << queue[i].studentName
                 << setw(22) << queue[i].department;

            if (i == front) {
                cout << "<=== NEXT IN LINE";
            } else if (i == rear) {
                cout << "(Latest Arrival)";
            }
            cout << "\n";
            pos++;
        }
        cout << "-----------------------------------------------------------------\n";
        cout << "Total Waiting: " << (rear - front + 1) << " students.\n\n";
    }
};

// Interactive demonstration runner
int main() {
    AdmissionQueue admissionDesk;

    cout << "==============================================================\n";
    cout << "   COLLEGE ADMISSION COUNTER QUEUE (LINEAR QUEUE SIMULATOR)   \n";
    cout << "==============================================================\n";

    // 1. Initial State
    admissionDesk.displayCompleteQueue();

    // 2. a. Enqueue Student Tokens
    cout << "--- DEMO STEP A: Issuing Tokens to Arriving Students ---\n";
    admissionDesk.enqueueToken(101, "Aarav Sharma", "Computer Engineering");
    admissionDesk.enqueueToken(102, "Bhavna Patil", "Information Technology");
    admissionDesk.enqueueToken(103, "Chetan Joshi", "Electronics & Telecom");
    admissionDesk.enqueueToken(104, "Divya Kulkarni", "Computer Engineering");

    // 3. d. Display Complete Queue
    cout << "\n--- DEMO STEP D: Displaying Complete Queue ---\n";
    admissionDesk.displayCompleteQueue();

    // 4. c. Display Front and Rear Tokens
    cout << "--- DEMO STEP C: Displaying Front and Rear Tokens ---\n";
    admissionDesk.displayFrontAndRearTokens();

    // 5. b. Dequeue and Display Processed Students
    cout << "--- DEMO STEP B: Serving Students from Front of Queue ---\n";
    admissionDesk.dequeueAndProcess(); // Serves Token 101
    admissionDesk.dequeueAndProcess(); // Serves Token 102

    // 6. Inspecting Updated Queue
    admissionDesk.displayFrontAndRearTokens();
    admissionDesk.displayCompleteQueue();

    // 7. Enqueuing more students
    cout << "--- DEMO STEP E: New Students Arriving ---\n";
    admissionDesk.enqueueToken(105, "Esha Verma", "Mechanical Engineering");
    admissionDesk.displayCompleteQueue();

    cout << "==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
1. Enqueue Token 101 (Aarav), 102 (Bhavna), 103 (Chetan), 104 (Divya)
2. Front: Token 101, Rear: Token 104
3. Dequeue -> Token 101 processed and admitted
4. Dequeue -> Token 102 processed and admitted
5. Front is now Token 103, Rear is Token 104
6. Enqueue Token 105 (Esha) -> Rear becomes Token 105

SAMPLE OUTPUT:
==============================================================
   COLLEGE ADMISSION COUNTER QUEUE (LINEAR QUEUE SIMULATOR)   
==============================================================

[INFO] Complete admission queue is empty.
--- DEMO STEP A: Issuing Tokens to Arriving Students ---
>> ISSUED: Token #101 issued to Aarav Sharma (Computer Engineering) | Added at Queue Position 1.
>> ISSUED: Token #102 issued to Bhavna Patil (Information Technology) | Added at Queue Position 2.
>> ISSUED: Token #103 issued to Chetan Joshi (Electronics & Telecom) | Added at Queue Position 3.
>> ISSUED: Token #104 issued to Divya Kulkarni (Computer Engineering) | Added at Queue Position 4.

--- DEMO STEP D: Displaying Complete Queue ---

================ CURRENT WAITING ADMISSION QUEUE ================
QueuePosToken #   Applicant Name          Department            Desk Note
-----------------------------------------------------------------
#1      101       Aarav Sharma            Computer Engineering  <=== NEXT IN LINE
#2      102       Bhavna Patil            Information Technology
#3      103       Chetan Joshi            Electronics & Telecom 
#4      104       Divya Kulkarni          Computer Engineering  (Latest Arrival)
-----------------------------------------------------------------
Total Waiting: 4 students.

--- DEMO STEP C: Displaying Front and Rear Tokens ---

--- ADMISSION COUNTER BOUNDARY STATUS ---
 FRONT TOKEN (Currently being called / next in line) : Token #101 (Aarav Sharma)
 REAR TOKEN  (Most recently issued token)            : Token #104 (Divya Kulkarni)
 Total Students Waiting in Line                      : 4
-----------------------------------------

--- DEMO STEP B: Serving Students from Front of Queue ---

**************************************************************
   [DESK OFFICER CALLING] Token #101
   Applicant Name : Aarav Sharma
   Department     : Computer Engineering
   Status         : Verification Complete & Admission Finalized.
**************************************************************

**************************************************************
   [DESK OFFICER CALLING] Token #102
   Applicant Name : Bhavna Patil
   Department     : Information Technology
   Status         : Verification Complete & Admission Finalized.
**************************************************************

--- ADMISSION COUNTER BOUNDARY STATUS ---
 FRONT TOKEN (Currently being called / next in line) : Token #103 (Chetan Joshi)
 REAR TOKEN  (Most recently issued token)            : Token #104 (Divya Kulkarni)
 Total Students Waiting in Line                      : 2
-----------------------------------------


================ CURRENT WAITING ADMISSION QUEUE ================
QueuePosToken #   Applicant Name          Department            Desk Note
-----------------------------------------------------------------
#1      103       Chetan Joshi            Electronics & Telecom <=== NEXT IN LINE
#2      104       Divya Kulkarni          Computer Engineering  (Latest Arrival)
-----------------------------------------------------------------
Total Waiting: 2 students.

--- DEMO STEP E: New Students Arriving ---
>> ISSUED: Token #105 issued to Esha Verma (Mechanical Engineering) | Added at Queue Position 5.

================ CURRENT WAITING ADMISSION QUEUE ================
QueuePosToken #   Applicant Name          Department            Desk Note
-----------------------------------------------------------------
#1      103       Chetan Joshi            Electronics & Telecom <=== NEXT IN LINE
#2      104       Divya Kulkarni          Computer Engineering  
#3      105       Esha Verma              Mechanical Engineering(Latest Arrival)
-----------------------------------------------------------------
Total Waiting: 3 students.

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

TIME COMPLEXITY:
- Enqueue: O(1) constant time.
- Dequeue: O(1) constant time.
- Peek Front / Rear: O(1) constant time.
- Display: O(N) where N is number of waiting applicants.

SPACE COMPLEXITY:
- Auxiliary Space: O(1).
- Total Space: O(MAX_ADMISSIONS) array memory.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Forgetting to Update `front = 0` on First Enqueue.
2. Forgetting to Reset `front = -1; rear = -1;` when the Last Student is Served.
3. Reading `queue[rear]` when queue is empty.
========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Enqueue: `if (isEmpty()) front = 0; queue[++rear] = token;`
[ ] 2. Dequeue: `token = queue[front]; if (front == rear) front = rear = -1; else front++;`
[ ] 3. Front token: `queue[front].tokenNumber;`
[ ] 4. Rear token: `queue[rear].tokenNumber;`
[ ] 5. Display: loop `for (int i = front; i <= rear; i++)`
========================================================================================
*/
