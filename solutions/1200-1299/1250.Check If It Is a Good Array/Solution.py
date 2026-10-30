# 题目：1250. 检查「好数组」（Check If It Is a Good Array）
# 思路：裴蜀定理——数组中存在若干数配上整数系数后和为 1，当且仅当这整组数的最大公约数为 1；因此把所有元素归约求 gcd 再判断即可。
# 时间复杂度：O(n log V)，n 为数组长度、V 为元素最大值；空间复杂度：O(1)，reduce 只维持一个累加值。
class Solution:  # LeetCode 约定的题解类
    def isGoodArray(self, nums: List[int]) -> bool:  # nums：输入数组，元素均为正整数；返回这组数是否构成「好数组」
        return reduce(gcd, nums) == 1  # reduce(gcd, nums) 把所有元素依次求 gcd 归约成一个数，等于 1 才说明能凑出和 1
