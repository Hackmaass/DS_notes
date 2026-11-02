/*
========================================================================================
PROGRAM HEADER:
- Program Number: 11
- Program Title: Parenthesis Checking in Expressions using Stack
- Unit: Unit III - Stack and Recursion
- Relevant Curriculum Topic: Stack Applications (Delimiter Matching / Balanced Parentheses)
- Course Code: CE25PCC-203 (Data Structures Laboratory) - Group C, Assignment 11
- Problem Statement:
  Write a Program for Parenthesis checking in an expression using stack.
- Data Structure Used: Custom Character Stack (`class CharStack`)
- What This Program Demonstrates:
  LIFO nested delimiter matching for `()`, `{}`, and `[]`, syntax validation used
  by compilers and code editors, and detection of underflow/overflow imbalances.
========================================================================================

CONCEPT: WHY USE A STACK FOR CHECKING BALANCED PARENTHESES?
Consider the expression: `{ [ ( a + b ) * c ] + d }`
Notice how the parentheses are NESTED:
- The bracket opened LAST is the `(` inside.
- When we reach the first closing bracket, it MUST close the innermost `(`!
- In other words: The delimiter opened LAST must be closed FIRST (LIFO)!
- A Stack is the perfect data structure for this:
  * Whenever an opening delimiter `(`, `{`, `[` is seen: PUSH it.
  * Whenever a closing delimiter `)`, `}`, `]` is seen: POP the most recently opened
    delimiter and verify that they form a matching pair!

THREE FAILURE MODES TO DETECT:
1. Mismatched Pairs: e.g., `( a + b ]` (Popped `(` does not match `]`).
2. Premature Closing (Underflow): e.g., `a + b )` (Stack is empty when `)` is encountered).
3. Unclosed Openings: e.g., `( ( a + b )` (Expression finishes but stack still contains `(`).
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_STACK = 100;

// Custom manual character stack
class CharStack {
private:
    char items[MAX_STACK];
    int topIndex;

public:
    CharStack() { topIndex = -1; }

    bool isEmpty() const { return topIndex == -1; }
    bool isFull() const { return topIndex == MAX_STACK - 1; }

    void push(char c) {
        if (!isFull()) {
            items[++topIndex] = c;
        }
    }

    char pop() {
        if (!isEmpty()) {
            return items[topIndex--];
        }
        return '\0';
    }

    char peek() const {
        if (!isEmpty()) {
            return items[topIndex];
        }
        return '\0';
    }

    void display() const {
        if (isEmpty()) {
            cout << "[Empty]";
            return;
        }
        cout << "[ ";
        for (int i = 0; i <= topIndex; i++) {
            cout << items[i] << " ";
        }
        cout << "]";
    }
};

// Helper function to check if opening and closing brackets match
bool isMatchingPair(char opening, char closing) {
    if (opening == '(' && closing == ')') return true;
    if (opening == '{' && closing == '}') return true;
    if (opening == '[' && closing == ']') return true;
    return false;
}

/*
ALGORITHM: BALANCED PARENTHESIS CHECKER
Input: Expression string `expr`.
1. Initialize an empty `CharStack s`.
2. Loop through each character `c` in `expr`:
   a. If `c == '(' || c == '{' || c == '['`:
      Push `c` onto `s`.
   b. Else if `c == ')' || c == '}' || c == ']'`:
      - If `s.isEmpty()`:
        Return FALSE (Failure Mode 2: Closing bracket with no opening partner).
      - Pop top bracket: `topBracket = s.pop();`
      - If `!isMatchingPair(topBracket, c)`:
        Return FALSE (Failure Mode 1: Mismatched bracket types).
3. After the entire string has been scanned:
   - If `s.isEmpty()`:
     Return TRUE (All brackets opened have been perfectly matched and closed).
   - Else:
     Return FALSE (Failure Mode 3: Unclosed opening bracket left in stack).
*/
bool checkBalancedParentheses(const string &expr, string &errorReason) {
    CharStack s;

    cout << "\n   [Parenthesis Checking Trace for: \"" << expr << "\"]\n";
    cout << "   " << left << setw(6)  << "Step"
         << setw(10) << "Char"
         << setw(20) << "Action"
         << "Stack State\n";
    cout << "   ------------------------------------------------------------\n";

    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];

        // 1. Opening Delimiters
        if (c == '(' || c == '{' || c == '[') {
            s.push(c);
            cout << "   " << left << setw(6)  << (i + 1)
                 << setw(10) << c
                 << setw(20) << "Pushed Opening";
            s.display();
            cout << "\n";
        }
        // 2. Closing Delimiters
        else if (c == ')' || c == '}' || c == ']') {
            if (s.isEmpty()) {
                errorReason = "Unexpected closing bracket '" + string(1, c) + "' at position " + to_string(i + 1) + " (No matching opening bracket).";
                cout << "   " << left << setw(6) << (i + 1) << setw(10) << c << "FAILED! Stack Underflow.\n";
                return false;
            }

            char topBracket = s.pop();
            if (!isMatchingPair(topBracket, c)) {
                errorReason = "Mismatched pair: Opened with '" + string(1, topBracket) + "' but closed with '" + string(1, c) + "' at position " + to_string(i + 1) + ".";
                cout << "   " << left << setw(6) << (i + 1) << setw(10) << c << "FAILED! Mismatched Pair.\n";
                return false;
            }

            cout << "   " << left << setw(6)  << (i + 1)
                 << setw(10) << c
                 << setw(20) << ("Matched with '" + string(1, topBracket) + "'");
            s.display();
            cout << "\n";
        }
    }

    cout << "   ------------------------------------------------------------\n";

    // 3. Final Stack Check
    if (s.isEmpty()) {
        errorReason = "None. All brackets perfectly balanced.";
        return true;
    } else {
        errorReason = "Unclosed opening bracket '" + string(1, s.peek()) + "' remaining on stack.";
        return false;
    }
}

