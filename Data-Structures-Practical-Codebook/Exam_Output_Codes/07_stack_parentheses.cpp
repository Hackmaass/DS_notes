/**
 * ============================================================================
 * EXAM PROGRAM 07: STACK (PARENTHESES BALANCING CHECKER)
 * ============================================================================
 * 🧠 60-SECOND EXAM MEMORIZATION TECHNIQUE:
 * 
 * 1. THE 3-STEP ALGORITHM FORMULA:
 *    - Initialize: `char stack[50]; int top = -1;`
 *    - Loop through each character `c` in the string:
 *        1. If OPENING `(`, `{`, `[`:
 *           `stack[++top] = c;` // PUSH
 *        2. If CLOSING `)`, `}`, `]`:
 *           - If `top == -1` -> return `false;` (Premature close!)
 *           - Pop: `char open = stack[top--];`
 *           - Check: If mismatched pair -> return `false;`
 *    - Final Check: `return top == -1;` (Stack MUST be empty!)
 * 
 * 2. THE EXAM PANIC CHECKLIST (The 3 Bugs Examiners Catch):
 *    - TRAP 1: Forgetting `if (top == -1) return false;` before popping.
 *              If the string starts with `)`, `top` is -1. Popping `stack[-1]`
 *              accesses illegal memory and crashes your program!
 *    - TRAP 2: Returning `true` at the end instead of `top == -1`.
 *              If you just write `return true;`, strings like `((()` will be
 *              reported as BALANCED! Only empty stack (`top == -1`) is balanced.
 *    - TRAP 3: Mixing up `++top` and `top--`. Push PRE-increments (`++top`),
 *              Pop POST-decrements (`top--`).
 * 
 * ============================================================================
 * EXPECTED TERMINAL OUTPUT SHOWN TO EXAMINER:
 * 
 * {[()]} : BALANCED
 * {[(])} : UNBALANCED
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

bool isBalanced(const string& s) {
    char stack[50];
    int top = -1; // Top starts at -1 (empty stack)

    for (char c : s) {
        // 1. PUSH any opening bracket
        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        }
        // 2. CHECK any closing bracket
        else if (c == ')' || c == '}' || c == ']') {
            // Failure 1: Closing bracket when stack is empty
            if (top == -1) return false;

            char open = stack[top--]; // POP topmost opening bracket

            // Failure 2: Mismatched bracket types
            if (c == ')' && open != '(') return false;
            if (c == '}' && open != '{') return false;
            if (c == ']' && open != '[') return false;
        }
    }

    // Failure 3: Stack still has unclosed brackets if top != -1
    return (top == -1);
}

int main() {
    string s1 = "{[()]}";
    string s2 = "{[(])}";

    cout << s1 << " : " << (isBalanced(s1) ? "BALANCED" : "UNBALANCED") << "\n";
    cout << s2 << " : " << (isBalanced(s2) ? "BALANCED" : "UNBALANCED") << "\n";

    return 0;
}

/**
 * ============================================================================
 * 🎓 EXAMINER VIVA QUESTIONS & INSTANT ANSWERS:
 * Q: Why must a Stack be used for parenthesis balancing instead of a Queue?
 * A: Because bracket nesting follows LIFO (Last-In, First-Out). The bracket that
 *    opened most recently must be the first one to be closed.
 *
 * Q: What are the 3 conditions that make an expression unbalanced?
 * A: 1. Closing bracket with no opening bracket (stack underflow).
 *    2. Mismatch between the popped opening bracket and closing bracket.
 *    3. Unclosed opening brackets remaining in stack after reading the string.
 * ============================================================================
 */
