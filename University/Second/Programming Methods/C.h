// Hubert Jastrzębski | Satori C (Stos i kolejka z minimum) | 2025-03-11
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9757594

#ifndef SOLUTION_H
#define SOLUTION_H

using namespace std;

template<typename C>
class vector {
 private:
  C *tab = nullptr;
  int capacity = 1;
  int size = 0;

  void resize_(int c) {
      capacity = c;
      if (tab == nullptr)
          tab = new C[capacity];
      else {
          C *new_tab = new C[capacity];
          for (int i = 0; i < size; i++)
              new_tab[i] = std::move(tab[i]);

          delete[] tab;
          tab = new_tab;
      }
  }

 public:
  vector(int a = 4) {
      resize_(a);
      size = 0;
  }

  vector(const vector &v) {
      *this = v;
  }

  ~vector() {
      delete[] tab;
  }

  void push_back(const C &x) {
      if (size == capacity)
          resize_(2 * capacity);
      tab[size++] = x;
  }

  void pop_back() {
      size--;
  }

  C top() {
      return tab[size - 1];
  }

  void clear() {
      size = 0;
  }

  void operator=(const vector &v) {
      if (this == &v) return;
      size = 0;
      resize_(v.capacity);
      for (int i = 0; i < v.size; i++)
          tab[i] = v.tab[i];
      size = v.size;
  }

  operator bool() const {
      return size != 0;
  }

  bool operator!() const {
      return size == 0;
  }
};

template<typename C, typename O>
class stackMin {
  vector<pair<C, C> > arr;
  O cmp;

 public:
  stackMin(int a = 4) : arr(a) { }

  void push(C x) {
      auto y = x;
      if (arr && !cmp(x, arr.top().second))
          y = arr.top().second;
      arr.push_back({x, y});
  }

  bool pop() {
      if (arr) {
          arr.pop_back();
          return true;
      }
      return false;
  }

  C top() {
      return arr.top().first;
  }

  C min() {
      return arr.top().second;
  }

  void clear() {
      arr.clear();
  }

  bool empty() {
      return !arr;
  }
};

template<typename C, typename O>
class queueMin {
  stackMin<C, O> S1, S2;
  O cmp;

  void move() {
      while (!S1.empty()) {
          S2.push(S1.top());
          S1.pop();
      }
  }

 public:
  queueMin(int a = 4) : S1(a), S2(a) {
  }

  void enqueue(C x) {
      S1.push(x);
  }

  bool dequeue() {
      if (S1.empty() && S2.empty())
          return false;
      if (S2.empty())
          move();
      S2.pop();
      return true;
  }

  C front() {
      if (S2.empty())
          move();
      return S2.top();
  }

  C min() {
      if (S1.empty())
          return S2.min();
      if (S2.empty())
          return S1.min();
      if (cmp(S1.min(), S2.min()))
          return S1.min();
      return S2.min();
  }

  void clear() {
      S1.clear();
      S2.clear();
  }

  bool empty() {
      return S1.empty() && S2.empty();
  }
};

template<typename C>
class myPair {
 public:
  C first, second;
};

template<typename C, typename O>
void solveStack(stackMin<C, O> &S, int n) {
    while (n--) {
        string s;
        cin >> s;
        if (s == "push") {
            C x;
            cin >> x;
            S.push(x);
        } else if (s == "pop") {
            if (S.empty())
                cout << "ERROR\n";
            else {
                cout << S.top() << "\n";
                S.pop();
            }
        } else if (s == "top") {
            if (S.empty())
                cout << "EMPTY\n";
            else
                cout << S.top() << '\n';
        } else if (s == "min") {
            if (S.empty())
                cout << "EMPTY\n";
            else
                cout << S.min() << '\n';
        } else if (s == "clear") {
            S.clear();
        } else {
            cout << (S.empty() ? "YES\n" : "NO\n");
        }
    }
}

template<typename C, typename O>
void solveQueue(queueMin<C, O> &Q, int n) {
    while (n--) {
        string s;
        cin >> s;
        if (s == "enqueue") {
            C x;
            cin >> x;
            Q.enqueue(x);
        } else if (s == "dequeue") {
            if (Q.empty())
                cout << "ERROR\n";
            else {
                cout << Q.front() << '\n';
                Q.dequeue();
            }
        } else if (s == "front") {
            if (Q.empty())
                cout << "EMPTY\n";
            else
                cout << Q.front() << '\n';
        } else if (s == "min") {
            if (Q.empty())
                cout << "EMPTY\n";
            else
                cout << Q.min() << '\n';
        } else if (s == "clear") {
            Q.clear();
        } else {
            cout << (Q.empty() ? "YES\n" : "NO\n");
        }
    }
}

#endif //SOLUTION_H