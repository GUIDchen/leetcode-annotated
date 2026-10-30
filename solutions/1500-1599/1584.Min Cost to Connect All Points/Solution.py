# 题目：1584. 连接所有点的最小费用（Min Cost to Connect All Points）
# 思路：把点看作完全图，边权为曼哈顿距离，再用 Prim 算法求最小生成树的边权和。
# 时间复杂度：O(n^2)，每轮线性找最近点；空间复杂度：O(n^2)，邻接矩阵。
class Solution:  # LeetCode 约定的题解类
    def minCostConnectPoints(self, points: List[List[int]]) -> int:  # points 为平面上各点的坐标
        n = len(points)  # 点的个数
        g = [[0] * n for _ in range(n)]  # 邻接矩阵，g[i][j] 为两点间的曼哈顿距离
        dist = [inf] * n  # Prim：dist[j] 为 j 到生成树的最短边权，inf 表示还不知道
        vis = [False] * n  # vis[j] 表示 j 是否已加入生成树
        for i, (x1, y1) in enumerate(points):  # 枚举边的一个端点，同时解包出坐标
            for j in range(i + 1, n):  # 只取 j > i，无向边不重复算
                x2, y2 = points[j]  # 另一个端点的坐标
                t = abs(x1 - x2) + abs(y1 - y2)  # 费用为曼哈顿距离
                g[i][j] = g[j][i] = t  # 对称写入矩阵的两个方向
        dist[0] = 0  # 从 0 号点开始，入树代价为 0
        ans = 0  # 最小生成树的总费用
        for _ in range(n):  # 循环 n 次，每次加入一个点
            i = -1  # i 记录本轮 dist 最小的未访问点
            for j in range(n):  # 线性扫描找最近的点
                if not vis[j] and (i == -1 or dist[j] < dist[i]):  # 未访问且距离更小
                    i = j  # 更新候选点
            vis[i] = True  # 把 i 并入生成树
            ans += dist[i]  # 累加这条最短的连接边
            for j in range(n):  # 用 i 松弛其余未访问点的入树距离
                if not vis[j]:  # 只更新还在树外的点
                    dist[j] = min(dist[j], g[i][j])  # 取更短的入树边权
        return ans  # 返回最小总费用
