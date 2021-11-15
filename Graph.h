//
// Created by User on 16.10.2021.
//

#ifndef CTCI_GRAPH_H
#define CTCI_GRAPH_H

#include <unordered_set>
#include <vector>
#include <stack>

using namespace std;

enum State { Unvisited, Visited, Visiting };

template<class T>
class GraphNode {
public:
    explicit GraphNode (T val): data(val), indegree(0) {

    }

    ~GraphNode () = default;

    void AddEdge(GraphNode* node) {
        if (nullptr != node)
            adjList.push_back(node);
    }

    T data;
    int indegree;
    State isVisited;
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

    void Reset() {
        ResetVisitedStates();
        ResetIndegrees();
    }

    vector<GraphNode<T>*> nodes;

private:
    void ResetVisitedStates() {
        for (auto& n : nodes)
            n->isVisited = State::Unvisited;
    }

    void ResetIndegrees() {
        for (auto& n : nodes)
            n->indegree = 0;
    }
};

void Dfs(GraphNode<int>* root, int indegree = 0) {
    if (nullptr == root)
        return;

    if (root->isVisited == State::Unvisited) {
        root->isVisited = State::Visited;
        root->indegree = indegree;
        cout << root->data << "(" << root->indegree << ") ";

        for (auto n : root->adjList)
            Dfs(n, indegree + 1);
    }
}

void DfsIterative(GraphNode<int>* root) {
    if (nullptr == root)
        return;

    stack<GraphNode<int>*> st;
    root->indegree = 0;
    st.push(root);

    while (!st.empty()) {
        auto node = st.top();
        st.pop();

        if (node->isVisited == State::Unvisited) {
            node->isVisited = State::Visited;
            cout << node->data << "(" << node->indegree << ") ";

            for (auto n : node->adjList) {
                n->indegree = node->indegree + 1;
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
    root->isVisited = State::Visited;

    while (!q.empty()) {
        GraphNode<int>* node = q.front();
        q.pop();
        cout << node->data << " ";

        for (auto& n : node->adjList) {
            if (n->isVisited == State::Unvisited) {
                n->isVisited = State::Visited;
                q.push(n);
            }
        }
    }
}

bool FindRoute(GraphNode<int>* n1, GraphNode<int>* n2) {
    if (nullptr == n1 || nullptr == n2)
        return false;

    if (n1 == n2)
        return true;

    queue<GraphNode<int>*> q;
    q.push(n1);
    n1->isVisited = State::Visiting;

    while (!q.empty()) {
        GraphNode<int>* node = q.front();
        q.pop();

        if (nullptr != node) {
            for (auto& n : node->adjList) {
                if (n->isVisited == State::Unvisited) {
                    if (n == n2)
                        return true;

                    n->isVisited = State::Visiting;
                    q.push(n);
                }
            }
        }
    }

    return false;
}

#endif //CTCI_GRAPH_H
