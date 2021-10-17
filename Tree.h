//
// Created by User on 16.10.2021.
//

#ifndef CTCI_TREE_H
#define CTCI_TREE_H

#include <iostream>
#include <unordered_set>
#include <queue>

using namespace std;

template<class T>
class TreeNode {
public:
    explicit TreeNode (T val): data(val), left(nullptr), right(nullptr) {

    }

    ~TreeNode () = default;

    T data;
    TreeNode *left;
    TreeNode *right;
};

template<class T>
class Tree {
public:
    Tree() = default;
    ~Tree() = default;

    void InsertNodes(TreeNode<T>* node ) {
        nodes.push_back(node);
    }

    void ClearNodes() {
        for (auto& n : nodes) {
            delete n;
            n = nullptr;
        }

        nodes.clear();
    }

    vector<TreeNode<T>*> nodes;
};

void TraverseInOrder(TreeNode<int>* root) {
    if (nullptr != root) {
        TraverseInOrder(root->left);
        cout << root->data << " ";
        TraverseInOrder(root->right);
    }
}

void TraversePreOrder(TreeNode<int>* root) {
    if (nullptr != root) {
        cout << root->data << " ";
        TraversePreOrder(root->left);
        TraversePreOrder(root->right);
    }
}

void TraversePostOrder(TreeNode<int>* root) {
    if (nullptr != root) {
        TraversePostOrder(root->left);
        TraversePostOrder(root->right);
        cout << root->data << " ";
    }
}

void PerformDfs(TreeNode<int>* root, unordered_set<TreeNode<int>*>& set) {
    set.insert(root);
    if (nullptr != root) {
        if (set.find(root) != set.end()) {
            cout << root->data << " ";
            PerformDfs(root->left, set);
            PerformDfs(root->right, set);
        }
    }
}

void Dfs(TreeNode<int>* root) {
    unordered_set<TreeNode<int>*> set;
    PerformDfs(root, set);
}

void Bfs(TreeNode<int>* root) {
    queue<TreeNode<int>*> q;
    unordered_set<TreeNode<int>*> set;
    q.push(root);

    while (!q.empty()) {
        TreeNode<int>* n = q.front();
        q.pop();
        if (nullptr != n) {
            cout << n->data << " ";

            if (set.find(n) == set.end()) {
                q.push(n->left);
                q.push(n->right);
            } else
                set.insert(n);
        }
    }
}

#endif //CTCI_TREE_H
