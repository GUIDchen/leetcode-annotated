# 题目：2874. 有序三元组中的最大值 II（Maximum Value of an Ordered Triplet II）
# 思路：与 2873 相同的单次遍历：维护前缀最大值 mx 与最大差值 mx_diff，用 mx_diff * x 更新答案，避免 O(n^3) 暴力。
# 时间复杂度：O(n)，n 更大也只扫一遍；空间复杂度：O(1)，只用了三个变量。
class Solution:  # LeetCode 约定的题解类
    def maximumTripletValue(self, nums: List[int]) -> int:  # nums 为输入数组，返回最大的三元组值
        ans = mx = mx_diff = 0  # ans 是最大三元组值；mx 是前缀最大值；mx_diff 是下标 i<j 时 nums[i] - nums[j] 的最大值
        for x in nums:  # 依次把 x 当作第三个下标 k 位置的元素
            ans = max(ans, mx_diff * x)  # 先用「之前的最佳差值 * 当前 x」尝试更新答案
            mx_diff = max(mx_diff, mx - x)  # 再把 x 当作 j，用「前缀最大值 - x」更新最佳差值
            mx = max(mx, x)  # 最后更新前缀最大值，供后面的元素使用
        return ans  # 返回最大三元组值（Python 整数不会溢出，无需额外处理）
