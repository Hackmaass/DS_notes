/**
 * ============================================================================
 * COURSE:        Data Structures (CE25PCC-202) - Unit IV: Queues
 * LAB COURSE:    Data Structures Laboratory (CE25PCC-203)
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * MODULE:        Unit IV Theory Foundation & Practical Application
 * TITLE:         Queue Applications: Round-Robin CPU Scheduling & Print Spooler Queue
 * 
 * CURRICULUM SYLLABUS REFERENCE:
 *   "Unit IV: Queue: Representation of queue using array and linked list,
 *    Concept of Circular queue, Priority queue, Deque. 
 *    Applications of queue: CPU scheduling, Print queue simulation."
 * 
 * ============================================================================
 * CONCEPT EXPLANATION: WHY QUEUES IN REAL-WORLD COMPUTING SYSTEMS?
 * ============================================================================
 * A Queue is fundamental to asynchronous resource sharing where multiple 
 * consumers/producers share a single shared hardware resource (CPU, Printer,
 * Network socket, Disk controller).
 * 
 * APPLICATION 1: ROUND-ROBIN CPU SCHEDULING
 *   - The CPU is a single fast resource; multiple processes (tasks) demand CPU time.
 *   - In Round-Robin (RR) scheduling, time is divided into small slices called
 *     TIME QUANTA (e.g., 2 ms or 3 ms).
 *   - A circular ready queue holds runnable processes.
 *   - The scheduler dequeues the process at the front, grants it CPU time up to
 *     the quantum:
 *       * If the process finishes within the quantum, it completes and terminates.
 *       * If it still needs more time, it is PREEMPTED and re-enqueued at the rear.
 *   - The queue ensures complete fairness with no starvation!
 * 
 * APPLICATION 2: PRINTER SPOOLER QUEUE
 *   - Printers are mechanical devices that print pages orders of magnitude
 *     slower than computers generate print requests.
 *   - The operating system implements a print spooler queue (FIFO).
 *   - Documents submitted by users are queued at the rear.
 *   - The printer hardware dequeues from the front and prints page-by-page.
 * ============================================================================
 * STEP-BY-STEP ALGORITHM: ROUND-ROBIN CPU SCHEDULING
 * ============================================================================
 * 1. Define `Process` struct: `pid`, `name`, `burstTime`, `remainingTime`.
 * 2. Maintain a Circular Ready Queue of capacity `MAX_PROC`.
 * 3. Set `TIME_QUANTUM` (e.g., 2 units).
 * 4. While the Ready Queue is not empty:
 *    a. Dequeue process `P` from the front.
 *    b. Determine execution time: `execTime = min(P.remainingTime, TIME_QUANTUM)`.
 *    c. Deduct: `P.remainingTime -= execTime`. Advance global simulation clock.
 *    d. If `P.remainingTime == 0`: Process has finished execution.
 *    e. Else: Process still needs CPU; re-enqueue `P` at the rear of the ready queue.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Maximum capacities for queues
const int MAX_PROCESSES = 10;
const int MAX_PRINT_JOBS = 10;
const int TIME_QUANTUM = 3; // CPU time slice per round

// ============================================================================
// PART 1: CPU SCHEDULING DATA STRUCTURES & IMPLEMENTATION
// ============================================================================
struct Process {
    int pid;
    string processName;
    int burstTime;      // Total CPU time required
    int remainingTime;  // CPU time left to complete
};

class RoundRobinReadyQueue {
private:
    Process queue[MAX_PROCESSES];
    int front;
    int rear;
    int count;

public:
    RoundRobinReadyQueue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    bool isEmpty() const {
        return (count == 0);
    }

    bool isFull() const {
        return (count == MAX_PROCESSES);
    }

    int getCount() const {
        return count;
    }

    bool enqueue(const Process& p) {
        if (isFull()) {
            cout << "  [OVERFLOW] CPU Ready Queue is full! Cannot schedule PID: " << p.pid << "\n";
            return false;
        }
        rear = (rear + 1) % MAX_PROCESSES;
        queue[rear] = p;
        count++;
        return true;
    }

    bool dequeue(Process& p) {
        if (isEmpty()) {
            return false;
        }
        p = queue[front];
        front = (front + 1) % MAX_PROCESSES;
        count--;
        return true;
    }

    void displayReadyQueue() const {
        if (isEmpty()) {
            cout << "  [READY QUEUE] Empty (CPU is IDLE)\n";
            return;
        }
        cout << "  [READY QUEUE] ";
        int idx = front;
        for (int i = 0; i < count; ++i) {
            cout << "[" << queue[idx].processName << " (Rem: " << queue[idx].remainingTime << "ms)]";
            if (i < count - 1) cout << " -> ";
            idx = (idx + 1) % MAX_PROCESSES;
        }
        cout << "\n";
    }
};

void simulateRoundRobinCPU() {
    cout << "\n====================================================================\n";
    cout << "  APPLICATION 1: ROUND-ROBIN CPU SCHEDULING SIMULATION\n";
    cout << "  (Time Quantum = " << TIME_QUANTUM << " ms)\n";
    cout << "====================================================================\n";

    RoundRobinReadyQueue readyQ;

    // Load initial processes
    Process p1 = {1, "Compiler_Task", 7, 7};
    Process p2 = {2, "Browser_Tab  ", 4, 4};
    Process p3 = {3, "Media_Player ", 2, 2};
    Process p4 = {4, "Text_Editor  ", 6, 6};

    readyQ.enqueue(p1);
    readyQ.enqueue(p2);
    readyQ.enqueue(p3);
    readyQ.enqueue(p4);

    cout << "Initial Ready Queue State:\n";
    readyQ.displayReadyQueue();

    int currentTime = 0;
    int cycle = 1;

    cout << "\n" << setfill('-') << setw(72) << "-" << setfill(' ') << "\n";
    cout << left << setw(8) << "Cycle" 
         << setw(16) << "Active Process" 
         << setw(12) << "Allocated" 
         << setw(14) << "Time Range" 
         << setw(12) << "Rem Time" 
         << "Action\n";
    cout << setfill('-') << setw(72) << "-" << setfill(' ') << "\n";

    while (!readyQ.isEmpty()) {
        Process curr;
        readyQ.dequeue(curr);

        int executeFor = (curr.remainingTime < TIME_QUANTUM) ? curr.remainingTime : TIME_QUANTUM;
        int startTime = currentTime;
        currentTime += executeFor;
        curr.remainingTime -= executeFor;

        cout << left << setw(8) << cycle
             << setw(16) << curr.processName
             << setw(3) << executeFor << " ms     "
             << "[" << setw(2) << startTime << " - " << setw(2) << currentTime << " ms]  "
             << setw(3) << curr.remainingTime << " ms     ";

        if (curr.remainingTime == 0) {
            cout << "COMPLETED [Terminated]\n";
        } else {
            cout << "PREEMPTED -> Re-enqueued\n";
            readyQ.enqueue(curr);
        }

        readyQ.displayReadyQueue();
        cout << "\n";
        cycle++;
    }

    cout << "All processes completed execution successfully at Time = " << currentTime << " ms.\n";
}

// ============================================================================
// PART 2: PRINT SPOOLER QUEUE DATA STRUCTURES & IMPLEMENTATION
// ============================================================================
struct PrintJob {
    int jobId;
    string documentName;
    string owner;
    int pages;
};

class PrintSpoolerQueue {
private:
    PrintJob arr[MAX_PRINT_JOBS];
    int front;
    int rear;
    int count;

public:
    PrintSpoolerQueue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    bool isEmpty() const {
        return (count == 0);
    }

    bool isFull() const {
        return (count == MAX_PRINT_JOBS);
    }

    bool addPrintJob(int id, const string& doc, const string& user, int pages) {
        if (isFull()) {
            cout << "  [PRINT OVERFLOW] Print spooler buffer full! Cannot accept Job #" << id << "\n";
            return false;
        }
        rear = (rear + 1) % MAX_PRINT_JOBS;
        arr[rear] = {id, doc, user, pages};
        count++;
        cout << "  [JOB QUEUED] Job #" << id << " ('" << doc << "' by " 
             << user << ", " << pages << " pages) added to spooler.\n";
        return true;
    }

    bool printNextJob() {
        if (isEmpty()) {
            cout << "  [SPOOLER IDLE] No print jobs pending in queue.\n";
            return false;
        }
        PrintJob job = arr[front];
        front = (front + 1) % MAX_PRINT_JOBS;
        count--;

        cout << "  [PRINTING...] Printing Job #" << job.jobId << " ('" << job.documentName 
             << "') for user [" << job.owner << "] -> " << job.pages << " pages printed.\n";
        return true;
    }

    void displaySpooler() const {
        if (isEmpty()) {
            cout << "  [PRINT SPOOLER] Queue is EMPTY. Ready for new print requests.\n";
            return;
        }

        cout << "\n  --- Current Print Spooler Queue (" << count << " jobs pending) ---\n";
        int idx = front;
        for (int i = 0; i < count; ++i) {
            cout << "  #" << (i + 1) << " [Job " << arr[idx].jobId << "]: " 
                 << arr[idx].documentName << " (" << arr[idx].pages << " pgs) by " 
                 << arr[idx].owner << "\n";
            idx = (idx + 1) % MAX_PRINT_JOBS;
        }
        cout << "\n";
    }
};

void simulatePrintSpooler() {
    cout << "\n====================================================================\n";
    cout << "  APPLICATION 2: PRINTER SPOOLER QUEUE SIMULATION (FIFO)\n";
    cout << "====================================================================\n";

    PrintSpoolerQueue spooler;

    spooler.addPrintJob(201, "Data_Structures_Manual.pdf", "Omkar Rane", 24);
    spooler.addPrintJob(202, "Research_Paper_Draft.docx", "Prof. Sharma", 8);
    spooler.addPrintJob(203, "Lab_Attendance_Report.xlsx", "Admin Office", 3);
    spooler.displaySpooler();

    cout << "Printer Hardware Ready -> Dequeuing and Printing from FRONT:\n";
    spooler.printNextJob();
    spooler.displaySpooler();

    spooler.printNextJob();
    spooler.displaySpooler();

    cout << "New incoming urgent print job arrives during active printing:\n";
    spooler.addPrintJob(204, "Exam_Paper_Sealed.pdf", "Exam Controller", 15);
    spooler.displaySpooler();

    cout << "Printing all remaining jobs:\n";
    while (!spooler.isEmpty()) {
        spooler.printNextJob();
    }
    spooler.displaySpooler();
}

int main() {
    simulateRoundRobinCPU();
    simulatePrintSpooler();
    return 0;
}

/*
 * ============================================================================
 * COMPLEXITY ANALYSIS
 * ============================================================================
 * Application      | Operation        | Time Complexity | Space Complexity
 * -----------------+------------------+-----------------+------------------
 * CPU Scheduling   | Enqueue Process  | O(1)            | O(1)
 * CPU Scheduling   | Dequeue Process  | O(1)            | O(1)
 * CPU Scheduling   | Complete Run     | O(Total Burst/Q)| O(MAX_PROCESSES)
 * Print Spooler    | Submit Job       | O(1)            | O(1)
 * Print Spooler    | Print/Serve Job  | O(1)            | O(1)
 * Print Spooler    | Display Buffer   | O(Jobs)         | O(MAX_PRINT_JOBS)
 * ============================================================================
 * COMMON EXAM PITFALLS & MISTAKES TO AVOID
 * ============================================================================
 * 1. Forgetting Preemption Re-enqueue: When a process still has remaining time,
 *    failing to enqueue it back into the ready queue loses the process!
 * 2. Deducting Fixed Quantum Blindly: If remaining time < Time Quantum, do NOT
 *    deduct the full quantum, only deduct `min(remainingTime, Quantum)`.
 *    Otherwise, remaining time becomes negative!
 * 3. Violating FIFO in Print Spooler: Print jobs must be printed strictly in
 *    the order received from front to rear.
 * ============================================================================
 * EXAM MEMORIZATION CHECKLIST
 * ============================================================================
 * [ ] Round Robin Loop:
 *     `while(!queue.isEmpty()) {`
 *         `p = dequeue();`
 *         `exec = min(p.remTime, QUANTUM);`
 *         `p.remTime -= exec;`
 *         `if (p.remTime > 0) enqueue(p);`
 *     `}`
 * [ ] Print Spooler:
 *     Standard circular FIFO queue: Enqueue at rear, dequeue at front to print.
 * ============================================================================
 */
