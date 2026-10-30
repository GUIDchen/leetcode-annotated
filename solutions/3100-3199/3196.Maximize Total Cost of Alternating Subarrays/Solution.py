# 3196. 最大化子数组的总成本（Maximize Total Cost of Alternating Subarrays）
# 核心思路：记忆化搜索。dfs(i, j) 返回从 i 开始的最大总成本，j 表示 nums[i] 能否继承负号；要么取正号当新首项，要么取负号与前项同组。
# 复杂度：时间 O(n)，空间 O(n)

class Solution:  # 定义题解类
    def maximumTotalCost(self, nums: List[int]) -> int:  # 返回把 nums 划分成交替子数组后的最大总成本
        @cache  # 用记忆化缓存 dfs 的结果，避免重复子问题
        def dfs(i: int, j: int) -> int:  # 递归函数：i 为当前下标，j 为 0/1 表示 nums[i] 能否取负号
            if i >= len(nums):  # 边界：后缀为空
                return 0  # 空后缀成本为 0
            ans = nums[i] + dfs(i + 1, 1)  # 方案一：nums[i] 作为新子数组首项取正号，下一项状态放开为 1
            if j == 1:  # 若当前元素可以继承负号
                ans = max(ans, -nums[i] + dfs(i + 1, 0))  # 方案二：nums[i] 取负号，下一项只能取正号（状态 0），取较大值
            return ans  # 返回当前状态的最优值

        return dfs(0, 0)  # 从下标 0 开始，首项必须取正号（j = 0）
