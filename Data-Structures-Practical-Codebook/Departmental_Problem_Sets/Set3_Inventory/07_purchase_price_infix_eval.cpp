/**
 * ============================================================================
 * Departmental Problem Set 3 (Inventory) - Problem 7
 * Program: Purchase Price Infix to Postfix Conversion and Evaluation
 * ============================================================================
 * Problem Statement:
 *   Evaluate inventory purchase pricing formulas using Stack ADT:
 *   - Formula Example: (C * Q) + S - D
 *     Where C = Cost, Q = Quantity, S = Shipping, D = Discount.
 *   - Convert infix expression to postfix notation.
 *   - Evaluate postfix expression with numeric inputs using stack.
 * ============================================================================
 */

#include <iostream>
#include <string>
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

double evaluatePostfix(const string& postfix, double C, double Q, double S, double D) {
    NumStack s;

    for (char c : postfix) {
        if (c == 'C') s.push(C);
        else if (c == 'Q') s.push(Q);
        else if (c == 'S') s.push(S);
        else if (c == 'D') s.push(D);
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
    cout << "=== Purchase Price Infix to Postfix & Evaluation ===\n\n";

    // Variables: C = Cost (250), Q = Qty (10), S = Shipping (100), D = Discount (50)
    double C = 250.0;
    double Q = 10.0;
    double S = 100.0;
    double D = 50.0;

    string formula = "(C*Q)+S-D";

    cout << "Purchase Formula (Infix) : " << formula << "\n";
    cout << "Given Parameter Values   : C=" << C << ", Q=" << Q 
         << ", S=" << S << ", D=" << D << "\n";

    string postfix = infixToPostfix(formula);
    cout << "Generated Postfix String : " << postfix << "\n";

    double netPurchasePrice = evaluatePostfix(postfix, C, Q, S, D);

    cout << "\nCalculated Net Purchase Price: Rs. " << netPurchasePrice << "\n";
    cout << "Step Breakdown: (250 * 10) = 2500 -> 2500 + 100 = 2600 -> 2600 - 50 = Rs. 2550\n";

    return 0;
}
