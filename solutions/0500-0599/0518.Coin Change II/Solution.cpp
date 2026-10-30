// 题目：518. 零钱兑换 II（Coin Change II）
// 思路：完全背包求组合数。f[i][j] 表示用前 i 种硬币凑出金额 j 的方案数，金额从小到大枚举以允许同一种硬币重复使用。
// 时间复杂度：O(m·n)，m 为硬币种类数、n 为金额；空间复杂度：O(m·n)，即 DP 表大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int change(int amount, vector<int>& coins) {  // 返回凑出 amount 的硬币组合数（顺序不同视为同一种）
        int m = coins.size(), n = amount;  // m 是硬币种类数，n 是目标金额
        unsigned f[m + 1][n + 1];  // f[i][j]：用前 i 种硬币凑出金额 j 的方案数，用无符号类型避免负数语义
        memset(f, 0, sizeof(f));  // 方案数全部初始化为 0
        f[0][0] = 1;  // 不选任何硬币凑出 0 元，恰好一种空方案
        for (int i = 1; i <= m; ++i) {  // 逐个加入第 i 种硬币
            for (int j = 0; j <= n; ++j) {  // 金额从小到大枚举，允许同种硬币重复使用
                f[i][j] = f[i - 1][j];  // 完全不用第 i 种硬币的方案数
                if (j >= coins[i - 1]) {  // 金额够用才可能再放一枚该硬币
                    f[i][j] += f[i][j - coins[i - 1]];  // 用掉一枚后，剩余金额仍可用前 i 种硬币（完全背包的复用）
                }  // 分支结束
            }  // 枚举完金额
        }  // 枚举完硬币种类
        return f[m][n];  // 用全部硬币凑出 amount 的方案数
    }  // 方法结束
};  // 类定义结束