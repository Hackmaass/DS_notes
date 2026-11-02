# Practical Question Inventory

This inventory catalogs every practical question from the official Data Structures curriculum and the departmental question banks. Original numbering and wording are strictly preserved.

---

## Part 1: Official Curriculum Laboratory Assignments (CE25PCC-203)
*Source: `Syllabus/Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf` (Pages 18–20)*

### Group A: Arrays and Linked Lists

#### Assignment 1
- **Original Wording:**  
  Write a program for the Student Information System which stores details of N students (Roll No, Name, CGPA). Write functions for the following:  
  a. Insert a new student at a given position  
  b. Delete a student by roll number  
  c. Search a student by roll number and display the record  
  d. Display all students stored in the array  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 18  
- **Relevant Unit:** Unit I (Arrays and Linked Lists)  
- **Required Data Structure:** Array of Structs / Classes  
- **Required Operations:** Position-based insertion, key-based deletion, linear/key search, array traversal  
- **Planned Source File:** `Unit_1_Arrays_Linked_Lists/arrays/01_student_information_system.cpp`

#### Assignment 2
- **Original Wording:**  
  Create a program to maintain daily attendance of students using a singly linked list. Write functions to:  
  a. Insert attendance (P/A) at the end of the list  
  b. Update the attendance of a given day  
  c. Calculate total number of Present and Absent days  
  d. Display the complete attendance list  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 18  
- **Relevant Unit:** Unit I (Arrays and Linked Lists)  
- **Required Data Structure:** Singly Linked List  
- **Required Operations:** Append (insert at end), node data update by day index, conditional count traversal, full list display  
- **Planned Source File:** `Unit_1_Arrays_Linked_Lists/singly_linked_list/02_daily_attendance_sll.cpp`

#### Assignment 3
- **Original Wording:**  
  Write a program to maintain a list of students sorted by roll number using a doubly linked list. Implement functions to:  
  a. Insert a student so that the list remains sorted  
  b. Delete a student by roll number  
  c. Traverse the list forward to display all students  
  d. Traverse backward to display all students in reverse order  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 18  
- **Relevant Unit:** Unit I (Arrays and Linked Lists)  
- **Required Data Structure:** Doubly Linked List (sorted)  
- **Required Operations:** Sorted insertion (maintaining ascending roll number order), key deletion by roll number, forward traversal via `next`, backward traversal via `prev`  
- **Planned Source File:** `Unit_1_Arrays_Linked_Lists/doubly_linked_list/03_sorted_students_dll.cpp`

#### Assignment 4
- **Original Wording:**  
  Write a program that stores Internal Assessment (IA) marks of N students using both array and linked list. Implement:  
  a. Insert student marks in both structures  
  b. Display memory representation/index nodes  
  c. Count how many students scored more than 80 marks  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 18  
- **Relevant Unit:** Unit I (Arrays and Linked Lists)  
- **Required Data Structure:** Static Array alongside Singly Linked List  
- **Required Operations:** Dual insertion, memory layout inspection (printing array index with contiguous memory address vs linked list node pointer addresses), conditional threshold counting (> 80)  
- **Planned Source File:** `Unit_1_Arrays_Linked_Lists/arrays/04_ia_marks_array_vs_linkedlist.cpp`

---

### Group B: Searching and Sorting

#### Assignment 5
- **Original Wording:**  
  Write a program for preparing a merit list of students based on CGPA. Implement:  
  a. Selection sort for descending CGPA  
  b. Insertion sort and count number of shifts  
  c. Display the top 5 students  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 18  
- **Relevant Unit:** Unit II (Searching and Sorting Techniques)  
- **Required Data Structure:** Array of Student Records  
- **Required Operations:** Selection Sort (descending by finding maximum), Insertion Sort (descending with element shift tracking), Top-5 extraction  
- **Planned Source File:** `Unit_2_Searching_Sorting/selection_sort/05_merit_list_selection_sort.cpp` (and companion `Unit_2_Searching_Sorting/insertion_sort/05_merit_list_insertion_sort.cpp`)

#### Assignment 6
- **Original Wording:**  
  Write a program for an academic office to search a student record (Roll No, Name, Division). Implement:  
  a. Linear search by Name  
  b. Binary search by Roll Number (use sorting)  
  c. Display number of comparisons for each search  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Pages 18–19  
