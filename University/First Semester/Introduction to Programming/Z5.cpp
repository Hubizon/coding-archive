// Hubert Jastrzębski | Satori Z5 (Kółko i krzyżyk) | 2024-12-24
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9423550

#include <bits/stdc++.h>

using namespace std;

enum CellType {
  CELL_EMPTY = '#',
  CELL_O = 'O',
  CELL_X = 'X'
};

enum GameResult {
  RESULT_NOT_ENDED,
  RESULT_X_WON,
  RESULT_O_WON,
  RESULT_TIE
};

enum MoveType {
  MOVE_BAD,
  MOVE_OK,
  MOVE_TIE
};

struct board {
  array<array<CellType, 3>, 3> state;

  board() {
      for (int i = 0; i < 3; i++)
          for (int j = 0; j < 3; j++)
              state[i][j] = CELL_EMPTY;
  }

  GameResult Check() {
      bool is_tie = true;
      int sum_d1 = 0, sum_d2 = 0;
      for (int i = 0; i < 3; i++) {
          int sum_row = 0, sum_column = 0;
          for (int j = 0; j < 3; j++) {
              if (state[i][j] == CELL_EMPTY) is_tie = false;
              sum_row += (state[i][j] != CELL_EMPTY) * (state[i][j] == CELL_X ? 1 : -1);
              sum_column += (state[j][i] != CELL_EMPTY) * (state[j][i] == CELL_X ? 1 : -1);
          }
          if (sum_row == 3 || sum_column == 3) return RESULT_X_WON;
          if (sum_row == -3 || sum_column == -3) return RESULT_O_WON;

          sum_d1 += (state[i][i] != CELL_EMPTY) * (state[i][i] == CELL_X ? 1 : -1);
          sum_d2 += (state[i][2 - i] != CELL_EMPTY) * (state[i][2 - i] == CELL_X ? 1 : -1);
      }

      if (sum_d1 == 3 || sum_d2 == 3) return RESULT_X_WON;
      if (sum_d1 == -3 || sum_d2 == -3) return RESULT_O_WON;

      if (is_tie) return RESULT_TIE;
      return RESULT_NOT_ENDED;
  }

  void Print() {
      cout << "\nPlansza:\n";
      for (auto &row : state) {
          for (auto &field : row)
              cout << (char) field;
          cout << '\n';
      }
      cout << '\n';
  }
};

MoveType CheckMove(board &b, int i, int j, CellType current_player, GameResult desired) {
    if (b.state[i][j] != CELL_EMPTY)
        return MOVE_BAD;

    b.state[i][j] = current_player;
    auto r = b.Check();
    if (r != RESULT_NOT_ENDED) {
        b.state[i][j] = CELL_EMPTY;
        if (r == RESULT_TIE)
            return MOVE_TIE;
        if (r == desired)
            return MOVE_OK;
        return MOVE_BAD;
    }

    auto res = MOVE_OK;
    for (int it = 0; it < 3; it++) {
        for (int jt = 0; jt < 3; jt++) {
            auto move = CheckMove(b, it, jt, (current_player == CELL_X ? CELL_O : CELL_X),
                                  (desired == RESULT_X_WON ? RESULT_O_WON : RESULT_X_WON));
            if (move == MOVE_OK) {
                b.state[i][j] = CELL_EMPTY;
                return MOVE_BAD;
            } else if (move == MOVE_TIE)
                res = MOVE_TIE;
        }
    }

    b.state[i][j] = CELL_EMPTY;

    return res;
}

pair<int, int> Move(board &b) {
    pair<int, int> tie_move;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            auto r = CheckMove(b, i, j, CELL_X, RESULT_X_WON);
            if (r == MOVE_OK)
                return {i, j};
            if (r == MOVE_TIE)
                tie_move = {i, j};
        }
    }

    return tie_move;
}

int main() {
    board b;
    b.Print();

    GameResult result = RESULT_NOT_ENDED;
    bool is_computers_turn = false;
    while (result == RESULT_NOT_ENDED) {
        if (is_computers_turn) {
            auto [i, j] = Move(b);
            b.state[i][j] = CELL_X;
            cout << "Ruch komputera! Rusza sie na pole: (" << i + 1 << ", " << j + 1 << ")\n";
        } else {
            cout << "Twoj ruch! Ruszasz sie na pole: ";
            int x, y;
            cin >> x >> y;
            if (x < 1 || x > 3 || y < 1 || y > 3 || b.state[x - 1][y - 1] != CELL_EMPTY) {
                cout << "Niepoprawne pole!\n";
                continue;
            }
            x--, y--;
            b.state[x][y] = CELL_O;
        }

        b.Print();
        result = b.Check();
        is_computers_turn ^= 1;
    }

    if (result == RESULT_O_WON)
        cout << "Komputer przegral! To... nie powinno byc mozliwe..?";
    else if (result == RESULT_X_WON)
        cout << "Komputer wygral";
    else
        cout << "Remis";
}