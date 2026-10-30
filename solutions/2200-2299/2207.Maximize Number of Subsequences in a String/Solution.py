# 题目：2207. 字符串中最多数目的子序列（Maximize Number of Subsequences in a String）
# 核心思路：一次扫描累计原串已有的子序列数；最后插入的字符最多贡献 max(pattern[0] 的个数, pattern[1] 的个数)。
# 时间复杂度：O(n)，只扫描一遍；空间复杂度：O(1)，仅常数个计数器。
class Solution:  # LeetCode 约定的题解类
    def maximumSubsequenceCount(self, text: str, pattern: str) -> int:  # text 是原串，pattern 是长度为 2 的目标子序列
        ans = x = y = 0  # ans 记已有子序列数，x 记 pattern[0] 的个数，y 记 pattern[1] 的个数
        for c in text:  # 从左到右扫描每个字符
            if c == pattern[1]:  # 当前字符是目标子序列的第二个字符
                y += 1  # 第二个字符的计数加一
                ans += x  # 它与左侧出现的每个 pattern[0] 都能组成一个子序列
            if c == pattern[0]:  # 当前字符是目标子序列的第一个字符
                x += 1  # 第一个字符的计数加一；放在第二次判断里才能兼容 pattern 两字符相同的情况
        ans += max(x, y)  # 插入字符的贡献是另一侧同伴字符总数，两者取大
        return ans  # 返回最多能得到的子序列数目