- **Relevant Unit:** Unit II (Searching and Sorting Techniques)  
- **Required Data Structure:** Array of Records  
- **Required Operations:** Linear search (sequential match with comparison tally), pre-search sorting (by roll number), binary search (`low`, `high`, `mid` with comparison tally), performance comparison  
- **Planned Source File:** `Unit_2_Searching_Sorting/searching/06_student_search_linear_binary.cpp`

#### Assignment 7
- **Original Wording:**  
  Write a program to arrange student percentages using Quick Sort. Implement:  
  a. Partition the list  
  b. Recursively apply Quick Sort  
  c. Display the sorted percentage list  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 19  
- **Relevant Unit:** Unit II (Searching and Sorting Techniques)  
- **Required Data Structure:** Floating-Point Array  
- **Required Operations:** Lomuto / Hoare partition mechanism, recursive divide-and-conquer calls, intermediate pivot placement display, final sorted array display  
- **Planned Source File:** `Unit_2_Searching_Sorting/quick_sort/07_student_percentage_quick_sort.cpp`

#### Assignment 8
- **Original Wording:**  
  Write a program to store the percentage of students in an array. Write function for sorting array of floating-point numbers in ascending order using:  
  a. Selection Sort  
  b. Bubble sort and display top five scores.  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 19  
- **Relevant Unit:** Unit II (Searching and Sorting Techniques)  
- **Required Data Structure:** Floating-Point Array  
- **Required Operations:** Selection Sort (ascending order), Bubble Sort (ascending adjacent comparisons with early stop), extraction and display of top five scores  
- **Planned Source File:** `Unit_2_Searching_Sorting/bubble_sort/08_percentage_selection_bubble_sort.cpp`

---

### Group C: Stack and Recursion / Expression Processing

#### Assignment 9
- **Original Wording:**  
  Write a program to simulate the browser history of a student portal using a stack. Implement functions to:  
  a. Visit a new page (push URL)  
  b. Go back to the previous page (pop URL)  
  c. Display the current page  
  d. Show the entire browsing history stack  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 19  
- **Relevant Unit:** Unit III (Stack)  
- **Required Data Structure:** Stack (Array-based / Linked List-based)  
- **Required Operations:** Push (visit), Pop (back button), Peek (current page), Stack display without destroying stack state  
- **Planned Source File:** `Unit_3_Stacks_Recursion/stack_applications/09_browser_history_stack.cpp`

#### Assignment 10
- **Original Wording:**  
  Given a marks calculation formula (infix), write a program to:  
  a. Convert infix expression to postfix  
  b. Evaluate postfix expression for given inputs  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 19  
- **Relevant Unit:** Unit III (Stack)  
- **Required Data Structure:** Operator Stack (Character) and Operand Stack (Numeric)  
- **Required Operations:** Shunting-yard infix to postfix conversion (precedence, associativity, parentheses handling), postfix stack evaluation given operand values  
- **Planned Source File:** `Unit_3_Stacks_Recursion/stack_applications/10_marks_infix_to_postfix_eval.cpp`

#### Assignment 11
- **Original Wording:**  
  Write a Program for Parenthesis checking in an expression using stack.  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 19  
- **Relevant Unit:** Unit III (Stack)  
- **Required Data Structure:** Character Stack  
- **Required Operations:** Opening bracket push, closing bracket pop and match verification for `()`, `{}`, `[]`, stack-empty verification upon string end  
- **Planned Source File:** `Unit_3_Stacks_Recursion/stack_applications/11_parenthesis_checker_stack.cpp`

#### Assignment 12
- **Original Wording:**  
  Write a program for the College Billing System to compute the final payable fees of a student.  
  The administrator enters the fee calculation formula in infix form, for example:  
  a. Read the fee formula in infix form as entered by the administrator.  
  b. Convert the infix expression into postfix using a stack.  
  c. Display the postfix expression after conversion.  
  d. Accept values for Tuition, Hostel, ExamFee, and Scholarship from the user.  
  e. Evaluate the postfix expression using a stack.  
  f. Display the final payable fees for the student.  
  g. Also display intermediate stack contents during postfix conversion and evaluation.  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 19  
