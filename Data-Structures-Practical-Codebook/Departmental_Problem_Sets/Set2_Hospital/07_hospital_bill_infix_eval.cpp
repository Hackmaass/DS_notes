/**
 * ============================================================================
 * SET 2: HOSPITAL MANAGEMENT SYSTEM (Part B - Problem 2)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program to evaluate the hospital bill formula:
 *     (Consultation + Medicine) * Days - Insurance
 *   a. Convert infix expression to postfix using a stack
 *   b. Accept values for Consultation, Medicine, Days, Insurance and evaluate
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

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
            if (!s.isEmpty()) s.pop();
        } else {
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
float evaluateHospitalBill(string postfix, float C, float M, float D, float I) {
    FloatStack s;

    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];
        if (isspace(ch)) continue;

        if (isalpha(ch)) {
            float val = 0.0f;
            if (ch == 'C') val = C;
            else if (ch == 'M') val = M;
            else if (ch == 'D') val = D;
            else if (ch == 'I') val = I;
            s.push(val);
        } else {
            float op2 = s.pop();
            float op1 = s.pop();
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
    cout << "  SET 2 (PART B - PROBLEM 2): HOSPITAL BILL INFIX TO POSTFIX\n";
    cout << "==============================================================\n";

    string formula = "(C + M) * D - I";
    cout << "Hospital Bill Formula : (Consultation + Medicine) * Days - Insurance\n";
    cout << "Infix Notation        : " << formula << "\n";

    // a. Convert to Postfix
    string postfix = infixToPostfix(formula);
    cout << "Postfix Notation      : " << postfix << "\n\n";

    // b. Accepted parameters
    float consultation = 800.0f;
    float medicine = 1200.0f;
    float days = 4.0f;
    float insurance = 3000.0f;

    cout << "Parameters Accepted:\n";
    cout << "  Daily Consultation (C) : Rs " << consultation << "\n";
    cout << "  Daily Medicine (M)     : Rs " << medicine << "\n";
    cout << "  Admission Days (D)     : " << days << " days\n";
    cout << "  Insurance Coverage (I) : Rs " << insurance << "\n";

    // Evaluate
    float totalBill = evaluateHospitalBill(postfix, consultation, medicine, days, insurance);
    cout << "\n>>> FINAL PAYABLE HOSPITAL BILL: Rs " << fixed << setprecision(2) << totalBill << " <<<\n";

    return 0;
}
