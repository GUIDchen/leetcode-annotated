# 题目：959. 由斜杠划分区域（Regions Cut By Slashes）
# 思路：每个格子拆成上(0)、右(1)、下(2)、左(3)四个小三角形，并查集合并跨格子的相邻边与斜杠同侧的三角形，最后返回连通分量数。
# 时间复杂度：O(n²·α(n²))，并查集近似 O(1) 每次合并；空间复杂度：O(n²)，父数组长度 4n²。
class Solution:  # LeetCode 约定的题解类
    def regionsBySlashes(self, grid: List[str]) -> int:  # grid 是 n×n 的斜杠网格，返回划分出的区域个数
        def find(x):  # 内部函数 find：查并查集里 x 的根，带路径压缩
            if p[x] != x:  # 父亲不是自己，说明还没走到根
                p[x] = find(p[x])  # 递归找根，并把 x 直接挂到根上，压缩后续查询路径
            return p[x]  # 返回根节点

        def union(a, b):  # 内部函数 union：合并 a、b 所在的两个集合
            pa, pb = find(a), find(b)  # 分别求两个节点的根
            if pa != pb:  # 根不同才需要真正合并
                p[pa] = pb  # 把一个根挂到另一个根下
                nonlocal size  # 声明 size 来自外层函数：这里要修改它而不是新建局部变量
                size -= 1  # 连通分量个数减一

        n = len(grid)  # n：网格边长
        size = n * n * 4  # 每个格子拆成 4 个三角形，区域数上限是 n*n*4
        p = list(range(size))  # 并查集初始化：每个节点自成一个集合
        for i, row in enumerate(grid):  # 同时枚举行下标 i 和该行字符串 row
            for j, v in enumerate(row):  # 同时枚举列下标 j 与该位置字符 v
                k = i * n + j  # 二维坐标压成一维格子编号 k
                if i < n - 1:  # 与下一行同一列的格子相邻
                    union(4 * k + 2, (k + n) * 4)  # 本格「下」(4k+2) 接下一行同列格的「上」(4*(k+n))
                if j < n - 1:  # 与右边同一行的格子相邻
                    union(4 * k + 1, (k + 1) * 4 + 3)  # 本格「右」(4k+1) 接右邻格的「左」(4*(k+1)+3)
                if v == '/':  # 正斜杠把「上」与「左」、「右」与「下」分别连成一片
                    union(4 * k, 4 * k + 3)  # 合并「上」(0) 与「左」(3)
                    union(4 * k + 1, 4 * k + 2)  # 合并「右」(1) 与「下」(2)
                elif v == '\\':  # 反斜杠把「上」与「右」、「下」与「左」分别连成一片
                    union(4 * k, 4 * k + 1)  # 合并「上」(0) 与「右」(1)
                    union(4 * k + 2, 4 * k + 3)  # 合并「下」(2) 与「左」(3)
                else:  # 空格不切割格子，四个三角形属于同一片区域
                    union(4 * k, 4 * k + 1)  # 合并「上」与「右」
                    union(4 * k + 1, 4 * k + 2)  # 合并「右」与「下」
                    union(4 * k + 2, 4 * k + 3)  # 合并「下」与「左」
        return size  # 剩余连通分量个数就是区域数量
