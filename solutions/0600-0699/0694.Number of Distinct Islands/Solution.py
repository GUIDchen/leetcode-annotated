# 题目：694. 不同岛屿的数量（Number of Distinct Islands）
# 思路：DFS 染色 + 路径签名。对每座岛按固定方向顺序遍历，进入方向 k 记 +k、离开时记 -k，平移后形状相同的岛会得到同一签名，用集合去重后计数。
# 时间复杂度：O(m·n)，每个格子最多访问一次；空间复杂度：O(m·n)，签名列表与递归栈。
class Solution:
    def numDistinctIslands(self, grid: List[List[int]]) -> int:  # grid 为 0/1 矩阵，返回形状互不相同的岛屿数量
        def dfs(i: int, j: int, k: int):  # 内部 DFS：i、j 为当前格子，k 为进入该格子的方向编号
            grid[i][j] = 0  # 把当前格子置 0，表示已访问
            path.append(str(k))  # 进入方向写入路径签名，记录「从哪来」
            dirs = (-1, 0, 1, 0, -1)  # 四个方向按「上、右、下、左」环形排列，末尾重复首元素便于相邻配对
            for h in range(1, 5):  # 依次尝试四个方向，h 同时作为子方向编号
                x, y = i + dirs[h - 1], j + dirs[h]  # 计算邻格坐标：dirs[h-1]、dirs[h] 组成一个方向偏移
                if 0 <= x < m and 0 <= y < n and grid[x][y]:  # 邻格在界内且为陆地才继续深搜
                    dfs(x, y, h)  # 递归访问邻格，把方向编号 h 传下去
            path.append(str(-k))  # 离开时记录相反方向，使不同形状的签名不会碰撞

        paths = set()  # 集合保存每座岛的形状签名，自动去重
        path = []  # 当前岛屿的签名列表
        m, n = len(grid), len(grid[0])  # m、n 分别是网格行数与列数
        for i, row in enumerate(grid):  # 按行遍历网格，i 是行号、row 是该行内容
            for j, x in enumerate(row):  # 按列遍历该行，j 是列号、x 是格子值
                if x:  # 遇到陆地说明发现一座新岛
                    dfs(i, j, 0)  # 从该格开始 DFS，起点方向记为 0
                    paths.add("".join(path))  # 把签名列表拼成字符串放入集合
                    path.clear()  # 清空签名，准备记录下一座岛
        return len(paths)  # 集合大小即不同形状的岛屿数量
