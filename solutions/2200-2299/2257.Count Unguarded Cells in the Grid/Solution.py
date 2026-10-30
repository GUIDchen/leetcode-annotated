# 题目：2257. 统计网格图中没有被保卫的格子数（Count Unguarded Cells in the Grid）
# 思路：用二维标记表（2 = 守卫或墙，1 = 已被保卫，0 = 未保卫），从每个守卫向四个方向直线延伸，遇到墙或守卫即停。
# 时间复杂度：O(m * n + g * (m + n))；空间复杂度：O(m * n)，标记表与网格同规模。
class Solution:  # LeetCode 约定的题解类
    def countUnguarded(  # 统计网格中未被保卫的格子数
        self, m: int, n: int, guards: List[List[int]], walls: List[List[int]]  # m 行 n 列；guards 是守卫坐标，walls 是墙坐标
    ) -> int:  # 返回未被任何守卫看到的格子数量
        g = [[0] * n for _ in range(m)]  # 初始化标记表：0 表示未保卫，之后用 1 表示已保卫、2 表示守卫或墙
        for i, j in guards:  # 遍历守卫坐标
            g[i][j] = 2  # 守卫所在格子标 2：阻挡视线，也不计入答案
        for i, j in walls:  # 遍历墙坐标
            g[i][j] = 2  # 墙同样阻挡视线，一并标成 2
        dirs = (-1, 0, 1, 0, -1)  # 方向数组，相邻两项组成 (上、右、下、左) 的行列增量
        for i, j in guards:  # 以每个守卫为扫描起点
            for a, b in pairwise(dirs):  # pairwise 把方向数组两两配对，得到四个方向向量
                x, y = i, j  # 当前位置从守卫自身出发
                while 0 <= x + a < m and 0 <= y + b < n and g[x + a][y + b] < 2:  # 下一格在界内且不是守卫或墙，就继续前进
                    x, y = x + a, y + b  # 走到下一格
                    g[x][y] = 1  # 该格被这个守卫看到，标记为已保卫
        return sum(v == 0 for row in g for v in row)  # 统计整张表中仍为 0（未被保卫）的格子数
