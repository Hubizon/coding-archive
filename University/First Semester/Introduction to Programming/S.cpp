// Hubert Jastrzębski | Satori S (Mathematica) | 2024-12-25
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9424488

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class stack {
 private:
  long long *arr;
  int size;
  int max_size;

 public:
  stack();
  stack(int max_size);
  void push(const long long &x);
  long long pop();
  long long top();
  bool empty();
  void clear();
  ~stack();
};

stack::stack() : max_size(15), size(0) {
    arr = (long long *) malloc(max_size * sizeof(long long));
}

stack::stack(int max_size) : max_size(max_size), size(0) {
    arr = (long long *) malloc(max_size * sizeof(long long));
}

void stack::push(const long long &x) {
    if (size >= max_size)
        throw std::string("PUSH");
    arr[size++] = x;
}

long long stack::pop() {
    if (size == 0)
        throw std::string("POP");
    return arr[--size];
}

long long stack::top() {
    if (size == 0)
        throw std::string("TOP");
    return arr[size - 1];
}

bool stack::empty() {
    return size == 0;
}

void stack::clear() {
    size = 0;
}

stack::~stack() {
    free(arr);
}

int priority(char c) {
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    if (c == '^')
        return 3;
    return 0;
}

int main()
{
    int z;
    cin >> z;
    while (z--) {
        vector<int> A(26);
        for (auto& a : A)
            cin >> a;

        int wcnt;
        cin >> wcnt;
        while (wcnt--) {
            string W;
            cin >> W;
            stack S(W.size());

            string ONP;
            for (auto& w : W) {
                if (isalpha(w))
                    ONP += w;
                else if (w == '(')
                    S.push(w);
                else if (w == ')') {
                    while (S.top() != '(')
                        ONP += S.pop();
                    S.pop();
                }
                else {
                    while (!S.empty() && priority(S.top()) >= priority(w))
                        ONP += S.pop();
                    S.push(w);
                }
            }

            while (!S.empty())
                ONP += S.pop();

            cout << ONP << '\n';

            S.clear();
            for (auto& c : ONP) {
                if (isalpha(c))
                    S.push(A[c - 'a']);
                else {
                    auto b = S.pop();
                    auto a = S.pop();
                    if (c == '+')
                        S.push(a + b);
                    else if (c == '-')
                        S.push(a - b);
                    else if (c == '*')
                        S.push(a * b);
                    else if (c == '/') {
                        if (b == 0)
                            S.push(0);
                        else
                            S.push(a / b);
                    }
                    else if (c == '^') {
                        if (b < 0)
                            S.push(1);
                        else
                            S.push(pow(a, b));
                    }
                }
            }

            cout << S.top() << '\n';
        }
    }
}