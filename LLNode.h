//
// Created by User on 20.09.2021.
//

#ifndef CTCI_LLNODE_H
#define CTCI_LLNODE_H

class Node {
public:
    Node* next;
    int data;

    explicit Node(int d) {
        data = d;
        next = nullptr;
    }

    void appendToTail(int d) {
        Node* end = new Node(d);
        Node* n = this;

        while (n->next != nullptr) {
            n = n->next;
        }

        n->next = end;
    }

    void appendToTail(Node* node) {
        Node* n = this;

        while (n->next != nullptr) {
            n = n->next;
        }

        n->next = node;
    }
};

#endif //CTCI_LLNODE_H
