// 题目：72. 编辑距离（Edit Distance）
// 思路：二维 DP，f[i][j] 表示把 word1 前 i 个字符变成 word2 前 j 个字符的最少操作数；末字符相同则继承 f[i-1][j-1]，否则在删除/插入/替换三者中取最小再加 1。
// 时间复杂度：O(m·n)，两重循环填满整张表；空间复杂度：O(m·n)，需要 (m+1)×(n+1) 的状态表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minDistance(string word1, string word2) {  // word1 为源串，word2 为目标串
        int m = word1.size(), n = word2.size();  // 分别记录两个串的长度，即 DP 表的两个维度
        int f[m + 1][n + 1];  // f[i][j]：word1 前 i 个字符编辑成 word2 前 j 个字符的最少步数
        for (int j = 0; j <= n; ++j) {  // 处理第一行：源串为空时
            f[0][j] = j;  // 只能不断插入，需要 j 次操作
        }
        for (int i = 1; i <= m; ++i) {  // 逐行推进源串的前缀长度
            f[i][0] = i;  // 第一列：目标串为空，只能把源串字符全删掉，需要 i 次
            for (int j = 1; j <= n; ++j) {  // 逐个计算这一行的每一列
                if (word1[i - 1] == word2[j - 1]) {  // 两个前缀的末字符相同（下标从 0 起所以要减 1）
                    f[i][j] = f[i - 1][j - 1];  // 这一位天然匹配，不需要额外操作，直接继承左上角状态
                } else {
                    f[i][j] = min({f[i - 1][j], f[i][j - 1], f[i - 1][j - 1]}) + 1;  // 分别对应删除、插入、替换，取最小后再加本次这一刀
                }
            }
        }
        return f[m][n];  // 右下角就是整串 word1 变成整串 word2 的最少操作数
    }
};