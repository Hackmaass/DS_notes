# Departmental Problem Sets Codebook (56 Standalone Programs)

This folder contains **all 56 standalone, educational C++ programs** corresponding directly to the official departmental problem statements from:
1. `Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx`
2. `Four Alternate Problem Sets Sorting and Searching.docx`

Each program is **100% self-contained**, beginner-friendly (80–150 lines), contains **zero STL abstractions** (everything is implemented from scratch using basic arrays, pointers, and structures), and compiles with `0 errors and 0 warnings` under `g++ -std=c++14 -Wall -Wextra`.

---

## Complete Quick Reference Map

| Set | Domain | Total Programs | Subfolder |
|:---:|:---|:---:|:---|
| **Set 1** | **Library Management System** | 14 | [Set1_Library/](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library) |
| **Set 2** | **Hospital Management System** | 14 | [Set2_Hospital/](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital) |
| **Set 3** | **Inventory Management System** | 14 | [Set3_Inventory/](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory) |
| **Set 4** | **Banking Management System** | 14 | [Set4_Bank/](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank) |

---

## Detailed Problem-by-Problem Directory

### Set 1: Library Management System
| # | Topic / Practical Concept | Program File | Description |
|:---:|:---|:---|:---|
| 01 | **Array Operations** | [01_book_records_array.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library/01_book_records_array.cpp) | Insert at index, delete by ID, search by ID, display |
| 02 | **SLL Append & Update** | [02_returns_sll_append.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library/02_returns_sll_append.cpp) | SLL append book return status, update status, count 'R' |
| 03 | **SLL Mid Insert & Del Front** | [03_returns_sll_mid_delete.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library/03_returns_sll_mid_delete.cpp) | SLL insert at position, delete front, count 'P' (Pending) |
| 04 | **Sorted Doubly Linked List** | [04_members_sorted_dll.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library/04_members_sorted_dll.cpp) | Sorted insert by member ID, delete by ID, forward & backward traversal |
| 05 | **Array vs Linked List** | [05_books_issued_array_vs_ll.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library/05_books_issued_array_vs_ll.cpp) | Memory layout comparison, count books issued > 3 |
| 06 | **Stack Navigation (Array ADT)** | [06_catalogue_navigation_stack.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library/06_catalogue_navigation_stack.cpp) | LIFO push, pop, peek, navigation history display |
| 07 | **Infix to Postfix & Evaluation** | [07_late_fine_infix_eval.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library/07_late_fine_infix_eval.cpp) | Evaluate `(D * R) + S - W` fine formula |
| 08 | **Parenthesis Checker** | [08_search_query_parentheses.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library/08_search_query_parentheses.cpp) | Bracket balancing for search expressions `()`, `{}`, `[]` |
| 09 | **Stack Infix Trace** | [09_fine_billing_system.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library/09_fine_billing_system.cpp) | Complete trace table with operator & operand stack snapshots |
| 10 | **Circular Queue Simulation** | [10_issue_counter_queue.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library/10_issue_counter_queue.cpp) | Array-based circular queue of size 5 (enqueue, dequeue, front, rear) |
| 11 | **Selection & Insertion Sort** | [11_books_selection_insertion_sort.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library/11_books_selection_insertion_sort.cpp) | Sort books by popularity (descending), comparisons/shifts, top 5 |
| 12 | **Linear vs Binary Search** | [12_book_linear_binary_search.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library/12_book_linear_binary_search.cpp) | Linear search by Title vs Binary search by Book ID with comparison counts |
| 13 | **Quick Sort (Lomuto)** | [13_fines_quick_sort.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library/13_fines_quick_sort.cpp) | Sort fine amounts in ascending order using Lomuto partitioning |
| 14 | **Selection & Bubble Sort** | [14_prices_selection_bubble_sort.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set1_Library/14_prices_selection_bubble_sort.cpp) | Ascending Selection & Bubble Sort, display top 5 most expensive books |

---

