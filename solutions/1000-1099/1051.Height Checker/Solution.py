# 题目：1051. 高度检查器（Height Checker）
# 思路：用 sorted 得到期望的非递减排列，再与原排列逐位比较，统计不相等的下标个数。
# 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(n)，保存期望排列的副本。
class Solution:  # LeetCode 约定的题解类
    def heightChecker(self, heights: List[int]) -> int:  # heights：当前排列；返回需要调整的位置个数
        expected = sorted(heights)  # 升序排序得到期望排列（不修改原列表）
        return sum(a != b for a, b in zip(heights, expected))  # 逐位比较，布尔值求和就是与期望排列不一致的个数
