/*
========================================================================================
PROGRAM HEADER:
- Program Number: 00-Recursion
- Program Title: Recursion, Stack Frames, and Function Call Mechanism Tracing
- Unit: Unit III - Stack and Recursion
- Relevant Curriculum Topic: Stack Frame, Activation Records, Function Call Mechanism, Recursion
- Course Code: CE25PCC-202 (Theory Core) & CE25PCC-203 (Laboratory Foundation)
- Objective:
  Demonstrate how the CPU's runtime call stack manages recursive function calls through
  activation records (stack frames), tracing both the winding (call) phase and
  the unwinding (return) phase for Factorial and Fibonacci computations.
- Data Structure Used: System Call Stack Simulation alongside recursive C++ functions.
- What This Program Demonstrates:
  Base case vs recursive case, activation record memory layout (parameters, return address,
  local variables), call stack growth, and stack overflow prevention.
========================================================================================

CONCEPT: WHAT IS A STACK FRAME (ACTIVATION RECORD)?
When a function is called in C++, the operating system allocates a temporary block of memory
on the top of the program's Call Stack. This block is called an Activation Record or Stack Frame.

AN ACTIVATION RECORD CONTAINS:
1. Function Parameters: The arguments passed into the function (e.g., `int n`).
2. Return Address: The instruction pointer memory address where execution must resume
   once this function call finishes.
3. Local Variables: Variables declared inside the function's scope.
4. Saved Frame Pointer: Reference to the caller's stack frame.

THE TWO PHASES OF RECURSION:
1. Winding Phase (Forward Call Tree):
   - Each recursive call creates and pushes a BRAND NEW stack frame on top of the call stack.
   - The caller pauses execution and waits for the callee to return.
   - Memory on the call stack grows downwards (or upwards, depending on architecture).
2. Base Case:
   - The stopping condition where no further recursive call is made.
   - Prevents infinite recursion and catastrophic Stack Overflow!
3. Unwinding Phase (Backward Return Chain):
   - The base case returns a value.
   - The topmost stack frame is popped and destroyed.
   - Control jumps back to the saved return address in the caller's frame.
   - Each waiting function completes its computation and returns to its own caller.
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Helper to print call stack depth indentation
void printCallIndent(int depth) {
    for (int i = 0; i < depth; i++) {
        cout << "  │ ";
    }
}

/*
ALGORITHM 1: FACTORIAL WITH EXPLICIT CALL STACK TRACE
Function: `traceFactorial(int n, int depth)`
1. Enter function: A new stack frame for `Factorial(n)` is pushed.
2. BASE CASE CHECK:
   - If `n <= 1`:
     Print base case hit.
     Return 1 immediately.
3. RECURSIVE CASE:
   - Print pause message: `Factorial(n)` must wait for `Factorial(n - 1)`.
   - Make recursive call: `subResult = traceFactorial(n - 1, depth + 1);`
   - Compute multiplication: `result = n * subResult;`
   - Print unwinding return message: Frame is popping with computed result.
   - Return `result`.
*/
long long traceFactorial(int n, int depth) {
    // 1. Winding Phase: Stack frame created
    printCallIndent(depth);
    cout << "┌── [PUSH STACK FRAME] Entering Factorial(n = " << n 
         << ") | Depth = " << depth << "\n";

    // 2. Base Case Condition
    if (n <= 1) {
        printCallIndent(depth);
        cout << "└── [BASE CASE HIT] Factorial(1) returns 1 immediately.\n";
        printCallIndent(depth);
        cout << "    [POP STACK FRAME] Factorial(1) destroyed.\n";
        return 1;
    }

    // 3. Recursive Winding: Caller pauses and invokes child
    printCallIndent(depth);
    cout << "│   Factorial(" << n << ") paused. Waiting for Factorial(" << (n - 1) << ")...\n";

    long long subResult = traceFactorial(n - 1, depth + 1);

    // 4. Unwinding Phase: Child returned, caller resumes computation
    long long finalResult = n * subResult;

    printCallIndent(depth);
    cout << "└── [RESUMING] Factorial(" << n << "): " << n << " * " << subResult 
         << " = " << finalResult << "\n";
    printCallIndent(depth);
    cout << "    [POP STACK FRAME] Factorial(" << n << ") destroyed. Returning " 
         << finalResult << " to caller.\n";

    return finalResult;
}