- **Relevant Unit:** Unit III (Stack)  
- **Required Data Structure:** Stack with explicit step-by-step state printing  
- **Required Operations:** Variable-name tokenization, infix-to-postfix conversion showing intermediate stack at each token, token substitution with accepted numerical values, postfix evaluation showing operand stack at each step, final result computation  
- **Planned Source File:** `Unit_3_Stacks_Recursion/stack_applications/12_college_billing_system_stack.cpp`

---

### Group D: Queues

#### Assignment 13
- **Original Wording:**  
  Write a program to simulate the admission queue of students.  
  a. Enqueue student token number  
  b. Dequeue and display student processes  
  c. Display front and rear token number  
  d. Display complete queue  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 19  
- **Relevant Unit:** Unit IV (Queue)  
- **Required Data Structure:** Linear Queue using Array  
- **Required Operations:** `enqueue()`, `dequeue()`, peek front/rear, queue empty/full checks, sequential queue traversal  
- **Planned Source File:** `Unit_4_Queues/queue_array/13_admission_queue_linear.cpp`

#### Assignment 14
- **Original Wording:**  
  Write a program using circular queue for bus pass distribution.  
  a. Insert student IDs in circular queue  
  b. Delete student ID as pass is issued  
  c. Detect queue full/empty conditions  
  d. Display the circular queue  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 20  
- **Relevant Unit:** Unit IV (Queue)  
- **Required Data Structure:** Circular Queue using fixed-size array  
- **Required Operations:** Circular increment via modulo `(rear + 1) % MAX`, circular decrement/dequeue via `(front + 1) % MAX`, full condition `(rear + 1) % MAX == front`, circular traversal display  
- **Planned Source File:** `Unit_4_Queues/circular_queue/14_bus_pass_circular_queue.cpp`

#### Assignment 15
- **Original Wording:**  
  Write a program using priority queue where priority = higher CGPA.  
  a. Insert student with CGPA  
  b. Delete the highest CGPA student  
  c. Display queue after each operation  
  d. Count students processed  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 20  
- **Relevant Unit:** Unit IV (Queue)  
- **Required Data Structure:** Ascending/Descending Ordered Priority Queue using Array / Linked Structure  
- **Required Operations:** Priority-ordered insertion (or max search on dequeue), highest-priority deletion, live status display after each step, processed record counter  
- **Planned Source File:** `Unit_4_Queues/priority_queue/15_cgpa_priority_queue.cpp`

#### Assignment 16
- **Original Wording:**  
  Student Service Desk Using Deque: Write a program using deque for student service requests.  
  a. Add emergency cases at front  
  b. Add normal cases at rear  
  c. Serve from front  
  d. Display deque after each operation  
- **Source File:** `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf`  
- **Source Page:** Page 20  
- **Relevant Unit:** Unit IV (Queue)  
- **Required Data Structure:** Double-Ended Queue (Deque)  
- **Required Operations:** `insertFront()` (emergency cases), `insertRear()` (normal cases), `deleteFront()` (service point), deque state display after every mutation  
- **Planned Source File:** `Unit_4_Queues/deque/16_student_service_desk_deque.cpp`

---

## Part 2: Departmental Alternate Problem Sets (Batched Question Bank)

### Source: `Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx`

