# 题目：1547. 切棍子的最小成本（Minimum Cost to Cut a Stick）
# 思路：把 0 与 n 也放进切点列表并排序，做区间 DP：f[i][j] 表示切完 cuts[i] 到 cuts[j] 这段木棍的最小成本，
# 时间复杂度：O(m^3)（m 为切点个数，枚举区间与切点）；空间复杂度：O(m^2)（DP 表）。
class Solution:  # LeetCode 约定的题解类
    def minCost(self, n: int, cuts: List[int]) -> int:  # n：木棍长度；cuts：所有需要切的切点位置
        cuts.extend([0, n])  # 把木棍的两个端点 0 和 n 也作为切点补进列表
        cuts.sort()  # 升序排序，使相邻切点之间正好是一段完整的木棍
        m = len(cuts)  # 切点总数（原有切点 + 两个端点）
        f = [[0] * m for _ in range(m)]  # f[i][j]：切完 cuts[i]..cuts[j] 这段木棍的最小成本
        for l in range(2, m):  # 枚举区间跨度 l：跨度小于 2 的区间内部没有切点，无需切割
            for i in range(m - l):  # 枚举区间左端点 i（右端点随之确定且不越界）
                j = i + l  # 由左端点与跨度推出右端点 j
                f[i][j] = inf  # 先置为正无穷，便于后续取最小值
                for k in range(i + 1, j):  # 枚举"最后切的一刀"落在 cuts[k] 处
                    f[i][j] = min(f[i][j], f[i][k] + f[k][j] + cuts[j] - cuts[i])  # 左右两段子问题的成本 + 这一刀的代价（当前整段长度）
        return f[0][-1]  # 答案：整根木棍（0 到 n）切完的最小成本
