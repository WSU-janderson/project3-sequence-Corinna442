#include "Sequence.h"
#include <iostream>

// Creates an empty sequence (numElts == 0) or a sequence of numElts items
// indexed from 0 ... (numElts - 1).
// Constructor (initializer list)

Sequence::Sequence(size_t sz) : numElts(sz), memory(sz) {

    sequenceData = new std::string[memory]; // allocated memory

}

// Copy constructor (deep) of sequence s
Sequence::Sequence(const Sequence& s) : numElts(s.numElts), memory(s.numElts) {
    sequenceData = new std::string[memory]; // allocated memory (again for new copy)

    // creates each element slot in the sequence object s
    for (size_t i = 0; i < numElts; i++) {
        sequenceData[i] = s.sequenceData[i];
    }
}

// The current sequence is released and replaced by a (deep) copy of sequence
// s. A reference to the copied sequence is returned (return *this;)
// Assignment operator
Sequence& Sequence::operator=(const Sequence& s) {
    // Check so that delete[] will not wipe out the memory we need to use
    // to copy
    if (this != &s) { // Checking if current object s = this sequence object (RHS = LHS)
        delete[] sequenceData; // free old memory for this block

        numElts = s.numElts; // copy size of sequence
        memory = s.memory; // copy memory/capacity

        sequenceData = new std::string[memory]; // Allocate new memory for this sequence
        for (size_t i = 0; i < numElts; i++) {
            sequenceData[i] = s.sequenceData[i]; // Copy each element from first s array obj to a new array obj
        }
    }

    return *this; // Chaining: a=b=c

}

// Destroys all items in the sequence and release the memory
// associated with the sequence.
// Deconstructor
Sequence::~Sequence() {
    delete[] sequenceData;
}

// The position satisfies ( position >= 0 && position <= last_index() ).
// The return value is a reference to the item at index position in the
// sequence. Throws an exception if the position is outside the bounds
// of the sequence.
// Operator[]
std::string& Sequence::operator[](size_t position) {
    if (position >= numElts) {
        throw std::out_of_range("Index is out of range");
    }
    return sequenceData[position];
}








void Sequence::push_back(std::string item)
// The item at the end of the sequence is deleted and size of the sequence is
// reduced by one. If sequence was empty, throws an exception
void Sequence::pop_back()
// The position satisfies ( position >= 0 && position <= last_index() ). The
// value of item is inserted at position and the size of sequence is increased
// by one. Throws an exceptionif the position is outside the bounds of the
// sequence
void Sequence::insert(size_t position, std::string item)
// Returns the first element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::front() const
// Return the last element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::back() const
// Return true if the sequence has no elements, otherwise false.
bool Sequence::empty() const
// Return the number of elements in the sequence.
size_t Sequence::size() const
// sequence is released, resetting the sequence to an empty state that can have
 // items re-inserted.
 void Sequence::clear()
 // The item at position is removed from the sequence, and the memory
 // is released. If called with an invalid position throws an exception.
 void Sequence::erase(size_t position)
 // The items in the sequence at ( position ... (position + count - 1) ) are
 // deleted and their memory released. If called with invalid position and/or
 // count throws an exception.
 void Sequence::erase(size_t position, size_t count)
 // Outputs all elements (ex: <4, 8, 15, 16, 23, 42>) as a string to the output
 // stream. This is *not* a method of the Sequence class, but instead it is a
 // friend function
 friend ostream& operator<<(ostream& os, const Sequence& s)