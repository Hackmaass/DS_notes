/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit III: Stacks & Recursion
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 4 - Bank Management System (Stack Applications Suite)
 * TITLE:         Bank System: Netbanking Portal, Simple Interest Formula, Loan Parentheses & Billing
 * 
 * PROBLEMS COVERED:
 *   1. Netbanking Portal Navigation History Stack (visit URL, back URL, current, history).
 *   2. Simple Interest Formula `(Principal * Rate * Time) / 100` (Infix to Postfix & Evaluation).
 *   3. Balanced Parentheses in Loan-Eligibility Expression.
 *   4. Loan Billing System with Intermediate Stack Contents Display.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// PROBLEM 1: INTERNET BANKING PORTAL NAVIGATION
class NetbankingPortalStack {
private:
    string history[50];
    int top;
public:
    NetbankingPortalStack() : top(-1) {}
    bool isEmpty() const { return top == -1; }
    void visitPage(const string& url) { history[++top] = url; cout << "  [VISITED] " << url << "\n"; }
    void backPage() {
        if (isEmpty()) return;
        cout << "  [BACK] Navigated back from: " << history[top--] << "\n";
        cout << "  [CURRENT]: " << (isEmpty() ? "Netbanking Dashboard" : history[top]) << "\n";
    }
    void displayHistory() const {
        cout << "  [NETBANKING NAVIGATION HISTORY]:\n";
        for (int i = top; i >= 0; --i) {
            cout << "    [" << (i + 1) << "] " << history[i] 
                 << (i == top ? "  <-- Current Active Tab" : "") << "\n";
        }
    }
};

// PROBLEM 2 & 4: SIMPLE INTEREST FORMULA INFIX TO POSTFIX & EVALUATION
// Formula: (Principal * Rate * Time) / 100
// Mapping: (P * R * T) / H   (where H = 100)
class CharStack {
private:
    char arr[100];
    int top;
public:
    CharStack() : top(-1) {}
    bool isEmpty() const { return top == -1; }
    void push(char c) { arr[++top] = c; }
    char pop() { return arr[top--]; }
    char peek() const { return arr[top]; }
    void printStack() const {
        cout << "[ ";
        for (int i = 0; i <= top; ++i) cout << arr[i] << " ";
        cout << "]";
    }
};

class FloatStack {
private:
    float arr[100];
    int top;
public:
    FloatStack() : top(-1) {}
    bool isEmpty() const { return top == -1; }
    void push(float val) { arr[++top] = val; }
    float pop() { return arr[top--]; }
    void printStack() const {
        cout << "[ ";
        for (int i = 0; i <= top; ++i) cout << fixed << setprecision(1) << arr[i] << " ";
        cout << "]";
    }
};

int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string convertInterestInfixToPostfix(const string& infix) {
    CharStack s;
    string postfix = "";
    cout << "\n  " << left << setw(8) << "Token" << setw(20) << "Operator Stack" << "Postfix Output\n";
    cout << "  --------------------------------------------------------\n";
    for (size_t i = 0; i < infix.length(); ++i) {
        char ch = infix[i];
        if (isspace(ch)) continue;
        if (isalnum(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') postfix += s.pop();
            if (!s.isEmpty()) s.pop();
        } else {
            while (!s.isEmpty() && getPrecedence(s.peek()) >= getPrecedence(ch)) {
                postfix += s.pop();
            }
            s.push(ch);
        }
        cout << "  " << left << setw(8) << ch;
        cout << setw(20);
        s.printStack();
        cout << " " << postfix << "\n";
    }
    while (!s.isEmpty()) {
        postfix += s.pop();
        cout << "  " << left << setw(8) << "END ";
        s.printStack();
        cout << " " << postfix << "\n";
    }
    return postfix;
}

float evaluateInterest(const string& postfix, float P, float R, float T, float H) {
    FloatStack s;
    cout << "\n  --- Interest Evaluation Trace with Intermediate Stack ---\n";
    cout << "  " << left << setw(8) << "Token" << setw(10) << "Value" 
         << setw(25) << "Operand Stack" << "Action\n";
    cout << "  --------------------------------------------------------------------\n";

    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];
        if (isspace(ch)) continue;

        if (isalpha(ch)) {
            float val = 0.0f;
            if (ch == 'P') val = P;
            else if (ch == 'R') val = R;
            else if (ch == 'T') val = T;
            else if (ch == 'H') val = H;

            s.push(val);
            cout << "  " << left << setw(8) << ch << setw(10) << fixed << setprecision(1) << val;
            s.printStack();
            cout << "   Push " << val << "\n";
        } else {
            float op2 = s.pop();
            float op1 = s.pop();
            float res = 0.0f;
            if (ch == '+') res = op1 + op2;
            else if (ch == '-') res = op1 - op2;
            else if (ch == '*') res = op1 * op2;
            else if (ch == '/') res = op1 / op2;

            s.push(res);
            cout << "  " << left << setw(8) << ch << setw(10) << "Operator";
            s.printStack();
            cout << "   Compute: " << op1 << " " << ch << " " << op2 << " = " << res << "\n";
        }
    }
    return s.pop();
}

