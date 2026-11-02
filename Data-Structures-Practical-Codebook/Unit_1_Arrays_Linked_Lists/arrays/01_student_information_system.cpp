/*
========================================================================================
PROGRAM HEADER:
- Program Number: 01
- Program Title: Student Information System using Array
- Unit: Unit I - Introduction to Data Structures and Memory Representation
- Relevant Curriculum Topic: Array Operations (Insertion, Deletion, Search, Traversal)
- Course Code: CE25PCC-203 (Data Structures Laboratory) - Group A, Assignment 1
- Problem Statement:
  Write a program for the Student Information System which stores details of N students
  (Roll No, Name, CGPA). Write functions for the following:
  a. Insert a new student at a given position
  b. Delete a student by roll number
  c. Search a student by roll number and display the record
  d. Display all students stored in the array
- Data Structure Used: Static Contiguous Array of Structures (`struct Student`)
- What This Program Demonstrates:
  Manual memory shifting on insertion/deletion, boundary validation, linear search,
  and logical size vs capacity management.
========================================================================================

CONCEPT: WHY ARE WE USING AN ARRAY HERE?
An array stores elements in contiguous (adjacent) memory locations.
When we know the upper bound of students (e.g., maximum batch size of 50 or 100),
an array provides:
1. Instant Direct Access: Any record at index `i` can be accessed in O(1) time
   using address calculation: Base_Address + i * sizeof(Student).
2. Cache Locality: Because records sit shoulder-to-shoulder in RAM, iterating
   through all students is extremely fast.
3. Simplicity: No extra pointer memory overhead (unlike linked lists where every
   node stores an additional 8-byte pointer).

TRADE-OFF / COST:
- Inserting at position `pos` requires shifting all subsequent elements right by 1.
- Deleting at position `pos` requires shifting all subsequent elements left by 1.
- Size is physically fixed at compile-time (`MAX_STUDENTS`).
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Maximum physical capacity of our array.
// In practical exams, always define a constant capacity.
const int MAX_CAPACITY = 50;

// Structure representing a single student record.
// A struct groups heterogeneous data items into a single user-defined type.
struct Student {
    int rollNo;      // Unique integer identifier
    string name;     // Student's full name
    float cgpa;      // Academic performance metric (0.0 to 10.0)
};

/*
ALGORITHM 1: INSERT AT POSITION (1-based position)
1. Check if the array is full (`size >= MAX_CAPACITY`). If yes, print Overflow and return.
2. Validate position: Ensure `position >= 1` and `position <= size + 1`.
   If invalid, report error and return.
3. Convert 1-based position to 0-based array index: `insertIndex = position - 1`.
4. Shift elements to the right to make space:
   Loop index `i` from `size - 1` down to `insertIndex`:
       `students[i + 1] = students[i];`
   WHY SHIFT BACKWARDS?
   If we shift forward (left-to-right), we would overwrite `students[i + 1]` before
   saving its original value, corrupting the subsequent data!
5. Place the new student record into `students[insertIndex]`.
6. Increment logical count of students: `size++`.
7. Report successful insertion.
*/
bool insertStudentAtPosition(Student students[], int &size, int position, const Student &newStudent) {
    // Step 1: Check capacity overflow
    if (size >= MAX_CAPACITY) {
        cout << "[ERROR] Array Overflow! Cannot insert. Maximum capacity (" 
             << MAX_CAPACITY << ") reached.\n";
        return false;
    }

    // Step 2: Boundary check for insertion position
    // Valid positions are from 1 (insert at front) up to size + 1 (insert at end)
    if (position < 1 || position > size + 1) {
        cout << "[ERROR] Invalid position! Position must be between 1 and " 
             << (size + 1) << ".\n";
        return false;
    }

    int insertIndex = position - 1; // 1-based to 0-based conversion

    // Step 4: Shift elements right from the tail
    // Memory visual: [0][1][2] -> create room at [1] -> copy [2] to [3], copy [1] to [2]
    for (int i = size - 1; i >= insertIndex; i--) {
        students[i + 1] = students[i];
    }

    // Step 5: Assign the new student record to the newly freed slot
    students[insertIndex] = newStudent;

    // Step 6: Expand logical size
    size++;
    cout << ">> Success: Student with Roll No " << newStudent.rollNo 
         << " inserted at position " << position << ".\n";
    return true;
}

