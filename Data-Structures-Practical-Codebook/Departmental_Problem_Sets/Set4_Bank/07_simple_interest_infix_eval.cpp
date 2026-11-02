/**
 * ============================================================================
 * Departmental Problem Set 4 (Bank) - Problem 7
 * Program: Simple Interest Infix to Postfix Conversion and Evaluation
 * ============================================================================
 * Problem Statement:
 *   Evaluate banking loan interest formulas using Stack ADT:
 *   - Formula Example: (P * R * T) / H
 *     Where P = Principal, R = Rate, T = Time, H = 100 (Hundred).
 *   - Convert infix expression to postfix notation.
 *   - Evaluate postfix expression with numeric inputs using stack.
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

// Stack for char operators
class CharStack {
private:
    char arr[50];
    int top;
public:
    CharStack() : top(-1) {}
    void push(char c) { arr[++top] = c; }
    char pop() { return arr[top--]; }
    char peek() const { return arr[top]; }
    bool isEmpty() const { return top == -1; }
};

// Stack for numeric evaluation
class NumStack {
private:
    double arr[50];
    int top;
public:
    NumStack() : top(-1) {}
    void push(double v) { arr[++top] = v; }
    double pop() { return arr[top--]; }
    bool isEmpty() const { return top == -1; }
};

int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

string infixToPostfix(const string& infix) {
    CharStack s;
    string postfix = "";

    for (char c : infix) {
        if (c == ' ') continue;

        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();
            }
            if (!s.isEmpty()) s.pop(); // Pop '('
        } else if (isOperator(c)) {
            while (!s.isEmpty() && getPrecedence(s.peek()) >= getPrecedence(c)) {
                postfix += s.pop();
            }
            s.push(c);
        }
    }

    while (!s.isEmpty()) {
        postfix += s.pop();
    }

    return postfix;
}

double evaluatePostfix(const string& postfix, double P, double R, double T, double H) {
    NumStack s;

    for (char c : postfix) {
        if (c == 'P') s.push(P);
        else if (c == 'R') s.push(R);
        else if (c == 'T') s.push(T);
        else if (c == 'H') s.push(H);
        else if (isdigit(c)) s.push(c - '0');
        else if (isOperator(c)) {
            double val2 = s.pop();
            double val1 = s.pop();
            switch (c) {
                case '+': s.push(val1 + val2); break;
                case '-': s.push(val1 - val2); break;
                case '*': s.push(val1 * val2); break;
                case '/': s.push(val1 / val2); break;
            }
        }
    }
    return s.pop();
}

int main() {
    cout << "=== Loan Simple Interest Infix to Postfix & Evaluation ===\n\n";

    // Variables: P = Principal (50000), R = Rate (8%), T = Time (3 years), H = Hundred (100)
    double P = 50000.0;
    double R = 8.0;
    double T = 3.0;
    double H = 100.0;

    string formula = "(P*R*T)/H";

    cout << "Simple Interest Formula (Infix) : " << formula << "\n";
    cout << "Parameters: P=Rs." << P << ", R=" << R 
         << "%, T=" << T << " yrs, H=" << H << "\n";

    string postfix = infixToPostfix(formula);
    cout << "Generated Postfix Expression   : " << postfix << "\n";

    double interest = evaluatePostfix(postfix, P, R, T, H);

    cout << "\n============================================\n";
    cout << "  Calculated Simple Interest: Rs. " << fixed << setprecision(2) << interest << "\n";
    cout << "  Total Amount Due (P + SI) : Rs. " << fixed << setprecision(2) << (P + interest) << "\n";
    cout << "============================================\n";

    return 0;
}
