/**
 * ============================================================================
 * SET 1: LIBRARY MANAGEMENT SYSTEM (Part B - Problem 4)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program for the Library Fine Billing System to compute final fine.
 *   a. Read fine formula in infix form
 *   b. Convert infix into postfix using a stack
 *   c. Display postfix expression
 *   d. Accept values for LateDays, DailyRate, DamageCharge, and Waiver
 *   e. Evaluate postfix expression using a stack
 *   f. Display final payable fine
 *   g. Also display intermediate stack contents during conversion and evaluation
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// Stack displaying internal state
class CharStackWithTrace {
private:
    char arr[50];
    int top;
public:
    CharStackWithTrace() : top(-1) {}
    bool isEmpty() { return top == -1; }
    void push(char c) { arr[++top] = c; }
    char pop() { return arr[top--]; }
    char peek() { return arr[top]; }
    void print() {
        cout << "[ ";
        for (int i = 0; i <= top; ++i) cout << arr[i] << " ";
        cout << "]";
    }
};

class FloatStackWithTrace {
private:
    float arr[50];
    int top;
public:
    FloatStackWithTrace() : top(-1) {}
    bool isEmpty() { return top == -1; }
    void push(float val) { arr[++top] = val; }
    float pop() { return arr[top--]; }
    void print() {
        cout << "[ ";
        for (int i = 0; i <= top; ++i) cout << fixed << setprecision(1) << arr[i] << " ";
        cout << "]";
    }
};

int getPrec(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string convertToPostfixWithTrace(string infix) {
    CharStackWithTrace s;
    string postfix = "";

    cout << "\n--- Infix to Postfix Conversion with Stack Trace ---\n";
    cout << left << setw(8) << "Token" << setw(18) << "Operator Stack" << "Postfix Output\n";
    cout << "----------------------------------------------------\n";

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
            if (!s.isEmpty()) s.pop();
        } else {
            while (!s.isEmpty() && getPrec(s.peek()) >= getPrec(ch)) {
                postfix += s.pop();
            }
            s.push(ch);
        }

        cout << left << setw(8) << ch;
        s.print();
        cout << " " << postfix << "\n";
    }

    while (!s.isEmpty()) {
        postfix += s.pop();
        cout << left << setw(8) << "END ";
        s.print();
        cout << " " << postfix << "\n";
    }
    return postfix;
}

float evaluateWithTrace(string postfix, float D, float R, float C, float W) {
    FloatStackWithTrace s;

    cout << "\n--- Postfix Evaluation with Intermediate Stack Trace ---\n";
    cout << left << setw(8) << "Token" << setw(12) << "Operand Stack" << "Operation\n";
    cout << "--------------------------------------------------------\n";

    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];
        if (isspace(ch)) continue;

        if (isalpha(ch)) {
            float val = 0.0f;
            if (ch == 'D') val = D;
            else if (ch == 'R') val = R;
            else if (ch == 'C') val = C;
            else if (ch == 'W') val = W;

            s.push(val);
            cout << left << setw(8) << ch;
            s.print();
            cout << " Push " << val << "\n";
        } else {
            float op2 = s.pop();
            float op1 = s.pop();
            float res = 0.0f;

            if (ch == '+') res = op1 + op2;
            else if (ch == '-') res = op1 - op2;
            else if (ch == '*') res = op1 * op2;
            else if (ch == '/') res = op1 / op2;

            s.push(res);
            cout << left << setw(8) << ch;
            s.print();
            cout << " Compute: " << op1 << " " << ch << " " << op2 << " = " << res << "\n";
        }
    }
    return s.pop();
}

int main() {
    cout << "==============================================================\n";
    cout << "  SET 1 (PART B - PROBLEM 4): LIBRARY FINE BILLING SYSTEM\n";
    cout << "==============================================================\n";

    // a. Infix formula: (LateDays * DailyRate) + DamageCharge - Waiver
    string formula = "(D * R) + C - W";
    cout << "Infix Formula: (LateDays * DailyRate) + DamageCharge - Waiver\n";
    cout << "Tokenized    : " << formula << "\n";

    // b & c. Convert to postfix and display
    string postfix = convertToPostfixWithTrace(formula);
    cout << "\nFinal Postfix Expression: " << postfix << "\n";

    // d. Accept parameters
    float lateDays = 10.0f;
    float dailyRate = 5.0f;
    float damageCharge = 150.0f;
    float waiver = 30.0f;

    cout << "\nParameters Accepted:\n";
    cout << "  Late Days (D)     : " << lateDays << "\n";
    cout << "  Daily Rate (R)    : Rs " << dailyRate << "\n";
    cout << "  Damage Charge (C) : Rs " << damageCharge << "\n";
    cout << "  Waiver (W)        : Rs " << waiver << "\n";

    // e, f, g. Evaluate with intermediate trace & print final fine
    float finalFine = evaluateWithTrace(postfix, lateDays, dailyRate, damageCharge, waiver);
    cout << "\n>>> FINAL PAYABLE FINE: Rs " << fixed << setprecision(2) << finalFine << " <<<\n";

    return 0;
}
