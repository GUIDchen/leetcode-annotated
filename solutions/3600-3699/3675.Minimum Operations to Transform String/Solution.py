# 3675. Minimum Operations to Transform String（转换字符串的最小操作次数）
# 核心思路：非 'a' 字符变成 'a' 需要 26 - (ord(c) - 97) 次操作，答案取最大值，没有非 'a' 字符时为 0。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # 定义 Solution 类
    def minOperations(self, s: str) -> int:  # 求把字符串所有字符变成 'a' 的最小操作次数
        return max((26 - (ord(c) - 97) for c in s if c != "a"), default=0)  # 取所有非 'a' 字符所需操作次数的最大值，没有时默认 0
