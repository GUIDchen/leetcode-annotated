# 题目：2529. 正整数和负整数的最大计数（Maximum Count of Positive Integer and Negative Integer）
# 核心思路：用生成器表达式分别数出正数个数 a 与负数个数 b（0 不计数），返回两者的较大值。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只保存两个计数结果。
class Solution:  # LeetCode 约定的题解类
    def maximumCount(self, nums: List[int]) -> int:  # nums 是升序数组，返回正数个数与负数个数中的较大值
        a = sum(x > 0 for x in nums)  # 布尔值参与求和：True 记 1，从而数出正数个数
        b = sum(x < 0 for x in nums)  # 同理数出负数个数，等于 0 的元素两边都不计入
        return max(a, b)  # 返回两类数字个数的较大者即为答案
