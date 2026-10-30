# 题目：478. 在圆内随机生成点（Generate Random Point in a Circle）
# 思路：极坐标均匀采样。半径取 sqrt(均匀分布 × R^2) 而不是直接均匀取 [0,R]，才能保证点在圆内面积上均匀；角度在 [0,2π) 均匀取。
# 时间复杂度：O(1)，每次调用只做常数次随机数与三角函数；空间复杂度：O(1)，只保存圆心与半径三个参数。
class Solution:  # LeetCode 约定的题解类
    def __init__(self, radius: float, x_center: float, y_center: float):  # 用圆心坐标和半径初始化对象
        self.radius = radius  # 保存圆的半径，供后续采样使用
        self.x_center = x_center  # 保存圆心的横坐标
        self.y_center = y_center  # 保存圆心的纵坐标

    def randPoint(self) -> List[float]:  # 在圆内均匀随机返回一个点 [x, y]
        length = math.sqrt(random.uniform(0, self.radius**2))  # 对半径平方做均匀采样再开方，使落点按面积均匀分布
        degree = random.uniform(0, 1) * 2 * math.pi  # 在 [0,1) 上均匀取数并放大到 [0,2π)，得到随机角度
        x = self.x_center + length * math.cos(degree)  # 极坐标转直角坐标，再加上圆心横坐标做平移
        y = self.y_center + length * math.sin(degree)  # 同理得到纵坐标
        return [x, y]  # 按题目要求以列表形式返回生成的点
