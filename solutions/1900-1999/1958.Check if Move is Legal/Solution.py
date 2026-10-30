# 题目：1958. 检查操作是否合法（Check if Move is Legal）
# 思路：从落子点出发沿八个方向探测，某方向若先经过至少一枚对方棋子、再遇到我方棋子，就能把中间的对方棋子夹住，操作合法。
# 时间复杂度：O(1)，8 个方向、每方向至多 6 步；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def checkMove(  # board 是 8×8 棋盘，rMove/cMove 是落子位置，color 是落子方颜色
        self, board: List[List[str]], rMove: int, cMove: int, color: str
    ) -> bool:
        for a in range(-1, 2):  # a 取 -1、0、1，表示行方向增量
            for b in range(-1, 2):  # b 取 -1、0、1，表示列方向增量
                if a == 0 and b == 0:  # (0, 0) 是原地，不算方向
                    continue  # 跳过原地，只保留八个真实方向
                i, j = rMove, cMove  # 从落子点出发沿 (a, b) 前进
                cnt = 0  # 统计本方向已走的格数
                while 0 <= i + a < 8 and 0 <= j + b < 8:  # 下一格仍在棋盘内才继续探测
                    cnt += 1  # 先计数，表示即将走到下一格
                    i, j = i + a, j + b  # 坐标前进一步
                    if cnt > 1 and board[i][j] == color:  # 跳过紧邻的一格后遇到同色，说明中间夹着对方棋子
                        return True  # 该方向合法，整体判为合法
                    if board[i][j] in (color, "."):  # 遇到我方棋子或空位，本方向无法夹子
                        break  # 结束本方向探测
        return False  # 八个方向都不成立，操作不合法
