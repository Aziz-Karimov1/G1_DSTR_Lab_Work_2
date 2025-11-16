#ifndef PATIENTQUEUE_HPP
#define PATIENTQUEUE_HPP

#include "Models.hpp"
#include <iostream>

class PatientQueue {
private:
    struct Node {
        Patient p;
        Node* next;
        Node(const Patient& pt): p(pt), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int count;
public:
    PatientQueue();
    ~PatientQueue();
    void admitPatient(const Patient& p);
    bool dischargePatient(Patient& out);
    void viewQueue() const;
    bool isEmpty() const;
    int size() const;
};

#endif // PATIENTQUEUE_HPP
