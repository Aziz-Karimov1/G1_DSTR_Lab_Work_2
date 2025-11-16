#include "SupplyStack.hpp"

SupplyStack::SupplyStack(): topNode(nullptr), count(0) {}
SupplyStack::~SupplyStack() {
    while (topNode) {
        Node* t = topNode;
        topNode = topNode->next;
        delete t;
    }
}

void SupplyStack::addSupply(const Supply& s) {
    Node* n = new Node(s);
    n->next = topNode;
    topNode = n;
    ++count;
    std::cout << "Added supply: " << s.type << " (" << s.quantity << "), batch " << s.batch << "\n";
}

bool SupplyStack::useLastAdded(Supply& out) {
    if (!topNode) return false;
    Node* n = topNode;
    out = n->s;
    topNode = topNode->next;
    delete n;
    --count;
    std::cout << "Used supply: " << out.type << " (" << out.quantity << "), batch " << out.batch << "\n";
    return true;
}

void SupplyStack::viewSupplies() const {
    if (!topNode) {
        std::cout << "[No supplies available]\n";
        return;
    }
    Node* cur = topNode;
    std::cout << "Supplies (top -> bottom):\n";
    while (cur) {
        std::cout << "  Type: " << cur->s.type << " | Qty: " << cur->s.quantity << " | Batch: " << cur->s.batch << "\n";
        cur = cur->next;
    }
}

bool SupplyStack::isEmpty() const { return topNode == nullptr; }
int SupplyStack::size() const { return count; }
