# 题目：130. 被围绕的区域（Surrounded Regions）
# 思路：从四条边界的 'O' 出发做 DFS，把与边界连通的格子先标成 '.'，最后把 '.' 还原成 'O'、把剩下的 'O' 改成 'X'。
# 时间复杂度：O(m * n)，每个格子最多访问一次；空间复杂度：O(m * n)，DFS 递归栈的最坏深度。
class Solution:  # LeetCode 约定的题解类
    def solve(self, board: List[List[str]]) -> None:  # 原地修改棋盘，函数没有返回值
        def dfs(i: int, j: int):  # 内层 DFS：把从 (i, j) 开始能走到的 'O' 全部标成 '.'
            if not (0 <= i < m and 0 <= j < n and board[i][j] == "O"):  # 越界或当前格子不是 'O'（已被标记 / 本来是 'X'）就返回
                return  # 结束本次递归
            board[i][j] = "."  # 打上标记：既表示与边界连通，也避免重复访问
            for a, b in pairwise((-1, 0, 1, 0, -1)):  # pairwise 把一维方向序列拆成 (a, b) 偏移对，正好是上下左右四个方向
                dfs(i + a, j + b)  # 递归处理相邻格子

        m, n = len(board), len(board[0])  # 先取到行数 m 和列数 n（放在 dfs 定义之后也没问题，调用时才查名字）
        for i in range(m):  # 左右两列边界上的所有格
            dfs(i, 0)  # 左边界 (i, 0)
            dfs(i, n - 1)  # 右边界 (i, n-1)
        for j in range(n):  # 上下两行边界上的所有格
            dfs(0, j)  # 上边界 (0, j)
            dfs(m - 1, j)  # 下边界 (m-1, j)
        for i in range(m):  # 遍历整个棋盘做最后的翻转
            for j in range(n):  # 逐列处理当前行
                if board[i][j] == ".":  # '.' 是与边界连通的 'O'
                    board[i][j] = "O"  # 还原成 'O'
                elif board[i][j] == "O":  # 'O' 被 'X' 完全包围
                    board[i][j] = "X"  # 翻转成 'X'
