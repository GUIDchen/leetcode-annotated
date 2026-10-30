# 题目：600. 不含连续 1 的非负整数（Non-negative Integers without Consecutive Ones）
# 思路：数位 DP，从最高位向下决定每一位填 0 还是 1，用 pre 记录上一位、limit 记录是否贴住 n 的二进制上界，并用 cache 记忆化。
# 时间复杂度：O(log n)，状态数为位数 × 2；空间复杂度：O(log n)，缓存与递归深度。
class Solution:  # LeetCode 约定的题解类
    def findIntegers(self, n: int) -> int:  # 统计 [0, n] 范围内二进制不含相邻 1 的整数个数
        @cache  # 装饰器缓存 dfs 的结果，避免同一个子问题被反复计算
        def dfs(i: int, pre: int, limit: bool) -> int:  # i 是当前位数，pre 是上一位取值，limit 表示是否贴着 n 的上界
            if i < 0:  # 所有位都填完了，说明得到一个合法整数
                return 1  # 这种填法贡献 1 种方案
            up = (n >> i & 1) if limit else 1  # 受限时当前位最多取 n 的对应位，不受限时 0 和 1 都能取
            ans = 0  # 累计当前状态的方案数
            for j in range(up + 1):  # 枚举当前位填入的取值 j
                if pre and j:  # 上一位是 1 且当前位也填 1，会出现连续的两个 1
                    continue  # 该填法非法，跳过
                ans += dfs(i - 1, j, limit and j == up)  # 递归下一位；只有原本受限且当前位取到上界时，才继续受限
            return ans  # 返回当前状态下的全部合法方案数

        return dfs(n.bit_length() - 1, 0, True)  # 从 n 的最高位开始枚举，上一位记为 0，并且一开始紧贴上界
