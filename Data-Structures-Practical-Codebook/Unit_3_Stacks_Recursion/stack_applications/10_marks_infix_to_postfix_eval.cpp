/*
========================================================================================
PROGRAM HEADER:
- Program Number: 10
- Program Title: Marks Calculation Formula - Infix to Postfix Conversion & Evaluation
- Unit: Unit III - Stack and Recursion
- Relevant Curriculum Topic: Stack Applications (Expression Conversion & Evaluation)
- Course Code: CE25PCC-203 (Data Structures Laboratory) - Group C, Assignment 10
- Problem Statement:
  Given a marks calculation formula (infix), write a program to:
  a. Convert infix expression to postfix
  b. Evaluate postfix expression for given inputs
- Data Structures Used:
  1. Custom Character Stack for Operators (Conversion Phase)
  2. Custom Floating-Point Stack for Operands (Evaluation Phase)
  *(Manual stack implementations without using `std::stack`)*
- What This Program Demonstrates:
  Dijkstra's Shunting-Yard conversion algorithm, operator precedence, associativity rules,
  parentheses resolution, and linear single-pass postfix stack evaluation.
========================================================================================

CONCEPT: WHY CONVERT INFIX TO POSTFIX?
1. Infix Notation:
   - Operators sit BETWEEN operands: `(Theory + Practical) * Weightage - Deduction`.
   - Natural for humans, but a nightmare for computer hardware to evaluate!
   - Why? Because to evaluate an infix expression, a computer must repeatedly scan
     forward and backward to respect operator precedence (`*` before `+`) and nested parentheses.

2. Postfix Notation (Reverse Polish Notation - RPN):
   - Operators FOLLOW their operands: `Theory Practical + Weightage * Deduction -`.
   - ADVANTAGE 1: Requires ZERO parentheses! The order of evaluation is completely unambiguous.
   - ADVANTAGE 2: Can be evaluated in a SINGLE linear pass from left to right using an
     operand stack in O(N) time!
   - Every modern compiler, calculator (HP), and virtual machine (JVM / Python bytecode)
     converts source code expressions into postfix/bytecode before evaluation.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

const int MAX_STACK = 100;

// ====================================================================================
// 1. MANUAL CHARACTER STACK FOR OPERATOR STORAGE DURING CONVERSION
// ====================================================================================
class CharStack {
private:
    char data[MAX_STACK];
    int topIndex;

public:
    CharStack() { topIndex = -1; }

    bool isEmpty() const { return topIndex == -1; }
    bool isFull() const { return topIndex == MAX_STACK - 1; }

    void push(char c) {
        if (!isFull()) {
            data[++topIndex] = c;
        }
    }

    char pop() {
        if (!isEmpty()) {
            return data[topIndex--];
        }
        return '\0';
    }

    char peek() const {
        if (!isEmpty()) {
            return data[topIndex];
        }
        return '\0';
    }
};

// ====================================================================================
// 2. MANUAL FLOAT STACK FOR NUMERIC VALUES DURING EVALUATION
// ====================================================================================
class FloatStack {
private:
    float data[MAX_STACK];
    int topIndex;

public:
    FloatStack() { topIndex = -1; }

    bool isEmpty() const { return topIndex == -1; }
    bool isFull() const { return topIndex == MAX_STACK - 1; }

    void push(float val) {
        if (!isFull()) {
            data[++topIndex] = val;
        }
    }

    float pop() {
        if (!isEmpty()) {
            return data[topIndex--];
        }
        return 0.0f;
    }

    float peek() const {
        if (!isEmpty()) {
            return data[topIndex];
        }
        return 0.0f;
    }
};

// Returns operator precedence rank (Higher number = Higher priority)
int getPrecedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0; // For '(' and non-operators
}

// Check if character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

/*
ALGORITHM 1: INFIX TO POSTFIX CONVERSION (Shunting-Yard)
1. Initialize an empty operator stack `CharStack opStack` and empty result string `postfix`.
2. Iterate character `c` across the infix string:
   CASE A: If `c` is alphanumeric (Operand: letter or digit):
           Append `c` directly to `postfix`.
   CASE B: If `c == '('` (Left parenthesis):
           Push `c` onto `opStack`.
   CASE C: If `c == ')'` (Right parenthesis):
           Pop operators from `opStack` and append to `postfix` until `opStack.peek() == '('`.
           Pop and discard the matching `'('`.
   CASE D: If `c` is an operator (`+`, `-`, `*`, `/`, `^`):
           While `!opStack.isEmpty()` AND `getPrecedence(opStack.peek()) >= getPrecedence(c)`:
               (Exception: `^` is right-associative, so strictly `>` for `^`):
               Append `opStack.pop()` to `postfix`.
           Push current operator `c` onto `opStack`.
3. After string is completely scanned:
   Pop any remaining operators from `opStack` and append to `postfix`.
4. Return `postfix`.
*/
string infixToPostfix(const string &infix) {
    CharStack opStack;
    string postfix = "";

    cout << "\n   [Infix to Postfix Step-by-Step Conversion]\n";
    cout << "   " << left << setw(8)  << "Token"
         << setw(24) << "Current Postfix"
         << "Action / Stack State\n";
    cout << "   ------------------------------------------------------------\n";

    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];

        // Ignore whitespace
        if (c == ' ') continue;

        // Case A: Operand (Alphanumeric variable/number)
        if (isalnum(c)) {
            postfix += c;
            cout << "   " << left << setw(8)  << c
                 << setw(24) << postfix
                 << "Operand -> Appended to output\n";
        }
        // Case B: Left Parenthesis
        else if (c == '(') {
            opStack.push(c);
            cout << "   " << left << setw(8)  << c
                 << setw(24) << postfix
                 << "Pushed '(' onto operator stack\n";
        }
        // Case C: Right Parenthesis
        else if (c == ')') {
            while (!opStack.isEmpty() && opStack.peek() != '(') {
                postfix += opStack.pop();
            }
            if (!opStack.isEmpty() && opStack.peek() == '(') {
                opStack.pop(); // Discard '('
            }
            cout << "   " << left << setw(8)  << c
                 << setw(24) << postfix
                 << "Popped operators until '('\n";
        }
        // Case D: Operator
        else if (isOperator(c)) {
            while (!opStack.isEmpty() && opStack.peek() != '(' &&
                   (getPrecedence(opStack.peek()) > getPrecedence(c) ||
                   (getPrecedence(opStack.peek()) == getPrecedence(c) && c != '^'))) {
                postfix += opStack.pop();
            }
            opStack.push(c);
            cout << "   " << left << setw(8)  << c
                 << setw(24) << postfix
                 << "Pushed '" << c << "' onto operator stack\n";
        }
    }

    // Pop all remaining operators
    while (!opStack.isEmpty()) {
        postfix += opStack.pop();
    }

    cout << "   ------------------------------------------------------------\n";
    cout << "   Final Postfix Output: " << postfix << "\n\n";
    return postfix;
}

