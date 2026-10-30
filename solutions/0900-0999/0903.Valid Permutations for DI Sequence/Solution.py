# 题目：903. DI 序列的有效排列（Valid Permutations for DI Sequence）
# 核心思路：区间 DP，f[i][j] 表示长度 i+1、末位元素排第 j 小的合法排列数，按 s[i-1] 是 D 还是 I 转移。
# 时间复杂度：O(n^3)，三重循环；空间复杂度：O(n^2) 的 DP 表。
class Solution:  # LeetCode 约定的题解类
    def numPermsDISequence(self, s: str) -> int:  # s：由 'D' 与 'I' 组成的序列
        mod = 10**9 + 7  # 取模常数，防止结果溢出
        n = len(s)  # 序列长度，排列长度为 n + 1
        f = [[0] * (n + 1) for _ in range(n + 1)]  # DP 表：f[i][j] 表示长度 i + 1 且末位排第 j 小的方案数
        f[0][0] = 1  # 只有 1 个数字时，唯一排列的末位排第 0 小
        for i, c in enumerate(s, 1):  # 逐步把排列长度从 1 扩到 n + 1
            if c == "D":  # 关系是下降，新加元素排在原末位之前
                for j in range(i + 1):  # 枚举新排列末位元素的排名 j
                    for k in range(j, i):  # 原末位排名 k 必须不小于 j 才能插到它前面
                        f[i][j] = (f[i][j] + f[i - 1][k]) % mod  # 累加所有可转移的前驱状态并取模
            else:  # 关系是上升，新加元素排在原末位之后
                for j in range(i + 1):  # 枚举新排列末位元素的排名 j
                    for k in range(j):  # 原末位排名 k 必须小于 j 才能插到它后面
                        f[i][j] = (f[i][j] + f[i - 1][k]) % mod  # 累加所有可转移的前驱状态并取模
        return sum(f[n][j] for j in range(n + 1)) % mod  # 汇总末位取任意排名的方案数并取模
