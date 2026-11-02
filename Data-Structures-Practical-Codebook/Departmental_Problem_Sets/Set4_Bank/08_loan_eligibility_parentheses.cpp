/**
 * ============================================================================
 * Departmental Problem Set 4 (Bank) - Problem 8
 * Program: Loan Eligibility Expression Parenthesis Checker
 * ============================================================================
 * Problem Statement:
 *   Check whether parenthesis expressions in banking loan eligibility rules
 *   and scoring criteria are well-formed and balanced using a Stack ADT:
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

bool checkLoanEligibilityParentheses(const string& expr, string& reason) {
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
        reason = string("Unclosed opening bracket '") + s.peek() + "' remaining on stack.";
        return false;
    }

    reason = "All brackets and parentheses are well-balanced and properly nested.";
    return true;
}

void testEligibilityRule(const string& rule) {
    cout << "Rule: " << rule << "\n";
    string reason;
    bool balanced = checkLoanEligibilityParentheses(rule, reason);
    if (balanced) {
        cout << "  Status: BALANCED\n  Reason: " << reason << "\n\n";
    } else {
        cout << "  Status: UNBALANCED\n  Reason: " << reason << "\n\n";
    }
}

int main() {
    cout << "=== Loan Eligibility Rule Parentheses Checker ===\n\n";

    testEligibilityRule("{ [ (Salary * 12) * 0.6 ] - (ExistingEMI + CreditCardDue) }");
    testEligibilityRule("[ (CIBIL_Score > 750) && (Age >= 21) }"); // Mismatched [ and }
    testEligibilityRule("{ (MonthlyIncome - Expenses) * [TenureInMonths / 12] "); // Missing }
    testEligibilityRule("((Principal * Rate) / (1 - (1 + Rate)^(-Tenure)))");

    return 0;
}
