#include <iostream>
#include <vector>

#include "function.h"

IQueue::IQueue(IQueue const& rhs) {
    capacity = rhs.capacity;
    size = rhs.size;
    front = 0;
    data = new int[capacity];
    for(int i=rhs.front;i<rhs.front+size;i++){
        data[i-rhs.front] = rhs.data[i];
    }
}
IQueue::IQueue(IQueue&& rhs) {
    capacity = rhs.capacity;
    size = rhs.size;
    front = rhs.front;
    data = rhs.data;
    rhs.data = nullptr;
}
IQueue& IQueue::operator=(IQueue const& rhs) {
    if (this == &rhs) return *this; // FIXME new-> 5,6 wrong
    capacity = rhs.capacity;
    size = rhs.size;
    delete[] data;
    data = new int[capacity];
    for(int i=(rhs.front);i<(rhs.front)+size;i++){
        data[i-rhs.front] = rhs.data[i];
    }
    front = 0;
    return *this;
}
IQueue& IQueue::operator=(IQueue&& rhs) {
    if (this == &rhs) return *this; // FIXME new -> 5,6 wrong
    capacity = rhs.capacity;
    size = rhs.size;
    data = rhs.data;
    front = rhs.front;
    rhs.data = nullptr; // FIXME new -> 5,6,7 wrong
    return *this;
}
IQueue::~IQueue() {
    if(data) delete[] data;
}
void IQueue::Push(int val) {
    data[front+size] = val;
    ++size;
    if (front+size == capacity) DoubleCapacity();
}
void IQueue::Pop(void) {
    front++;
    size--;
}
int& IQueue::Front(void) {
    return data[front];
}
int& IQueue::operator[](size_t pos) {
    return data[front+pos];
}
int& IQueue::At(size_t pos) {
    if(pos<size) return data[front+pos];
    else throw std::out_of_range("Out of range");
}
void IQueue::Swap(IQueue& other) {
    IQueue tmp = std::move(*this);
    *this = std::move(other);
    other = std::move(tmp);
}
bool IQueue::Empty(void) const {
    if(!size) return 1;
    else return 0;
}
void IQueue::DoubleCapacity(void) {
    capacity *= 2;
    int *temp = new int[capacity];
    for(int i=front;i<front+size;i++){
        temp[i-front] = data[i];
    }
    front = 0;
    delete[] data;
    data = temp;
}

using namespace std;

void Swap(IQueue& a, IQueue& b) {
    IQueue tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

int main() {
    int n;
    cin >> n;
    vector<IQueue> queues;
    string command;
    for (int i = 0; i < n; ++i) {
        cin >> command;
        if (command == "NEW")
            queues.emplace_back();
        else if (command == "PUSH") {
            size_t idx;
            int val;
            cin >> idx >> val;
            queues[idx].Push(val);
        } else if (command == "POP") {
            size_t idx;
            cin >> idx;
            if (!queues[idx].Empty())
                queues[idx].Pop();
            else
                cout << "Queue is empty\n";
        } else if (command == "PRINTFRONT") {
            size_t idx;
            cin >> idx;
            if (!queues[idx].Empty())
                cout << queues[idx].Front() << '\n';
            else
                cout << "Queue is empty\n";
        } else if (command == "ASSIGNFRONT") {
            size_t idx;
            int val;
            cin >> idx >> val;
            if (!queues[idx].Empty())
                queues[idx].Front() = val;
            else
                cout << "Queue is empty\n";
        } else if (command == "PRINT[]") {
            size_t idx, pos;
            cin >> idx >> pos;
            if (pos < queues[idx].Size())
                cout << queues[idx][pos] << '\n';
            else
                cout << "Out of range\n";
        } else if (command == "ASSIGN[]") {
            size_t idx, pos;
            int val;
            cin >> idx >> pos >> val;
            if (pos < queues[idx].Size())
                queues[idx][pos] = val;
            else
                cout << "Out of range\n";
        } else if (command == "PRINTAT") {
            size_t idx, pos;
            cin >> idx >> pos;
            try {
                cout << queues[idx].At(pos) << '\n';
            } catch (out_of_range const& e) {
                cout << e.what() << '\n';
            }
        } else if (command == "ASSIGNAT") {
            size_t idx, pos;
            int val;
            cin >> idx >> pos >> val;
            try {
                queues[idx].At(pos) = val;
            } catch (out_of_range const& e) {
                cout << e.what() << '\n';
            }
        } else if (command == "SWAP1") {
            size_t idx1, idx2;
            cin >> idx1 >> idx2;
            queues[idx1].Swap(queues[idx2]);
        } else if (command == "SWAP2") {
            size_t idx1, idx2;
            cin >> idx1 >> idx2;
            Swap(queues[idx1], queues[idx2]);
        } else if (command == "COPY") {
            size_t idx1, idx2;
            cin >> idx1 >> idx2;
            queues[idx1] = queues[idx2];
        } else if (command == "EMPTY") {
            size_t idx;
            cin >> idx;
            cout << queues[idx].Empty() << '\n';
        } else if (command == "SIZE") {
            size_t idx;
            cin >> idx;
            cout << queues[idx].Size() << '\n';
        }
    }
}
