/**
 * ============================================================================
 * Departmental Problem Set 3 (Inventory) - Problem 8
 * Program: Stock Valuation Expression Parenthesis Checker
 * ============================================================================
 * Problem Statement:
 *   Check whether parenthesis expressions in stock valuation rules/formulas
 *   are well-formed and balanced using a Stack ADT:
 *   - Supports '()', '{}', and '[]'.
 *   - Reports balanced or unbalanced with reason.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

class BracketStack {
private:
    char arr[100];
    int top;
public:
    BracketStack() : top(-1) {}
    void push(char c) { arr[++top] = c; }
    char pop() { return arr[top--]; }
    char peek() const { return arr[top]; }
    bool isEmpty() const { return top == -1; }
};

bool isMatchingPair(char opening, char closing) {
    if (opening == '(' && closing == ')') return true;
    if (opening == '{' && closing == '}') return true;
    if (opening == '[' && closing == ']') return true;
    return false;
}

bool checkValuationParentheses(const string& expr, string& reason) {
    BracketStack s;

    for (size_t i = 0; i < expr.length(); i++) {
        char ch = expr[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.isEmpty()) {
                reason = string("Closing bracket '") + ch + "' at position " + to_string(i) + " has no opening match.";
                return false;
            }
            char open = s.pop();
            if (!isMatchingPair(open, ch)) {
                reason = string("Mismatched pair: opening '") + open + "' does not match closing '" + ch + "'.";
                return false;
            }
        }
    }

    if (!s.isEmpty()) {
        reason = string("Unclosed opening bracket '") + s.peek() + "' left on stack.";
        return false;
    }

    reason = "All parentheses are correctly matched and nested.";
    return true;
}

void testExpression(const string& formula) {
    cout << "Formula: " << formula << "\n";
    string reason;
    bool balanced = checkValuationParentheses(formula, reason);
    if (balanced) {
        cout << "  Status: BALANCED\n  Reason: " << reason << "\n\n";
    } else {
        cout << "  Status: UNBALANCED\n  Reason: " << reason << "\n\n";
    }
}

int main() {
    cout << "=== Stock Valuation Rule Parentheses Checker ===\n\n";

    testExpression("{ [ (Qty * Cost) + Shipping ] * (1 - Discount) }");
    testExpression("[ (OpeningStock + Purchases) - ClosingStock )"); // Mismatched
    testExpression("{ (UnitsOnHand * UnitCost) + [TransitStock * Cost] "); // Missing closing brace
    testExpression("((FIFO_Valuation + LIFO_Valuation) / 2)");

    return 0;
}
