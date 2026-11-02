/*
========================================================================================
PROGRAM HEADER:
- Program Number: 09
- Program Title: Student Portal Browser History Navigation using Stack
- Unit: Unit III - Stack and Recursion
- Relevant Curriculum Topic: Stack Applications (Browser Navigation History, LIFO)
- Course Code: CE25PCC-203 (Data Structures Laboratory) - Group C, Assignment 9
- Problem Statement:
  Write a program to simulate the browser history of a student portal using a stack.
  Implement functions to:
  a. Visit a new page (push URL)
  b. Go back to the previous page (pop URL)
  c. Display the current page
  d. Show the entire browsing history stack
- Data Structure Used: Custom Array-Based String Stack (Manual implementation without `std::stack`)
- What This Program Demonstrates:
  LIFO modeling for real-world software features (web browser "Back" button),
  state tracking, stack inspection, and boundary validation.
========================================================================================

CONCEPT: WHY IS A STACK THE NATURAL MODEL FOR BROWSER HISTORY?
When browsing the student portal:
1. You start at the Login page.
2. You click on "Dashboard" -> You move forward.
3. You click on "Exam Results" -> You move forward again.
4. You click on "Grade Card" -> Current view is Grade Card.

If you hit the "BACK" button on your browser:
- You expect to return immediately to the page you were on MOST RECENTLY ("Exam Results").
- The page visited LAST is the one retrieved FIRST!
- This is the pure definition of LIFO (Last-In, First-Out).
- A stack is the fundamental data structure used by Chrome, Firefox, and Safari
  to power their Back button navigation.
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_PAGES = 30;

class BrowserHistoryStack {
private:
    string history[MAX_PAGES]; // Array holding URLs
    int top;                   // Index of current page URL

public:
    BrowserHistoryStack() {
        top = -1; // -1 indicates browser was just launched (no page opened)
    }

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == MAX_PAGES - 1;
    }

    /*
    ALGORITHM 1: VISIT NEW PAGE (PUSH URL)
    1. Check if history stack is full: `if (isFull())`.
       If full, report error and return false.
    2. Increment top: `top++;`
    3. Store new URL: `history[top] = url;`
    4. Print confirmation that page is now loaded.
    */
    bool visitPage(const string &url) {
        if (isFull()) {
            cout << "[ERROR] Browser history stack full! Cannot visit new page.\n";
            return false;
        }

        top++;
        history[top] = url;
        cout << ">> VISITING: Loading page -> \"" << url << "\"\n";
        return true;
    }

    /*
    ALGORITHM 2: GO BACK TO PREVIOUS PAGE (POP URL)
    1. Check if back navigation is possible:
       - If `isEmpty()`, browser has no pages opened; return error.
       - If `top == 0`, user is at the initial root landing page!
         Popping would leave an empty blank window. Report that no further back history exists!
    2. Retrieve departing page: `departingPage = history[top];`
    3. Decrement top: `top--;`
    4. Current page is now `history[top]`.
    5. Print message showing user moved back to `history[top]`.
    */
    bool goBack() {
        if (isEmpty()) {
            cout << "[ERROR] Cannot go back: No pages opened yet.\n";
            return false;
        }

        if (top == 0) {
            cout << "[WARNING] You are already on the initial homepage (\"" 
                 << history[top] << "\"). Cannot go back further!\n";
            return false;
        }

        string departingPage = history[top];
        top--; // Pop current page off the top

        cout << ">> BACK: Left \"" << departingPage 
             << "\" ---> Returned to \"" << history[top] << "\"\n";
        return true;
    }

    /*
    ALGORITHM 3: DISPLAY CURRENT PAGE (PEEK)
    1. If `isEmpty()`, display "No active page" and return "".
    2. Return `history[top]`.
    */
    string getCurrentPage() const {
        if (isEmpty()) {
            return "[No Page Active]";
        }
        return history[top];
    }

    /*
    ALGORITHM 4: SHOW ENTIRE BROWSING HISTORY STACK
    1. If `isEmpty()`, report "History is empty".
    2. Print formatted table showing stack index, URL, and marker indicating
       which page is currently active.
    3. Iterate from `top` down to `0`.
    */
    void showHistory() const {
        if (isEmpty()) {
            cout << "\n   [BROWSING HISTORY: EMPTY]\n";
            return;
        }

        cout << "\n   ================ STUDENT PORTAL BROWSING HISTORY ================\n";
        cout << "   " << left << setw(8) << "Step" 
             << setw(36) << "Page URL" 
             << "Status\n";
        cout << "   -----------------------------------------------------------------\n";

        for (int i = top; i >= 0; i--) {
            cout << "   " << left << setw(8) << ("#" + to_string(i + 1))
                 << setw(36) << history[i];
            if (i == top) {
                cout << "<=== CURRENT ACTIVE PAGE";
            } else {
                cout << "(In Back History)";
            }
            cout << "\n";
        }
        cout << "   -----------------------------------------------------------------\n";
        cout << "   Total Pages in History Trail: " << (top + 1) << "\n\n";
    }
};

