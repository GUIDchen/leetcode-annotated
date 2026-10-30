// 题目：1682. 最长回文子序列 II（Longest Palindromic Subsequence II）
// 思路：区间记忆化搜索。dfs(i, j, x) 表示在 s[i..j] 中、外层已选字符 x 时能取到的最长「相邻字符不同」回文子序列长度；两端字符相同时才能同时取用，否则分别丢掉一端取较大值。
// 时间复杂度：O(n^2 · 26) 个状态，每个状态常数次转移；空间复杂度：O(n^2 · 26) 的记忆化数组 f。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int f[251][251][27];  // f[i][j][x]：区间 [i, j] 在外层字符为 x 时的答案，初始化为 -1 表示未计算

    int longestPalindromeSubseq(string s) {  // 求满足「相邻字符两两不同」的最长回文子序列长度
        int n = s.size();  // n 是字符串长度
        memset(f, -1, sizeof f);  // 全部置为 -1，作为「该状态还没算过」的标记
        function<int(int, int, int)> dfs = [&](int i, int j, int x) -> int {  // 定义递归函数：区间 [i, j]，外层已经用掉的字符编号为 x（26 表示还没用字符）
            if (i >= j) return 0;  // 区间长度不足 2，无法再构成回文对，返回 0
            if (f[i][j][x] != -1) return f[i][j][x];  // 该状态算过就直接返回缓存值，避免重复搜索
            int ans = 0;  // ans 暂存当前区间的答案
            if (s[i] == s[j] && s[i] - 'a' != x)  // 两端字符相同，且与外层字符不同，才能把它们同时纳入回文
                ans = dfs(i + 1, j - 1, s[i] - 'a') + 2;  // 两端各取一个，长度加 2，并把该字符作为新的外层字符继续向里搜
            else  // 两端字符不同，只能舍去其中一端
                ans = max(dfs(i + 1, j, x), dfs(i, j - 1, x));  // 分别尝试丢掉左端与丢掉右端，取较优者
            f[i][j][x] = ans;  // 写入记忆化数组，供后续状态复用
            return ans;  // 返回当前区间的答案
        };
        return dfs(0, n - 1, 26);  // 从整个串开始搜，26 表示外层还没有字符
    }
};  // 题解类结束