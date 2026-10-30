# 题目：1434. 每个人戴不同帽子的方案数（Number of Ways to Wear Different Hats to Each Other）
# 思路：按帽子编号从小到大做状态压缩 DP，f[i][j] 表示只考虑前 i 顶帽子、已戴帽子的人集合为 j 的方案数。
# 时间复杂度：O(m 2^n + 总喜好数)；空间复杂度：O(m 2^n)，二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def numberWays(self, hats: List[List[int]]) -> int:  # hats[i] 是第 i 个人喜欢的帽子编号列表，返回让每人戴不同帽子的方案数
        g = defaultdict(list)  # 把「人 → 帽子」翻转成「帽子 → 人」，便于按帽子递推
        for i, h in enumerate(hats):  # 逐个处理每个人（i 是其下标，也对应状态压缩中的第 i 位）
            for v in h:  # 处理他喜欢的每一顶帽子
                g[v].append(i)  # 把这个人加入该帽子的候选列表
        mod = 10**9 + 7  # 方案数取模，防止溢出
        n = len(hats)  # n：人数，也是状态压缩的位数
        m = max(max(h) for h in hats)  # m：所有喜好中最大的帽子编号，决定要枚举多少顶帽子
        f = [[0] * (1 << n) for _ in range(m + 1)]  # 状态表：f[i][j] 为前 i 顶帽子、已戴帽子的集合为 j 的方案数
        f[0][0] = 1  # 边界：0 顶帽子、没人戴帽子，只有 1 种方案（什么都不做）
        for i in range(1, m + 1):  # 按帽子编号从小到大递推
            for j in range(1 << n):  # 枚举已戴帽子的所有可能集合 j
                f[i][j] = f[i - 1][j]  # 本顶帽子不选：方案数完全继承上一顶帽子的结果
                for k in g[i]:  # 尝试把帽子 i 分给喜欢它的某个人 k
                    if j >> k & 1:  # 只有当 j 中已包含 k（第 k 位为 1）时才可能由更小的集合转移来
                        f[i][j] = (f[i][j] + f[i - 1][j ^ (1 << k)]) % mod  # 去掉 k 这一位，表示 k 在本步才戴上帽子；累加并取模
        return f[m][-1]  # f[m][-1] 即集合为全 1（所有人都戴上帽子）的方案数
