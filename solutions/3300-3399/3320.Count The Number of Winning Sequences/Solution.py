# 题目：3320. 统计能获胜的出招序列数（Count The Number of Winning Sequences）
# 思路：记忆化搜索。dfs(i, j, k) 表示已出 i 招、Bob 净胜分为 j（负数表示我领先）、上一招为 k 的方案数；每轮枚举与上一招不同的三招之一并用 calc 累加得分，
# 剩余轮数已追不上当前领先分时剪枝。时间复杂度：O(n^2 · 3 · 3)；空间复杂度：O(n^2 · 4)，n = len(s)。
class Solution:  # LeetCode 约定的题解类
    def countWinningSequences(self, s: str) -> int:  # s：Bob 的出招序列
        def calc(x: int, y: int) -> int:  # calc(x, y)：Bob 出 x、我出 y 时 Bob 的得分（1 表示 Bob 赢，0 平，-1 表示我赢）
            if x == y:  # 出招相同即为平局
                return 0  # 平局双方都不得分
            if x < y:  # 下标小的招式对下标大的招式，只有下面一种例外
                return 1 if x == 0 and y == 2 else -1  # F(0) 克 E(2)，Bob 得 1 分；其余情况 Bob 失分
            return -1 if x == 2 and y == 0 else 1  # E(2) 被 F(0) 克时 Bob 失分；其余大下标招式胜出得 1 分

        @cache  # 用 functools.cache 做记忆化：同一状态只计算一次
        def dfs(i: int, j: int, k: int) -> int:  # i：已出轮数；j：Bob 净胜分（负数表示我领先）；k：我上一轮出的招式
            if len(s) - i <= j:  # 剩余轮数 <= Bob 的领先分：最多追平，反超不了
                return 0  # 剪枝：该分支不可能让我获胜
            if i >= len(s):  # n 轮已全部出完
                return int(j < 0)  # 只有 Bob 净胜分为负（即我领先）才算一种获胜序列
            res = 0  # 累计当前状态的方案数
            for l in range(3):  # 枚举本轮我出的招式 0 / 1 / 2
                if l == k:  # 不能连续两轮出同一招
                    continue  # 跳过与上一轮相同的招式
                res = (res + dfs(i + 1, j + calc(d[s[i]], l), l)) % mod  # 递归下一轮并累加 Bob 本轮得分，按模取余
            return res  # 返回当前状态的方案数

        mod = 10**9 + 7  # 取模常量；dfs 在调用时才读取它，定义在 dfs 之后也合法
        d = {"F": 0, "W": 1, "E": 2}  # 招式到数字的映射，与 C++ 版保持一致
        ans = dfs(0, 0, -1)  # 从第 0 轮、Bob 净胜分 0、无上一招开始搜索
        dfs.cache_clear()  # 清空缓存，避免多次调用之间占用内存
        return ans  # 返回获胜序列总数
