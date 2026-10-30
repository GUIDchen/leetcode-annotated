# 题目：2018. 判断单词是否能放入填字游戏内（Check if Word Can Be Placed In Crossword）
# 思路：枚举每个格子作为起点，只接受左侧（或上方）紧邻边界或障碍的位置；再用内部 check 函数沿四个方向逐格比对字符，并要求单词末尾之后不是普通字母。
# 时间复杂度：O(m * n * k)，每个起点最多校验四个方向、每个方向 k 个字符；空间复杂度：O(1)，只用常数个扫描变量。
class Solution:  # LeetCode 约定的题解类
    def placeWordInCrossword(self, board: List[List[str]], word: str) -> bool:  # board：填字棋盘（' ' 为空格，'#' 为障碍）；word：待放置的单词
        def check(i, j, a, b):  # 从 (i, j) 沿方向 (a, b) 试放；闭包内直接读取外层的 m、n、k、board、word
            x, y = i + a * k, j + b * k  # 单词末尾之后的下一格坐标
            if 0 <= x < m and 0 <= y < n and board[x][y] != '#':  # 末尾之后仍在棋盘内且是普通字母，说明这一段更长，放不下
                return False  # 该方向不可行
            for c in word:  # 把单词字符逐个对齐到棋盘
                if (  # 越界、撞障碍、字符不符都判失败
                    i < 0  # 行坐标越界（负方向走出棋盘）
                    or i >= m  # 行坐标越界（正方向走出棋盘）
                    or j < 0  # 列坐标越界（负方向）
                    or j >= n  # 列坐标越界（正方向）
                    or (board[i][j] != ' ' and board[i][j] != c)  # 该格既不是空格，也不是当前需要的字符
                ):  # 条件表达式结束
                    return False  # 匹配失败
                i, j = i + a, j + b  # 沿方向前进到下一个格子
            return True  # 全部字符都匹配，该方向可行

        m, n = len(board), len(board[0])  # 行数 m、列数 n；check 在调用时才读取它们，所以可以后定义
        k = len(word)  # 单词长度，决定末尾之后那一格的位置
        for i in range(m):  # 枚举起点行
            for j in range(n):  # 枚举起点列
                left_to_right = (j == 0 or board[i][j - 1] == '#') and check(i, j, 0, 1)  # 从左往右：左侧是边界或障碍才允许作为起点
                right_to_left = (j == n - 1 or board[i][j + 1] == '#') and check(  # 从右往左：右侧是边界或障碍
                    i, j, 0, -1  # 上面 check 调用的续行：方向为 (0, -1)
                )  # check 调用结束
                up_to_down = (i == 0 or board[i - 1][j] == '#') and check(i, j, 1, 0)  # 从上往下：上方是边界或障碍
                down_to_up = (i == m - 1 or board[i + 1][j] == '#') and check(  # 从下往上：下方是边界或障碍
                    i, j, -1, 0  # 上面 check 调用的续行：方向为 (-1, 0)
                )  # check 调用结束
                if left_to_right or right_to_left or up_to_down or down_to_up:  # 四个方向任一可行即可
                    return True  # 找到可行放法
        return False  # 全部起点都试过仍失败
