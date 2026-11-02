# 🎯 Exam Output-Focused Codes (35-Line Master Guide)

Welcome to the **Exam Output Codes** folder!

This folder was created specifically for **rapid university practical examination preparation**. Each file contains:
1. **The Exact Expected Terminal Output**: The output the examiner wants to see on your screen.
2. **The Ultra-Compact Working Code (30–40 Lines)**: Real, working C++ with zero unnecessary fluff that runs instantaneously.
3. **The Examiner's Viva Q&A**: The exact 2–3 questions asked when looking at your screen.

---

## 📋 The 8 Exam Codes Checklist

| # | Topic | Exam Program File | Key Output Shown to Examiner |
|:---:|:---|:---|:---|
| **01** | **Array CRUD** | [`01_array_insert_delete_search.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Exam_Output_Codes/01_array_insert_delete_search.cpp) | Shift right to insert, search index, shift left to delete |
| **02** | **Searching** | [`02_linear_vs_binary_search.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Exam_Output_Codes/02_linear_vs_binary_search.cpp) | Shows Linear $O(N)$ vs Binary $O(\log N)$ comparison counts |
| **03** | **Selection Sort** | [`03_selection_sort_top5.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Exam_Output_Codes/03_selection_sort_top5.cpp) | Unsorted $\rightarrow$ Ascending Sort $\rightarrow$ Top 5 highest scores |
| **04** | **Insertion Sort** | [`04_insertion_sort_shifts.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Exam_Output_Codes/04_insertion_sort_shifts.cpp) | Unsorted $\rightarrow$ Sorted $\rightarrow$ Total shifts and comparisons count |
| **05** | **Quick Sort** | [`05_quick_sort_lomuto.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Exam_Output_Codes/05_quick_sort_lomuto.cpp) | Unsorted $\rightarrow$ Lomuto partition around pivot $\rightarrow$ Sorted |
| **06** | **Singly Linked List** | [`06_singly_linked_list.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Exam_Output_Codes/06_singly_linked_list.cpp) | `[10] -> [20] -> [30] -> [40] -> NULL` (Append & Walk) |
| **07** | **Stack Parentheses** | [`07_stack_parentheses.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Exam_Output_Codes/07_stack_parentheses.cpp) | `{[()]}` is BALANCED, `{[(])}` is UNBALANCED |
| **08** | **Circular Queue** | [`08_circular_queue.cpp`](file:///d:/Projects/DS_notes/Data-Structures-Practical-Codebook/Exam_Output_Codes/08_circular_queue.cpp) | Full 5/5 $\rightarrow$ Dequeue 2 $\rightarrow$ Enqueue 2 (reusing slots 0 and 1 via `% MAX`) |

---

## ⚡ How to Compile & Run Any Program

```bash
# Example: Compile and run Program 1
g++ -std=c++14 -Wall -Wextra 01_array_insert_delete_search.cpp -o app
./app
```

All 8 programs compile cleanly with **0 errors and 0 warnings**.
