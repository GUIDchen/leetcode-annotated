// 题目：115. 不同的子序列（Distinct Subsequences）
// 思路：二维 DP，f[i][j] 表示 s 的前 i 个字符中能选出 t 的前 j 个字符的方案数；不选 s[i-1] 时继承 f[i-1][j]，字符相等时再累加 f[i-1][j-1]。
// 时间复杂度：O(m * n)，双重循环遍历整张表；空间复杂度：O(m * n)，需要 m+1 行 n+1 列的 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numDistinct(string s, string t) {  // s 是原串，t 是目标串，返回 s 中不同子序列等于 t 的个数
        int m = s.size(), n = t.size();  // m、n 分别是两个串的长度，后面会反复用到
        unsigned long long f[m + 1][n + 1];  // f[i][j]：s 的前 i 个字符里能组成 t 的前 j 个字符的方案数；用无符号 64 位整数防止计数溢出
        memset(f, 0, sizeof(f));  // 先把整张表清零，后面按转移方程逐格覆盖
        for (int i = 0; i < m + 1; ++i) {  // 边界递推：t 为空串时任何 s 前缀都有 1 种方案（什么都不选）
            f[i][0] = 1;  // 所以第一列整体置 1
        }
        for (int i = 1; i < m + 1; ++i) {  // 按照 s 的前缀长度逐行递推
            for (int j = 1; j < n + 1; ++j) {  // 再按 t 的前缀长度逐列递推
                f[i][j] = f[i - 1][j];  // 不使用 s[i-1] 这一位的情况：方案数直接继承上一行
                if (s[i - 1] == t[j - 1]) {  // 字符相等时，还可以让 s[i-1] 去匹配 t[j-1]
                    f[i][j] += f[i - 1][j - 1];  // 累加「去掉这两个字符」的子问题方案数
                }
            }
        }
        return f[m][n];  // 用整个 s 拼出整个 t 的方案总数
    }
};  // 类定义结束