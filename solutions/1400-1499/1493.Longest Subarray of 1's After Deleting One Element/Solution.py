# 题目：1493. 删掉一个元素以后全为 1 的最长子数组（Longest Subarray of 1's After Deleting One Element）
# 思路：先分别预处理以每个位置结尾/开头的连续 1 长度，再枚举删除位置，把左右两段长度相加取最大。
# 时间复杂度：O(n)；空间复杂度：O(n)，两个长度为 n+1 的辅助数组。
class Solution:  # LeetCode 约定的题解类
    def longestSubarray(self, nums: List[int]) -> int:  # 返回删掉一个元素后最长的全 1 子数组长度
        n = len(nums)  # 数组长度
        left = [0] * (n + 1)  # left[i] 表示以 nums[i-1] 结尾的连续 1 个数
        right = [0] * (n + 1)  # right[i] 表示以 nums[i] 开头的连续 1 个数
        for i, x in enumerate(nums, 1):  # enumerate 从 1 开始编号，方便直接用 left[i-1] 递推
            if x:  # 当前位置是 1 才延长连续段
                left[i] = left[i - 1] + 1  # 接上前一个位置结尾的长度
        for i in range(n - 1, -1, -1):  # 逆序扫描，递推 right 数组
            if nums[i]:  # 当前位置是 1 才延长连续段
                right[i] = right[i + 1] + 1  # 接上后一个位置开头的长度
        return max(left[i] + right[i + 1] for i in range(n))  # 枚举删除位置 i，把左侧 left[i] 与右侧 right[i+1] 拼起来，取最大
