/**
 * ============================================================================
 * COURSE:        Data Structures Laboratory (CE25PCC-203)
 * THEORY COURSE: Data Structures (CE25PCC-202) - Unit III: Stacks & Recursion
 * INSTITUTION:   Pimpri Chinchwad Education Trust / NMIET, Pune
 * CLASS:         S.Y. B.Tech Computer Engineering (Semester III)
 * 
 * BATCH SET:     Set 2 - Hospital Management System (Stack Applications Suite)
 * TITLE:         Hospital System: Patient Portal Navigation, Hospital Bill Formula, Dosage Parentheses & Billing
 * 
 * PROBLEMS COVERED:
 *   1. Patient Portal Navigation History Stack (visit URL, back URL, current, history).
 *   2. Hospital Bill Formula `(Consultation + Medicine) * Days - Insurance` (Infix to Postfix & Evaluation).
 *   3. Balanced Parentheses in Medical Dosage Formula.
 *   4. Hospital Billing System with Intermediate Stack Contents Display.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// PROBLEM 1: HOSPITAL PORTAL NAVIGATION
class HospitalPortalStack {
private:
    string history[50];
    int top;
public:
    HospitalPortalStack() : top(-1) {}
    bool isEmpty() const { return top == -1; }
    void visitPage(const string& url) {
        history[++top] = url;
        cout << "  [VISITED] " << url << "\n";
    }
    void backPage() {
        if (isEmpty()) return;
        cout << "  [BACK] Navigated back from: " << history[top--] << "\n";
        cout << "  [CURRENT ACTIVE]: " << (isEmpty() ? "Hospital Home" : history[top]) << "\n";
    }
    void displayHistory() const {
        cout << "  [PATIENT PORTAL NAVIGATION HISTORY]:\n";
        for (int i = top; i >= 0; --i) {
            cout << "    [" << (i + 1) << "] " << history[i] 
                 << (i == top ? "  <-- Current View" : "") << "\n";
        }
    }
};

// PROBLEM 2 & 4: HOSPITAL BILL FORMULA INFIX TO POSTFIX & EVALUATION
// Formula: (Consultation + Medicine) * Days - Insurance
// Mapping: (C + M) * D - I
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

string convertHospitalInfixToPostfix(const string& infix) {
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

float evaluateHospitalBill(const string& postfix, float C, float M, float D, float I) {
    FloatStack s;
    cout << "\n  --- Hospital Bill Evaluation Trace with Intermediate Stack ---\n";
    cout << "  " << left << setw(8) << "Token" << setw(10) << "Value" 
         << setw(25) << "Operand Stack" << "Action\n";
    cout << "  --------------------------------------------------------------------\n";

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

// PROBLEM 3: DOSAGE FORMULA PARENTHESES CHECKER
bool checkDosageParentheses(const string& formula) {
    CharStack s;
    for (size_t i = 0; i < formula.length(); ++i) {
        char ch = formula[i];
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
    cout << "  SET 2: HOSPITAL MANAGEMENT SYSTEM - STACK APPLICATIONS SUITE\n";
    cout << "====================================================================\n";

    // 1. Navigation
    cout << "\n>>> PROBLEM 1: HOSPITAL PATIENT PORTAL NAVIGATION <<<\n";
    HospitalPortalStack nav;
    nav.visitPage("hospital.org/portal");
    nav.visitPage("hospital.org/portal/lab-reports");
    nav.visitPage("hospital.org/portal/lab-reports/blood-test-302");
    nav.displayHistory();
    nav.backPage();

    // 2. Parentheses
    cout << "\n>>> PROBLEM 3: MEDICAL DOSAGE PARENTHESIS BALANCING <<<\n";
    string d1 = "[(Weight_kg * 10) / {Age_years + 2}] * 5";
    string d2 = "(Dose_mg * {BodySurface / 1.73) + Baseline]";
    cout << "Dosage 1: \"" << d1 << "\" -> " 
         << (checkDosageParentheses(d1) ? "BALANCED (Safe Formula)" : "UNBALANCED (Dangerous Formula Error)") << "\n";
    cout << "Dosage 2: \"" << d2 << "\" -> " 
         << (checkDosageParentheses(d2) ? "BALANCED (Safe Formula)" : "UNBALANCED (Dangerous Formula Error)") << "\n";

    // 3 & 4. Hospital Billing System
    cout << "\n>>> PROBLEMS 2 & 4: HOSPITAL BILLING SYSTEM <<<\n";
    cout << "Infix Formula: (Consultation + Medicine) * Days - Insurance\n";
    cout << "Mapping: (C + M) * D - I\n";
    string infix = "(C + M) * D - I";
    string postfix = convertHospitalInfixToPostfix(infix);
    cout << "\nFinal Postfix Expression: " << postfix << "\n";

    float consultation = 800.0f;
    float medicine = 1200.0f;
    float days = 4.0f;
    float insurance = 3000.0f;

    cout << "\nAccepted Patient Billing Parameters:\n";
    cout << "  Daily Consultation (C) : Rs " << consultation << "\n";
    cout << "  Daily Medicine (M)     : Rs " << medicine << "\n";
    cout << "  Admission Days (D)     : " << days << " days\n";
    cout << "  Insurance Coverage (I) : Rs " << insurance << "\n";

    float totalBill = evaluateHospitalBill(postfix, consultation, medicine, days, insurance);
    cout << "\n>>> FINAL PAYABLE HOSPITAL BILL: Rs " << fixed << setprecision(2) << totalBill << " <<<\n";

    return 0;
}
