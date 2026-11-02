# Data Structures Practical Codebook
### Second Year B.Tech Computer Engineering (Semester III)
**Course Codes:** `CE25PCC-202` (Data Structures Theory) & `CE25PCC-203` (Data Structures Laboratory)  
**Institution:** Nutan Maharashtra Institute of Engineering & Technology (NMIET), Pune  
**Affiliation:** Pimpri Chinchwad Education Trust (PCET) Autonomous Curriculum

---

## 📖 About This Codebook

This repository is an educational, production-grade, and curriculum-aligned **Data Structures Practical Codebook** crafted specifically for S.Y. B.Tech Computer Engineering students.

Unlike typical code repositories with sparse snippets, every single program in this codebook has been authored as an exhaustive **study manual and exam memorization guide**. Each program is designed to be understood, traced on paper, committed to memory, and reproduced with zero compilation errors in university practical exams.

### 🏛 Strict Curriculum Compliance Guarantees
1. **100% Curriculum-Aligned**: Derived directly from official university syllabus documents:
   - `Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf` (Course `CE25PCC-202` & `CE25PCC-203`, Pages 15–20)
   - `Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx` (Departmental Lab Question Bank)
   - `Four Alternate Problem Sets Sorting and Searching.docx` (Departmental Sorting & Searching Bank)
2. **First-Principles C++**: Textbooks prescribed in syllabus (Sartaj Sahni, Yashavant Kanetkar, Mark Allen Weiss, Ellis Horowitz, D.S. Malik). Zero reliance on ready-made STL containers (`std::stack`, `std::queue`, `std::list`, `std::sort`). Everything is built from scratch using structs, pointers, arrays, and standard I/O streams.
3. **100% Tested & Warning-Free**: Every program compiles cleanly under `g++ -std=c++14 -Wall -Wextra` with **0 errors and 0 warnings**.

---

## 📚 13-Part Pedagogical Anatomy of Every Program

Every C++ file in this codebook adheres strictly to this rigorous pedagogical framework:
1. **Program Header**: Course code, lab group, official problem statement verbatim, and learning objective.
2. **Concept Explanation (WHY)**: Why this data structure or algorithm is needed over simpler alternatives.
3. **Step-by-Step Numbered Algorithm (WHAT & WHY)**: Plain-English numbered steps explaining both action and rationale.
4. **Data Structure Definition**: Clean structs/classes with explicit member variable naming.
5. **Core Functions with Line-by-Line Comments**: Every non-trivial line explained directly in code.
6. **Pointer & Memory State Tracking**: Clear explanation of stack vs. heap allocation, address mutations, and pointer link updates.
7. **Automated Verification Driver**: Built-in verification suites demonstrating typical, edge-case, and boundary operations.
8. **Interactive Examination Menu**: Console-driven switch-case interface for live practical examination testing.
9. **Dry Run Trace Table**: Formatted ASCII table showing variable values, pointers, and memory state at each step.
10. **Sample Input / Output Block**: Real terminal transcripts for study comparison.
11. **Complexity Analysis**: Big-O Best, Average, Worst Time Complexity and Auxiliary Space Complexity with mathematical derivations.
12. **Common Exam Traps & Pitfalls**: Specific off-by-one, dangling pointer, and boundary bugs with corrections.
13. **Exam Memorization Checklist**: Compact mental checklist for reproduction under exam time constraints.

---

## 🗂 Codebook Repository Structure

