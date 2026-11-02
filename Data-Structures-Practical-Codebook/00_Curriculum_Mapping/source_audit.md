# Source Audit

## 1. Overview and Authority Hierarchy
This document audits all source files provided in the project repository for the **Data Structures (CE25PCC-202)** and **Data Structures Laboratory (CE25PCC-203)** courses prescribed for the Second Year B.Tech Computer Engineering program at Nutan Maharashtra Institute of Engineering and Technology (NMIET) under the Pimpri Chinchwad Education Trust (PCET) autonomy framework.

The primary authority for all course outcomes, unit contents, laboratory assignment requirements, evaluation rubrics, and textbook specifications is the official curriculum and the departmentally distributed alternate problem set documents located in the repository's `Syllabus/` directory.

---

## 2. Source Files Inspection Table

| Source file | Pages / Paras Inspected | Relevant information | Status |
|---|---:|---|---|
| `Syllabus/Curriculum-S.-Y.-B.Tech_.-Computer-Engg-merged.pdf` | Pages 1–101 (In-depth: Pages 4, 8, 15–20, 71–73) | **Semester III Core Syllabus:**<br>- Course Code: `CE25PCC-202` (Data Structures Theory, 30 Hrs, 2 Credits)<br>- Course Code: `CE25PCC-203` (Data Structures Laboratory, 4 Hrs/week, 2 Credits)<br>- Prescribed Textbooks & References: Sahni (C++), Kanetkar (C++), Weiss (C++), Horowitz & Sahni (C++), Malik (C++).<br>- Prescribed Language: **C++**.<br>- **Laboratory Assignment List (16 Experiments):**<br>  * **Group A (Assignments 1–4):** Arrays and Linked Lists (Student Info System, Attendance SLL, Sorted Roll No DLL, Marks Array vs LL).<br>  * **Group B (Assignments 5–8):** Searching and Sorting (Merit List CGPA Selection/Insertion, Academic Search Linear/Binary, Percentages Quick Sort, Percentages Selection/Bubble Sort).<br>  * **Group C (Assignments 9–12):** Stacks and Expressions (Browser History Stack, Infix to Postfix & Eval, Balanced Parentheses, College Fee Billing System).<br>  * **Group D (Assignments 13–16):** Queues (Student Admission Queue, Bus Pass Circular Queue, CGPA Priority Queue, Service Desk Deque).<br>- Lab Conduction Note: Instructor conducts at least 3 assignments per group across batches.<br>- Pages 71–73 confirmed as Semester IV Advanced Data Structures (Trees/Graphs/Hashing). | Verified & Fully Extracted |
| `Syllabus/Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx` | 205 Paragraphs (Complete document) | **Departmental Batched Practical Problem Sets for Groups A, C, and D:**<br>Distributed across four real-world application domains:<br>1. **Set 1:** Library Management System (Books Array, Return Status SLL insert-end & update, Return Status SLL insert-mid & delete-front, Members Sorted DLL, Book Count Array vs LL, Catalogue History Stack, Fine Formula Infix-Postfix & Eval, Search Query Parentheses, Fine Billing Stack Trace, Issue Counter Queue).<br>2. **Set 2:** Hospital Management System (Patients Array, Checkup SLL insert-end & update, Checkup SLL insert-mid & delete-front, Doctors Sorted DLL, Temp Array vs LL, Patient Portal Stack, Bill Formula Infix-Postfix & Eval, Dosage Parentheses, Hospital Billing Stack Trace, OPD Queue).<br>3. **Set 3:** Inventory and Warehouse System (Products Array, Stock Status SLL insert-end & update, Stock Status SLL insert-mid & delete-front, Suppliers Sorted DLL, Sales Array vs LL, Warehouse Portal Stack, Price Formula Infix-Postfix & Eval, Stock Valuation Parentheses, Purchase Billing Stack Trace, Goods Dispatch Queue).<br>4. **Set 4:** Bank Management System (Customers Array, EMI Status SLL insert-end & update, EMI Status SLL insert-mid & delete-front, Loan Applicants Sorted DLL, Balance Array vs LL, NetBanking Stack, Interest Formula Infix-Postfix & Eval, Loan Eligibility Parentheses, Loan Billing Stack Trace, Teller Counter Queue). | Verified & Fully Extracted |
| `Syllabus/Four Alternate Problem Sets Sorting and Searching.docx` | 79 Paragraphs (Complete document) | **Departmental Batched Practical Problem Sets for Group B (Searching & Sorting):**<br>Distributed across four application domains:<br>1. **Set 1 (Library):** Ranked most-issued books (Selection Sort desc, Insertion Sort shift count, Top 5); Book Search (Linear by Title, Binary by Book ID, comparison count); Quick Sort fine amounts; Book prices (Selection & Bubble Sort asc, Top 5).<br>2. **Set 2 (Hospital):** Priority patients by severity (Selection Sort desc, Insertion Sort shifts, Top 5); Patient Search (Linear by Name, Binary by Patient ID, comparison count); Quick Sort temperatures; Patient bills (Selection & Bubble Sort asc, Top 5).<br>3. **Set 3 (Inventory):** Best-seller products by sales (Selection Sort desc, Insertion Sort shifts, Top 5); Product Search (Linear by Name, Binary by Product ID, comparison count); Quick Sort unit prices; Stock quantities (Selection & Bubble Sort asc, Top 5).<br>4. **Set 4 (Bank):** Ranked customers by balance (Selection Sort desc, Insertion Sort shifts, Top 5); Customer Search (Linear by Name, Binary by Account No, comparison count); Quick Sort interest rates; Transaction amounts (Selection & Bubble Sort asc, Top 5). | Verified & Fully Extracted |