/*
ALGORITHM 2: SEARCH BY ROLL NUMBER (Linear Search)
1. Iterate through array from index `i = 0` to `size - 1`.
2. Compare `students[i].rollNo` with target `searchRoll`.
3. If a match is found:
   Return index `i`.
4. If loop completes without match:
   Return -1 (indicating record does not exist).
*/
int searchStudentByRoll(const Student students[], int size, int searchRoll) {
    for (int i = 0; i < size; i++) {
        // Compare target key with stored roll number
        if (students[i].rollNo == searchRoll) {
            return i; // Found at index i
        }
    }
    return -1; // Not found
}

/*
ALGORITHM 3: DELETE BY ROLL NUMBER
1. Search for `targetRoll` in array using `searchStudentByRoll()`.
2. If index returned is -1, student does not exist; display error and return.
3. If found at index `delIndex`:
   Shift all elements from `delIndex + 1` up to `size - 1` to the left by 1 position:
       `students[i] = students[i + 1];`
   WHY SHIFT FORWARDS (LEFTWARDS)?
   To fill the hole left by the deleted student and maintain contiguous storage.
4. Decrement logical count: `size--`.
5. Report successful deletion.
*/
bool deleteStudentByRoll(Student students[], int &size, int targetRoll) {
    if (size == 0) {
        cout << "[ERROR] Array Underflow! Database is currently empty.\n";
        return false;
    }

    int delIndex = searchStudentByRoll(students, size, targetRoll);
    if (delIndex == -1) {
        cout << "[ERROR] Student with Roll No " << targetRoll << " not found!\n";
        return false;
    }

    string removedName = students[delIndex].name;

    // Shift elements leftward to overwrite deleted slot
    for (int i = delIndex; i < size - 1; i++) {
        students[i] = students[i + 1];
    }

    // Shrink logical size
    size--;
    cout << ">> Success: Student " << removedName << " (Roll: " << targetRoll 
         << ") successfully deleted.\n";
    return true;
}

/*
ALGORITHM 4: DISPLAY ALL STUDENTS
1. Check if `size == 0`. If empty, notify user and return.
2. Print tabular header with columns: Index, Position, Roll No, Name, CGPA.
3. Loop from index `0` to `size - 1`:
   Print formatted student details.
*/
void displayAllStudents(const Student students[], int size) {
    if (size == 0) {
        cout << "\n[INFO] Student records array is empty.\n";
        return;
    }

    cout << "\n--------------------------------------------------------------\n";
    cout << left << setw(8) << "Index" 
         << setw(10) << "Pos" 
         << setw(12) << "Roll No" 
         << setw(22) << "Name" 
         << setw(8)  << "CGPA" << "\n";
    cout << "--------------------------------------------------------------\n";

    for (int i = 0; i < size; i++) {
        cout << left << setw(8)  << i
             << setw(10) << (i + 1)
             << setw(12) << students[i].rollNo
             << setw(22) << students[i].name
             << fixed << setprecision(2) << setw(8) << students[i].cgpa << "\n";
    }
    cout << "--------------------------------------------------------------\n";
    cout << "Total Active Students: " << size << " / " << MAX_CAPACITY << "\n\n";
}

