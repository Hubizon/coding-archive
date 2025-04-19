// Hubert Jastrzębski | Satori W (Macierze) | 2025-01-24
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9660321

#include <bits/stdc++.h>

using namespace std;

class Matrix {
 private:
  int **a = nullptr;
  int n = 0, m = 0;

  void clear_();
  long long det_(int nl, int startingRow, int *colAvailable) const;

 public:
  Matrix() {};
  Matrix(int n, int m);
  Matrix(const Matrix &matrix) { *this = matrix; };
  ~Matrix();

  long long determinant() const;
  void operator=(const Matrix &A);
  void operator=(Matrix &&A);

  friend Matrix operator+(const Matrix &A, const Matrix &B);
  friend Matrix operator*(const Matrix &A, const Matrix &B);
  friend Matrix operator^(const Matrix &A, int k);
  friend istream &operator>>(istream &s, Matrix &A);
  friend ostream &operator<<(ostream &s, const Matrix &A);
};

Matrix::Matrix(int n, int m) : n(n), m(m) {
    a = new int *[n];
    for (int i = 0; i < n; i++) {
        a[i] = new int[m];
        for (int j = 0; j < m; j++)
            a[i][j] = 0;
    }
}

Matrix::~Matrix() {
    clear_();
}

void Matrix::clear_() {
    if (a != nullptr) {
        for (int i = 0; i < n; i++)
            delete[] a[i];
        delete[] a;
    }
}

long long Matrix::det_(int ml, int startingRow, int *colAvailable) const {
    if (ml == 1)
        return a[startingRow][colAvailable[0]];

    int *newColums = new int[ml - 1];
    long long s = 0;
    int p = 1;
    for (int i = 0; i < ml; i++) {
        int r = 0;
        for (int j = 0; j < ml - 1; j++) {
            if (r == i) r++;
            newColums[j] = colAvailable[r++];
        }
        if (a[startingRow][colAvailable[i]] != 0)
            s += p * a[startingRow][colAvailable[i]] * det_(ml - 1, startingRow + 1, newColums);
        p *= -1;
    }

    delete[] newColums;
    return s;
}

long long Matrix::determinant() const {
    if (n != m)
        throw "ERROR DETERMINANT";
    if (n == 0) return 0;
    int *colAvailable = new int[m];
    for (int i = 0; i < m; i++)
        colAvailable[i] = i;
    return det_(m, 0, colAvailable);
}

void Matrix::operator=(const Matrix &matrix) {
    clear_();

    n = matrix.n;
    m = matrix.m;
    a = new int *[m];
    for (int i = 0; i < n; i++) {
        a[i] = new int[m];
        for (int j = 0; j < m; j++)
            a[i][j] = matrix.a[i][j];
    }
}

void Matrix::operator=(Matrix &&matrix) {
    if (this == &matrix) return;
    clear_();
    n = matrix.n;
    m = matrix.m;
    a = matrix.a;
    matrix.a = nullptr;
}

Matrix operator+(const Matrix &A, const Matrix &B) {
    if (A.n != B.n || A.m != B.m)
        throw "ERROR ADD";

    Matrix temp(A.n, A.m);

    for (int i = 0; i < A.n; i++)
        for (int j = 0; j < A.m; j++)
            temp.a[i][j] = A.a[i][j] + B.a[i][j];

    return temp;
}

Matrix operator*(const Matrix &A, const Matrix &B) {
    if (A.m != B.n)
        throw "ERROR MULTIPLY";

    Matrix temp(A.n, B.m);

    for (int i = 0, j; i < A.n; i++)
        for (j = 0; j < B.m; j++)
            temp.a[i][j] = 0;

    for (int i = 0; i < A.n; i++)
        for (int z = 0; z < A.m; z++)
            for (int j = 0; j < B.m; j++)
                (temp.a[i][j] += A.a[i][z] * B.a[z][j]) %= 1000;

    return temp;
}

Matrix operator^(const Matrix &A, int k) {
    if (A.n != A.m)
        throw "ERROR POWER";

    int n = A.n;
    Matrix res(n, n), B = A;
    for (int i = 0; i < n; i++)
        res.a[i][i] = 1;

    while (k) {
        if (k % 2)
            res = res * B;
        B = B * B;
        k /= 2;
    }

    return res;
}

istream &operator>>(istream &s, Matrix &A) {
    for (int i = 0; i < A.n; i++)
        for (int j = 0; j < A.m; j++)
            s >> A.a[i][j];
    return s;
}

ostream &operator<<(ostream &s, const Matrix &A) {
    for (int i = 0, j; i < A.n; i++) {
        for (j = 0; j < A.m; j++)
            s << A.a[i][j] % 1000 << ' ';
        s << '\n';
    }
    return s;
}

void ADD(const Matrix &A) {
    int n2, m2;
    cin >> n2 >> m2;
    Matrix B(n2, m2);
    cin >> B;

    cout << (A + B);
}

void MULTIPLY(const Matrix &A) {
    int n2, m2;
    cin >> n2 >> m2;
    Matrix B(n2, m2);
    cin >> B;

    cout << (A * B);
}

void POWER(const Matrix &A) {
    int k;
    cin >> k;

    cout << (A ^ k);
}

void DETERMINANT(const Matrix &A) {
    cout << A.determinant() << '\n';
}

int main() {
    void (*OP[])(const Matrix &) = {&ADD, &MULTIPLY, &POWER, &DETERMINANT};

    int z;
    cin >> z;
    while (z--) {
        int op;
        cin >> op;

        int n2, m2;
        cin >> n2 >> m2;
        Matrix A(n2, m2);
        cin >> A;

        try {
            OP[op - 1](A);
        } catch (const char* &e) {
            cout << e << '\n';
        }
    }
}
