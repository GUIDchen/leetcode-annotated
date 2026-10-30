# 题目：2697. 字典序最小回文串（Lexicographically Smallest Palindrome）
# 核心思路：双指针从两端向中间夹逼，把每对对称位置都改成两者中字典序更小的字符，既保证回文又让字典序最小。
# 时间复杂度：O(n)，只走一半长度；空间复杂度：O(n)，因为 Python 的 str 不可变，需要另建字符列表。
class Solution:  # LeetCode 约定的题解类
    def makeSmallestPalindrome(self, s: str) -> str:  # s：待改造的字符串；返回字典序最小的回文串
        cs = list(s)  # 字符串不可变，先转成列表才能按下标就地改字符
        i, j = 0, len(s) - 1  # 双指针：i 指向左端，j 指向右端
        while i < j:  # 两端向中间靠拢，i < j 保证每对对称位置只处理一次
            cs[i] = cs[j] = min(cs[i], cs[j])  # 对称的两个位置统一取字典序更小的字符，回文与最小字典序同时满足
            i, j = i + 1, j - 1  # 两个指针同时向内收缩一格
        return "".join(cs)  # 字符列表拼回字符串返回
