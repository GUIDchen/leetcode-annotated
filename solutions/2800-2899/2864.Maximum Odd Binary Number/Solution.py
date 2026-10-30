# 题目：2864. 最大二进制奇数（Maximum Odd Binary Number）
# 思路：二进制数为奇数等价于最低位是 1，所以留一个 '1' 放末位，其余 cnt-1 个 '1' 全部前置，'0' 紧随其后。
# 时间复杂度：O(n)，统计与构造都是线性；空间复杂度：O(n)，保存返回的新字符串。
class Solution:  # LeetCode 约定的题解类
    def maximumOddBinaryNumber(self, s: str) -> str:  # s 是 '0'/'1' 串，返回重排后最大的奇数二进制串
        cnt = s.count("1")  # 数出 1 的个数，0 的个数为 len(s) - cnt
        return "1" * (cnt - 1) + (len(s) - cnt) * "0" + "1"  # 前面的 1 越多越大，末位放 1 保证为奇数
