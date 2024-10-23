// https://leetcode.com/problems/find-maximum-removals-from-source-string/
#include <stdio.h>
#define N 3003
#define C 2
int dp[N][C], temp[N][C], disregard_cnt[N], take[N];
// 0 - length of longest common subsequence between source and pattern.
// 1 - maximum characters that can be removed from source without reducing max LCS formed 

void init() {
    memset(dp, 0, sizeof(dp));
    memset(temp, 0, sizeof(temp));
    memset(disregard_cnt, -1, sizeof(disregard_cnt));
    memset(take, 0, sizeof(take));
    return;
}
void ckmax(const void* _self, const void* _other, int row, int row1) {
    int* t1 = (int*)_self;
    int* t2 = (int*)_other;
    if (t1[row * C] == t2[row1 * C]) {
        if (t1[row * C + 1] < t2[row1 * C + 1]) { // absorb _other's value as _self  is lesser
            t1[row * C + 1] = t2[row1 * C + 1];
        }
    }
    if (t1[row * C] < t2[row1 * C]) { // absorb _other's value as _self  is lesser
        t1[row * C] = t2[row1 * C];
        t1[row * C + 1] = t2[row1 * C + 1];
    }
    return;
}
void ckmin(const void* _self, const void* _other, int row, int row1) {
    int* t1 = (int*)_self;
    int* t2 = (int*)_other;
    if (t1[row * C] == t2[row1 * C]) {
        if (t1[row * C + 1] > t2[row1 * C + 1]) { // absorb _other's value as _self  is higher
            t1[row * C + 1] = t2[row1 * C + 1];
        }
    }
    if (t1[row * C] > t2[row1 * C]) { // absorb _other's value as _self  is higher
        t1[row * C] = t2[row1 * C];
        t1[row * C + 1] = t2[row1 * C + 1];
    }
    return;
}
int maxRemovals(char* source, char* pattern, int* targetIndices, int targetIndicesSize) {
    init();
    int sn = strlen(source), pn = strlen(pattern), i, j, cnt = 0;
    for (i = 0; i < targetIndicesSize; i++) {
        disregard_cnt[targetIndices[i]] = i; // prefix count for start from current begin ?
        take[targetIndices[i]] = 1;
        // consider take[i-1],disregard_cnt[i-1] below
    }
    cnt = 0;
    for (i = 1; i <= 3002; i++) {
        if (disregard_cnt[i] != -1) {
            cnt = 0;
        }
        if ((disregard_cnt[i] == -1) && (disregard_cnt[i - 1] != -1)) {
            disregard_cnt[i] = disregard_cnt[i - 1] + (cnt == 0);
            cnt++;
        }
    }

    for (i = 1; i <= sn; i++) {
        for (j = 1; j <= pn; j++) {
            int withoutCurrent[1][2] = { dp[j][0],dp[j][1] + take[i - 1] };  // not tk current,can remove if allowed
            int withCurrent[1][2] = { dp[j - 1][0] + (source[i - 1] == pattern[j - 1]),dp[j - 1][1] }; // considering current

            // start of pattern with any index in source could have all previous characters deleted in source as its allowed here
            if (j == 1) { // start a new subsequence from current i in source by considering current index
                int dis_cnt[1][2] = { (source[i - 1] == pattern[j - 1]),disregard_cnt[i - 1] };
                ckmax(withCurrent, dis_cnt, 0, 0);
            }
            
            ckmax(temp, withoutCurrent, j, 0);
            ckmax(temp, withCurrent, j, 0);
            ckmax(temp, temp, j, j - 1);
        }
        memcpy(dp, temp, sizeof(dp));
    }
    return dp[pn][1];
}
void solve() {
    char src[N];
    char pat[N];
    int target[N];
    int n=10;
    // lazy to scan numbers from console.
    printf("%d",maxRemovals(src, pat, target, n));
    return;
}
int main() {
    solve();
}
