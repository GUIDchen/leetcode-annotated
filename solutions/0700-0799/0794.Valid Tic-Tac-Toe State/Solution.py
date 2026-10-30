# 题目：794. 有效的井字游戏（Valid Tic-Tac-Toe State）
# 思路：合法局面只需满足三条：X 先手所以 X 数等于 O 数或比 O 多 1；X 赢时必须刚下完（X 比 O 多 1）；O 赢时数量必须相等。
# 时间复杂度：O(1)，棋盘固定 3x3；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def validTicTacToe(self, board: List[str]) -> bool:  # board：3x3 棋盘，字符为 'X'、'O' 或空格
        def win(x):  # win(x)：判断字符 x 是否已经连成三子
            for i in range(3):  # 依次检查第 i 行与第 i 列
                if all(board[i][j] == x for j in range(3)):  # 第 i 行全为 x
                    return True  # 已经三连，直接返回
                if all(board[j][i] == x for j in range(3)):  # 第 i 列全为 x
                    return True  # 已经三连，直接返回
            if all(board[i][i] == x for i in range(3)):  # 主对角线全为 x
                return True  # 已经三连，直接返回
            return all(board[i][2 - i] == x for i in range(3))  # 副对角线全为 x 就是赢，否则没连成

        x = sum(board[i][j] == 'X' for i in range(3) for j in range(3))  # 统计 X 的落子数
        o = sum(board[i][j] == 'O' for i in range(3) for j in range(3))  # 统计 O 的落子数
        if x != o and x - 1 != o:  # X 先手：X 的个数只能等于 O，或恰好比 O 多 1
            return False  # 数量关系不合法
        if win('X') and x - 1 != o:  # X 赢说明最后一步是 X 下的，此时 X 必须比 O 多 1
            return False  # 否则局面不可能出现
        return not (win('O') and x != o)  # O 赢时双方数量必须相等；同时排除双方都赢的局面
