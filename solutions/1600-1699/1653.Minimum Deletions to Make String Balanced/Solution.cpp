// 题目：1653. 使字符串平衡的最少删除次数（Minimum Deletions to Make String Balanced）
// 思路：动态规划：f[i] 表示让前 i 个字符平衡的最少删除数；遇到 b 直接继承且计数，遇到 a 则取「删掉这个 a」与「删掉前面所有 b」的较小值。
// 时间复杂度：O(n)；空间复杂度：O(n)，一维 DP 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumDeletions(string s) {  // s 只含 a、b，返回使其变成若干 b 后接若干 a 的最少删除数
        int n = s.size();  // 字符串长度
        int f[n + 1];  // f[i]：前 i 个字符平衡的最少删除次数（变长数组，C++ 扩展特性）
        memset(f, 0, sizeof(f));  // 全部初始化为 0
        int b = 0;  // b：已扫描前缀中 b 的个数
        for (int i = 1; i <= n; ++i) {  // 从第 1 个字符递推到第 n 个
            if (s[i - 1] == 'b') {  // 当前字符是 b：它排在所有 a 之前天然合法
                f[i] = f[i - 1];  // 状态直接继承，不需要删除
                ++b;  // b 的计数加一
            } else {  // 否则当前字符是 a
                f[i] = min(f[i - 1] + 1, b);  // 两种选择取较小：删掉这个 a（f[i-1]+1），或删掉前面所有 b（b）
            }  // 分支结束
        }  // 递推结束
        return f[n];  // 整串的答案
    }  // 方法结束
};  // Solution 类定义结束