```
Data-Structures-Practical-Codebook/
├── Exam_Output_Codes/                     # 35-Line Output-Focused Programs + Viva Q&A (Exam Fast Track!)
│   ├── 01_array_insert_delete_search.cpp  # Minimal Array CRUD (exact output + viva)
│   ├── 02_linear_vs_binary_search.cpp     # Minimal Search Comparison (exact output + viva)
│   ├── 03_selection_sort_top5.cpp         # Minimal Selection Sort & Top 5 (exact output + viva)
│   ├── 04_insertion_sort_shifts.cpp       # Minimal Insertion Sort & Shifts (exact output + viva)
│   ├── 05_quick_sort_lomuto.cpp           # Minimal Quick Sort Lomuto (exact output + viva)
│   ├── 06_singly_linked_list.cpp          # Minimal Singly Linked List (exact output + viva)
│   ├── 07_stack_parentheses.cpp           # Minimal Stack Parentheses (exact output + viva)
│   ├── 08_circular_queue.cpp              # Minimal Circular Queue Modulo (exact output + viva)
│   └── README.md                          # Output reference & viva checklist
│
├── Fundamentals/                          # 8 Core Building Block Programs (Deep Conceptual Guide)
│   ├── 01_array_shift_insert_delete.cpp   # Array shifting (right for insert, left for delete)
│   ├── 02_singly_linked_list_basics.cpp   # Node creation, next pointer walk, delete by value
│   ├── 03_doubly_linked_list_basics.cpp   # Two-way links (prev/next), bidirectional traversal
│   ├── 04_linear_vs_binary_search.cpp     # Linear search O(N) vs Binary search O(log N)
│   ├── 05_selection_and_insertion_sort.cpp# Selection Sort (min swap) & Insertion Sort (card shift)
│   ├── 06_quick_sort_partition.cpp        # Lomuto partition around pivot, recursive sorting
│   ├── 07_stack_lifo_and_parentheses.cpp  # LIFO push/pop, matching parentheses (), {}, []
│   ├── 08_circular_queue_fifo.cpp         # Modulo index wrapping (rear+1)%MAX, (front+1)%MAX
│   └── README.md                          # Concept-to-exam mapping guide
│
├── Departmental_Problem_Sets/             # 56 Standalone Programs directly from College DOCX Problem Sets
│   ├── Set1_Library/                      # 14 Standalone Programs for Set 1 (Library Management)
│   ├── Set2_Hospital/                     # 14 Standalone Programs for Set 2 (Hospital Management)
│   ├── Set3_Inventory/                    # 14 Standalone Programs for Set 3 (Inventory Management)
│   ├── Set4_Bank/                         # 14 Standalone Programs for Set 4 (Bank Management)
│   └── README.md                          # Master index for all 56 standalone departmental programs
│
├── 00_Curriculum_Mapping/
│   ├── source_audit.md                    # Complete audit of official PDF & DOCX curriculum sources
│   ├── practical_question_inventory.md    # Verbatim inventory of all 16 lab & 36 alternate questions
│   ├── curriculum_coverage.md             # CO1-CO4, Units I-IV cross-mapping matrix
│   └── practical_index.md                # Master hyperlinked navigation index
│
├── Unit_1_Arrays_Linked_Lists/
│   ├── arrays/
│   │   ├── 01_student_information_system.cpp      # Lab 01: Array insert at pos, delete by roll, search, display
│   │   └── 04_ia_marks_array_vs_linkedlist.cpp    # Lab 04: Contiguous vs Heap memory addresses (>80 marks)
│   ├── singly_linked_list/
│   │   └── 02_daily_attendance_sll.cpp            # Lab 02: SLL append, update day, count P/A, display
│   ├── doubly_linked_list/
│   │   └── 03_sorted_students_dll.cpp             # Lab 03: DLL sorted insert, delete by key, bidirectional traversal
│   ├── circular_linked_list/
│   │   └── 00_circular_linked_list_operations.cpp # Theory: CLL insert, delete, do-while traversal
│   └── applications/
│       ├── set1_library_system.cpp                # Set 1: Library books array, SLL returns, sorted DLL members
│       ├── set2_hospital_system.cpp               # Set 2: Hospital patients array, SLL checkup, sorted DLL doctors
│       ├── set3_inventory_system.cpp              # Set 3: Warehouse products array, SLL stock, sorted DLL suppliers
│       └── set4_bank_system.cpp                   # Set 4: Customer accounts array, SLL EMI, sorted DLL loan applicants
│
├── Unit_2_Searching_Sorting/
│   ├── selection_sort/
│   │   └── 05_merit_list_selection_sort.cpp       # Lab 05a: Selection sort descending by CGPA, Top 5
│   ├── insertion_sort/
│   │   └── 05_merit_list_insertion_sort.cpp       # Lab 05b: Insertion sort descending with shift count, Top 5
│   ├── searching/
│   │   └── 06_student_search_linear_binary.cpp    # Lab 06: Linear search by Name vs Binary search by Roll
│   ├── quick_sort/
│   │   └── 07_student_percentage_quick_sort.cpp   # Lab 07: Lomuto partition, recursive Quick Sort on float %
│   ├── bubble_sort/
│   │   └── 08_percentage_selection_bubble_sort.cpp# Lab 08: Ascending Selection Sort, Bubble Sort, Top 5
│   ├── merge_sort/
│   │   └── 00_merge_sort_divide_conquer.cpp       # Theory: Divide-and-conquer Merge Sort with stability
│   └── applications/
│       ├── set1_library_sorting_searching.cpp     # Set 1: Library books ranking, searching, fines quicksort, prices
│       ├── set2_hospital_sorting_searching.cpp    # Set 2: Hospital severity ranking, search, temps quicksort, bills
│       ├── set3_inventory_sorting_searching.cpp   # Set 3: Inventory sales ranking, search, prices quicksort, stock
│       └── set4_bank_sorting_searching.cpp        # Set 4: Bank balances ranking, search, interest quicksort, txns
│
├── Unit_3_Stacks_Recursion/
│   ├── stack_array/
│   │   └── 00_stack_array_adt.cpp                 # Theory: LIFO array stack ADT with boundary checks
│   ├── stack_linked_list/
│   │   └── 00_stack_linked_list_adt.cpp           # Theory: Dynamic linked stack with heap management
│   ├── recursion/
│   │   └── 00_recursion_call_stack_tracing.cpp    # Theory: Factorial & Fibonacci call stack frame trace
│   └── stack_applications/
│       ├── 09_browser_history_stack.cpp           # Lab 09: Student portal browser history simulator
│       ├── 10_marks_infix_to_postfix_eval.cpp     # Lab 10: Shunting-Yard conversion & postfix evaluation
│       ├── 11_parenthesis_checker_stack.cpp       # Lab 11: Delimiter matching `()`, `{}`, `[]`
│       ├── 12_college_billing_system_stack.cpp    # Lab 12: Infix fee formula conversion with stack contents
│       ├── set1_library_stack_apps.cpp            # Set 1: Library catalogue stack, fine formula, query parentheses
│       ├── set2_hospital_stack_apps.cpp           # Set 2: Patient portal stack, bill formula, dosage parentheses
│       ├── set3_inventory_stack_apps.cpp          # Set 3: Warehouse portal stack, price formula, valuation parentheses
│       └── set4_bank_stack_apps.cpp               # Set 4: Netbanking stack, interest formula, eligibility parentheses
│
├── Unit_4_Queues/
│   ├── queue_array/
│   │   ├── 00_queue_array_adt.cpp                 # Theory: Linear array queue & false overflow demonstration
│   │   └── 13_admission_queue_linear.cpp          # Lab 13: Admission token queue with front/rear display
│   ├── queue_linked_list/
│   │   └── 00_queue_linked_list_adt.cpp           # Theory: Dynamic linked queue with front & rear pointers
│   ├── circular_queue/
│   │   └── 14_bus_pass_circular_queue.cpp         # Lab 14: Bus pass circular queue via modulo arithmetic
│   ├── priority_queue/
│   │   └── 15_cgpa_priority_queue.cpp             # Lab 15: CGPA priority queue (max-CGPA served first)
│   ├── deque/
│   │   └── 16_student_service_desk_deque.cpp      # Lab 16: Service desk deque (emergency front, normal rear)
│   └── applications/
│       ├── 00_cpu_scheduling_print_queue.cpp      # Theory: Round-Robin CPU scheduling & print spooler
│       ├── set1_library_issue_counter_queue.cpp   # Set 1: Book issue counter queue simulation
│       ├── set2_hospital_opd_queue.cpp            # Set 2: Hospital OPD patient queue simulation
│       ├── set3_inventory_dispatch_queue.cpp      # Set 3: Warehouse dispatch order queue simulation
│       └── set4_bank_teller_queue.cpp             # Set 4: Bank teller counter customer queue simulation
│
└── 99_Revision/
    ├── algorithm_revision.md                      # Quick numbered steps for every algorithm
    ├── complexity_reference.md                    # Comparative Big-O time and space lookup table
    ├── common_mistakes.md                         # Student exam traps, off-by-one errors & bug prevention
    └── practical_viva_questions.md                # 35+ high-yield viva questions with concise model answers
```

