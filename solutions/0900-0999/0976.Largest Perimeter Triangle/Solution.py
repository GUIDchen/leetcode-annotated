# 题目：976. 三角形的最大周长（Largest Perimeter Triangle）
# 思路：升序排序后从最长边开始往前枚举，一旦满足「两短边之和大于最长边」即为最大周长。
# 时间复杂度：O(n log n)，来自排序；空间复杂度：O(1)，只用了常数级额外变量。
class Solution:  # LeetCode 约定的题解类
    def largestPerimeter(self, nums: List[int]) -> int:  # nums：边长数组，返回能组成的最大三角形周长
        nums.sort()  # 原地升序排序，最长的边在末尾
        for i in range(len(nums) - 1, 1, -1):  # 从最长边开始往前枚举，i 是最长边的下标
            if (c := nums[i - 1] + nums[i - 2]) > nums[i]:  # 海象运算符先算出两短边之和 c，再判断它是否严格大于最长边
                return c + nums[i]  # 命中即返回周长；从大到小枚举，第一次命中就是最大周长
        return 0  # 没有能组成三角形的三条边，返回 0
