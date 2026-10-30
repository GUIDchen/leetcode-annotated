# 题目：1872. 石子游戏 VIII（Stone Game VIII）
# 思路：先求前缀和 s，再记忆化搜索 dfs(i) = max(dfs(i+1), s[i] - dfs(i+1))，表示轮到当前玩家时能取得的最大分差。
# 时间复杂度：O(n)，每个状态只计算一次；空间复杂度：O(n)，前缀和数组与缓存各占 O(n)。
class Solution:  # LeetCode 约定的题解类
    def stoneGameVIII(self, stones: List[int]) -> int:  # stones：每堆石子的数量
        @cache  # 记忆化装饰器：缓存 dfs(i) 的结果，避免重复递归
        def dfs(i: int) -> int:  # 返回从下标 i 开始行动时当前玩家能获得的最大分差
            if i >= len(stones) - 1:  # 只剩最后一堆可选，只能全取
                return s[-1]  # 分差就是全部石子之和（即最大前缀和）
            return max(dfs(i + 1), s[i] - dfs(i + 1))  # 取走前 i+1 堆后由对手从 i+1 行动；或这次跳过、让对手先行动，两者取较大值

        s = list(accumulate(stones))  # 前缀和数组：s[i] 表示前 i+1 堆石子总数
        return dfs(1)  # 第一次行动必须取走前两堆，因此从下标 1 开始
