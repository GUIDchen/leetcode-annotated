// 题目：1977. 划分数字的方案数（Number of Ways to Separate Numbers）
// 思路：先预处理 lcp 让两段数能 O(1) 比较大小，再用 dp[i][j]（前缀和形式）表示前缀 i 最后一段长度不超过 j 的方案数。
// 时间复杂度：O(n^2)；空间复杂度：O(n^2)，lcp 与 dp 两张表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfCombinations(string num) {  // num：只含数字的字符串，返回把它切成若干段非递减数字的方案数
        const int mod = 1e9 + 7;  // 方案数要取模的模数
        int n = num.size();  // 字符串长度
        vector<vector<int>> lcp(n + 1, vector<int>(n + 1));  // lcp[i][j]：后缀 num[i..] 与 num[j..] 的最长公共前缀长度，用来快速比较两段数
        for (int i = n - 1; i >= 0; --i) {  // i 从后往前推，保证 i+1 行的值已经算好
            for (int j = n - 1; j >= 0; --j) {  // j 同样从后往前推
                if (num[i] == num[j]) {  // 首字符相同才能继续比后面的字符
                    lcp[i][j] = 1 + lcp[i + 1][j + 1];  // 公共前缀长度等于右移一位的结果再加 1
                }  // 首字符不同则 lcp 保持 0
            }  // j 循环结束
        }  // i 循环结束
        auto cmp = [&](int i, int j, int k) {  // cmp：判断从 i 开始与从 j 开始、长度都为 k 的两段数，前者是否 >= 后者
            int x = lcp[i][j];  // 先取出两段数的公共前缀长度
            return x >= k || num[i + x] >= num[j + x];  // 前 k 位全相同则两数相等；否则比较第一个不同的字符就够了
        };  // lambda 结束
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));  // dp[i][j]：把前缀 num[0..i) 切完、且最后一段长度不超过 j 的方案数（前缀和形式）
        dp[0][0] = 1;  // 空前缀、最后一段长度为 0，作为基础方案数 1
        for (int i = 1; i <= n; ++i) {  // 枚举前缀长度 i
            for (int j = 1; j <= i; ++j) {  // 枚举最后一段的长度 j
                int v = 0;  // v：当上一段长度也恰好为 j 时新增的方案数
                if (num[i - j] != '0') {  // 最后一段不能有前导零，首字符非 '0' 才合法
                    if (i - j - j >= 0 && cmp(i - j, i - j - j, j)) {  // 上一段也能取长度 j，且它的数值不大于当前段，说明可以直接接在后面
                        v = dp[i - j][j];  // 这些方案全部合法
                    } else {  // 否则上一段长度必须严格小于 j
                        v = dp[i - j][min(j - 1, i - j)];  // 用 dp 的前缀和形式一次取到「长度不超过 min(j-1, i-j)」的全部方案
                    }  // 分支结束
                }  // 前导零分支结束
                dp[i][j] = (dp[i][j - 1] + v) % mod;  // 前缀和递推：不超过 j 的方案 = 不超过 j-1 的方案 + 恰好为 j 的方案
            }  // j 循环结束
        }  // i 循环结束
        return dp[n][n];  // 整个串切完、最后一段长度不超过 n 的方案总数
    }  // 方法结束
};  // 类定义结束
