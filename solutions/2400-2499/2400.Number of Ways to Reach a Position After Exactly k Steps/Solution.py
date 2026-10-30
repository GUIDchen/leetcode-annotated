# 题目：2400. 恰好移动 k 步到达某一位置的方法数目（Number of Ways to Reach a Position After Exactly k Steps）
# 思路：以“到目标的距离 i + 剩余步数 j”为状态做记忆化 DFS，每步要么让距离加 1、要么让距离减 1（取绝对值）。
# 时间复杂度：O(k^2)，状态数为 k×k；空间复杂度：O(k^2)，@cache 保存的记忆化结果。
class Solution:  # LeetCode 约定的题解类
    def numberOfWays(self, startPos: int, endPos: int, k: int) -> int:  # startPos：起点；endPos：终点；k：恰好 k 步
        @cache  # 用 @cache 做记忆化，避免重复计算同一状态
        def dfs(i: int, j: int) -> int:  # 内部递归函数：i 当前到终点的距离，j 剩余步数
            if i > j or j < 0:  # 距离超过剩余步数，或步数已用尽为负：都不可能恰好到达
                return 0  # 这种状态返回 0 种方案
            if j == 0:  # 剩余步数为 0 时，是否到达取决于距离是否为 0
                return 1 if i == 0 else 0  # 距离为 0 记 1 种方案，否则 0 种
            return (dfs(i + 1, j - 1) + dfs(abs(i - 1), j - 1)) % mod  # 走远使距离 +1，或走近使距离 -1（取绝对值），相加后取模

        mod = 10**9 + 7  # 方案数对 1e9+7 取模；此处绑定后 dfs 被调用时已能看见它
        return dfs(abs(startPos - endPos), k)  # 从起终点距离出发，走满 k 步的方案数
