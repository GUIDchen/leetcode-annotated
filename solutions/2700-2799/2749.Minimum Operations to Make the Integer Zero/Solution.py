# 题目：2749. 得到整数零需要执行的最少操作数（Minimum Operations to Make the Integer Zero）
# 思路：设做 k 次操作，剩余 num1 - k*num2 要由 k 个 2 的幂之和凑出；可行性等价于 bit_count(x) ≤ k ≤ x，从小到大枚举 k。
# 时间复杂度：O(log(num1))，k 只需枚举到 num1；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def makeTheIntegerZero(self, num1: int, num2: int) -> int:  # num1：初始整数；num2：每次操作额外减去的固定值；返回最少操作次数
        for k in count(1):  # count(1) 产生 1,2,3,... 的无限递增序列，用于从小到大枚举 k
            x = num1 - k * num2  # k 次操作后剩余 num1-k*num2，要由 k 个 2 的幂之和凑出
            if x < 0:  # 剩余值变负，继续增大 k 不可能归零
                break  # 结束枚举
            if x.bit_count() <= k <= x:  # x 的二进制 1 的个数是凑出 x 的最少 2 的幂个数，需 ≤ k；k ≤ x 保证每项至少为 1
                return k  # 第一个可行的 k 就是最小操作次数
        return -1  # 无解时返回 -1
