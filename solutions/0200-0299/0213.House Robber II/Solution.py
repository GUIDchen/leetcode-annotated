# 题目：213. 打家劫舍 II（House Robber II）
# 思路：首尾相邻成环，于是拆成两个线性区间分别做打家劫舍：不偷最后一户 / 不偷第 0 户，取两者较优。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只用常数个滚动变量（切片会额外占用 O(n) 拷贝）。
class Solution:  # LeetCode 约定的题解类
    def rob(self, nums: List[int]) -> int:  # nums 是每户金额，首尾相邻成环
        def _rob(nums):  # 内部函数：对线性排列的房屋做打家劫舍
            f = g = 0  # f 表示当前这户不偷的最大收益，g 表示当前这户偷的最大收益
            for x in nums:  # 逐个房屋递推
                f, g = max(f, g), f + x  # 同时更新：不偷取两者较大值，偷则上一户必须不偷再加本户金额
            return max(f, g)  # 两种状态取较大者

        if len(nums) == 1:  # 只有一户，首尾是同一户
            return nums[0]  # 直接返回这户金额
        return max(_rob(nums[1:]), _rob(nums[:-1]))  # 分两种情况取较优：nums[1:] 舍去第 0 户，nums[:-1] 舍去最后一户