// Interactive demonstration runner
int main() {
    BrowserHistoryStack browser;

    cout << "==============================================================\n";
    cout << "   STUDENT PORTAL BROWSER HISTORY SIMULATOR (STACK ADT)       \n";
    cout << "==============================================================\n";

    // 1. Initial State
    cout << "\n--- DEMO STEP 1: Initial Browser Launch ---\n";
    cout << "Current Page: " << browser.getCurrentPage() << "\n";
    browser.showHistory();

    // 2. Navigating through student portal pages
    cout << "--- DEMO STEP 2: Student logs into portal and visits sections ---\n";
    browser.visitPage("portal.nmiet.edu.in/login");
    browser.visitPage("portal.nmiet.edu.in/dashboard");
    browser.visitPage("portal.nmiet.edu.in/attendance");
    browser.visitPage("portal.nmiet.edu.in/ia_marks");
    browser.visitPage("portal.nmiet.edu.in/fee_receipt");

    // 3. Inspecting State
    cout << "\n--- DEMO STEP 3: Inspecting Current Page and Full History Trail ---\n";
    cout << "Active Page via getCurrentPage(): " << browser.getCurrentPage() << "\n";
    browser.showHistory();

    // 4. Clicking Back button repeatedly (LIFO)
    cout << "--- DEMO STEP 4: Clicking Browser 'BACK' Button Twice ---\n";
    browser.goBack(); // Back from fee_receipt to ia_marks
    browser.goBack(); // Back from ia_marks to attendance
    browser.showHistory();

    // 5. Visiting a new page from the middle of history
    cout << "--- DEMO STEP 5: Clicking a new link from current page ---\n";
    browser.visitPage("portal.nmiet.edu.in/exam_timetable");
    browser.showHistory();

    // 6. Going all the way back to the root page
    cout << "--- DEMO STEP 6: Clicking 'BACK' all the way to Homepage ---\n";
    browser.goBack(); // Back to attendance
    browser.goBack(); // Back to dashboard
    browser.goBack(); // Back to login
    browser.showHistory();

    // 7. Testing boundary condition: Going back past homepage
    cout << "--- DEMO STEP 7: Testing boundary (Back past Homepage) ---\n";
    browser.goBack(); // Should warn user that root page has been reached!

    cout << "\n==============================================================\n";
    cout << "   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  \n";
    cout << "==============================================================\n";

    return 0;
}

