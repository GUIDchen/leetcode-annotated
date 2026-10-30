# 题目：1515. 服务中心的最佳位置（Best Position for a Service Centre）
# 思路：距离和是关于坐标的凸函数，用「重心为起点 + 梯度下降 + 步长衰减」迭代逼近最优位置。
# 时间复杂度：O(n·迭代轮数)；空间复杂度：O(1)，只维护坐标、梯度与步长。
class Solution:  # LeetCode 约定的题解类
    def getMinDistSum(self, positions: List[List[int]]) -> float:  # positions：客户点坐标列表；返回服务中心到所有点距离之和的最小值
        n = len(positions)  # n：点的个数
        x = y = 0  # x、y：当前迭代坐标，链式赋值同时置 0，准备累加
        for x1, y1 in positions:  # 逐点累加坐标，求重心作为迭代起点
            x += x1  # 累加横坐标
            y += y1  # 累加纵坐标
        x, y = x / n, y / n  # 取平均得到初始服务中心坐标
        decay = 0.999  # decay：步长每轮的衰减系数，保证后期收敛
        eps = 1e-6  # eps：判停阈值，移动量足够小即认为收敛
        alpha = 0.5  # alpha：初始步长系数
        while 1:  # 无限循环，直到移动量足够小才 return
            grad_x = grad_y = 0  # grad_x、grad_y：本轮梯度，链式赋值清零
            dist = 0  # dist：当前坐标到所有点的距离和
            for x1, y1 in positions:  # 遍历每个点，累计梯度与距离
                a = x - x1  # a：x 方向的坐标差
                b = y - y1  # b：y 方向的坐标差
                c = sqrt(a * a + b * b)  # c：当前坐标到该点的欧氏距离
                grad_x += a / (c + 1e-8)  # 距离对 x 的偏导为 a/c，加 1e-8 避免与点重合时除零
                grad_y += b / (c + 1e-8)  # 距离对 y 的偏导为 b/c，同样防止除零
                dist += c  # 累加目标函数值
            dx = grad_x * alpha  # 沿负梯度方向走一步，dx 为横坐标移动量
            dy = grad_y * alpha  # dy 为纵坐标移动量
            x -= dx  # 更新横坐标（梯度下降）
            y -= dy  # 更新纵坐标（梯度下降）
            alpha *= decay  # 步长衰减，下一轮更保守
            if abs(dx) <= eps and abs(dy) <= eps:  # 移动量已经足够小，认为到达最优点
                return dist  # 返回此时的距离和，即最小总距离
