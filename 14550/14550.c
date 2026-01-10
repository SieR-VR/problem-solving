#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a > b) ? (b) : (a))
#define MAX(a, b) ((a > b) ? (a) : (b))

typedef int dp_state_t;

const dp_state_t ZERO_INITIAL_STATE = 0;
const dp_state_t INITIAL_STATE = -10000000;

int main() {
  while (1) {
    int flag;
    scanf("%d", &flag);

    if (!flag)
      return 0;

    int n = flag, s, t;
    scanf("%d %d", &s, &t);

    int *arr = (int *)malloc(sizeof(int) * (n + 2));
    for (int i = 1; i <= n; i++)
      scanf("%d", &arr[i]);
    arr[0] = 0;
    arr[n + 1] = 0;

    dp_state_t dp[202][202];

    dp[0][0] = ZERO_INITIAL_STATE;

    for (int turn = 1; turn <= t; turn++)
      dp[0][turn] = INITIAL_STATE;

    for (int cell = 1; cell <= n + 1; cell++)
      for (int turn = 0; turn <= t; turn++)
        dp[cell][turn] = INITIAL_STATE;

    for (int cell = 1; cell <= n + 1; cell++)
      for (int turn = 1; turn <= t; turn++)
        for (int roll = 1; (roll <= s) && (roll <= cell); roll++)
          dp[cell][turn] =
              MAX(dp[cell][turn], dp[cell - roll][turn - 1] + arr[cell]);

    int maximum_score = INITIAL_STATE;
    for (int turn = 0; turn <= t; turn++) {
      maximum_score = MAX(maximum_score, dp[n + 1][turn]);
    }

    printf("%d\n", maximum_score);
  }
}