#### Set 1: Library Management System
- **Part A - Problem 1 (Array):** Maintain records of N books (Book ID, Title, Price). Functions: a. Insert at position, b. Delete by Book ID, c. Search by Book ID and display, d. Display all books.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set1_library_array_books.cpp`
- **Part A - Problem 2 (SLL):** Daily return status of issued books (R/N). Functions: a. Insert at end, b. Update given day, c. Calculate total returned, d. Display complete list.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set1_library_sll_returns_end.cpp`
- **Part A - Problem 3 (SLL):** Same return status list. Functions: a. Insert in middle, b. Delete from front, c. Calculate total not returned, d. Display complete list.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set1_library_sll_returns_mid_delete.cpp`
- **Part A - Problem 4 (DLL):** Library members sorted by Member ID. Functions: a. Sorted insert, b. Delete by Member ID, c. Forward traversal, d. Backward traversal.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set1_library_dll_members_sorted.cpp`
- **Part A - Problem 5 (Array vs LL):** Books issued by N members. Functions: a. Insert count in both, b. Display memory representation (index & nodes), c. Count members issuing > 5 books.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set1_library_array_vs_ll_issued.cpp`
- **Part B - Problem 1 (Stack):** Navigation history of online library catalogue (visit URL, back URL, current page, full history).  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set1_library_catalogue_stack.cpp`
- **Part B - Problem 2 (Stack):** Late-fine calculation formula `(Days * Rate) + Fixed - Waiver` (infix to postfix, evaluate).  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set1_library_fine_infix_eval.cpp`
- **Part B - Problem 3 (Stack):** Balanced parentheses in book-search query expression.  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set1_library_query_parentheses.cpp`
- **Part B - Problem 4 (Stack):** Library Fine Billing System (formula, postfix, accept LateDays, DailyRate, DamageCharge, Waiver, evaluate, intermediate stack contents).  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set1_library_billing_system.cpp`
- **Part B - Problem 5 (Queue):** Book issue counter queue (enqueue token, dequeue served, display front/rear, display complete queue).  
  *Planned File:* `Unit_4_Queues/applications/set1_library_issue_counter_queue.cpp`

#### Set 2: Hospital Management System
- **Part A - Problem 1 (Array):** Records of N patients (Patient ID, Name, Age). Functions: insert at position, delete by ID, search by ID, display all.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set2_hospital_array_patients.cpp`
- **Part A - Problem 2 (SLL):** Daily check-up status (C=Completed/M=Missed). Insert at end, update given day, count completed check-ups, display complete list.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set2_hospital_sll_checkup_end.cpp`
- **Part A - Problem 3 (SLL):** Same list. Insert in middle, delete from front, count missed check-ups, display complete list.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set2_hospital_sll_checkup_mid_delete.cpp`
- **Part A - Problem 4 (DLL):** Doctors sorted by Doctor ID. Sorted insert, delete by Doctor ID, traverse forward, traverse backward.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set2_hospital_dll_doctors_sorted.cpp`
- **Part A - Problem 5 (Array vs LL):** Patient body temperature readings. Insert in both, display memory representation, count patients with temp > 100°F.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set2_hospital_array_vs_ll_temperature.cpp`
- **Part B - Problem 1 (Stack):** Hospital patient portal navigation history (push, pop, current, full history).  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set2_hospital_portal_stack.cpp`
- **Part B - Problem 2 (Stack):** Bill formula `(Consultation + Medicine) * Days - Insurance` (infix to postfix, evaluate).  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set2_hospital_bill_infix_eval.cpp`
- **Part B - Problem 3 (Stack):** Balanced parentheses in medical dosage formula.  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set2_hospital_dosage_parentheses.cpp`
- **Part B - Problem 4 (Stack):** Hospital Billing System (accept Consultation, RoomCharge, Medicine, Insurance, evaluate, show intermediate stack).  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set2_hospital_billing_system.cpp`
- **Part B - Problem 5 (Queue):** OPD queue (enqueue token, dequeue called patient, display front/rear, display complete queue).  
  *Planned File:* `Unit_4_Queues/applications/set2_hospital_opd_queue.cpp`

