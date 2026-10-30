# 3794. 反转字符串前缀 / Reverse String Prefix
# 核心思路：切片取前 k 个字符并逆序，再与第 k 位之后的后缀拼接。
# 复杂度：时间 O(n)，空间 O(n)。
class Solution:  # 定义 LeetCode 题解类
    def reversePrefix(self, s: str, k: int) -> str:  # 返回前 k 个字符反转后的字符串
        return s[:k][::-1] + s[k:]  # 前缀逆序后与后缀拼接
