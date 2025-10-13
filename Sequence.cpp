#include "Sequence.h"
#include <iostream>
#include <stdexcept>
using namespace std;

/**
 * Corinna Green
 * Project 3 - Linked Sequence Data Structure
 * CS - 3100 Data Structures
 * 10/13/25
 *
 * This project implements a doubly-linked list that stores a sequence of
 * string elements. The sequence supports operations such as push_back,
 * pop-back, insertion, deletion and access by index. The key features/ideas
 * used in this class include dynamic memory management, single and multiple
 * deletions via erase, ostream display, bound checking, and the "Big Three"
 * constructors: default, copy, and deconstruct; along with the assignment operator.
 *
 * Designed to use the SequenceDebug file and TestHarness to test the following code.
 */

/**
 * Constructs a Sequence of given size. Start with a sequence of 0 elements, or
 * create a sequence with sz elements initialized with an empty string.
 *
 * @param sz number of initialized elements
 */
Sequence::Sequence(size_t sz) : numElts(sz), head(nullptr), tail(nullptr) {
    for (size_t i = 0; i < sz; i++) {
        push_back(""); // initialize nodes using push back
    }
}

/**
 * Deep copy constructor. Create an independent copy of another sequence
 * object. This copies each element value from s into a new list for this
 * object.
 *
 *
 * @param s Sequence to be copied from.
 */
Sequence::Sequence(const Sequence &s) : numElts(0), head(nullptr), tail(nullptr) {
    SequenceNode *current = s.head; // node object to serve as the pointer for *this list

    while (current != nullptr) {
        // make sure pointer isn't pointing at nothing
        push_back(current->element); // Copy each element into this list
        current = current->next; // Move to the next node
    }
}

/**
 * Assignment operator.
 * Replaces the contents of the current Sequence with a deep copy of another Sequence.
 * This makes sure that the nodes in this list are deleted before initializing
 * and copying the new nodes.
 *
 * @param s Sequence object to copy from. (RHS).
 * @return Reference to the new Sequence object (LHS)
 */
Sequence &Sequence::operator=(const Sequence &s) {
    //Prevent shallow copy**
    if (this != &s) {
        // Checking if this sequence object = current object s (LHS = RHS)
        // Copying from: s (const - cannot be modified)
        // Assigning to: this

        // Delete any remaining nodes in the section we are using
        SequenceNode *current = head; // Start with the ptr to the first element of the list
        while (current != nullptr) {
            SequenceNode *newPointer = current; // temporary ptr for deletion
            current = current->next; // move ptr to the next before deleting current ptr
            delete newPointer; // delete current node's memory from heap
        }

        // Reset fields
        head = nullptr;
        tail = nullptr;
        numElts = 0;

        // Deep copy from sequence obj s
        SequenceNode *other = s.head;
        while (other != nullptr) {
            // make sure pointer isn't pointing at nothin from orig list
            push_back(other->element); // create new nodes in deep copied list
            current = other->next; // Move and add node to source list
        }
    }

    return *this; // Chaining: a=b=c
}

/**
 * Deconstructor.
 * Destroys all dynamically allocated memory in the nodes of the sequence.
 * This goes through the list, deleting each node.
 */
Sequence::~Sequence() {
    while (head != nullptr) {
        SequenceNode *newPointer = head;
        head = head->next; // Move head forward
        delete newPointer; // Delete old head ptr
    }
}

/**
 * Provides access to a specified element by index. Will throw exception if
 * the position is outside the sequence bounds.
 *
 * @param position Index of the desired element
 * @return Reference to the string element at the specific position.
 * @throws std::out_of_range if position >= numElts
 */
std::string &Sequence::operator[](size_t position) {
    if (position >= numElts) {
        throw std::out_of_range("Index is out of range");
    }

    SequenceNode *current = head;
    for (size_t i = 1; i < position; i++) {
        current = current->next; // Move forward position times
    }

    return current->element;
}

/**
 * Adds a new element to the end of the sequence. Dynamically allocates a new
 * node with the string item and attaches it to the tail end (becomes tail ptr)
 * of the list.
 *
 * @param item The string that is added to the sequence.
 */
void Sequence::push_back(std::string item) {
    // Note: doubly-linked list requires pointing forward and backward
    SequenceNode *newNode = new SequenceNode(item); // Create new node
    if (head == nullptr) {
        head = newNode; // list is empty -> new node will be both head and tail
        tail = newNode;
    } else {
        tail->next = newNode; // Attach item to the end
        newNode->prev = tail; // tail is right before newNode (must keep a pointer backward)
        tail = newNode; // New tail = added item
    }

    numElts++; // increment numElts
}

/**
 * Removes last element of the sequence. This deletes the tail node and
 * decreases the sequence by one. Throws an exception if the list is empty.
 *
 * @throws std::out_of_range if the sequence is empty.
 */
