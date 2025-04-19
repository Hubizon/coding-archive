// Hubert Jastrzębski | Satori U (Kolejka PRLowska) | 2024-12-25
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9424548

#include <iostream>
#include <vector>

using namespace std;

class person {
 private:
  string name = "";
  int age = 0;
  int p = 0;
  person *next = nullptr;

 public:
  person() {}
  person(string name, int age, int p, person *next) : name(name), age(age), p(p), next(next) {}

  friend class list;
};

class list {
 private:
  person *head = nullptr;
  int size = 0;

  int _remove(person* ptr, person* prev, string name, int age) {
      if (ptr == nullptr) return 0;
      int cnt = _remove(ptr->next, ptr, name, age);
      if (ptr->name == name && ptr->age == age) {
          prev->next = ptr->next;
          delete ptr;
          size--;
          return cnt + 1;
      }
      return cnt;
  }

  void _remove(person* ptr, person* prev, int p) {
      if (ptr == nullptr) return;
      _remove(ptr->next, ptr, p);
      if (ptr->p == p) {
          prev->next = ptr->next;
          delete ptr;
          size--;
      }
  }

  person* _reverse(person* ptr, person* prev) {
      if (ptr == nullptr) return prev;
      auto next = ptr->next;
      ptr->next = prev;
      return _reverse(next, ptr);
  }

  void _print(person* ptr) {
      if (ptr == nullptr) return;
      cout << ptr->name << ' ' << ptr->age << ' ' << ptr->p << '\n';
      _print(ptr->next);
  }

  void _clean(person* ptr) {
      if (ptr == nullptr) return;
      _clean(ptr->next);
      delete ptr;
  }

 public:
  list() { head = new person(); }

  void push_front(string name, int age, int p) {
      head->next = new person(name, age, p, head->next);
      size++;
  }

  void push_back(string name, int age, int p) {
      person* last = head;
      while (last->next != nullptr)
          last = last->next;
      last->next = new person(name, age, p, nullptr);
      size++;
  }

  void insert(string name, int age, int p, int pos) {
      if (pos < 0 || pos > size)
          cout << "ERROR\n";
      else {
          person* ptr = head;
          for (int i = 0; i < pos; i++)
              ptr = ptr->next;
          ptr->next = new person(name, age, p, ptr->next);
          size++;
      }
  }

  void pop_front() {
      if (empty())
          cout << "ERROR\n";
      else {
          auto ptr = head->next;
          head->next = ptr->next;
          delete ptr;
          size--;
      }
  }

  void pop_back() {
      if (empty())
          cout << "ERROR\n";
      else {
          person* plast = head;
          while (plast->next->next != nullptr)
              plast = plast->next;
          delete plast->next;
          plast->next = nullptr;
          size--;
      }
  }

  void remove(string name, int age) {
      int cnt = _remove(head->next, head, name, age);
      if (cnt == 0)
          cout << "ERROR\n";
  }

  void remove(int p) {
      _remove(head->next, head, p);
  }

  bool empty() {
      return size == 0;
  }

  void reverse() {
      if (empty())
          cout << "EMPTY\n";
      else {
          auto first = head->next;
          head->next = _reverse(head->next->next, head->next);
          first->next = nullptr;
      }
  }

  void reprioritize(int age) {
      vector<tuple<string, int, int>> T;
      person* ptr = head->next, *prev = head;
      while (ptr != nullptr) {
          if (ptr->age >= age) {
              T.push_back({ ptr->name, ptr->age, ptr->p });
              ptr = ptr->next;
              delete prev->next;
              prev->next = ptr;
              size--;
          }
          else {
              ptr = ptr->next;
              prev = prev->next;
          }
      }

      for (int i = T.size() - 1; i >= 0; i--) {
          auto& [tname, tage, tp] = T[i];
          push_front(tname, tage, tp);
      }
  }

  void print() {
      if (empty())
          cout << "EMPTY\n";
      else
          _print(head->next);
  }

  void clean() {
      _clean(head->next);
      head->next = nullptr;
      size = 0;
  }

  ~list() {
      clean();
  }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n, w;
        cin >> n >> w;

        list L;
        while (n--) {
            string command;
            cin >> command;
            if (command == "NEW") {
                string name;
                int age, p;
                cin >> name >> age >> p;
                if (age >= w)
                    L.push_front(name, age, p);
                else
                    L.push_back(name, age, p);
            } else if (command == "INSERT") {
                string name;
                int age, number, p;
                cin >> name >> age >> number >> p;
                L.insert(name, age, p, number - 1);
            } else if (command == "BUYING") {
                L.pop_front();
            } else if (command == "RESIGNATION") {
                L.pop_back();
            } else if (command == "DELETE") {
                string name;
                int age;
                cin >> name >> age;
                L.remove(name, age);
            } else if (command == "PRINT") {
                L.print();
            } else if (command == "REVERSE") {
                L.reverse();
            } else if (command == "CHANGE") {
                int age;
                cin >> age;
                if (age <= w)
                    L.reprioritize(age);
                w = age;
            } else if (command == "LACK") {
                int p;
                cin >> p;
                L.remove(p);
            } else if (command == "CLEAN") {
                L.clean();
            } else
                cout << "INVALID\n";
        }
    }
}