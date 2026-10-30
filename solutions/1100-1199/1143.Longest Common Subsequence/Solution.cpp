// 题目：1143. 最长公共子序列（Longest Common Subsequence）
// 思路：二维 DP：f[i][j] 表示 text1 前 i 个字符与 text2 前 j 个字符的 LCS 长度，末位相同则继承左上角加 1，否则取上、左的较大值。
// 时间复杂度：O(m*n)；空间复杂度：O(m*n)，二维 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestCommonSubsequence(string text1, string text2) {  // text1、text2 是两个字符串，返回最长公共子序列的长度
        int m = text1.size(), n = text2.size();  // 两个字符串的长度
        int f[m + 1][n + 1];  // f[i][j]：text1 前 i 个字符与 text2 前 j 个字符的最长公共子序列长度（变长数组）
        memset(f, 0, sizeof f);  // 清零，第 0 行与第 0 列天然是 0（空串与任何串的 LCS 为 0）
        for (int i = 1; i <= m; ++i) {  // 枚举 text1 的前缀长度 1..m
            for (int j = 1; j <= n; ++j) {  // 枚举 text2 的前缀长度 1..n
                if (text1[i - 1] == text2[j - 1]) {  // 两个前缀的末位字符相同（下标要减 1）
                    f[i][j] = f[i - 1][j - 1] + 1;  // 这个字符一定能进公共子序列，继承各自去掉末位后的最优值再加 1
                } else {  // 末位不同
                    f[i][j] = max(f[i - 1][j], f[i][j - 1]);  // 至少有一个末位字符不在 LCS 里，取「丢掉 text1 末位」和「丢掉 text2 末位」的较大值
                }  // 分支结束
            }  // j 循环结束
        }  // i 循环结束
        return f[m][n];  // f[m][n] 即两个完整串的 LCS 长度
    }  // 方法结束
};  // 类定义结束