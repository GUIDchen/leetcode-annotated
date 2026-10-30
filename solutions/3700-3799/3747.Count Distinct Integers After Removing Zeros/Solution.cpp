// 题目：3747. 统计移除零后不同整数的数目（Count Distinct Integers After Removing Zeros）
// 核心思路：去掉所有零后得到的数必不含 0，且任何不含 0 的数 y 都能由 y 自身得到，所以 [1, n] 去零后的不同结果恰好是区间内不含数字 0 的整数；用数位 DP 按位枚举，统计不含 0 的正整数个数。
// 复杂度：时间 O(log n)，每个数位状态至多被计算一次；空间 O(log n)，记忆化数组规模与上界位数成正比。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countDistinct(long long n) {  // 返回 1..n 每个数去掉所有零后能得到的不同整数个数
        string s = to_string(n);  // 把上界 n 转成字符串，便于逐位枚举
        int m = s.size();  // m 是上界的位数，也是数位 DP 的递归深度
        static long long f[20][2][2][2];  // 记忆化数组，下标依次为位置、是否已出现 0、是否仍在前导零、是否贴上界
        memset(f, -1, sizeof(f));  // 先全部置为 -1，表示该状态还没有被计算过

        auto dfs = [&](this auto&& dfs, int i, int zero, int lead, int limit) -> long long {  // 数位 DP：i 为当前位，zero 表示已出现过数字 0，lead 表示仍在前导零，limit 表示是否贴着上界；返回合法方案数
            if (i == m) {  // 已经填完全部数位
                return (zero == 0 && lead == 0) ? 1 : 0;  // 既已开始填数又没出现过 0，说明是一个不含 0 的正整数，计 1 个
            }  // 递归出口结束
            if (!limit && f[i][zero][lead][limit] != -1) {  // 不受上界限制时状态可复用，命中缓存就直接返回
                return f[i][zero][lead][limit];  // 返回已算好的方案数
            }  // 缓存判断结束

            int up = limit ? (s[i] - '0') : 9;  // 贴着上界时当前位最多取到 s[i]，否则可以取到 9
            long long ans = 0;  // ans 累加当前位枚举出的所有后续方案数
            for (int d = 0; d <= up; d++) {  // 枚举当前位填入的数字 d
                int nxtZero = zero || (d == 0 && !lead);  // 已经填过数却填入 0，就标记该数含有数字 0
                int nxtLead = lead && d == 0;  // 一直填 0 才继续处于前导零阶段
                int nxtLimit = limit && d == up;  // 只有前缀一直紧贴上界，限制才会继续传递
                ans += dfs(i + 1, nxtZero, nxtLead, nxtLimit);  // 递归处理下一位，把子问题的方案数累加进来
            }  // 当前位的枚举结束

            if (!limit) f[i][zero][lead][limit] = ans;  // 只有不受上界限制的状态才通用，可以写入缓存
            return ans;  // 返回当前状态下的合法方案数
        };  // lambda 定义结束

        return dfs(0, 0, 1, 1);  // 从最高位开始：尚未出现 0、处于前导零、贴着上界
    }  // 方法结束
};  // 类定义结束
