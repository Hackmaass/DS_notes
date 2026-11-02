# Data Structures Practical Codebook

> **S.Y. B.Tech Computer Engineering — Semester III**  
> Course Codes: `CE25PCC-202` (Theory) · `CE25PCC-203` (Laboratory)  
> **NMIET, Pune** — PCET Autonomous Curriculum

---

## What Is This?

A complete, exam-ready C++ practical codebook for Data Structures — built from the ground up for university lab exams, viva rounds, and departmental problem sets.

Every program is written as a **study manual**: clean first-principles C++ (no STL containers), line-by-line comments, dry-run trace tables, complexity analysis, and viva Q&A — all in one file.

- ✅ **100% Curriculum-Aligned** — Derived directly from `CE25PCC-202/203` syllabus + departmental DOCX question banks  
- ✅ **Zero STL Abstractions** — Arrays, structs, and raw pointers only (as prescribed exams demand)  
- ✅ **0 Errors, 0 Warnings** — Every file compiles clean under `g++ -std=c++14 -Wall -Wextra`

---

## Repository Structure

```
Data-Structures-Practical-Codebook/
│
├── 🎯 Exam_Output_Codes/              ← START HERE for exam day
│   ├── 01_array_insert_delete_search.cpp
│   ├── 02_linear_vs_binary_search.cpp
│   ├── 03_selection_sort_top5.cpp
│   ├── 04_insertion_sort_shifts.cpp
│   ├── 05_quick_sort_lomuto.cpp
│   ├── 06_singly_linked_list.cpp
│   ├── 07_stack_parentheses.cpp
│   ├── 08_circular_queue.cpp
│   └── README.md
│
├── 🧠 Fundamentals/                   ← 8 core building blocks
│   ├── 01_array_shift_insert_delete.cpp
│   ├── 02_singly_linked_list_basics.cpp
│   ├── 03_doubly_linked_list_basics.cpp
│   ├── 04_linear_vs_binary_search.cpp
│   ├── 05_selection_and_insertion_sort.cpp
│   ├── 06_quick_sort_partition.cpp
│   ├── 07_stack_lifo_and_parentheses.cpp
│   ├── 08_circular_queue_fifo.cpp
│   └── README.md
│
├── 📁 Departmental_Problem_Sets/      ← 56 standalone domain programs
│   ├── Set1_Library/   (14 programs)
│   ├── Set2_Hospital/  (14 programs)
│   ├── Set3_Inventory/ (14 programs)
│   ├── Set4_Bank/      (14 programs)
│   └── README.md
│
├── 📘 Unit_1_Arrays_Linked_Lists/
│   ├── arrays/
│   ├── singly_linked_list/
│   ├── doubly_linked_list/
│   ├── circular_linked_list/
│   └── applications/               (Library / Hospital / Inventory / Bank)
│
├── 📗 Unit_2_Searching_Sorting/
│   ├── searching/
│   ├── selection_sort/
│   ├── insertion_sort/
│   ├── quick_sort/
│   ├── bubble_sort/
│   ├── merge_sort/
│   └── applications/
│
├── 📙 Unit_3_Stacks_Recursion/
│   ├── stack_array/
│   ├── stack_linked_list/
│   ├── recursion/
│   └── stack_applications/
│
├── 📕 Unit_4_Queues/
│   ├── queue_array/
│   ├── queue_linked_list/
│   ├── circular_queue/
│   ├── priority_queue/
│   ├── deque/
│   └── applications/
│
├── 🗺 00_Curriculum_Mapping/
│   ├── source_audit.md
│   ├── practical_question_inventory.md
│   ├── curriculum_coverage.md
│   └── practical_index.md
│
└── 🔁 99_Revision/
    ├── algorithm_revision.md
    ├── complexity_reference.md
    ├── common_mistakes.md
    └── practical_viva_questions.md
```

---

## Quick-Start: Exam Day Checklist

The [`Exam_Output_Codes/`](Exam_Output_Codes/) folder has **8 ultra-compact programs** (~35 lines each). Each one shows the **exact terminal output** the examiner sees + 2–3 viva Q&As.

