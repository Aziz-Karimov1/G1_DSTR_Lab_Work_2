#ifndef SUPPLYSTACK_HPP
#define SUPPLYSTACK_HPP

#include "Models.hpp"
#include <iostream>

class SupplyStack {
private:
    struct Node {
        Supply s;
        Node* next;
        Node(const Supply& sup): s(sup), next(nullptr) {}
    };
    Node* topNode;
    int count;
public:
    SupplyStack();
    ~SupplyStack();
    void addSupply(const Supply& s);
    bool useLastAdded(Supply& out);
    void viewSupplies() const;
    bool isEmpty() const;
    int size() const;
};

#endif // SUPPLYSTACK_HPP
