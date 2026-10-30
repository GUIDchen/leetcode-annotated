# 题目：688. 骑士在棋盘上的概率（Knight Probability in Chessboard）
# 思路：概率 DP。f[h][i][j] 表示从 (i, j) 走 h 步后仍在棋盘内的概率，8 个方向各按 1/8 概率回传累加。
# 时间复杂度：O(k·n²)；空间复杂度：O(k·n²)，保存 k+1 层 n×n 的状态。
class Solution:
    def knightProbability(self, n: int, k: int, row: int, column: int) -> float:  # n 是棋盘边长，k 是移动步数，(row, column) 是起始格
        f = [[[0] * n for _ in range(n)] for _ in range(k + 1)]  # 三维 DP 表：f[h][i][j] 表示在 (i, j) 走 h 步后仍在棋盘内的概率，先全部置 0
        for i in range(n):  # 枚举格子行下标
            for j in range(n):  # 枚举格子列下标
                f[0][i][j] = 1  # 走 0 步必然还在棋盘内，概率为 1，作为递推边界
        for h in range(1, k + 1):  # 按步数 1..k 逐层递推
            for i in range(n):  # 枚举当前格子的行
                for j in range(n):  # 枚举当前格子的列
                    for a, b in pairwise((-2, -1, 2, 1, -2, 1, 2, -1, -2)):  # pairwise 把 8 个方向的偏移两两配对成 (dx, dy)，依次遍历 8 种走法
                        x, y = i + a, j + b  # x、y 是上一步的落点（从 (x, y) 走一步才到 (i, j)）
                        if 0 <= x < n and 0 <= y < n:  # 上一步必须仍在棋盘内才合法
                            f[h][i][j] += f[h - 1][x][y] / 8  # 每个来向占 1/8 概率，把上一层概率除以 8 后累加，得到当前位置在 h 步时的概率
        return f[k][row][column]  # 返回从起点出发走满 k 步仍在棋盘内的概率
