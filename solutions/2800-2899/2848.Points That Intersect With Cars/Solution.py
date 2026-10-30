# 题目：2848. 与车相交的点（Points That Intersect With Cars）
# 思路：对每个区间做差分标记 +1 与 -1，再求前缀和；前缀和大于 0 的位置就是被至少一辆车覆盖的点。
# 时间复杂度：O(n + 100)，一次差分遍历加一次扫描；空间复杂度：O(100)，固定大小的差分数组。
class Solution:  # LeetCode 约定的题解类
    def numberOfPoints(self, nums: List[List[int]]) -> int:  # nums：若干区间 [start, end]，统计被至少一个区间覆盖的整数点个数
        m = 102  # 差分数组长度，多留 2 位以容纳 end + 1
        d = [0] * m  # 差分数组初始化全 0
        for start, end in nums:  # 遍历每个区间做差分标记
            d[start] += 1  # 区间起点处覆盖数 +1
            d[end + 1] -= 1  # 区间终点的下一位覆盖数 -1，前缀和时覆盖自动结束
        return sum(s > 0 for s in accumulate(d))  # 求前缀和，统计其中大于 0 的位置个数（即被覆盖的点数）
