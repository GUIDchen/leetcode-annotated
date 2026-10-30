# 题目：2992. 自整除排列的数量（Number of Self-Divisible Permutations）
# 核心思路：状压 DP + 记忆化搜索；mask 的二进制位记录已用的数字，按位置下标 i 从小到大填数，要求 gcd(i, j) == 1。
# 时间复杂度：O(n · 2^n)，每个状态最多枚举 n 个数字；空间复杂度：O(2^n)，cache 保存全部状态。
class Solution:  # LeetCode 约定的题解类
    def selfDivisiblePermutationCount(self, n: int) -> int:  # n 为排列长度，返回满足「每个位置 i 与它上面的数字互质」的排列个数
        @cache  # 给 dfs 加上缓存装饰器，等价于记忆化搜索
        def dfs(mask: int) -> int:  # mask 的二进制位记录已用数字，返回剩余位置的合法填法数
            i = mask.bit_count() + 1  # 已用数字个数加一，就是当前要填的位置下标（从 1 开始）
            if i > n:  # 位置下标超过 n，说明 n 个位置都已填满
                return 1  # 得到一个完整的合法排列，贡献 1 种方案
            ans = 0  # 累加器，统计本状态的方案数
            for j in range(1, n + 1):  # 枚举准备放在位置 i 上的数字 j
                if (mask >> j & 1) == 0 and gcd(i, j) == 1:  # j 未被使用，且与位置 i 互质（gcd 为 1 即满足自整除条件）
                    ans += dfs(mask | 1 << j)  # 把 j 标记为已用后递归，累加后续位置的方案数
            return ans  # 返回本状态的方案数

        return dfs(0)  # 从空掩码出发求解全部方案
