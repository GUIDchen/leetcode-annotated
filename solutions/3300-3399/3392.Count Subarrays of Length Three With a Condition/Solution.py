# 3392. 统计符合条件长度为 3 的子数组数目 / Count Subarrays of Length Three With a Condition
# 核心思路：用生成器枚举所有长度为 3 的子数组的中间下标，统计“两侧元素之和的两倍等于中间元素”的个数
# 复杂度：时间 O(n)、空间 O(1)
class Solution:  # 定义 Solution 类
    def countSubarrays(self, nums: List[int]) -> int:  # 统计满足条件的长度为 3 的子数组个数
        return sum(  # 返回满足条件的中间下标的个数
            (nums[i - 1] + nums[i + 1]) * 2 == nums[i] for i in range(1, len(nums) - 1)  # 逐个判断三元组的中间元素是否等于两侧元素之和的两倍
        )  # 生成器表达式结束
