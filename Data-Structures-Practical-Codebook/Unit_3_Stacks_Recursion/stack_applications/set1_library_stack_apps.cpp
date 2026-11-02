/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit III: Stacks & Recursion
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 1 - Library Management System (Stack Applications Suite)
 * TITLE:         Library System: Catalogue Navigation, Late-Fine Infix/Postfix, Parentheses & Billing
 * 
 * PROBLEMS COVERED (Official Departmental Alternate Problem Set):
 *   1. Online Library Catalogue Navigation History Stack (visit URL, back URL, current, history).
 *   2. Late-Fine Formula `(Days * Rate) + Fixed - Waiver` (Infix to Postfix & Evaluation).
 *   3. Balanced Parentheses in Book-Search Query Expression.
 *   4. Library Fine Billing System with Intermediate Stack Contents Display.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// ============================================================================
// PROBLEM 1: ONLINE LIBRARY CATALOGUE NAVIGATION HISTORY STACK
// ============================================================================
class LibraryCatalogueStack {
private:
    string history[50];
    int top;

public:
    LibraryCatalogueStack() : top(-1) {}

    bool isEmpty() const { return (top == -1); }
    bool isFull() const { return (top == 49); }

    void visitPage(const string& url) {
        if (isFull()) {
            cout << "  [HISTORY FULL] Stack overflow!\n";
            return;
        }
        history[++top] = url;
        cout << "  [VISITED] Navigated to: " << url << "\n";
    }

    void backPage() {
        if (isEmpty()) {
            cout << "  [HISTORY EMPTY] No previous page to go back to.\n";
            return;
        }
        cout << "  [BACK] Leaving: " << history[top--] << "\n";
        if (!isEmpty()) {
            cout << "  [CURRENT PAGE]: " << history[top] << "\n";
        } else {
            cout << "  [CURRENT PAGE]: Library Home Portal\n";
        }
    }

    void displayCurrent() const {
        if (isEmpty()) cout << "  [CURRENT PAGE]: Library Home Portal (Empty History)\n";
        else cout << "  [CURRENT PAGE]: " << history[top] << "\n";
    }

    void displayHistory() const {
        if (isEmpty()) {
            cout << "  [NAVIGATION HISTORY]: Empty\n";
            return;
        }
        cout << "  [NAVIGATION HISTORY (Top to Bottom)]:\n";
        for (int i = top; i >= 0; --i) {
            cout << "    [" << (i + 1) << "] " << history[i] 
                 << (i == top ? "  <-- Current Active Page" : "") << "\n";
        }
    }
};

// ============================================================================
// PROBLEM 2 & 4: LATE-FINE FORMULA INFIX TO POSTFIX, EVALUATION & BILLING TRACE
// Formula: (Days * Rate) + Fixed - Waiver
// Single-char variables: D * R + F - W
// ============================================================================
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

string convertInfixToPostfixWithTrace(const string& infix) {
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

        cout << "  " << left << setw(8) << ch;
        // Print stack
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

float evaluateLateFinePostfixWithTrace(const string& postfix, float D, float R, float F, float W) {
    FloatStack s;
    cout << "\n  --- Postfix Evaluation Trace with Intermediate Stack ---\n";
    cout << "  " << left << setw(8) << "Token" << setw(10) << "Value" 
         << setw(25) << "Operand Stack" << "Action\n";
    cout << "  --------------------------------------------------------------------\n";

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

// ============================================================================
// PROBLEM 3: BALANCED PARENTHESES IN BOOK SEARCH QUERY
// ============================================================================
bool checkQueryParentheses(const string& query) {
    CharStack s;
    for (size_t i = 0; i < query.length(); ++i) {
        char ch = query[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
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
    cout << "  SET 1: LIBRARY MANAGEMENT SYSTEM - STACK APPLICATIONS SUITE\n";
    cout << "====================================================================\n";

    // 1. Catalogue History
    cout << "\n>>> PROBLEM 1: ONLINE CATALOGUE NAVIGATION HISTORY <<<\n";
    LibraryCatalogueStack nav;
    nav.visitPage("library.nmiet.edu.in");
    nav.visitPage("library.nmiet.edu.in/search?q=DataStructures");
    nav.visitPage("library.nmiet.edu.in/books/DS-101/details");
    nav.displayHistory();
    nav.backPage();
    nav.displayCurrent();

    // 2. Parentheses Checker
    cout << "\n>>> PROBLEM 3: SEARCH QUERY PARENTHESIS BALANCING <<<\n";
    string q1 = "(Author='Sahni' AND (Year=2024 OR Subject='Algorithms'))";
    string q2 = "[Category='CS' AND {Status='Available' OR (Issues > 5)]";
    cout << "Query 1: \"" << q1 << "\" -> " 
         << (checkQueryParentheses(q1) ? "BALANCED (Valid Syntax)" : "UNBALANCED (Syntax Error)") << "\n";
    cout << "Query 2: \"" << q2 << "\" -> " 
         << (checkQueryParentheses(q2) ? "BALANCED (Valid Syntax)" : "UNBALANCED (Syntax Error)") << "\n";

    // 3 & 4. Late-Fine Infix to Postfix & Evaluation Billing System
    cout << "\n>>> PROBLEMS 2 & 4: LIBRARY FINE BILLING SYSTEM <<<\n";
    cout << "Infix Formula: (Days * Rate) + Fixed - Waiver\n";
    cout << "Variable Mapping: (D * R) + F - W\n";
    string infix = "(D * R) + F - W";
    string postfix = convertInfixToPostfixWithTrace(infix);
    cout << "\nFinal Converted Postfix Expression: " << postfix << "\n";

    float lateDays = 12.0f;
    float dailyRate = 5.0f;
    float fixedCharge = 50.0f;
    float waiver = 20.0f;

    cout << "\nAccepted Student Fine Parameters:\n";
    cout << "  Late Days (D)   : " << lateDays << " days\n";
    cout << "  Daily Rate (R)  : Rs " << dailyRate << " / day\n";
    cout << "  Fixed Charge (F): Rs " << fixedCharge << "\n";
    cout << "  Waiver (W)      : Rs " << waiver << "\n";

    float totalFine = evaluateLateFinePostfixWithTrace(postfix, lateDays, dailyRate, fixedCharge, waiver);
    cout << "\n>>> TOTAL PAYABLE LIBRARY FINE: Rs " << fixed << setprecision(2) << totalFine << " <<<\n";

    return 0;
}