| # | Topic | File | Key Output |
|:-:|:------|:-----|:-----------|
| 01 | Array CRUD | [`01_array_insert_delete_search.cpp`](Exam_Output_Codes/01_array_insert_delete_search.cpp) | Shift right → insert, search index, shift left → delete |
| 02 | Searching | [`02_linear_vs_binary_search.cpp`](Exam_Output_Codes/02_linear_vs_binary_search.cpp) | Linear O(N) vs Binary O(log N) comparison counts |
| 03 | Selection Sort | [`03_selection_sort_top5.cpp`](Exam_Output_Codes/03_selection_sort_top5.cpp) | Unsorted → ascending sort → top 5 |
| 04 | Insertion Sort | [`04_insertion_sort_shifts.cpp`](Exam_Output_Codes/04_insertion_sort_shifts.cpp) | Sorted output + total shifts & comparisons |
| 05 | Quick Sort | [`05_quick_sort_lomuto.cpp`](Exam_Output_Codes/05_quick_sort_lomuto.cpp) | Lomuto partition around pivot → sorted |
| 06 | Singly Linked List | [`06_singly_linked_list.cpp`](Exam_Output_Codes/06_singly_linked_list.cpp) | `[10] -> [20] -> [30] -> [40] -> NULL` |
| 07 | Stack / Parentheses | [`07_stack_parentheses.cpp`](Exam_Output_Codes/07_stack_parentheses.cpp) | `{[()]}` BALANCED · `{[(])}` UNBALANCED |
| 08 | Circular Queue | [`08_circular_queue.cpp`](Exam_Output_Codes/08_circular_queue.cpp) | Full 5/5 → dequeue 2 → enqueue 2 via `% MAX` |

---

## The 8 Core Fundamentals

Every exam question is a disguised version of one of these 8 patterns. Master these first.

| Unit | File | Core Concept |
|:----:|:-----|:-------------|
| 1 | [`01_array_shift_insert_delete.cpp`](Fundamentals/01_array_shift_insert_delete.cpp) | Shift right to insert, shift left to delete |
| 1 | [`02_singly_linked_list_basics.cpp`](Fundamentals/02_singly_linked_list_basics.cpp) | Node creation, `curr = curr->next`, delete by value |
| 1 | [`03_doubly_linked_list_basics.cpp`](Fundamentals/03_doubly_linked_list_basics.cpp) | `prev`/`next` two-way links, bidirectional traversal |
| 2 | [`04_linear_vs_binary_search.cpp`](Fundamentals/04_linear_vs_binary_search.cpp) | Linear O(N) vs Binary O(log N) with comparison counters |
| 2 | [`05_selection_and_insertion_sort.cpp`](Fundamentals/05_selection_and_insertion_sort.cpp) | Selection Sort (1 swap/pass) & Insertion Sort (card-game shift) |
| 2 | [`06_quick_sort_partition.cpp`](Fundamentals/06_quick_sort_partition.cpp) | Lomuto partition, recursive divide & conquer |
| 3 | [`07_stack_lifo_and_parentheses.cpp`](Fundamentals/07_stack_lifo_and_parentheses.cpp) | LIFO push/pop, delimiter matching `()` `{}` `[]` |
| 4 | [`08_circular_queue_fifo.cpp`](Fundamentals/08_circular_queue_fifo.cpp) | `(rear+1)%MAX`, `(front+1)%MAX` modulo wrap-around |

---

## Departmental Problem Sets (56 Programs)

Four domain-specific sets, each with 14 standalone programs covering every lab topic:

| Set | Domain | Subfolder | Problems Covered |
|:---:|:-------|:----------|:-----------------|
| 1 | Library Management | [`Set1_Library/`](Departmental_Problem_Sets/Set1_Library/) | Array CRUD, SLL, DLL, Stack, Queue, Search, Sort |
| 2 | Hospital Management | [`Set2_Hospital/`](Departmental_Problem_Sets/Set2_Hospital/) | Array CRUD, SLL, DLL, Stack, Queue, Search, Sort |
| 3 | Inventory Management | [`Set3_Inventory/`](Departmental_Problem_Sets/Set3_Inventory/) | Array CRUD, SLL, DLL, Stack, Queue, Search, Sort |
| 4 | Banking Management | [`Set4_Bank/`](Departmental_Problem_Sets/Set4_Bank/) | Array CRUD, SLL, DLL, Stack, Queue, Search, Sort |

Each set covers this sequence of 14 topics:

