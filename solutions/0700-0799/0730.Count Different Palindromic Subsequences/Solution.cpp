// 题目：730. 统计不同回文子序列（Count Different Palindromic Subsequences）
// 思路：区间 DP，dp[i][j][c] 表示 s[i..j] 内以字符 c 为首尾的不同回文子序列个数，按区间长度从小到大转移，最后把四种首字符的结果求和。
// 时间复杂度：O(n²·4)，区间数 n² 乘以 4 种字母；空间复杂度：O(n²·4)，即三维 DP 表。
using ll = long long;  // 给长整型起别名，累加时避免 int 溢出

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countPalindromicSubsequences(string s) {  // s 只由 'a'~'d' 组成，因此可以按这 4 种字符分类统计
        int mod = 1e9 + 7;  // 取模基数 1e9+7，防止计数溢出
        int n = s.size();  // n 为字符串长度
        vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(n, vector<ll>(4)));  // 三维 DP：dp[i][j][k] 表示区间 [i, j] 内以第 k 种字母（a~d）为首尾的回文子序列数
        for (int i = 0; i < n; ++i) dp[i][i][s[i] - 'a'] = 1;  // 长度为 1 的区间只有一个单字符回文子序列
        for (int l = 2; l <= n; ++l) {  // l 枚举区间长度，从 2 开始（长度 1 已初始化）
            for (int i = 0; i + l <= n; ++i) {  // i 是区间左端点，由长度 l 推出右端点 j，保证 j < n
                int j = i + l - 1;  // j 是区间右端点
                for (char c = 'a'; c <= 'd'; ++c) {  // c 枚举首尾字符 a~d
                    int k = c - 'a';  // k 是该字符对应的 DP 下标
                    if (s[i] == c && s[j] == c)  // 两端字符都等于 c：可以用它们各夹一层
                        dp[i][j][k] = 2 + accumulate(dp[i + 1][j - 1].begin(), dp[i + 1][j - 1].end(), 0ll) % mod;  // 长度至少 2 的夹层各新增一个（"cc" 及再套一层），再加上内部区间的全部回文子序列（先取模防止累加溢出）
                    else if (s[i] == c)  // 只有左端是 c，右端得从区间里去掉
                        dp[i][j][k] = dp[i][j - 1][k];  // 等价于区间 [i, j-1] 的计数
                    else if (s[j] == c)  // 只有右端是 c，左端得从区间里去掉
                        dp[i][j][k] = dp[i + 1][j][k];  // 等价于区间 [i+1, j] 的计数
                    else  // 两端都不是 c，直接收缩到内部区间
                        dp[i][j][k] = dp[i + 1][j - 1][k];  // 沿用 [i+1, j-1] 的计数
                }  // c 循环结束
            }  // i 循环结束
        }  // 长度 l 循环结束
        ll ans = accumulate(dp[0][n - 1].begin(), dp[0][n - 1].end(), 0ll);  // 整串内四种首字符的回文子序列总数
        return (int) (ans % mod);  // 取模后转回 int 返回
    }  // countPalindromicSubsequences 方法结束
};  // Solution 类定义结束