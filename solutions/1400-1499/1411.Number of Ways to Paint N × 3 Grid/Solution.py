# 题目：1411. 给 N x 3 网格图涂色的方案数（Number of Ways to Paint N × 3 Grid）
# 思路：把每行配色分成首尾同色的 ABA 型与三色互异的 ABC 型，按固定系数逐行滚动递推。
# 时间复杂度：O(n)，共 n-1 次常数级迭代；空间复杂度：O(1)，只保存两个计数。
class Solution:  # LeetCode 约定的题解类
    def numOfWays(self, n: int) -> int:  # n 是网格行数，返回合法涂色方案数对 1e9+7 取模的结果
        mod = 10**9 + 7  # 取模常量，防止结果过大
        f0 = f1 = 6  # 第一行两类配色各 6 种：f0 首尾同色，f1 三色互异
        for _ in range(n - 1):  # 逐行向上推 n-1 次，每轮由上一行算出下一行
            g0 = (3 * f0 + 2 * f1) % mod  # 新的 ABA 型：3 倍 ABA 型加 2 倍 ABC 型
            g1 = (2 * f0 + 2 * f1) % mod  # 新的 ABC 型：2 倍 ABA 型加 2 倍 ABC 型
            f0, f1 = g0, g1  # 同时赋值覆盖，避免两个状态互相污染
        return (f0 + f1) % mod  # 两类方案相加再取模