---

## 3. Discrepancy Analysis and Reconciliation
1. **Curriculum PDF vs Alternate DOCX Sets:**
   - The Curriculum PDF specifies the foundational canonical assignments (Assignments 1 through 16) themed around an Academic / Student Information context.
   - The two Word documents (`.docx`) provide the alternate batch problem sets created specifically to fulfill the guideline on Page 17 of the curriculum: *"The instructor is expected to conduct Three assignments from each group (A, B, C, D). The instructor may set multiple sets of assignments and distribute them among batches of students."*
   - These alternate sets adapt the identical core algorithmic operations (arrays, singly linked list variations, doubly linked lists, linear/binary search with comparisons, bubble/selection/insertion/quick sort with shift counting, stack navigation, infix-to-postfix/eval, bracket matching, billing traces, and queues) to 4 domains: Library, Hospital, Warehouse, and Bank.
   - **Reconciliation Strategy:**
     - The Codebook provides complete, independently compilable, thoroughly annotated implementations for all **16 canonical curriculum laboratory assignments**.
     - In addition, it provides standalone implementations for the required **theory-mandated foundational structures** (Circular Linked List, Merge Sort, Linked Stack, Linked Queue, Recursion Call Stack Tracing, Round Robin / Print Queue).
     - Furthermore, it provides dedicated comprehensive domain applications covering the **Four Alternate Sets** (Library, Hospital, Warehouse, Bank) preserving every single required operation, variable name, and scenario.

2. **Programming Language Decision:**
   - Both the Theory (Page 16) and Laboratory (Page 20) curriculum documents cite only C++ textbooks (Sartaj Sahni, Yashavant Kanetkar, Mark Allen Weiss, Horowitz & Sahni, D.S. Malik).
   - Therefore, **Modern Educational C++ (C++11/C++14 standard, manual memory management using structs, pointers, `new`/`delete`, standard console I/O, no STL container shortcuts)** is established as the sole, consistent programming language across the entire codebook.

---

## 4. Verification Check
- PDF text extraction: Completed and verified against page renders.
- DOCX XML extraction: Completed and verified across all 4 sets.
- Course numbers and codes: Verified (`CE25PCC-202` and `CE25PCC-203`).
- Semesters verified: Semester III (Data Structures) isolated from Semester IV (Advanced Data Structures).
- Zero discrepancies left unresolved.
