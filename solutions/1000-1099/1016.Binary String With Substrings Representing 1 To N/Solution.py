# 题目：1016. 子串能表示从 1 到 N 数字的二进制串（Binary String With Substrings Representing 1 To N）
# 思路：只需检查 (n/2, n] 这些数：它们位数比更小的数多一位，更小的数的二进制正是它们的后缀，因此这些数都出现时其余数必然出现。
# 时间复杂度：O(n * |s|)，n 至多 1000；空间复杂度：O(1)，只用到常数级临时字符串。
class Solution:  # LeetCode 约定的题解类
    def queryString(self, s: str, n: int) -> bool:  # s：给定的 01 串；n：需要能被表示的数字上界
        if n > 1000:  # n 的二进制超过 9 位，而 s 最长 1000 位，长度上就不可能覆盖，直接剪枝
            return False  # 直接判否
        return all(bin(i)[2:] in s for i in range(n, n // 2, -1))  # 只查区间 (n/2, n]；bin(i)[2:] 去掉 0b 前缀得到二进制表示；all 要求每个数都是 s 的子串
