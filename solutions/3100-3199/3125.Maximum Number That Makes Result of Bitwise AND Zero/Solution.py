# 题目：3125. 使得按位与结果为 0 的最大数字（Maximum Number That Makes Result of Bitwise AND Zero）
# 思路：取 n 的最高二进制位，把它及其以上全部清零、以下全部置 1，得到的数既最大又与 n 按位与为 0。
# 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def maxNumber(self, n: int) -> int:  # 求满足 (n & x) == 0 的最大整数 x
        return (1 << (n.bit_length() - 1)) - 1  # n.bit_length() - 1 是最高位的下标，1 左移后再减 1 得到最高位以下全为 1 的数
