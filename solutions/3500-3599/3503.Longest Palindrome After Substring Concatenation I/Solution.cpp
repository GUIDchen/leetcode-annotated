// 题目：3503. 子字符串连接后的最长回文串 I（Longest Palindrome After Substring Concatenation I）
// 思路：先中心扩展求出 s、t 各自每个起点的最长回文长度；再把 t 反转，用 f[i][j] 求 s 前缀与反转 t 前缀的匹配长度，匹配段左右对称成回文，两侧各可再接一段原串中的回文。
// 时间复杂度：O(n² + m·n)；空间复杂度：O(m·n)，主要开销是二维 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestPalindrome(string s, string t) {  // s、t：两个待拼接的字符串，返回拼接后可能的最长回文长度
        int m = s.size(), n = t.size();  // 记录两个串的长度
        ranges::reverse(t);  // 反转 t：此后 s 的某段与 t 的某段相等，正好对应原题意里 s 与 t 首尾对称的一段
        vector<int> g1 = calc(s), g2 = calc(t);  // g1[i]/g2[j]：以 i/j 为起点、向右延伸的最长回文长度
        int ans = max(ranges::max(g1), ranges::max(g2));  // 答案至少可以完全取自 s，或完全取自 t
        vector<vector<int>> f(m + 1, vector<int>(n + 1));  // f[i][j]：s 前 i 个字符与 t 前 j 个字符的匹配长度
        for (int i = 1; i <= m; ++i) {  // 枚举 s 的前缀长度 i
            for (int j = 1; j <= n; ++j) {  // 枚举 t 的前缀长度 j
                if (s[i - 1] == t[j - 1]) {  // 末尾字符相同，才可能继续向外匹配
                    f[i][j] = f[i - 1][j - 1] + 1;  // 匹配长度在去掉末尾字符的方案上加一
                    ans = max(ans, f[i][j] * 2 + (i < m ? g1[i] : 0));  // 匹配段左右对称共 2f 个字符，再接上 s 里从 i 开始的一段回文
                    ans = max(ans, f[i][j] * 2 + (j < n ? g2[j] : 0));  // 或者接上 t 里从 j 开始的一段回文
                }  // 字符相同分支结束
            }  // 枚举 j 结束
        }  // 枚举 i 结束
        return ans;  // 返回最长回文的长度
    }  // 主方法结束

private:  // 以下为内部辅助函数
    void expand(const string& s, vector<int>& g, int l, int r) {  // 从中心 (l, r) 向两侧扩展，更新以 l 为起点的最长回文长度
        while (l >= 0 && r < s.size() && s[l] == s[r]) {  // 两侧字符相等就继续向外扩
            g[l] = max(g[l], r - l + 1);  // 当前回文的起点是 l，长度为 r - l + 1
            --l;  // 左端点左移一位
            ++r;  // 右端点右移一位
        }  // 本次扩展结束
    }  // expand 结束

    vector<int> calc(const string& s) {  // 预处理：算出字符串中每个起点的最长回文长度
        int n = s.size();  // 当前串长度
        vector<int> g(n, 0);  // 结果数组，先全部置 0
        for (int i = 0; i < n; ++i) {  // 枚举每个可能的回文中心
            expand(s, g, i, i);  // 奇数长度回文，中心是单个字符
            expand(s, g, i, i + 1);  // 偶数长度回文，中心在两个字符之间
        }  // 中心枚举结束
        return g;  // 返回每个起点的最长回文长度
    }  // calc 结束
};  // 类定义结束
