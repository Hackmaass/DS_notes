# 🧠 Data Structures Fundamentals (The 8 Core Primitives)

Welcome to the **Fundamentals** folder!

Every complex exam problem statement—whether it's about **Students, Library Books, Hospital Patients, Warehouse Inventory, or Bank Customers**—is just one of these 8 core building blocks in disguise.

If you study and understand these 8 short programs (each is only 40–80 lines of clean C++), you will be able to approach and write **any** problem statement with confidence!

---

## 🗺️ Master Curriculum Mapping

| Unit | Fundamental File | The Core Concept | What College Problems Use This? |
|:---:|:---|:---|:---|
| **Unit 1** | [`01_array_shift_insert_delete.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Fundamentals/01_array_shift_insert_delete.cpp) | **Array Shifting**: Shift right (insert) & shift left (delete) | Student Records, Book Records, Patient Records, Product Inventory, Customer Accounts |
| **Unit 1** | [`02_singly_linked_list_basics.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Fundamentals/02_singly_linked_list_basics.cpp) | **Singly Linked List**: Node creation, `curr = curr->next`, delete by value | Daily Attendance SLL, Book Returns, Checkup Queue, Stock Inward, Loan EMI |
| **Unit 1** | [`03_doubly_linked_list_basics.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Fundamentals/03_doubly_linked_list_basics.cpp) | **Doubly Linked List**: Two-way pointers (`next` & `prev`), forward/backward traversal | Sorted Students DLL, Library Members DLL, Doctors DLL, Suppliers DLL, Loan Applicants DLL |
| **Unit 2** | [`04_linear_vs_binary_search.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Fundamentals/04_linear_vs_binary_search.cpp) | **Searching**: Linear search $O(N)$ vs Binary search $O(\log N)$ | Search student by Roll, Search book by ID, Search patient by ID, Search account by AccNo |
| **Unit 2** | [`05_selection_and_insertion_sort.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Fundamentals/05_selection_and_insertion_sort.cpp) | **Basic Sorting**: Selection Sort (find min, 1 swap) & Insertion Sort (card-game shift) | CGPA Merit List, Most-Issued Books, Patient Severity Ranking, Product Best-Sellers, Balance Ranking |
| **Unit 2** | [`06_quick_sort_partition.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Fundamentals/06_quick_sort_partition.cpp) | **Divide & Conquer**: Lomuto partition around pivot, recursive sorting | Student Percentages, Library Fines, Patient Temperatures, Product Prices, Loan Interest Rates |
| **Unit 3** | [`07_stack_lifo_and_parentheses.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Fundamentals/07_stack_lifo_and_parentheses.cpp) | **Stack LIFO**: `top++`, `top--`, and delimiter matching `()`, `{}`, `[]` | Browser History, Portal Navigation, Expression Parentheses Checking, Infix to Postfix |
| **Unit 4** | [`08_circular_queue_fifo.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Fundamentals/08_circular_queue_fifo.cpp) | **Queue FIFO**: Modulo arithmetic `(rear+1)%MAX` and `(front+1)%MAX` | Admission Queue, Bus Pass Queue, Book Counter Queue, OPD Queue, Dispatch Bay, Teller Counter |

---

## ⚡ How to Compile & Run Any Fundamental

Every program is completely self-contained with no special dependencies:

```bash
# Example: Run Fundamental 1
g++ -std=c++14 -Wall -Wextra 01_array_shift_insert_delete.cpp -o app
./app
```
