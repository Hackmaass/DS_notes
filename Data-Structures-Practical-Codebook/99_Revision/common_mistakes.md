# Common Student Mistakes & Exam Pitfalls Catalog

A curated guide to the most frequent errors made by undergraduate students during Data Structures lab practical exams, compiled with precise code corrections.

---

## 1. Array Operations

### Mistake 1.1: Off-by-One in Shifting During Insertion
- **Wrong:**
  ```cpp
  for (int i = size - 1; i >= pos; i--) arr[i] = arr[i - 1]; // Overwrites and misses last index!
  ```
- **Correction:**
  ```cpp
  // Make space by shifting from 'size' down to 'pos'
  for (int i = size; i >= pos; --i) {
      arr[i] = arr[i - 1];
  }
  arr[pos - 1] = newItem;
  size++;
  ```

### Mistake 1.2: Off-by-One in Shifting During Deletion
- **Wrong:**
  ```cpp
  for (int i = targetIdx; i < size; i++) arr[i] = arr[i + 1]; // Accesses arr[size], which is garbage or out-of-bounds!
  ```
- **Correction:**
  ```cpp
  for (int i = targetIdx; i < size - 1; ++i) {
      arr[i] = arr[i + 1];
  }
  size--;
  ```

---

## 2. Linked Lists

### Mistake 2.1: Losing the Rest of the List During SLL Insertion
- **Wrong:**
  ```cpp
  temp->next = newNode;
  newNode->next = temp->next; // BUG: Points back to newNode itself, creating an infinite loop and dropping the rest of the list!
  ```
- **Correction:**
  ```cpp
  newNode->next = temp->next; // 1. Save connection to the subsequent node FIRST!
  temp->next = newNode;       // 2. Safely re-point predecessor to newNode
  ```

### Mistake 2.2: Memory Leaks (Forgetting `delete`)
- **Wrong:**
  ```cpp
  head = head->next; // Orphaned former head node remains allocated on the heap indefinitely!
  ```
- **Correction:**
  ```cpp
  Node* temp = head;
  head = head->next;
  delete temp; // Reclaim heap memory
  ```

### Mistake 2.3: Incomplete Pointer Update in DLL
- **Wrong:** Only updating `next` and forgetting `prev`.
- **Correction:**
  ```cpp
  newNode->next = curr->next;
  newNode->prev = curr;
  if (curr->next != nullptr) {
      curr->next->prev = newNode;
  }
  curr->next = newNode;
  ```

### Mistake 2.4: Infinite Loop in Circular Linked List Traversal
- **Wrong:** `while (temp != nullptr)` — in CLL, `next` never equals `nullptr`!
- **Correction:**
  ```cpp
  Node* temp = head;
  if (head != nullptr) {
      do {
          cout << temp->data << " ";
          temp = temp->next;
      } while (temp != head);
  }
  ```

---

## 3. Searching & Sorting

### Mistake 3.1: Binary Search Integer Overflow
- **Wrong:** `int mid = (low + high) / 2;` (Overlows if `low + high > INT_MAX`)
- **Correction:** `int mid = low + (high - low) / 2;`

### Mistake 3.2: Forgetting to Reset Swapped Flag in Bubble Sort
- If `swapped = false;` is placed outside the outer loop, early exit optimization never triggers correctly.
- **Correction:** Place `bool swapped = false;` at the beginning of each outer loop iteration.

### Mistake 3.3: Inverted Operands in Quick Sort Partition
- In Lomuto partition, `i` must start at `low - 1`. Advancing `i` before swapping:
  ```cpp
  int i = low - 1;
  for (int j = low; j < high; ++j) {
      if (arr[j] <= pivot) {
          i++;
          swap(arr[i], arr[j]);
      }
  }
  swap(arr[i + 1], arr[high]);
  return i + 1;
  ```

---

## 4. Stacks

### Mistake 4.1: Operand Order Inversion in Postfix Evaluation
- **Fatal Error:**
  ```cpp
  float op1 = s.pop();
  float op2 = s.pop();
  float res = op1 - op2; // WRONG! Evaluates (op2 - op1) backwards!
  ```
- **Explanation:** In a stack, the FIRST popped element is the SECOND operand.
- **Correction:**
  ```cpp
  float op2 = s.pop(); // Right operand
  float op1 = s.pop(); // Left operand
  float res = op1 - op2;
  ```

### Mistake 4.2: Missing Final Unclosed Bracket Check in Parentheses
- **Wrong:** Checking only if mismatch occurs during scan, but forgetting `return s.isEmpty();`.
- **Symptom:** String `((()` reported as balanced!

---

## 5. Queues

### Mistake 5.1: Circular Queue Full Condition Misconception
- **Wrong:** Writing `rear == MAX - 1` (that's linear queue full condition!).
- **Correction:** `(rear + 1) % MAX == front`

### Mistake 5.2: Forgetting to Reset on Empty
- When deleting the last element (`front == rear`):
  ```cpp
  if (front == rear) {
      front = -1;
      rear = -1; // MUST reset both to -1!
  } else {
      front = (front + 1) % MAX;
  }
  ```

### Mistake 5.3: Circular Deque Front Decrement Bug
- When `front == 0`, decrementing requires wrap-around to `MAX - 1`:
  ```cpp
  if (front == 0) front = MAX - 1;
  else front = front - 1;
  ```
  Writing `front--` accesses `arr[-1]`, corrupting memory and causing segmentation faults!
