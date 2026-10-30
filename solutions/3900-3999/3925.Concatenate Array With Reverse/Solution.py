# 题目：3925. 连接逆序数组（Concatenate Array With Reverse）
# 思路：开一个长度为 2n 的答案数组，一次遍历同时填好两半：前 n 位照抄 nums，后 n 位把 nums 倒序写入。
# 时间复杂度：O(n)，只遍历一遍；空间复杂度：O(n)，答案数组本身占 2n 个位置。
class Solution:  # LeetCode 约定的题解类
    def concatWithReverse(self, nums: list[int]) -> list[int]:  # nums：原数组，返回长度为 2n 的拼接结果
        n = len(nums)  # 原数组长度
        ans = [0] * (2 * n)  # 预分配长度为 2n 的答案数组
        for i, x in enumerate(nums):  # 同时取得下标 i 与元素 x
            ans[i] = x  # 前 n 位原样复制
            ans[i + n] = nums[n - i - 1]  # 后 n 位按倒序填入
        return ans  # 返回拼接结果
