/**
 * ============================================================================
 * SET 1: LIBRARY MANAGEMENT SYSTEM (Part B - Problem 5)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to simulate a book issue counter queue where students
 *   queue up to get books issued.
 *   a. Enqueue student token number
 *   b. Dequeue and display student processed
 *   c. Display front and rear token number
 *   d. Display complete queue
 * ============================================================================
 * ALGORITHM:
 *   1. Use a Circular Queue of fixed capacity MAX.
 *   2. Enqueue Token:
 *      - If (rear + 1) % MAX == front, queue is FULL (Overflow).
 *      - If front == -1, front = rear = 0; else rear = (rear + 1) % MAX.
 *      - queue[rear] = token.
 *   3. Dequeue Token:
 *      - If front == -1, queue is EMPTY (Underflow).
 *      - token = queue[front].
 *      - If front == rear, reset front = rear = -1.
 *      - Else front = (front + 1) % MAX.
 *   4. Front / Rear Display:
 *      - Print queue[front] and queue[rear].
 *   5. Display Queue:
 *      - Loop from front to rear using modulo arithmetic: (i + 1) % MAX.
 * ============================================================================
 */

#include <iostream>

using namespace std;

const int MAX = 6;

class BookIssueQueue {
private:
    int queue[MAX];
    int front;
    int rear;

public:
    BookIssueQueue() : front(-1), rear(-1) {}

    bool isEmpty() { return (front == -1); }
    bool isFull()  { return ((rear + 1) % MAX == front); }

    // a. Enqueue student token number
    bool enqueueToken(int token) {
        if (isFull()) {
            cout << "Counter queue is FULL! Token #" << token << " cannot be issued.\n";
            return false;
        }
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % MAX;
        }
        queue[rear] = token;
        cout << "Enqueued Token #" << token << " at position [" << rear << "].\n";
        return true;
    }

    // b. Dequeue and display student processed
    int dequeueServed() {
        if (isEmpty()) {
            cout << "Counter is IDLE! No students waiting.\n";
            return -1;
        }
        int served = queue[front];
        if (front == rear) {
            front = rear = -1; // Reset when empty
        } else {
            front = (front + 1) % MAX;
        }
        cout << ">> Processed and issued books to Token #" << served << "!\n";
        return served;
    }

    // c. Display front and rear token number
    void displayFrontRear() {
        if (isEmpty()) {
            cout << "Queue is empty. Front and rear are inactive (-1).\n";
            return;
        }
        cout << "\n--- Counter Status ---\n";
        cout << "  Front Token (Next to serve) : #" << queue[front] << "\n";
        cout << "  Rear Token  (Latest arrived): #" << queue[rear] << "\n";
    }

    // d. Display complete queue
    void displayQueue() {
        if (isEmpty()) {
            cout << "Issue counter queue is empty.\n";
            return;
        }
        cout << "\nActive Tokens in Queue (Front to Rear):\n  ";
        int i = front;
        while (true) {
            cout << "[Token #" << queue[i] << "]";
            if (i == rear) break;
            cout << " -> ";
            i = (i + 1) % MAX;
        }
        cout << "\n\n";
    }
};

int main() {
    cout << "==============================================================\n";
    cout << "  SET 1 (PART B - PROBLEM 5): BOOK ISSUE COUNTER QUEUE\n";
    cout << "==============================================================\n";

    BookIssueQueue q;

    // a. Enqueue student tokens
    q.enqueueToken(501);
    q.enqueueToken(502);
    q.enqueueToken(503);
    q.enqueueToken(504);

    // c. Display front & rear
    q.displayFrontRear();

    // d. Display complete queue
    q.displayQueue();

    // b. Dequeue and serve students
    q.dequeueServed();
    q.dequeueServed();

    q.displayFrontRear();
    q.displayQueue();

    return 0;
}
