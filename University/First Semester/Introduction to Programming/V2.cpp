// Hubert Jastrzębski | Satori V2 (Wielomiany) | 2025-01-03
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9424876

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

class Poly {
 private:
  class Mono {
    ll coef_ = 0;
    int exp_ = 0;
    Mono *prev_ = nullptr, *next_ = nullptr;
   public:
    Mono() {}
    Mono(const ll &coef, const int &exp, Mono *prev, Mono *next) : coef_(coef), exp_(exp), prev_(prev), next_(next) {}
    bool Print(bool is_first) {
        if (coef_ > 0 && !is_first) cout << '+';
        if (exp_ == 0)
            cout << coef_;
        else {
            if (coef_ == -1) cout << '-';
            else if (coef_ != 1) cout << coef_;
            if (exp_ > 0) {
                cout << 'x';
                if (exp_ > 1)
                    cout << '^' << exp_;
            }
        }
        return false;
    }
    friend class Poly;
  } *head_, *tail_;

  inline void _insert(Mono *lhs, Mono *rhs, const ll &coef, const int &exp) {
      lhs->next_ = rhs->prev_ = new Mono(coef, exp, lhs, rhs);
  }

  inline void _remove(Mono *lhs, Mono *rhs) {
      delete lhs->next_;
      lhs->next_ = rhs;
      rhs->prev_ = lhs;
  }

  Mono *_add(Mono *ptr, const ll &coef, const int &exp) {
      while (ptr->next_->exp_ < exp)
          ptr = ptr->next_;
      if (ptr->next_->exp_ == exp) {
          ptr->next_->coef_ += coef;
          if (ptr->next_->coef_ == 0)
              _remove(ptr, ptr->next_->next_);
      } else
          _insert(ptr, ptr->next_, coef, exp);
      return ptr;
  }

  int _size() const {
      int res = -1;
      Mono* ptr = head_;
      while (ptr != tail_) {
          ptr = ptr->next_;
          res++;
      }
      return res;
  }

  void _clean() {
      auto ptr = head_->next_;
      while (ptr != tail_) {
          auto temp = ptr->next_;
          delete ptr;
          ptr = temp;
      }
      head_->next_ = tail_;
      tail_->prev_ = head_;
  }

 public:
  Poly() {
      head_ = new Mono(0, -1, nullptr, nullptr);
      tail_ = new Mono(0, 1e9, nullptr, nullptr);
      head_->next_ = tail_;
      tail_->prev_ = head_;
  }

  void AddMono(const ll &coef, const int &exp) {
      cout << "ADD OK\n";
      if (coef == 0) return;
      _add(head_, coef, exp);
  }

  void Derivative() {
      if (Empty()) return;
      if (head_->next_->exp_ == 0)
          _remove(head_, head_->next_->next_);

      auto ptr = head_->next_;
      while (ptr != tail_) {
          ptr->coef_ *= ptr->exp_;
          ptr->exp_--;
          ptr = ptr->next_;
      }
  }

  void PrintAsc() {
      if (Empty())
          cout << "EMPTY\n";
      else {
          auto ptr = head_->next_;
          bool is_first = true;
          while (ptr != tail_) {
              is_first = ptr->Print(is_first);
              ptr = ptr->next_;
          }
          cout << '\n';
      }
  }

  void PrintDesc() {
      if (Empty())
          cout << "EMPTY\n";
      else {
          auto ptr = tail_->prev_;
          bool is_first = true;
          while (ptr != head_) {
              is_first = ptr->Print(is_first);
              ptr = ptr->prev_;
          }
          cout << '\n';
      }
  }

  void PrintMin() {
      if (Empty())
          cout << "ERROR\n";
      else
          cout << head_->next_->coef_ << '\n';
  }

  void PrintMax() {
      if (Empty())
          cout << "ERROR\n";
      else
          cout << tail_->prev_->coef_ << '\n';
  }

