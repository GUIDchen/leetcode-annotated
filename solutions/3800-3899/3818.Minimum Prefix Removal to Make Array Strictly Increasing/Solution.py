# 题目：3818. 移除前缀使数组严格递增（Minimum Prefix Removal to Make Array Strictly Increasing）
# 思路：删掉前缀后剩下的是原数组的一个后缀，所以只要从右往左找到第一个破坏严格递增的位置即可。一旦 nums[i-1] >= nums[i]，下标 i-1 必须被删除，而删前缀必须连带它左侧的全部元素，故最少删除长度就是 i。
# 时间复杂度：O(n)，最坏情况从右往左扫完整个数组；空间复杂度：O(1)，只用了一个循环变量。
class Solution:  # LeetCode 约定的题解类
    def minimumPrefixLength(self, nums: List[int]) -> int:  # nums：待处理的整数数组，返回需要删除的最短前缀长度
        for i in range(len(nums) - 1, 0, -1):  # 从最后一个下标倒着扫到 1（不包含 0）
            if nums[i - 1] >= nums[i]:  # 发现相邻两个元素不再严格递增
                return i  # 下标 i-1 必须被删，而删前缀要连带左侧全部元素，所以最少删除长度就是 i
        return 0  # 整个数组本来就严格递增，不需要删除任何元素
