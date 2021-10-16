//
// Created by User on 5.10.2021.
//

#ifndef CTCI_STACKSQUEUES_H
#define CTCI_STACKSQUEUES_H

#include "MyStack.h"
#include "MyQueue.h"
#include <vector>
#include <list>

#define SORT_STACK_OPT 1

using namespace std;

template<int N, int Cap>
class MultiFixedStack {
public:
    MultiFixedStack(): values{0}, sizes{0} {
        for (int& s : sizes)
            s = 0;
    }

    ~MultiFixedStack() = default;

    void Push(int st, int val) {
        if (!isFull(st)) {
            int index = findTopIndex(st);
            values[index + 1] = val;
            ++sizes[st];
        }
    }

    int Pop(int st) {
        int index = findTopIndex(st);
        int val = 0;
        if (!isEmpty(st)) {
            val = values[index];
            values[index] = 0;
            --sizes[st];
        }

        return val;
    }

    int Peek(int st) {
        if (isEmpty(st))
            return 0;
        return values[findTopIndex(st)];
    }

    bool isEmpty(int st) {
        return sizes[st] == 0;
    }

    bool isFull(int st) {
        return sizes[st] == Cap;
    }

    int findTopIndex(int st) {
        return st * Cap + sizes[st] - 1;
    }

    int Size(int st) {
        return sizes[st];
    }

    void Print() {
        for (int i : values)
            cout << i << " ";
        cout << endl;
    }

private:
    int values[N * Cap];
    int sizes[N];
};

template<int N, int Cap>
class SetOfStacks {
public:
    explicit SetOfStacks(): size{0} {

    }

    ~SetOfStacks() = default;

    void Push(int val) {
        int index = size / Cap;
        if (index < N) {
            if (setOfStacks[index].size() < Cap)
                PushToStack(index, val);
            else {
                if (index + 1 < N)
                    PushToStack(index + 1, val);
            }
        }
    }

    int Pop() {
        if (size == 0)
            return -1;

        int top = Peek();
        int index = size / Cap;
        if (size % Cap == 0)
            --index;

        if (!setOfStacks[index].empty())
            setOfStacks[index].pop();

        --size;
        return top;
    }

    int Peek() {
        if (size == 0)
            return -1;

        int index = size / Cap;
        if (size % Cap == 0)
            --index;
        return setOfStacks[index].top();
    }

    bool isEmpty() {
        return size == 0;
    }

    void Print() {
        while (!isEmpty()) {
            cout << Peek() << " ";
            Pop();
        }
        cout << endl;
    }

private:
    void PushToStack(int index, int val) {
        setOfStacks[index].push(val);
        ++size;
    }

    stack<int> setOfStacks[N];
    int size;
};

template<int N, int Cap>
class SetOfStacks2 {
public:
    explicit SetOfStacks2(): size{0} {

    }

    ~SetOfStacks2() = default;

    void Push(int val) {
        stack<int>* curSt = GetLastStack();
        if (nullptr != curSt && curSt->size() < Cap)
            PushToStack(curSt, val);
        else {
            if (setOfStacks.size() < N) {
                auto* st = new stack<int>();
                PushToStack(st, val, true);
            }
        }
    }

    int Pop() {
        if (isEmpty())
            return -1;

        int top = Peek();
        stack<int>* curSt = GetLastStack();
        if (nullptr != curSt) {
            PopFromStack(curSt);
        }

        return top;
    }

    int PopAt(int index) {
        if (index >= setOfStacks.size())
            return -1;
        auto st = setOfStacks[index];

        return PopFromStack(st);
    }

    int Peek() {
        stack<int>* curSt = GetLastStack();
        if (nullptr != curSt && !curSt->empty()) {
            return curSt->top();
        }

        return -1;
    }

    bool isEmpty() {
        return size == 0;
    }

    int Size() {
        int s = 0;
        for (auto st : setOfStacks)
            s += st->size();

        return s;
    }

    void Print() {
        while (!isEmpty()) {
            cout << Peek() << " ";
            Pop();
        }
        cout << endl;
    }

private:
    void PushToStack(stack<int>* st, int val, bool isNew = false) {
        if (isNew)
            setOfStacks.push_back(st);

        if (st->size() < Cap) {
            st->push(val);
            ++size;
        }
    }

