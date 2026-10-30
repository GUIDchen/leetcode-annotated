# 题目：3001. 捕获黑皇后需要的最少移动次数（Minimum Moves to Capture The Queen）
# 思路：分别判断车或象能否一步吃到皇后；能则答案为 1，否则先用一步腾挪、第二步必能吃，答案为 2。
# 时间复杂度：O(1)，只有四个常数的判定；空间复杂度：O(1)，没有额外存储。
class Solution:  # LeetCode 约定的题解类
    def minMovesToCaptureTheQueen(  # (a,b)：车的位置；(c,d)：象的位置；(e,f)：黑皇后的位置
        self, a: int, b: int, c: int, d: int, e: int, f: int  # 逐个接收车、象、皇后的坐标
    ) -> int:  # 返回捕获皇后所需的最少移动次数
        if a == e and (c != a or (d - b) * (d - f) > 0):  # 车与皇后同一列：象不在这一列，或象不夹在两者之间，车一步就能吃
            return 1  # 一步即可捕获
        if b == f and (d != b or (c - a) * (c - e) > 0):  # 车与皇后同一行：象不在这一行，或象不夹在两者之间，车一步就能吃
            return 1  # 一步即可捕获
        if c - e == d - f and (a - e != b - f or (a - c) * (a - e) > 0):  # 象与皇后同在「左上—右下」方向的对角线：车不在该对角线，或车不夹在两者之间
            return 1  # 一步即可捕获
        if c - e == f - d and (a - e != f - b or (a - c) * (a - e) > 0):  # 象与皇后同在「左下—右上」方向的对角线：车不在该对角线，或车不夹在两者之间
            return 1  # 一步即可捕获
        return 2  # 双方都无法一步到达，最多两步：先挪开挡路的棋子再吃，所以答案是 2
