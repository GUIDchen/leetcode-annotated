# 题目：999. 可以被一步捕获的棋子数（Available Captures for Rook）
# 思路：先定位白车 R，再向上下左右四个方向逐格扫描，遇到边界或黑象 B 即停；遇到第一个黑卒 p 就计数加一并停止该方向。
# 时间复杂度：O(n^2)，n = 8 为棋盘边长；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def numRookCaptures(self, board: List[List[str]]) -> int:  # board：8×8 棋盘；返回白车一步内可吃掉的黑卒个数
        dirs = (-1, 0, 1, 0, -1)  # 方向元组：上、右、下、左的坐标增量
        n = len(board)  # 棋盘边长
        for i in range(n):  # 枚举行
            for j in range(n):  # 枚举列
                if board[i][j] == "R":  # 定位白车 R
                    ans = 0  # 答案计数器：四个方向最多各吃一个
                    for a, b in pairwise(dirs):  # pairwise 把相邻增量配成 (a, b)，得到四个单位方向向量
                        x, y = i + a, j + b  # 该方向上的第一个格子坐标
                        while 0 <= x < n and 0 <= y < n and board[x][y] != "B":  # 不出界且没有被黑象 B 挡住时，才继续扫描
                            if board[x][y] == "p":  # 遇到黑卒 p
                                ans += 1  # 吃子数加一
                                break  # 同一方向最多吃一个，跳出该方向的循环
                            x, y = x + a, y + b  # 沿当前方向再前进一格
                    return ans  # 白车唯一，找到后直接返回答案
