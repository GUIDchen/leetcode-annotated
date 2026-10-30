// 题目：3339. 查找 K 偶数数组的数量（Find the Number of K-Even Arrays）
// 思路：记忆化搜索。按位置从左往右填数，状态是 (已填位数 i, 还差的相邻偶数对 j, 上一位的奇偶性 k)；放奇数有 cnt1 种选法，放偶数有 cnt0 种选法。
// 时间复杂度：O(n·k) 个状态，每个状态 O(1) 转移；空间复杂度：O(n·k)，即记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countOfArrays(int n, int m, int k) {  // n：数组长度；m：元素取值 1..m；k：要求恰好有 k 对相邻的偶数
        int f[n][k + 1][2];  // 记忆化数组：f[i][j][k] 表示填到第 i 位、还差 j 对相邻偶数、上一位奇偶性为 k 时的方案数
        memset(f, -1, sizeof(f));  // 全部置 -1，表示该状态尚未被计算过
        const int mod = 1e9 + 7;  // 取模常量，防止方案数过大
        int cnt0 = m / 2;  // 1..m 中偶数的个数
        int cnt1 = m - cnt0;  // 1..m 中奇数的个数
        auto dfs = [&](this auto&& dfs, int i, int j, int k) -> int {  // C++23 显式对象参数 this auto&&：让 lambda 能在内部递归调用自己
            if (j < 0) {  // 还差的相邻偶数对已经被减成负数，说明超额了
                return 0;  // 超额方案不合法，贡献 0
            }  // if 结束
            if (i >= n) {  // 已经填满 n 个数
                return j == 0 ? 1 : 0;  // 恰好凑够 k 对相邻偶数才算 1 个合法方案，否则为 0
            }  // if 结束
            if (f[i][j][k] != -1) {  // 该状态已经计算过
                return f[i][j][k];  // 直接返回记忆化结果，避免重复搜索
            }  // if 结束
            int a = 1LL * cnt1 * dfs(i + 1, j, 1) % mod;  // 第 i 位放奇数：有 cnt1 种选法，上一位奇偶性记为 1，不消耗相邻偶数配额
            int b = 1LL * cnt0 * dfs(i + 1, j - (k & 1 ^ 1), 0) % mod;  // 第 i 位放偶数：有 cnt0 种选法；(k & 1 ^ 1) 在上一位是偶数时为 1，说明新产生一对相邻偶数
            return f[i][j][k] = (a + b) % mod;  // 两种选择相加取模，并写回 f 作为记忆化结果
        };  // lambda 定义结束
        return dfs(0, k, 1);  // 从第 0 位开始搜，还需要 k 对；虚拟上一位取 1（奇数），避免首位被误算成一对偶数
    }  // 方法结束
};  // 类定义结束
