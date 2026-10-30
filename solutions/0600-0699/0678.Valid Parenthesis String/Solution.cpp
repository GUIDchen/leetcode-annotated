// 题目：678. 有效的括号字符串（Valid Parenthesis String）
// 思路：区间动态规划，dp[i][j] 表示 s[i..j] 能否构成合法括号串；要么首尾是一对括号且中间合法，要么在某个位置拆成两段合法串。
// 时间复杂度：O(n^3)，两层区间枚举加一层断点枚举；空间复杂度：O(n^2)，二维布尔表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkValidString(string s) {  // s：只含 '('、')'、'*' 的字符串，'*' 可当左括号、右括号或空串
        int n = s.size();  // 字符串长度
        vector<vector<bool>> dp(n, vector<bool>(n));  // dp[i][j]：子串 s[i..j] 是否为合法括号串
        for (int i = 0; i < n; ++i) {  // 长度为 1 的区间
            dp[i][i] = s[i] == '*';  // 单个字符只有 '*' 可以解释成空串，才算合法
        }
        for (int i = n - 2; i >= 0; --i) {  // 区间左端从后往前枚举
            for (int j = i + 1; j < n; ++j) {  // 区间右端从左端右侧开始，保证子区间已经算好
                char a = s[i], b = s[j];  // 区间首尾两个字符
                dp[i][j] = (a == '(' || a == '*') && (b == '*' || b == ')') && (i + 1 == j || dp[i + 1][j - 1]);  // 情形一：首尾配成一对，中间子串合法
                for (int k = i; k < j && !dp[i][j]; ++k) {  // 情形二：在 k 处断开成两个合法子串，已成立就不再试
                    dp[i][j] = dp[i][k] && dp[k + 1][j];  // 左右两半都合法则整体合法
                }
            }
        }
        return dp[0][n - 1];  // 整个字符串是否合法
    }
};