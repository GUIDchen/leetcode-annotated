# 题目：1480. 一维数组的动态和（Running Sum of 1d Array）
# 思路：直接调用 itertools.accumulate 求前缀和，再转成 list 返回（题解环境已自带该工具，故无需 import）。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，返回的新列表。
class Solution:  # LeetCode 约定的题解类
    def runningSum(self, nums: List[int]) -> List[int]:  # nums：输入数组，函数不修改它
        return list(accumulate(nums))  # accumulate 依次产出前缀和，转成列表即为动态和数组
