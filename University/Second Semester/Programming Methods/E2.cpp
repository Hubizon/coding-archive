// Hubert Jastrzębski | Satori E2 (Krasnoludki) | 2025-03-22
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9757746

#include <bits/stdc++.h>

using namespace std;

struct Node {
  int left, right, size = 0;
  pair<int, int> farthest; // dist, index
  Node() : left(-1), right(-1) {}
  Node(int left, int right) : left(left), right(right) {}
  bool isLeaf() { return left == -1 && right == -1; }
};

vector<Node> nodes;

void dfs_index(int node, string &type) {
    if (node == -1) return;
    if (type == "PREORDER") cout << node << " ";
    dfs_index(nodes[node].left, type);
    if (type == "INORDER") cout << node << " ";
    dfs_index(nodes[node].right, type);
    if (type == "POSTORDER") cout << node << " ";
    if (nodes[node].isLeaf()) nodes[node].size = 1;
    if (nodes[node].left != -1) nodes[node].size += nodes[nodes[node].left].size;
    if (nodes[node].right != -1) nodes[node].size += nodes[nodes[node].right].size;
}

void dfs_depth(int node, int depth, string &type) {
    if (node == -1) return;
    if (nodes[node].isLeaf() && type == "PREORDER") cout << node << ':' << depth << ' ';
    dfs_depth(nodes[node].left, depth + 1, type);
    if (nodes[node].isLeaf() && type == "INORDER") cout << node << ':' << depth << ' ';
    dfs_depth(nodes[node].right, depth + 1, type);
    if (nodes[node].isLeaf() && type == "POSTORDER") cout << node << ':' << depth << ' ';

    nodes[node].farthest = { 0, -node };
    if (nodes[node].left != -1) nodes[node].farthest = max(nodes[node].farthest, { nodes[nodes[node].left].farthest.first + 1, nodes[nodes[node].left].farthest.second });
    if (nodes[node].right != -1) nodes[node].farthest = max(nodes[node].farthest, { nodes[nodes[node].right].farthest.first + 1, nodes[nodes[node].right].farthest.second });
}

void dfs_farthest(int node, pair<int, int> rup) {
    if (node == -1) return;
    nodes[node].farthest = max(nodes[node].farthest, rup);
    rup.first++;

    auto far_left = rup, far_right = rup;
    if (nodes[node].left != -1) {
        auto temp = nodes[nodes[node].left].farthest;
        temp.first += 2;
        far_left = max(far_left, temp);
    }
    if (nodes[node].right != -1) {
        auto temp = nodes[nodes[node].right].farthest;
        temp.first += 2;
        far_right = max(far_right, temp);
    }

    dfs_farthest(nodes[node].left, far_right);
    dfs_farthest(nodes[node].right, far_left);
}

bool check_size(int node, int t_size) {
    bool is_ok = true;
    if (nodes[node].left != -1) is_ok &= nodes[nodes[node].left].size <= t_size / 2;
    if (nodes[node].right != -1) is_ok &= nodes[nodes[node].right].size <= t_size / 2;
    return is_ok && (t_size - nodes[node].size) <= t_size / 2 && !nodes[node].isLeaf();
}

int dfs_size(int node, int t_size, string &type) {
    if (node == -1) return -1;
    if (type == "PREORDER" && check_size(node, t_size))
        return node;

    int a = dfs_size(nodes[node].left, t_size, type);
    if (a != -1) return a;

    if (type == "INORDER" && check_size(node, t_size))
        return node;

    int b = dfs_size(nodes[node].right, t_size, type);
    if (b != -1) return b;

    if (type == "POSTORDER" && check_size(node, t_size))
        return node;

    return -1;
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

        dfs_index(0, order_type);
        cout << '\n';

        dfs_depth(0, 0, order_type);
        cout << '\n';

        dfs_farthest(0, { -1e9, -1 });

        for (int i = 0; i < n; i++)
            cout << i << ':' << -nodes[i].farthest.second << ':' << nodes[i].farthest.first << ' ';
        cout << '\n';

        cout << dfs_size(0, nodes[0].size, order_type) << '\n';
    }
}