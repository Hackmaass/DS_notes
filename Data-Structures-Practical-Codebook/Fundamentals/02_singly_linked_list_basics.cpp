/**
 * ============================================================================
 * FUNDAMENTAL 02: SINGLY LINKED LIST (CREATION, WALK & DELETION)
 * ============================================================================
 * 👨‍🏫 PROFESSOR'S DEEP-DIVE CONCEPTUAL GUIDE:
 * 
 * 1. WHY DO WE NEED A LINKED LIST OVER AN ARRAY?
 *    Arrays have two severe limitations:
 *      a) Fixed Size: You must predict capacity in advance (e.g., MAX = 100).
 *      b) Expensive Shifting: Inserting or deleting at the front takes O(N) time.
 *    A Singly Linked List (SLL) solves this!
 *    Elements (called "Nodes") live anywhere in Heap memory. They do NOT need
 *    to be next to each other. They stay connected via "Pointers".
 *
 * 2. WHAT DOES A NODE LOOK LIKE IN MEMORY?
 *    +--------------------+-------------------------+
 *    |  int data (4 B)    |  Node* next (8 B ptr)   |
 *    +--------------------+-------------------------+
 *    Address: 0x1000       Address: 0x1004
 * 
 *    `data` stores the information (e.g., 10, 20).
 *    `next` stores the HEXADECIMAL RAM ADDRESS of the next node.
 *    If there is no next node, `next` holds `nullptr` (0x0).
 *
 * 3. THE SACRED "POINTER WALK" (TRAVERSAL):
 *    In an array, you step forward with index arithmetic: `i++`.
 *    In a linked list, you CANNOT do `curr++` because nodes are scattered in RAM!
 *    Instead, you read the address written inside the current node:
 *      `curr = curr->next;`
 *    This tells the CPU: "Look at the address stored in my `next` compartment,
 *    and jump there!"
 *
 * 4. DELETION BY BYPASSING:
 *    To remove node B from: [ A ] -> [ B ] -> [ C ]
 *    Step 1: Point A's `next` directly to C: `prev->next = curr->next;`
 *    Step 2: Free B's memory: `delete curr;`
 *    Notice: Zero elements were shifted in memory! Just one pointer was redirected!
 * ============================================================================
 */

#include <iostream>

using namespace std;

/**
 * ----------------------------------------------------------------------------
 * THE NODE STRUCTURE: The fundamental atom of a Linked List
 * ----------------------------------------------------------------------------
 */
struct Node {
    int data;     // The payload value
    Node* next;   // Self-referential pointer: points to another Node of the same type

