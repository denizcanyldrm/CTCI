//
// Created by User on 5.10.2021.
//

#ifndef CTCI_MYSTACK_H
#define CTCI_MYSTACK_H

#include <iostream>
#include <stack>

using namespace std;

#define STACK_OPT 3
#define CAPACITY 10

#if STACK_OPT == 1
template<class T>
struct StackNode {
    explicit StackNode(T d): min(d), data(d), next(nullptr) {

    }

    T min;
    T data;
    StackNode* next;
};

template<class T>
class MyStack {
public:
    MyStack(): top(nullptr) {
    }

    ~MyStack() = default;

    void Push(int d) {
        StackNode<T>* stNode = new StackNode(d);
        if (nullptr != top) {
            stNode->next = top;

            if (stNode->data > top->min)
                stNode->min = top->min;
        }

        top = stNode;
    }

    T Pop() {
        if (nullptr != top) {
            T d = top->data;
            top = top->next;
            return d;
        }

        return 0;
    }

    StackNode<T>* Peek() {
        return top;
    }

    bool IsEmpty() {
        return nullptr == top;
    }

    T Min() {
        return !IsEmpty() ? top->min : INT32_MAX;
    }

    void Print() {
        while (nullptr != Peek())
            cout << "(" << Min() << ")" << Pop() << " ";
    }

private:
    StackNode<T>* top;
};

#elif STACK_OPT == 2
template<class T>
class MyStack {
public:
    MyStack(): data{}, top(-1) {

    }

    ~MyStack() = default;

    void Push(T d) {
        if (CAPACITY != top)
            data[++top] = d;
    }

    T Pop() {
        return -1 != top ? data[top--] : T{};
    }

    T Peek() {
        return data[top];
    }

    [[nodiscard]] bool IsEmpty() const {
        return top == -1;
    }

    void Print() {
        cout << "Stack Array" << endl;
        for (int i = top; i >= 0; --i)
            cout << data[i] << " ";
        cout << endl;
    }

private:
    T data[CAPACITY];
    int top;
};

#elif STACK_OPT == 3
template<class T>
struct StackNode {
    explicit StackNode(T d): data(d), next(nullptr) {

    }

    T data;
    StackNode* next;
};

template<class T>
class MyStack {
public:
    MyStack(): top(nullptr) {
    }

    ~MyStack() = default;

    void Push(int d) {
        StackNode<T>* stNode = new StackNode(d);
        if (nullptr != top)
            stNode->next = top;

        top = stNode;
        if (stNode->data <= Min())
            minSt.push(d);
    }

    T Pop() {
        if (nullptr != top) {
            T d = top->data;
            top = top->next;

            if (d == Min())
                minSt.pop();

            return d;
        }

        return 0;
    }

    StackNode<T>* Peek() {
        return top;
    }

    bool IsEmpty() {
        return nullptr == top;
    }

    T Min() {
        return !minSt.empty() ? minSt.top() : INT32_MAX;
    }

    void Print() {
        while (nullptr != Peek()) {
            cout << Pop() << " ";
        }
        cout << endl;
    }

private:
    stack<T> minSt;
    StackNode<T>* top;
};
#endif

#endif //CTCI_MYSTACK_H
