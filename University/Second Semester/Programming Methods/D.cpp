// Hubert Jastrzębski | Satori D (Zabawa karnawałowa) | 2025-03-11
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9757638

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename T>
struct node {
  node *N[2] = {this, this};
  T name;

 public:
  node() { }
  node(const T name) : name(name) {}

  ~node() {
      //delete[] N;
  };
};

template<typename T>
struct doubleList {
  T* head; // head->N[0] - first, head->N[1] - last
  string name;

 public:
  doubleList(const string& name, const string& wagonName) : head(new T()), name(name) {
      addFirst(new T(wagonName));
  }

  void addFirst(T *wagon) {
      wagon->N[0] = head;
      wagon->N[1] = head->N[0];
      head->N[0]->N[head->N[0]->N[1] == head] = wagon;
      head->N[0] = wagon;
  }

  void addLast(T *wagon) {
      wagon->N[0] = head;
      wagon->N[1] = head->N[1];
      head->N[1]->N[head->N[1]->N[1] == head] = wagon;
      head->N[1] = wagon;
  }

  ~doubleList() {
      clean();
      delete head;
  }

  void clean() {
      auto train = this;
      auto prev = train->head;
      auto person = prev->N[0];

      while (person != train->head) {
          auto temp = person;
          person = person->N[person->N[1] != prev];
          if (prev != train->head)
              delete prev;
          prev = temp;
      }
  }

  void reverse() {
      swap(head->N[0], head->N[1]);
  }

  void unify(doubleList<T> *trainBack) {
      this->head->N[1]->N[this->head->N[1]->N[1] == this->head] = trainBack->head->N[0];
      trainBack->head->N[0]->N[trainBack->head->N[0]->N[1] == trainBack->head] = this->head->N[1];
      trainBack->head->N[1]->N[trainBack->head->N[1]->N[1] == trainBack->head] = this->head;
      this->head->N[1] = trainBack->head->N[1];
      trainBack->head->N[0] = trainBack->head->N[1] = trainBack->head;
      delete trainBack;
  }

  void print() {
      auto prev = head;
      auto person = prev->N[0];

      while (person != head) {
          if (prev != head)
              cout << "<-";
          cout << person->name;
          auto temp = person;
          person = person->N[person->N[1] != prev];
          prev = temp;
      }
      cout << '\n';
  }

  doubleList<node<string>>* detachFront(string train2) {
      auto person = head->N[0];
      auto newFront = person->N[person->N[1] != head];
      newFront->N[newFront->N[1] == person] = head;
      head->N[0] = newFront;
      string name = person->name;
      delete person;
      return new doubleList<node<string>>(train2, name);
  }

  doubleList<node<string>>* detachBack(string train2) {
      auto person = train->head->N[1];
      auto newBack = person->N[person->N[1] != train->head];
      newBack->N[newBack->N[1] == person] = train->head;
      train->head->N[1] = newBack;
      string name = person->name;
      delete person;

      return new doubleList<node<string>>(train2, name);
  }

  bool empty() {
      return head->N[0] == head;
  }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;

        unordered_map<string, doubleList<node<string>>*> M;

        while (n--) {
            string command;
            cin >> command;
            if (command == "NEW") {
                string train1, person;
                cin >> train1 >> person;
                doubleList<node<string>>* train = new doubleList<node<string>>(train1, person);
                M[train1] = train;
            }
            else if (command == "BACK") {
                string train2, person;
                cin >> train2 >> person;
                auto train = M[train2];
                train->addLast(new node<string>(person));
            }
            else if (command == "FRONT") {
                string train2, person;
                cin >> train2 >> person;
                auto train = M[train2];
                train->addFirst(new node<string>(person));
            }
            else if (command == "PRINT") {
                string train2;
                cin >> train2;

                cout << "\"" << train2 << "\":\n";
                auto train = M[train2];
                train->print();
            }
            else if (command == "REVERSE") {
                string train2;
                cin >> train2;
                auto train = M[train2];
                train->reverse();
            }
            else if (command == "UNION") {
                string train2, train3;
                cin >> train2 >> train3;
                auto trainFront = M[train2], trainBack = M[train3];
                trainFront->unify(trainBack);
                M.erase(train3);
            }
            else if (command == "DELFRONT") {
                string train1, train2;
                cin >> train1 >> train2;
                auto train = M[train2];

                doubleList<node<string>>* trainNew = train->detachFront(train2);
                M[train1] = trainNew;

                if (train->empty()) {
                    M.erase(train->name);
                    delete train;
                }
            }
            else if (command == "DELBACK") {
                string train2, train1;
                cin >> train2 >> train1;
                auto train = M[train2];

                doubleList<node<string>>* trainNew = train->detachBack(train2);
                M[train1] = trainNew;

                if (train->empty()) {
                    M.erase(train->name);
                    delete train;
                }
            }
        }

        for (auto [k, v] : M)
            delete v;
    }
}