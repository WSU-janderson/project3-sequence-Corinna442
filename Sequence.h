#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <cstddef> // For size_t
#include <stdexcept> // exceptions


class SequenceNode {
public:

    SequenceNode* next; // pointer to the next node
    SequenceNode* prev; // pointer to previous node
    std::string element; // value stored

    SequenceNode() : next(nullptr), prev(nullptr) {} // default constructor
    SequenceNode(std::string element) : next(nullptr), prev(nullptr), element(element) {} // constructor with params

};

class Sequence {

private:
    SequenceNode* head;
    SequenceNode* tail;
    size_t numElts; // Keeps track of how many elements are stored
    //Sequence

public:
    // Default constructor, deconstructor, copy constructor
    Sequence(size_t sz = 0); // Default constructor
    Sequence(const Sequence& s); // Copy constructor (deep)
    ~Sequence(); // Deconstructor

    Sequence& operator=(const Sequence& s); // Assignment copy

    // Access for operator
    std::string& operator[](size_t position); // to access non-const element
    const std::string& operator[](size_t position) const; // to access const element

    // Mutable methods
    void push_back(std::string element);
    void pop_back();
    void insert(size_t position, std::string element);
    void erase(size_t position);
    void erase(size_t position, size_t count);
    void clear();

    // Getters
    std::string front() const;
    std::string back() const;
    bool empty() const;
    size_t size() const;

    // Friend method for printing sequence
    // **Can only use friend keyword in .h**
    friend std::ostream& operator<<(std::ostream& os, const Sequence& s);
};

#endif
