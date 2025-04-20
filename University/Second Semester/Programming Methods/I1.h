// Hubert Jastrzębski | Satori I1 (Bajto-Play) | 2025-04-21
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/9821510

#include <bits/stdc++.h>

using namespace std;

template<typename T1, typename T2>
class Map;

template<typename T1, typename T2>
void print(const Map<T1, T2>& M, const T1& k1, const T1& k2);

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& o, const Map<T1, T2>& M);

template<typename T1, typename T2>
class Map {
 private:
  struct Node {
    pair<T1, T2> value;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    Node() {}
    Node(const pair<T1, T2> value, Node* parent) : value(value), parent(parent) {}
  } *end_;

  size_t size_ = 0;

  void clear_(Node* node) {
      if (node->left != nullptr) clear_(node->left);
      if (node->right != nullptr) clear_(node->right);
      delete node;
  }

  Node* insert_(Node* node, Node* parent, pair<T1, T2> value) {
      if (node == nullptr) {
          size_++;
          return new Node(value, parent);
      }
      if (node->value.first == value.first) {
          node->value = value;
          return node;
      }
      if (node->value.first > value.first)
          node->left = insert_(node->left, node, value);
      else
          node->right = insert_(node->right, node, value);
      return node;
  }

  Node* find_(Node* node, const T1& key) const {
      if (node == nullptr)
          return nullptr;
      if (node->value.first == key)
          return node;
      if (node->value.first > key)
          return find_(node->left, key);
      return find_(node->right, key);
  }

  void erase_(Node* node) {
      if (node == nullptr)
          return;

      if (node->left != nullptr && node->right != nullptr) {
          Node* temp = node->right;
          while (temp->left != nullptr)
              temp = temp->left;
          node->value = temp->value;
          node = temp;
      }

      if (node->left == nullptr && node->right == nullptr) {
          if (node->parent->left == node)
              node->parent->left = nullptr;
          else
              node->parent->right = nullptr;
      }
      else if (node->left == nullptr) {
          if (node->parent->left == node)
              node->parent->left = node->right;
          else
              node->parent->right = node->right;
          node->right->parent = node->parent;
      }
      else if (node->right == nullptr) {
          if (node->parent->left == node)
              node->parent->left = node->left;
          else
              node->parent->right = node->left;
          node->left->parent = node->parent;
      }

      delete node;
  }

  Node* lower_bound_(Node* node, const T1& key) const {
      if (node == nullptr)
          return nullptr;
      Node* res = nullptr;
      if (node->value.first == key)
          return node;
      if (node->value.first > key)
          res = lower_bound_(node->left, key);
      else
          res = lower_bound_(node->right, key);
      if (res != nullptr)
          return res;
      if (node->value.first >= key)
          return node;
      return nullptr;
  }

  Node* upper_bound_(Node* node, const T1& key) const {
      if (node == nullptr)
          return nullptr;
      Node* res = nullptr;
      if (node->value.first > key)
          res = upper_bound_(node->left, key);
      else
          res = upper_bound_(node->right, key);
      if (res != nullptr)
          return res;
      if (node->value.first > key)
          return node;
      return nullptr;
  }

  Node* copy_(Node* other, Node* parent) {
      Node* node = new Node(other->value, parent);
      if (other->left != nullptr)
          node->left = copy_(other->left, node);
      if (other->right != nullptr)
          node->right = copy_(other->right, node);
      return node;
  }

 public:
  class Iterator {
   private:
    Node* node_ = nullptr;

    Iterator(Node* node) : node_(node) { }

    void next_() {
        if (node_ == nullptr)
            return;

        if (node_->right != nullptr) {
            node_ = node_->right;
            while (node_->left != nullptr)
                node_ = node_->left;
        }
        else {
            while (node_->parent != nullptr && node_->parent->right != nullptr && node_->parent->right == node_)
                node_ = node_->parent;
            node_ = node_->parent;
        }
    }

