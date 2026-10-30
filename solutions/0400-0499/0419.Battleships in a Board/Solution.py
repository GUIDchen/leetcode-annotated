# 题目：419. 棋盘上的战舰（Battleships in a Board）
# 思路：只统计每艘战舰的左上端——当前格是 X 且上方、左方都不是 X，它就是这艘战舰的第一格，计数一次。
# 时间复杂度：O(m * n)，只扫一遍棋盘；空间复杂度：O(1)，只用了几个计数变量。
class Solution:  # LeetCode 约定的题解类
    def countBattleships(self, board: List[List[str]]) -> int:  # board 是 X（战舰）与点（空）组成的棋盘，返回战舰数量
        m, n = len(board), len(board[0])  # m 行、n 列
        ans = 0  # ans 记录战舰数量
        for i in range(m):  # 遍历每一行
            for j in range(n):  # 遍历每一列
                if board[i][j] == '.':  # 空格直接跳过
                    continue  # 继续检查下一格
                if i > 0 and board[i - 1][j] == 'X':  # 上方也是 X，说明当前格是纵向战舰的中间或尾部，不能重复计数
                    continue  # 跳过，避免一艘战舰被数多次
                if j > 0 and board[i][j - 1] == 'X':  # 左方也是 X，说明当前格是横向战舰的中间或尾部
                    continue  # 跳过，避免重复计数
                ans += 1  # 上方、左方都不是 X，当前格是一艘新战舰的左上端，计数加一
        return ans  # 返回战舰总数
