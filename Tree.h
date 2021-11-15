//
// Created by User on 16.10.2021.
//

#ifndef CTCI_TREE_H
#define CTCI_TREE_H

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

template<class T>
class TreeNode {
public:
    explicit TreeNode (T val): data(val), isVisited(false), left(nullptr), right(nullptr) {

    }

    ~TreeNode () = default;

    T data;
    bool isVisited;
    TreeNode *left;
    TreeNode *right;
};

template<class T>
class Tree {
public:
    Tree() = default;
    ~Tree() = default;

    void Insert(TreeNode<T>* node) {
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

template<class T>
class BinarySearchTree {
public:
    BinarySearchTree(): root(nullptr) {

    };

    ~BinarySearchTree() = default;

    void Insert(TreeNode<T>* node, TreeNode<T>* & ref) {
        if (nullptr == ref)
            ref = node;
        else if (node->data < ref->data) {
            Insert(node, ref->left);
        } else if (node->data > ref->data) {
            Insert(node, ref->right);
        }
    }

    void Clear() {
    }

//private:
    TreeNode<T>* root;
};

int GetHeight(TreeNode<int>* root) {
    if (nullptr == root)
        return -1;

    return max(GetHeight(root->left), GetHeight(root->right)) + 1;
}

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

void PerformDfs(TreeNode<int>* root, int depth, unordered_set<TreeNode<int>*>& set) {
    set.insert(root);
    if (nullptr != root) {
        if (set.find(root) != set.end()) {
            cout << root->data << "(" << depth << ") ";
            PerformDfs(root->left, depth + 1, set);
            PerformDfs(root->right, depth + 1, set);
        }
    }
}

void Dfs(TreeNode<int>* root) {
    unordered_set<TreeNode<int>*> set;
    PerformDfs(root, 0, set);
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

template<class T>
TreeNode<T>* CreateMinimalBST(T arr[], int left, int right) {
    if (right < left)
        return nullptr;

    int middle = (left + right) / 2;

    auto* root = new TreeNode<T>{arr[middle]};
    root->left = CreateMinimalBST(arr, left, middle - 1);
    root->right = CreateMinimalBST(arr, middle + 1, right);

    return root;
}

template<class T>
void CreateListOfDepthsPreOrder(TreeNode<T>* root, vector<vector<TreeNode<T>*>*>& res, int level) {
    if (nullptr == root)
        return;

    cout << "data: " << root->data << " resSize: " << res.size() << " level: " << level << endl;
    vector<TreeNode<T>*>* vec = nullptr;
    if (res.size() == level) {
        vec = new vector<TreeNode<T>*>{};
        res.push_back(vec);
    } else
        vec = res[level];

    vec->push_back(root);
    CreateListOfDepthsPreOrder(root->left, res, level + 1);
    CreateListOfDepthsPreOrder(root->right, res, level + 1);
}

template<class T>
void CreateListOfDepthsBfs(TreeNode<T>* root, vector<vector<TreeNode<T>*>*>& res) {
    if (nullptr == root)
        return;

    auto current = new vector<TreeNode<T>*>{root};
    while (current->size() != 0) {
        res.push_back(current);
        auto parents = current;

        current = new vector<TreeNode<T>*>{};
        for (auto p : *parents) {
            if (nullptr != p->left)
                current->push_back(p->left);

            if (nullptr != p->right)
                current->push_back(p->right);
        }
    }
}

#endif //CTCI_TREE_H
