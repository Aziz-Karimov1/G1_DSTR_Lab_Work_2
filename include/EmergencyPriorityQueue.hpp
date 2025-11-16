#ifndef EMERGENCYPRIORITYQUEUE_HPP
#define EMERGENCYPRIORITYQUEUE_HPP

#include "Models.hpp"
#include <iostream>

class EmergencyPriorityQueue {
private:
    struct Node {
        EmergencyCase e;
        Node* next;
        Node(const EmergencyCase& em): e(em), next(nullptr) {}
    };
    Node* head; // highest priority at head (largest priority value)
    int count;
public:
    EmergencyPriorityQueue();
    ~EmergencyPriorityQueue();
    void logEmergency(const EmergencyCase& e);
    bool processMostCritical(EmergencyCase& out);
    void viewPending() const;
    bool isEmpty() const;
    int size() const;
};

#endif // EMERGENCYPRIORITYQUEUE_HPP
