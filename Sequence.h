#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <cstddef> // For size_t
#include <stdexcept> // exceptions

class Sequence {

private:
    std::string* sequenceData; // pointer to the dynamic array of strings
    size_t numElts; // Keeps track of how many elements are stored
    size_t memory; // Tracks how much memory has been distributed so that we can grow the array when needed

public:
    // Default constructor, deconstructor, copy constructor
    Sequence(size_t sz = 0); // Default constructor
    Sequence(const Sequence& s); // Copy constructor (deep)
    ~Sequence(); // Deconstructor

    Sequence& operator=(const Sequence& s); // Assignment copy

    // Access for operator
    std::string& operator[](size_t position); // to access non-const element
    const std::string& operator[](size_t position) const; // to access const element

};

#endif
