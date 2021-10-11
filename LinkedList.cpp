//
// Created by User on 20.09.2021.
//

#include "LinkedList.h"
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <stack>

#define COND_Q1 2
#define COND_Q2 2
#define COND_Q4 1
#define COND_Q5 2
#define COND_Q6 4
#define COND_Q7 3

using namespace std;

Node *LinkedList::DeleteNode(Node *head, int d) {
    Node* n = head;

    if (n->data == d) {
        cout << "deleted" << endl;
        return head->next; /* moved head*/
    }

    while (n->next != nullptr) {
        if (n->next->data == d) {
            n->next = n->next->next;
            return head; /* head didn't change*/
        }

        n = n->next;
    }

    return head;
}

void LinkedList::PrintLinkedList(Node *head) {
    Node* n = head;

    while (n != nullptr) {
        cout << n->data << " ";
        n = n->next;
    }
    cout << endl;
}

void LinkedList::ClearList(Node *head) {
    Node* n = head;
    Node* t = nullptr;
    while (nullptr != n) {
        t = n;
        n = n->next;
        delete t;
        t = nullptr;
    }
}

void LinkedList::RemoveDuplicate(Node *head) {
#if COND_Q1 == 1
    Node* n = head;

    while (n != nullptr) {
        Node* t = n->next;
        Node* p = n;

        while (t != nullptr) {
            if (t->data == n->data)
                p->next = t->next;
            else
                p = t;

            t = t->next;
        }

        n = n->next;
    }
#else
    unordered_set<int> set;
    Node* n = head;
    Node* t = n->next;

    set.insert(n->data);
    while (t != nullptr) {
        if (set.find(t->data) == set.end()) {
            set.insert(t->data);
            n = t;
        } else {
            n->next = t->next;
        }

        t = t->next;
    }
#endif
}

Node *LinkedList::FindKthtoLast(Node *head, int k) {
#if COND_Q2 == 1
    int i = 0;
    Node* n = head;
    Node* res = nullptr;
    while (nullptr != n) {
        n = n->next;
        ++i;
        if (i == k + 1)
            res = head;
        else if (i > k + 1)
            res = res->next;
    }

    return res;
#else
    Node* n = head;
    Node* runner = n->next;
    for (int i = 0; i < k; ++i) {
        if (nullptr != runner)
            runner = runner->next;
        else
            return nullptr;
    }

    while (nullptr != runner) {
        runner = runner->next;
        n = n->next;
    }

    return n;
#endif
}

Node *LinkedList::FindKthtoLastRecursive(Node *head, int k, int &i) {
    if (nullptr == head)
        return nullptr;

    Node* res = FindKthtoLastRecursive(head->next, k, i);
    if (i++ == k)
        return head;

    return res;
}

void LinkedList::DeleteMiddleNode(Node *node) {
    if (nullptr == node || nullptr == node->next)
        return;

    Node* next = node->next;
    node->data = next->data;
    node->next = next->next;
}

Node* LinkedList::Partition(Node *head, int x) {
    if (nullptr == head || nullptr == head->next)
        return nullptr;

    Node dummy(x);
    Node* prev = nullptr;
    Node* next = nullptr;
    Node* p = head;
    while (nullptr != p) {
        if (p->data < x) {
            if (nullptr == prev) {
                prev = p;
                p = p->next;
                prev->next = &dummy;
            } else {
                Node* t = p;
                p = p->next;

                t->next = prev;
                prev = t;
            }
        } else if (p->data > x) {
            if (nullptr == next) {
                next = p;
                dummy.next = p;
                p = p->next;

                next->next = nullptr;
            } else {
                Node* t = p;
                p = p->next;

                next->next = t;
                t->next = nullptr;
                next = t;
            }
        } else {
            Node* t = p;
            p = p->next;
            if (nullptr == next) {
                dummy.next = t;
                next = t;
                next->next = nullptr;
            } else {
                t->next = dummy.next;
                dummy.next = t;
            }
        }
    }

    if (prev == &dummy) {
        prev = prev->next;
        return prev;
    }

    if (nullptr == prev) {
        prev = dummy.next;
        return prev;
    }

    Node* t1 = prev->next;
    Node* t2 = prev;
    while (nullptr != t1) {
        if (t1 == &dummy) {
            t2->next = t1->next;
            t1 = t2->next;
            break;
        } else {
            t2 = t1;
            t1 = t1->next;
        }
    }

    return prev;
}

Node *LinkedList::SumList(Node *head1, Node *head2) {
    Node* p1 = head1;
    Node* p2 = head2;

    Node* sumList = new Node(0);
    int carry = 0;
    int sum = 0;
    while (true) {
        if (nullptr == p1 && nullptr == p2)
            break;

        if (nullptr != p1) {
            sum = p1->data;
            p1 = p1->next;
        }

        if (nullptr != p2) {
            sum += p2->data;
            p2 = p2->next;
        }

        sum += carry;
        carry = sum / 10;
        sumList->appendToTail(sum % 10);
    }

    if (carry == 1)
        sumList->appendToTail(carry);

    Node* temp = sumList;
    sumList = sumList->next;
    delete temp;

    return sumList;
}

