# Curriculum Coverage Matrix

This document provides a comprehensive mapping between the theoretical curriculum syllabus (`CE25PCC-202`), the practical laboratory curriculum (`CE25PCC-203`), the departmental alternate problem sets, and the planned source code implementations in this practical codebook.

---

## 1. Course Outcomes (CO) Mapping

| Course Outcome | Description | Core Practical Mapped | Domain Applications Mapped |
|---|---|---|---|
| **CO1** | Choose appropriate data structures by evaluating the memory requirements of a given application; perform operations such as insertion, deletion, and traversal on arrays and linked lists. | Assignments 1, 2, 3, 4 | Set 1, 2, 3, 4 (Array, Singly LL, Doubly LL, Memory Representation) |
| **CO2** | Implement suitable searching and sorting algorithms for a given problem scenario (Bubble, Selection, Insertion, Quick, Merge, Linear, Binary Search). | Assignments 5, 6, 7, 8 | Set 1, 2, 3, 4 (Sorting by metric, Searching by ID/Name, Quick Sort, Bubble/Selection) |
| **CO3** | Apply stack operations to perform expression conversion and evaluation, and to manage recursion and function call execution. | Assignments 9, 10, 11, 12 | Set 1, 2, 3, 4 (Portal History, Infix-to-Postfix Formulas, Parenthesis Match, Billing Traces) |
| **CO4** | Utilize appropriate queue structures to efficiently solve problems in CPU scheduling, task management, request handling, and resource allocation. | Assignments 13, 14, 15, 16 | Set 1, 2, 3, 4 (Token Counters, Dispatch, Bus Pass Circular, CGPA Priority, Service Deque) |

---

## 2. Unit-Wise Detailed Syllabus Coverage

### Unit I: Introduction to Data Structures and Memory Representation (8 Hours)
- **Theory Syllabus Topics:**
  - Concept of data, information, and data structures
  - Abstract Data Types (ADT) and Classification of Data Structures
  - Array: Types, operations on arrays (insertion, deletion, traversal, search, update), memory address calculation
  - Linked Lists: Types — singly, doubly, circular linked lists; memory representation, pointer manipulation
- **Implementations Provided:**
  1. `Unit_1_Arrays_Linked_Lists/arrays/01_student_information_system.cpp` (Canonical Lab Assignment 1: Insert at position, delete by roll number, search, display)
  2. `Unit_1_Arrays_Linked_Lists/singly_linked_list/02_daily_attendance_sll.cpp` (Canonical Lab Assignment 2: SLL insert at end, update given day, count Present/Absent, display)
  3. `Unit_1_Arrays_Linked_Lists/doubly_linked_list/03_sorted_students_dll.cpp` (Canonical Lab Assignment 3: Sorted insertion, delete by key, forward & backward traversal)
  4. `Unit_1_Arrays_Linked_Lists/arrays/04_ia_marks_array_vs_linkedlist.cpp` (Canonical Lab Assignment 4: Array vs SLL memory layout and threshold counting)
  5. `Unit_1_Arrays_Linked_Lists/circular_linked_list/00_circular_linked_list_operations.cpp` (Theory Foundation: Circular LL node insertion, deletion, and loop termination)
  6. `Unit_1_Arrays_Linked_Lists/applications/set1_library_array_books.cpp` (Set 1: Book records array)
  7. `Unit_1_Arrays_Linked_Lists/applications/set1_library_sll_returns_end.cpp` (Set 1: Return status SLL append & update)
  8. `Unit_1_Arrays_Linked_Lists/applications/set1_library_sll_returns_mid_delete.cpp` (Set 1: Return status SLL insert-middle & delete-front)
  9. `Unit_1_Arrays_Linked_Lists/applications/set1_library_dll_members_sorted.cpp` (Set 1: Library members sorted DLL)
  10. `Unit_1_Arrays_Linked_Lists/applications/set1_library_array_vs_ll_issued.cpp` (Set 1: Books issued Array vs LL)
  11. `Unit_1_Arrays_Linked_Lists/applications/set2_hospital_array_patients.cpp` (Set 2: Patient records array)
  12. `Unit_1_Arrays_Linked_Lists/applications/set2_hospital_sll_checkup_end.cpp` (Set 2: Checkup status SLL append & update)
  13. `Unit_1_Arrays_Linked_Lists/applications/set2_hospital_sll_checkup_mid_delete.cpp` (Set 2: Checkup status SLL insert-mid & delete-front)
  14. `Unit_1_Arrays_Linked_Lists/applications/set2_hospital_dll_doctors_sorted.cpp` (Set 2: Doctors sorted DLL)
  15. `Unit_1_Arrays_Linked_Lists/applications/set2_hospital_array_vs_ll_temperature.cpp` (Set 2: Body temperature Array vs LL)
  16. `Unit_1_Arrays_Linked_Lists/applications/set3_inventory_array_products.cpp` (Set 3: Product inventory array)
  17. `Unit_1_Arrays_Linked_Lists/applications/set3_inventory_sll_stock_end.cpp` (Set 3: Stock status SLL append & update)
  18. `Unit_1_Arrays_Linked_Lists/applications/set3_inventory_sll_stock_mid_delete.cpp` (Set 3: Stock status SLL insert-mid & delete-front)
  19. `Unit_1_Arrays_Linked_Lists/applications/set3_inventory_dll_suppliers_sorted.cpp` (Set 3: Suppliers sorted DLL)
  20. `Unit_1_Arrays_Linked_Lists/applications/set3_inventory_array_vs_ll_sales.cpp` (Set 3: Monthly sales units Array vs LL)
  21. `Unit_1_Arrays_Linked_Lists/applications/set4_bank_array_customers.cpp` (Set 4: Bank customer records array)
  22. `Unit_1_Arrays_Linked_Lists/applications/set4_bank_sll_emi_end.cpp` (Set 4: EMI status SLL append & update)
  23. `Unit_1_Arrays_Linked_Lists/applications/set4_bank_sll_emi_mid_delete.cpp` (Set 4: EMI status SLL insert-mid & delete-front)
  24. `Unit_1_Arrays_Linked_Lists/applications/set4_bank_dll_applicants_sorted.cpp` (Set 4: Loan applicants sorted DLL)
  25. `Unit_1_Arrays_Linked_Lists/applications/set4_bank_array_vs_ll_balance.cpp` (Set 4: Account balances Array vs LL)

