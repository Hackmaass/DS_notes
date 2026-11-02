# Rapid Algorithm Revision & Memorization Guide

Designed specifically for Second Year Computer Engineering students preparing for the **Data Structures Practical Examination (CE25PCC-203)** at NMIET / PCET Autonomy.

---

## Unit I: Arrays & Linked Lists

### 1. Array Insertion at Position `pos` (1-Based)
```
1. Check Overflow: if size >= MAX, return Overflow.
2. Check Bounds: if pos < 1 or pos > size + 1, return Invalid Position.
3. Shift Right: for i = size down to pos:
       arr[i] = arr[i - 1]
4. Insert: arr[pos - 1] = newItem
5. Update: size = size + 1
```

### 2. Array Deletion by Key
```
1. Search Key: targetIndex = -1
   for i = 0 to size - 1:
       if arr[i].key == searchKey: targetIndex = i; break;
2. If targetIndex == -1, return Not Found.
3. Shift Left: for i = targetIndex to size - 2:
       arr[i] = arr[i + 1]
4. Update: size = size - 1
```

### 3. Singly Linked List (SLL) Append (Insert at End)
```
1. Allocate new node: Node* nn = new Node(data)
2. If head == NULL:
       head = nn; return;
3. Traverse to tail:
       Node* temp = head
       while temp->next != NULL:
           temp = temp->next
4. Link: temp->next = nn
```

### 4. SLL Insert After a Key / Middle
```
1. Traverse to find key:
       Node* temp = head
       while temp != NULL and temp->data != key:
           temp = temp->next
2. If temp == NULL, return Key Not Found.
3. Allocate new node: Node* nn = new Node(newData)
4. Link: nn->next = temp->next
5. Link predecessor: temp->next = nn
```

### 5. SLL Delete Front
```
1. If head == NULL, return Underflow.
2. Node* temp = head
3. Advance head: head = head->next
4. Deallocate: delete temp
```

### 6. Doubly Linked List (DLL) Sorted Insertion
```
1. Allocate new node: Node* nn = new Node(data)
2. If head == NULL or data < head->data:
       nn->next = head
       if head != NULL: head->prev = nn
       head = nn
       return
3. Traverse until next node has larger key:
       Node* curr = head
       while curr->next != NULL and curr->next->data < data:
           curr = curr->next
4. Splice:
       nn->next = curr->next
       nn->prev = curr
       if curr->next != NULL: curr->next->prev = nn
       curr->next = nn
```

### 7. Circular Linked List (CLL) Traversal
```
1. If head == NULL, return Empty.
2. Node* temp = head
3. do {
       print temp->data
       temp = temp->next
   } while temp != head;
```

---

## Unit II: Searching & Sorting

### 8. Linear Search
```
1. for i = 0 to n - 1:
       if arr[i] == target: return i (Found)
2. return -1 (Not Found)
```

### 9. Binary Search (Requires Sorted Array)
```
1. low = 0, high = n - 1
2. while low <= high:
       mid = low + (high - low) / 2
       if arr[mid] == target: return mid (Found)
       else if arr[mid] < target: low = mid + 1
       else: high = mid - 1
3. return -1 (Not Found)
```

### 10. Bubble Sort (With Early Exit Optimization)
```
1. for i = 0 to n - 2:
       swapped = false
       for j = 0 to n - 2 - i:
           if arr[j] > arr[j + 1]:
               swap(arr[j], arr[j + 1])
               swapped = true
       if not swapped: break (Already sorted)
```

### 11. Selection Sort
```
1. for i = 0 to n - 2:
       minIdx = i
       for j = i + 1 to n - 1:
           if arr[j] < arr[minIdx]: minIdx = j
       if minIdx != i:
           swap(arr[i], arr[minIdx])
```

### 12. Insertion Sort (With Shift Counting)
```
1. for i = 1 to n - 1:
       key = arr[i]
       j = i - 1
       while j >= 0 and arr[j] > key:
           arr[j + 1] = arr[j]  (Shift right)
           shifts++
           j--
       arr[j + 1] = key
```

### 13. Quick Sort (Lomuto Partition Scheme)
```
Partition(arr, low, high):
1. pivot = arr[high]
2. i = low - 1
3. for j = low to high - 1:
       if arr[j] <= pivot:
           i++
           swap(arr[i], arr[j])
4. swap(arr[i + 1], arr[high])
5. return i + 1

QuickSort(arr, low, high):
1. if low < high:
       pi = Partition(arr, low, high)
       QuickSort(arr, low, pi - 1)
       QuickSort(arr, pi + 1, high)
```

