// 题目：583. 两个字符串的删除操作（Delete Operation for Two Strings）
// 核心思路：转化为最长公共子序列问题；f[i][j] 表示让 word1 前 i 个字符与 word2 前 j 个字符相同所需的最少删除次数。
// 时间复杂度：O(m * n)，双重循环填表；空间复杂度：O(m * n)，二维 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minDistance(string word1, string word2) {  // word1、word2 为待处理的两个字符串
        int m = word1.length(), n = word2.length();  // 两个字符串的长度
        vector<vector<int>> f(m + 1, vector<int>(n + 1));  // DP 表：f[i][j] 表示前缀 word1[0..i) 与 word2[0..j) 的答案
        for (int i = 0; i <= m; ++i) {  // 初始化第一列：word2 取空前缀
            f[i][0] = i;  // 只能删掉 word1 的全部 i 个字符
        }  // 第一列初始化结束
        for (int j = 0; j <= n; ++j) {  // 初始化第一行：word1 取空前缀
            f[0][j] = j;  // 只能删掉 word2 的全部 j 个字符
        }  // 第一行初始化结束
        for (int i = 1; i <= m; ++i) {  // 从长度 1 开始填表
            for (int j = 1; j <= n; ++j) {  // 逐列填第 i 行
                char a = word1[i - 1];  // 当前考察的 word1 字符（下标从 0 开始）
                char b = word2[j - 1];  // 当前考察的 word2 字符
                if (a == b) {  // 两个字符相等，可以直接匹配，不需要额外删除
                    f[i][j] = f[i - 1][j - 1];  // 继承去掉这两个字符后的答案
                } else {  // 字符不同，必须至少删掉其中一个
                    f[i][j] = min(f[i - 1][j], f[i][j - 1]) + 1;  // 删 word1 末尾或删 word2 末尾，取较优者再加这一步
                }  // 字符比较分支结束
            }  // 内层循环结束
        }  // 外层循环结束
        return f[m][n];  // 答案：两个完整字符串的最少删除次数
    }  // minDistance 结束
};  // 类定义结束
