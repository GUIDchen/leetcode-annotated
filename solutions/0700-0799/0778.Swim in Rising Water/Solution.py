# 题目：778. 水位上升的泳池中游泳（Swim in Rising Water）
# 思路：按高度从小到大逐格淹没，用并查集维护已淹没格子的连通性；当起点 0 与终点 m-1 属于同一集合时，当前水位 t 即答案。
# 时间复杂度：O(n^2·α(n^2))，每格只被淹没一次；空间复杂度：O(n^2)，并查集 p 与高度索引 hi 各占 n^2。
class Solution:  # LeetCode 约定的题解类
    def swimInWater(self, grid: List[List[int]]) -> int:  # grid：高度矩阵；返回从左上角游到右下角所需的最小时间
        def find(x: int) -> int:  # 嵌套函数 find：带路径压缩的并查集查找，直接读取外层的 p
            if p[x] != x:  # 根节点满足 p[x] == x，不等就还没找到根
                p[x] = find(p[x])  # 递归找到根，并让 p[x] 直接指向根，完成路径压缩
            return p[x]  # 返回压缩后的根

        n = len(grid)  # n：矩阵边长
        m = n * n  # m：格子总数，也是高度上界 +1
        p = list(range(m))  # p：并查集父指针，初始每个格子自成一个集合
        hi = [0] * m  # hi：按高度存放格子编号，之后按 t 递增顺序淹没
        for i, row in enumerate(grid):  # 枚举行，row 是当前行；i 是行号
            for j, h in enumerate(row):  # 枚举列，h 是该格子的高度
                hi[h] = i * n + j  # 把高度 h 映射到格子编号 i*n+j
        dirs = (-1, 0, 1, 0, -1)  # 四方向偏移量，相邻两个数拼成一个方向，配合 pairwise 两两取用
        for t in range(m):  # 水位 t 从 0 递增到 m-1，逐格淹没
            x, y = divmod(hi[t], n)  # 把高度为 t 的格子编号拆成行列坐标（divmod 同时得到商和余数）
            for dx, dy in pairwise(dirs):  # pairwise 依次给出四个方向向量 (dx, dy)
                nx, ny = x + dx, y + dy  # 邻居格子的坐标
                if 0 <= nx < n and 0 <= ny < n and grid[nx][ny] <= t:  # 邻居越界则跳过；高度 > t 说明它还没被淹没，水过不去
                    p[find(x * n + y)] = find(nx * n + ny)  # 把当前格所在集合的根挂到邻居格的根下，两者连通
            if find(0) == find(m - 1):  # 起点与终点已经连通，说明此刻可以游到终点
                return t  # 最早可行的水位 t 就是答案
        return 0  # 兜底返回：t=m-1 时全图连通，正常不会走到这里
