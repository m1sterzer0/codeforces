#include <bits/stdc++.h>

using namespace std;

const int N = 123456;
const int m = 5;
const int k = 6;

int a[N][m];
int score[N];
int cost[m];
int solved[m];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", a[i] + j);
      if (a[i][j] != -1) {
        solved[j]++;
      }
    }
  }
  for (int bots = 0; bots <= ((1 << (k - 1)) - 1) * n; bots++) {
    for (int j = 0; j < m; j++) {
      int total = n + bots;
      int cur = solved[j];
      if (a[0][j] != -1 && a[1][j] != -1 && a[0][j] > a[1][j]) {
        cur += bots;
      }
      cost[j] = 500;
      while (cost[j] < 500 * k && 2 * cur <= total) {
        cur *= 2;
        cost[j] += 500;
      }
    }
    for (int i = 0; i < 2; i++) {
      score[i] = 0;
      for (int j = 0; j < m; j++) {
        if (a[i][j] != -1) {
          score[i] += cost[j] / 250 * (250 - a[i][j]);
        }
      }
    }
    if (score[0] > score[1]) {
      printf("%d\n", bots);
      return 0;
    }
  }
  printf("%d\n", -1);
  return 0;
}