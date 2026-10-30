# 题目：2860. 让所有学生保持开心的分组方法数（Happy Students）
# 思路：升序排序后，选前 i 个学生时，合法性等价于 nums[i-1] < i 且 nums[i] > i，枚举所有 i 计数即可。
# 复杂度：时间 O(n log n)，瓶颈是排序；空间 O(1)，只用了几个计数变量。
class Solution:  # LeetCode 约定的题解类
    def countWays(self, nums: List[int]) -> int:  # nums：每个学生的能力值
        nums.sort()  # 升序排序，候选分组就是「能力值最小的前 i 个学生」
        n = len(nums)  # 学生总数
        ans = 0  # 记录合法的分组方案数
        for i in range(n + 1):  # 枚举选进组内的学生人数 i，范围 0..n
            if i and nums[i - 1] >= i:  # 组内最后一个学生能力值必须小于 i
                continue  # 不满足就换个大小
            if i < n and nums[i] <= i:  # 组外第一个学生能力值必须大于 i
                continue  # 不满足就换个大小
            ans += 1  # 两个条件都满足，方案数加一
        return ans  # 返回合法方案总数
