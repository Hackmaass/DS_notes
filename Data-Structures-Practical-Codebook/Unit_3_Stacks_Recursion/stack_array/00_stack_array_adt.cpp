/*
========================================================================================
PROGRAM HEADER:
- Program Number: 00-StackArray
- Program Title: Stack Abstract Data Type (ADT) using Contiguous Array
- Unit: Unit III - Stack and Recursion
- Relevant Curriculum Topic: Stack Definition, Operations, LIFO Principle, Array Implementation
- Course Code: CE25PCC-202 (Theory Core) & CE25PCC-203 (Laboratory Foundation)
- Objective:
  Implement a complete Stack ADT using a fixed-size array with all fundamental operations:
  push, pop, peek, isEmpty, isFull, and stack display, with robust boundary checking.
- Data Structure Used: Static Integer Array with integer `top` index.
- What This Program Demonstrates:
  LIFO (Last-In, First-Out) discipline, pointer-index management, overflow and underflow
  detection, and constant-time O(1) operations.
========================================================================================

CONCEPT: WHAT IS A STACK AND WHY DO WE NEED IT?
A Stack is a restricted linear data structure that follows the LIFO (Last In, First Out) principle.
This means that insertion and deletion can take place at ONLY ONE END, called the `top`.

REAL-WORLD ANALOGY:
Think of a vertical stack of dinner plates in a cafeteria:
- You add a clean plate on top (`push`).
- You pick up a plate from the top (`pop`).
- You can look at the topmost plate without removing it (`peek`).
- You never pull a plate out from the bottom or middle, as that would cause the stack to collapse!

WHY DO WE INITIALIZE `top = -1`?
In C++, array indices start at 0.
- When the stack contains 1 element, it resides at index 0 (`top = 0`).
- Therefore, when the stack is completely empty, `top` must point to a location BEFORE index 0,
  which is `-1`!

SYSTEM APPLICATIONS:
- Undo / Redo mechanisms in text editors.
- Function call execution stack (managing activation records and local variables).
- Expression evaluation and syntax parsing in compilers.
- Depth-First Search (DFS) in graph algorithms.
*/

#include <iostream>
#include <iomanip>

using namespace std;

// Maximum physical capacity of the stack array
const int MAX_STACK = 5;

class ArrayStack {
private:
    int items[MAX_STACK]; // Contiguous memory storage
    int top;              // Index of the topmost element

public:
    // Constructor: Initializes empty stack state
    ArrayStack() {
        top = -1; // -1 indicates stack has zero elements
    }

    /*
    ALGORITHM: IS EMPTY
    1. Check if `top == -1`.
    2. If true, return true (stack is empty). Else return false.
    */
    bool isEmpty() const {
        return top == -1;
    }

    /*
    ALGORITHM: IS FULL
    1. Check if `top == MAX_STACK - 1`.
    2. If true, return true (no free slots remaining). Else return false.
    */
    bool isFull() const {
        return top == MAX_STACK - 1;
    }

    /*
    ALGORITHM: PUSH
    1. Check if stack is full: `if (isFull())`.
       If true, report Stack Overflow and return false.
    2. Increment top: `top++;`
       WHY INCREMENT FIRST?
       Because `top` currently holds the index of the last occupied slot.
       The next free slot is at `top + 1`.
    3. Store new value: `items[top] = value;`
    4. Report success and return true.
    */
    bool push(int value) {
        if (isFull()) {
            cout << "[ERROR] Stack Overflow! Capacity (" << MAX_STACK 
                 << ") reached. Cannot push " << value << ".\n";
            return false;
        }

        top++;               // Step 2: Advance top index
        items[top] = value;  // Step 3: Insert element into newly opened slot
        cout << ">> PUSH: [" << value << "] pushed onto stack. Top is now at index " << top << ".\n";
        return true;
    }

    /*
    ALGORITHM: POP
    1. Check if stack is empty: `if (isEmpty())`.
       If true, report Stack Underflow and return -1.
    2. Retrieve topmost element: `poppedVal = items[top];`
    3. Decrement top: `top--;`
       WHY DECREMENT TOP?
       We do not physically erase the data in RAM; simply decrementing `top` logically
       removes the element, making that slot available for future overwrites.
    4. Return `poppedVal`.
    */
    int pop() {
        if (isEmpty()) {
            cout << "[ERROR] Stack Underflow! Stack is completely empty. Cannot pop.\n";
            return -1;
        }

        int poppedVal = items[top]; // Retrieve current top
        top--;                      // Logically shrink the stack
        cout << ">> POP:  [" << poppedVal << "] popped from stack. Top is now at index " << top << ".\n";
        return poppedVal;
    }

    /*
    ALGORITHM: PEEK
    1. Check if stack is empty: `if (isEmpty())`.
       If true, report error and return -1.
    2. Return `items[top]` WITHOUT decrementing `top`.
    */
    int peek() const {
        if (isEmpty()) {
            cout << "[ERROR] Cannot peek into an empty stack.\n";
            return -1;
        }
        return items[top];
    }

    /*
    ALGORITHM: DISPLAY STACK
    1. Check if empty. If so, print "[EMPTY]" and return.
    2. Print stack vertically from `top` down to `0`.
       WHY FROM TOP DOWN TO 0?
       To visually reinforce the LIFO structure (top plate seen first!).
    */
    void display() const {
        if (isEmpty()) {
            cout << "\n   [STACK STATUS: EMPTY]\n";
            return;
        }

        cout << "\n   --- CURRENT STACK CONTENTS (TOP TO BOTTOM) ---\n";
        for (int i = top; i >= 0; i--) {
            cout << "   | " << setw(4) << items[i] << " |";
            if (i == top) {
                cout << " <-- TOP (Index " << i << ")";
            }
            cout << "\n";
        }
        cout << "   +------+\n";
        cout << "   Elements Count: " << (top + 1) << " / " << MAX_STACK << "\n\n";
    }
};