// Helper test harness
void testExpression(const string &expr, const string &label) {
    cout << "\n>>> TEST CASE: " << label << " <<<\n";
    cout << "Expression: " << expr << "\n";
    string reason;
    bool isBalanced = checkBalancedParentheses(expr, reason);

    if (isBalanced) {
        cout << "   RESULT: [VALID / BALANCED]\n";
    } else {
        cout << "   RESULT: [INVALID / UNBALANCED]\n";
        cout << "   REASON: " << reason << "\n";
    }
}

// Interactive demonstration runner
int main() {
    cout << "==============================================================\n";
    cout << "   PARENTHESIS CHECKING IN EXPRESSIONS (STACK APPLICATION)    \n";
    cout << "==============================================================\n";

    // 1. Perfectly Balanced Expression
    testExpression("{ [ ( a + b ) * ( c - d ) ] / e }", "Valid Multi-Level Nested Brackets");

    // 2. Mismatched Bracket Types
    testExpression("( [ a + b } )", "Mismatched Delimiters (Opened '[' but closed with '}')");

    // 3. Premature Closing (Underflow)
    testExpression("a + b ) * c", "Premature Closing Bracket (No opening bracket)");

    // 4. Unclosed Opening Bracket
    testExpression("{ ( a + b ) * c", "Unclosed Bracket (Missing closing '}')");

    cout << "\n==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
1. "{ [ ( a + b ) * ( c - d ) ] / e }" -> Perfectly Balanced.
2. "( [ a + b } )" -> Mismatched Pair ('[' with '}').
3. "a + b ) * c" -> Premature Closing ')' (Stack empty).
4. "{ ( a + b ) * c" -> Unclosed '{' remains on stack.

SAMPLE OUTPUT:
==============================================================
   PARENTHESIS CHECKING IN EXPRESSIONS (STACK APPLICATION)    
==============================================================

>>> TEST CASE: Valid Multi-Level Nested Brackets <<<
Expression: { [ ( a + b ) * ( c - d ) ] / e }

   [Parenthesis Checking Trace for: "{ [ ( a + b ) * ( c - d ) ] / e }"]
   Step  Char      Action              Stack State
   ------------------------------------------------------------
   1     {         Pushed Opening      [ { ]
   3     [         Pushed Opening      [ { [ ]
   5     (         Pushed Opening      [ { [ ( ]
   13    )         Matched with '('    [ { [ ]
   17    (         Pushed Opening      [ { [ ( ]
   25    )         Matched with '('    [ { [ ]
   27    ]         Matched with '['    [ { ]
   33    }         Matched with '{'    [Empty]
   ------------------------------------------------------------
   RESULT: [VALID / BALANCED]

>>> TEST CASE: Mismatched Delimiters (Opened '[' but closed with '}') <<<
Expression: ( [ a + b } )

   [Parenthesis Checking Trace for: "( [ a + b } )"]
   Step  Char      Action              Stack State
   ------------------------------------------------------------
   1     (         Pushed Opening      [ ( ]
   3     [         Pushed Opening      [ ( [ ]
   11    }         FAILED! Mismatched Pair.
   RESULT: [INVALID / UNBALANCED]
   REASON: Mismatched pair: Opened with '[' but closed with '}' at position 11.

>>> TEST CASE: Premature Closing Bracket (No opening bracket) <<<
Expression: a + b ) * c

   [Parenthesis Checking Trace for: "a + b ) * c"]
   Step  Char      Action              Stack State
   ------------------------------------------------------------
   7     )         FAILED! Stack Underflow.
   RESULT: [INVALID / UNBALANCED]
   REASON: Unexpected closing bracket ')' at position 7 (No matching opening bracket).

>>> TEST CASE: Unclosed Bracket (Missing closing '}') <<<
Expression: { ( a + b ) * c

   [Parenthesis Checking Trace for: "{ ( a + b ) * c"]
   Step  Char      Action              Stack State
   ------------------------------------------------------------
   1     {         Pushed Opening      [ { ]
   3     (         Pushed Opening      [ { ( ]
   11    )         Matched with '('    [ { ]
   ------------------------------------------------------------
   RESULT: [INVALID / UNBALANCED]
   REASON: Unclosed opening bracket '{' remaining on stack.

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

TIME COMPLEXITY:
- O(N) where N is the length of the string.
  * Every character is processed once.
  * Each opening delimiter is pushed onto the stack at most once (O(1)).
  * Each closing delimiter pops at most one element (O(1)).

SPACE COMPLEXITY:
- Auxiliary Space: O(N) worst case (e.g., expression with all opening brackets `(((((((`).

WHY?
Because the nesting of brackets has a strict hierarchical LIFO relationship:
the most recently opened scope must be resolved first.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Forgetting Final Empty Check (CRITICAL):
   - Merely checking that no mismatches occurred during the loop is NOT ENOUGH!
   - For example: `( ( a + b )` will never trigger a mismatch inside the loop,
     but it is UNBALANCED because one `(` is left over.
     Always verify `s.isEmpty()` at the end!
2. Missing Underflow Check:
   - If user inputs `a + b )`, popping an empty stack without checking `isEmpty()`
     causes a crash or reads uninitialized garbage memory.
3. Ignoring Non-bracket Characters:
   - Operators, variables, and spaces must be completely ignored.
========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Openers `( { [`: `s.push(c);`
[ ] 2. Closers `) } ]`:
       - `if (s.isEmpty()) return false;`
       - `char top = s.pop();`
       - `if (!match(top, c)) return false;`
[ ] 3. End of string: `return s.isEmpty();`
========================================================================================
*/
