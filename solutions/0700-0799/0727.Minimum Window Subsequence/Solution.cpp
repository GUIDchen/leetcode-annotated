// 题目：727. 最小窗口子序列（Minimum Window Subsequence）
// 思路：f[i][j] 表示 s1 前 i 个字符中、以第 i 个字符结尾且覆盖 s2 前 j 个字符的最短窗口起点；按行递推后枚举右端点取最短窗口。
// 时间复杂度：O(m·n)，双重枚举两串长度；空间复杂度：O(m·n)，DP 表大小为 (m+1)×(n+1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string minWindow(string s1, string s2) {  // s1 是主串，s2 是需要被完整包含的子序列
        int m = s1.size(), n = s2.size();  // m、n 分别是两串长度，作为 DP 的边界
        int f[m + 1][n + 1];  // f[i][j]：s1 前缀 i 中覆盖 s2 前缀 j 的最短窗口起点（1-based），此处用 GCC 变长数组
        memset(f, 0, sizeof(f));  // 全部清零，0 表示该状态还无法匹配
        for (int i = 1; i <= m; ++i) {  // i 枚举 s1 的前缀长度（1-based，方便用 i-1 取字符）
            for (int j = 1; j <= n; ++j) {  // j 枚举 s2 的前缀长度
                if (s1[i - 1] == s2[j - 1]) {  // 两串当前字符相同，可以尝试用 s1[i-1] 匹配 s2[j-1]
                    f[i][j] = j == 1 ? i : f[i - 1][j - 1];  // j==1 时窗口就是第 i 个字符本身，否则继承 f[i-1][j-1] 记录的起点
                } else {  // 字符不同，s1[i-1] 无法参与匹配
                    f[i][j] = f[i - 1][j];  // 直接继承上一行同列的答案
                }  // if 分支结束
            }  // 内层 j 循环结束
        }  // 外层 i 循环结束
        int p = 0, k = m + 1;  // p 记录最优窗口左端点（0-based），k 记录最短长度，m+1 表示尚未找到
        for (int i = 1; i <= m; ++i) {  // 枚举窗口的右端点 i
            if (s1[i - 1] == s2[n - 1] && f[i][n]) {  // 右端点必须是 s2 的末字符，且 f[i][n] 非 0 才说明 s2 已完整出现
                int j = f[i][n] - 1;  // f 存的是 1-based 起点，减 1 转成字符串下标
                if (i - j < k) {  // 找到更短的窗口就更新答案
                    k = i - j;  // 更新最短长度
                    p = j;  // 更新对应的左端点
                }  // if (i - j < k) 结束
            }  // 外层 if 结束
        }  // for 循环结束
        return k > m ? "" : s1.substr(p, k);  // k > m 说明没找到，返回空串；否则从 p 开始截取长度为 k 的子串
    }  // minWindow 方法结束
};  // Solution 类定义结束