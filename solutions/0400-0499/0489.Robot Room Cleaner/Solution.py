# 题目：489. 扫地机器人（Robot Room Cleaner）
# 思路：把房间抽象成格子坐标系，从 (0,0) 朝向 0 开始 DFS；每到一个格子先 clean，再尝试四个方向，能 move 就递归，递归返回后「右转两次 + move + 右转两次」把机器人还原到原位置与原朝向。
# 时间复杂度：O(m·n)，每个可达格子至多访问一次（每次 4 个方向）；空间复杂度：O(m·n)，vis 集合与递归栈深度。
# """
# This is the robot's control interface.
# You should not implement it, or speculate about its implementation
# """
# class Robot:
#    def move(self):
#        """
#        Returns true if the cell in front is open and robot moves into the cell.
#        Returns false if the cell in front is blocked and robot stays in the current cell.
#        :rtype bool
#        """
#
#    def turnLeft(self):
#        """
#        Robot will stay in the same cell after calling turnLeft/turnRight.
#        Each turn will be 90 degrees.
#        :rtype void
#        """
#
#    def turnRight(self):
#        """
#        Robot will stay in the same cell after calling turnLeft/turnRight.
#        Each turn will be 90 degrees.
#        :rtype void
#        """
#
#    def clean(self):
#        """
#        Clean the current cell.
#        :rtype void
#        """


class Solution:  # LeetCode 约定的题解类
    def cleanRoom(self, robot):  # robot：题目提供的机器人接口对象，只能通过 move/turnLeft/turnRight/clean 感知房间
        """
        :type robot: Robot
        :rtype: None
        """

        def dfs(i, j, d):  # 递归函数：i、j 是相对起点的坐标，d 是当前朝向（0~3 对应上右下左）
            vis.add((i, j))  # 先把当前格子标记为已访问
            robot.clean()  # 清理当前格子
            for k in range(4):  # 四个方向都要尝试
                nd = (d + k) % 4  # 在当前朝向上顺时针转 k 次，得到本次要探索的方向
                x, y = i + dirs[nd], j + dirs[nd + 1]  # 目标格子的坐标（行增量为 dirs[nd]，列增量为 dirs[nd + 1]）
                if (x, y) not in vis and robot.move():  # 目标没走过、且前方是空地（move 成功，机器人已进入目标格）
                    dfs(x, y, nd)  # 进入目标格子继续深搜
                    robot.turnRight()  # 回溯第一步：右转两次共 180 度中的第一次
                    robot.turnRight()  # 第二次右转，朝向反转，正对来路
                    robot.move()  # 沿来路退回上一格，恢复递归前的位置
                    robot.turnRight()  # 转回朝向：右转两次中的第一次
                    robot.turnRight()  # 第二次右转，朝向还原成进入目标格时的 nd
                robot.turnRight()  # 顺时针转 90 度，让下一轮循环的 (d + k) % 4 指向下一个方向

        dirs = (-1, 0, 1, 0, -1)  # 方向数组：上右下左四组 (dx, dy)，末尾多一个 -1 便于取列增量；写在 dfs 之后，靠闭包在调用时才解析
        vis = set()  # 已访问格子集合
        dfs(0, 0, 0)  # 从相对原点 (0, 0) 出发，初始朝向设为 0
