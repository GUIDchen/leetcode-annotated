// 题目：2992. 自整除排列的数量（Number of Self-Divisible Permutations）
// 核心思路：状压 DP + 记忆化搜索；mask 的二进制位记录已用的数字，按位置下标 i 从小到大填数，要求 gcd(i, j) == 1。
// 时间复杂度：O(n · 2^n)，每个状态最多枚举 n 个数字；空间复杂度：O(2^n)，记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 对外可见的解法接口
    int selfDivisiblePermutationCount(int n) {  // n 为排列长度，返回满足「每个位置 i 与它上面的数字互质」的排列个数
        int f[1 << (n + 1)];  // 记忆化数组，下标是已用数字的二进制掩码，需要 1 << (n + 1) 个槽位
        memset(f, -1, sizeof(f));  // 全部初始化成 -1，表示该状态尚未被计算过
        function<int(int)> dfs = [&](int mask) {  // 递归函数：mask 记录已填入的数字集合，返回剩余位置的合法填法数
            if (f[mask] != -1) {  // 该状态已经计算过
                return f[mask];  // 直接返回缓存的结果，避免重复搜索
            }  // 否则继续往下计算
            int i = __builtin_popcount(mask) + 1;  // 已用数字个数加一，就是当前要填的位置下标（从 1 开始）
            if (i > n) {  // 位置下标超过 n，说明 n 个位置都已填满
                return 1;  // 得到一个完整的合法排列，贡献 1 种方案
            }  // 否则继续枚举能填的数字
            f[mask] = 0;  // 先把当前状态的答案清 0，作为累加起点
            for (int j = 1; j <= n; ++j) {  // 枚举准备放在位置 i 上的数字 j
                if ((mask >> j & 1) == 0 && __gcd(i, j) == 1) {  // j 还没被使用，且它与位置 i 互质（gcd 为 1 就满足自整除条件）
                    f[mask] += dfs(mask | 1 << j);  // 把 j 标进 mask 后递归，累加后续位置的方案数
                }  // 不满足条件就跳过这个数字
            }  // 数字枚举结束
            return f[mask];  // 返回并缓存当前状态的答案
        };  // 递归函数定义结束
        return dfs(0);  // 从空掩码出发，求全部方案数
    }  // 方法结束
};  // 类结束