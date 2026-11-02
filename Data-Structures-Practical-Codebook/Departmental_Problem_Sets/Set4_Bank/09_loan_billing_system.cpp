/**
 * ============================================================================
 * Departmental Problem Set 4 (Bank) - Problem 9
 * Program: Loan Billing / Repayment System (Infix Evaluation with Stack Trace)
 * ============================================================================
 * Problem Statement:
 *   Complete banking loan interest evaluator showing:
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

double evaluateWithTrace(const string& postfix, double P, double R, double T, double H) {
    OperandStack s;

    cout << "\n--- Step 2: Postfix Evaluation Trace ---\n";
    cout << left << setw(8) << "Token" << setw(24) << "Operand Stack" << setw(30) << "Operation Performed" << "\n";
    cout << "----------------------------------------------------------------\n";

    for (char c : postfix) {
        if (c == 'P') {
            s.push(P);
            cout << left << setw(8) << c << setw(24) << s.toString() << "Pushed Principal (" << P << ")\n";
        } else if (c == 'R') {
            s.push(R);
            cout << left << setw(8) << c << setw(24) << s.toString() << "Pushed Rate (" << R << "%)\n";
        } else if (c == 'T') {
            s.push(T);
            cout << left << setw(8) << c << setw(24) << s.toString() << "Pushed Time (" << T << " yrs)\n";
        } else if (c == 'H') {
            s.push(H);
            cout << left << setw(8) << c << setw(24) << s.toString() << "Pushed Hundred (" << H << ")\n";
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
    cout << "=== Loan Simple Interest Billing System with Stack Traces ===\n";

    // Variables: P=Principal, R=Rate, T=Time, H=100
    string formula = "(P*R*T)/H";
    double P = 60000.0, R = 10.0, T = 2.0, H = 100.0;

    cout << "\nInput Infix Formula: " << formula << "\n";
    cout << "Values: Principal(P)=Rs." << P << ", Rate(R)=" << R 
         << "%, Time(T)=" << T << " yrs, Divisor(H)=" << H << "\n";

    string postfix = convertWithTrace(formula);
    cout << "\nFinal Postfix Result: " << postfix << "\n";

    double interestDue = evaluateWithTrace(postfix, P, R, T, H);

    cout << "\n=========================================\n";
    cout << "  Interest Amount Due  : Rs. " << fixed << setprecision(2) << interestDue << "\n";
    cout << "  Total Loan Repayment : Rs. " << fixed << setprecision(2) << (P + interestDue) << "\n";
    cout << "=========================================\n";

    return 0;
}
