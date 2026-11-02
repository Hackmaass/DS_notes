/**
 * ============================================================================
 * FUNDAMENTAL 03: DOUBLY LINKED LIST (TWO-WAY POINTERS)
 * ============================================================================
 * 👨‍🏫 PROFESSOR'S DEEP-DIVE CONCEPTUAL GUIDE:
 * 
 * 1. THE LIMITATION OF A SINGLY LINKED LIST:
 *    A Singly Linked List is a ONE-WAY STREET.
 *    If you are standing at node `C`, you CANNOT go back to node `B`!
 *    To delete node `C`, you must start all the way back from `head` just to
 *    find the predecessor node `B`!
 *
 * 2. THE DOUBLY LINKED LIST (DLL) REVOLUTION:
 *    Each node contains TWO pointers:
 *      +-------------------+-------------------+-------------------+
 *      |  DNode* prev (8B) |  int data (4B)    |  DNode* next (8B) |
 *      +-------------------+-------------------+-------------------+
 *      - `prev`: points BACKWARDS to previous node (or nullptr at head).
 *      - `next`: points FORWARDS to next node (or nullptr at tail).
 *
 * 3. HOW A TWO-WAY CONNECTION IS ESTABLISHED:
 *    Suppose we have [ 10 ] and want to append [ 20 ]:
 *      Step 1: Create newNode (20).
 *      Step 2: Old tail points forward: `tail->next = newNode;`
 *      Step 3: New node points backward: `newNode->prev = tail;`
 *      Step 4: Update tail pointer: `tail = newNode;`
 *    Result: [ 10 ] <===> [ 20 ]
 *
 * 4. EFFORTLESS DELETION (NO EXTRA TRAVERSAL!):
 *    To delete node `X`:
 *      `X->prev->next = X->next;`  // Left neighbor skips X going right
 *      `X->next->prev = X->prev;`  // Right neighbor skips X going left
 *      `delete X;`
 *    Both neighbors bypass `X` simultaneously!
 * ============================================================================
 */

#include <iostream>

using namespace std;

/**
 * ----------------------------------------------------------------------------
 * THE DOUBLY LINKED LIST NODE
 * ----------------------------------------------------------------------------
 */
struct DNode {
    int data;     // Value payload
    DNode* prev;  // Backward pointer
    DNode* next;  // Forward pointer