    int PopFromStack(stack<int>* st) {
        int top = -1;
        if (!st->empty()) {
            top = st->top();
            st->pop();
            --size;
        }

        if (st->empty()) {
            //for (auto it = setOfStacks.begin(); it != setOfStacks.end(); ++it) {
                //if (*it == st)
                    //setOfStacks.erase(it);
            //}
            setOfStacks.erase(setOfStacks.begin() + setOfStacks.size() - 1);
        }

        return top;
    }

    stack<int>* GetLastStack() {
        if (setOfStacks.empty())
            return nullptr;

        return setOfStacks[setOfStacks.size() - 1];
    }

    vector<stack<int>*> setOfStacks;
    int size;
};

template <class T>
class MyQueueWithTwoStacks {
public:
    MyQueueWithTwoStacks() = default;
    ~MyQueueWithTwoStacks() = default;

    void Add(T d) {
        stNewest.push(d);
    }

    T Remove() {
        PushToOtherStack();
        if (!stOldest.empty()) {
            T top = stOldest.top();
            stOldest.pop();
            cout << "Pop: " << top << endl;
            return top;
        }

        return T{};
    }

    T Peek() {
        PushToOtherStack();
        return !stOldest.empty() ? stOldest.top() : T{};
    }

    bool IsEmpty() {
        return stNewest.empty() && stOldest.empty();
    }

    int Size() {
        return stNewest.size() + stOldest.size();
    }

    void Print() {
        PushToOtherStack();
        while (!stOldest.empty()) {
            cout << stOldest.top() << " ";
            stOldest.pop();
        }
        cout << endl;
    }

private:
    void PushToOtherStack() {
        if (stOldest.empty()) {
            while (!stNewest.empty()) {
                T top = stNewest.top();
                stNewest.pop();
                stOldest.push(top);
            }
        }
    }

    stack<T> stNewest;
    stack<T> stOldest;
};

