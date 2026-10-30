// 题目：1062. 最长重复子串的长度（Longest Repeating Substring）
// 思路：动态规划，f[i][j] 表示分别以 s[i]、s[j] 结尾的两个子串的最长公共后缀长度，全程取最大值。
// 时间复杂度：O(n^2)，双重循环枚举下标对；空间复杂度：O(n^2)，二维 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestRepeatingSubstring(string s) {  // s：原串；返回最长的、至少出现两次的连续子串长度
        int n = s.length();  // 串长，同时作为所有循环与表格的上界
        vector<vector<int>> f(n, vector<int>(n));  // f[i][j]：以 s[i] 与 s[j] 结尾的两个子串的最长公共后缀长度
        int ans = 0;  // 记录出现过的最大公共后缀长度，即最终答案
        for (int i = 1; i < n; ++i) {  // 枚举较靠后的结束位置 i，从 1 起保证 j 总能取到更小的下标
            for (int j = 0; j < i; ++j) {  // 枚举较靠前的结束位置 j，只取 j < i，避免同一对下标被算两次
                if (s[i] == s[j]) {  // 末字符相同，公共后缀才有可能再延长一位
                    f[i][j] = 1 + (j > 0 ? f[i - 1][j - 1] : 0);  // 各自前移一位复用已算结果；j 为 0 时没有前驱，公共后缀只含当前这 1 个字符
                    ans = max(ans, f[i][j]);  // 用当前公共后缀长度更新全局最大值
                }  // end if：末字符不同则长度保持 0，无需处理
            }  // end for j：本起点 i 的所有可能前驱枚举完毕
        }  // end for i：所有下标对枚举完毕
        return ans;  // 返回最长重复子串的长度；完全不存在重复时返回 0
    }  // end method
};  // end class
