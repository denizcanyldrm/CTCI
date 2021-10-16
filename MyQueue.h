//
// Created by User on 5.10.2021.
//

#ifndef CTCI_MYQUEUE_H
#define CTCI_MYQUEUE_H

struct QueueNode;

template <class T>
class MyQueue {
public:
    MyQueue(): data(0), top(nullptr), last(nullptr)  {

    }

    ~MyQueue() = default;

    void Add(T d) {
        auto* qNode = new QueueNode(d);
        if (nullptr != last)
            last->next = qNode;

        last = qNode;
        if (nullptr == top)
            top = qNode;
    }

    int Remove() {
        if (nullptr != top) {
            T d = top->data;
            top = top->next;

            if (nullptr == top)
                last = nullptr;

            return d;
        }

        return 0;
    }

    T Peek() {
        return nullptr != top ? top->data : T{};
    }

    bool IsEmpty() {
        return nullptr == top;
    }

private:
    struct QueueNode {
        explicit QueueNode(T d): data(d), next(nullptr) {

        }

        T data;
        QueueNode* next;
    };

    T data;
    QueueNode* top;
    QueueNode* last;
};

#endif //CTCI_MYQUEUE_H
