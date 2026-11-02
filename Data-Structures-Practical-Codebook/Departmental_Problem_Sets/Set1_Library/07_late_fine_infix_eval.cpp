/**
 * ============================================================================
 * SET 1: LIBRARY MANAGEMENT SYSTEM (Part B - Problem 2)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to evaluate the late-fine calculation formula:
 *     (Days * Rate) + Fixed - Waiver
 *   a. Convert infix expression to postfix using a stack
 *   b. Accept values for Days, Rate, Fixed, Waiver and evaluate using a stack
 * ============================================================================
 * ALGORITHM:
 *   1. Variables: D = Days, R = Rate, F = Fixed, W = Waiver.
 *      Infix: (D * R) + F - W
 *   2. Infix to Postfix:
 *      - If operand, append to postfix string.
 *      - If '(', push to operator stack.
 *      - If ')', pop from stack to output until '(' is met. Pop '('.
 *      - If operator (+, -, *, /): pop operators with >= precedence, then push.
 *   3. Postfix Evaluation:
 *      - Scan postfix from left to right.
 *      - If operand letter, substitute numerical value and push to operand stack.
 *      - If operator, pop op2, pop op1, compute (op1 op op2), and push result.
 *      - Return top element as final late fine.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// Character Stack for Infix to Postfix Conversion
class CharStack {
private:
    char arr[50];
    int top;
public:
    CharStack() : top(-1) {}
    bool isEmpty() { return top == -1; }
    void push(char c) { arr[++top] = c; }
    char pop() { return arr[top--]; }
    char peek() { return arr[top]; }
};

// Float Stack for Postfix Evaluation
class FloatStack {
private:
    float arr[50];
    int top;
public:
    FloatStack() : top(-1) {}
    bool isEmpty() { return top == -1; }
    void push(float val) { arr[++top] = val; }
    float pop() { return arr[top--]; }
};

int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// a. Convert Infix to Postfix
string infixToPostfix(string infix) {
    CharStack s;
    string postfix = "";

    for (size_t i = 0; i < infix.length(); ++i) {
        char ch = infix[i];
        if (isspace(ch)) continue;

        if (isalnum(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();
            }
            if (!s.isEmpty()) s.pop(); // Pop '('
        } else {
            // Operator
            while (!s.isEmpty() && getPrecedence(s.peek()) >= getPrecedence(ch)) {
                postfix += s.pop();
            }
            s.push(ch);
        }
    }

    while (!s.isEmpty()) {
        postfix += s.pop();
    }
    return postfix;
}

// b. Evaluate Postfix Expression
float evaluatePostfix(string postfix, float D, float R, float F, float W) {
    FloatStack s;

    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];
        if (isspace(ch)) continue;

        if (isalpha(ch)) {
            float val = 0.0f;
            if (ch == 'D') val = D;
            else if (ch == 'R') val = R;
            else if (ch == 'F') val = F;
            else if (ch == 'W') val = W;
            s.push(val);
        } else {
            float op2 = s.pop(); // Right operand
            float op1 = s.pop(); // Left operand
            float res = 0.0f;

            if (ch == '+') res = op1 + op2;
            else if (ch == '-') res = op1 - op2;
            else if (ch == '*') res = op1 * op2;
            else if (ch == '/') res = op1 / op2;

            s.push(res);
        }
    }
    return s.pop();
}

int main() {
    cout << "==============================================================\n";
    cout << "  SET 1 (PART B - PROBLEM 2): LATE-FINE FORMULA INFIX TO POSTFIX\n";
    cout << "==============================================================\n";

    string infixFormula = "(D * R) + F - W";
    cout << "Late-Fine Formula : (Days * Rate) + Fixed - Waiver\n";
    cout << "Infix Notation    : " << infixFormula << "\n";

    // a. Convert to Postfix
    string postfix = infixToPostfix(infixFormula);
    cout << "Postfix Notation  : " << postfix << "\n\n";

    // b. Accept input values
    float days = 12.0f;
    float rate = 5.0f;
    float fixedCharge = 50.0f;
    float waiver = 20.0f;

    cout << "Accepted Parameter Values:\n";
    cout << "  Late Days (D)    : " << days << " days\n";
    cout << "  Daily Rate (R)   : Rs " << rate << " per day\n";
    cout << "  Fixed Charge (F) : Rs " << fixedCharge << "\n";
    cout << "  Waiver (W)       : Rs " << waiver << "\n";

    // Evaluate
    float totalFine = evaluatePostfix(postfix, days, rate, fixedCharge, waiver);
    cout << "\n>>> TOTAL PAYABLE LATE FINE: Rs " << fixed << setprecision(2) << totalFine << " <<<\n";

    return 0;
}
