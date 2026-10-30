# 题目：1295. 统计位数为偶数的数字（Find Numbers with Even Number of Digits）
# 核心思路：把每个数字转成字符串取长度即为十进制位数，判断位数是否为偶数并计数。
# 时间复杂度：O(n·log V)，每个数做一次位数转换；空间复杂度：O(1)，Python 版另有 O(log V) 的字符串开销。
class Solution:  # LeetCode 约定的题解类
    def findNumbers(self, nums: List[int]) -> int:  # 题解方法对外可见
        return sum(len(str(x)) % 2 == 0 for x in nums)  # nums 是正整数数组，返回其中「十进制位数为偶数」的元素个数
