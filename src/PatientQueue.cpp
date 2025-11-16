#include "PatientQueue.hpp"

PatientQueue::PatientQueue(): head(nullptr), tail(nullptr), count(0) {}

PatientQueue::~PatientQueue() {
    while (head) {
        Node* t = head;
        head = head->next;
        delete t;
    }
}

void PatientQueue::admitPatient(const Patient& p) {
    Node* n = new Node(p);
    if (!tail) {
        head = tail = n;
    } else {
        tail->next = n;
        tail = n;
    }
    ++count;
    std::cout << "Admitted patient: " << p.name << " (ID " << p.id << ")\n";
}

bool PatientQueue::dischargePatient(Patient& out) {
    if (!head) return false;
    Node* n = head;
    out = n->p;
    head = head->next;
    if (!head) tail = nullptr;
    delete n;
    --count;
    std::cout << "Discharged patient: " << out.name << " (ID " << out.id << ")\n";
    return true;
}

void PatientQueue::viewQueue() const {
    Node* cur = head;
    if (!cur) {
        std::cout << "[Patient queue is empty]\n";
        return;
    }
    std::cout << "Patients waiting (FIFO):\n";
    while (cur) {
        std::cout << "  ID: " << cur->p.id << " | Name: " << cur->p.name << " | Condition: " << cur->p.condition << "\n";
        cur = cur->next;
    }
}

bool PatientQueue::isEmpty() const { return head == nullptr; }

int PatientQueue::size() const { return count; }
