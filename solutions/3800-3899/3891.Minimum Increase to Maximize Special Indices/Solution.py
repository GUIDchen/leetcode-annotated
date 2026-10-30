# 题目：3891. 最大化特殊下标数目的最少增加次数（Minimum Increase to Maximize Special Indices）
# 思路：特殊下标不能相邻，最多能取 ceil((n-2)/2) 个；用记忆化搜索从左往右决策，每个位置要么选为特殊下标（跳到 i+2），要么消耗一次“跳过”额度（跳到 i+1）。
# 时间复杂度：O(n)，每个状态只算一次；空间复杂度：O(n)，记忆化缓存。
class Solution:  # LeetCode 约定的题解类
    def minIncrease(self, nums: List[int]) -> int:  # nums：输入数组
        @cache  # @cache 自动记忆化，避免重复计算同一状态
        def dfs(i: int, j: int) -> int:  # dfs(i, j)：i 为当前下标，j 为剩余的跳过额度
            if i >= len(nums) - 1:  # 越过最后一个可能的下标，没有可选的特殊下标了
                return 0  # 返回 0 代价
            cost = max(0, max(nums[i - 1], nums[i + 1]) + 1 - nums[i])  # 把 nums[i] 抬到严格大于左右邻居所需的最少代价（不小于 0）
            ans = cost + dfs(i + 2, j)  # 选择 i 作为特殊下标，之后跳到 i+2（相邻下标不能再选）
            if j:  # 还有跳过额度可用
                ans = min(ans, dfs(i + 1, 0))  # 放弃 i，消耗一次额度后从 i+1 继续
            return ans  # 返回两种选择里的较小代价

        return dfs(1, len(nums) & 1 ^ 1)  # 从下标 1 开始；n 为偶数时多给一次跳过额度，用来对齐奇偶相位
