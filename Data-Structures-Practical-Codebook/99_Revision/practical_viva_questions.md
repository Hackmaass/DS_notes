# Practical Viva-Voce Master Question Bank

A high-yield compilation of 35 core questions and concise model answers frequently asked by university examiners during S.Y. B.Tech Computer Engineering practical exams for **CE25PCC-203 (Data Structures Laboratory)** at NMIET.

---

## Unit I: Arrays & Linked Lists

**Q1: What is the fundamental difference between an Array and a Linked List in memory?**  
*Answer:* An array is allocated as a single contiguous block of memory (usually in the stack or heap), where elements are accessed via base address plus index offset in $O(1)$ time. A linked list consists of individual nodes scattered across non-contiguous heap memory, each holding data and explicit pointer(s) to neighbor(s), accessed sequentially in $O(N)$ time.

**Q2: What is the time complexity of inserting an element at position $k$ in an array vs. a linked list (given node pointer)?**  
*Answer:* In an array, inserting at position $k$ requires shifting $N - k$ elements, taking $O(N)$ time. In a linked list, if a pointer to the $k$-th node is already available, insertion takes $O(1)$ time (simple pointer updates); however, finding that position from head takes $O(k) = O(N)$ time.

**Q3: Why does a Doubly Linked List require more memory than a Singly Linked List?**  
*Answer:* Each DLL node stores two pointers (`prev` and `next`), whereas an SLL node stores only one pointer (`next`). On a 64-bit architecture, each pointer occupies 8 bytes, so a DLL node incurs 16 bytes of pointer overhead per node compared to 8 bytes in an SLL node.

**Q4: What is the termination condition for traversing a Circular Linked List?**  
*Answer:* In a standard SLL, traversal stops when `temp == NULL`. In a CLL, the last node points back to the `head`. Therefore, we use a `do-while` loop: `do { ... temp = temp->next; } while (temp != head);`.

**Q5: What is a memory leak, and how do we prevent it in C++ linked lists?**  
*Answer:* A memory leak occurs when heap memory dynamically allocated with `new` is no longer reachable by any pointer and is never released using `delete`. We prevent it by writing explicit destructors or delete functions that iterate through the list and free every node before terminating or reassigning pointers.

---

## Unit II: Searching & Sorting

**Q6: What prerequisite must an array satisfy before performing Binary Search?**  
*Answer:* The array elements must be strictly sorted in monotonic (ascending or descending) order. Binary search relies on this ordering to eliminate half of the remaining search space in each iteration.

**Q7: Explain the difference between Stable and Unstable sorting algorithms.**  
*Answer:* A sorting algorithm is **stable** if elements with identical keys maintain their original relative order after sorting. Examples: Bubble Sort, Insertion Sort, Merge Sort. An algorithm is **unstable** if identical keys may swap relative positions. Examples: Selection Sort, Quick Sort, Heap Sort.

**Q8: Why is Selection Sort preferred when memory write operations are extremely expensive?**  
*Answer:* Selection Sort performs at most $N - 1$ swaps (data writes) across the entire sort ($O(N)$ writes), whereas Bubble Sort and Insertion Sort can perform up to $O(N^2)$ writes/shifts.

**Q9: Why does Quick Sort have a worst-case time complexity of $O(N^2)$?**  
*Answer:* When the chosen pivot repeatedly yields the most unbalanced partition possible (e.g., partitioning an already sorted array using the last element as pivot, resulting in subproblems of size $N - 1$ and $0$).

**Q10: Explain the Divide-and-Conquer strategy used in Merge Sort.**  
*Answer:* Merge Sort divides the array into two halves ($mid = left + (right - left)/2$), recursively sorts both halves, and then merges the two sorted subarrays into a single sorted array using temporary buffer arrays in $O(N)$ time.

**Q11: Can Binary Search be performed efficiently on a Singly Linked List?**  
*Answer:* No. Finding the midpoint of a linked list requires linear traversal ($O(N)$), negating the logarithmic benefit. The overall search time on a linked list would still be $O(N)$.

---

## Unit III: Stacks & Recursion

**Q12: What is an Abstract Data Type (ADT)?**  
*Answer:* An ADT is a mathematical model for data types defined solely by the operations that can be performed on it and the behaviors/constraints of those operations, without specifying how the data is stored in memory or how the algorithms are implemented.

**Q13: What is the LIFO principle? Name two practical applications.**  
*Answer:* Last-In, First-Out: the element inserted most recently is the first one removed. Applications: Browser history back-button navigation, Undo/Redo operations in text editors, and compiler call stacks.

**Q14: Explain the role of the Call Stack in recursion.**  
*Answer:* When a function calls itself, the system allocates an **Activation Record (Stack Frame)** on the runtime call stack storing local variables, parameters, and the return address. When a base case is reached, frames are popped and control unwinds back to the callers.

**Q15: What is Stack Overflow and Stack Underflow?**  
*Answer:*
- **Overflow:** Occurs when an attempt is made to push an item onto a stack that has already reached its maximum capacity (`top == MAX - 1`).
- **Underflow:** Occurs when an attempt is made to pop an item from an empty stack (`top == -1`).

**Q16: Why are postfix expressions preferred over infix expressions by compilers?**  
*Answer:* Postfix expressions are parenthesis-free and operators appear strictly in execution order. A compiler can evaluate a postfix expression in a single left-to-right pass using a simple stack in $O(N)$ time without needing operator precedence lookahead or backtracking.

**Q17: In evaluating postfix `5 3 -`, why must we compute `op1 - op2` and not `op2 - op1`?**  
*Answer:* Because the stack is LIFO, the first popped operand is `3` (the right operand `op2`), and the second popped operand is `5` (the left operand `op1`). Subtraction is non-commutative, so we must calculate `op1 - op2 = 5 - 3 = 2`.

---

## Unit IV: Queues

**Q18: What is "False Overflow" in a linear array queue?**  
*Answer:* In a linear queue, when `rear` reaches `MAX - 1`, the queue reports "Overflow" on any subsequent enqueue, even if multiple elements have been dequeued from `front` leaving free slots at the start of the array.

**Q19: How does a Circular Queue solve False Overflow?**  
*Answer:* A circular queue conceptually connects the end of the array back to the beginning using modulo arithmetic (`(rear + 1) % MAX`), allowing newly arriving elements to wrap around and occupy slots vacated by earlier dequeues.

**Q20: What are the exact full and empty conditions in a circular queue?**  
*Answer:*
- **Empty Condition:** `front == -1`
- **Full Condition:** `(rear + 1) % MAX == front`

**Q21: What is a Priority Queue? How does it differ from a standard FIFO queue?**  
*Answer:* In a standard queue, elements exit strictly in FIFO order. In a Priority Queue, each element has a priority; elements with highest priority are dequeued before lower-priority elements regardless of their arrival time. If priorities are equal, FIFO order is maintained.

**Q22: What is a Deque (Double-Ended Queue)?**  
*Answer:* A linear data structure that supports insertion and deletion at both ends: `insertFront`, `insertRear`, `deleteFront`, `deleteRear`.

**Q23: What is the difference between an Input-Restricted Deque and an Output-Restricted Deque?**  
*Answer:*
- **Input-Restricted:** Insertion is allowed at only one end, while deletion is allowed at both ends.
- **Output-Restricted:** Deletion is allowed at only one end, while insertion is allowed at both ends.

**Q24: Give two real-world operating system applications of queues.**  
*Answer:*
1. **CPU Process Scheduling:** Round-Robin scheduler ready queue.
2. **I/O Device Spooling:** Printer spooler buffer queue and disk I/O request queues.
