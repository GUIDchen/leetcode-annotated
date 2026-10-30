# 3904. 最小稳定下标 II（Smallest Stable Index II）
# 思路：预处理每个位置的后缀最小值，再从左往右维护前缀最大值；第一个满足「前缀最大值 - 后缀最小值 <= k」的位置就是最小稳定下标。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(n)。
class Solution:  # LeetCode 约定的题解类
    def firstStableIndex(self, nums: list[int], k: int) -> int:  # nums：输入数组；k：允许的最大差值
        n = len(nums)  # 数组长度
        right = [nums[-1]] * n  # right[i] 表示 nums[i..n-1] 的最小值，先整体填成末元素
        for i in range(n - 2, -1, -1):  # 从右往左递推
            right[i] = min(right[i + 1], nums[i])  # 后缀最小值 = min(右侧后缀最小值, 当前元素)
        left = 0  # left 维护 nums[0..i] 的前缀最大值
        for i, x in enumerate(nums):  # 从左往右扫描，同时取得下标与元素值
            left = max(left, x)  # 更新前缀最大值
            if left - right[i] <= k:  # 前后缀极差不超过 k 即为稳定下标
                return i  # 首次命中即最小稳定下标
        return -1  # 没有稳定下标，返回 -1
