# 题目：3248. 矩阵中的蛇（Snake in Matrix）
# 思路：从 (0,0) 出发逐条模拟移动命令，维护行列坐标，最后按 row * n + col 换算成一维编号。
# 时间复杂度：O(m)，m 为命令条数；空间复杂度：O(1)，只用了行列两个变量。
class Solution:  # # LeetCode 约定的题解类
    def finalPositionOfSnake(self, n: int, commands: List[str]) -> int:  # # n 是矩阵边长，commands 是移动命令，返回蛇最终位置的一维编号
        x = y = 0  # # x 是行号、y 是列号，蛇从左上角 (0,0) 出发
        for c in commands:  # # 逐条处理移动命令
            match c[0]:  # # 只看命令字符串的首字母即可判断方向
                case "U":  # # 上移：行号减一
                    x -= 1  # # 执行 x -= 1
                case "D":  # # 下移：行号加一
                    x += 1  # # 执行 x += 1
                case "L":  # # 左移：列号减一
                    y -= 1  # # 执行 y -= 1
                case "R":  # # 右移：列号加一
                    y += 1  # # 执行 y += 1
        return x * n + y  # # 按题目约定把二维坐标换算成一维编号 row * n + col
