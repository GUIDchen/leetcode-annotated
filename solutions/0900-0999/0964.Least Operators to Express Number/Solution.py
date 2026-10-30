# 题目：964. 表示数字的最少运算符（Least Operators to Express Number）
# 思路：记忆化 DFS。找到不小于 v 的最小 x 的幂 x^k，答案取「用 k-1 次乘法凑出 v - x^(k-1)」与「用 x^k 减掉差额」的较小值。
# 时间复杂度：O(log_x target) 个状态，每个状态常数工作量；空间复杂度：O(log_x target)，cache 保存记忆化结果。
class Solution:  # LeetCode 约定的题解类
    def leastOpsExpressTarget(self, x: int, target: int) -> int:  # x 是允许使用的底数，target 是要表示的目标数
        @cache  # @cache 装饰器自动记忆化，避免同一状态被重复计算
        def dfs(v: int) -> int:  # dfs(v)：表示出数值 v 需要的最少运算符个数
            if x >= v:  # 边界：v 不超过 x 时不需要做乘法
                return min(v * 2 - 1, 2 * (x - v))  # v 个 1 相加需 v*2-1 个运算符；用 x 减去差额需 2*(x-v) 个，取较小者
            k = 2  # k 是 x 的幂次，从 x^2 开始尝试
            while x**k < v:  # 不断增大幂次，直到 x^k >= v
                k += 1  # 幂次加一
            if x**k - v < v:  # 若「用 x^k 减去差额」比「凑出 v - x^(k-1)」更省，就走前一种方案
                return min(k + dfs(x**k - v), k - 1 + dfs(v - x ** (k - 1)))  # 两种方案取较小者：用 x^k 减掉差额，或用 k-1 次乘凑出 v - x^(k-1)
            return k - 1 + dfs(v - x ** (k - 1))  # 否则只用方案一：先凑出 x^(k-1)，再补足剩余部分

        return dfs(target)  # 从目标数 target 开始求解
