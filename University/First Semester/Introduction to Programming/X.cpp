// Hubert Jastrzębski | Satori X (Księgarnia kolejny raz) | 2025-01-25
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9660355

#include <bits/stdc++.h>

using namespace std;

struct book {
  string author, title;
};

vector<int> A(256);
class Cmp {
 private:
  int compare(const string &lhs, const string &rhs) {
      for (int i = 0; i < min(lhs.size(), rhs.size()); i++) {
          if (A[lhs[i]] > A[rhs[i]])
              return false;
          if (A[lhs[i]] < A[rhs[i]])
              return true;
      }
      if (lhs.size() != rhs.size())
          return lhs.size() < rhs.size();
      return -1;
  }

 public:
  bool operator()(const book &lhs, const book &rhs) {
      int compare_author = compare(lhs.author, rhs.author);
      if (compare_author == -1)
          return compare(lhs.title, rhs.title);
      return compare_author;
  }
};

bool compare_author(const book &value, const string &author) {
    if (value.author.size() != author.size())
        return false;
    for (int i = 0; i < author.size(); i++)
        if (tolower(value.author[i]) != tolower(author[i]))
            return false;
    return true;
}

class Cnt {
 private:
  string author;

 public:
  int result = 0;

  Cnt(const string &a) : author(a) {}
  void operator()(const book &value) {
      result += compare_author(value, author);
  }
};

class Find {
 private:
  string author;

 public:
  Find(const string &a) : author(a) {}
  bool operator()(const book &value) const {
      return compare_author(value, author);
  }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    A[' '] = A['\n'] = A[0] = -1;

    int z;
    cin >> z;
    while (z--) {
        int n, k;
        cin >> n >> k;

        vector<book> V(n);
        cin.ignore();

        for_each(V.begin(), V.end(), [&](auto &value) {
            cin >> value.author;
            getline(cin, value.title);
        });

        while (k--) {
            for (int i = 0; i < 26; i++) {
                char d;
                cin >> d;
                A[tolower(d)] = i + 1;
                A[toupper(d)] = i + 1;
            }

            sort(V.begin(), V.end(), Cmp());
            for_each(V.begin(), V.end(), [&](const auto &value) {
                cout << value.author << value.title << '\n'; });

            string s1, s2;
            cin >> s1 >> s2;

            Cnt cnt(s1);
            for_each(V.begin(), V.end(), ref(cnt));
            cout << cnt.result;

            auto it = find_if(V.begin(), V.end(), Find(s2));
            if (it == V.end())
                cout << " BRAK\n";
            else
                cout << it->title << '\n';
        }
    }
}