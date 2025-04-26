// Hubert Jastrzębski | Satori E1 (Krasnoludki) | 2025-03-21
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9757687

#include <bits/stdc++.h>

using namespace std;

struct Node {
  int left, right;
  Node() : left(-1), right(-1) {}
  Node(int left, int right) : left(left), right(right) {}
  bool isLeaf() { return left == -1 && right == -1; }
};

vector<Node> nodes;

void dfs_index(int node, int depth, string &type) {
    if (node == -1) return;
    if (type == "PREORDER") cout << node << " ";
    dfs_index(nodes[node].left, depth + 1, type);
    if (type == "INORDER") cout << node << " ";
    dfs_index(nodes[node].right, depth + 1, type);
    if (type == "POSTORDER") cout << node << " ";
}

void dfs_depth(int node, int depth, string &type) {
    if (node == -1) return;
    if (nodes[node].isLeaf() && type == "PREORDER") cout << node << ':' << depth << ' ';
    dfs_depth(nodes[node].left, depth + 1, type);
    if (nodes[node].isLeaf() && type == "INORDER") cout << node << ':' << depth << ' ';
    dfs_depth(nodes[node].right, depth + 1, type);
    if (nodes[node].isLeaf() && type == "POSTORDER") cout << node << ':' << depth << ' ';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;

        nodes = vector<Node>(n);
        for (int i = 0; i < n; i++) {
            int left, right;
            cin >> left >> right;
            if (left != -1) nodes[i].left = left;
            if (right != -1) nodes[i].right = right;
        }

        string order_type;
        cin >> order_type;

        dfs_index(0, 0, order_type);
        cout << '\n';

        dfs_depth(0, 0, order_type);
        cout << '\n';
    }
}