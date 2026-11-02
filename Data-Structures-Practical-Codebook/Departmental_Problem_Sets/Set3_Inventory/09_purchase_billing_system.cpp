/**
 * ============================================================================
 * Departmental Problem Set 3 (Inventory) - Problem 9
 * Program: Purchase Billing System (Infix Evaluation with Stack Trace)
 * ============================================================================
 * Problem Statement:
 *   Complete purchase billing formula evaluator showing:
 *   - Infix to Postfix conversion with step-by-step operator stack snapshots.
 *   - Postfix evaluation with intermediate operand stack contents.
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

// Stack tracking operators
class OperatorStack {
private:
    char arr[50];
    int top;
public:
    OperatorStack() : top(-1) {}
    void push(char c) { arr[++top] = c; }
    char pop() { return arr[top--]; }
    char peek() const { return arr[top]; }
    bool isEmpty() const { return top == -1; }
    string toString() const {
        if (top == -1) return "EMPTY";
        string s = "";
        for (int i = 0; i <= top; i++) s += arr[i];
        return s;
    }
};

// Stack tracking operands
class OperandStack {
private:
    double arr[50];
    int top;
public:
    OperandStack() : top(-1) {}
    void push(double v) { arr[++top] = v; }
    double pop() { return arr[top--]; }
    string toString() const {
        if (top == -1) return "EMPTY";
        string s = "[";
        for (int i = 0; i <= top; i++) {
            s += to_string((int)arr[i]);
            if (i < top) s += ", ";
        }
        s += "]";
        return s;
    }
};

int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

string convertWithTrace(const string& infix) {
    OperatorStack s;
    string postfix = "";

    cout << "\n--- Step 1: Infix to Postfix Conversion Trace ---\n";
    cout << left << setw(8) << "Token" << setw(18) << "Operator Stack" << setw(20) << "Postfix Expression" << "\n";
    cout << "--------------------------------------------------------\n";

    for (char c : infix) {
        if (c == ' ') continue;

        if (isalnum(c)) {
            postfix += c;
            cout << left << setw(8) << c << setw(18) << s.toString() << setw(20) << postfix << "\n";
        } else if (c == '(') {
            s.push(c);
            cout << left << setw(8) << c << setw(18) << s.toString() << setw(20) << postfix << "\n";
        } else if (c == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();
            }
            if (!s.isEmpty()) s.pop(); // Pop '('
            cout << left << setw(8) << c << setw(18) << s.toString() << setw(20) << postfix << "\n";
        } else if (isOperator(c)) {
            while (!s.isEmpty() && getPrecedence(s.peek()) >= getPrecedence(c)) {
                postfix += s.pop();
            }
            s.push(c);
            cout << left << setw(8) << c << setw(18) << s.toString() << setw(20) << postfix << "\n";
        }
    }

    while (!s.isEmpty()) {
        postfix += s.pop();
        cout << left << setw(8) << "END" << setw(18) << s.toString() << setw(20) << postfix << "\n";
    }

    return postfix;
}

double evaluateWithTrace(const string& postfix, double C, double Q, double S, double D) {
    OperandStack s;

    cout << "\n--- Step 2: Postfix Evaluation Trace ---\n";
    cout << left << setw(8) << "Token" << setw(24) << "Operand Stack" << setw(30) << "Operation Performed" << "\n";
    cout << "----------------------------------------------------------------\n";

    for (char c : postfix) {
        if (c == 'C') {
            s.push(C);
            cout << left << setw(8) << c << setw(24) << s.toString() << "Pushed Cost (" << C << ")\n";
        } else if (c == 'Q') {
            s.push(Q);
            cout << left << setw(8) << c << setw(24) << s.toString() << "Pushed Quantity (" << Q << ")\n";
        } else if (c == 'S') {
            s.push(S);
            cout << left << setw(8) << c << setw(24) << s.toString() << "Pushed Shipping (" << S << ")\n";
        } else if (c == 'D') {
            s.push(D);
            cout << left << setw(8) << c << setw(24) << s.toString() << "Pushed Discount (" << D << ")\n";
        } else if (isOperator(c)) {
            double op2 = s.pop();
            double op1 = s.pop();
            double res = 0;
            switch (c) {
                case '+': res = op1 + op2; break;
                case '-': res = op1 - op2; break;
                case '*': res = op1 * op2; break;
                case '/': res = op1 / op2; break;
            }
            s.push(res);
            cout << left << setw(8) << c << setw(24) << s.toString() 
                 << "Evaluated: " << op1 << " " << c << " " << op2 << " = " << res << "\n";
        }
    }

    return s.pop();
}

int main() {
    cout << "=== Purchase Billing Formula Evaluator with Stack Traces ===\n";

    // Variables: C=Unit Cost, Q=Quantity, S=Shipping, D=Discount
    string formula = "(C*Q)+S-D";
    double C = 150.0, Q = 20.0, S = 200.0, D = 100.0;

    cout << "\nInput Infix Formula: " << formula << "\n";
    cout << "Values: Cost(C)=" << C << ", Qty(Q)=" << Q 
         << ", Shipping(S)=" << S << ", Discount(D)=" << D << "\n";

    string postfix = convertWithTrace(formula);
    cout << "\nFinal Postfix Result: " << postfix << "\n";

    double totalBill = evaluateWithTrace(postfix, C, Q, S, D);

    cout << "\n=========================================\n";
    cout << "  Final Invoice Amount: Rs. " << fixed << setprecision(2) << totalBill << "\n";
    cout << "=========================================\n";

    return 0;
}