/*
ALGORITHM 2: FIBONACCI WITH BINARY CALL TREE TRACE
Function: `traceFibonacci(int n, int depth, string branch)`
1. Base case: If `n == 0` return 0; if `n == 1` return 1.
2. Recursive step: `fib(n - 1) + fib(n - 2)`.
   Demonstrates how binary recursion creates a branched call tree.
*/
int traceFibonacci(int n, int depth, const string &branch) {
    printCallIndent(depth);
    cout << "┌── [CALL: " << branch << "] Fib(" << n << ") [Depth " << depth << "]\n";

    if (n == 0) {
        printCallIndent(depth);
        cout << "└── [BASE 0] Returns 0\n";
        return 0;
    }
    if (n == 1) {
        printCallIndent(depth);
        cout << "└── [BASE 1] Returns 1\n";
        return 1;
    }

    // Left child call
    int left = traceFibonacci(n - 1, depth + 1, "Left: Fib(" + to_string(n - 1) + ")");

    // Right child call
    int right = traceFibonacci(n - 2, depth + 1, "Right: Fib(" + to_string(n - 2) + ")");

    int sum = left + right;
    printCallIndent(depth);
    cout << "└── [RETURN] Fib(" << n << ") = " << left << " + " << right << " = " << sum << "\n";
    return sum;
}

