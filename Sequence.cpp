#include "Sequence.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Creates an empty sequence (numElts == 0) or a sequence of numElts items
// indexed from 0 ... (numElts - 1).
// Constructor (initializer list)

Sequence::Sequence(size_t sz) : numElts(sz), head(nullptr), tail(nullptr) {

    for (size_t i = 0; i < sz; i++) {
        push_back(""); // initialize nodes using push back
    }

}

// Copy constructor (deep) of sequence s
Sequence::Sequence(const Sequence& s) : numElts(0), head(nullptr), tail(nullptr) {
    SequenceNode* current = s.head; // node object to serve as the pointer for *this list

    while (current != nullptr) { // make sure pointer isn't pointing at nothin
        push_back(current->element); // create new nodes in deep copied list
        current = current->next; // add nodes
    }

}

// The current sequence is released and replaced by a (deep) copy of sequence
// s. A reference to the copied sequence is returned (return *this;)
// Assignment operator
Sequence& Sequence::operator=(const Sequence& s) {
    // Check so that delete[] will not wipe out the memory we need to use
    // to copy
    if (this != &s) {
        // Checking if current object s = this sequence object (RHS = LHS)

        // Delete memory after usage to prevent leaks
        SequenceNode* current = s.head; // Start with the ptr to the first element of the list
        while (current != nullptr) { // keep going until it reaches the end
            SequenceNode* newPointer = current; // temporary ptr- so that we can safely delete current node after continuing forward
            current = current->next; // move ptr to the next before deleting current ptr
            delete newPointer; // delete current node's memory from heap
        }

        // Reset fields so that everything is empty
        head = nullptr;
        tail = nullptr;
        numElts = 0;

        // Deep copy from sequence obj s
        SequenceNode* other = s.head;
        while (other != nullptr) { // make sure pointer isn't pointing at nothin
            push_back(other->element); // create new nodes in deep copied list
            current = other->next; // add nodes
        }

    }

        return *this; // Chaining: a=b=c


}

// Destroys all items in the sequence and release the memory
// associated with the sequence.
// Deconstructor
Sequence::~Sequence() {
    while (head != nullptr) {
        SequenceNode* newPointer = head;
        head = head->next;
        delete newPointer;
    }
}

// The position satisfies ( position >= 0 && position <= last_index() ).
// The return value is a reference to the item at index position in the
// sequence. Throws an exception if the position is outside the bounds
// of the sequence.
// Operator[]
std::string& Sequence::operator[](size_t position) {
    if (position >= numElts) {
        throw std::out_of_range("Index is out of range");

        SequenceNode* current = head;
        for (size_t i = 1; i < position; i++) {
            current = current->next;
        }

        return current->element;
    }
}

// pop_back
void Sequence::push_back(std::string item) {
    SequenceNode* newNode = new SequenceNode(item);
    if (head == nullptr) {
        head = newNode; // list is empty -> new node will be both head and tail
        tail = newNode;
    } else {
        tail->next = newNode; // Attach item to the end
        newNode->prev = tail; // tail is right before newNode (must keep a pointer backward)
        tail = newNode;
    }

    numElts++; // increment numElts
}

// The item at the end of the sequence is deleted and size of the sequence is
// reduced by one. If sequence was empty, throws an exception
void Sequence::pop_back() {
    if (head == nullptr) {
        throw std::out_of_range("Sequence is empty");
    }
    else if (head == tail) {
        delete tail;
        head = nullptr;
        tail = nullptr;
    } else {
        SequenceNode* oldTail = tail;

        tail = tail->prev; // move tail back one node
        tail->next = nullptr;
        delete oldTail; // Delete old tail to prevent leak
    }

    numElts--; // decrement

}

// The position satisfies ( position >= 0 && position <= last_index() ). The
// value of item is inserted at position and the size of sequence is increased
// by one. Throws an exceptionif the position is outside the bounds of the
// sequence
void Sequence::insert(size_t position, std::string item) {
    if (position >= numElts) {
        throw std::out_of_range("Position is out of range");
    }

    SequenceNode* newNode = new SequenceNode(item);

    if (position == 0) {
        // insert beginning node
        newNode->next = head;

        // List empty check
        if (head == nullptr) {
            head->prev = newNode;
        }

        head = newNode;

        if (tail == nullptr) {
            tail = newNode;
        }
    } else if (position == numElts) {
        // Insert at end
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    } else {
        // Insert in the middle
        SequenceNode* current = head;
        for (size_t i = 0; i < position; i++) {
            current = current->next;
        }

        newNode->next = current; // points to node position
        newNode->prev = current->prev; // points to next node position
        current->prev->next = newNode;
        current->prev = newNode;
    }

    numElts++;
}

// Returns the first element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::front() const {
    if (head == nullptr) {
        throw std::out_of_range("Sequence is empty");
    }
    return head->element;
}

// Return the last element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::back() const {
    if (tail == nullptr) {
        throw std::out_of_range("Sequence is empty");
    }
    return tail->element;

}

// Return true if the sequence has no elements, otherwise false.
bool Sequence::empty() const {
    return head == nullptr && tail == nullptr; // Empty if head and tail are null
}

// Return the number of elements in the sequence.
size_t Sequence::size() const {
    return numElts;
}

// sequence is released, resetting the sequence to an empty state that can have
 // items re-inserted.
 void Sequence::clear() {
    SequenceNode* current = head;
    while (current != nullptr) {
        SequenceNode* newPointer = current->next;
        delete current;
        current = newPointer;
    }
    head = nullptr;
    tail = nullptr;
    numElts = 0;
}

 // The item at position is removed from the sequence, and the memory
 // is released. If called with an invalid position throws an exception.
// Remove a single element from the list at a specific position
 void Sequence::erase(size_t position) {
    if (position >= numElts) {
        throw std::out_of_range("Position is out of range");
    }

    SequenceNode* current = head;
    for (size_t i = 0; i < position; i++) {
        current = current->next;
    }

    // Re-structure sequence FIRST

    // tail
    if (current->next != nullptr) {
        current->next->prev = current->prev; // restore original element pos
    } else {
        tail = current->prev; // removing last element
    }

    // head
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
        head = current->next; // remove first element
    }

    delete current;
    numElts--;
}

 // The items in the sequence at ( position ... (position + count - 1) ) are
 // deleted and their memory released. If called with invalid position and/or
 // count throws an exception.
 void Sequence::erase(size_t position, size_t count) {
     if (position >= numElts || position + count >= numElts) {
         throw std::out_of_range("Position and/or count is out of range");
     }

    for (size_t i = 0; i < count; i++) {
        erase(position); // keep removing the same position
    }
}

 // Outputs all elements (ex: <4, 8, 15, 16, 23, 42>) as a string to the output
 // stream. This is *not* a method of the Sequence class, but instead it is a
 // friend function
 ostream& operator<<(ostream& os, const Sequence& s) {
    os << "<";
    SequenceNode* current = s.head;
    while (current != nullptr) {
        os << current->element; // keep printing out elements
        if (current->next != nullptr) { // next element
            os << ", ";
        }

        current = current->next;

    }

    os << ">";
    return os;
}