Node *LinkedList::SumListRecursive(Node *head1, Node *head2, int carry) {
    if (nullptr == head1 && nullptr == head2 && carry == 0)
        return nullptr;

    int sum = carry;
    if (nullptr != head1)
        sum += head1->data;

    if (nullptr != head2)
        sum += head2->data;

    Node* sumList = new Node(sum % 10);

    if (nullptr != head1 || nullptr != head2) {
        Node* res  = SumListRecursive(nullptr != head1 ? head1->next : nullptr,
                                      nullptr != head2 ? head2->next : nullptr,
                                      sum / 10);
        sumList->next = res;
    }

    return sumList;
}

Node *LinkedList::SumListRecursiveForwardOrder(Node *head1, Node *head2) {
    int count1 = GetSize(head1);
    int count2 = GetSize(head2);

    if (count1 > count2)
        AddPadding(head2, count1 - count2);

    if (count2 > count1)
        AddPadding(head1, count2 - count1);

    Node* sum = new Node(0);
    int carry = SumListRecursiveForwardOrderHelper(head1, head2, sum);

    if (0 ==carry)
        return sum->next;

    sum->data = carry;
    return sum;
}

int LinkedList::SumListRecursiveForwardOrderHelper(Node *head1, Node *head2, Node *sum) {
    if (nullptr == head1)
        return 0;

    Node* sumList = new Node(0);
    sum->next = sumList;

    int carry  = SumListRecursiveForwardOrderHelper(head1->next, head2->next, sumList);

    int intSum = head1->data + head2->data + carry;
    sumList->data = intSum % 10;

    return intSum / 10;
}

void LinkedList::AddPadding(Node *&node, int count) {
    Node* newNode = nullptr;
    for (int i = 0; i < count; ++i) {
        newNode = new Node(0);
        newNode->next = node;
        node = newNode;
    }
}

int LinkedList::GetSize(Node* head) {
    int count = 0;
    while (nullptr != head) {
        ++count;
        head = head->next;
    }

    return count;
}

bool LinkedList::CheckPalindrome(Node *head) {
#if COND_Q6 == 1
    int size = GetSize(head);

    Node* i = head;
    Node* j = head;
    int step = size - 1;
    while (nullptr != i) {
        j = i;
        for (int k = 0; k < step; ++k)
            j = j->next;

        if (i->data != j->data)
            return false;

        step -= 2;
        i = i->next;
    }

    return true;
#elif COND_Q6 == 2
    stack<int> st;
    Node* n = head;
    while (nullptr != n) {
        st.push(n->data);
        n = n->next;
    }

    n = head;
    while (!st.empty()) {
        if (n->data != st.top())
            return false;

        n = n->next;
        st.pop();
    }

    return true;
#elif COND_Q6 == 3
    stack<int> st;
    Node* fast = head;
    Node* slow = head;
    while (nullptr != fast && nullptr != fast->next) {
        st.push(slow->data);
        slow = slow->next;
        fast = fast->next->next;
    }

    if (nullptr != fast)
        slow = slow->next;

    while (!st.empty()) {
        if (slow->data != st.top())
            return false;

        slow = slow->next;
        st.pop();
    }

    return true;
#else
    int size = GetSize(head);

    //PaddingNode* res = CheckPalindromeRecursive(head, size);
    //return nullptr != res && res->result;
    return CheckPalindromeRecursive(head, size, head->next);
#endif
}

LinkedList::PaddingNode *LinkedList::CheckPalindromeRecursive(Node *head, int size) {
    if (nullptr == head || size < 1)
        return new PaddingNode(head, true);
    else if (size == 1)
        return new PaddingNode(head->next, true);

    PaddingNode* res = CheckPalindromeRecursive(head->next, size - 2);
    if (nullptr == res || !res->result || nullptr == res->node)
        return res;

    res->result = res->node->data == head->data;
    res->node = res->node->next;
    return res;
}

bool LinkedList::CheckPalindromeRecursive(Node *head, int size, Node *&next) {
    if (nullptr == head || size < 1) {
        next = head;
        return true;
    } else if (size == 1) {
        next = head->next;
        return true;
    }

    bool res = CheckPalindromeRecursive(head->next, size - 2, next);
    if (!res)
        return res;

    res = head->data == next->data;
    next = next->next;
    return res;
}