#### Set 3: Inventory and Warehouse System
- **Part A - Problem 1 (Array):** N products (Product ID, Name, Quantity). Insert at position, delete by ID, search by ID, display all.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set3_inventory_array_products.cpp`
- **Part A - Problem 2 (SLL):** Daily stock status (A=Available/O=Out of stock). Insert at end, update given day, count available days, display complete list.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set3_inventory_sll_stock_end.cpp`
- **Part A - Problem 3 (SLL):** Same list. Insert in middle, delete from front, count out-of-stock days, display complete list.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set3_inventory_sll_stock_mid_delete.cpp`
- **Part A - Problem 4 (DLL):** Suppliers sorted by Supplier ID. Sorted insert, delete by ID, traverse forward, traverse backward.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set3_inventory_dll_suppliers_sorted.cpp`
- **Part A - Problem 5 (Array vs LL):** Monthly sales units of N products. Insert in both, display memory representation, count products sold > 500 units.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set3_inventory_array_vs_ll_sales.cpp`
- **Part B - Problem 1 (Stack):** Warehouse management portal navigation history (push, pop, current, full history).  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set3_inventory_portal_stack.cpp`
- **Part B - Problem 2 (Stack):** Price formula `(Cost * Qty) + Shipping - Discount` (infix to postfix, evaluate).  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set3_inventory_price_infix_eval.cpp`
- **Part B - Problem 3 (Stack):** Balanced parentheses in stock-valuation expression.  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set3_inventory_stock_parentheses.cpp`
- **Part B - Problem 4 (Stack):** Purchase Billing System (accept UnitCost, Quantity, Shipping, Discount, evaluate, show intermediate stack).  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set3_inventory_billing_system.cpp`
- **Part B - Problem 5 (Queue):** Goods dispatch queue (enqueue order number, dequeue dispatched, display front/rear, display complete queue).  
  *Planned File:* `Unit_4_Queues/applications/set3_inventory_dispatch_queue.cpp`

#### Set 4: Bank Management System
- **Part A - Problem 1 (Array):** N customers (Account No, Name, Balance). Insert at position, delete by Account No, search by Account No, display all.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set4_bank_array_customers.cpp`
- **Part A - Problem 2 (SLL):** Daily EMI payment status (P=Paid/D=Due). Insert at end, update given day, count paid EMIs, display complete list.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set4_bank_sll_emi_end.cpp`
- **Part A - Problem 3 (SLL):** Same list. Insert in middle, delete from front, count due EMIs, display complete list.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set4_bank_sll_emi_mid_delete.cpp`
- **Part A - Problem 4 (DLL):** Loan applicants sorted by Application No. Sorted insert, delete by Application No, traverse forward, traverse backward.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set4_bank_dll_applicants_sorted.cpp`
- **Part A - Problem 5 (Array vs LL):** Account balances of N customers. Insert in both, display memory representation, count customers with balance > ₹50,000.  
  *Planned File:* `Unit_1_Arrays_Linked_Lists/applications/set4_bank_array_vs_ll_balance.cpp`
- **Part B - Problem 1 (Stack):** Internet banking portal navigation history (push, pop, current, full history).  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set4_bank_portal_stack.cpp`
- **Part B - Problem 2 (Stack):** Interest formula `(Principal * Rate * Time) / 100` (infix to postfix, evaluate).  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set4_bank_interest_infix_eval.cpp`
- **Part B - Problem 3 (Stack):** Balanced parentheses in loan-eligibility expression.  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set4_bank_loan_parentheses.cpp`
- **Part B - Problem 4 (Stack):** Loan Billing System (accept Principal, Interest, ProcessingFee, Rebate, evaluate, show intermediate stack).  
  *Planned File:* `Unit_3_Stacks_Recursion/stack_applications/set4_bank_billing_system.cpp`
- **Part B - Problem 5 (Queue):** Teller counter queue (enqueue token, dequeue served, display front/rear, display complete queue).  
  *Planned File:* `Unit_4_Queues/applications/set4_bank_teller_queue.cpp`

---

### Source: `Four Alternate Problem Sets Sorting and Searching.docx`

#### Set 1: Library Management System (Searching & Sorting)
- **Problem 1 (Sorting):** Ranked list of most-issued books by issue count. a. Selection sort descending, b. Insertion sort with shift count, c. Display top 5.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set1_library_sorting_selection_insertion.cpp`
- **Problem 2 (Searching):** Search book record (Book ID, Title, Author). a. Linear search by Title, b. Binary search by Book ID (sort first), c. Display comparison counts.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set1_library_searching_linear_binary.cpp`
- **Problem 3 (Quick Sort):** Arrange fine amounts collected using Quick Sort. a. Partition list, b. Recursive Quick Sort, c. Display sorted fines.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set1_library_quicksort_fines.cpp`
- **Problem 4 (Selection & Bubble):** Store book prices in floating-point array. a. Selection sort ascending, b. Bubble sort ascending and display top 5 highest prices.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set1_library_prices_selection_bubble.cpp`

#### Set 2: Hospital Management System (Searching & Sorting)
- **Problem 1 (Sorting):** Priority list of patients based on severity score. a. Selection sort descending, b. Insertion sort with shift count, c. Display top 5 critical patients.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set2_hospital_sorting_selection_insertion.cpp`
- **Problem 2 (Searching):** Search patient record (Patient ID, Name, Ward). a. Linear search by Name, b. Binary search by Patient ID (sort first), c. Display comparison counts.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set2_hospital_searching_linear_binary.cpp`
- **Problem 3 (Quick Sort):** Arrange patient body temperature readings using Quick Sort. a. Partition, b. Recursive Quick Sort, c. Display sorted temperatures.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set2_hospital_quicksort_temperatures.cpp`
- **Problem 4 (Selection & Bubble):** Store patient bills in floating-point array. a. Selection sort ascending, b. Bubble sort ascending and display top 5 highest bills.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set2_hospital_bills_selection_bubble.cpp`

