# 题目：2710. 移除字符串中的尾随零（Remove Trailing Zeros From a String）
# 思路：用 rstrip("0") 从右端一次性删掉所有 '0' 字符。
# 时间复杂度：O(n)，只扫描尾部；空间复杂度：O(n)，返回的是新字符串。
class Solution:  # LeetCode 约定的题解类
    def removeTrailingZeros(self, num: str) -> str:  # num 是只含数字字符的字符串
        return num.rstrip("0")  # rstrip 会把右侧所有 '0' 字符一次性去掉
