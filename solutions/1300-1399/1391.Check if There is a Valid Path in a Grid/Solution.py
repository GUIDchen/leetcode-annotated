# 题目：1391. 检查网格中是否存在有效路径（Check if There is a Valid Path in a Grid）
# 思路：并查集；对每个格子的管道类型检查它与左、右、上、下邻居能否对接（邻居必须有朝向本格的开口），能对接就合并，最后看起点与终点是否同根。
# 时间复杂度：O(m*n*α(m*n))，带路径压缩的 find 近似常数；空间复杂度：O(m*n)，父数组 p。
class Solution:  # LeetCode 约定的题解类
    def hasValidPath(self, grid: List[List[int]]) -> bool:  # grid 的每个元素是 1~6 的管道类型
        m, n = len(grid), len(grid[0])  # m 行 n 列
        p = list(range(m * n))  # 并查集父数组，初始每个格子自成一个集合

        def find(x):  # 并查集查找，带路径压缩
            if p[x] != x:  # x 不是根节点
                p[x] = find(p[x])  # 递归找到根，并把 x 直接挂到根上（路径压缩）
            return p[x]  # 返回根节点

        def left(i, j):  # 尝试把当前格与左邻居合并
            if j > 0 and grid[i][j - 1] in (1, 4, 6):  # 左邻居存在，且它的右侧有开口（类型 1、4、6 才有右出口）
                p[find(i * n + j)] = find(i * n + j - 1)  # 合并当前格与左邻居所在集合

        def right(i, j):  # 尝试把当前格与右邻居合并
            if j < n - 1 and grid[i][j + 1] in (1, 3, 5):  # 右邻居存在，且它的左侧有开口（类型 1、3、5 才有左出口）
                p[find(i * n + j)] = find(i * n + j + 1)  # 合并当前格与右邻居所在集合

        def up(i, j):  # 尝试把当前格与上邻居合并
            if i > 0 and grid[i - 1][j] in (2, 3, 4):  # 上邻居存在，且它的下方有开口（类型 2、3、4 才有下出口）
                p[find(i * n + j)] = find((i - 1) * n + j)  # 合并当前格与上邻居所在集合

        def down(i, j):  # 尝试把当前格与下邻居合并
            if i < m - 1 and grid[i + 1][j] in (2, 5, 6):  # 下邻居存在，且它的上方有开口（类型 2、5、6 才有上出口）
                p[find(i * n + j)] = find((i + 1) * n + j)  # 合并当前格与下邻居所在集合

        for i in range(m):  # 逐行遍历网格
            for j in range(n):  # 逐列遍历网格
                e = grid[i][j]  # 当前格子的管道类型
                if e == 1:  # 类型 1：左右直通
                    left(i, j)  # 与左邻居连通
                    right(i, j)  # 与右邻居连通
                elif e == 2:  # 类型 2：上下直通
                    up(i, j)  # 与上邻居连通
                    down(i, j)  # 与下邻居连通
                elif e == 3:  # 类型 3：左 + 下
                    left(i, j)  # 与左邻居连通
                    down(i, j)  # 与下邻居连通
                elif e == 4:  # 类型 4：右 + 下
                    right(i, j)  # 与右邻居连通
                    down(i, j)  # 与下邻居连通
                elif e == 5:  # 类型 5：左 + 上
                    left(i, j)  # 与左邻居连通
                    up(i, j)  # 与上邻居连通
                else:  # 类型 6：右 + 上
                    right(i, j)  # 与右邻居连通
                    up(i, j)  # 与上邻居连通
        return find(0) == find(m * n - 1)  # 起点与终点同属一个集合，说明存在有效路径
