# 题目：3550. 数位和等于下标的最小下标（Smallest Index With Digit Sum Equal to Index）
# 思路：从下标 0 开始顺序枚举，逐个算出元素的十进制数位和并与下标比较，第一个相等的位置就是答案；枚举结束仍未命中则返回 -1。
# 时间复杂度：O(n · log M)，M 为元素最大值，每个元素最多拆 log10(M) 位；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def smallestIndex(self, nums: List[int]) -> int:  # nums：给定数组；返回数位和等于下标的最小下标，不存在则返回 -1
        for i, x in enumerate(nums):  # 按下标从小到大枚举，x 是当前元素的副本
            s = 0  # s：当前元素的数位和
            while x:  # 不断取最低位，直到 x 被除到 0
                s += x % 10  # 累加最低位上的数字
                x //= 10  # 整除去掉最低位，继续处理更高位
            if s == i:  # 数位和恰好等于下标
                return i  # 从小到大枚举，首个命中的下标必然最小，直接返回
        return -1  # 没有数位和等于下标的元素
