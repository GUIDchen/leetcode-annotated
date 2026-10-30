# 题目：645. 错误的集合（Set Mismatch）
# 核心思路：重复值 = 原数组总和 - 去重集合之和；缺失值 = 1..n 的理论总和 - 去重集合之和。
# 时间复杂度：O(n)，求和与去重各扫一遍；空间复杂度：O(n)，set 存放去重后的元素。
class Solution:  # LeetCode 约定的题解类
    def findErrorNums(self, nums: List[int]) -> List[int]:  # 返回 [重复的数字, 缺失的数字]
        n = len(nums)  # 数组长度，也等于 1..n 的取值范围
        s1 = (1 + n) * n // 2  # 1..n 的理论总和
        s2 = sum(set(nums))  # 去重后的元素之和
        s = sum(nums)  # 原数组的总和
        return [s - s2, s1 - s2]  # 多出来的部分就是重复值，少掉的部分就是缺失值
