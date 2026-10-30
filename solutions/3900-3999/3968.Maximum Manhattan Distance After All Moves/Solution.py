# 3968. 移动后的最大曼哈顿距离 / Maximum Manhattan Distance After All Moves
# 核心思路：先统计固定上下左右移动得到净位移 (x, y)，并把每个通配符 '_' 的个数记为 z；
#          每个通配符都能朝远离原点的方向多走 1 步，因此最大曼哈顿距离为 |x| + |y| + z。
# 复杂度：时间 O(L)（L 为字符串长度），空间 O(1)。

class Solution:
    def maxDistance(self, moves: str) -> int:  # 返回所有移动完成后能得到的最大曼哈顿距离
        x = y = z = 0  # x 为纵向净位移，y 为横向净位移，z 为通配符个数
        for c in moves:  # 逐个字符统计各类移动
            if c == "U":  # 向上移动
                x -= 1  # 纵坐标减一
            elif c == "D":  # 向下移动
                x += 1  # 纵坐标加一
            elif c == "L":  # 向左移动
                y -= 1  # 横坐标减一
            elif c == "R":  # 向右移动
                y += 1  # 横坐标加一
            else:  # 剩下的通配符 '_'，可任意替换方向
                z += 1  # 通配符计数加一
        return abs(x) + abs(y) + z  # 固定位移贡献 |x|+|y|，每个通配符最多再贡献 1
