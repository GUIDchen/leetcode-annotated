// 题目：600. 不含连续 1 的非负整数（Non-negative Integers without Consecutive Ones）
// 思路：数位 DP，从最高位往低位逐位填 0/1，用 pre 表示上一位是否为 1、用 limit 表示是否紧贴 n 的上界，并对非受限状态记忆化。
// 时间复杂度：O(log n)，状态只有「位数 × 上一位取值」；空间复杂度：O(log n)，记忆化数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findIntegers(int n) {  // 统计 [0, n] 区间内二进制表示不含相邻 1 的整数个数
        int m = 32 - __builtin_clz(n);  // 用前导零个数算出 n 的二进制位数 m，即需要枚举的数位长度
        int f[m][2];  // 记忆化数组：f[i][pre] 表示第 i 位以下、上一位为 pre 时不受限的方案数
        memset(f, -1, sizeof(f));  // 初始化为 -1，表示该状态还没有被计算过
        auto dfs = [&](this auto&& dfs, int i, int pre, bool limit) -> int {  // 递归 lambda：i 是当前处理到第几位，pre 是上一位是否为 1，limit 表示是否贴着 n 的上界
            if (i < 0) {  // 所有位都已经填完，得到一个合法整数
                return 1;  // 这个填法贡献 1 种方案
            }  // 递归出口结束
            if (!limit && f[i][pre] != -1) {  // 不受上界限制的状态可以复用之前算好的结果
                return f[i][pre];  // 直接返回记忆化的方案数，避免重复搜索
            }  // 记忆化命中判断结束
            int up = limit ? (n >> i & 1) : 1;  // 受限时这一位最多取到 n 的对应位，否则可以自由取到 1
            int ans = 0;  // 累计当前状态下的方案数
            for (int j = 0; j <= up; ++j) {  // 枚举当前位能填的数字 j（0 或 1）
                if (j && pre) {  // 上一位是 1 且这一位也想填 1，会出现连续的 1
                    continue;  // 这种填法非法，直接跳过
                }  // 合法性判断结束
                ans += dfs(i - 1, j, limit && j == up);  // 递归处理下一位；只有既受上界限制又恰好取到上界时，新状态才继续受限
            }  // 枚举当前位结束
            if (!limit) {  // 不受限的状态才对所有 n 通用，适合记忆化
                f[i][pre] = ans;  // 把答案存起来，下次直接复用
            }  // 记忆化写入结束
            return ans;  // 返回当前状态的方案数
        };  // 递归 lambda 定义结束
        return dfs(m - 1, 0, true);  // 从最高位开始枚举，上一位视为 0，且一开始紧贴上界
    }  // 方法结束
};  // 类定义结束
