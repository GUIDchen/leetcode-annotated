// 题目：712. 两个字符串的最小ASCII删除和（Minimum ASCII Delete Sum for Two Strings）
// 核心思路：二维区间 DP。f[i][j] 表示让 s1 的前 i 个字符与 s2 的前 j 个字符相等的最小删除代价，字符相同就继承左上角，否则删掉其中一个字符并累加其 ASCII 值。
// 时间复杂度：O(m·n)，状态表每个位置算一次；空间复杂度：O(m·n)，需要保存整张 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 对外可见的接口区
    int minimumDeleteSum(string s1, string s2) {  // s1、s2 是输入字符串，返回使两者相等所需删除字符的最小 ASCII 值之和
        int m = s1.size(), n = s2.size();  // 取两个字符串的长度，用于建立 DP 表
        int f[m + 1][n + 1];  // f[i][j]：让 s1 前 i 个字符与 s2 前 j 个字符相等的最小删除代价
        memset(f, 0, sizeof f);  // 先把整张表清零，第 0 行与第 0 列稍后单独填边界值
        for (int i = 1; i <= m; ++i) {  // 预处理第 0 列：s2 为空时只能把 s1 全部删掉
            f[i][0] = f[i - 1][0] + s1[i - 1];  // 删掉 s1 的第 i 个字符，代价累加它的 ASCII 值
        }  // 结束第 0 列的初始化
        for (int j = 1; j <= n; ++j) {  // 预处理第 0 行：s1 为空时只能把 s2 全部删掉
            f[0][j] = f[0][j - 1] + s2[j - 1];  // 删掉 s2 的第 j 个字符，代价累加它的 ASCII 值
        }  // 结束第 0 行的初始化
        for (int i = 1; i <= m; ++i) {  // 按 s1 的长度逐层递推
            for (int j = 1; j <= n; ++j) {  // 按 s2 的长度逐列递推
                if (s1[i - 1] == s2[j - 1]) {  // 当前两个字符相同，可以免费匹配
                    f[i][j] = f[i - 1][j - 1];  // 不用删除，直接继承去掉这两个字符后的最优解
                } else {  // 字符不同，说明至少有一个要被删掉
                    f[i][j] = min(f[i - 1][j] + s1[i - 1], f[i][j - 1] + s2[j - 1]);  // 取「删 s1 当前字符」与「删 s2 当前字符」两种方案的较小代价
                }  // 结束 else 分支
            }  // 结束内层列循环
        }  // 结束外层行循环
        return f[m][n];  // 两个字符串都处理完毕，f[m][n] 就是最终答案
    }  // 结束 minimumDeleteSum 方法
};  // 结束 Solution 类定义