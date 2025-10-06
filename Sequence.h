#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <cstddef> // For size_t
#include <stdexcept> // exceptions

class Sequence {
private:

std::string* sequenceData;
size_t numElts;
size_t memory;

public:

// Default constructor, deconstructor, copy constructor
Sequence(size_t sz = 0); // Default constructor
Sequence(const Sequence& s); // Copy constructor (deep)
~Sequence(); // Deconstructor

Sequence& operator=(const Sequence& s); // Assignment copy


};

#endif
