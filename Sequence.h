#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <cstddef> // For size_t
#include <stdexcept> // exceptions

/**
 * Represents *a* node in a doubly-linked list.
 *
 * Each node stores a string element and has pointers to the next and
 * previous nodes in the sequence.
 */
class SequenceNode {
public:
    SequenceNode *next; // pointer to the next node
    SequenceNode *prev; // pointer to previous node
    std::string element; // value stored

    SequenceNode() : next(nullptr), prev(nullptr) {
    } // default constructor
    SequenceNode(std::string element) : next(nullptr), prev(nullptr), element(element) {
    } // constructor with params
};

/**
 * Doubly linked list for storing string sequences. It is used to create and
 * modify a sequence of strings. It manages memory and ensures no memory
 * leaks happen.
 */
class Sequence {
private:
    SequenceNode *head; // Pointer for the first node in the list
    SequenceNode *tail; // Pointer to the last node in the list
    size_t numElts; // Keeps track of how many elements are stored

public:
    Sequence(size_t sz = 0); // Default constructor
    Sequence(const Sequence &s); // Copy constructor (deep)
    ~Sequence(); // Deconstructor

    Sequence &operator=(const Sequence &s); // Assignment copy

    // Access for operator
    std::string &operator[](size_t position); // Returns a reference to the element at the specified index.

    // Mutable methods
    void push_back(std::string element); // Adds an element to the end of the sequence.
    void pop_back(); //Removes the last element of the sequence.
    void insert(size_t position, std::string element); // Inserts an element at the given position.
    void erase(size_t position); // Removes an element at the specified position.
    void erase(size_t position, size_t count); // Removes multiple elements starting at given position.
    void clear(); // Clears all elements from the sequence.

    // Getters
    std::string front() const; // Returns the first element in the sequence.
    std::string back() const; // Returns the last element in the sequence.
    bool empty() const; // Checks if the sequence in empty.
    size_t size() const; // Returns the number of elements in the sequence.

    // Friend method for printing sequence
    // **Can only use friend keyword in .h**
    friend std::ostream &operator<<(std::ostream &os, const Sequence &s);
};

#endif