// Interactive demonstration runner
int main() {
    ArrayStack myStack;

    cout << "==============================================================\n";
    cout << "   STACK ABSTRACT DATA TYPE (ARRAY IMPLEMENTATION)           \n";
    cout << "==============================================================\n";

    // 1. Initial State Check
    cout << "\n--- DEMO STEP 1: Inspecting empty stack ---\n";
    cout << "Is stack empty? " << (myStack.isEmpty() ? "YES" : "NO") << "\n";
    myStack.display();

    // 2. Testing Underflow
    cout << "--- DEMO STEP 2: Testing Underflow condition on empty stack ---\n";
    myStack.pop();

    // 3. Pushing elements
    cout << "\n--- DEMO STEP 3: Pushing elements (10, 20, 30, 40) ---\n";
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);
    myStack.push(40);
    myStack.display();

    // 4. Peeking
    cout << "--- DEMO STEP 4: Peeking at top element ---\n";
    cout << "Top element via peek(): [" << myStack.peek() << "] (Stack remains unchanged)\n";

    // 5. Testing Overflow
    cout << "\n--- DEMO STEP 5: Pushing 5th element and triggering Overflow ---\n";
    myStack.push(50); // Fills 5th slot
    myStack.display();
    cout << "Attempting to push 6th element (60) into full stack:\n";
    myStack.push(60); // Triggers Overflow error!

    // 6. Popping elements (LIFO demonstration)
    cout << "\n--- DEMO STEP 6: Popping elements (LIFO Demonstration) ---\n";
    cout << "Notice that elements come out in REVERSE order of insertion:\n";
    myStack.pop(); // Removes 50
    myStack.pop(); // Removes 40
    myStack.display();

    cout << "==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
Push 10, Push 20, Push 30, Push 40, Push 50 -> Stack full.
Push 60 -> Overflow.
Pop -> 50 (last in, first out).
Pop -> 40.

SAMPLE OUTPUT:
==============================================================
   STACK ABSTRACT DATA TYPE (ARRAY IMPLEMENTATION)           
==============================================================

--- DEMO STEP 1: Inspecting empty stack ---
Is stack empty? YES

   [STACK STATUS: EMPTY]
--- DEMO STEP 2: Testing Underflow condition on empty stack ---
[ERROR] Stack Underflow! Stack is completely empty. Cannot pop.

--- DEMO STEP 3: Pushing elements (10, 20, 30, 40) ---
>> PUSH: [10] pushed onto stack. Top is now at index 0.
>> PUSH: [20] pushed onto stack. Top is now at index 1.
>> PUSH: [30] pushed onto stack. Top is now at index 2.
>> PUSH: [40] pushed onto stack. Top is now at index 3.

   --- CURRENT STACK CONTENTS (TOP TO BOTTOM) ---
   |   40 | <-- TOP (Index 3)
   |   30 |
   |   20 |
   |   10 |
   +------+
   Elements Count: 4 / 5

--- DEMO STEP 4: Peeking at top element ---
Top element via peek(): [40] (Stack remains unchanged)

--- DEMO STEP 5: Pushing 5th element and triggering Overflow ---
>> PUSH: [50] pushed onto stack. Top is now at index 4.

   --- CURRENT STACK CONTENTS (TOP TO BOTTOM) ---
   |   50 | <-- TOP (Index 4)
   |   40 |
   |   30 |
   |   20 |
   |   10 |
   +------+
   Elements Count: 5 / 5

Attempting to push 6th element (60) into full stack:
[ERROR] Stack Overflow! Capacity (5) reached. Cannot push 60.

--- DEMO STEP 6: Popping elements (LIFO Demonstration) ---
Notice that elements come out in REVERSE order of insertion:
>> POP:  [50] popped from stack. Top is now at index 3.
>> POP:  [40] popped from stack. Top is now at index 2.

   --- CURRENT STACK CONTENTS (TOP TO BOTTOM) ---
   |   30 | <-- TOP (Index 2)
   |   20 |
   |   10 |
   +------+
   Elements Count: 3 / 5

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

TIME COMPLEXITY:
- `push()`:    O(1) - direct index assignment `items[++top] = val`.
- `pop()`:     O(1) - direct index decrement `return items[top--]`.
- `peek()`:    O(1) - direct access `return items[top]`.
- `isEmpty()`: O(1) - single boolean check `top == -1`.
- `isFull()`:  O(1) - single boolean check `top == MAX - 1`.
- `display()`: O(N) - visits each of the active elements from top to 0.

SPACE COMPLEXITY:
- Auxiliary Space: O(1).
- Total Space: O(MAX_STACK) contiguous memory.

WHY?
Because top represents a direct numeric index. No searching or element shifting
is ever required.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Pre-increment vs Post-increment in Push:
   - Must increment BEFORE assigning: `top++; items[top] = value;`
   - If you write `items[top] = value; top++;`, you will write into `items[-1]` on
     the first push (Memory Corruption / Segmentation Fault!).
2. Post-decrement vs Pre-decrement in Pop:
   - Must read value BEFORE decrementing: `val = items[top]; top--;`
   - If you decrement first, you read the wrong element below the top!
3. Forgetting Overflow Check:
   - Pushing when `top == MAX - 1` overwrites memory outside array bounds.
========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Stack initialization: `top = -1;`
[ ] 2. Overflow condition: `if (top == MAX - 1)`
[ ] 3. Underflow condition: `if (top == -1)`
[ ] 4. Push: `items[++top] = val;`
[ ] 5. Pop: `return items[top--];`
[ ] 6. Peek: `return items[top];`
========================================================================================
*/
