//
// Created by User on 20.09.2021.
//

#ifndef CTCI_LINKEDLIST_H
#define CTCI_LINKEDLIST_H

#include "LLNode.h"

class LinkedList {
public:
    LinkedList() = default;
    ~LinkedList() = default;

    static void RemoveDuplicate(Node* head);
    static Node* FindKthtoLast(Node* head, int k);
    static Node* FindKthtoLastRecursive(Node* head, int k, int& i);
    static void DeleteMiddleNode(Node* node);
    static Node* Partition(Node* head, int x);
    static Node* SumList(Node* head1, Node* head2);
    static Node* SumListRecursive(Node* head1, Node* head2, int carry);
    static Node* SumListRecursiveForwardOrder(Node* head1, Node* head2);
    static bool CheckPalindrome(Node* head);
    static Node* Intersect(Node* head1, Node* head2);
    static Node* DetectLoop(Node* head);
    static void PrintLinkedList(Node* head);
    static void ClearList(Node* head);

private:
    struct PaddingNode {
        PaddingNode(Node* n, bool res) {
            node = n;
            result = res;
        }

        Node* node = nullptr;
        bool result = false;
    };

    static Node* DeleteNode(Node* head, int d);
    static void AddPadding(Node* & node, int count);
    static int GetSize(Node* head);
    static int SumListRecursiveForwardOrderHelper(Node* head1, Node* head2, Node* sum);
    static PaddingNode* CheckPalindromeRecursive(Node* head, int size);
    static bool CheckPalindromeRecursive(Node* head, int size, Node* &next);
};

#endif //CTCI_LINKEDLIST_H
