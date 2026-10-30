# 题目：1374. 生成每种字符都是奇数个的字符串（Generate a String With Characters That Have Odd Counts）
# 思路：n 为奇数时返回 n 个 'a'；n 为偶数时返回 n-1 个 'a' 加 1 个 'b'，两种字符的个数都是奇数。
# 时间复杂度：O(n)，要生成长度为 n 的字符串；空间复杂度：O(n)，返回值占 n 个字符。
class Solution:  # LeetCode 约定的题解类
    def generateTheString(self, n: int) -> str:  # n 为字符串长度，返回每种字符出现次数都为奇数的字符串
        return 'a' * n if n & 1 else 'a' * (n - 1) + 'b'  # 奇数直接返回 n 个 'a'；偶数用 n-1 个 'a' 加 1 个 'b'，两者都是奇数个