/*
ALGORITHM 2: POSTFIX EXPRESSION EVALUATION
Input: `postfix` string, and numeric values for variables.
1. Initialize an empty operand stack: `FloatStack numStack`.
2. Scan `postfix` string character by character:
   CASE A: If `c` is an operand variable:
           Look up its assigned floating-point value and push onto `numStack`.
   CASE B: If `c` is an operator (`+`, `-`, `*`, `/`, `^`):
           a. Pop operand 2: `val2 = numStack.pop();`
              WHY OPERAND 2 FIRST?
              Because in LIFO, the right operand was pushed LAST!
           b. Pop operand 1: `val1 = numStack.pop();`
           c. Apply operation: `result = val1 (op) val2`.
              (Order is critical for non-commutative operations like `-` and `/`!).
           d. Push `result` back onto `numStack`.
3. At the end of the scan, `numStack` contains exactly ONE element: the final result!
4. Return `numStack.pop()`.
*/
float evaluatePostfix(const string &postfix, float valT, float valP, float valW, float valD) {
    FloatStack numStack;

    cout << "   [Postfix Evaluation Execution Trace]\n";
    cout << "   " << left << setw(8)  << "Token"
         << setw(30) << "Operation Performed"
         << "Stack Top\n";
    cout << "   ------------------------------------------------------------\n";

    for (size_t i = 0; i < postfix.length(); i++) {
        char c = postfix[i];

        if (isalpha(c)) {
            float val = 0.0f;
            if (c == 'T' || c == 't') val = valT;
            else if (c == 'P' || c == 'p') val = valP;
            else if (c == 'W' || c == 'w') val = valW;
            else if (c == 'D' || c == 'd') val = valD;
            else val = 1.0f;

            numStack.push(val);
            cout << "   " << left << setw(8)  << c
                 << setw(30) << ("Pushed variable " + string(1, c) + " = " + to_string(val).substr(0,4))
                 << fixed << setprecision(2) << numStack.peek() << "\n";
        }
        else if (isOperator(c)) {
            // First pop gives the second operand
            float val2 = numStack.pop();
            // Second pop gives the first operand
            float val1 = numStack.pop();
            float res = 0.0f;

            switch (c) {
                case '+': res = val1 + val2; break;
                case '-': res = val1 - val2; break;
                case '*': res = val1 * val2; break;
                case '/': 
                    if (val2 != 0.0f) res = val1 / val2;
                    else { cout << "[ERROR] Division by zero!\n"; res = 0.0f; }
                    break;
                case '^': res = pow(val1, val2); break;
            }

            numStack.push(res);
            string opDesc = to_string(val1).substr(0,4) + " " + c + " " + to_string(val2).substr(0,4) + " = " + to_string(res).substr(0,4);
            cout << "   " << left << setw(8)  << c
                 << setw(30) << opDesc
                 << fixed << setprecision(2) << res << "\n";
        }
    }

    float finalResult = numStack.pop();
    cout << "   ------------------------------------------------------------\n";
    cout << "   Final Evaluated Result = " << fixed << setprecision(2) << finalResult << "\n\n";
    return finalResult;
}

