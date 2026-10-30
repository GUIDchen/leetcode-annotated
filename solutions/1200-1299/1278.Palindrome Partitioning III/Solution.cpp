// 题目：1278. 分割回文串 III（Palindrome Partitioning III）
// 思路：先用区间 DP 预处理 g[i][j]（把 s[i..j] 变成回文串的最少改动字符数），再用划分 DP 求切成 k 段的最小总代价。
// 时间复杂度：O(n^3 + n^2·k)，区间预处理 O(n^2) 之外还要枚举切点；空间复杂度：O(n^2 + n·k)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int palindromePartition(string s, int k) {  // s 为原串，k 为要切成的段数，返回最少修改字符数
        int n = s.size();  // 字符串长度
        vector<vector<int>> g(n, vector<int>(n));  // g[i][j]：把子串 s[i..j] 变成回文串所需的最少字符修改数
        for (int i = n - 1; i >= 0; --i) {  // 左端点从右往左，保证依赖的更短区间已经算好
            for (int j = i; j < n; ++j) {  // 右端点从左端点开始向右扩展
                g[i][j] = s[i] != s[j] ? 1 : 0;  // 两端字符不同则至少需要改 1 个字符
                if (i + 1 < j) g[i][j] += g[i + 1][j - 1];  // 中间部分递归：剥掉两端后累加内层代价
            }
        }
        vector<vector<int>> f(n + 1, vector<int>(k + 1));  // f[i][j]：把前 i 个字符切成 j 段的最小修改数
        for (int i = 1; i <= n; ++i) {  // 枚举前缀长度 i
            for (int j = 1; j <= min(i, k); ++j) {  // 段数 j 不能超过前缀长度，也不能超过总段数 k
                if (j == 1) {  // 只切一段：整段前缀就是最后一段
                    f[i][j] = g[0][i - 1];  // 代价等于把 s[0..i-1] 变成回文串的代价
                } else {  // 切多段：枚举最后一段的起点 h
                    f[i][j] = 10000;  // 用一个足够大的数初始化最优值
                    for (int h = j - 1; h < i; ++h) {  // h 是最后一段的起点，前面至少要留出 j-1 个字符
                        f[i][j] = min(f[i][j], f[h][j - 1] + g[h][i - 1]);  // 前 h 个字符切 j-1 段，再加上最后一段的代价
                    }
                }
            }
        }
        return f[n][k];  // 前 n 个字符切成 k 段的最小修改次数即为答案
    }
};  // 题解类定义结束（本文件末尾无换行，已保留）