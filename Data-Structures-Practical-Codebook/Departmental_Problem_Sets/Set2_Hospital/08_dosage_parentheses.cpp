/**
 * ============================================================================
 * SET 2: HOSPITAL MANAGEMENT SYSTEM (Part B - Problem 3)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program for checking balanced parentheses in a medical dosage
 *   formula using a Stack.
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

const int MAX = 100;

class Stack {
private:
    char arr[MAX];
    int top;

public:
    Stack() : top(-1) {}
    bool isEmpty() { return top == -1; }
    void push(char c) { arr[++top] = c; }
    char pop() { return arr[top--]; }
};

bool isMatchingPair(char open, char close) {
    if (open == '(' && close == ')') return true;
    if (open == '{' && close == '}') return true;
    if (open == '[' && close == ']') return true;
    return false;
}

bool checkDosageParentheses(string formula) {
    Stack s;
    for (size_t i = 0; i < formula.length(); ++i) {
        char ch = formula[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.isEmpty()) {
                return false;
            }
            char open = s.pop();
            if (!isMatchingPair(open, ch)) {
                return false;
            }
        }
    }
    return s.isEmpty();
}

int main() {
    cout << "==============================================================\n";
    cout << "  SET 2 (PART B - PROBLEM 3): MEDICAL DOSAGE PARENTHESES CHECKER\n";
    cout << "==============================================================\n";

    string formula1 = "[(Weight_kg * 10) / {Age_years + 2}] * 5";
    string formula2 = "(Dose_mg * {BodySurface / 1.73) + Baseline]";

    cout << "Dosage 1: \"" << formula1 << "\"\n";
    cout << "Result  : " << (checkDosageParentheses(formula1) ? "BALANCED (Safe Formula)" : "UNBALANCED (Dangerous Formula Error)") << "\n\n";

    cout << "Dosage 2: \"" << formula2 << "\"\n";
    cout << "Result  : " << (checkDosageParentheses(formula2) ? "BALANCED (Safe Formula)" : "UNBALANCED (Dangerous Formula Error)") << "\n";

    return 0;
}