---

### Unit II: Searching and Sorting Techniques (7 Hours)
- **Theory Syllabus Topics:**
  - Searching: Linear Search and Binary Search with step-by-step examples and comparison counters
  - Sorting Concepts: Internal vs external sorting, stable vs unstable sorting
  - Sorting Algorithms: Bubble Sort, Selection Sort, Insertion Sort, Quick Sort, Merge Sort
- **Implementations Provided:**
  1. `Unit_2_Searching_Sorting/searching/06_student_search_linear_binary.cpp` (Canonical Lab Assignment 6: Linear search by Name, Binary search by Roll No, comparison tracking)
  2. `Unit_2_Searching_Sorting/selection_sort/05_merit_list_selection_sort.cpp` (Canonical Lab Assignment 5a: Selection sort descending by CGPA, Top 5)
  3. `Unit_2_Searching_Sorting/insertion_sort/05_merit_list_insertion_sort.cpp` (Canonical Lab Assignment 5b: Insertion sort descending with element shift counter)
  4. `Unit_2_Searching_Sorting/quick_sort/07_student_percentage_quick_sort.cpp` (Canonical Lab Assignment 7: Lomuto/Hoare partition and recursive Quick Sort)
  5. `Unit_2_Searching_Sorting/bubble_sort/08_percentage_selection_bubble_sort.cpp` (Canonical Lab Assignment 8: Selection Sort ascending, Bubble Sort ascending & Top 5)
  6. `Unit_2_Searching_Sorting/merge_sort/00_merge_sort_divide_conquer.cpp` (Theory Foundation: Divide-and-conquer Merge Sort with stability)
  7. `Unit_2_Searching_Sorting/applications/set1_library_sorting_selection_insertion.cpp` (Set 1: Most-issued books ranking)
  8. `Unit_2_Searching_Sorting/applications/set1_library_searching_linear_binary.cpp` (Set 1: Book search Title linear vs ID binary)
  9. `Unit_2_Searching_Sorting/applications/set1_library_quicksort_fines.cpp` (Set 1: Library fines Quick Sort)
  10. `Unit_2_Searching_Sorting/applications/set1_library_prices_selection_bubble.cpp` (Set 1: Book prices Selection & Bubble Sort)
  11. `Unit_2_Searching_Sorting/applications/set2_hospital_sorting_selection_insertion.cpp` (Set 2: Patient severity ranking)
  12. `Unit_2_Searching_Sorting/applications/set2_hospital_searching_linear_binary.cpp` (Set 2: Patient search Name linear vs ID binary)
  13. `Unit_2_Searching_Sorting/applications/set2_hospital_quicksort_temperatures.cpp` (Set 2: Patient temperature Quick Sort)
  14. `Unit_2_Searching_Sorting/applications/set2_hospital_bills_selection_bubble.cpp` (Set 2: Patient bills Selection & Bubble Sort)
  15. `Unit_2_Searching_Sorting/applications/set3_inventory_sorting_selection_insertion.cpp` (Set 3: Product sales ranking)
  16. `Unit_2_Searching_Sorting/applications/set3_inventory_searching_linear_binary.cpp` (Set 3: Product search Name linear vs ID binary)
  17. `Unit_2_Searching_Sorting/applications/set3_inventory_quicksort_prices.cpp` (Set 3: Product unit prices Quick Sort)
  18. `Unit_2_Searching_Sorting/applications/set3_inventory_stock_selection_bubble.cpp` (Set 3: Stock quantities Selection & Bubble Sort)
  19. `Unit_2_Searching_Sorting/applications/set4_bank_sorting_selection_insertion.cpp` (Set 4: Customer balance ranking)
  20. `Unit_2_Searching_Sorting/applications/set4_bank_searching_linear_binary.cpp` (Set 4: Customer search Name linear vs Account No binary)
  21. `Unit_2_Searching_Sorting/applications/set4_bank_quicksort_interest.cpp` (Set 4: Loan interest rates Quick Sort)
  22. `Unit_2_Searching_Sorting/applications/set4_bank_transactions_selection_bubble.cpp` (Set 4: Transaction amounts Selection & Bubble Sort)

