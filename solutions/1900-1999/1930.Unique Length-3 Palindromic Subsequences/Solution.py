# 题目：1930. 长度为 3 的不同回文子序列（Unique Length-3 Palindromic Subsequences）
# 思路：枚举 26 个小写字母作为回文两端，切片取两端之间的子串，其不同字符数就是新增个数。
# 时间复杂度：O(26·n) 即 O(n)；空间复杂度：O(1)，切片与集合最多 26 个元素。
class Solution:  # LeetCode 约定的题解类
    def countPalindromicSubsequence(self, s: str) -> int:  # 返回长度为 3 的不同回文子序列个数
        ans = 0  # 答案计数器
        for c in ascii_lowercase:  # 枚举回文子序列首尾两端使用的字符
            l, r = s.find(c), s.rfind(c)  # l / r 分别是字符 c 第一次与最后一次出现的位置
            if r - l > 1:  # 两端之间还有位置时才可能存在中间字符
                ans += len(set(s[l + 1 : r]))  # 中间子串里不同字符的个数，就是两端固定为 c 时新增的回文子序列数
        return ans  # 返回不同回文子序列的总数
