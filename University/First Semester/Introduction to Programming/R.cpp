// Hubert Jastrzębski | Satori R (Stos i kolejka) | 2024-12-25
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9424456

#include <iostream>
#include <cstring>

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
  bool full();
  void clear();
  void resize(int n);
  ~stack();
};

class point {
 private:
  int x, y;

 public:
  point();
  point(int x, int y);
  int getX();
  int getY();
  void print();
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
  point front();
  bool empty();
  bool full();
  void clear();
  void resize(int n);
  ~queue();
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

bool stack::full() {
    return size == max_size;
}

void stack::clear() {
    size = 0;
}

void stack::resize(int n) {
    if (n > max_size) {
        max_size = n;
        arr = (long long *) realloc(arr, max_size * sizeof(long long));
    }
}
stack::~stack() {
    free(arr);
}

point::point() : x(0), y(0) {}

point::point(int x, int y) : x(x), y(y) {}

int point::getX() {
    return x;
}

int point::getY() {
    return y;
}

void point::print() {
    std::cout << x << ' ' << y << '\n';
}

queue::queue() : max_size(15), front_pos(0), back_pos(0), size(0) {
    arr = new point[max_size];
}

queue::queue(int max_size) : max_size(max_size), front_pos(0), back_pos(0), size(0) {
    arr = new point[max_size];
}

void queue::enqueue(const point &x) {
    if (size >= max_size)
        throw std::string("ENQUEUE");
    arr[back_pos % max_size] = x;
    back_pos++, size++;
}

point queue::dequeue() {
    if (size == 0)
        throw std::string("DEQUEUE");
    size--;
    return arr[front_pos++ % max_size];
}

point queue::front() {
    if (size == 0)
        throw std::string("FRONT");
    return arr[front_pos % max_size];
}

bool queue::empty() {
    return size == 0;
}

bool queue::full() {
    return size == max_size;
}

void queue::clear() {
    front_pos = back_pos = size = 0;
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
