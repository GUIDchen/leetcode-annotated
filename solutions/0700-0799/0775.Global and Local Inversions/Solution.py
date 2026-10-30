# 题目：775. 全局倒置与局部倒置（Global and Local Inversions）
# 核心思路：局部倒置必是全局倒置，所以只需检查所有全局倒置都相邻；扫描时维护 nums[i-2] 的前缀最大值，若它大于 nums[i] 就存在跨位倒置。
# 时间复杂度 O(n)（一次线性扫描）；空间复杂度 O(1)（只维护一个前缀最大值）。
class Solution:  # LeetCode 约定的题解类
    def isIdealPermutation(self, nums: List[int]) -> bool:  # nums：0..n-1 的排列；判断全局倒置数是否等于局部倒置数
        mx = 0  # mx 维护 nums[0..i-2] 的最大值
        for i in range(2, len(nums)):  # 从下标 2 开始扫描，保证 i-2 合法
            if (mx := max(mx, nums[i - 2])) > nums[i]:  # 海象运算符顺便把 nums[i-2] 并入前缀最大值，再判断是否存在远距离倒置
                return False  # 前缀最大值大于 nums[i]，说明存在距离超过 1 的倒置
        return True  # 全部检查通过，两种倒置数相等
