# 题目：1062. 最长重复子串的长度（Longest Repeating Substring）
# 思路：动态规划，f[i][j] 表示分别以 s[i]、s[j] 结尾的两个子串的最长公共后缀长度，全程取最大值。
# 时间复杂度：O(n^2)，双层循环枚举下标对；空间复杂度：O(n^2)，二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def longestRepeatingSubstring(self, s: str) -> int:  # s：原串；返回最长的、至少出现两次的连续子串长度
        n = len(s)  # 串长，作为循环与表格的上界
        f = [[0] * n for _ in range(n)]  # 二维 DP 表，f[i][j] 分别以 s[i]、s[j] 结尾的最长公共后缀长度
        ans = 0  # 记录出现过的最大公共后缀长度，即最终答案
        for i in range(1, n):  # 枚举较靠后的结束位置 i，从 1 起保证 j 能取到更小的下标
            for j in range(i):  # 枚举较靠前的结束位置 j，只取 j < i，避免重复计算
                if s[i] == s[j]:  # 末字符相同，公共后缀才可能再延长一位
                    f[i][j] = 1 + (f[i - 1][j - 1] if j else 0)  # 前移一位复用已算结果；j 为 0 时无前驱，公共后缀只含当前字符
                    ans = max(ans, f[i][j])  # 用当前公共后缀长度更新全局最大值
        return ans  # 返回最长重复子串的长度；不存在重复时返回 0
