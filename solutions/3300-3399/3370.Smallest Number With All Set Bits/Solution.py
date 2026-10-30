# 题目：3370. 仅含置位位的最小整数（Smallest Number With All Set Bits）
# 思路：从 1 开始不断左移，直到 x-1 ≥ n；此时 x-1 的二进制形如 111…1，正是最小的全 1 整数。
# 时间复杂度：O(log n)，最多左移 log2(n)+1 次；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def smallestNumber(self, n: int) -> int:  # n 是下界，返回大于等于 n 且二进制全为 1 的最小整数
        x = 1  # x 始终是 2 的幂，因此 x-1 的二进制全为 1
        while x - 1 < n:  # x-1 还小于 n，说明位数不够，继续加一位
            x <<= 1  # 左移一位，让全 1 的位数多一位
        return x - 1  # x-1 就是大于等于 n 的最小全 1 整数
