#include <stdio.h>
#include <stdlib.h>

#include <string.h>

int dp[5000];

int main() {
    char pw[5001];
    scanf("%s", pw);

    if (pw[0] == '0') {
        printf("0\n");
        return 0;
    }

    int len = strlen(pw);
    dp[0] = 1;

    int first = (pw[0] - '0') * 10 + (pw[1] - '0');
    dp[1] = 1 + (first <= 26);

    int flag = 0;

    for (int i = 2; i < len; i++) {
        int target = (pw[i - 1] - '0') * 10 + (pw[i] - '0');
        if (target % 10 == 0 && (target != 10 && target != 20)) {
            flag = 1;
            break;
        }
        int seek = pw[i + 1] == '0';

        dp[i] = (dp[i - 1] * (!seek) + (dp[i - 2]) * (target <= 26)) % 1000000;
    }

    if (!flag) {
        printf("%d\n", dp[len - 1]);
    } else {
        printf("0\n");
    }
}
