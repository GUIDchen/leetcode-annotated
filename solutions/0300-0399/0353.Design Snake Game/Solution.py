# 题目：353. 设计贪吃蛇（Design Snake Game）
# 思路：deque 按“队首蛇头、队尾蛇尾”存蛇身坐标，集合记录占用格子；每步先算新头，再判越界、判吃食物，最后判自撞并入队。
# 时间复杂度：move 为 O(1)；空间复杂度：O(width × height)，蛇身与占用集合的最大规模。
class SnakeGame:  # 贪吃蛇游戏的数据结构类
    def __init__(self, width: int, height: int, food: List[List[int]]):  # width 为列数，height 为行数，food 是按出现顺序给出的食物坐标
        self.m = height  # 记录行数，即 x 方向的取值范围
        self.n = width  # 记录列数，即 y 方向的取值范围
        self.food = food  # 保存食物序列，用 idx 顺序取用
        self.score = 0  # 初始得分为 0
        self.idx = 0  # 下一个待吃食物的下标
        self.q = deque([(0, 0)])  # 蛇身用双端队列存坐标，队首是蛇头，初始只有 (0,0)
        self.vis = {(0, 0)}  # 蛇身占用格子的集合，用于 O(1) 判重

    def move(self, direction: str) -> int:  # 按方向走一步并返回得分；撞墙或撞到自己返回 -1
        i, j = self.q[0]  # 队首即蛇头坐标
        x, y = i, j  # x、y 为移动后的新蛇头坐标，先复制当前蛇头
        match direction:  # 按方向字符串分支（Python 3.10 的结构化模式匹配）
            case "U":  # 向上
                x -= 1  # 行号减一
            case "D":  # 向下
                x += 1  # 行号加一
            case "L":  # 向左
                y -= 1  # 列号减一
            case "R":  # 向右
                y += 1  # 列号加一
        if x < 0 or x >= self.m or y < 0 or y >= self.n:  # 越界即撞墙，游戏结束
            return -1  # 返回 -1 表示游戏结束
        if (  # 新蛇头正好是下一个待吃的食物
            self.idx < len(self.food)  # 还有没吃完的食物
            and x == self.food[self.idx][0]  # 行号与食物坐标一致
            and y == self.food[self.idx][1]  # 列号与食物坐标一致
        ):  # 条件结束
            self.score += 1  # 吃到食物，得分加一
            self.idx += 1  # 该食物已消费，指向下一个
        else:  # 没吃到食物，蛇身长度保持不变
            self.vis.remove(self.q.pop())  # 先 pop 出队尾（蛇尾），再把它的格子从占用集合里删掉
        if (x, y) in self.vis:  # 新蛇头撞到仍在场上的身体就直接结束
            return -1  # 返回 -1 表示游戏结束
        self.q.appendleft((x, y))  # 新蛇头从队首入队
        self.vis.add((x, y))  # 标记该格子已被身体占用
        return self.score  # 返回当前得分


# 下面是 LeetCode 模板注释，仅演示对象的构造与调用方式
# Your SnakeGame object will be instantiated and called as such:
# obj = SnakeGame(width, height, food)
# param_1 = obj.move(direction)