> Array Ops → SLL Append → SLL Mid Insert/Delete → Sorted DLL → Array vs LL Memory → Stack Navigation → Infix to Postfix Eval → Parenthesis Checker → Stack Infix Trace → Circular Queue → Selection + Insertion Sort → Linear + Binary Search → Quick Sort → Selection + Bubble Sort

Full index: [`Departmental_Problem_Sets/README.md`](Departmental_Problem_Sets/README.md)

---

## Unit Coverage

### Unit 1 — Arrays & Linked Lists
| Lab | Program | Concept |
|:---:|:--------|:--------|
| 01 | [`01_student_information_system.cpp`](Unit_1_Arrays_Linked_Lists/arrays/01_student_information_system.cpp) | Array insert at position, delete by roll, search, display |
| 02 | [`02_daily_attendance_sll.cpp`](Unit_1_Arrays_Linked_Lists/singly_linked_list/02_daily_attendance_sll.cpp) | SLL append, update day status, count P/A |
| 03 | [`03_sorted_students_dll.cpp`](Unit_1_Arrays_Linked_Lists/doubly_linked_list/03_sorted_students_dll.cpp) | DLL sorted insert, delete by key, bidirectional traversal |
| 04 | [`04_ia_marks_array_vs_linkedlist.cpp`](Unit_1_Arrays_Linked_Lists/arrays/04_ia_marks_array_vs_linkedlist.cpp) | Contiguous (stack) vs dynamic (heap) memory address comparison |

### Unit 2 — Searching & Sorting
| Lab | Program | Concept |
|:---:|:--------|:--------|
| 05a | [`05_merit_list_selection_sort.cpp`](Unit_2_Searching_Sorting/selection_sort/05_merit_list_selection_sort.cpp) | Selection Sort descending by CGPA, Top 5 |
| 05b | [`05_merit_list_insertion_sort.cpp`](Unit_2_Searching_Sorting/insertion_sort/05_merit_list_insertion_sort.cpp) | Insertion Sort with shift count, Top 5 |
| 06 | [`06_student_search_linear_binary.cpp`](Unit_2_Searching_Sorting/searching/06_student_search_linear_binary.cpp) | Linear by Name vs Binary by Roll with comparison counters |
| 07 | [`07_student_percentage_quick_sort.cpp`](Unit_2_Searching_Sorting/quick_sort/07_student_percentage_quick_sort.cpp) | Lomuto partition on float percentages |
| 08 | [`08_percentage_selection_bubble_sort.cpp`](Unit_2_Searching_Sorting/bubble_sort/08_percentage_selection_bubble_sort.cpp) | Ascending Selection + Bubble Sort, Top 5 |

### Unit 3 — Stacks & Recursion
| Lab | Program | Concept |
|:---:|:--------|:--------|
| 09 | [`09_browser_history_stack.cpp`](Unit_3_Stacks_Recursion/stack_applications/09_browser_history_stack.cpp) | Student portal browser history (LIFO) |
| 10 | [`10_marks_infix_to_postfix_eval.cpp`](Unit_3_Stacks_Recursion/stack_applications/10_marks_infix_to_postfix_eval.cpp) | Shunting-Yard algorithm + postfix evaluation |
| 11 | [`11_parenthesis_checker_stack.cpp`](Unit_3_Stacks_Recursion/stack_applications/11_parenthesis_checker_stack.cpp) | Delimiter matching `()` `{}` `[]` |
| 12 | [`12_college_billing_system_stack.cpp`](Unit_3_Stacks_Recursion/stack_applications/12_college_billing_system_stack.cpp) | Infix fee formula → postfix conversion with stack trace |

### Unit 4 — Queues
| Lab | Program | Concept |
|:---:|:--------|:--------|
| 13 | [`13_admission_queue_linear.cpp`](Unit_4_Queues/queue_array/13_admission_queue_linear.cpp) | Linear array queue with false-overflow demonstration |
| 14 | [`14_bus_pass_circular_queue.cpp`](Unit_4_Queues/circular_queue/14_bus_pass_circular_queue.cpp) | Circular queue via `(rear+1)%MAX` modulo |
| 15 | [`15_cgpa_priority_queue.cpp`](Unit_4_Queues/priority_queue/15_cgpa_priority_queue.cpp) | Max-CGPA priority queue (highest served first) |
| 16 | [`16_student_service_desk_deque.cpp`](Unit_4_Queues/deque/16_student_service_desk_deque.cpp) | Deque: emergency front insert, normal rear insert |

---

