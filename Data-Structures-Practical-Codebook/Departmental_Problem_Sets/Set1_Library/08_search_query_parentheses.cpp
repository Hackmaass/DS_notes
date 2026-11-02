/**
 * ============================================================================
 * SET 1: LIBRARY MANAGEMENT SYSTEM (Part B - Problem 3)
 * SOURCE: Four Alternate Problem Sets Arrays, Linked Lists, Stacks and Queues.docx
 * 
 * PROBLEM STATEMENT:
 *   Write a program for checking balanced parentheses in a book-search query
 *   expression using a Stack.
 * ============================================================================
 * ALGORITHM:
 *   1. Create an empty character stack.
 *   2. For each character 'ch' in the query string:
 *      - If 'ch' is an opening bracket '(', '{', or '[', push onto stack.
 *      - If 'ch' is a closing bracket ')', '}', or ']':
 *        * If stack is empty, return false (unbalanced closing bracket).
 *        * Pop top element and check if it pairs correctly:
 *          '(' matches ')', '{' matches '}', '[' matches ']'.
 *        * If mismatched, return false.
 *   3. After string ends:
 *      - If stack is empty, return true (Balanced).
 *      - Else return false (Unclosed opening bracket remained).
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

bool checkQueryParentheses(string query) {
    Stack s;
    for (size_t i = 0; i < query.length(); ++i) {
        char ch = query[i];

        // Push opening brackets
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        }
        // Match closing brackets
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.isEmpty()) {
                return false; // Closing without opening
            }
            char open = s.pop();
            if (!isMatchingPair(open, ch)) {
                return false; // Type mismatch
            }
        }
    }
    return s.isEmpty(); // Must be empty at end
}

int main() {
    cout << "==============================================================\n";
    cout << "  SET 1 (PART B - PROBLEM 3): SEARCH QUERY PARENTHESIS CHECKER\n";
    cout << "==============================================================\n";

    string query1 = "(Author='Sahni' AND (Year=2024 OR Subject='Algorithms'))";
    string query2 = "[Category='CS' AND {Status='Available' OR (Issues > 5)]";

    cout << "Query 1: \"" << query1 << "\"\n";
    cout << "Result : " << (checkQueryParentheses(query1) ? "BALANCED (Valid Syntax)" : "UNBALANCED (Syntax Error)") << "\n\n";

    cout << "Query 2: \"" << query2 << "\"\n";
    cout << "Result : " << (checkQueryParentheses(query2) ? "BALANCED (Valid Syntax)" : "UNBALANCED (Syntax Error)") << "\n";

    return 0;
}
