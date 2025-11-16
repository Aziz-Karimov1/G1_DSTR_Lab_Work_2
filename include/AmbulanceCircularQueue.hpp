#ifndef AMBULANCECIRCULARQUEUE_HPP
#define AMBULANCECIRCULARQUEUE_HPP

#include "Models.hpp"
#include <iostream>

class AmbulanceCircularQueue {
private:
    Ambulance* arr;
    int capacity;
    int head;
    int tail;
    int count;
public:
    AmbulanceCircularQueue(int cap = 10); // default capacity 10
    ~AmbulanceCircularQueue();
    bool registerAmbulance(const Ambulance& a);
    bool rotateShift(); // moves head to tail
    void displaySchedule() const;
    bool isEmpty() const;
    bool isFull() const;
    int size() const;
};

#endif // AMBULANCECIRCULARQUEUE_HPP
