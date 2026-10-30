# 题目：283. 移动零（Move Zeroes）
# 思路：双指针 k 记录下一个非零元素该放的位置，遍历时把非零元素交换到 nums[k]，零自然被挤到末尾。
# 时间复杂度：O(n) 一次遍历；空间复杂度：O(1)，原地交换。
class Solution:  # LeetCode 约定的题解类
    def moveZeroes(self, nums: List[int]) -> None:  # nums 是待原地调整的数组，原地修改返回 None
        k = 0  # k：下一个非零元素应该放置的位置
        for i, x in enumerate(nums):  # 同时取得下标 i 与元素值 x
            if x:  # 只处理非零元素（0 是假值）
                nums[k], nums[i] = nums[i], nums[k]  # 把非零元素换到 k 位置，k 位置上的 0 被换到 i
                k += 1  # k 后移，指向下一个空位
