//
// Created by User on 16.10.2021.
//

#ifndef CTCI_GRAPH_H
#define CTCI_GRAPH_H

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

enum State { Unvisited, Visited, Visiting };

template<class T>
class GraphNode {
public:
    explicit GraphNode (T val): data(val), indegree(0), isVisited(State::Unvisited) {

    }

    ~GraphNode () = default;

    void AddEdge(GraphNode* node) {
        if (nullptr != node) {
            adjList.push_back(node);
            ++node->indegree;
        }
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

    void InsertNodes(GraphNode<T>* node) {
        nodes.push_back(node);
    }

    void InsertEdge(GraphNode<T>* node1, GraphNode<T>* node2) {
        edgeList.push_back(make_pair(node1, node2));
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
    vector<pair<GraphNode<T>*,GraphNode<T>*>> edgeList;

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

template<class T>
void Dfs(GraphNode<T>* root, int indegree = 0) {
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

template<class T>
void DfsIterative(GraphNode<T>* root) {
    if (nullptr == root)
        return;

    stack<GraphNode<T>*> st;
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

template<class T>
void Bfs(GraphNode<T>* root) {
    if (nullptr == root)
        return;

    queue<GraphNode<int>*> q;
    q.push(root);
    root->isVisited = State::Visited;

    while (!q.empty()) {
        GraphNode<T>* node = q.front();
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

template<class T>
bool FindRoute(GraphNode<T>* n1, GraphNode<T>* n2) {
    if (nullptr == n1 || nullptr == n2)
        return false;

    if (n1 == n2)
        return true;

    queue<GraphNode<int>*> q;
    q.push(n1);
    n1->isVisited = State::Visiting;

    while (!q.empty()) {
        GraphNode<T>* node = q.front();
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

template<class T>
void TopologicalSort(Graph<T> & graph) {
    if (0 == graph.nodes.size())
        return;

    unordered_map<GraphNode<T>*, int> map;
    queue<GraphNode<T>*> q;
    for (auto n : graph.nodes) {
        if (n->indegree == 0)
            q.push(n);

        map[n] = n->indegree;
    }

    queue<T> res;
    while (!q.empty()) {
        auto root = q.front();
        q.pop();

        res.push(root->data);
        if (root->isVisited != State::Visited) {
            root->isVisited = State::Visited;

            for (auto n : root->adjList) {
                --map[n];
                if (map[n] == 0) {
                    q.push(n);
                }
            }
        }
    }

    cout << "TopologicalSort: ";
    while (!res.empty()) {
        cout << res.front() << " ";
        res.pop();
    }
    cout << endl;
}

template<class T>
bool TopologicalSort(GraphNode<T>* root, stack<T> & st) {
    if (nullptr == root)
        return true;

    if (State::Visiting == root->isVisited)
        return false;

    if (State::Unvisited == root->isVisited) {
        root->isVisited = State::Visiting;

        for (auto n : root->adjList) {
            if (!TopologicalSort(n, st))
                return false;
        }

        st.push(root->data);
        root->isVisited = State::Visited;
    }

    return true;
}

template<class T>
void TopologicalSortDfs(Graph<T> & g) {
    stack<T> st;

    for (auto n : g.nodes) {
        if (State::Unvisited == n->isVisited) {
            if (!TopologicalSort(n, st))
                return;
        }
    }

    cout << "TopologicalSort: ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

#endif //CTCI_GRAPH_H
