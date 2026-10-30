# 题目：461. 汉明距离（Hamming Distance）
# 思路：异或后不同位为 1，再用 bit_count() 统计 1 的个数（Python 3.10+ 提供）。
# 时间复杂度：O(1)（最多 32 位）；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def hammingDistance(self, x: int, y: int) -> int:  # x、y 是两个整数，返回二进制位不同的个数
        return (x ^ y).bit_count()  # 异或后不同位为 1，bit_count() 统计 1 的个数
