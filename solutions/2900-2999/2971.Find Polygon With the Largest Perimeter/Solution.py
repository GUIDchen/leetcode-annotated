# 题目：2971. 找到最大周长的多边形（Find Polygon With the Largest Perimeter）
# 思路：排序后枚举前 k 条边，用前缀和判断其余边之和是否大于最长边，满足则用总和更新答案。
# 时间复杂度：O(n log n)（排序）；空间复杂度：O(n)（前缀和）。
class Solution:  # LeetCode 约定的题解类
    def largestPerimeter(self, nums: List[int]) -> int:  # nums：边长数组，返回最大周长，无法构成多边形返回 -1
        nums.sort()  # 排序后取前 k 条边时，最长边固定是 nums[k-1]
        s = list(accumulate(nums, initial=0))  # 前缀和，s[i] 表示前 i 条边之和（initial=0 使 s[0]=0）
        ans = -1  # 答案初值 -1：还没找到可行方案
        for k in range(3, len(nums) + 1):  # 枚举参与构成多边形的边数 k，至少需要 3 条
            if s[k - 1] > nums[k - 1]:  # 多边形不等式：其余边之和 > 最长边
                ans = max(ans, s[k])  # 满足就用总和（周长 s[k]）更新答案
        return ans  # 返回最大周长，找不到则为 -1
