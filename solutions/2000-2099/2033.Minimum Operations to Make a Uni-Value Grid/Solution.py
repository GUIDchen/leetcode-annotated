# 题目：2033. 获取单值网格的最小操作数（Minimum Operations to Make a Uni-Value Grid）
# 思路：所有元素必须对 x 同余，否则无解；把网格摊平排序后取中位数作为目标值，答案是 ∑|v - mid| // x。
# 时间复杂度：O(mn log(mn))，排序占主导；空间复杂度：O(mn)，额外用一维列表存放所有元素。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, grid: List[List[int]], x: int) -> int:  # grid 是二维网格，x 是每次操作允许的增减量
        nums = []  # 摊平后的元素列表
        mod = grid[0][0] % x  # 以左上角元素对 x 的余数作为基准，所有元素必须与之相同
        for row in grid:  # 逐行遍历网格
            for v in row:  # 逐列遍历当前行
                if v % x != mod:  # 余数不一致说明该元素无法通过加减 x 对齐到同一值
                    return -1  # 判定无解
                nums.append(v)  # 同余则收集到摊平列表里
        nums.sort()  # 排序，为取中位数做准备
        mid = nums[len(nums) >> 1]  # 中位数是让绝对偏差之和最小的目标值
        return sum(abs(v - mid) // x for v in nums)  # 生成器求和：每个元素需要 |v - mid| // x 次操作
