# 题目：89. 格雷编码（Gray Code）
# 思路：格雷码第 i 项等于 i ^ (i >> 1)。这个公式保证相邻两项只差一个二进制位，且首项为 0。
# 时间复杂度：O(2^n)，需要生成 2^n 个结果；空间复杂度：O(1)（不计返回列表）。

class Solution:  # LeetCode 约定的题解类
    def grayCode(self, n: int) -> List[int]:  # n：格雷码的二进制位数
        return [i ^ (i >> 1) for i in range(1 << n)]  # 枚举 0 .. 2^n-1，每项按 i 异或 (i >> 1) 的公式生成
