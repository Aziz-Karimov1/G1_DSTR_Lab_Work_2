#include "EmergencyPriorityQueue.hpp"

EmergencyPriorityQueue::EmergencyPriorityQueue(): head(nullptr), count(0) {}
EmergencyPriorityQueue::~EmergencyPriorityQueue() {
    while (head) {
        Node* t = head;
        head = head->next;
        delete t;
    }
}

void EmergencyPriorityQueue::logEmergency(const EmergencyCase& e) {
    Node* n = new Node(e);
    if (!head || e.priority > head->e.priority) {
        n->next = head;
        head = n;
    } else {
        Node* cur = head;
        while (cur->next && cur->next->e.priority >= e.priority) cur = cur->next;
        n->next = cur->next;
        cur->next = n;
    }
    ++count;
    std::cout << "Logged emergency: " << e.patientName << " | " << e.emergencyType << " | priority " << e.priority << "\n";
}

bool EmergencyPriorityQueue::processMostCritical(EmergencyCase& out) {
    if (!head) return false;
    Node* n = head;
    out = n->e;
    head = head->next;
    delete n;
    --count;
    std::cout << "Processing emergency: " << out.patientName << " (priority " << out.priority << ")\n";
    return true;
}

void EmergencyPriorityQueue::viewPending() const {
    if (!head) {
        std::cout << "[No pending emergency cases]\n";
        return;
    }
    std::cout << "Pending emergency cases (highest priority first):\n";
    Node* cur = head;
    while (cur) {
        std::cout << "  Patient: " << cur->e.patientName << " | Type: " << cur->e.emergencyType << " | Priority: " << cur->e.priority << "\n";
        cur = cur->next;
    }
}

bool EmergencyPriorityQueue::isEmpty() const { return head == nullptr; }
int EmergencyPriorityQueue::size() const { return count; }
