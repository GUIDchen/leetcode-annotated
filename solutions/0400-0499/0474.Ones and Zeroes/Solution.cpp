// 题目：474. 一和零（Ones and Zeroes）
// 思路：把每个字符串看成占用 a 个 0、b 个 1 的物品，做三维 01 背包：f[i][j][k] 表示前 i 个串在容量 j 个 0、k 个 1 下的最大子集大小。
// 时间复杂度：O(L·m·n)，L 为字符串个数；空间复杂度：O(L·m·n)，使用三维 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findMaxForm(vector<string>& strs, int m, int n) {  // strs 是字符串数组，m 是最多可用的 0 的个数，n 是最多可用的 1 的个数
        int sz = strs.size();  // 字符串个数，即背包的物品数
        vector<vector<vector<int>>> f(sz + 1, vector<vector<int>>(m + 1, vector<int>(n + 1)));  // f[i][j][k]：考虑前 i 个串、用 j 个 0 和 k 个 1 时的最大子集大小
        for (int i = 1; i <= sz; ++i) {  // 逐个考虑第 i 个字符串（1 开始，便于用 i-1 表示前一行）
            auto [a, b] = count(strs[i - 1]);  // 统计当前字符串里 0 的个数 a 与 1 的个数 b
            for (int j = 0; j <= m; ++j) {  // 枚举 0 的容量
                for (int k = 0; k <= n; ++k) {  // 枚举 1 的容量
                    f[i][j][k] = f[i - 1][j][k];  // 不选当前字符串：沿用前 i-1 个的结果
                    if (j >= a && k >= b) {  // 容量够放下当前字符串时才考虑选它
                        f[i][j][k] = max(f[i][j][k], f[i - 1][j - a][k - b] + 1);  // 选它：容量回退 a、b，子集大小加 1
                    }
                }
            }
        }
        return f[sz][m][n];  // 前 sz 个串、容量 m 个 0 与 n 个 1 时的最大子集大小
    }

    pair<int, int> count(string& s) {  // 统计字符串中 0 与 1 的个数，返回 (0 的个数, 1 的个数)
        int a = count_if(s.begin(), s.end(), [](char c) { return c == '0'; });  // 统计字符 '0' 出现的次数
        return {a, s.size() - a};  // 总数减去 0 的个数就是 1 的个数
    }
};