//
// Created by User on 16.10.2021.
//

#ifndef CTCI_GRAPH_H
#define CTCI_GRAPH_H

#include <unordered_set>
#include <vector>
#include <stack>

using namespace std;

template<class T>
class GraphNode {
public:
    explicit GraphNode (T val): data(val), isVisited(false) {

    }

    ~GraphNode () = default;

    void AddEdge(GraphNode* node) {
        if (nullptr != node)
            adjList.push_back(node);
    }

    T data;
    bool isVisited;
    vector<GraphNode*> adjList;
};

template<class T>
class Graph {
public:
    Graph() = default;
    ~Graph() = default;

    void InsertNodes(GraphNode<T>* node ) {
        nodes.push_back(node);
    }

    void ClearNodes() {
        for (auto& n : nodes) {
            delete n;
            n = nullptr;
        }

        nodes.clear();
    }

    void SetVisitedStates() {
        for (auto& n : nodes)
            n->isVisited = false;
    }

    vector<GraphNode<T>*> nodes;
};

void Dfs(GraphNode<int>* root) {
    if (nullptr == root)
        return;

    if (!root->isVisited) {
        root->isVisited = true;
        cout << root->data << " ";

        for (auto n : root->adjList)
            Dfs(n);
    }
}

void DfsIterative(GraphNode<int>* root) {
    if (nullptr == root)
        return;

    stack<GraphNode<int>*> st;
    st.push(root);

    while (!st.empty()) {
        auto node = st.top();
        st.pop();

        if (!node->isVisited) {
            node->isVisited = true;
            cout << node->data << " ";

            for (auto n : node->adjList) {
                st.push(n);
            }
        }
    }
}

void Bfs(GraphNode<int>* root) {
    if (nullptr == root)
        return;

    queue<GraphNode<int>*> q;
    q.push(root);
    root->isVisited = true;

    while (!q.empty()) {
        GraphNode<int>* node = q.front();
        q.pop();
        cout << node->data << " ";

        for (auto& n : node->adjList) {
            if (!n->isVisited) {
                n->isVisited = true;
                q.push(n);
            }
        }
    }
}

#endif //CTCI_GRAPH_H