    void prev_() {
        if (node_ == nullptr)
            return;

        if (node_->left != nullptr) {
            node_ = node_->left;
            while (node_->right != nullptr)
                node_ = node_->right;
        }
        else {
            while (node_->parent != nullptr && node_->parent->left != nullptr && node_->parent->left == node_)
                node_ = node_->parent;
            node_ = node_->parent;
        }
    }

    friend class Map;

   public:
    Iterator() { }

    bool operator==(const Iterator& other) const {
        return node_ == other.node_;
    }

    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }

    pair<T1,T2>& operator*() {
        return node_->value;
    }

    pair<T1,T2>* operator->() {
        return &node_->value;
    }

    Iterator operator++(int) {
        Iterator res(node_);
        next_();
        return res;
    }

    Iterator operator--(int) {
        Iterator res(node_);
        prev_();
        return res;
    }

    Iterator& operator++() {
        next_();
        return *this;
    }

    Iterator& operator--() {
        prev_();
        return *this;
    }
  };

  Map() {
      end_ = new Node();
  }

  Map(Map& other) {
      end_ = copy_(other.end_, nullptr);
      size_ = other.size_;
  }

  ~Map() {
      clear_(end_);
  }

  void insert(pair<T1, T2> p) {
      end_->left = insert_(end_->left, end_, p);
  }

  size_t erase(const T1& key) {
      Node* node = find_(end_->left, key);
      if (node == nullptr)
          return 0;
      erase_(node);
      size_--;
      return 1;
  }

  void erase(const Iterator& it) {
      erase(it.node_->value.first);
  }

  Iterator end() const {
      return Iterator(end_);
  }

  Iterator begin() const {
      if (size() == 0)
          return end();

      Node* node = end_->left;
      while (node != nullptr && node->left != nullptr)
          node = node->left;
      return Iterator(node);
  }

  Iterator find(const T1& key) const {
      Node* node = find_(end_->left, key);
      if (node == nullptr)
          return end();
      return Iterator(node);
  }

  Iterator lower_bound(const T1& key) const {
      Node *node = lower_bound_(end_->left, key);
      if (node == nullptr)
          return end();
      return Iterator(node);
  }

  Iterator upper_bound(const T1& key) const {
      Node *node = upper_bound_(end_->left, key);
      if (node == nullptr)
          return end();
      return Iterator(node);
  }

  size_t size() const {
      return size_;
  }

  void clear() {
      if (end_->left != nullptr)
          clear_(end_->left);
      end_->left = nullptr;
      size_ = 0;
  }

  T2& operator[](const T1& key) {
      Node* node = find_(end_->left, key);
      if (node != nullptr)
          return node->value.second;

      pair<T1, T2> p = {key, T2()};
      insert(p);

      node = find_(end_->left, key);
      return node->value.second;
  }

  Map<T1, T2>& operator=(const Map<T1, T2>& other) {
      if (this == &other)
          return *this;

      clear();
      end_ = copy_(other.end_, nullptr);
      size_ = other.size_;

      return *this;
  }

  friend void print<T1, T2>(const Map<T1,T2>& M, const T1& k1, const T1& k2);
  friend ostream& operator << <T1, T2>(ostream& o, const Map<T1,T2>& M);
};

template<typename T1, typename T2>
void print(const Map<T1, T2>& M, const T1& k1, const T1& k2) {
    if (M.size() == 0) {
        cout << "EMPTY\n";
        return;
    }

    typename Map<T1, T2>::Iterator iter = M.lower_bound(k1);
    typename Map<T1, T2>::Iterator end = M.upper_bound(k2);
    while (iter != end) {
        cout << iter->first << ' ' << iter->second << '\n';
        iter++;
    }
}

template<typename T1, typename T2>
ostream& operator<< (ostream& o, const Map<T1,T2>& M) {
    if (M.size() == 0) {
        cout << "EMPTY\n";
        return o;
    }

    typename Map<T1, T2>::Iterator iter = M.begin();
    typename Map<T1, T2>::Iterator end = M.end();
    while (iter != end) {
        o << iter->first << ' ' << iter->second << '\n';
        iter++;
    }
    return o;
}