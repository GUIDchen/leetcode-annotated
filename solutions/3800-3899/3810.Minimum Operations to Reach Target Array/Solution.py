# 3810. Minimum Operations to Reach Target Array | 变成目标数组的最少操作次数
# 核心思路：一次操作可以把所有等于同一个值的元素一起加一，所以每个“需要修改的数值”只需一次操作；答案就是 nums[i] != target[i] 处 nums[i] 的去重个数。
# 复杂度：时间 O(n)；空间 O(n)（集合）。
class Solution:  # 定义题解类
    def minOperations(self, nums: List[int], target: List[int]) -> int:  # 返回把 nums 变成 target 的最少操作次数
        s = {x for x, y in zip(nums, target) if x != y}  # 集合推导式：收集所有与目标不同的 nums 值，自动去重
        return len(s)  # 不同数值的个数即最少操作次数
