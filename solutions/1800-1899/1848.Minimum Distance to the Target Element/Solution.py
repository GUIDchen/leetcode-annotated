# 题目：1848. 到目标元素的最小距离（Minimum Distance to the Target Element）
# 思路：用生成器表达式筛出所有等于 target 的下标，直接对 |i - start| 取最小值。
# 时间复杂度：O(n)，遍历数组一次；空间复杂度：O(n)，生成器在 min 内部展开。
class Solution:  # LeetCode 约定的题解类
    def getMinDistance(self, nums: List[int], target: int, start: int) -> int:  # nums：输入数组；target：目标值；start：起始下标
        return min(abs(i - start) for i, x in enumerate(nums) if x == target)  # 只保留值等于 target 的下标 i，取 |i - start| 的最小值