  void Clean() {
      if (Empty())
          cout << "EMPTY\n";
      else {
          _clean();
          cout << "CLEAN OK\n";
      }
  }

  bool Empty() const {
      return head_->next_ == tail_;
  }

  void add(const Poly &rhs, bool verbose = true) {
      if (verbose)
        cout << "ADD OK\n";
      auto ptr_lhs = head_;
      auto ptr_rhs = rhs.head_->next_;
      while (ptr_rhs != rhs.tail_) {
          ptr_lhs = _add(ptr_lhs, ptr_rhs->coef_, ptr_rhs->exp_);
          ptr_rhs = ptr_rhs->next_;
      }
  }

  void operator*=(const ll &coef) {
      cout << "MULTI OK\n";
      if (coef == 0)
          _clean();
      else {
          auto ptr = head_->next_;
          while (ptr != tail_) {
              ptr->coef_ *= coef;
              ptr = ptr->next_;
          }
      }
  }

  void operator*=(const Poly &rhs) {
      cout << "MULTI OK\n";
      if (Empty() || rhs.Empty()) {
          _clean();
          return;
      }

      Mono *r_head = new Mono(0, -1, nullptr, nullptr);
      Mono *r_tail = new Mono(0, 1e9, nullptr, nullptr);
      r_head->next_ = r_tail;
      r_tail->prev_ = r_head;

      vector<Mono*> P(rhs._size(), r_head);

      Mono *ptr_lhs = head_->next_;
      while (ptr_lhs != tail_) {
          ll lcoef = ptr_lhs->coef_;
          int lexp = ptr_lhs->exp_;
          Mono *ptr_rhs = rhs.head_->next_;
          Mono *ptr = r_head;

          int pos = 0;
          while (ptr_rhs != rhs.tail_) {
              Mono* prev = P[pos];
              if (prev->exp_ > ptr->exp_)
                  ptr = prev;
              P[pos++] = ptr = _add(ptr, lcoef * ptr_rhs->coef_, lexp + ptr_rhs->exp_);
              ptr_rhs = ptr_rhs->next_;
          }
          ptr_lhs = ptr_lhs->next_;
      }

      _clean();
      head_->next_ = r_head->next_;
      head_->next_->prev_ = head_;
      tail_->prev_ = r_tail->prev_;
      tail_->prev_->next_ = tail_;
      delete r_head;
      delete r_tail;
  }

  ~Poly() {
      _clean();
      delete head_;
      delete tail_;
  }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;

        vector<Poly> L(26);
        while (n--) {
            string command;
            cin >> command;
            if (command == "PRINT_ASC") {
                char id;
                cin >> id;
                L[id - 'A'].PrintAsc();
            } else if (command == "PRINT_DESC") {
                char id;
                cin >> id;
                L[id - 'A'].PrintDesc();
            } else if (command == "DERIVATIVE") {
                char id;
                cin >> id;
                L[id - 'A'].Derivative();
            } else if (command == "ADD_MONO") {
                char id;
                int a, b;
                cin >> id >> a >> b;
                L[id - 'A'].AddMono(b, a);
            } else if (command == "ADD") {
                char id1, id2;
                cin >> id1 >> id2;
                L[id1 - 'A'].add(L[id2 - 'A']);
            } else if (command == "MULTI_CONST") {
                char id;
                int a;
                cin >> id >> a;
                L[id - 'A'] *= a;
            } else if (command == "MULTI") {
                char id1, id2;
                cin >> id1 >> id2;
                L[id1 - 'A'] *= L[id2 - 'A'];
            } else if (command == "MIN") {
                char id;
                cin >> id;
                L[id - 'A'].PrintMin();
            } else if (command == "MAX") {
                char id;
                cin >> id;
                L[id - 'A'].PrintMax();
            } else if (command == "CLEAN") {
                char id;
                cin >> id;
                L[id - 'A'].Clean();
            } else
                cout << "INVALID\n";
        }
    }
}