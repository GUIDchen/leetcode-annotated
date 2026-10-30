// 题目：1092. 最短公共超序列（Shortest Common Supersequence）
// 思路：先求两串的最长公共子序列 DP 表 f，再从右下角回溯构造答案：公共字符只写一次并同时消耗两串，否则沿 f 较大的方向取走一个字符；回溯结果是逆序，最后整体反转。
// 时间复杂度：O(m·n)，填表与回溯各一遍；空间复杂度：O(m·n)，f 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string shortestCommonSupersequence(string str1, string str2) {  // 返回同时以 str1 与 str2 为子序列的最短字符串
        int m = str1.size(), n = str2.size();  // 两个串的长度
        vector<vector<int>> f(m + 1, vector<int>(n + 1));  // f[i][j] 是 str1 前 i 个字符与 str2 前 j 个字符的 LCS 长度，多一行一列作为空串边界
        for (int i = 1; i <= m; ++i) {  // 枚举 str1 的前缀长度
            for (int j = 1; j <= n; ++j) {  // 枚举 str2 的前缀长度
                if (str1[i - 1] == str2[j - 1])  // 两个前缀的末尾字符相同，可以并入 LCS
                    f[i][j] = f[i - 1][j - 1] + 1;  // 长度等于去掉这两个字符后的 LCS 再加一
                else  // 末尾字符不同
                    f[i][j] = max(f[i - 1][j], f[i][j - 1]);  // 取「丢掉 str1 末字符」与「丢掉 str2 末字符」中较大的 LCS
            }  // 结束列枚举
        }  // 结束行枚举
        int i = m, j = n;  // 从 DP 表右下角开始回溯
        string ans;  // 逆序收集答案字符
        while (i || j) {  // 还有字符没被消耗完
            if (i == 0)  // str1 已用完
                ans += str2[--j];  // 把 str2 剩余的字符逐个接到答案（先减下标再取字符）
            else if (j == 0)  // str2 已用完
                ans += str1[--i];  // 把 str1 剩余的字符逐个接到答案
            else {  // 两串都还有剩余字符
                if (f[i][j] == f[i - 1][j])  // 长度来自上方，说明 str1 的第 i 个字符不在 LCS 中
                    ans += str1[--i];  // 取走 str1 的这个字符并把下标左移
                else if (f[i][j] == f[i][j - 1])  // 长度来自左方，说明 str2 的第 j 个字符不在 LCS 中
                    ans += str2[--j];  // 取走 str2 的这个字符并把下标左移
                else  // 上下都不等，说明这个字符是 LCS 里的公共字符
                    ans += str1[--i], --j;  // 公共字符只写一次，逗号表达式里同时把两个下标都左移
            }  // 结束两串都非空的分支
        }  // 结束回溯循环
        reverse(ans.begin(), ans.end());  // 回溯得到的是逆序答案，需要整体反转
        return ans;  // 返回最短公共超序列
    }  // 结束方法体
};  // 类定义结束