# 3731. 找出缺失的元素 / Find Missing Elements
# 核心思路：先求数组最小值与最大值，再把区间内的整数逐个检查是否出现在集合中，缺失的即为答案。
# 复杂度：时间 O(n + max - min)，空间 O(n)。
class Solution:  # 定义 LeetCode 解法类
    def findMissingElements(self, nums: List[int]) -> List[int]:  # 返回区间内缺失的所有元素
        mn, mx = min(nums), max(nums)  # 求数组的最小值与最大值，确定检查区间
        s = set(nums)  # 用集合支持 O(1) 的存在性判断
        return [x for x in range(mn + 1, mx) if x not in s]  # 列表推导式收集区间内未出现的整数并返回