Node *LinkedList::Intersect(Node *head1, Node *head2) {
#if COND_Q7 == 1
    Node* n1 = head1;
    Node* n2 = nullptr;

    while (nullptr != n1) {
        n2 = head2;
        while(nullptr != n2) {
            if (n1 == n2)
                return n1;

            n2 = n2->next;
        }
        n1 = n1->next;
    }

    return nullptr;
#elif COND_Q7 == 2
    Node* n1 = head1;
    Node* n2 = head2;
    unordered_set<Node*> set;

    while (nullptr != n1) {
        set.insert(n1);
        n1 = n1->next;
    }

    while (nullptr != n2) {
        if (set.find(n2) != set.end())
            return n2;

        n2 = n2->next;
    }

    return nullptr;
#elif COND_Q7 == 3
    if (nullptr == head1 || nullptr == head2)
        return nullptr;

    Node* n1 = head1;
    Node* n2 = head2;
    Node* tail1 = nullptr;
    Node* tail2 = nullptr;
    int size1 = 1, size2 = 1;
    while (nullptr != n1->next) {
        tail1 = n1;
        n1 = n1->next;
        ++size1;
    }

    while (nullptr != n2->next) {
        tail2 = n2;
        n2 = n2->next;
        ++size2;
    }

    if (tail1 != tail2)
        return nullptr;

    Node* longer = size1 > size2 ? head1 : head2;
    Node* shorter = size1 < size2 ? head1 : head2;
    for (int i = 0; i < abs(size1 - size2); ++i)
        longer = longer->next;

    while (shorter != longer) {
        shorter = shorter->next;
        longer = longer->next;
    }

    return longer;
#endif
}

Node* LinkedList::DetectLoop(Node *head) {
    if (nullptr == head || nullptr == head->next)
        return nullptr;

    Node* r1 = head;
    Node* r2 = head;

    while (nullptr != r1 && nullptr != r2->next) {
        r1 = r1->next;
        r2 = r2->next->next;

        if (r1 == r2)
            break;
    }

    if (nullptr == r2)
        return nullptr;

    r1 = head;
    while (r1 != r2) {
        r1 = r1->next;
        r2 = r2->next;
    }

    return r1;
}

/*
     Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    Node* node5 = new Node(5);
    Node* node6 = new Node(6);
    Node* node7 = new Node(7);
    Node* node8 = new Node(8);
    vector<Node*> nodeArr{node1, node2, node3, node4, node5, node6, node7, node8};

    node1->appendToTail(node2);
    node1->appendToTail(node3);
    node1->appendToTail(node4);
    node1->appendToTail(node5);
    node1->appendToTail(node6);
    //node1->appendToTail(node7);
    //node1->appendToTail(node8);
    node6->next = node4;

    // 5 5 1 2 1 3 3 1 1
    // 5 1 2 3
    //LinkedList::PrintLinkedList(node);
    //LinkedList::RemoveDuplicate(node);
    //LinkedList::PrintLinkedList(node);

    // 1 2 3 4 5 6 7 8 9 10
    //cout << LinkedList::FindKthtoLast(node, 4)->data << " ";
    //cout << LinkedList::FindKthtoLast(node, 1)->data << " ";
    //cout << LinkedList::FindKthtoLast(node, 2)->data << " ";
    //cout << LinkedList::FindKthtoLast(node, 0)->data << " ";
    //cout << LinkedList::FindKthtoLast(node, 9)->data << endl;
    //int i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0;
    //cout << LinkedList::FindKthtoLastRecursive(node, 4, i1)->data << " ";
    //cout << LinkedList::FindKthtoLastRecursive(node, 1, i2)->data << " ";
    //cout << LinkedList::FindKthtoLastRecursive(node, 2, i3)->data << " ";
    //cout << LinkedList::FindKthtoLastRecursive(node, 0, i4)->data << " ";
    //cout << LinkedList::FindKthtoLastRecursive(node, 9, i5)->data << endl;

    //LinkedList::PrintLinkedList(node);
    //LinkedList::DeleteMiddleNode(node->next->next);
    //LinkedList::PrintLinkedList(node);

    // 3 5 8 5 10 2 1
    //LinkedList::PrintLinkedList(node);
    //LinkedList::PrintLinkedList(LinkedList::Partition(node, 5));

    //LinkedList::PrintLinkedList(node1);
    //LinkedList::PrintLinkedList(node2);
    //LinkedList::PrintLinkedList(LinkedList::SumList(node1, node2));
    //LinkedList::PrintLinkedList(LinkedList::SumListRecursive(node1, node2, 0));
    //LinkedList::PrintLinkedList(LinkedList::SumListRecursiveForwardOrder(node1, node2));

    // 2 1 6 1 2 - 1 2 3 4 4 3 2 1
    //LinkedList::PrintLinkedList(node1);
    //cout << LinkedList::CheckPalindrome(node1) << endl;
    //LinkedList::PrintLinkedList(node2);
    //cout << LinkedList::CheckPalindrome(node2) << endl;

    // 1 2 3 4 5 6 - 8 7 4 5 6
    //LinkedList::PrintLinkedList(node1);
    //LinkedList::PrintLinkedList(node8);

    //cout << LinkedList::Intersect(node1, node8)->data << endl;
    //cout << (LinkedList::Intersect(node1, nullptr) == nullptr ? "null" : "intersect") << endl;

    // 1 2 3 4 5 6 7 8 5 ...
    cout << LinkedList::DetectLoop(node1)->data << endl;


    for (auto n : nodeArr)
        delete n;
 */

