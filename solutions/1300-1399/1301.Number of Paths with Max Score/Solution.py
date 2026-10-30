# 题目：1301. 最大得分的路径数目（Number of Paths with Max Score）
# 思路：从右下角往左上角做网格 DP，f[i][j] 是到终点的最大得分（-1 表示不可达），g[i][j] 是取到该得分的方案数。
# 时间复杂度：O(n^2)，每个格子只向三个方向转移；空间复杂度：O(n^2)，两个 n×n 数组。
class Solution:  # LeetCode 约定的题解类
    def pathsWithMaxScore(self, board: List[str]) -> List[int]:  # board：棋盘，'S' 起点、'E' 终点、'X' 障碍、数字为分数
        def update(i, j, x, y):  # 用相邻格子 (x,y) 的结果去更新 (i,j)
            if x >= n or y >= n or f[x][y] == -1 or board[i][j] in "XS":  # 越界、后继不可达，或当前格是障碍/起点
                return  # 不做任何转移
            if f[x][y] > f[i][j]:  # 后继给的得分更高，直接替换
                f[i][j] = f[x][y]  # 更新最大得分
                g[i][j] = g[x][y]  # 方案数跟着替换
            elif f[x][y] == f[i][j]:  # 两条路线得分相同，方案数累加
                g[i][j] += g[x][y]  # 累加方案数

        n = len(board)  # 棋盘边长
        f = [[-1] * n for _ in range(n)]  # 最大得分表，全部初始化为不可达
        g = [[0] * n for _ in range(n)]  # 方案数表，全部初始化为 0
        f[-1][-1], g[-1][-1] = 0, 1  # 终点自身得分 0，路径数 1（空路径）
        for i in range(n - 1, -1, -1):  # 从最后一行往上推
            for j in range(n - 1, -1, -1):  # 从最后一列往左推
                update(i, j, i + 1, j)  # 转移到下方格子
                update(i, j, i, j + 1)  # 转移到右方格子
                update(i, j, i + 1, j + 1)  # 转移到右下对角格子
                if f[i][j] != -1 and board[i][j].isdigit():  # 该格子可达且是数字格
                    f[i][j] += int(board[i][j])  # 把该格的分数加上去
        mod = 10**9 + 7  # 方案数取模
        return [0, 0] if f[0][0] == -1 else [f[0][0], g[0][0] % mod]  # 起点不可达返回 [0,0]，否则返回得分与取模后的方案数
