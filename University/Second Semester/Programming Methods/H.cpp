// Hubert Jastrzębski | Satori H (Budżet) | 2025-04-06
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9757883

#include <bits/stdc++.h>

using namespace std;

struct Node {
  int res, operation; // 0 - minus, 1 - add, 2 - min, 3 - max
  Node* parent;
  vector<Node*> children;
};

void calculate(Node* node) {
    if (node->operation == 0) {
        node->res = -node->children[0]->res;
    }
    else if (node->operation == 1) {
        node->res = 0;
        for (auto child : node->children)
            node->res += child->res;
    }
    else if (node->operation == 2) {
        node->res = 1e9;
        for (auto child : node->children)
            node->res = min(node->res, child->res);
    }
    else {
        node->res = -1e9;
        for (auto child : node->children)
            node->res = max(node->res, child->res);
    }
}

Node* DFS(string& s, int& pos, vector<int>& V, vector<Node*>& N, Node* p) {
    Node* node = new Node();
    node->parent = p;

    if (s[pos] == 'x') {
        node->res = V[N.size()];
        N.push_back(node);
    }
    else {
        pos++;
        if (s[pos] == '-')
            node->operation = 0;
        else if (s[pos] == '+')
            node->operation = 1;
        else if (s[pos] == '<')
            node->operation = 2;
        else
            node->operation = 3;
        pos++;

        while (s[pos] != ')')
            node->children.push_back(DFS(s, pos, V, N, node));

        calculate(node);
    }

    pos++;
    return node;
}

void update(Node* node, int prev, int now) {
    if (node == nullptr) return;
    int node_prev = node->res;

    if (node->operation == 1)
        node->res += now - prev;
    else if ((node->operation == 2 && now <= node->res) || (node->operation == 3 && now >= node->res))
        node->res = now;
    else if ((node->operation == 2 && prev > node->res && now > node->res) || (node->operation == 3 && prev < node->res && now < node->res))
        return;
    else
        calculate(node);

    if (node_prev != node->res)
        update(node->parent, node_prev, node->res);
}

int main()  {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int p, r;
        cin >> p >> r;

        string s;
        cin >> s;

        vector<int> V(p);
        for (auto& v : V)
            cin >> v;

        int pos = 0;
        vector<Node*> N;
        Node* root = DFS(s, pos, V, N, nullptr);
        cout << root->res << '\n';

        while (r--) {
            int d, f;
            cin >> d >> f;

            N[d]->res = f;
            update(N[d]->parent, V[d], f);
            V[d] = f;

            cout << root->res << '\n';
        }

        // TODO: clean up the tree
    }
}