#### Set 3: Inventory and Warehouse System (Searching & Sorting)
- **Problem 1 (Sorting):** Best-seller list of products by monthly sales units. a. Selection sort descending, b. Insertion sort with shift count, c. Display top 5 best-sellers.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set3_inventory_sorting_selection_insertion.cpp`
- **Problem 2 (Searching):** Search product record (Product ID, Name, Category). a. Linear search by Name, b. Binary search by Product ID (sort first), c. Display comparison counts.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set3_inventory_searching_linear_binary.cpp`
- **Problem 3 (Quick Sort):** Arrange unit prices of products using Quick Sort. a. Partition, b. Recursive Quick Sort, c. Display sorted prices.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set3_inventory_quicksort_prices.cpp`
- **Problem 4 (Selection & Bubble):** Store stock quantities in floating-point array. a. Selection sort ascending, b. Bubble sort ascending and display top 5 highest stock quantities.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set3_inventory_stock_selection_bubble.cpp`

#### Set 4: Bank Management System (Searching & Sorting)
- **Problem 1 (Sorting):** Ranked list of customers by account balance. a. Selection sort descending, b. Insertion sort with shift count, c. Display top 5 customers.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set4_bank_sorting_selection_insertion.cpp`
- **Problem 2 (Searching):** Search customer record (Account No, Name, Branch). a. Linear search by Name, b. Binary search by Account No (sort first), c. Display comparison counts.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set4_bank_searching_linear_binary.cpp`
- **Problem 3 (Quick Sort):** Arrange customer loan interest rates using Quick Sort. a. Partition, b. Recursive Quick Sort, c. Display sorted interest rates.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set4_bank_quicksort_interest.cpp`
- **Problem 4 (Selection & Bubble):** Store transaction amounts in floating-point array. a. Selection sort ascending, b. Bubble sort ascending and display top 5 highest transactions.  
  *Planned File:* `Unit_2_Searching_Sorting/applications/set4_bank_transactions_selection_bubble.cpp`

---

## Part 3: Mandatory Theory Syllabus Practical Foundations
*Source: `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf` (Pages 15–16)*

To ensure 100% complete syllabus coverage as required by Section 4:
1. **Circular Linked List:** Creation, insertion (front, end), deletion (front, end), circular traversal without infinite loops.  
   *Planned File:* `Unit_1_Arrays_Linked_Lists/circular_linked_list/00_circular_linked_list_operations.cpp`
2. **Merge Sort:** Divide-and-conquer splitting, recursive sort, two-way merging, time complexity O(N log N).  
   *Planned File:* `Unit_2_Searching_Sorting/merge_sort/00_merge_sort_divide_conquer.cpp`
3. **Stack using Array (Foundational ADT):** Push, pop, peek, isFull, isEmpty, overflow/underflow handling.  
   *Planned File:* `Unit_3_Stacks_Recursion/stack_array/00_stack_array_adt.cpp`
4. **Stack using Linked List (Foundational ADT):** Dynamic memory, top pointer, push, pop, peek, memory deallocation.  
   *Planned File:* `Unit_3_Stacks_Recursion/stack_linked_list/00_stack_linked_list_adt.cpp`
5. **Recursion & Call Stack Tracing:** Activation records, call stack simulation, stack frames, base cases, factorial and Fibonacci execution trace.  
   *Planned File:* `Unit_3_Stacks_Recursion/recursion/00_recursion_call_stack_tracing.cpp`
6. **Queue using Array (Foundational Linear ADT):** FIFO, front, rear, enqueue, dequeue, linear boundary conditions.  
   *Planned File:* `Unit_4_Queues/queue_array/00_queue_array_adt.cpp`
7. **Queue using Linked List (Foundational ADT):** Front and rear pointers, dynamic memory, enqueue at rear, dequeue from front.  
   *Planned File:* `Unit_4_Queues/queue_linked_list/00_queue_linked_list_adt.cpp`
8. **System Queue Application (CPU Scheduling / Print Queue):** Round-robin time-quantum simulation and sequential print spooler queue.  
   *Planned File:* `Unit_4_Queues/applications/00_cpu_scheduling_print_queue.cpp`