---

## 🛠 Compilation & Execution Instructions

All programs can be compiled using any C++11/C++14 compliant compiler (GCC, Clang, MSVC).

### Using GCC / G++ (Windows / Linux / macOS):
```bash
# Compile with strict compiler warnings enabled
g++ -std=c++14 -Wall -Wextra <filename>.cpp -o <executable_name>

# Execute
./<executable_name>        # Linux / macOS
.\<executable_name>.exe    # Windows PowerShell / CMD
```

### Example: Running Group D Assignment 14 (Bus Pass Circular Queue)
```powershell
g++ -std=c++14 -Wall -Wextra Unit_4_Queues/circular_queue/14_bus_pass_circular_queue.cpp -o 14_bus_pass_circular_queue.exe
.\14_bus_pass_circular_queue.exe
```

---

## 🎯 Recommended Study Sequence for Exam Preparation

1. **Step 1: Understand Data Representation**: Start with [`01_student_information_system.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Unit_1_Arrays_Linked_Lists/arrays/01_student_information_system.cpp) and [`04_ia_marks_array_vs_linkedlist.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Unit_1_Arrays_Linked_Lists/arrays/04_ia_marks_array_vs_linkedlist.cpp) to master contiguous stack memory vs. dynamic heap pointer linking.
2. **Step 2: Master Pointer Manipulation**: Study [`02_daily_attendance_sll.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Unit_1_Arrays_Linked_Lists/singly_linked_list/02_daily_attendance_sll.cpp) and [`03_sorted_students_dll.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Unit_1_Arrays_Linked_Lists/doubly_linked_list/03_sorted_students_dll.cpp). Draw the pointer diagrams on paper!
3. **Step 3: Internalize Searching & Sorting**: Trace [`06_student_search_linear_binary.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Unit_2_Searching_Sorting/searching/06_student_search_linear_binary.cpp) and [`07_student_percentage_quick_sort.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Unit_2_Searching_Sorting/quick_sort/07_student_percentage_quick_sort.cpp) Lomuto partition index pointer advances.
4. **Step 4: Conquer Stack Transformations**: Work through [`10_marks_infix_to_postfix_eval.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Unit_3_Stacks_Recursion/stack_applications/10_marks_infix_to_postfix_eval.cpp) and [`12_college_billing_system_stack.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Unit_3_Stacks_Recursion/stack_applications/12_college_billing_system_stack.cpp).
5. **Step 5: Solve False Overflow**: Trace the circular pointer wrap-around in [`14_bus_pass_circular_queue.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Unit_4_Queues/circular_queue/14_bus_pass_circular_queue.cpp).
6. **Step 6: Pre-Exam Rapid Memorization**: Review [`99_Revision/algorithm_revision.md`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/99_Revision/algorithm_revision.md), [`99_Revision/common_mistakes.md`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/99_Revision/common_mistakes.md), and quiz yourself with [`99_Revision/practical_viva_questions.md`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/99_Revision/practical_viva_questions.md).
