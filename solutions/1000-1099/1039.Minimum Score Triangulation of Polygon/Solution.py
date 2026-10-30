# 题目：1039. 多边形三角剖分的最低得分（Minimum Score Triangulation of Polygon）
# 思路：区间 DP 记忆化搜索，枚举边 (i, j) 对应的三角形第三个顶点 k，把多边形拆成两个子区间递归求解，答案是各三角形顶点乘积之和的最小值。
# 时间复杂度：O(n^3)，共 O(n^2) 个区间、每个区间枚举 O(n) 个 k；空间复杂度：O(n^2)，cache 保存所有区间结果。
class Solution:  # LeetCode 约定的题解类
    def minScoreTriangulation(self, values: List[int]) -> int:  # values 是多边形各顶点的值，返回最低三角剖分得分
        @cache  # @cache 自动记忆化，同一组 (i, j) 只计算一次
        def dfs(i: int, j: int) -> int:  # 递归函数：下标 i 到 j 这一段多边形的最低得分
            if i + 1 == j:  # 只剩一条边（i 与 j 相邻），无法再剖分出三角形
                return 0  # 没有三角形产生，得分为 0
            return min(  # 对每个分割点 k 求出剖分总得分并取最小值
                dfs(i, k) + dfs(k, j) + values[i] * values[k] * values[j]  # 子区间 i..k 与 k..j 的得分，加上三角形 (i, k, j) 的顶点乘积
                for k in range(i + 1, j)  # 枚举 i 与 j 之间的所有分割点 k
            )  # min 调用的括号收尾

        return dfs(0, len(values) - 1)  # 从整个多边形的首尾下标开始求解
