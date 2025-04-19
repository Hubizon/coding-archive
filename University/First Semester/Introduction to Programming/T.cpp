// Hubert Jastrzębski | Satori T (Mapa gór) | 2024-12-25
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9424508

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class point {
 private:
  int x, y;

 public:
  point() { };
  point(int x, int y) : x(x), y(y) { };
  int getX() { return x; };
  int getY() { return y; };
};

class queue {
 private:
  point *arr;
  int front_pos;
  int back_pos;
  int size;
  int max_size;

 public:
  queue();
  queue(int max_size);
  void enqueue(const point &x);
  point dequeue();
  bool empty();
  void resize(int n);
  ~queue();
};

queue::queue() : max_size(15), front_pos(0), back_pos(0), size(0) {
    arr = new point[max_size];
}

void queue::enqueue(const point &x) {
    if (size >= max_size)
        resize(2 * max_size);
    arr[back_pos % max_size] = x;
    back_pos++, size++;
}

point queue::dequeue() {
    if (size == 0)
        throw std::string("DEQUEUE");
    size--;
    return arr[front_pos++ % max_size];
}

bool queue::empty() {
    return size == 0;
}

void queue::resize(int n) {
    if (n > max_size) {
        point *new_arr = new point[n];
        front_pos %= max_size, back_pos %= max_size;
        if (front_pos < back_pos)
            memcpy(new_arr, arr + front_pos, size * sizeof(point));
        else {
            int len = max_size - front_pos;
            memcpy(new_arr, arr + front_pos, len * sizeof(point));
            memcpy(new_arr + len, arr, back_pos * sizeof(point));
        }

        delete[] arr;
        arr = new_arr;

        front_pos = 0;
        back_pos = size;
        max_size = n;
    }
}

queue::~queue() {
    delete[] arr;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<pair<int, int>> G = { { -1, -1 }, { -1, 0 }, { -1, 1}, { 0, - 1 }, { 0, 1 },
                        { 1, -1 }, { 1, 0 }, { 1, 1 } };

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;
        vector<vector<int>> H(n, vector<int>(n));
        for (auto& h : H)
            for (auto &hh : h)
                cin >> hh;

        vector<vector<int>> res(n, vector<int>(n, -1));
        vector<char> V;

        auto bfs = [&](point src) {
            if (res[src.getX()][src.getY()] != -1) return;
            res[src.getX()][src.getY()] = V.size();
            queue Q;
            Q.enqueue(src);

            bool czy_dolina = true, czy_gora = true;
            while (!Q.empty()) {
                auto u = Q.dequeue();
                int ux = u.getX(), uy = u.getY();

                for (auto [ta, tb] : G) {
                    int vx = ux + ta, vy = uy + tb;
                    if (vx < 0 || vy < 0 || vx >= n || vy >= n)
                        continue;
                    if (H[ux][uy] < H[vx][vy])
                        czy_gora = false;
                    else if (H[ux][uy] > H[vx][vy])
                        czy_dolina = false;
                    else if (res[vx][vy] == -1) {
                        res[vx][vy] = V.size();
                        Q.enqueue({vx, vy});
                    }
                }
            }

            if (czy_dolina)
                V.push_back('D');
            else if (czy_gora)
                V.push_back('G');
            else
                V.push_back('i');
        };

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                bfs(point(i, j));

        for (auto& r : res) {
            for (auto &&rr : r)
                cout << V[rr] << ' ';
            cout << '\n';
        }
    }
}