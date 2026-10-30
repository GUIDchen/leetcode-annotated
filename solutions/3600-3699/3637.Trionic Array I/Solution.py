# 3637. 三段式数组 I / Trionic Array I
# 核心思路：用指针依次找出严格递增段、严格递减段、再一个严格递增段，三段都非空且恰好走到末尾即为三段式数组
# 时间复杂度 O(n)，空间复杂度 O(1)
#
class Solution:  # 题目要求实现的类
    def isTrionic(self, nums: List[int]) -> bool:  # 判断数组能否拆成严格递增、严格递减、严格递增三段
        n = len(nums)  # n 为数组长度
        p = 0  # p 指向第一段（递增段）的末尾
        while p < n - 2 and nums[p] < nums[p + 1]:  # 先找最长的严格递增前缀，留出后两段的空间
            p += 1  # 指针右移
        if p == 0:  # 递增段为空则不合法
            return False  # 返回 False
        q = p  # q 从 p 出发，寻找中间的递减段
        while q < n - 1 and nums[q] > nums[q + 1]:  # 再找严格递减段
            q += 1  # 指针右移
        if q == p or q == n - 1:  # 递减段为空，或递减段直接走到末尾（缺第三段）都不合法
            return False  # 返回 False
        while q < n - 1 and nums[q] < nums[q + 1]:  # 最后找第三段的严格递增
            q += 1  # 指针右移
        return q == n - 1  # 只有恰好走到最后一个下标，才说明是合法的三段式
