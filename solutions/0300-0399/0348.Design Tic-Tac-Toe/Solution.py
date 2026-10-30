# 题目：348. 设计井字棋（Design Tic-Tac-Toe）
# 思路：不保存棋盘，给每个玩家维护「每行 / 每列 / 两条对角线」的棋子计数；某条线的计数达到 n 即该玩家连成 n 子获胜。
# 时间复杂度：move 为 O(1)；空间复杂度：O(n)，每个玩家用字典存 2n+2 个计数器。
class TicTacToe:  # 井字棋类

    def __init__(self, n: int):  # 构造函数：n 为棋盘边长，获胜需要一条线上有 n 个同色棋子
        self.n = n  # 保存棋盘边长，供 move 使用
        self.cnt = [defaultdict(int), defaultdict(int)]  # 两个玩家各一个默认值为 0 的字典，键是线编号，值是这条线上的棋子数

    def move(self, row: int, col: int, player: int) -> int:  # row、col：落子坐标；player 取 1 或 2；返回获胜玩家编号，暂时无人获胜返回 0
        cur = self.cnt[player - 1]  # 取出当前玩家对应的计数字典（下标 player-1 映射到 0/1）
        n = self.n  # 把边长取到局部变量，下面多次使用，省去属性查找
        cur[row] += 1  # 该行棋子数加一：行编号直接占键 0..n-1
        cur[n + col] += 1  # 该列棋子数加一：列编号偏移 n 后占键 n..2n-1
        if row == col:  # 落在主对角线（行列下标相等）上才累加
            cur[n << 1] += 1  # 主对角线计数加一，键为 2n（即 n << 1）
        if row + col == n - 1:  # 落在副对角线（行列下标之和为 n-1）上才累加
            cur[n << 1 | 1] += 1  # 副对角线计数加一，键为 2n+1（即 n << 1 | 1）
        if any(cur[i] == n for i in (row, n + col, n << 1, n << 1 | 1)):  # 四条经过本次落子的线里只要有一条计满 n 个，当前玩家即获胜
            return player  # 返回获胜玩家编号
        return 0  # 没有任何一条线被填满，游戏继续


# Your TicTacToe object will be instantiated and called as such:
# obj = TicTacToe(n)
# param_1 = obj.move(row,col,player)
