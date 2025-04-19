// Hubert Jastrzębski | Satori Y1 (Vector) | 2025-01-31
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9660394

#ifndef CODING_ARCHIVE__SOLUTION_H_
#define CODING_ARCHIVE__SOLUTION_H_

#include <iostream>
#include <string>

class vector {
 private:
  std::string* tab = nullptr;
  int capacity = 1;
  int size = 0;

  void resize_(int c) {
      capacity = c;
      if (tab == nullptr)
          tab = new std::string[capacity];
      else {
          std::string* new_tab = new std::string[capacity];
          for (int i = 0; i < size; i++)
              new_tab[i] = std::move(tab[i]);

          delete[] tab;
          tab = new_tab;
      }
  }

 public:
  vector(int a = 4, int b = 0, std::string c = "") {
      if (b > a) a = b;
      resize_(a);
      for (int i = 0; i < b; i++)
          tab[i] = c;
      size = b;
  }

  vector(const vector& v) {
      *this = v;
  }

  ~vector() {
      delete[] tab;
  }

  void add(const std::string& x) {
      if (size == capacity)
          resize_(2 * capacity);
      tab[size++] = x;
  }

  int getSize() {
      return size;
  }

  void resize(int s) {
      if (s > capacity)
          resize_(2 * s);
      for (int i = size; i < s; i++)
          tab[i] = "";
      size = s;
  }

  void clear() {
      size = 0;
  }

  void insert(int i, const std::string& s) {
      if (size == capacity)
          resize_(2 * capacity);
      if (i < 0 || i > size) return;
      for (int j = size - 1; j >= i; j--)
          tab[j + 1] = std::move(tab[j]);
      tab[i] = s;
      size++;
  }

  void erase(int i) {
      if (i < 0 || i >= size) return;
      for (int j = i; j < size - 1; j++)
          tab[j] = std::move(tab[j + 1]);
      size--;
  }

  std::string& operator[](int i) {
      if (i >= size)
          return tab[size - 1];
      return tab[i];
  }

  void operator=(const vector& v) {
      if (this == &v) return;
      size = 0;
      resize_(v.capacity);
      for (int i = 0; i < v.size; i++)
          tab[i] = v.tab[i];
      size = v.size;
  }

  friend std::ostream& operator<<(std::ostream& out, vector& v) {
      for (int i = 0; i < v.size; i++)
          out << v[i] << ' ';
      return out;
  }

  friend std::istream& operator>>(std::istream& in, vector& v) {
      for (int i = 0; i < v.size; i++)
          in >> v[i];
      return in;
  }

  operator bool() const {
      return size != 0;
  }

  bool operator!() const {
      return size == 0;
  }
};

#endif //CODING_ARCHIVE__SOLUTION_H_
