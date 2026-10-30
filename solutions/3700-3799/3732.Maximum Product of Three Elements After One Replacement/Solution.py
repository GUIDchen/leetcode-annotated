# 3732. 一次替换后的三元素最大乘积 / Maximum Product of Three Elements After One Replacement
# 核心思路：把其中一个元素替换成上界 x 后，最大乘积只会来自三种组合：两个最小值乘 x、两个最大值乘 x、最大正数与最小负数相乘再乘 x。排序后直接比较这三者。
# 复杂度：时间 O(n log n)，空间 O(1)（排序所需栈空间除外）。
class Solution:  # 定义 LeetCode 解法类
    def maxProduct(self, nums: List[int]) -> int:  # 返回替换一个元素后的三数最大乘积
        nums.sort()  # 升序排序，方便取两端极值
        a, b = nums[0], nums[1]  # a、b 为最小的两个元素（可能为负数）
        c, d = nums[-2], nums[-1]  # c、d 为最大的两个元素
        x = 10**5  # 替换值的上界
        return max(a * b * x, c * d * x, a * d * -x)  # 三种候选取最大：两个最小值乘 x、两个最大值乘 x、最大正数与最小负数相乘再乘 x
