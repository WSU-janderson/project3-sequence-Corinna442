/**
 * SequenceDebug.cpp
 * Project 3
 * CS 3100
 *
 * In this file, you will write your tests as you implement Sequence. If you are using CLion, you need to select
 * SequenceDebug from the drop-down menu next to the Build (hammer icon) if it is on SequenceTestHarness
 */
#include <iostream>
#include "Sequence.h"

using namespace std;

int main() {

    Sequence s;

    cout << "Push back elements: " << endl;
    s.push_back("Red");
    s.push_back("Green");
    s.push_back("Blue");
    s.push_back("Yellow");
    s.pop_back();

    cout << "Sequence: " << s << endl;
    // push and pop work

    cout << "Front element: " << s.front() << endl;
    cout << "Back element: " << s.back() << endl;

    cout << "Erase position 1" << endl;
    s.erase(0);
    cout << s << endl;

    cout << "Insert Purple at position 0: " << endl;
    s.insert(0, "Purple");
    cout << "Sequence: " << s << endl;
    // ???

    // Clear sequence
    s.clear();
    cout << "Is sequence empty? (bool): " << endl;
    cout << boolalpha << s.empty() << endl;
    cout << s << endl;



    return 0;
}