// Interactive demonstration runner
int main() {
    cout << "==============================================================\n";
    cout << "   RECURSION, STACK FRAMES, AND CALL MECHANISM TRACER         \n";
    cout << "==============================================================\n";

    // 1. Linear Recursion Demonstration (Factorial of 5)
    int factNum = 5;
    cout << "\n================ 1. LINEAR RECURSION: FACTORIAL(" << factNum << ") ================\n";
    cout << "Tracing activation records on the system runtime stack:\n\n";

    long long factResult = traceFactorial(factNum, 0);

    cout << "\n>> COMPUTATION COMPLETE: " << factNum << "! = " << factResult << "\n";
    cout << "======================================================================\n\n";

    // 2. Binary Tree Recursion Demonstration (Fibonacci of 4)
    int fibNum = 4;
    cout << "================ 2. TREE RECURSION: FIBONACCI(" << fibNum << ") ==================\n";
    cout << "Tracing branching call tree stack frames:\n\n";

    int fibResult = traceFibonacci(fibNum, 0, "Root: Fib(" + to_string(fibNum) + ")");

    cout << "\n>> COMPUTATION COMPLETE: Fibonacci(" << fibNum << ") = " << fibResult << "\n";
    cout << "======================================================================\n";

    cout << "\n==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
Factorial(5):
- Calls: Fact(5) -> Fact(4) -> Fact(3) -> Fact(2) -> Fact(1) [Max stack depth = 5]
- Returns: Fact(1)=1 -> Fact(2)=2 -> Fact(3)=6 -> Fact(4)=24 -> Fact(5)=120.

SAMPLE OUTPUT:
==============================================================
   RECURSION, STACK FRAMES, AND CALL MECHANISM TRACER         
==============================================================

================ 1. LINEAR RECURSION: FACTORIAL(5) ================
Tracing activation records on the system runtime stack:

┌── [PUSH STACK FRAME] Entering Factorial(n = 5) | Depth = 0
│   Factorial(5) paused. Waiting for Factorial(4)...
  │ ┌── [PUSH STACK FRAME] Entering Factorial(n = 4) | Depth = 1
  │ │   Factorial(4) paused. Waiting for Factorial(3)...
  │   │ ┌── [PUSH STACK FRAME] Entering Factorial(n = 3) | Depth = 2
  │   │ │   Factorial(3) paused. Waiting for Factorial(2)...
  │   │   │ ┌── [PUSH STACK FRAME] Entering Factorial(n = 2) | Depth = 3
  │   │   │ │   Factorial(2) paused. Waiting for Factorial(1)...
  │   │   │   │ ┌── [PUSH STACK FRAME] Entering Factorial(n = 1) | Depth = 4
  │   │   │   │ └── [BASE CASE HIT] Factorial(1) returns 1 immediately.
  │   │   │   │     [POP STACK FRAME] Factorial(1) destroyed.
  │   │   │ └── [RESUMING] Factorial(2): 2 * 1 = 2
  │   │   │     [POP STACK FRAME] Factorial(2) destroyed. Returning 2 to caller.
  │   │ └── [RESUMING] Factorial(3): 3 * 2 = 6
  │   │     [POP STACK FRAME] Factorial(3) destroyed. Returning 6 to caller.
  │ └── [RESUMING] Factorial(4): 4 * 6 = 24
  │     [POP STACK FRAME] Factorial(4) destroyed. Returning 24 to caller.
└── [RESUMING] Factorial(5): 5 * 24 = 120
    [POP STACK FRAME] Factorial(5) destroyed. Returning 120 to caller.

>> COMPUTATION COMPLETE: 5! = 120
======================================================================

================ 2. TREE RECURSION: FIBONACCI(4) ==================
Tracing branching call tree stack frames:

┌── [CALL: Root: Fib(4)] Fib(4) [Depth 0]
  │ ┌── [CALL: Left: Fib(3)] Fib(3) [Depth 1]
  │   │ ┌── [CALL: Left: Fib(2)] Fib(2) [Depth 2]
  │   │   │ ┌── [CALL: Left: Fib(1)] Fib(1) [Depth 3]
  │   │   │ └── [BASE 1] Returns 1
  │   │   │ ┌── [CALL: Right: Fib(0)] Fib(0) [Depth 3]
  │   │   │ └── [BASE 0] Returns 0
  │   │ └── [RETURN] Fib(2) = 1 + 0 = 1
  │   │ ┌── [CALL: Right: Fib(1)] Fib(1) [Depth 2]
  │   │ └── [BASE 1] Returns 1
  │ └── [RETURN] Fib(3) = 1 + 1 = 2
  │ ┌── [CALL: Right: Fib(2)] Fib(2) [Depth 1]
  │   │ ┌── [CALL: Left: Fib(1)] Fib(1) [Depth 2]
  │   │ └── [BASE 1] Returns 1
  │   │ ┌── [CALL: Right: Fib(0)] Fib(0) [Depth 2]
  │   │ └── [BASE 0] Returns 0
  │ └── [RETURN] Fib(2) = 1 + 0 = 1
└── [RETURN] Fib(4) = 2 + 1 = 3

>> COMPUTATION COMPLETE: Fibonacci(4) = 3
======================================================================

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

TIME COMPLEXITY:
- Factorial: O(N) linear calls.
- Recursive Fibonacci: O(2^N) exponential calls (repeated overlapping subproblems).

SPACE COMPLEXITY (CALL STACK):
- Factorial Call Stack: O(N) stack frames active at maximum depth.
- Fibonacci Call Stack: O(N) maximum depth along the left spine.

WHY DOES STACK OVERFLOW OCCUR?
If a recursive function lacks a base case, or if the base case condition is never met
(e.g., calling `fact(-1)`), the program continuously pushes stack frames without ever popping.
Eventually, the call stack exceeds the operating system's reserved stack memory limit
(typically 1MB to 8MB in Windows/Linux), causing an immediate segmentation fault
(EXC_BAD_ACCESS / Stack Overflow).

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Missing Base Case:
   - Always place the base case at the VERY FIRST line of the recursive function.
2. Forgetting to Return the Result of the Recursive Call:
   - Writing `fact(n - 1);` without `return n * fact(n - 1);` drops the return value.
3. Modifying Global State Without Need:
   - Keep parameters local to the activation record so each invocation has independent scope.
========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Identify Base Case: `if (n <= 1) return 1;`
[ ] 2. Identify Recursive Step: `return n * factorial(n - 1);`
[ ] 3. Understand call stack winding (pushing frames) vs unwinding (popping & multiplying).
[ ] 4. Call stack memory limit causes Stack Overflow if recursion is unbounded.
========================================================================================
*/