template<class T>
void Sort(stack<T> st) {
    if (st.empty())
        return;

    stack<T> sec;
    bool isOrdered = false;
    while (!st.empty()) {
#if SORT_STACK_OPT == 1
        sec.push(st.top());
        st.pop();

        if (!st.empty() && st.top() < sec.top()) {
            swap(st.top(), sec.top());
            sec.push(st.top());
            st.pop();

            while (!sec.empty()) {
                st.push(sec.top());
                sec.pop();
            }
        }
#else
        int tmp = st.top();
        st.pop();
        while (!sec.empty() && tmp < sec.top()) {
            st.push(sec.top());
            sec.pop();
        }
        sec.push(tmp);
#endif
    }

    while (!sec.empty()) {
        st.push(sec.top());
        sec.pop();
    }

    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

class Animal {
public:
    Animal(): id{0}, type{0} {

    };
    virtual ~Animal() = default;

    int GetId() const {
        return id;
    }

    void SetId(int val) {
        id = val;
    }

    int GetType() const {
        return type;
    }

    void Print() const {
        cout << (type == 0 ? "cat-" : "dog-") << id << endl;
    }

protected:
    int id;
    int type;
};

class Cat: public Animal  {
public:
    Cat() {
        type = 0;
    };
    ~Cat() override = default;
};

class Dog: public Animal {
public:
    Dog() {
        type = 1;
    };
    ~Dog() override = default;
};

class AnimalQueue {
public:
    AnimalQueue(): id{0} {

    };

    ~AnimalQueue() = default;

    void Enqueue(Animal* animal) {
        animal->SetId(++id);
        if (0 == animal->GetType())
            qCat.push_back(animal);
        else
            qDog.push_back(animal);
    }

    Animal* DequeueAny() {
        if (qCat.empty())
            return DequeueDog();

        if (qDog.empty())
            return DequeueCat();

        if (qDog.front()->GetId() < qCat.front()->GetId())
            return DequeueDog();
        else
            return DequeueCat();
    }

    Dog* DequeueDog() {
        if (!qDog.empty()) {
            cout << "DequeueDog: ";
            Dog* dog = dynamic_cast<Dog*>(qDog.front());
            dog->Print();
            qDog.pop_front();
            return dog;
        }

        return nullptr;
    }

    Cat* DequeueCat() {
        if (!qCat.empty()) {
            cout << "DequeueCat: ";
            Cat* cat = dynamic_cast<Cat*>(qCat.front());
            cat->Print();
            qCat.pop_front();
            return cat;
        }

        return nullptr;
    }

    bool IsEmpty() {
        return qCat.empty() && qDog.empty();
    }

    int Size() {
        return qCat.size() + qDog.size();
    }

private:
    list<Animal*> qCat;
    list<Animal*> qDog;
    int id;
};

#endif //CTCI_STACKSQUEUES_H

/*
#define NUMBER_OF_STACKS 3

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    MyStack<int> st;
    for (int i : arr)
        st.Push(i);

    st.Print();

    MultiFixedStack<NUMBER_OF_STACKS, CAPACITY> fixedSt;
    cout << "Initial: " << endl;
    for (int i = 0; i < NUMBER_OF_STACKS; ++i)
        cout << fixedSt.isEmpty(i) << " " << fixedSt.findTopIndex(i) << endl;

    for (int i = 0; i < CAPACITY; ++i) {
        fixedSt.Push(0, i + 1);
        fixedSt.Push(1, i + 16);
        fixedSt.Push(2, i + 31);
    }

    fixedSt.Print();

    cout << "Sizes: " << endl;
    for (int i = 0; i < NUMBER_OF_STACKS; ++i)
        cout << fixedSt.Size(i) << " ";
    cout << endl;

    cout << "After push: " << endl;
    for (int i = 0; i < NUMBER_OF_STACKS; ++i)
        cout << fixedSt.findTopIndex(i) << " " << fixedSt.Peek(i) << " " << fixedSt.isEmpty(i) << endl;

    cout << "Pop: " << endl;
    for (int i = 0; i < NUMBER_OF_STACKS; ++i) {
        for (int j = 0; j < CAPACITY; ++j)
            cout << fixedSt.Pop(i) << " ";

        cout << endl;
    }

    cout << "After pop: " << endl;
    for (int i = 0; i < NUMBER_OF_STACKS; ++i)
        cout << fixedSt.isEmpty(i) << " " << fixedSt.findTopIndex(i) << endl;

    MyStack<int> st;
    st.Push(4);
    st.Push(5);
    st.Push(2);
    st.Push(3);
    st.Push(1);

    st.Print();

    SetOfStacks<NUMBER_OF_STACKS, CAPACITY> st;
    for (int i : arr)
        st.Push(i);

    cout << "isEmpty: " << st.isEmpty() << endl;
    cout << "Peek:" << st.Peek() << endl;
    st.Print();
    cout << "isEmpty: " << st.isEmpty() << endl;
    cout << "----------------" << endl;

    SetOfStacks2<NUMBER_OF_STACKS, CAPACITY> st2;
    for (int i : arr)
        st2.Push(i);

    cout << "size: " << st2.Size() << endl;
    cout << "Peek: " << st2.Peek() << endl;
    st2.Print();
    cout << "isEmpty: " << st2.isEmpty() << endl;

    MyQueueWithTwoStacks<int> q;
    q.Add(1);
    q.Add(2);
    q.Add(3);
    q.Remove();
    q.Remove();
    q.Add(4);
    q.Add(5);
    q.Remove();
    q.Add(6);
    q.Add(7);
    q.Remove();
    q.Remove();
    q.Remove();
    q.Remove();

    int arr2[] = {3, 2, 4, 1, 5};
    stack<int> st;
    for (int i : arr2)
        st.push(i);

    Sort<int>(st);

    stack<int> st2;
    int arr3[] = {8, 12, 17, 3, 4, 13, 5, 23, 27, 51};
    for (int i : arr3)
        st2.push(i);

    Sort<int>(st2);

    AnimalQueue q;
    q.Enqueue(new Cat()); // 1
    q.Enqueue(new Dog()); // 2
    q.Enqueue(new Cat()); // 3
    q.Enqueue(new Dog()); // 4
    q.Enqueue(new Cat()); // 5
    q.Enqueue(new Dog()); // 6
    q.Enqueue(new Cat()); // 7
    q.Enqueue(new Dog()); // 8
    q.Enqueue(new Cat()); // 9

    q.DequeueCat();
    q.DequeueDog();
    q.DequeueAny();
    q.DequeueCat();
    q.DequeueDog();
    q.DequeueDog();
    q.DequeueDog();
    q.DequeueAny();
    q.DequeueAny();
    cout << q.Size() << endl;

    return 0;
}
 */