### Set 2: Hospital Management System
| # | Topic / Practical Concept | Program File | Description |
|:---:|:---|:---|:---|
| 01 | **Array Operations** | [01_patient_records_array.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital/01_patient_records_array.cpp) | Insert at index, delete by patient ID, search by ID, display |
| 02 | **SLL Append & Update** | [02_checkup_sll_append.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital/02_checkup_sll_append.cpp) | SLL append checkup status, update status, count 'C' (Completed) |
| 03 | **SLL Mid Insert & Del Front** | [03_checkup_sll_mid_delete.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital/03_checkup_sll_mid_delete.cpp) | SLL priority insertion, delete front, count 'P' (Pending) |
| 04 | **Sorted Doubly Linked List** | [04_doctors_sorted_dll.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital/04_doctors_sorted_dll.cpp) | Sorted insert by doctor ID, delete by ID, forward & backward traversal |
| 05 | **Array vs Linked List** | [05_temperatures_array_vs_ll.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital/05_temperatures_array_vs_ll.cpp) | Memory layout comparison, count fever cases > 99.5°F |
| 06 | **Stack Navigation (Array ADT)** | [06_portal_navigation_stack.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital/06_portal_navigation_stack.cpp) | LIFO push, pop, peek, medical record breadcrumbs |
| 07 | **Infix to Postfix & Evaluation** | [07_hospital_bill_infix_eval.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital/07_hospital_bill_infix_eval.cpp) | Evaluate `(C * D) + M - I` hospital bill formula |
| 08 | **Parenthesis Checker** | [08_dosage_parentheses.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital/08_dosage_parentheses.cpp) | Prescription formula bracket validator `()`, `{}`, `[]` |
| 09 | **Stack Infix Trace** | [09_hospital_billing_system.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital/09_hospital_billing_system.cpp) | Complete trace table with operator & operand stack snapshots |
| 10 | **Circular Queue Simulation** | [10_opd_counter_queue.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital/10_opd_counter_queue.cpp) | Array-based circular queue of size 5 (OPD consultation tokens) |
| 11 | **Selection & Insertion Sort** | [11_patients_selection_insertion_sort.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital/11_patients_selection_insertion_sort.cpp) | Sort patient severity scores (descending), metrics, top 5 critical |
| 12 | **Linear vs Binary Search** | [12_patient_linear_binary_search.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital/12_patient_linear_binary_search.cpp) | Linear search by Name vs Binary search by Patient ID with comparisons |
| 13 | **Quick Sort (Lomuto)** | [13_temperatures_quick_sort.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital/13_temperatures_quick_sort.cpp) | Sort patient body temperatures in ascending order |
| 14 | **Selection & Bubble Sort** | [14_bills_selection_bubble_sort.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set2_Hospital/14_bills_selection_bubble_sort.cpp) | Ascending Selection & Bubble Sort, display top 5 highest bills |

---

### Set 3: Inventory Management System
| # | Topic / Practical Concept | Program File | Description |
|:---:|:---|:---|:---|
| 01 | **Array Operations** | [01_product_inventory_array.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory/01_product_inventory_array.cpp) | Insert at index, delete by product ID, search by ID, display |
| 02 | **SLL Append & Update** | [02_stock_sll_append.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory/02_stock_sll_append.cpp) | SLL append stock status, update status, count 'A' (Available) |
| 03 | **SLL Mid Insert & Del Front** | [03_stock_sll_mid_delete.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory/03_stock_sll_mid_delete.cpp) | SLL priority arrival, dispatch oldest front item, count 'O' (Out of stock) |
| 04 | **Sorted Doubly Linked List** | [04_suppliers_sorted_dll.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory/04_suppliers_sorted_dll.cpp) | Sorted insert by supplier ID, delete by ID, forward & backward traversal |
| 05 | **Array vs Linked List** | [05_sales_array_vs_ll.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory/05_sales_array_vs_ll.cpp) | Memory layout comparison, count monthly sales > 500 units |
| 06 | **Stack Navigation (Array ADT)** | [06_warehouse_navigation_stack.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory/06_warehouse_navigation_stack.cpp) | LIFO push, pop, peek, warehouse portal navigation history |
| 07 | **Infix to Postfix & Evaluation** | [07_purchase_price_infix_eval.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory/07_purchase_price_infix_eval.cpp) | Evaluate `(C * Q) + S - D` purchase pricing formula |
| 08 | **Parenthesis Checker** | [08_stock_valuation_parentheses.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory/08_stock_valuation_parentheses.cpp) | Stock valuation expression bracket validator `()`, `{}`, `[]` |
| 09 | **Stack Infix Trace** | [09_purchase_billing_system.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory/09_purchase_billing_system.cpp) | Complete trace table with operator & operand stack snapshots |
| 10 | **Circular Queue Simulation** | [10_dispatch_counter_queue.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory/10_dispatch_counter_queue.cpp) | Array-based circular queue of size 5 (warehouse dispatch bay) |
| 11 | **Selection & Insertion Sort** | [11_sales_selection_insertion_sort.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory/11_sales_selection_insertion_sort.cpp) | Sort best-selling products (descending), metrics, top 5 bestsellers |
| 12 | **Linear vs Binary Search** | [12_product_linear_binary_search.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory/12_product_linear_binary_search.cpp) | Linear search by Name vs Binary search by Product ID with comparisons |
| 13 | **Quick Sort (Lomuto)** | [13_prices_quick_sort.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory/13_prices_quick_sort.cpp) | Sort unit prices in ascending order using Lomuto partition |
| 14 | **Selection & Bubble Sort** | [14_stock_selection_bubble_sort.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set3_Inventory/14_stock_selection_bubble_sort.cpp) | Ascending Selection & Bubble Sort, display top 5 highest stock items |