## Pedagogical Structure of Every Program

Each `.cpp` file follows this 13-part anatomy:

1. **Program Header** — Course code, problem statement verbatim, learning objective  
2. **Concept Explanation (WHY)** — Why this DS/algo over simpler alternatives  
3. **Numbered Algorithm** — Plain-English steps with rationale  
4. **Data Structure Definition** — Clean struct/class with named members  
5. **Core Functions** — Every non-trivial line commented  
6. **Pointer & Memory State Tracking** — Stack vs heap, address mutations  
7. **Automated Verification Driver** — Typical, edge-case, and boundary tests  
8. **Interactive Exam Menu** — Console switch-case for live practical testing  
9. **Dry Run Trace Table** — Variable values, pointers, and memory state per step  
10. **Sample Input / Output Block** — Real terminal transcript for comparison  
11. **Complexity Analysis** — Big-O Best / Average / Worst + Space with derivations  
12. **Common Exam Traps** — Off-by-one, dangling pointer, and boundary bugs  
13. **Exam Memorization Checklist** — Compact mental checklist for exam reproduction  

---

## Compilation & Execution

All programs are self-contained and compile with any C++11/14 compliant compiler.

```bash
# Standard compile command (use for any file)
g++ -std=c++14 -Wall -Wextra <filename>.cpp -o app

# Linux / macOS
./app

# Windows PowerShell / CMD
.\app.exe
```

**Example — Lab 14 (Bus Pass Circular Queue):**
```powershell
g++ -std=c++14 -Wall -Wextra Unit_4_Queues/circular_queue/14_bus_pass_circular_queue.cpp -o app.exe
.\app.exe
```

---

## Recommended Study Sequence

```
Week 1-2  →  Fundamentals/ (8 files — understand the 8 core patterns)
Week 3    →  Unit_1 + Unit_2 (Lab files 01–08)
Week 4    →  Unit_3 + Unit_4 (Lab files 09–16)
Week 5    →  Departmental_Problem_Sets/ (your assigned set)
Exam Eve  →  Exam_Output_Codes/ + 99_Revision/
```

| Step | What to Study | Why |
|:----:|:-------------|:----|
| 1 | [`Fundamentals/`](Fundamentals/) | Internalize the 8 base patterns |
| 2 | Unit lab files (01–08) | Array + Linked List depth |
| 3 | Unit lab files (09–16) | Stack + Queue depth |
| 4 | Your departmental set | Domain-specific exam practice |
| 5 | [`99_Revision/algorithm_revision.md`](99_Revision/algorithm_revision.md) | Quick numbered steps for every algo |
| 6 | [`99_Revision/complexity_reference.md`](99_Revision/complexity_reference.md) | Big-O lookup table |
| 7 | [`99_Revision/practical_viva_questions.md`](99_Revision/practical_viva_questions.md) | 35+ high-yield viva Q&A |
| 8 | [`Exam_Output_Codes/`](Exam_Output_Codes/) | Final exam-day rapid review |

---

## Reference Documents

| File | Purpose |
|:-----|:--------|
| [`00_Curriculum_Mapping/source_audit.md`](00_Curriculum_Mapping/source_audit.md) | Complete audit of official PDF & DOCX curriculum sources |
| [`00_Curriculum_Mapping/practical_question_inventory.md`](00_Curriculum_Mapping/practical_question_inventory.md) | Verbatim inventory of all 16 lab + 36 alternate questions |
| [`00_Curriculum_Mapping/curriculum_coverage.md`](00_Curriculum_Mapping/curriculum_coverage.md) | CO1–CO4, Units I–IV cross-mapping matrix |
| [`00_Curriculum_Mapping/practical_index.md`](00_Curriculum_Mapping/practical_index.md) | Master hyperlinked navigation index |
| [`99_Revision/common_mistakes.md`](99_Revision/common_mistakes.md) | Off-by-one errors, dangling pointers, boundary bugs |

---

## Prescribed Textbooks

> As per `CE25PCC-202` syllabus (Pages 15–20):

- Sartaj Sahni — *Data Structures, Algorithms and Applications in C++*
- Yashavant Kanetkar — *Data Structures Through C++*
- Mark Allen Weiss — *Data Structures and Algorithm Analysis in C++*
- Ellis Horowitz & Sartaj Sahni — *Fundamentals of Data Structures*
- D.S. Malik — *Data Structures Using C++*