// Interactive demonstration runner
int main() {
    cout << "==============================================================\n";
    cout << "   MARKS CALCULATION: INFIX TO POSTFIX CONVERSION & EVAL      \n";
    cout << "==============================================================\n";

    // Standard marks calculation formula:
    // Final Marks = (Theory + Practical) * Weightage - Deduction
    // Variable Representation: (T + P) * W - D
    string infixFormula = "(T + P) * W - D";

    cout << "\n--- STEP 1: Given Infix Marks Formula ---\n";
    cout << "Formula: " << infixFormula << "\n";
    cout << "Where:\n";
    cout << "  T = Theory Exam Marks\n";
    cout << "  P = Practical Lab Marks\n";
    cout << "  W = Semester Weightage Factor\n";
    cout << "  D = Late Submission Deduction\n";

    // 1. Convert Infix to Postfix
    cout << "\n--- STEP 2: Converting Infix to Postfix using Operator Stack ---\n";
    string postfixFormula = infixToPostfix(infixFormula);

    // 2. Input values for student marks
    float theory = 45.0f;
    float practical = 35.0f;
    float weightage = 1.2f;
    float deduction = 5.0f;

    cout << "--- STEP 3: Student Input Parameters ---\n";
    cout << "Theory Marks (T)    : " << theory << " / 60\n";
    cout << "Practical Marks (P) : " << practical << " / 40\n";
    cout << "Weightage (W)       : " << weightage << "\n";
    cout << "Deduction (D)       : " << deduction << "\n\n";

    // 3. Evaluate Postfix Expression
    cout << "--- STEP 4: Evaluating Postfix Expression using Operand Stack ---\n";
    float finalScore = evaluatePostfix(postfixFormula, theory, practical, weightage, deduction);

    // 4. Verification Check
    float expected = (theory + practical) * weightage - deduction;
    cout << "======================= AUDIT VERIFICATION =======================\n";
    cout << " Expected Value via Direct Infix Math : " << expected << "\n";
    cout << " Computed Value via Postfix Evaluation : " << finalScore << "\n";
    if (abs(finalScore - expected) < 0.001f) {
        cout << " [STATUS: PASS] Expression evaluation matches mathematical ground truth!\n";
    }
    cout << "==================================================================\n\n";

    cout << "==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
Infix Formula: (T + P) * W - D
Input Values: T = 45, P = 35, W = 1.2, D = 5

Conversion Steps:
1. '(' -> pushed to stack
2. 'T' -> output: T
3. '+' -> pushed to stack
4. 'P' -> output: T P
5. ')' -> pop until '(': output: T P +
6. '*' -> pushed to stack
7. 'W' -> output: T P + W
8. '-' -> '*' has higher precedence than '-', so '*' pops: output: T P + W *
          '-' pushed to stack
9. 'D' -> output: T P + W * D
10. End of string: pop remaining: output: T P + W * D -

Evaluation:
- Push T (45), Push P (35)
- Operator '+': Pop 35, Pop 45 -> 45 + 35 = 80. Push 80.
- Push W (1.2)
- Operator '*': Pop 1.2, Pop 80 -> 80 * 1.2 = 96. Push 96.
- Push D (5)
- Operator '-': Pop 5, Pop 96 -> 96 - 5 = 91. Push 91.
Result: 91.00.

SAMPLE OUTPUT:
==============================================================
   MARKS CALCULATION: INFIX TO POSTFIX CONVERSION & EVAL      
==============================================================

--- STEP 1: Given Infix Marks Formula ---
Formula: (T + P) * W - D
Where:
  T = Theory Exam Marks
  P = Practical Lab Marks
  W = Semester Weightage Factor
  D = Late Submission Deduction

--- STEP 2: Converting Infix to Postfix using Operator Stack ---

   [Infix to Postfix Step-by-Step Conversion]
   Token   Current Postfix         Action / Stack State
   ------------------------------------------------------------
   (                               Pushed '(' onto operator stack
   T       T                       Operand -> Appended to output
   +       T                       Pushed '+' onto operator stack
   P       TP                      Operand -> Appended to output
   )       TP+                     Popped operators until '('
   *       TP+                     Pushed '*' onto operator stack
   W       TP+W                    Operand -> Appended to output
   -       TP+W*                   Pushed '-' onto operator stack
   D       TP+W*D                  Operand -> Appended to output
   ------------------------------------------------------------
   Final Postfix Output: TP+W*D-

--- STEP 3: Student Input Parameters ---
Theory Marks (T)    : 45 / 60
Practical Marks (P) : 35 / 40
Weightage (W)       : 1.2
Deduction (D)       : 5

--- STEP 4: Evaluating Postfix Expression using Operand Stack ---
   [Postfix Evaluation Execution Trace]
   Token   Operation Performed           Stack Top
   ------------------------------------------------------------
   T       Pushed variable T = 45.0      45.00
   P       Pushed variable P = 35.0      35.00
   +       45.0 + 35.0 = 80.0            80.00
   W       Pushed variable W = 1.20      1.20
   *       80.0 * 1.20 = 96.0            96.00
   D       Pushed variable D = 5.00      5.00
   -       96.0 - 5.00 = 91.0            91.00
   ------------------------------------------------------------
   Final Evaluated Result = 91.00

======================= AUDIT VERIFICATION =======================
 Expected Value via Direct Infix Math : 91
 Computed Value via Postfix Evaluation : 91.00
 [STATUS: PASS] Expression evaluation matches mathematical ground truth!
==================================================================

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

TIME COMPLEXITY:
- Infix to Postfix Conversion: O(N)
  * Every character is pushed at most once and popped at most once.
- Postfix Evaluation: O(N)
  * Single linear scan across all tokens in the postfix string.
- Total Time: O(N), where N is the length of the expression.

SPACE COMPLEXITY:
- Conversion: O(N) auxiliary space for operator stack and postfix output string.
- Evaluation: O(N) auxiliary space for operand float stack.

WHY?
Because the algorithm visits each token exactly once, eliminating nested rescanning.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Reversing Operand Order in Subtraction/Division (CRITICAL):
   - In evaluation, `val2 = pop()` is the RIGHT operand, and `val1 = pop()` is the LEFT operand.
   - If you compute `val2 - val1` or `val2 / val1`, your result is completely WRONG!
     Must compute `val1 - val2` and `val1 / val2`.
2. Missing Remaining Stack Drain:
   - Forgetting to empty all remaining operators from `opStack` after the string loop ends!
3. Precedence Handling of Parentheses:
   - When an operator is being pushed, `(` in the stack must NOT be popped!
     Give `(` precedence 0 inside the stack.
========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Precedence function: `^: 3`, `* /: 2`, `+ -: 1`, default: `0`.
[ ] 2. Conversion:
       - If operand: `postfix += c;`
       - If `(`: `push(c);`
       - If `)`: `while(peek() != '(') postfix += pop(); pop();`
       - If operator: `while(precedence(peek()) >= precedence(c)) postfix += pop(); push(c);`
[ ] 3. Postfix eval:
       - `val2 = pop(); val1 = pop();`
       - `res = val1 (op) val2;`
       - `push(res);`
========================================================================================
*/
