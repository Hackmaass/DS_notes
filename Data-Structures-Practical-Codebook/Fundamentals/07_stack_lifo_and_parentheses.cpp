/**
 * ============================================================================
 * FUNDAMENTAL 07: STACK (LIFO ADT & PARENTHESES CHECKER)
 * ============================================================================
 * 👨‍🏫 PROFESSOR'S DEEP-DIVE CONCEPTUAL GUIDE:
 * 
 * 1. THE STACK PHILOSOPHY (LIFO: LAST-IN, FIRST-OUT):
 *    - Mental Model: A stack of dinner plates in a cafeteria.
 *      - You place a new plate on the TOP (`push`).
 *      - You remove the topmost plate first (`pop`).
 *      - The bottom plate was placed first, but is removed LAST.
 *
 * 2. HOW AN ARRAY IMPLEMENTS A STACK:
 *    We keep an integer variable `top`:
 *      - When empty: `top = -1`
 *      - To PUSH(x): Increment top first, then store: `arr[++top] = x;`
 *      - To POP(): Retrieve element, then decrement top: `return arr[top--];`
 *      - To PEEK(): Just read the current top: `return arr[top];`
 *
 * 3. THE PARENTHESIS BALANCING ALGORITHM:
 *    Why is a Stack REQUIRED to check parentheses?
 *    Because nesting follows LIFO order:
 *      The MOST RECENTLY OPENED bracket must be the FIRST ONE CLOSED!
 *      Example: `[ ( { } ) ]`
 *               `{` was opened last, so it must close first!
 *
 *    Three Distinct Failure Conditions to Watch For in Exams:
 *      1. Underflow / Premature Close: A closing bracket appears with no matching opening bracket.
 *         Example: `( ) )` -> Stack is empty when 2nd `)` arrives!
 *      2. Mismatched Bracket Types: An opening bracket is closed by the wrong type.
 *         Example: `( ]` -> `(` popped, but doesn't match `]`!
 *      3. Incomplete / Dangling Open: String ends, but stack is not empty.
 *         Example: `( ( )` -> One `(` remains unclosed!
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

const int MAX_STACK = 25;

/**
 * ----------------------------------------------------------------------------
 * THE STACK ADT CLASS
 * ----------------------------------------------------------------------------
 */
class CharStack {
private:
    char arr[MAX_STACK]; // Static array storage
    int top;             // Index of topmost element (-1 when empty)

public:
    CharStack() : top(-1) {}

    // Check if stack has 0 elements
    bool isEmpty() const { return top == -1; }

    // Check if stack has reached maximum array capacity
    bool isFull() const { return top == MAX_STACK - 1; }

    // PUSH: Add element to top
    void push(char c) {
        if (isFull()) {
            cout << "  [ERROR] Stack Overflow! Capacity exceeded.\n";
            return;
        }
        arr[++top] = c; // Pre-increment: top moves from -1 to 0, then stores c
    }

    // POP: Remove and return topmost element
    char pop() {
        if (isEmpty()) {
            cout << "  [ERROR] Stack Underflow! Stack is empty.\n";
            return '\0';
        }
        return arr[top--]; // Post-decrement: returns arr[top], then top decrements
    }

    // PEEK: Inspect topmost element without removing it
    char peek() const {
        if (isEmpty()) return '\0';
        return arr[top];
    }
};

/**
 * Helper: Validates if opening bracket matches closing bracket
 */
bool isMatchingPair(char open, char close) {
    if (open == '(' && close == ')') return true;
    if (open == '{' && close == '}') return true;
    if (open == '[' && close == ']') return true;
    return false;
}

/**
 * ----------------------------------------------------------------------------
 * THE PARENTHESIS BALANCING ALGORITHM
 * ----------------------------------------------------------------------------
 */
bool isBalanced(const string &expr, string &failureReason) {
    CharStack s;

    for (size_t i = 0; i < expr.length(); i++) {
        char ch = expr[i];

        // 1. If opening bracket, push onto stack
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        }
        // 2. If closing bracket, check stack top
        else if (ch == ')' || ch == '}' || ch == ']') {
            // Failure Condition 1: Stack is empty (no opening bracket exists!)
            if (s.isEmpty()) {
                failureReason = string("Closing '") + ch + "' at position " + to_string(i) + " has no opening match.";
                return false;
            }

            char open = s.pop();
            // Failure Condition 2: Mismatched bracket types
            if (!isMatchingPair(open, ch)) {
                failureReason = string("Mismatched pair: opening '") + open + "' does not match closing '" + ch + "'.";
                return false;
            }
        }
    }

    // Failure Condition 3: Unclosed opening brackets remain on stack
    if (!s.isEmpty()) {
        failureReason = string("Unclosed opening bracket '") + s.peek() + "' left on stack.";
        return false;
    }

    failureReason = "All brackets matched and properly nested.";
    return true;
}

void testExpression(const string &expr) {
    cout << "Expression: " << expr << "\n";
    string reason;
    bool balanced = isBalanced(expr, reason);
    if (balanced) {
        cout << "  -> Result: BALANCED\n  -> Detail: " << reason << "\n\n";
    } else {
        cout << "  -> Result: UNBALANCED\n  -> Detail: " << reason << "\n\n";
    }
}

int main() {
    cout << "========================================================\n";
    cout << "  TEACHER DEMO: STACK ADT & PARENTHESES BALANCING\n";
    cout << "========================================================\n\n";

    // 1. Basic Stack Demonstrations
    cout << "--- 1. Basic Stack Push & Pop Demonstration ---\n";
    CharStack demo;
    demo.push('A');
    demo.push('B');
    demo.push('C');
    cout << "  Pushed: 'A', 'B', 'C'\n";
    cout << "  Top element (peek): " << demo.peek() << "\n";
    cout << "  Popped: " << demo.pop() << " (C came out first - LIFO!)\n";
    cout << "  New top element   : " << demo.peek() << "\n\n";

    // 2. Parentheses Balance Tests
    cout << "--- 2. Parentheses Balancing Algorithm Tests ---\n";
    testExpression("{ [ ( a + b ) * c ] }");     // Correctly balanced
    testExpression("{ [ ( a + b ] ) }");         // Mismatched
    testExpression("( ( a + b )");               // Unclosed open bracket
    testExpression(") a + b (");                 // Starts with closing bracket

    return 0;
}

/**
 * ============================================================================
 * 🎓 VIVA QUESTIONS & ANSWERS FOR THIS CODE:
 * ============================================================================
 * Q1: What are the primary applications of a Stack?
 * A1: 1. Expression Evaluation & Syntax Parsing (Parenthesis matching, Infix to Postfix).
 *     2. Function Call Stack & Recursion tracking in operating systems.
 *     3. Backtracking algorithms (Maze solving, DFS graph traversal).
 *     4. Undo / Redo operations in text editors and browser history.
 *
 * Q2: What is the Time and Space Complexity of Parentheses Balancing?
 * A2: - Time Complexity: O(N) where N is length of string (single linear scan).
 *     - Auxiliary Space: O(N) worst-case when string contains all opening brackets.
 *
 * Q3: What is the difference between `arr[++top]` and `arr[top++]`?
 * A3: - `arr[++top]` (Pre-increment): Increments `top` FIRST, then uses the new index.
 *       Used in PUSH because top starts at -1 and must become 0 before writing.
 *     - `arr[top++]` (Post-increment): Uses the current index first, then increments.
 *       Using this in push would write to `arr[-1]`, corrupting memory!
 * ============================================================================
 */
