# 题目：529. 扫雷游戏（Minesweeper）
# 思路：DFS 洪水填充。点到地雷直接改 X；否则数周围 8 格的地雷数，为 0 才继续向四周扩散。
# 时间复杂度：O(m*n)，每个格子至多被挖开一次；空间复杂度：O(m*n)，递归栈最坏深度。
class Solution:  # LeetCode 约定的题解类
    def updateBoard(self, board: List[List[str]], click: List[int]) -> List[List[str]]:  # board 是棋盘，click 是点击坐标
        def dfs(i: int, j: int):  # 内层递归函数：挖开格子 (i,j)，直接闭包修改 board
            cnt = 0  # 统计周围 8 格里的地雷数
            for x in range(i - 1, i + 2):  # 枚举行偏移 -1、0、1
                for y in range(j - 1, j + 2):  # 枚举列偏移 -1、0、1
                    if 0 <= x < m and 0 <= y < n and board[x][y] == "M":  # 先判越界，再看是不是未引爆地雷
                        cnt += 1  # 地雷计数加一
            if cnt:  # 周围有地雷，到此为止
                board[i][j] = str(cnt)  # 把地雷数写成字符；题目棋盘用字符串表示
            else:  # 周围没有地雷，标 B 并继续扩散
                board[i][j] = "B"  # B 表示挖开的空白格
                for x in range(i - 1, i + 2):  # 再遍历 8 邻域
                    for y in range(j - 1, j + 2):  # 同上
                        if 0 <= x < m and 0 <= y < n and board[x][y] == "E":  # 只递归尚未挖开的空格 E
                            dfs(x, y)  # 递归挖开相邻空格

        m, n = len(board), len(board[0])  # 行数、列数；dfs 在调用时才读，写在定义之后也没问题
        i, j = click  # 把点击坐标拆成行列
        if board[i][j] == "M":  # 第一下就点到地雷
            board[i][j] = "X"  # 直接引爆，不再扩散
        else:  # 点到的不是地雷
            dfs(i, j)  # 从点击位置开始挖
        return board  # 返回更新后的棋盘
