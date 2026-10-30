# 题目：1631. 最小体力消耗路径（Path With Minimum Effort）
# 思路：把相邻格子的高度差当成边权，按边权从小到大做 Kruskal 连通，起点与终点首次连通时的边权就是最小体力消耗。
# 时间复杂度：O(mn·log(mn))，边数约 2mn，排序主导；空间复杂度：O(mn)，存边表与并查集数组。
class UnionFind:  # 并查集：维护连通分量，支持按大小合并与路径压缩
    def __init__(self, n):  # 构造函数：n 个结点，初始各自独立
        self.p = list(range(n))  # p 记录每个结点的父结点，初始时指向自己
        self.size = [1] * n  # size 记录每个根的集合大小，用于小集合挂到大集合上

    def find(self, x):  # 查找 x 所在集合的根，并做路径压缩
        if self.p[x] != x:  # 父结点不是自己，说明还没到根
            self.p[x] = self.find(self.p[x])  # 递归找根，并把 x 直接挂到根上（路径压缩）
        return self.p[x]  # 返回根结点编号

    def union(self, a, b):  # 合并 a、b 所在集合；返回 False 表示原本已连通
        pa, pb = self.find(a), self.find(b)  # 先找到两个结点各自的根
        if pa == pb:  # 根相同说明已在同一集合
            return False  # 无需合并
        if self.size[pa] > self.size[pb]:  # 比较集合大小，决定把哪一个根挂到另一个根下
            self.p[pb] = pa  # pa 集合更大，把 pb 挂到 pa 下
            self.size[pa] += self.size[pb]  # 更新新根 pa 的集合大小
        else:  # 否则（pb 更大或相等）做反向挂接
            self.p[pa] = pb  # 把 pa 挂到 pb 下
            self.size[pb] += self.size[pa]  # 更新新根 pb 的集合大小
        return True  # 合并成功

    def connected(self, a, b):  # 判断 a、b 是否连通
        return self.find(a) == self.find(b)  # 两者根相同即连通


class Solution:  # LeetCode 约定的题解类
    def minimumEffortPath(self, heights: List[List[int]]) -> int:  # heights 是 m×n 的高度矩阵，返回从左上角到右下角的最小体力消耗
        m, n = len(heights), len(heights[0])  # m、n 分别为行数与列数
        uf = UnionFind(m * n)  # 并查集初始化 mn 个格子结点（编号 i*n+j）
        e = []  # 边表：元素为 (高度差, 起点编号, 终点编号)
        dirs = (0, 1, 0)  # 方向元组：配合 pairwise 依次得到 (0,1) 向右 与 (1,0) 向下
        for i in range(m):  # 枚举行
            for j in range(n):  # 枚举列
                for a, b in pairwise(dirs):  # 依次取相邻两方向（右、下），避免重复建边
                    x, y = i + a, j + b  # 由当前格 (i,j) 与方向得到相邻格 (x,y)
                    if 0 <= x < m and 0 <= y < n:  # 边界检查：相邻格必须仍在矩阵内
                        e.append(  # 追加一条边；元组会自动按第一个元素（高度差）优先排序
                            (abs(heights[i][j] - heights[x][y]), i * n + j, x * n + y)  # 续行：高度差的绝对值、两端的压平编号
                        )  # appending 调用结束
        e.sort()  # 按边权升序排序：Kruskal 从小到大加边
        for h, a, b in e:  # 依次处理每条边，h 为高度差，a/b 为两端结点编号
            uf.union(a, b)  # 合并这条边两端的集合
            if uf.connected(0, m * n - 1):  # 检查起点 0 与终点 mn-1 是否已经连通
                return h  # 首次连通时刚加入的边权 h 就是该路径的最大高度差，即最小体力消耗
        return 0  # 只有 1 个格子（或无需移动）时消耗为 0
