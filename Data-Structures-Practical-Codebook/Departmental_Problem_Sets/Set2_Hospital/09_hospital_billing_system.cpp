/**
 * ============================================================================
 * SET 2: HOSPITAL MANAGEMENT SYSTEM (Part B - Problem 4)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program for the Hospital Billing System to compute final bill.
 *   a. Read bill formula in infix form
 *   b. Convert infix into postfix using a stack
 *   c. Display postfix expression
 *   d. Accept values for Consultation, RoomCharge, Medicine, Insurance
 *   e. Evaluate postfix expression using a stack
 *   f. Display final payable bill
 *   g. Also display intermediate stack contents during conversion and evaluation
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

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

float evaluateWithTrace(string postfix, float C, float R, float M, float I) {
    FloatStackWithTrace s;

    cout << "\n--- Postfix Evaluation with Intermediate Stack Trace ---\n";
    cout << left << setw(8) << "Token" << setw(14) << "Operand Stack" << "Operation\n";
    cout << "--------------------------------------------------------\n";

    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];
        if (isspace(ch)) continue;

        if (isalpha(ch)) {
            float val = 0.0f;
            if (ch == 'C') val = C;
            else if (ch == 'R') val = R;
            else if (ch == 'M') val = M;
            else if (ch == 'I') val = I;

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
    cout << "  SET 2 (PART B - PROBLEM 4): HOSPITAL BILLING SYSTEM\n";
    cout << "==============================================================\n";

    // Formula: (Consultation + RoomCharge + Medicine) - Insurance
    string formula = "(C + R + M) - I";
    cout << "Infix Formula: (Consultation + RoomCharge + Medicine) - Insurance\n";
    cout << "Tokenized    : " << formula << "\n";

    string postfix = convertToPostfixWithTrace(formula);
    cout << "\nFinal Postfix Expression: " << postfix << "\n";

    float consultation = 2500.0f;
    float roomCharge = 8000.0f;
    float medicine = 4500.0f;
    float insurance = 5000.0f;

    cout << "\nParameters Accepted:\n";
    cout << "  Consultation (C) : Rs " << consultation << "\n";
    cout << "  Room Charge (R)  : Rs " << roomCharge << "\n";
    cout << "  Medicine (M)     : Rs " << medicine << "\n";
    cout << "  Insurance (I)    : Rs " << insurance << "\n";

    float finalBill = evaluateWithTrace(postfix, consultation, roomCharge, medicine, insurance);
    cout << "\n>>> FINAL PAYABLE HOSPITAL BILL: Rs " << fixed << setprecision(2) << finalBill << " <<<\n";

    return 0;
}
