# 题目：2318. 不同骰子序列的数目（Number of Distinct Roll Sequences）
# 核心思路：动态规划，dp[k][i][j] 表示长度为 k、末两面为 i+1 与 j+1 的合法序列数；转移时枚举倒数第三面 h，检查相邻互质且两两不等。
# 时间复杂度：O(n·6³)；空间复杂度：O(n·6²)，三维 dp 表。
class Solution:  # LeetCode 约定的题解类
    def distinctSequences(self, n: int) -> int:  # n：骰子投掷次数；返回相邻两面互质且互不相同的序列数目
        if n == 1:  # 只有 1 次投掷时，6 个面各成一种序列，直接返回 6
            return 6  # 直接返回 6
        mod = 10**9 + 7  # 取模常量，防止累加溢出
        dp = [[[0] * 6 for _ in range(6)] for _ in range(n + 1)]  # dp[k][i][j]：长度 k、末两面为点数 i+1 与 j+1 的合法序列数，先全部置 0
        for i in range(6):  # 枚举倒数第二个面的下标 i（0..5 对应点数 1..6）
            for j in range(6):  # 枚举最后一个面的下标 j
                if gcd(i + 1, j + 1) == 1 and i != j:  # 长度为 2 的合法条件：相邻两面互质且互不相同
                    dp[2][i][j] = 1  # 长度为 2 时每种合法组合恰好 1 种序列
        for k in range(3, n + 1):  # 从长度 3 开始逐层递推到长度 n
            for i in range(6):  # 枚举新序列末两面的前一个面 i
                for j in range(6):  # 枚举新序列末两面的后一个面 j
                    if gcd(i + 1, j + 1) == 1 and i != j:  # 末两面 (i, j) 也必须互质且不相等
                        for h in range(6):  # 枚举倒数第三个面 h，作为转移来源
                            if gcd(h + 1, i + 1) == 1 and h != i and h != j:  # 转移合法：h 与 i 互质，且 h 不等于 i（相邻不等）也不等于 j（间隔两面不等）
                                dp[k][i][j] += dp[k - 1][h][i]  # 由上一状态 dp[k-1][h][i] 转移累加，循环中暂不取模以减少运算
        ans = 0  # 答案累加器，初始为 0
        for i in range(6):  # 枚举长度 n 序列的倒数第二个面 i
            for j in range(6):  # 枚举长度 n 序列的最后一个面 j
                ans += dp[-1][i][j]  # 长度 n 的末两面为 (i, j)，把对应方案数全部累加
        return ans % mod  # 累加和最后统一取模后返回
