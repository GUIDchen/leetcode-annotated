# 题目：1042. 不邻接植花（Flower Planting With No Adjacent）
# 思路：建无向邻接表后贪心染色，每个花园只看已染色的邻居用了哪些颜色，从 1..4 里挑第一个没用过的颜色。
# 时间复杂度：O(n + m)，m 为路径数（每个点度数不超过 3）；空间复杂度：O(n + m)，邻接表开销。
class Solution:  # LeetCode 约定的题解类
    def gardenNoAdj(self, n: int, paths: List[List[int]]) -> List[int]:  # n 是花园数（编号 1..n），paths 是相邻关系，返回每个花园种的花（1..4）
        g = defaultdict(list)  # 邻接表：g[i] 自动创建空列表，存与花园 i 相邻的花园下标
        for x, y in paths:  # 遍历每一条相邻关系
            x, y = x - 1, y - 1  # 把 1 基编号统一转成 0 基下标
            g[x].append(y)  # 记录 x 的邻居 y
            g[y].append(x)  # 记录 y 的邻居 x（无向图两个方向都要存）
        ans = [0] * n  # 答案数组，ans[i] 是花园 i 种的花，0 表示还没染色
        for x in range(n):  # 按编号从小到大贪心染色，保证每个点都有可选颜色
            used = {ans[y] for y in g[x]}  # 集合推导式：收集邻居已经用掉的颜色
            for c in range(1, 5):  # 从 1 到 4 挑一个没被邻居占用的颜色
                if c not in used:  # 该颜色可用
                    ans[x] = c  # 给当前花园染上这个颜色
                    break  # 选到即停，处理下一个花园
        return ans  # 返回所有花园的染色结果
