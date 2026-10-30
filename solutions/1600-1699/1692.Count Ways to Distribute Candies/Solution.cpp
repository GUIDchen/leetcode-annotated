// 题目：1692. 计算分配糖果的不同方式（Count Ways to Distribute Candies）
// 思路：第二类斯特林数；f[i][j] 表示前 i 颗糖恰放进 j 个非空袋子的方案数，转移 f[i][j] = f[i-1][j]*j + f[i-1][j-1]。
// 时间复杂度：O(n * k)，双重循环遍历整张表；空间复杂度：O(n * k)，需要保存 n+1 行 k+1 列的 dp 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int waysToDistribute(int n, int k) {  // n：糖果总数；k：恰好分成的非空袋子数
        const int mod = 1e9 + 7;  // 取模常量，防止方案数溢出
        int f[n + 1][k + 1];  // f[i][j]：前 i 颗糖放进 j 个非空袋子的方案数
        memset(f, 0, sizeof(f));  // 整表清零，未计算的状态默认记为 0
        f[0][0] = 1;  // 边界：0 颗糖、0 个袋子只有一种空方案，作为递推起点
        for (int i = 1; i <= n; ++i) {  // 逐颗放入糖果，从第 1 颗到第 n 颗
            for (int j = 1; j <= k; ++j) {  // 枚举当前已用到的非空袋子数
                f[i][j] = (1LL * f[i - 1][j] * j + f[i - 1][j - 1]) % mod;  // 放进已有 j 个袋子之一，或单独新开一个袋子
            }
        }
        return f[n][k];  // 答案：n 颗糖恰好分成 k 个非空袋子的方案数
    }
};