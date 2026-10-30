# 题目：1332. 删除回文子序列（Remove Palindromic Subsequences）
# 思路：只含 'a'、'b' 两种字符。整串回文则一次删完；否则先删全部 'a' 再删全部 'b'，两次必清空，答案只能是 1 或 2。
# 时间复杂度：O(n)，反转比较；空间复杂度：O(n)，切片产生副本。
class Solution:  # 题解类
    def removePalindromeSub(self, s: str) -> int:  # s：仅含 'a'、'b' 的字符串，返回最少删除次数
        return 1 if s[::-1] == s else 2  # s[::-1] == s 判断是否回文：是则 1 次，否则 2 次
