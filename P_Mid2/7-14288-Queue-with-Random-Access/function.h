#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>

class IQueue {
private:
    size_t capacity;
    size_t size;
    size_t front;
    int* data;

    void DoubleCapacity(void);

public:
    IQueue() : capacity(1), size(0), front(0), data(new int[1]) {}
    IQueue(IQueue const& rhs);
    IQueue(IQueue&& rhs);
    IQueue& operator=(IQueue const& rhs);
    IQueue& operator=(IQueue&& rhs);
    ~IQueue();

    void Push(int val);
    void Pop(void);
    [[nodiscard]] int& Front(void);
    [[nodiscard]] int& operator[](size_t pos);
    [[nodiscard]] int& At(size_t pos);

    void Swap(IQueue& other);

    [[nodiscard]] bool Empty(void) const;
    [[nodiscard]] size_t Size(void) const { return size; }
};

#endif

// Implement the above function in a `.cpp` file
// You might start with the following codes:

/*
#include "function.h"

IQueue::IQueue(IQueue const& rhs) {
    // Implement here
}
IQueue::IQueue(IQueue&& rhs) {
    // Implement here
}
IQueue& IQueue::operator=(IQueue const& rhs) {
    // Implement here
}
IQueue& IQueue::operator=(IQueue&& rhs) {
    // Implement here
}
IQueue::~IQueue() {
    // Implement here
}

void IQueue::Push(int val) {
    if (size == capacity) DoubleCapacity();
    // Implement here
}
void IQueue::Pop(void) {
    // Implement here
}
int& IQueue::Front(void) {
    // Implement here
}
int& IQueue::operator[](size_t pos) {
    // Implement here
}
int& IQueue::At(size_t pos) {
    // Implement here
}

void IQueue::Swap(IQueue& other) {
    // Implement here
}

bool IQueue::Empty(void) const {
    // Implement here
}

void IQueue::DoubleCapacity(void) {
    // Implement here
}

*/
