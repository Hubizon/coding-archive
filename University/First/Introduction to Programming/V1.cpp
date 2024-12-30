// Hubert Jastrzębski | Satori V1 (Wielomiany) | 2024-12-27
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9424852

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

class List {
 private:
  class Node {
    ll coef_ = 0, exp_ = 0;
    Node *prev_ = nullptr, *next_ = nullptr;
   public:
    Node() { }
    Node(ll coef, ll exp, Node* prev, Node* next) : coef_(coef), exp_(exp), prev_(prev), next_(next) { }
    bool Print(bool is_first) {
        if (coef_ == 0) return is_first;
        if (coef_ > 0 && !is_first) cout << '+';
        if (exp_ == 0)
            cout << coef_;
        else {
            if (coef_ == -1) cout << '-';
            else if (coef_ != 1) cout << coef_;
            if (exp_ > 0)
                cout << 'x';
            if (exp_ > 1)
                cout << '^' << exp_;
        }
        return false;
    }
    friend class List;
  } *head_, *tail_;

  inline void _insert(Node* lhs, Node* rhs, ll coef, ll exp) {
      auto x = new Node(coef, exp, lhs, rhs);
      lhs->next_ = x;
      rhs->prev_ = x;
  }

  inline void _remove(Node* lhs, Node* rhs) {
      delete lhs->next_;
      lhs->next_ = rhs;
      rhs->prev_ = lhs;
  }

  inline Node* _add(Node *ptr, ll coef, ll exp) {
      while (ptr->next_->exp_ < exp)
          ptr = ptr->next_;
      if (ptr->next_->exp_ == exp) {
          ptr->next_->coef_ += coef;
          if (ptr->next_->coef_ == 0)
              _remove(ptr, ptr->next_->next_);
      }
      else
          _insert(ptr, ptr->next_, coef, exp);
      return ptr;
  }

  inline void _clean() {
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
  List() {
      head_ = new Node(0, -1, nullptr, nullptr);
      tail_ = new Node(0, 1e18, nullptr, nullptr);
      head_->next_ = tail_;
      tail_->prev_ = head_;
  }

  void AddMono(ll coef, ll exp) {
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
          cout <<"EMPTY\n";
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
          cout <<"EMPTY\n";
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

  void operator+=(const List &rhs) {
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

  void operator*=(const List &rhs) {
      cout << "MULTI OK\n";
      if (Empty() || rhs.Empty()) {
          _clean();
          return;
      }

      Node *r_head = new Node(0, -1, nullptr, nullptr);
      Node *r_tail = new Node(0, 1e18, nullptr, nullptr);
      r_head->next_ = r_tail;
      r_tail->prev_ = r_head;

      auto ptr_lhs = head_->next_;
      while (ptr_lhs != tail_) {
          auto ptr_rhs = rhs.head_->next_;
          auto ptr = r_head;
          while (ptr_rhs != rhs.tail_) {
              ptr = _add(ptr, ptr_lhs->coef_ * ptr_rhs->coef_, ptr_lhs->exp_ + ptr_rhs->exp_);
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

  ~List() {
      _clean();
      delete head_;
      delete tail_;
  }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;

        vector<List> L(26);
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
                ll a, b;
                cin >> id >> a >> b;
                L[id - 'A'].AddMono(b, a);
            } else if (command == "ADD") {
                char id1, id2;
                cin >> id1 >> id2;
                L[id1 - 'A'] += L[id2 - 'A'];
            } else if (command == "MULTI_CONST") {
                char id;
                ll a;
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