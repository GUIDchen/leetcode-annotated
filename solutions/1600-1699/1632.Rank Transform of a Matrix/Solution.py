# 题目：1632. 矩阵转换后的排名（Rank Transform of a Matrix）
# 思路：按值从小到大分组，把同值元素所在的行与列用并查集合并，取组内各行列当前最大排名作基准，最后统一写成基准 +1。
# 时间复杂度：O(mn·(log(mn) + α))，排序分组加并查集；空间复杂度：O(mn)，分组表与答案矩阵。
class UnionFind:  # 并查集：把同值的行结点与列结点合并到同一个「连通块」里
    def __init__(self, n):  # 构造函数：n 个结点（这里是 m 行 + n 列）
        self.p = list(range(n))  # p 记录每个结点的父结点，初始时指向自己
        self.size = [1] * n  # size 记录每个根的集合大小，用于按大小合并

    def find(self, x):  # 查找 x 所在集合的根，并做路径压缩
        if self.p[x] != x:  # 父结点不是自己，说明还没到根
            self.p[x] = self.find(self.p[x])  # 递归找根，并把 x 直接挂到根上（路径压缩）
        return self.p[x]  # 返回根结点编号

    def union(self, a, b):  # 合并 a、b 所在集合
        pa, pb = self.find(a), self.find(b)  # 先找到两个结点各自的根
        if pa != pb:  # 根不同才需要合并
            if self.size[pa] > self.size[pb]:  # 比较集合大小，决定把哪一个根挂到另一个根下
                self.p[pb] = pa  # pa 集合更大，把 pb 挂到 pa 下
                self.size[pa] += self.size[pb]  # 更新新根 pa 的集合大小
            else:  # 否则（pb 更大或相等）做反向挂接
                self.p[pa] = pb  # 把 pa 挂到 pb 下
                self.size[pb] += self.size[pa]  # 更新新根 pb 的集合大小

    def reset(self, x):  # 重置单个结点：处理完一组同值元素后，把行/列结点恢复成独立状态
        self.p[x] = x  # 父结点指回自己
        self.size[x] = 1  # 集合大小恢复为 1


class Solution:  # LeetCode 约定的题解类
    def matrixRankTransform(self, matrix: List[List[int]]) -> List[List[int]]:  # matrix 是 m×n 整数矩阵，返回每个位置按题意转换后的排名
        m, n = len(matrix), len(matrix[0])  # m、n 分别为行数与列数
        d = defaultdict(list)  # 分组表：键是矩阵值，值是该值出现的所有坐标
        for i, row in enumerate(matrix):  # 枚举行（i 为行下标，row 为整行）
            for j, v in enumerate(row):  # 枚举列（j 为列下标，v 为该格的值）
                d[v].append((i, j))  # 把坐标 (i,j) 记到值 v 的分组里
        row_max = [0] * m  # row_max[i]：第 i 行目前已知的最大排名
        col_max = [0] * n  # col_max[j]：第 j 列目前已知的最大排名
        ans = [[0] * n for _ in range(m)]  # 答案矩阵，m 行 n 列，初值为 0
        uf = UnionFind(m + n)  # 并查集结点数 = m 个行结点 + n 个列结点，列编号后移 m 以免与行冲突
        for v in sorted(d):  # 按值从小到大处理每一组同值元素
            rank = defaultdict(int)  # rank[root]：该连通块当前的基准排名（每组重新统计）
            for i, j in d[v]:  # 第一遍：同值元素所在的行与列全部合并，表示排名必须相同
                uf.union(i, j + m)  # 该元素所在行与所在列（列号 +m）合并
            for i, j in d[v]:  # 第二遍：取整块内「行最大排名」「列最大排名」与自身基准的最大值，作为新基准
                rank[uf.find(i)] = max(rank[uf.find(i)], row_max[i], col_max[j])  # 同一连通块内反复取 max，把基准统一到全块的最大值上
            for i, j in d[v]:  # 第三遍：把基准 +1 写进答案，并同步更新该行、该列的最大排名
                ans[i][j] = row_max[i] = col_max[j] = 1 + rank[uf.find(i)]  # 三个位置一起赋值：答案格、行最大、列最大
            for i, j in d[v]:  # 第四遍：清空本组用到的行列结点，避免影响下一个更大的值
                uf.reset(i)  # 重置行结点
                uf.reset(j + m)  # 重置列结点（编号 +m）
        return ans  # 返回转换后的排名矩阵
