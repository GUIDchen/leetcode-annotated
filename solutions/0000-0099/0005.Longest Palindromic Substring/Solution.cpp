// 题目：5. 最长回文子串（Longest Palindromic Substring）
// 思路：区间 DP，f[i][j] 表示 s[i..j] 是否回文；i 倒序、j 正序枚举，保证内部区间 f[i+1][j-1] 先于外层求出。
// 时间复杂度：O(n^2)，枚举全部区间；空间复杂度：O(n^2)，二维布尔表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string longestPalindrome(string s) {  // s 为输入字符串，返回最长回文子串
        int n = s.size();  // 字符串长度
        vector<vector<bool>> f(n, vector<bool>(n, true));  // 二维 DP 表初始化为全 true；f[i][j] 表示 s[i..j] 是否回文
        int k = 0, mx = 1;  // k 为最长回文子串起点，mx 为最长长度（单字符至少为 1）
        for (int i = n - 2; ~i; --i) {  // i 倒序枚举（~i 即 i != -1），保证 f[i+1][j-1] 已经计算
            for (int j = i + 1; j < n; ++j) {  // 右端点从 i+1 开始，只处理长度 >= 2 的区间
                f[i][j] = false;  // 先默认该区间不是回文
                if (s[i] == s[j]) {  // 首尾字符相等才有可能是回文
                    f[i][j] = f[i + 1][j - 1];  // 回文性由内部子区间决定
                    if (f[i][j] && mx < j - i + 1) {  // 是回文且长度更长
                        mx = j - i + 1;  // 更新最长长度
                        k = i;  // 更新最长子串的起点
                    }
                }
            }
        }
        return s.substr(k, mx);  // 从 k 开始截取 mx 个字符作为答案
    }
};