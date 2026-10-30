# 题目：3862. 找出最小平衡下标（Find the Smallest Balanced Index）
# 思路：从右往左枚举，用「总和减去当前元素」维护左侧和、用累乘维护右侧积，并做单调性剪枝。
# 时间复杂度：O(n)，只扫描一遍；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def smallestBalancedIndex(self, nums: list[int]) -> int:  # 返回最小平衡下标（左侧和等于右侧积），不存在则返回 -1
        s = sum(nums)  # s 初值取总和，遍历中减去当前元素即得左侧和
        p = 1  # p：右侧元素的乘积，空乘积记为 1
        for i in range(len(nums) - 1, -1, -1):  # 从右往左枚举，p 可以直接递推成右侧乘积
            s -= nums[i]  # 扣掉 nums[i]，此时 s 正是下标 i 严格左侧的元素和
            if s == p:  # 左侧和等于右侧积，i 就是平衡下标
                return i  # 直接返回（元素均为正数时平衡下标唯一）
            p *= nums[i]  # 把 nums[i] 并入乘积，供下一个更小的下标使用
            if p >= s:  # 剪枝：继续左移时 p 只增、s 只减，不可能再相等
                break  # 提前结束
        return -1  # 遍历完都没有平衡下标，返回 -1