    // Constructor: initializes pointers safely to nullptr
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    DNode* head; // Anchor pointing to the first node
    DNode* tail; // Anchor pointing to the last node

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor: Clean up all allocated nodes
    ~DoublyLinkedList() {
        DNode* curr = head;
        while (curr != nullptr) {
            DNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    /**
     * ------------------------------------------------------------------------
     * 1. APPEND AT END (Establish two-way handshake)
     * ------------------------------------------------------------------------
     */
    void append(int val) {
        DNode* newNode = new DNode(val);

        // Case A: List is empty
        if (head == nullptr) {
            head = tail = newNode; // Head and tail both point to the first node
            cout << "  Appended [" << val << "] as the first node.\n";
            return;
        }

        // Case B: List already has elements
        tail->next = newNode; // 1. Old tail links forward to newNode
        newNode->prev = tail; // 2. newNode links backward to old tail
        tail = newNode;       // 3. Move tail anchor to newNode
        cout << "  Appended [" << val << "] to tail (established 2-way links).\n";
    }

    /**
     * ------------------------------------------------------------------------
     * 2. FORWARD TRAVERSAL (Head to Tail via `next`)
     * ------------------------------------------------------------------------
     */
    void displayForward() const {
        if (head == nullptr) {
            cout << "  Forward : [Empty]\n";
            return;
        }
        cout << "  Forward  (Head -> Tail): ";
        DNode* curr = head;
        while (curr != nullptr) {
            cout << "[" << curr->data << "]";
            if (curr->next != nullptr) cout << " <===> ";
            curr = curr->next; // Move forward
        }
        cout << " -> NULL\n";
    }

    /**
     * ------------------------------------------------------------------------
     * 3. BACKWARD TRAVERSAL (Tail to Head via `prev`)
     * ------------------------------------------------------------------------
     */
    void displayBackward() const {
        if (tail == nullptr) {
            cout << "  Backward: [Empty]\n";
            return;
        }
        cout << "  Backward (Tail -> Head): ";
        DNode* curr = tail;
        while (curr != nullptr) {
            cout << "[" << curr->data << "]";
            if (curr->prev != nullptr) cout << " <===> ";
            curr = curr->prev; // Move backward using 'prev'!
        }
        cout << " -> NULL\n\n";
    }

    /**
     * ------------------------------------------------------------------------
     * 4. DELETE A NODE (Unlinking both directions)
     * ------------------------------------------------------------------------
     */
    void deleteValue(int target) {
        if (head == nullptr) {
            cout << "  [ERROR] Cannot delete from an empty list!\n";
            return;
        }

        DNode* curr = head;

        // Step 1: Find target node
        while (curr != nullptr && curr->data != target) {
            curr = curr->next;
        }

        // Step 2: Target not found
        if (curr == nullptr) {
            cout << "  [NOT FOUND] Value " << target << " does not exist in list.\n";
            return;
        }

        // Step 3: Handle Deletion Cases
        // CASE A: Deleting the only node in the list
        if (curr == head && curr == tail) {
            head = tail = nullptr;
        }
        // CASE B: Deleting the HEAD node
        else if (curr == head) {
            head = head->next;   // Shift head forward
            head->prev = nullptr; // New head has no previous node
        }
        // CASE C: Deleting the TAIL node
        else if (curr == tail) {
            tail = tail->prev;   // Shift tail backward
            tail->next = nullptr; // New tail has no next node
        }
        // CASE D: Deleting a MIDDLE node (Double Bypass!)
        else {
            curr->prev->next = curr->next; // Predecessor skips curr
            curr->next->prev = curr->prev; // Successor skips curr
        }

        delete curr; // Free memory
        cout << "  [DELETED] Successfully unlinked and freed node [" << target << "].\n";
    }
};

int main() {
    cout << "========================================================\n";
    cout << "  TEACHER DEMO: DOUBLY LINKED LIST (TWO-WAY LINKS)\n";
    cout << "========================================================\n\n";

    DoublyLinkedList dll;

    cout << "1. BUILDING THE DOUBLY LINKED LIST (100, 200, 300, 400):\n";
    dll.append(100);
    dll.append(200);
    dll.append(300);
    dll.append(400);

    cout << "\n2. PROVING BIDIRECTIONAL TRAVERSAL:\n";
    dll.displayForward();
    dll.displayBackward();

    cout << "--------------------------------------------------------\n";
    cout << "3. DELETING A MIDDLE NODE (Value 300):\n";
    cout << "   -> Node 200's `next` jumps straight to 400\n";
    cout << "   -> Node 400's `prev` jumps straight back to 200\n";
    dll.deleteValue(300);
    dll.displayForward();
    dll.displayBackward();

    cout << "--------------------------------------------------------\n";
    cout << "4. DELETING HEAD (100) & TAIL (400):\n";
    dll.deleteValue(100);
    dll.deleteValue(400);
    dll.displayForward();
    dll.displayBackward();

    return 0;
}

/**
 * ============================================================================
 * 🎓 VIVA QUESTIONS & ANSWERS FOR THIS CODE:
 * ============================================================================
 * Q1: What is the primary advantage and disadvantage of DLL over SLL?
 * A1: - Advantage: Can be traversed in both directions; can delete a given node
 *       in O(1) time without knowing its predecessor.
 *     - Disadvantage: Each node consumes extra memory for the second pointer
 *       (`prev`), taking an additional 8 bytes per node on 64-bit systems.
 *
 * Q2: What happens if you forget `head->prev = nullptr` after deleting the head?
 * A2: The new head's `prev` pointer would continue pointing to freed/invalid heap
 *     memory (a dangling pointer). If backward traversal is attempted, it causes
 *     a memory access violation / segmentation fault.
 *
 * Q3: How do you check if a Doubly Linked List has only ONE node?
 * A3: When `head == tail && head != nullptr` (or `head->next == nullptr`).
 * ============================================================================
 */
