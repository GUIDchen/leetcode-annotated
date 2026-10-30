# 题目：2264. 字符串中最大的 3 位相同数字（Largest 3-Same-Digit Number in String）
# 思路：从 9 递减到 0，用海象运算符构造三位重复数字组成的字符串，判断它是否为 num 的子串，首次命中即为最大答案。
# 时间复杂度：O(10 * n) = O(n)，n 为字符串长度；空间复杂度：O(1)，只用了一个长度 3 的临时字符串。
class Solution:  # LeetCode 约定的题解类
    def largestGoodInteger(self, num: str) -> str:  # num：由数字字符组成的字符串
        for i in range(9, -1, -1):  # 从 9 递减到 0，先枚举较大的数字
            if (s := str(i) * 3) in num:  # 海象运算符：先构造三位相同的串 s，再判断它是否是 num 的子串
                return s  # 首次命中即为最大答案，直接返回
        return ""  # 不存在三位相同数字，返回空串
