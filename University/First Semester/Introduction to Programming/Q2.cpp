// Hubert Jastrzębski | Satori Q2 (Słowo specjalne) | 2024-12-14
// https://satori.tcs.uj.edu.pl/contest/9410000/problems/9614801

#include <bits/stdc++.h>

using namespace std;

#define MY_DEBUG 0

int main(int argc, char **argv) {
#if MY_DEBUG
    argc = 4;
    char *args[] = {0, "0.in", "0.out", "KROPKA"};
    argv = args;
#endif

    if (argc != 4) return 0;
    string in_name = string(argv[1]);
    string out_name = string(argv[2]);
    string special = string(argv[3]);
    for (auto &s : special)
        s = tolower(s);

    ifstream in(in_name);
    if (!in.good()) return 0;
    ofstream out(out_name);

    int line_cnt = 0, comment_cnt = 0, word_cnt = 0, good_cnt = 0;
    int mode = 0; // 0 - nic, 1 - komentarz, 2 - slowo

    string buffer = "";
    auto check = [&]() {
      if (mode == 0) buffer.clear();
      if (mode != 2 || buffer.empty())
          return;
      mode = 0;

      bool is_ok = (buffer == special);

      // usunięcie:
      if (!is_ok && buffer.size() == special.size() + 1) {
          bool is_del = false;
          int i = 0;
          for (int j = 0; j < special.size(); i++, j++) {
              if (buffer[i] != special[j]) {
                  if (is_del) break;
                  is_del = true;
                  i++;
                  if (buffer[i] != special[j]) break;
              }
          }

          if (!is_del || (is_del && i == buffer.size()))
              is_ok = true;
      }

      // dodanie:
      if (!is_ok && buffer.size() == special.size() - 1) {
          bool is_add = false;
          int i = 0;
          for (int j = 0; j < special.size() - 1; i++, j++) {
              if (buffer[i] != special[j]) {
                  if (is_add) break;
                  is_add = true;
                  i--;
              }
          }

          if (!is_add || (is_add && i == buffer.size() - 1 && buffer.back() == special.back()))
              is_ok = true;
      }

      // zamiana:
      if (!is_ok && buffer.size() == special.size()) {
          bool is_swap = false;
          int i = 0;
          for (int j = 0; j < special.size(); i++, j++) {
              if (buffer[i] != special[j]) {
                  if (is_swap) break;
                  is_swap = true;
              }
          }

          if (i == buffer.size())
              is_ok = true;
      }

      if (is_ok) {
          out << "Linia " << line_cnt << ": " << buffer << '\n';
          good_cnt++;
      }
      word_cnt++;
      buffer.clear();
    };

    string line;
    while (getline(in, line)) {
        line_cnt += (mode != 1);

        for (int i = 0; i < line.size(); i++) {
            if (isalpha(line[i])) {
                if (mode != 1) {
                    mode = 2;
                    if (buffer.size() < 40)
                        buffer += tolower(line[i]);
                }
            } else if (isdigit(line[i])) {
                if (mode == 2 && buffer.size() < 40)
                    buffer += line[i];
            } else if (line[i] == '/' && i != line.size() - 1 && line[i + 1] == '*') {
                mode = 1;
                comment_cnt++;
                i++;
            } else if (mode == 1 && line[i] == '*' && i != line.size() - 1 && line[i + 1] == '/') {
                if (--comment_cnt == 0)
                    mode = (buffer.empty() ? 0 : 2);
                i++;
            } else {
                check();
            }
        }

        check();
    }

    out << "Wyrazy: " << word_cnt << '\n';
    out << "Wyrazy specjalne: " << good_cnt;

    in.close();
    out.close();
}