---

### Unit III: Stack and Recursion (8 Hours)
- **Theory Syllabus Topics:**
  - Definition, Stack operations (Push, Pop, Peek, isEmpty, isFull), Stack as an ADT
  - Implementation using arrays and linked lists
  - Applications: Recursion, Infix, Prefix, Postfix expression conversion, expression evaluation
  - Stack frame and function call mechanism (activation records, call stack simulation)
- **Implementations Provided:**
  1. `Unit_3_Stacks_Recursion/stack_array/00_stack_array_adt.cpp` (Theory Foundation: Array-based LIFO stack with boundary checks)
  2. `Unit_3_Stacks_Recursion/stack_linked_list/00_stack_linked_list_adt.cpp` (Theory Foundation: Linked list stack with dynamic top pointer)
  3. `Unit_3_Stacks_Recursion/stack_applications/09_browser_history_stack.cpp` (Canonical Lab Assignment 9: Student portal navigation history)
  4. `Unit_3_Stacks_Recursion/stack_applications/10_marks_infix_to_postfix_eval.cpp` (Canonical Lab Assignment 10: Infix to postfix conversion & evaluation)
  5. `Unit_3_Stacks_Recursion/stack_applications/11_parenthesis_checker_stack.cpp` (Canonical Lab Assignment 11: Expression bracket balancing)
  6. `Unit_3_Stacks_Recursion/stack_applications/12_college_billing_system_stack.cpp` (Canonical Lab Assignment 12: Fee calculation formula with intermediate stack traces)
  7. `Unit_3_Stacks_Recursion/recursion/00_recursion_call_stack_tracing.cpp` (Theory Foundation: Stack frame simulation for recursive factorial and Fibonacci)
  8. `Unit_3_Stacks_Recursion/stack_applications/set1_library_catalogue_stack.cpp` (Set 1: Library catalogue navigation stack)
  9. `Unit_3_Stacks_Recursion/stack_applications/set1_library_fine_infix_eval.cpp` (Set 1: Fine formula infix to postfix & evaluation)
  10. `Unit_3_Stacks_Recursion/stack_applications/set1_library_query_parentheses.cpp` (Set 1: Book search query parentheses checker)
  11. `Unit_3_Stacks_Recursion/stack_applications/set1_library_billing_system.cpp` (Set 1: Library fine billing system with stack traces)
  12. `Unit_3_Stacks_Recursion/stack_applications/set2_hospital_portal_stack.cpp` (Set 2: Patient portal navigation stack)
  13. `Unit_3_Stacks_Recursion/stack_applications/set2_hospital_bill_infix_eval.cpp` (Set 2: Bill formula infix to postfix & evaluation)
  14. `Unit_3_Stacks_Recursion/stack_applications/set2_hospital_dosage_parentheses.cpp` (Set 2: Medical dosage formula parentheses checker)
  15. `Unit_3_Stacks_Recursion/stack_applications/set2_hospital_billing_system.cpp` (Set 2: Hospital billing system with stack traces)
  16. `Unit_3_Stacks_Recursion/stack_applications/set3_inventory_portal_stack.cpp` (Set 3: Warehouse portal navigation stack)
  17. `Unit_3_Stacks_Recursion/stack_applications/set3_inventory_price_infix_eval.cpp` (Set 3: Price formula infix to postfix & evaluation)
  18. `Unit_3_Stacks_Recursion/stack_applications/set3_inventory_stock_parentheses.cpp` (Set 3: Stock valuation parentheses checker)
  19. `Unit_3_Stacks_Recursion/stack_applications/set3_inventory_billing_system.cpp` (Set 3: Purchase billing system with stack traces)
  20. `Unit_3_Stacks_Recursion/stack_applications/set4_bank_portal_stack.cpp` (Set 4: Internet banking navigation stack)
  21. `Unit_3_Stacks_Recursion/stack_applications/set4_bank_interest_infix_eval.cpp` (Set 4: Interest formula infix to postfix & evaluation)
  22. `Unit_3_Stacks_Recursion/stack_applications/set4_bank_loan_parentheses.cpp` (Set 4: Loan eligibility parentheses checker)
  23. `Unit_3_Stacks_Recursion/stack_applications/set4_bank_billing_system.cpp` (Set 4: Loan billing system with stack traces)