---

### Set 4: Banking Management System
| # | Topic / Practical Concept | Program File | Description |
|:---:|:---|:---|:---|
| 01 | **Array Operations** | [01_customer_accounts_array.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank/01_customer_accounts_array.cpp) | Insert at index, delete by account number, search by acc, display |
| 02 | **SLL Append & Update** | [02_emi_sll_append.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank/02_emi_sll_append.cpp) | SLL append loan EMI status, update status, count 'P' (Paid) |
| 03 | **SLL Mid Insert & Del Front** | [03_emi_sll_mid_delete.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank/03_emi_sll_mid_delete.cpp) | SLL priority insertion, process front transaction, count 'D' (Due) |
| 04 | **Sorted Doubly Linked List** | [04_loan_applicants_sorted_dll.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank/04_loan_applicants_sorted_dll.cpp) | Sorted insert by applicant ID, delete by ID, forward & backward traversal |
| 05 | **Array vs Linked List** | [05_balances_array_vs_ll.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank/05_balances_array_vs_ll.cpp) | Memory layout comparison, count accounts with balance > Rs. 50,000 |
| 06 | **Stack Navigation (Array ADT)** | [06_netbanking_navigation_stack.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank/06_netbanking_navigation_stack.cpp) | LIFO push, pop, peek, netbanking session breadcrumbs |
| 07 | **Infix to Postfix & Evaluation** | [07_simple_interest_infix_eval.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank/07_simple_interest_infix_eval.cpp) | Evaluate `(P * R * T) / 100` loan simple interest formula |
| 08 | **Parenthesis Checker** | [08_loan_eligibility_parentheses.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank/08_loan_eligibility_parentheses.cpp) | Loan eligibility rule bracket validator `()`, `{}`, `[]` |
| 09 | **Stack Infix Trace** | [09_loan_billing_system.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank/09_loan_billing_system.cpp) | Complete trace table with operator & operand stack snapshots |
| 10 | **Circular Queue Simulation** | [10_teller_counter_queue.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank/10_teller_counter_queue.cpp) | Array-based circular queue of size 5 (bank teller tokens) |
| 11 | **Selection & Insertion Sort** | [11_balances_selection_insertion_sort.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank/11_balances_selection_insertion_sort.cpp) | Sort balances (descending), metrics, top 5 HNI privilege accounts |
| 12 | **Linear vs Binary Search** | [12_account_linear_binary_search.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank/12_account_linear_binary_search.cpp) | Linear search by Name vs Binary search by Account No with comparisons |
| 13 | **Quick Sort (Lomuto)** | [13_interest_rates_quick_sort.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank/13_interest_rates_quick_sort.cpp) | Sort loan interest rates in ascending order using Lomuto partition |
| 14 | **Selection & Bubble Sort** | [14_transactions_selection_bubble_sort.cpp](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Departmental_Problem_Sets/Set4_Bank/14_transactions_selection_bubble_sort.cpp) | Ascending Selection & Bubble Sort, display top 5 highest transactions |

---

## How to Compile and Run Any Program

Every file can be compiled standalone with standard `g++`:

```bash
# Example: Compile Problem 10 of Set 1 (Library Queue)
g++ -std=c++14 -Wall -Wextra 01_book_records_array.cpp -o app
./app
```