void Sequence::pop_back() {
    // An exception if there is no head and thus rest of the s
    if (head == nullptr) {
        throw std::out_of_range("Sequence is empty");
    } else if (head == tail) {
        // If there is only one node
        delete tail; // Delete the one node
        head = nullptr; // Make sure both are null
        tail = nullptr;
    } else {
        SequenceNode *oldTail = tail; // initialize old tail reference
        tail = tail->prev; // move tail back one node
        tail->next = nullptr; // Tail now points to end
        delete oldTail; // Delete old tail to prevent leak
    }

    numElts--; // Decrement element count
}

/**
 * Inserts a new node holding the item at the provided position in sequence.
 * Shifts the other nodes so that they "fit around" the new element. Throws
 * an exception if position is invalid.
 *
 * @param position The specified index where the new item should be inserted.
 * @param item The string value to insert
 * @throws std::out_of_range if position >= numElts
 */
void Sequence::insert(size_t position, std::string item) {
    if (position >= numElts) {
        throw std::out_of_range("Position is out of range");
    }

    SequenceNode *newNode = new SequenceNode(item);

    if (position == 0) {
        // insert beginning node
        newNode->next = head;

        // List empty check
        if (head != nullptr) {
            head->prev = newNode; // Update old head pointer
        }

        head = newNode;

        if (tail == nullptr) {
            // List is empty
            tail = newNode;
        }
    } else if (position == numElts) {
        // Insert at end
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    } else {
        // Insert in the middle
        SequenceNode *current = head;
        for (size_t i = 0; i < position; i++) {
            current = current->next;
        }

        // Link the new node between existing nodes
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }

    numElts++;
}

/**
 * Returns the first element in the sequence.
 *
 * @return The string stored in the head node.
 * @throws std::out_of_range if the sequence is null.
 */
std::string Sequence::front() const {
    if (head == nullptr) {
        throw std::out_of_range("Sequence is empty");
    }
    return head->element;
}

/**
 * Returns the last node in the sequence.
 *
 * @return The string stored in the tail node
 * @throws std::out_of_range if sequence is null.
 */
std::string Sequence::back() const {
    if (tail == nullptr) {
        throw std::out_of_range("Sequence is empty");
    }
    return tail->element;
}

/**
 * Checks if the sequence is empty.
 *
 * @return true if the sequence is empty, false otherwise.
 */
bool Sequence::empty() const {
    return head == nullptr && tail == nullptr;
}

/**
 * Returns the number of elements that are currently in the sequence.
 *
 * @return The total number of elements.
 */
size_t Sequence::size() const {
    return numElts;
}

/**
 * Clears the whole sequence.
 *
 * Deletes all nodes in the sequence and makes it empty. After clearing,
 * the sequence can still be reused by inserting items.
 */
void Sequence::clear() {
    SequenceNode *current = head;
    while (current != nullptr) {
        SequenceNode *newPointer = current->next;
        delete current;
        current = newPointer;
    }
    head = nullptr;
    tail = nullptr;
    numElts = 0;
}

/**
 * Removes one element from a specified position. It deletes the node at
 * its index and re-links the other nodes. Throws an exception if the
 * position is invalid.
 *
 * @param position The index of the element to remove.
 * @throws std::out_of_range if position >= numElts.
 */
void Sequence::erase(size_t position) {
    if (position >= numElts) {
        throw std::out_of_range("Position is out of range");
    }

    SequenceNode *current = head;
    for (size_t i = 0; i < position; i++) {
        current = current->next;
    }

    // Re-structure sequence FIRST

    // tail
    if (current->next != nullptr) {
        current->next->prev = current->prev; // Restore original element position
    } else {
        tail = current->prev; // Removing last element
    }

    // head
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
        head = current->next; // Remove first element
    }

    delete current; // Delete node and decrement list by one
    numElts--;
}

/**
 * Removes all nodes starting at the given position and continues to the
 * next counted elements. Will delete multiple elements in the sequence.
 *
 * @param position The starting index of removal.
 * @param count The number of consecutive elements to delete.
 * @throws std::out_of_range if position + count exceeds limit.
 */
void Sequence::erase(size_t position, size_t count) {
    if (position >= numElts || position + count >= numElts) {
        throw std::out_of_range("Position and/or count is out of range");
    }

    for (size_t i = 0; i < count; i++) {
        erase(position); // keep removing the same position
    }
}

/**
 * Outputs the sequence elements to an ostream in the following format:
 * " <item1, item2, item3> "
 *
 * @param os The output stream.
 * @param s The sequence object to print out.
 * @return Output stream object.
 */
ostream &operator<<(ostream &os, const Sequence &s) {
    os << "<";
    SequenceNode *current = s.head;
    while (current != nullptr) {
        os << current->element; // keep printing out elements
        if (current->next != nullptr) {
            // If next element is not null
            os << ", ";
        }

        current = current->next; // Move to next element
    }

    os << ">";
    return os; // Return ostream reference
}
