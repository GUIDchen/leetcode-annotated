// 3472. Longest Palindromic Subsequence After at Most K Operations / 3472. 至多 K 次操作后的最长回文子序列
// 核心思路：区间记忆化搜索，枚举丢弃左端、丢弃右端或两端配对三种转移，配对代价为字母的环形距离。
// 复杂度：时间 O(n^2 * k)，空间 O(n^2 * k)。

class Solution {  // LeetCode 题解统一使用 Solution 类
public:  // 公有接口
    int longestPalindromicSubsequence(string s, int k) {  // 返回至多 k 次字符循环操作后的最长回文子序列长度
        int n = s.size();  // 字符串长度
        vector f(n, vector(n, vector<int>(k + 1, -1)));  // 记忆化数组，f[i][j][k] 表示区间 [i, j] 还剩 k 次操作时的答案
        auto dfs = [&](this auto&& dfs, int i, int j, int k) -> int {  // 递归求区间 [i, j] 在剩余 k 次操作下的最长回文子序列长度
            if (i > j) {  // 区间为空
                return 0;  // 空区间长度为 0
            }  // 空区间分支结束
            if (i == j) {  // 区间只剩一个字符
                return 1;  // 单字符本身就是回文
            }  // 单字符分支结束
            if (f[i][j][k] != -1) {  // 该状态已经计算过
                return f[i][j][k];  // 直接返回记忆化结果
            }  // 记忆化命中分支结束
            int res = max(dfs(i + 1, j, k), dfs(i, j - 1, k));  // 丢弃左端或丢弃右端，取两者较大值
            int d = abs(s[i] - s[j]);  // 两字符在字母表上的直线距离
            int t = min(d, 26 - d);  // 环形字母表上的最小距离，即让两端字符相同所需的最少操作次数
            if (t <= k) {  // 剩余操作数足够让两端字符相同
                res = max(res, 2 + dfs(i + 1, j - 1, k - t));  // 两端配对成功，长度加 2 并扣掉本次代价
            }  // 配对分支结束
            return f[i][j][k] = res;  // 记忆化并返回区间答案
        };  // 递归函数定义结束
        return dfs(0, n - 1, k);  // 从整个字符串、k 次操作开始搜索
    }  // 方法结束
};  // 类定义结束