/*
========================================================================================
SAMPLE INPUT AND EXECUTION TRACE:
1. Visit /login, /dashboard, /attendance, /ia_marks, /fee_receipt
2. Current active page: /fee_receipt
3. Go Back -> Active page: /ia_marks
4. Go Back -> Active page: /attendance
5. Visit /exam_timetable -> Pushed on top of /attendance
6. Go Back 3 times -> Reaches /login
7. Go Back again -> Gracefully blocked with warning.

SAMPLE OUTPUT:
==============================================================
   STUDENT PORTAL BROWSER HISTORY SIMULATOR (STACK ADT)       
==============================================================

--- DEMO STEP 1: Initial Browser Launch ---
Current Page: [No Page Active]

   [BROWSING HISTORY: EMPTY]
--- DEMO STEP 2: Student logs into portal and visits sections ---
>> VISITING: Loading page -> "portal.nmiet.edu.in/login"
>> VISITING: Loading page -> "portal.nmiet.edu.in/dashboard"
>> VISITING: Loading page -> "portal.nmiet.edu.in/attendance"
>> VISITING: Loading page -> "portal.nmiet.edu.in/ia_marks"
>> VISITING: Loading page -> "portal.nmiet.edu.in/fee_receipt"

--- DEMO STEP 3: Inspecting Current Page and Full History Trail ---
Active Page via getCurrentPage(): portal.nmiet.edu.in/fee_receipt

   ================ STUDENT PORTAL BROWSING HISTORY ================
   Step    Page URL                            Status
   -----------------------------------------------------------------
   #5      portal.nmiet.edu.in/fee_receipt     <=== CURRENT ACTIVE PAGE
   #4      portal.nmiet.edu.in/ia_marks        (In Back History)
   #3      portal.nmiet.edu.in/attendance      (In Back History)
   #2      portal.nmiet.edu.in/dashboard       (In Back History)
   #1      portal.nmiet.edu.in/login           (In Back History)
   -----------------------------------------------------------------
   Total Pages in History Trail: 5

--- DEMO STEP 4: Clicking Browser 'BACK' Button Twice ---
>> BACK: Left "portal.nmiet.edu.in/fee_receipt" ---> Returned to "portal.nmiet.edu.in/ia_marks"
>> BACK: Left "portal.nmiet.edu.in/ia_marks" ---> Returned to "portal.nmiet.edu.in/attendance"

   ================ STUDENT PORTAL BROWSING HISTORY ================
   Step    Page URL                            Status
   -----------------------------------------------------------------
   #3      portal.nmiet.edu.in/attendance      <=== CURRENT ACTIVE PAGE
   #2      portal.nmiet.edu.in/dashboard       (In Back History)
   #1      portal.nmiet.edu.in/login           (In Back History)
   -----------------------------------------------------------------
   Total Pages in History Trail: 3

--- DEMO STEP 5: Clicking a new link from current page ---
>> VISITING: Loading page -> "portal.nmiet.edu.in/exam_timetable"

   ================ STUDENT PORTAL BROWSING HISTORY ================
   Step    Page URL                            Status
   -----------------------------------------------------------------
   #4      portal.nmiet.edu.in/exam_timetable  <=== CURRENT ACTIVE PAGE
   #3      portal.nmiet.edu.in/attendance      (In Back History)
   #2      portal.nmiet.edu.in/dashboard       (In Back History)
   #1      portal.nmiet.edu.in/login           (In Back History)
   -----------------------------------------------------------------
   Total Pages in History Trail: 4

--- DEMO STEP 6: Clicking 'BACK' all the way to Homepage ---
>> BACK: Left "portal.nmiet.edu.in/exam_timetable" ---> Returned to "portal.nmiet.edu.in/attendance"
>> BACK: Left "portal.nmiet.edu.in/attendance" ---> Returned to "portal.nmiet.edu.in/dashboard"
>> BACK: Left "portal.nmiet.edu.in/dashboard" ---> Returned to "portal.nmiet.edu.in/login"

   ================ STUDENT PORTAL BROWSING HISTORY ================
   Step    Page URL                            Status
   -----------------------------------------------------------------
   #1      portal.nmiet.edu.in/login           <=== CURRENT ACTIVE PAGE
   -----------------------------------------------------------------
   Total Pages in History Trail: 1

--- DEMO STEP 7: Testing boundary (Back past Homepage) ---
[WARNING] You are already on the initial homepage ("portal.nmiet.edu.in/login"). Cannot go back further!

==============================================================
   PROGRAM EXECUTION COMPLETED SUCCESSFULLY                  
==============================================================
========================================================================================

TIME COMPLEXITY:
- `visitPage()` (Push): O(1) constant time array assignment.
- `goBack()` (Pop):     O(1) constant time index decrement.
- `getCurrentPage()` (Peek): O(1) constant time.
- `showHistory()`:      O(N) linear time to iterate and display from top to 0.

SPACE COMPLEXITY:
- Auxiliary Space: O(1).
- Total Space: O(MAX_PAGES) for string array buffer.

WHY?
Because each visit is pushed directly onto the top of the stack, and each back navigation
simply pops the topmost URL.

========================================================================================
COMMON MISTAKES TO AVOID IN PRACTICAL EXAMS:
1. Popping the Only Remaining Page:
   - If `top == 0` (only 1 page in history), popping it leaves `top == -1` (no page visible).
     In a browser simulator, check `if (top == 0)` to warn the user that they are on
     the initial homepage!
2. Displaying History in Forward Order:
   - Displaying from `0` to `top` shows oldest first. Always display from `top` down to `0`
     to reflect what the user sees currently at the top of the stack!
========================================================================================
RECALL CHECKLIST FOR REPRODUCING FROM MEMORY:
[ ] 1. Stack of strings: `string history[MAX_PAGES]; int top;`
[ ] 2. Visit: `if (!isFull()) history[++top] = url;`
[ ] 3. Back: `if (top > 0) top--;`
[ ] 4. Current page: `return (top >= 0) ? history[top] : "";`
[ ] 5. Display: loop `for (int i = top; i >= 0; i--)`
========================================================================================
*/
