# 题目：2742. 给墙壁刷油漆（Painting the Walls）
# 核心思路：记忆化搜索，dfs(i, j) 表示处理到第 i 面墙、还剩 j 次免费额度时的最小花费，付费与免费两种转移取较小值。
# 时间复杂度：O(n^2)，每个 (i, j) 状态只算一次；空间复杂度：O(n^2)，cache 缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def paintWalls(self, cost: List[int], time: List[int]) -> int:  # cost：付费花费；time：付费后可免费刷的墙数
        @cache  # 装饰器缓存 dfs 的结果，避免同一状态被重复计算
        def dfs(i: int, j: int) -> int:  # dfs(当前墙下标 i, 剩余免费额度 j)
            if n - i <= j:  # 剩余墙数不超过免费额度，剩下的墙都能免费刷
                return 0  # 不再产生花费
            if i >= n:  # 墙已考虑完但额度仍不足
                return inf  # 返回无穷大，表示该方案不可行
            return min(dfs(i + 1, j + time[i]) + cost[i], dfs(i + 1, j - 1))  # 付费刷第 i 面墙（额度加 time[i]）或让第 i 面墙免费刷（额度减 1），取较小花费

        n = len(cost)  # 墙的总数，供上面的 dfs 闭包使用
        return dfs(0, 0)  # 从第 0 面墙、免费额度 0 开始搜索
