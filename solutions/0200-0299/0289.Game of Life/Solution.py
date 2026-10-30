# 题目：289. 生命游戏（Game of Life）—— 按规则把细胞矩阵原地更新为下一代状态（活细胞邻居数决定生死）。
# 核心思路：用状态编码省去额外数组——2 表示“活→死”，-1 表示“死→活”；统计邻居时只看值是否 > 0，兼容旧状态。
# 时间复杂度：O(m·n)，每格检查 3×3 邻域；空间复杂度：O(1)，原地完成。
class Solution:  # LeetCode 约定的题解类
    def gameOfLife(self, board: List[List[int]]) -> None:  # board：原地更新，0 表示死、1 表示活
        m, n = len(board), len(board[0])  # 行数、列数
        for i in range(m):  # 枚举每一行
            for j in range(n):  # 枚举每一列
                live = -board[i][j]  # 先扣掉自己，因为下面的 3×3 邻域会包含自身
                for x in range(i - 1, i + 2):  # 邻域行：i-1、i、i+1
                    for y in range(j - 1, j + 2):  # 邻域列：j-1、j、j+1
                        if 0 <= x < m and 0 <= y < n and board[x][y] > 0:  # 不越界，且上一代是活细胞（1 或中间态 2）
                            live += 1  # 活邻居数加一
                if board[i][j] and (live < 2 or live > 3):  # 真值判断：当前是活细胞，且邻居不足 2 或超过 3 → 下一代死亡
                    board[i][j] = 2  # 2 表示“活→死”，值 > 0 仍会被算作活
                if board[i][j] == 0 and live == 3:  # 当前是死细胞且恰有 3 个活邻居 → 下一代复活
                    board[i][j] = -1  # -1 表示“死→活”，值 <= 0 仍会被算作死
        for i in range(m):  # 第二遍扫描：把中间状态还原成 0/1
            for j in range(n):  # 枚举每一列
                if board[i][j] == 2:  # 处于“活→死”中间态
                    board[i][j] = 0  # 还原成死
                elif board[i][j] == -1:  # 处于“死→活”中间态
                    board[i][j] = 1  # 还原成活
