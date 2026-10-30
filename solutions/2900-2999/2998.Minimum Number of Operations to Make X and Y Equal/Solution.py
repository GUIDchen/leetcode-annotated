# 题目：2998. 使 X 和 Y 相等的最少操作次数（Minimum Number of Operations to Make X and Y Equal）
# 思路：记忆化 DFS。从 x 出发枚举「减 1」以及「先补到 5 / 11 的倍数再整除」这几类操作，取步数最小者。
# 时间复杂度：O(log x) 个可达状态、每个状态 5 种转移；空间复杂度：O(log x)，记忆化缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def minimumOperationsToMakeEqual(self, x: int, y: int) -> int:  # x：起始值；y：目标值；返回把 x 变成 y 的最少操作次数
        @cache  # 给 dfs 装上记忆化，相同入参只计算一次
        def dfs(x: int) -> int:  # 递归函数：把参数 x 变成 y 的最少操作次数
            if y >= x:  # 递归边界：x 已经不大于 y，继续除或加 1 只会更远
                return y - x  # 只能一路减 1，步数就是差值 y - x
            ans = x - y  # 候选方案零：完全不除，只用减 1 操作
            ans = min(ans, x % 5 + 1 + dfs(x // 5))  # 候选一：先减 x % 5 步补到 5 的倍数，再花 1 步整除 5
            ans = min(ans, 5 - x % 5 + 1 + dfs(x // 5 + 1))  # 候选二：先加 5 - x % 5 步补到上一个 5 的倍数，再花 1 步整除 5
            ans = min(ans, x % 11 + 1 + dfs(x // 11))  # 候选三：先减 x % 11 步补到 11 的倍数，再花 1 步整除 11
            ans = min(ans, 11 - x % 11 + 1 + dfs(x // 11 + 1))  # 候选四：先加 11 - x % 11 步补到上一个 11 的倍数，再花 1 步整除 11
            return ans  # 返回所有候选方案里的最小值

        return dfs(x)  # 从起点 x 开始求解
