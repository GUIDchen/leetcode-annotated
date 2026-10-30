# 3821. Find Nth Smallest Integer With K One Bits | 3821. 二进制中恰好 K 个 1 的第 N 小整数
# 核心思路：组合数打表，从最高位向最低位用 C(i, k) 整块跳过，逐位贪心构造第 n 个数
# 复杂度：预处理 O(mx^2)，单次查询 O(50)，额外空间 O(mx^2)
mx = 50  # 组合数表的最大规模（按 50 位处理）
c = [[0] * (mx + 1) for _ in range(mx)]  # c[i][j] 表示从 i 个位置里选 j 个位置放 1 的方案数
for i in range(mx):  # 枚举行 i
    c[i][0] = 1  # 从 i 个位置里选 0 个位置放 1，只有 1 种方案
    for j in range(1, i + 1):  # 枚举列 j
        c[i][j] = c[i - 1][j - 1] + c[i - 1][j]  # 杨辉三角递推：不选第 i 个 + 选第 i 个


class Solution:
    def nthSmallest(self, n: int, k: int) -> int:  # 求恰好含 k 个 1 的第 n 小正整数
        ans = 0  # 答案：逐位构造出来的数
        for i in range(49, -1, -1):  # 从最高位 49 向最低位 0 逐位贪心
            if n > c[i][k]:  # 最高位取 0 时后面 i 位放 k 个 1 仍有 C(i,k) 种，若不足 n 说明目标在取 1 的那一批里
                n -= c[i][k]  # 跳过最高位取 0 的那 C(i,k) 个数
                ans |= 1 << i  # 确认第 i 位置 1
                k -= 1  # 待放置的 1 的个数减一
                if k == 0:  # k 个 1 是否已全部放完
                    break  # 已放完则剩下的低位补 0
        return ans  # 返回第 n 小的数
