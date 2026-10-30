# 题目：3105. 最长的严格递增或递减子数组（Longest Strictly Increasing or Strictly Decreasing Subarray）
# 思路：用 enumerate(nums[1:]) 让 i 与 x 配对成相邻元素，分别统计严格递增、严格递减的连续段长度，边扫边用 ans 记录最大值。
# 时间复杂度：O(n)，两遍线性扫描；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def longestMonotonicSubarray(self, nums: List[int]) -> int:  # nums：输入数组；返回最长严格递增/递减子数组长度
        ans = t = 1  # ans 存答案；t 是当前单调连续段长度，至少为 1
        for i, x in enumerate(nums[1:]):  # 第一遍统计递增：i 从 0 开始，x 就是 nums[i + 1]
            if nums[i] < x:  # nums[i] < nums[i + 1]，严格递增
                t += 1  # 递增段长度加一
                ans = max(ans, t)  # 用当前段长更新答案
            else:  # 递增关系中断
                t = 1  # 段长重置为 1
        t = 1  # 重置段长，准备统计递减
        for i, x in enumerate(nums[1:]):  # 第二遍统计递减：同样用相邻元素配对
            if nums[i] > x:  # nums[i] > nums[i + 1]，严格递减
                t += 1  # 递减段长度加一
                ans = max(ans, t)  # 用当前段长更新答案
            else:  # 递减关系中断
                t = 1  # 段长重置为 1
        return ans  # 返回最长严格单调子数组长度
