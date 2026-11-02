/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit III: Stacks & Recursion
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 3 - Inventory & Warehouse System (Stack Applications Suite)
 * TITLE:         Warehouse System: Portal Navigation, Price Formula, Valuation Parentheses & Billing
 * 
 * PROBLEMS COVERED:
 *   1. Warehouse Portal Navigation History Stack (visit URL, back URL, current, history).
 *   2. Price Formula `(Cost * Qty) + Shipping - Discount` (Infix to Postfix & Evaluation).
 *   3. Balanced Parentheses in Stock-Valuation Expression.
 *   4. Purchase Billing System with Intermediate Stack Contents Display.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// PROBLEM 1: WAREHOUSE PORTAL NAVIGATION
class WarehousePortalStack {
private:
    string history[50];
    int top;
public:
    WarehousePortalStack() : top(-1) {}
    bool isEmpty() const { return top == -1; }
    void visitPage(const string& url) { history[++top] = url; cout << "  [VISITED] " << url << "\n"; }
    void backPage() {
        if (isEmpty()) return;
        cout << "  [BACK] Leaving: " << history[top--] << "\n";
        cout << "  [CURRENT]: " << (isEmpty() ? "Warehouse Main Dashboard" : history[top]) << "\n";
    }
    void displayHistory() const {
        cout << "  [WAREHOUSE PORTAL NAVIGATION HISTORY]:\n";
        for (int i = top; i >= 0; --i) {
            cout << "    [" << (i + 1) << "] " << history[i] 
                 << (i == top ? "  <-- Current Active Tab" : "") << "\n";
        }
    }
};

// PROBLEM 2 & 4: PRICE FORMULA INFIX TO POSTFIX & EVALUATION
// Formula: (Cost * Qty) + Shipping - Discount
// Mapping: (C * Q) + S - D
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

string convertPriceInfixToPostfix(const string& infix) {
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

float evaluatePurchasePrice(const string& postfix, float C, float Q, float S, float D) {
    FloatStack s;
    cout << "\n  --- Purchase Price Evaluation Trace with Intermediate Stack ---\n";
    cout << "  " << left << setw(8) << "Token" << setw(10) << "Value" 
         << setw(25) << "Operand Stack" << "Action\n";
    cout << "  --------------------------------------------------------------------\n";

    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];
        if (isspace(ch)) continue;

        if (isalpha(ch)) {
            float val = 0.0f;
            if (ch == 'C') val = C;
            else if (ch == 'Q') val = Q;
            else if (ch == 'S') val = S;
            else if (ch == 'D') val = D;

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

// PROBLEM 3: STOCK VALUATION PARENTHESES CHECKER
bool checkStockParentheses(const string& expr) {
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
    cout << "  SET 3: INVENTORY & WAREHOUSE SYSTEM - STACK APPLICATIONS SUITE\n";
    cout << "====================================================================\n";

    // 1. Navigation
    WarehousePortalStack nav;
    nav.visitPage("warehouse.corp.internal");
    nav.visitPage("warehouse.corp.internal/bay-4-logistics");
    nav.visitPage("warehouse.corp.internal/bay-4-logistics/order-9002");
    nav.displayHistory();
    nav.backPage();

    // 2. Parentheses
    cout << "\n>>> PROBLEM 3: STOCK VALUATION PARENTHESIS BALANCING <<<\n";
    string v1 = "{[(UnitCost * Quantity) + StorageFee] - TaxDepreciation}";
    string v2 = "{[(UnitCost * Quantity) + StorageFee) - TaxDepreciation}";
    cout << "Expression 1: \"" << v1 << "\" -> " 
         << (checkStockParentheses(v1) ? "BALANCED (Valid Valuation Expression)" : "UNBALANCED (Error)") << "\n";
    cout << "Expression 2: \"" << v2 << "\" -> " 
         << (checkStockParentheses(v2) ? "BALANCED (Valid Valuation Expression)" : "UNBALANCED (Error)") << "\n";

    // 3 & 4. Purchase Billing
    cout << "\n>>> PROBLEMS 2 & 4: PURCHASE BILLING SYSTEM <<<\n";
    cout << "Infix Formula: (Cost * Qty) + Shipping - Discount\n";
    cout << "Mapping: (C * Q) + S - D\n";
    string infix = "(C * Q) + S - D";
    string postfix = convertPriceInfixToPostfix(infix);
    cout << "\nFinal Postfix Expression: " << postfix << "\n";

    float cost = 45.0f;
    float qty = 200.0f;
    float shipping = 350.0f;
    float discount = 500.0f;

    cout << "\nAccepted Purchase Order Parameters:\n";
    cout << "  Unit Cost (C) : Rs " << cost << "\n";
    cout << "  Quantity (Q)  : " << qty << " units\n";
    cout << "  Shipping (S)  : Rs " << shipping << "\n";
    cout << "  Discount (D)  : Rs " << discount << "\n";

    float totalPurchase = evaluatePurchasePrice(postfix, cost, qty, shipping, discount);
    cout << "\n>>> FINAL PAYABLE PURCHASE INVOICE: Rs " << fixed << setprecision(2) << totalPurchase << " <<<\n";

    return 0;
}
