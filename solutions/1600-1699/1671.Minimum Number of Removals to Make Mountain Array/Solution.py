# 题目：1671. 得到山形数组的最少删除次数（Minimum Number of Removals to Make Mountain Array）
# 思路：分别求以每个位置结尾的最长严格递增子序列长度 left、以每个位置开头的最长严格递减子序列长度 right，再枚举峰顶取 left+right-1 的最大值。
# 时间复杂度：O(n²)，两重循环求两个 LIS；空间复杂度：O(n)，left 与 right 两个数组。
class Solution:  # LeetCode 约定的题解类
    def minimumMountainRemovals(self, nums: List[int]) -> int:  # 求最少删除次数，使剩余数组成为山形数组
        n = len(nums)  # 数组长度
        left = [1] * n  # left[i] 是以 i 结尾的最长严格递增子序列长度
        right = [1] * n  # right[i] 是以 i 开头的最长严格递减子序列长度
        for i in range(1, n):  # 正序递推 left
            for j in range(i):  # 枚举 i 之前的位置 j
                if nums[i] > nums[j]:  # nums[i] 能接在 nums[j] 后面继续上升
                    left[i] = max(left[i], left[j] + 1)  # 用 j 的最优解加 1 更新 left[i]
        for i in range(n - 2, -1, -1):  # 逆序递推 right
            for j in range(i + 1, n):  # 枚举 i 之后的位置 j
                if nums[i] > nums[j]:  # nums[i] 能接在 nums[j] 前面继续下降
                    right[i] = max(right[i], right[j] + 1)  # 用 j 的最优解加 1 更新 right[i]
        return n - max(a + b - 1 for a, b in zip(left, right) if a > 1 and b > 1)  # 总长度减去最长山体长度；峰顶两侧都必须有元素才算合法山形