// Interactive demonstration runner
int main() {
    Student registry[MAX_CAPACITY];
    int currentSize = 0;

    cout << "==============================================================\n";
    cout << "   STUDENT INFORMATION SYSTEM (ARRAY IMPLEMENTATION)        \n";
    cout << "==============================================================\n";

    // 1. Initial Populate: Inserting 4 foundational student records
    cout << "\n--- DEMO STEP 1: Inserting initial records at end positions ---\n";
    insertStudentAtPosition(registry, currentSize, 1, {101, "Aarav Sharma", 8.85f});
    insertStudentAtPosition(registry, currentSize, 2, {102, "Bhavna Patil", 9.10f});
    insertStudentAtPosition(registry, currentSize, 3, {104, "Chetan Joshi", 7.95f});
    insertStudentAtPosition(registry, currentSize, 4, {105, "Divya Kulkarni", 8.40f});

    displayAllStudents(registry, currentSize);

    // 2. Demonstration of Position-based insertion in the middle
    cout << "--- DEMO STEP 2: Inserting a student at Position 3 (Middle) ---\n";
    cout << "Notice that Chetan and Divya will be shifted right to index 3 and 4.\n";
    insertStudentAtPosition(registry, currentSize, 3, {103, "Aditya Deshmukh", 9.45f});
    displayAllStudents(registry, currentSize);

    // 3. Search Demonstration
    cout << "--- DEMO STEP 3: Searching for Roll No 103 ---\n";
    int foundIdx = searchStudentByRoll(registry, currentSize, 103);
    if (foundIdx != -1) {
        cout << ">> Found at Index [" << foundIdx << "] (Position " << (foundIdx + 1) << "):\n";
        cout << "   Roll: " << registry[foundIdx].rollNo 
             << " | Name: " << registry[foundIdx].name 
             << " | CGPA: " << registry[foundIdx].cgpa << "\n";
    }

    // 4. Deletion Demonstration
    cout << "\n--- DEMO STEP 4: Deleting Student by Roll No 102 ---\n";
    deleteStudentByRoll(registry, currentSize, 102);
    displayAllStudents(registry, currentSize);

    // 5. Boundary Testing: Invalid Position
    cout << "--- DEMO STEP 5: Testing boundary error (Invalid Position 10) ---\n";
    insertStudentAtPosition(registry, currentSize, 10, {106, "Esha Verma", 8.00f});

    // 6. Non-existent deletion test
    cout << "\n--- DEMO STEP 6: Testing deletion of non-existent Roll No 999 ---\n";
    deleteStudentByRoll(registry, currentSize, 999);

    cout << "\n==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
(Automatic interactive sequence executed by main):
1. Insert Roll 101, Name "Aarav Sharma", CGPA 8.85 at Pos 1
2. Insert Roll 102, Name "Bhavna Patil", CGPA 9.10 at Pos 2
3. Insert Roll 104, Name "Chetan Joshi", CGPA 7.95 at Pos 3
4. Insert Roll 105, Name "Divya Kulkarni", CGPA 8.40 at Pos 4
5. Insert Roll 103, Name "Aditya Deshmukh", CGPA 9.45 at Pos 3 (Intermediate Shift)
6. Search Roll 103 -> Found at Index 2
7. Delete Roll 102 -> Elements at index 2..3 shift left
8. Insert at invalid Pos 10 -> Handled gracefully

SAMPLE OUTPUT:
==============================================================
   STUDENT INFORMATION SYSTEM (ARRAY IMPLEMENTATION)        
==============================================================

--- DEMO STEP 1: Inserting initial records at end positions ---
>> Success: Student with Roll No 101 inserted at position 1.
>> Success: Student with Roll No 102 inserted at position 2.
>> Success: Student with Roll No 104 inserted at position 3.
>> Success: Student with Roll No 105 inserted at position 4.

--------------------------------------------------------------
Index   Pos       Roll No     Name                  CGPA    
--------------------------------------------------------------
0       1         101         Aarav Sharma          8.85    
1       2         102         Bhavna Patil          9.10    
2       3         104         Chetan Joshi          7.95    
3       4         105         Divya Kulkarni        8.40    
--------------------------------------------------------------
Total Active Students: 4 / 50

--- DEMO STEP 2: Inserting a student at Position 3 (Middle) ---
Notice that Chetan and Divya will be shifted right to index 3 and 4.
>> Success: Student with Roll No 103 inserted at position 3.

--------------------------------------------------------------
Index   Pos       Roll No     Name                  CGPA    
--------------------------------------------------------------
0       1         101         Aarav Sharma          8.85    
1       2         102         Bhavna Patil          9.10    
2       3         103         Aditya Deshmukh       9.45    
3       4         104         Chetan Joshi          7.95    
4       5         105         Divya Kulkarni        8.40    
--------------------------------------------------------------
Total Active Students: 5 / 50

--- DEMO STEP 3: Searching for Roll No 103 ---
>> Found at Index [2] (Position 3):
   Roll: 103 | Name: Aditya Deshmukh | CGPA: 9.45

--- DEMO STEP 4: Deleting Student by Roll No 102 ---
>> Success: Student Bhavna Patil (Roll: 102) successfully deleted.

--------------------------------------------------------------
Index   Pos       Roll No     Name                  CGPA    
--------------------------------------------------------------
0       1         101         Aarav Sharma          8.85    
1       2         103         Aditya Deshmukh       9.45    
2       3         104         Chetan Joshi          7.95    
3       4         105         Divya Kulkarni        8.40    
--------------------------------------------------------------
Total Active Students: 4 / 50

--- DEMO STEP 5: Testing boundary error (Invalid Position 10) ---
[ERROR] Invalid position! Position must be between 1 and 5.

--- DEMO STEP 6: Testing deletion of non-existent Roll No 999 ---
[ERROR] Student with Roll No 999 not found!

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

STEP-BY-STEP DRY RUN: INSERTION AT POSITION 3
Initial Array:
Index:   0            1            2            3
Data:  [101, Aarav] [102, Bhavna] [104, Chetan] [105, Divya]
Size = 4. Target Pos = 3 (InsertIndex = 2).

Shift Loop (i from 3 down to 2):
1. i = 3: students[4] = students[3] (Divya moves to index 4)
   Array: [101] [102] [104] [105] [105]
2. i = 2: students[3] = students[2] (Chetan moves to index 3)
   Array: [101] [102] [104] [104] [105]
Loop ends.
Slot at index 2 is now free to overwrite!
students[2] = [103, Aditya]
Array: [101] [102] [103] [104] [105]
Size increments: size = 5.

----------------------------------------------------------------------------------------
STEP-BY-STEP DRY RUN: DELETION BY ROLL 102
Target Roll = 102.
Search finds target at delIndex = 1.
Shift Loop (i from 1 to size - 2, i.e., 1 to 3):
1. i = 1: students[1] = students[2] ([103, Aditya] moves to index 1)
   Array: [101] [103] [103] [104] [105]
2. i = 2: students[2] = students[3] ([104, Chetan] moves to index 2)
   Array: [101] [103] [104] [104] [105]
3. i = 3: students[3] = students[4] ([105, Divya] moves to index 3)
   Array: [101] [103] [104] [105] [105]
Loop ends.
Size decrements: size = 4.
Logical view only reads up to index 3! [101, 103, 104, 105].

========================================================================================
TIME COMPLEXITY:
- Insertion at Position:
  * Best case: O(1) - when inserting at the very end (`position == size + 1`), no shifts.
  * Worst case: O(N) - when inserting at position 1 (`insertIndex == 0`), all N elements shift.
  * Average case: O(N) - on average, N/2 elements shift.
- Deletion by Roll Number:
  * Best case: O(1) search + O(1) shift - if element is at the last index.
  * Worst case: O(N) - if element is at index 0 or not found (N comparisons + N shifts).
  * Average case: O(N).
- Search by Roll Number:
  * Best case: O(1) - target is at index 0.
  * Worst case: O(N) - target is at index N-1 or absent.
  * Average case: O(N).
- Display: O(N) - visits each of the N active students once.

SPACE COMPLEXITY:
- Auxiliary Space: O(1) auxiliary space (operations happen in-place).
- Fixed Storage Space: O(MAX_CAPACITY) contiguous memory allocated for the array.

WHY?
Contiguous memory forces manual shifting of elements to preserve sequential order
without leaving empty gaps.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Off-By-One in Shift Loop (CRITICAL):
   - In insertion: Forgetting to loop backwards (`i = size - 1 down to insertIndex`).
     Looping forward (`i = insertIndex to size - 1`) will overwrite every element with
     the first shifted element!
   - In deletion: Shifting beyond `size - 1`. If `i < size`, `students[i + 1]` reads
     uninitialized garbage memory outside the logical size.
2. Forgetting 1-Based to 0-Based Conversion:
   - When a user asks for "Position 1", they mean index `0`. Always use `insertIndex = position - 1`.
3. Forgetting Logical Size Update:
   - Forgetting `size++` after insertion or `size--` after deletion corrupts subsequent
     operations.
4. Missing Overflow Check:
   - Always check `size >= MAX_CAPACITY` before shifting; otherwise, `students[i + 1]`
     leads to memory corruption (segmentation fault / buffer overrun).

========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Define `struct Student { int rollNo; string name; float cgpa; };`
[ ] 2. Pass `int &size` BY REFERENCE in `insertStudentAtPosition` and `deleteStudentByRoll`.
[ ] 3. Insertion shift: `for (int i = size - 1; i >= insertIndex; i--) students[i + 1] = students[i];`
[ ] 4. Deletion shift: `for (int i = delIndex; i < size - 1; i++) students[i] = students[i + 1];`
[ ] 5. Search loop: simple `for (int i = 0; i < size; i++) if (arr[i].roll == key) return i; return -1;`
[ ] 6. Always decrement `size--` on delete and increment `size++` on insert.
========================================================================================
*/
