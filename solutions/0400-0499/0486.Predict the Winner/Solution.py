# 题目：486. 预测赢家（Predict the Winner）
# 思路：区间博弈 DP。dfs(i, j) 表示当前玩家在 nums[i..j] 上先手能领先对手的分数，选左端或右端都要减去对手在剩余区间的领先值，最后判断整体分差是否不小于 0。
# 时间复杂度：O(n²)，共 O(n²) 个区间且每个只算一次；空间复杂度：O(n²)，@cache 缓存所有区间结果。
class Solution:  # LeetCode 约定的题解类
    def predictTheWinner(self, nums: List[int]) -> bool:  # nums 是可选分数序列，返回先手是否能赢（分数不少于对手即算赢）
        @cache  # 自动记忆化装饰器：相同 (i, j) 只计算一次
        def dfs(i: int, j: int) -> int:  # 递归函数：i、j 为当前可选区间的左右端点
            if i > j:  # 区间为空时没有分数可得
                return 0  # 空区间返回 0
            return max(nums[i] - dfs(i + 1, j), nums[j] - dfs(i, j - 1))  # 两种选法取更优：选左端 nums[i] 减去对手在 [i+1, j] 的领先值，或选右端 nums[j] 减去对手在 [i, j-1] 的领先值

        return dfs(0, len(nums) - 1) >= 0  # 整个区间的分差 ≥ 0 说明先手不会输，即可以赢