// PROBLEM 3: LOAN ELIGIBILITY PARENTHESES CHECKER
bool checkLoanParentheses(const string& expr) {
    CharStack s;
    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];
        if (ch == '(' || ch == '{' || ch == '[') s.push(ch);
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.isEmpty()) return false;
            char top = s.pop();
            if (ch == ')' && top != '(') return false;
            if (ch == '}' && top != '{') return false;
            if (ch == ']' && top != '[') return false;
        }
    }
    return s.isEmpty();
}

int main() {
    cout << "====================================================================\n";
    cout << "  SET 4: BANK MANAGEMENT SYSTEM - STACK APPLICATIONS SUITE\n";
    cout << "====================================================================\n";

    // 1. Navigation
    NetbankingPortalStack nav;
    nav.visitPage("netbanking.bank.com/accounts");
    nav.visitPage("netbanking.bank.com/loans");
    nav.visitPage("netbanking.bank.com/loans/home-loan-apply");
    nav.displayHistory();
    nav.backPage();

    // 2. Parentheses
    cout << "\n>>> PROBLEM 3: LOAN ELIGIBILITY PARENTHESIS BALANCING <<<\n";
    string e1 = "{[MonthlySalary * 0.50] - [ExistingEMI + CreditCardDue]} > 25000";
    string e2 = "{[MonthlySalary * 0.50] - [ExistingEMI + CreditCardDue) > 25000";
    cout << "Expression 1: \"" << e1 << "\" -> " 
         << (checkLoanParentheses(e1) ? "BALANCED (Valid Eligibility Rule)" : "UNBALANCED (Syntax Error)") << "\n";
    cout << "Expression 2: \"" << e2 << "\" -> " 
         << (checkLoanParentheses(e2) ? "BALANCED (Valid Eligibility Rule)" : "UNBALANCED (Syntax Error)") << "\n";

    // 3 & 4. Interest Billing
    cout << "\n>>> PROBLEMS 2 & 4: LOAN SIMPLE INTEREST BILLING SYSTEM <<<\n";
    cout << "Infix Formula: (Principal * Rate * Time) / 100\n";
    cout << "Mapping: (P * R * T) / H  (where H = 100)\n";
    string infix = "(P * R * T) / H";
    string postfix = convertInterestInfixToPostfix(infix);
    cout << "\nFinal Postfix Expression: " << postfix << "\n";

    float principal = 500000.0f; // Rs 5 Lakhs
    float rate = 8.5f;          // 8.5%
    float time = 3.0f;          // 3 Years
    float hundred = 100.0f;

    cout << "\nAccepted Loan Interest Parameters:\n";
    cout << "  Principal Amount (P) : Rs " << fixed << setprecision(2) << principal << "\n";
    cout << "  Interest Rate (R)    : " << rate << " % per annum\n";
    cout << "  Tenure in Years (T)  : " << time << " years\n";

    float totalInterest = evaluateInterest(postfix, principal, rate, time, hundred);
    cout << "\n>>> TOTAL SIMPLE INTEREST PAYABLE: Rs " << fixed << setprecision(2) << totalInterest << " <<<\n";
    cout << ">>> TOTAL LOAN REPAYMENT (P + SI) : Rs " << fixed << setprecision(2) << (principal + totalInterest) << " <<<\n";

    return 0;
}
