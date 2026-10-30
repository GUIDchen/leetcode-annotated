# 3678. Smallest Absent Positive Greater Than Average（大于平均值的最小未出现正整数）
# 核心思路：集合记录出现过的数并求和，从 max(1, 平均值下取整 + 1) 开始逐个检查是否未出现过。
# 复杂度：时间 O(n)，空间 O(n)。
class Solution:  # 定义 Solution 类
    def smallestAbsent(self, nums: List[int]) -> int:  # 求大于平均值且未出现过的最小正整数
        s = set(nums)  # 记录数组中出现过的所有元素
        ans = max(1, sum(nums) // len(nums) + 1)  # 从严格大于平均值的最小正整数开始找
        while ans in s:  # 该数已经出现过
            ans += 1  # 向后继续找下一个候选
        return ans  # 返回最小未出现且大于平均值的正整数
