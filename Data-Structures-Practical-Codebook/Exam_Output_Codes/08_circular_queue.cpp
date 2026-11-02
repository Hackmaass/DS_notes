/**
 * ============================================================================
 * EXAM PROGRAM 08: CIRCULAR QUEUE (FIFO & MODULO WRAP-AROUND)
 * ============================================================================
 * 🧠 60-SECOND EXAM MEMORIZATION TECHNIQUE:
 * 
 * 1. THE 3-VARIABLE ANCHOR:
 *    `int front = 0, rear = -1, count = 0;`
 * 
 * 2. THE 2 CORE MODULO FORMULAS:
 *    - Enqueue Formula:
 *        `rear = (rear + 1) % MAX;`
 *        `q[rear] = val;`
 *        `count++;`
 *    - Dequeue Formula:
 *        `int removed = q[front];`
 *        `front = (front + 1) % MAX;`
 *        `count--;`
 * 
 * 3. THE CIRCULAR DISPLAY FORMULA:
 *    - Loop `i` from `0` to `count - 1`:
 *        `int idx = (front + i) % MAX;`
 *        `cout << q[idx] << " ";`
 * 
 * 4. THE EXAM PANIC CHECKLIST (The 3 Bugs Examiners Catch):
 *    - TRAP 1 (The Linear Queue Trap): Writing `rear++` instead of
 *              `rear = (rear + 1) % MAX`. If you forget modulo, indices never
 *              wrap around, and you fail the circular queue test!
 *    - TRAP 2 (The Broken Display Trap): Writing `for (int i = front; i <= rear; i++)`.
 *              When the queue wraps around, `rear` (e.g. 1) is LESS than `front` (e.g. 3)!
 *              A simple `front` to `rear` loop will NOT RUN AT ALL! Always use
 *              `for (int i = 0; i < count; i++)` with `(front + i) % MAX`.
 *    - TRAP 3: Forgetting `count++` or `count--`.
 * 
 * ============================================================================
 * EXPECTED TERMINAL OUTPUT SHOWN TO EXAMINER:
 * 
 * Enqueued: 10 20 30 40 50 (Queue Full 5/5)
 * Dequeued: 10 and 20
 * Enqueued: 60 and 70 (Modulo wrap-around to indices 0 and 1!)
 * Current Circular Queue: 30 40 50 60 70 
 * Front Index: 2, Rear Index: 1
 * ============================================================================
 */

#include <iostream>

using namespace std;

const int MAX = 5;

int main() {
    int q[MAX];
    int front = 0, rear = -1, count = 0;

    // 1. ENQUEUE 5 ELEMENTS (Fills queue)
    cout << "Enqueued: ";
    for (int val : {10, 20, 30, 40, 50}) {
        rear = (rear + 1) % MAX; // Advance rear cyclically
        q[rear] = val;
        count++;
        cout << val << " ";
    }
    cout << "(Queue Full 5/5)\n";

    // 2. DEQUEUE 2 ELEMENTS FROM FRONT (Frees physical slots 0 and 1)
    cout << "Dequeued: " << q[front] << " ";
    front = (front + 1) % MAX; // Advance front cyclically
    count--;

    cout << "and " << q[front] << "\n";
    front = (front + 1) % MAX; // Advance front cyclically
    count--;

    // 3. ENQUEUE 60 AND 70 (WRAPS AROUND TO REUSE SLOTS 0 AND 1!)
    cout << "Enqueued: 60 and 70 (Modulo wrap-around to indices 0 and 1!)\n";
    for (int val : {60, 70}) {
        rear = (rear + 1) % MAX; // Wraps rear back to 0, then 1!
        q[rear] = val;
        count++;
    }

    // 4. DISPLAY ALL ACTIVE ELEMENTS USING CIRCULAR INDEXING
    cout << "Current Circular Queue: ";
    for (int i = 0; i < count; i++) {
        int idx = (front + i) % MAX; // Correct circular index formula
        cout << q[idx] << " ";
    }
    cout << "\nFront Index: " << front << ", Rear Index: " << rear << "\n";

    return 0;
}

/**
 * ============================================================================
 * 🎓 EXAMINER VIVA QUESTIONS & INSTANT ANSWERS:
 * Q: What problem does a Circular Queue solve that a Linear Queue cannot?
 * A: It eliminates "False Overflow". In a linear queue, when items are dequeued,
 *    space at the front is wasted and new items cannot be inserted once `rear == MAX - 1`.
 *    A circular queue wraps back to index 0 using modulo arithmetic to reuse that space.
 *
 * Q: What is the Time Complexity of Enqueue and Dequeue in a Circular Queue?
 * A: O(1) instantaneous time. No elements are ever shifted!
 *
 * Q: Why can't you display a circular queue with `for (int i = front; i <= rear; i++)`?
 * A: Because after wrap-around, `rear` can be a smaller number than `front` (e.g.
 *    front = 3, rear = 1). The standard loop condition `i <= rear` would be false
 *    on the very first iteration and print nothing!
 * ============================================================================
 */
