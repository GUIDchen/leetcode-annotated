# 题目：657. 机器人能否返回原点（Robot Return to Origin）
# 核心思路：分别维护水平与垂直位移，遍历完整指令串后判断坐标是否为 (0, 0)。
# 时间复杂度：O(n)，只遍历一次指令串；空间复杂度：O(1)，只用两个计数器。
class Solution:  # LeetCode 约定的题解类
    def judgeCircle(self, moves: str) -> bool:  # moves 是 U/D/L/R 组成的指令串，判断走完后是否回到原点
        x = y = 0  # x、y 同时初始化为 0，表示当前坐标
        for c in moves:  # 逐条处理移动指令
            match c:  # Python 3.10 的结构化模式匹配，作用相当于 switch
                case "U":  # 线上移动：纵坐标变化
                    y += 1  # 纵坐标加一
                case "D":  # 线下移动：纵坐标变化
                    y -= 1  # 纵坐标减一
                case "L":  # 向左移动：横坐标变化
                    x -= 1  # 横坐标减一
                case "R":  # 向右移动：横坐标变化
                    x += 1  # 横坐标加一
        return x == 0 and y == 0  # 两个坐标都回到 0 才算回到原点