### 14. Merge Sort (Divide & Conquer)
```
Merge(arr, left, mid, right):
1. Create temporary arrays L[n1] and R[n2].
2. Copy arr[left..mid] to L and arr[mid+1..right] to R.
3. Compare L[i] and R[j], place smaller into arr[k++].
4. Copy remaining elements of L and R.

MergeSort(arr, left, right):
1. if left < right:
       mid = left + (right - left) / 2
       MergeSort(arr, left, mid)
       MergeSort(arr, mid + 1, right)
       Merge(arr, left, mid, right)
```

---

## Unit III: Stacks & Recursion

### 15. Infix to Postfix Conversion (Shunting-Yard)
```
1. Create empty character stack `s`. Output string `postfix = ""`.
2. For each character `ch` in infix:
   a. If operand (letter/digit): append to `postfix`.
   b. If '(': push to `s`.
   c. If ')': pop from `s` to `postfix` until '(' is popped. Pop '('.
   d. If operator (+, -, *, /):
      while stack not empty and precedence(s.top()) >= precedence(ch):
          postfix += s.pop()
      push ch to `s`.
3. Pop all remaining operators from `s` into `postfix`.
```

### 16. Postfix Expression Evaluation
```
1. Create empty float/int operand stack `s`.
2. For each token in postfix:
   a. If operand: push numerical value onto `s`.
   b. If operator:
      op2 = s.pop()
      op1 = s.pop()
      result = op1 (operator) op2
      push result onto `s`.
3. Return s.pop() as final answer.
```

### 17. Balanced Parentheses Checker
```
1. Create empty character stack `s`.
2. For each character `ch` in expression:
   a. If `ch` in {'(', '{', '['}: push `ch` onto `s`.
   b. If `ch` in {')', '}', ']'}:
      if s.isEmpty(): return Unbalanced (Closing without opening).
      top = s.pop()
      if not match(top, ch): return Unbalanced (Mismatched type).
3. Return s.isEmpty() (True = Balanced, False = Unclosed brackets remaining).
```

---

## Unit IV: Queues

### 18. Circular Queue (Array Implementation)
```
1. Full Check: `(rear + 1) % MAX == front`
2. Empty Check: `front == -1`
3. Enqueue(val):
   - if isFull(): return Overflow
   - if isEmpty(): front = 0; rear = 0;
   - else: rear = (rear + 1) % MAX
   - queue[rear] = val
4. Dequeue():
   - if isEmpty(): return Underflow
   - val = queue[front]
   - if front == rear: front = -1; rear = -1; (Reset when empty)
   - else: front = (front + 1) % MAX
   - return val
```

### 19. Priority Queue (Ordered Array - Descending CGPA)
```
1. Enqueue(val, priority):
   - if size == MAX: return Overflow
   - i = size - 1
   - while i >= 0 and queue[i].priority < priority:
         queue[i + 1] = queue[i]  (Shift right)
         i--
   - queue[i + 1] = {val, priority}
   - size++
2. DequeueHighest():
   - if size == 0: return Underflow
   - highest = queue[0]
   - for i = 0 to size - 2: queue[i] = queue[i + 1] (Shift left)
   - size--; processedCount++; return highest
```

### 20. Deque (Double-Ended Queue - Circular Array)
```
1. isFull(): `(front == 0 and rear == MAX - 1) or (front == rear + 1)`
2. isEmpty(): `front == -1`
3. insertFront(val):
   - if isFull(): return Overflow
   - if isEmpty(): front = 0; rear = 0;
   - else if front == 0: front = MAX - 1 (Wrap)
   - else: front = front - 1
   - arr[front] = val
4. insertRear(val):
   - if isFull(): return Overflow
   - if isEmpty(): front = 0; rear = 0;
   - else if rear == MAX - 1: rear = 0 (Wrap)
   - else: rear = rear + 1
   - arr[rear] = val
5. deleteFront():
   - if isEmpty(): return Underflow
   - val = arr[front]
   - if front == rear: front = -1; rear = -1;
   - else if front == MAX - 1: front = 0 (Wrap)
   - else: front = front + 1
   - return val
```