    // Constructor: automatically sets next to nullptr so it never points to garbage RAM
    Node(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head; // The "anchor" pointer. Points to the 1st node, or nullptr if empty.

public:
    // Constructor: An empty list starts with head = nullptr
    SinglyLinkedList() : head(nullptr) {}

    // Destructor: Free all heap memory when the list goes out of scope (prevents memory leaks!)
    ~SinglyLinkedList() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* temp = curr;  // 1. Remember current node
            curr = curr->next;  // 2. Advance to next before deleting!
            delete temp;        // 3. Safe to delete old node
        }
    }

    /**
     * ------------------------------------------------------------------------
     * 1. APPEND AT END (Insertion at Tail)
     * ------------------------------------------------------------------------
     * Steps:
     *   A. Allocate new node on the heap using `new`.
     *   B. If list is empty, new node BECOMES the head.
     *   C. Otherwise, walk until `curr->next == nullptr` (the current tail).
     *   D. Link old tail to new node: `curr->next = newNode;`
     * Time Complexity: O(N) because we must walk from head to tail.
     * ------------------------------------------------------------------------
     */
    void append(int val) {
        Node* newNode = new Node(val);

        // Case A: List is completely empty
        if (head == nullptr) {
            head = newNode;
            cout << "  Appended [" << val << "] as the Head node.\n";
            return;
        }

        // Case B: Walk to the last node
        Node* curr = head;
        // Notice condition: `curr->next != nullptr` (we stop AT the last node, not past it!)
        while (curr->next != nullptr) {
            curr = curr->next;
        }

        // Now `curr` points to the last node. Connect it:
        curr->next = newNode;
        cout << "  Appended [" << val << "] to the tail of the list.\n";
    }

    /**
     * ------------------------------------------------------------------------
     * 2. DISPLAY (The Classic Pointer Walk)
     * ------------------------------------------------------------------------
     * Steps:
     *   Start at `head`.
     *   Loop while `curr != nullptr` (walks all the way through the end).
     *   Print `curr->data`, then advance: `curr = curr->next;`
     * ------------------------------------------------------------------------
     */
    void display() const {
        if (head == nullptr) {
            cout << "  List is [Empty] (head == nullptr)\n";
            return;
        }

        cout << "  List: ";
        Node* curr = head;
        while (curr != nullptr) {
            cout << "[" << curr->data << "]";
            if (curr->next != nullptr) cout << " -> ";
            curr = curr->next; // Leap to the next node in heap memory
        }
        cout << " -> NULL\n\n";
    }

    /**
     * ------------------------------------------------------------------------
     * 3. DELETE BY VALUE (Bypass & Free)
     * ------------------------------------------------------------------------
     * Scenarios:
     *   Scenario 1: List is empty -> nothing to delete.
     *   Scenario 2: The node to delete is the FIRST node (head).
     *               Move head to node 2, then delete node 1.
     *   Scenario 3: The node to delete is in the MIDDLE or END.
     *               Use two pointers: `prev` and `curr`.
     *               When `curr->data == target`, bypass: `prev->next = curr->next;`
     *               Then `delete curr;`
     * ------------------------------------------------------------------------
     */
    void deleteValue(int target) {
        if (head == nullptr) {
            cout << "  [ERROR] Cannot delete from an empty list!\n";
            return;
        }

        // SCENARIO 2: Target is at the head
        if (head->data == target) {
            Node* temp = head;   // Remember node to be freed
            head = head->next;   // Shift head pointer to the second node
            delete temp;         // Free heap memory
            cout << "  [DELETED] Head node containing " << target << " removed.\n";
            return;
        }

        // SCENARIO 3: Target is somewhere after the head
        Node* prev = head;
        Node* curr = head->next;

        // Search for target while keeping track of the preceding node (`prev`)
        while (curr != nullptr && curr->data != target) {
            prev = curr;
            curr = curr->next;
        }

        // If target was found before reaching NULL
        if (curr != nullptr) {
            // THE BYPASS: prev skips curr and connects directly to curr's child
            prev->next = curr->next;
            delete curr; // Free memory of target node
            cout << "  [DELETED] Node containing " << target << " bypassed and freed.\n";
        } else {
            cout << "  [NOT FOUND] Value " << target << " is not in the list.\n";
        }
    }
};

int main() {
    cout << "========================================================\n";
    cout << "  TEACHER DEMO: SINGLY LINKED LIST (CREATION & WALK)\n";
    cout << "========================================================\n\n";

    SinglyLinkedList list;

    cout << "1. APPENDING NODES (10, 20, 30, 40):\n";
    list.append(10);
    list.append(20);
    list.append(30);
    list.append(40);
    cout << "\nVisualizing the list after appends:\n";
    list.display();

    cout << "--------------------------------------------------------\n";
    cout << "2. DELETING A MIDDLE NODE (Value 20):\n";
    cout << "   -> `prev` (10) points its `next` directly to (30)\n";
    cout << "   -> Node 20 is deleted from the heap\n";
    list.deleteValue(20);
    list.display();

    cout << "--------------------------------------------------------\n";
    cout << "3. DELETING THE HEAD NODE (Value 10):\n";
    cout << "   -> `head` advances to point directly at (30)\n";
    cout << "   -> Node 10 is deleted from the heap\n";
    list.deleteValue(10);
    list.display();

    return 0;
}

/**
 * ============================================================================
 * 🎓 VIVA QUESTIONS & ANSWERS FOR THIS CODE:
 * ============================================================================
 * Q1: What is a Dangling Pointer and Memory Leak in Linked Lists?
 * A1: - Memory Leak: If you change `head = head->next` without calling `delete`
 *       on the old node, that heap memory stays reserved but unreachable.
 *     - Dangling Pointer: If you `delete temp;` and then try to read `temp->data`
 *       or `temp->next`, you are accessing freed memory, causing undefined behavior!
 *
 * Q2: What is the Time Complexity of Linked List operations?
 * A2: - Append at tail (without tail pointer): O(N) to walk to the end.
 *     - Insert at front: O(1) instantaneous! No shifting required.
 *     - Search: O(N) sequential search.
 *     - Delete node (given pointer to previous): O(1) bypass.
 *
 * Q3: Why does `append()` stop at `curr->next != nullptr` instead of `curr != nullptr`?
 * A3: If we stopped at `curr != nullptr`, `curr` would end up as `nullptr` (past
 *     the end of the list), and `curr->next` would crash with a segmentation fault!
 *     Stopping at `curr->next != nullptr` ensures `curr` points to the last VALID node.
 * ============================================================================
 */
