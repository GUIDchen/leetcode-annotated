# 题目：1690. 石子游戏 VII（Stone Game VII）
# 思路：区间 DP，dfs(i, j) 为当前玩家在 [i, j] 上能取得的最大分差；拿左端或右端后用「剩余区间和 - 对手分差」转移。
# 时间复杂度：O(n^2) 个区间、每个区间 O(1) 转移；空间复杂度：O(n^2) 缓存加 O(n) 前缀和。
class Solution:  # LeetCode 约定的题解类
    def stoneGameVII(self, stones: List[int]) -> int:  # stones：每颗石子的分值
        @cache  # cache：自动记忆化，避免同一区间重复递归
        def dfs(i: int, j: int) -> int:  # dfs(i, j)：区间 [i, j] 上当前玩家能获得的最大分差
            if i > j:  # 区间为空
                return 0  # 没有石子可拿，分差为 0
            a = s[j + 1] - s[i + 1] - dfs(i + 1, j)  # 拿左端：剩余区间和减去对手在剩余区间的最优分差
            b = s[j] - s[i] - dfs(i, j - 1)  # 拿右端：剩余区间和减去对手在剩余区间的最优分差
            return max(a, b)  # 两种取法中的较大者就是本区间的最优分差

        s = list(accumulate(stones, initial=0))  # 分值前缀和，initial=0 使 s[i] 表示前 i 颗石子的和
        ans = dfs(0, len(stones) - 1)  # 整个区间的最大分差就是答案
        dfs.cache_clear()  # 清空缓存，避免多次调用之间互相影响
        return ans  # 返回答案
