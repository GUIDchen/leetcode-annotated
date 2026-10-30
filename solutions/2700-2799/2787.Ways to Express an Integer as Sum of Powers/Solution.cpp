// 题目：2787. 将一个数字表示成幂的和的方案数（Ways to Express an Integer as Sum of Powers）
// 核心思路：0-1 背包计数 DP。底数 i 的 x 次幂就是物品 i 的体积，每个底数最多用一次；f[i][j] 表示用 1..i 凑出 j 的方案数。
// 时间复杂度：O(n^2)，n 个底数各扫一遍目标和；空间复杂度：O(n^2)，二维 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfWays(int n, int x) {  // n：目标和；x：幂次；返回把 n 写成若干互不相同正整数 x 次幂之和的方案数
        const int mod = 1e9 + 7;  // 答案要对 1e9+7 取模
        int f[n + 1][n + 1];  // f[i][j]：只用 1..i 这些底数、和恰好为 j 的方案数（变长数组按 n+1 开）
        memset(f, 0, sizeof(f));  // 二维 DP 表全部清零，避免用到未定义的值
        f[0][0] = 1;  // 边界：一个数都不用凑出 0，只有 1 种方案
        for (int i = 1; i <= n; ++i) {  // 逐个考虑底数 i（每个底数最多选一次）
            long long k = (long long) pow(i, x);  // i 的 x 次幂，即选 i 时贡献的体积（用 long long 防止溢出）
            for (int j = 0; j <= n; ++j) {  // 枚举目标和 j
                f[i][j] = f[i - 1][j];  // 不选 i：方案数直接从上一行继承
                if (k <= j) {  // 只有幂值 k ≤ j 时，才装得进容量 j
                    f[i][j] = (f[i][j] + f[i - 1][j - k]) % mod;  // 选 i：把凑出 j-k 的方案数累加进来，并按模数取余
                }  // if 分支结束
            }  // 内层循环结束
        }  // 外层循环结束
        return f[n][n];  // 返回用 1..n 这些底数凑出和 n 的方案数
    }  // 方法结束
};  // 类定义结束