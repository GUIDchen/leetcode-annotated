# 题目：2656. K 个元素的最大和（Maximum Sum With Exactly K Elements）
# 核心思路：每次取当前最大值并把它加一，等价于以数组最大值为首项、步长为 1 的等差数列求和。
# 时间复杂度：O(n)，只需找一次最大值；空间复杂度：O(1)。
class Solution:  # 题解类
    def maximizeSum(self, nums: List[int], k: int) -> int:  # nums：候选数组；k：恰好选取并累加的轮数
        x = max(nums)  # 取数组最大值作为第一次选取的值
        return k * x + k * (k - 1) // 2  # 共取 k 次，每次值加一，总和为 k*x + (0+1+...+(k-1))