---

### Unit IV: Queue (7 Hours)
- **Theory Syllabus Topics:**
  - Definition, Queue operations (Enqueue, Dequeue, Peek, isEmpty, isFull)
  - Implementation using arrays and linked lists
  - Variations: Circular Queue, Double-Ended Queue (Deque), Priority Queue
  - Applications in system design: CPU scheduling, print queue, buffer management
- **Implementations Provided:**
  1. `Unit_4_Queues/queue_array/00_queue_array_adt.cpp` (Theory Foundation: Linear array queue)
  2. `Unit_4_Queues/queue_linked_list/00_queue_linked_list_adt.cpp` (Theory Foundation: Linked list queue with front/rear pointers)
  3. `Unit_4_Queues/queue_array/13_admission_queue_linear.cpp` (Canonical Lab Assignment 13: Student admission token queue)
  4. `Unit_4_Queues/circular_queue/14_bus_pass_circular_queue.cpp` (Canonical Lab Assignment 14: Bus pass distribution circular queue)
  5. `Unit_4_Queues/priority_queue/15_cgpa_priority_queue.cpp` (Canonical Lab Assignment 15: CGPA priority queue)
  6. `Unit_4_Queues/deque/16_student_service_desk_deque.cpp` (Canonical Lab Assignment 16: Service desk deque with emergency front and normal rear)
  7. `Unit_4_Queues/applications/00_cpu_scheduling_print_queue.cpp` (Theory Foundation: Round-robin CPU scheduler & print queue)
  8. `Unit_4_Queues/applications/set1_library_issue_counter_queue.cpp` (Set 1: Book issue counter queue)
  9. `Unit_4_Queues/applications/set2_hospital_opd_queue.cpp` (Set 2: OPD queue)
  10. `Unit_4_Queues/applications/set3_inventory_dispatch_queue.cpp` (Set 3: Goods dispatch queue)
  11. `Unit_4_Queues/applications/set4_bank_teller_queue.cpp` (Set 4: Bank teller counter queue)

---

## 3. Coverage Completeness Summary
- **Curriculum Assignments (Group A, B, C, D):** 16 of 16 (100% coverage).
- **Theory Foundation Topics:** 8 of 8 (100% coverage: Circular Linked List, Merge Sort, Linked Stack, Linked Queue, Recursion Trace, Round-Robin/Print Queue).
- **Alternate Domain Sets (Sets 1–4 across all units):** All 36 problem statements mapped and implemented (100% coverage).
- **Language Alignment:** 100% Modern Educational C++ with zero non-standard libraries and zero hidden standard containers.
