# 题目：877. 石子游戏（Stone Game）
# 核心思路：区间博弈加记忆化搜索，dfs(i, j) 返回区间 [i, j] 上先手能领先对手的最大分差，取走一端后减去对手在剩余区间的最优分差。
# 时间复杂度：O(n^2)，共 O(n^2) 个区间、每个区间 O(1) 转移；空间复杂度：O(n^2)，@cache 缓存全部区间。
class Solution:  # LeetCode 约定的题解类
    def stoneGame(self, piles: List[int]) -> bool:  # piles：每堆石子数量，两人轮流从剩下的区间两端取走一堆
        @cache  # 记忆化装饰器：同一个区间只计算一次
        def dfs(i: int, j: int) -> int:  # 返回当前玩家在区间 [i, j] 上能领先对手的最大分差
            if i > j:  # 区间为空，没有石子可取
                return 0  # 分差为 0
            return max(piles[i] - dfs(i + 1, j), piles[j] - dfs(i, j - 1))  # 取左端或取右端，减去对手在剩余区间上的领先分差，取较优者

        return dfs(0, len(piles) - 1) > 0  # 整个区间上的先手分差为正即必胜
