# 题目：3193. 统计逆序对的数目（Count the Number of Inversions）
# 思路：按前缀长度做 DP，f[i][j] 表示长度 i+1、逆序对数为 j 的排列个数；插入新元素会新增 k 个逆序对，用 requirements 限制每层可取的值。
# 时间复杂度：O(n·m·n)（m 为约束中的最大逆序对数）；空间复杂度：O(n·m)，即二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def numberOfPermutations(self, n: int, requirements: List[List[int]]) -> int:  # n：排列长度；requirements：每个前缀下标的逆序对数约束
        req = [-1] * n  # req[i] 表示长度 i+1 的前缀要求的逆序对数，-1 表示没有约束
        for end, cnt in requirements:  # 遍历每条约束（前缀末下标、逆序对数）
            req[end] = cnt  # 把约束记录到对应位置
        if req[0] > 0:  # 只有一个元素时不可能产生逆序对
            return 0  # 约束矛盾，没有合法排列
        req[0] = 0  # 长度 1 的前缀逆序对数固定为 0
        mod = 10**9 + 7  # 取模常量，避免答案过大
        m = max(req)  # dp 的列上界：所有约束里最大的逆序对数
        f = [[0] * (m + 1) for _ in range(n)]  # f[i][j]：长度 i+1 且逆序对数为 j 的排列个数
        f[0][0] = 1  # 边界：单个元素且逆序对为 0 的方案数为 1
        for i in range(1, n):  # 依次把前缀长度扩展到 1..n
            l, r = 0, m  # 本层允许枚举的逆序对数区间
            if req[i] >= 0:  # 该前缀被 requirements 约束
                l = r = req[i]  # 只计算被约束的唯一取值
            for j in range(l, r + 1):  # 枚举当前前缀允许的逆序对数 j
                for k in range(min(i, j) + 1):  # 枚举新增的逆序对数 k，范围 0..min(i, j)
                    f[i][j] = (f[i][j] + f[i - 1][j - k]) % mod  # 从上一层累加转移并取模
        return f[n - 1][req[n - 1]]  # 返回满足全部约束的排列方案数
