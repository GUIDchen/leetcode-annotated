# 题目：3115. 质数的最大距离（Maximum Prime Difference）
# 思路：从左往右找到第一个质数，再从右往左找到最后一个质数，下标之差就是最大距离。
# 时间复杂度：O(n·√V)，最坏要扫完数组并对每个数试除到 √V；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maximumPrimeDifference(self, nums: List[int]) -> int:  # nums：输入数组；返回第一个与最后一个质数的下标之差
        def is_prime(x: int) -> bool:  # 内嵌函数：判断 x 是否为质数
            if x < 2:  # 0 和 1 都不是质数
                return False  # 直接返回假
            return all(x % i for i in range(2, int(sqrt(x)) + 1))  # 用生成器表达式试除 2 到 √x，一个因子都没有就是质数

        for i, x in enumerate(nums):  # 从左往右枚举下标与元素
            if is_prime(x):  # 遇到第一个质数，它就是最左边的质数
                for j in range(len(nums) - 1, i - 1, -1):  # 从最右端往左倒序扫描，下界取 i - 1 以便覆盖 i 本身
                    if is_prime(nums[j]):  # 找到最右边的质数
                        return j - i  # 下标之差即为答案
