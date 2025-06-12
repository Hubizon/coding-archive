// Hubert Jastrzębski | Satori X (Fabryka) | 2025-06-12
// https://satori.tcs.uj.edu.pl/contest/9746928/problems/10025007

#include <iostream>
#include <functional>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

struct Job {
  int id;
  int a, b, c;
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;

        vector<Job> V(n);
        for (int i = 0; i < n; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            V[i] = { i, a, b, c };
        }

        vector<int> G1, G2;
        for (int i = 0; i < n; i++) {
            if (V[i].a < V[i].c)
                G1.push_back(i);
            else
                G2.push_back(i);
        }

        sort(G1.begin(), G1.end(), [&](int i, int j) { return V[i].a + V[i].b < V[j].a + V[j].b; });
        sort(G2.begin(), G2.end(), [&](int i, int j) { return V[i].c + V[i].b > V[j].c + V[j].b; });

        vector<int> P;
        for (auto& g1 : G1) P.push_back(g1);
        for (auto& g2 : G2) P.push_back(g2);

        int tA = 0, tB = 0, tC = 0;
        for (auto idx : P) {
            tA += V[idx].a;
            tB = max(tA, tB) + V[idx].b;
            tC = max(tB, tC) + V[idx].c;
        }

        int Pres = tC;

        auto calculate = [&](long long tasks, int timeA, int timeB, int timeC) {
          if (tasks == 0)
              return timeC;

          int rTimeA = 0, rTimeB = 0, rTimeC = 0, mTimeC = INT_MAX, mTimeBC = INT_MAX;
          for (int i = 0; i < n; i++) {
              if ((tasks >> i) & 1) {
                  rTimeA += V[i].a;
                  rTimeB += V[i].b;
                  rTimeC += V[i].c;
                  mTimeC = min(mTimeC, V[i].c);
                  mTimeBC = min(mTimeBC, V[i].b + V[i].c);
              }
          }

          if (mTimeC == INT_MAX) mTimeC = 0;
          if (mTimeBC == INT_MAX) mTimeBC = 0;
          return max({ timeA + rTimeA + mTimeBC, timeB + rTimeB + mTimeC, timeC + rTimeC });
        };

        vector<int> tempP;
        function<void(long long, int, int, int)> fun = [&](long long tasks, int timeA, int timeB, int timeC) {
          if (tempP.size() == n) {
              if (timeC < Pres) {
                  Pres = timeC;
                  P = tempP;
              }
              return;
          }

          if (calculate(tasks, timeA, timeB, timeC) >= Pres)
              return;

          vector<pair<int, int>> jobs;
          for (int i = 0; i < n; i++) {
              if ((tasks >> i) & 1) {
                  int nTimeA = timeA + V[i].a;
                  int nTimeB = max(nTimeA, timeB) + V[i].b;
                  int nTimeC = max(nTimeB, timeC) + V[i].c;
                  int score = calculate(tasks ^ (1LL << i), nTimeA, nTimeB, nTimeC);
                  jobs.push_back({ score, i });
              }
          }

          sort(jobs.begin(), jobs.end());

          for (auto [score, i] : jobs) {
              if (score >= Pres)
                  continue;
              if ((tasks >> i) & 1) {
                  tempP.push_back(i);
                  int nTimeA = timeA + V[i].a;
                  int nTimeB = max(nTimeA, timeB) + V[i].b;
                  int nTimeC = max(nTimeB, timeC) + V[i].c;
                  fun(tasks ^ (1LL << i), nTimeA, nTimeB, nTimeC);
                  tempP.pop_back();
              }
          }
        };

        fun((1LL << n) - 1, 0, 0, 0);

        cout << Pres << '\n';
        for (auto& p : P)
            cout << p + 1 << ' ';
        cout << '\n';
    }
}