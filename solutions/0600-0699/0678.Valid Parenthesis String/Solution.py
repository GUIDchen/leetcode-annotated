# 题目：678. 有效的括号字符串（Valid Parenthesis String）
# 思路：区间动态规划，dp[i][j] 表示 s[i..j] 能否构成合法括号串；要么首尾配成一对且中间合法，要么在某个位置拆成两段合法串。
# 时间复杂度：O(n^3)，两层区间枚举加一层断点枚举；空间复杂度：O(n^2)，二维布尔表。
class Solution:  # LeetCode 约定的题解类
    def checkValidString(self, s: str) -> bool:  # s：只含 '('、')'、'*'，'*' 可当左括号、右括号或空串
        n = len(s)  # 字符串长度
        dp = [[False] * n for _ in range(n)]  # dp[i][j]：子串 s[i..j] 是否为合法括号串
        for i, c in enumerate(s):  # 处理长度为 1 的区间
            dp[i][i] = c == '*'  # 单个字符只有 '*' 能解释成空串，才算合法
        for i in range(n - 2, -1, -1):  # 区间左端从后往前枚举
            for j in range(i + 1, n):  # 区间右端从左端右侧开始，保证用到的子区间已算好
                dp[i][j] = (  # 情形一：首尾配成一对，且中间子串合法
                    s[i] in '(*' and s[j] in '*)' and (i + 1 == j or dp[i + 1][j - 1])  # 首字符可当左括号、尾字符可当右括号、中间合法
                )
                dp[i][j] = dp[i][j] or any(  # 情形二：在某个 k 处拆成两段，左段和右段都合法
                    dp[i][k] and dp[k + 1][j] for k in range(i, j)  # 枚举所有断点位置
                )
        return dp[0][-1]  # 整个字符串是否合法
