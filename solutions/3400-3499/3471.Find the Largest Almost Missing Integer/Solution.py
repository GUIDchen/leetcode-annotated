# 3471. Find the Largest Almost Missing Integer / 3471. 找出最大的几近缺失整数
# 核心思路：k = 1 取只出现一次的最大值，k = n 取整个数组最大值，1 < k < n 时只判断首尾元素是否唯一。
# 复杂度：时间 O(n)，空间 O(n)。

class Solution:  # LeetCode 题解统一使用 Solution 类
    def largestInteger(self, nums: List[int], k: int) -> int:  # 返回在所有长度 k 子数组中都恰好出现一次的最大整数
        def f(k: int) -> int:  # 判断 nums[k] 是否在整个数组中只出现一次
            for i, x in enumerate(nums):  # 遍历数组的下标与值
                if i != k and x == nums[k]:  # 别处出现了相同的值
                    return -1  # 不是唯一，返回 -1
            return nums[k]  # 唯一则返回该值本身

        if k == 1:  # k 等于 1 时长度为 1 的子数组就是元素本身
            cnt = Counter(nums)  # 统计每个值的出现次数
            return max((x for x, v in cnt.items() if v == 1), default=-1)  # 取只出现一次的最大值，没有候选则返回 -1
        if k == len(nums):  # k 等于 n 时只有一个长度为 n 的子数组
            return max(nums)  # 直接返回整个数组的最大值
        return max(f(0), f(len(nums) - 1))  # 1 < k < n 时只有首尾元素必然落在每个子数组中
