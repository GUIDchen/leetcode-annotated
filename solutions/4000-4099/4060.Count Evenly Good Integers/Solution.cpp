// 题目：4060. 统计偶好数（Count Evenly Good Integers）
// 思路：偶好数的定义只看“偶数数字有多少个”，因此用数位 DP 逐位填数：状态只需记住已填偶数数字个数的奇偶 st 和是否一直贴着上界 lim，填满所有位时 st 为偶数（st == 0）即为偶好数；对 dfs 做记忆化，区间答案再由 calc(r) - calc(l-1) 两个前缀答案相减得到。
// 时间复杂度：O(D × 2 × 2 × 10)，D 为十进制位数（不超过 16），每个状态枚举 10 个数字；空间复杂度：O(D × 2 × 2)，即记忆化数组的大小。
class Solution {  // LeetCode 约定的题解类
    string s;  // s 为上界 x 的十进制串，dfs 沿它逐位枚举
    long long f[20][2][2];  // 记忆化：f[pos][st][lim]，pos 为当前位、st 为已填偶数数字个数的奇偶、lim 为是否贴着上界

    long long dfs(int pos, int st, bool lim) {  // 从第 pos 位开始填数，st 记录已填偶数数字个数的奇偶，lim 表示前面是否一直贴着上界
        if (pos >= s.size()) {  // 所有位都填完了
            return st ^ 1;  // st 为 0 表示偶数数字个数是偶数，st ^ 1 把 0→1、1→0，正好当计数用
        }  // 填完分支结束
        if (f[pos][st][lim] != -1) {  // 该状态已经算过
            return f[pos][st][lim];  // 直接返回记忆化结果，避免重复枚举
        }  // 命中缓存分支结束
        int up = lim ? s[pos] - '0' : 9;  // 贴着上界时当前位最多取 s[pos]，否则可以填 0..9
        long long res = 0;  // res 累计当前状态下的合法方案数
        for (int i = 0; i <= up; ++i) {  // 枚举当前位能填的数字 i
            res += dfs(pos + 1, (st + (i & 1 ^ 1)) % 2, lim && i == up);  // i 为偶数时 (i & 1) ^ 1 取 1，用它翻转“偶数数字个数”的奇偶；lim && i == up 维护上界标记
        }  // 当前位枚举结束
        return f[pos][st][lim] = res;  // 记入记忆化数组并返回
    }  // dfs 结束

    long long calc(long long x) {  // 计算 [0, x] 中偶好数的个数
        s = to_string(x);  // 把上界转成字符串，供逐位比较
        memset(f, -1, sizeof(f));  // 换了一个上界，记忆化数组必须清空
        return dfs(0, 0, true);  // 从最高位、还没有偶数数字、贴上界开始统计
    }  // calc 结束

public:  // 对外接口
    long long countEvenlyGoodIntegers(long long l, long long r) {  // l、r 为闭区间端点；返回 [l, r] 中偶好数的个数
        return calc(r) - calc(l - 1);  // 区间答案 = 前缀 [0, r] 减去前缀 [0, l-1]
    }  // 方法结束
};  // 类定义结束