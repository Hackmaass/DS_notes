# Data Structures & Algorithms Complexity Reference

A concise theoretical and practical lookup table with derivation justifications for Second Year B.Tech Computer Engineering practical and oral examinations.

---

## 1. Master Complexity Lookup Table

| Data Structure / Algorithm | Operation / Case | Best Case Time | Average Case Time | Worst Case Time | Auxiliary Space | In-Place? | Stable? |
|---|---|---|---|---|---|---|---|
| **Array** | Access by Index | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | Yes | N/A |
| **Array** | Search (Unsorted) | $O(1)$ | $O(N)$ | $O(N)$ | $O(1)$ | Yes | N/A |
| **Array** | Insertion (at pos) | $O(1)$ (at end) | $O(N)$ | $O(N)$ (at head) | $O(1)$ | Yes | N/A |
| **Array** | Deletion (by index) | $O(1)$ (at end) | $O(N)$ | $O(N)$ (at head) | $O(1)$ | Yes | N/A |
| **Singly Linked List** | Insert at Head | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | Yes | N/A |
| **Singly Linked List** | Insert at Tail (no tail ptr) | $O(N)$ | $O(N)$ | $O(N)$ | $O(1)$ | Yes | N/A |
| **Singly Linked List** | Delete at Head | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | Yes | N/A |
| **Singly Linked List** | Delete by Key | $O(1)$ | $O(N)$ | $O(N)$ | $O(1)$ | Yes | N/A |
| **Doubly Linked List** | Sorted Insertion | $O(1)$ | $O(N)$ | $O(N)$ | $O(1)$ | Yes | N/A |
| **Doubly Linked List** | Delete Node (given ptr) | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | Yes | N/A |
| **Circular Linked List** | Traversal | $O(N)$ | $O(N)$ | $O(N)$ | $O(1)$ | Yes | N/A |
| **Linear Search** | Value Match | $O(1)$ (at idx 0) | $O(N)$ | $O(N)$ (not found) | $O(1)$ | Yes | N/A |
| **Binary Search** | Value Match | $O(1)$ (at mid) | $O(\log N)$ | $O(\log N)$ | $O(1)$ | Yes | N/A |
| **Bubble Sort** | Array Sorting | $O(N)$ (optimized) | $O(N^2)$ | $O(N^2)$ | $O(1)$ | Yes | **Yes** |
| **Selection Sort** | Array Sorting | $O(N^2)$ | $O(N^2)$ | $O(N^2)$ | $O(1)$ | Yes | **No** |
| **Insertion Sort** | Array Sorting | $O(N)$ (sorted) | $O(N^2)$ | $O(N^2)$ (reverse) | $O(1)$ | Yes | **Yes** |
| **Quick Sort** | Array Sorting | $O(N \log N)$ | $O(N \log N)$ | $O(N^2)$ (sorted/pivot) | $O(\log N)$ stack | Yes | **No** |
| **Merge Sort** | Array Sorting | $O(N \log N)$ | $O(N \log N)$ | $O(N \log N)$ | $O(N)$ buffer | No | **Yes** |
| **Stack (Array / LL)** | Push / Pop / Peek | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | Yes | N/A |
| **Infix to Postfix** | Shunting-Yard Scan | $O(N)$ | $O(N)$ | $O(N)$ | $O(N)$ stack | No | N/A |
| **Postfix Evaluation** | Stack Computation | $O(N)$ | $O(N)$ | $O(N)$ | $O(N)$ stack | No | N/A |
| **Parenthesis Match** | Delimiter Check | $O(N)$ | $O(N)$ | $O(N)$ | $O(N)$ stack | No | N/A |
| **Linear Queue** | Enqueue / Dequeue | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | Yes | N/A |
| **Circular Queue** | Enqueue / Dequeue | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | Yes | N/A |
| **Priority Queue** | Insert (Sorted Array) | $O(1)$ (at end) | $O(N)$ | $O(N)$ | $O(1)$ | Yes | N/A |
| **Priority Queue** | Dequeue Max (Array) | $O(N)$ (shift) | $O(N)$ | $O(N)$ | $O(1)$ | Yes | N/A |
| **Deque** | Insert/Delete Front/Rear | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | Yes | N/A |

---

## 2. Derivations & Justifications (Viva Favorites)

### 1. Why Binary Search is $O(\log_2 N)$
- In each step, the search interval $[low, high]$ is halved: $N, N/2, N/4, \dots, N/2^k = 1$.
- Solving $N/2^k = 1 \implies 2^k = N \implies k = \log_2 N$.
- Therefore, at most $\lceil \log_2 N \rceil$ comparisons are made.

### 2. Why Selection Sort is Always $O(N^2)$
- Outer loop runs $N - 1$ times.
- Inner loop runs $(N - 1), (N - 2), \dots, 1$ times regardless of whether the array is already sorted, randomly ordered, or reversely ordered!
- Total comparisons $= \sum_{i=1}^{N-1} i = \frac{N(N - 1)}{2} = \frac{N^2 - N}{2} = \Theta(N^2)$.

### 3. Why Quick Sort Worst Case is $O(N^2)$
- When the selected pivot is always the smallest or largest element (e.g., partitioning an already sorted array using the last element as pivot), one subproblem has size $N - 1$ and the other has size $0$.
- Recurrence: $T(N) = T(N - 1) + O(N) = O(N^2)$.
- Best Case (balanced partition): $T(N) = 2T(N/2) + O(N) = O(N \log N)$.

### 4. Why Merge Sort Auxiliary Space is $O(N)$
- The `merge()` procedure requires temporary buffer arrays `L[]` and `R[]` to hold elements before copying back into `arr[]`.
- Size of `L[]` + `R[]` across any merge step equals $N$. Hence, auxiliary space $= O(N)$.

### 5. Why Array vs Linked List Memory Overhead Differs
- **Array**: Zero per-element overhead; stores only raw data. Contiguous memory ensures high cache locality.
- **Singly Linked List**: Each node requires 1 pointer (`Node* next`, 8 bytes on 64-bit OS) in addition to data.
- **Doubly Linked List**: Each node requires 2 pointers (`prev` and `next`, $2 \times 8 = 16$ bytes overhead).
- **Heap Allocation Overhead**: Every `new` call incurs heap metadata overhead (typically 8–16 bytes per allocation in glibc/UCRT).
