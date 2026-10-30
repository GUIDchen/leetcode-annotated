# 题目：2013. 检测正方形（Detect Squares）
# 思路：用 defaultdict(Counter) 记录「x → (y → 次数)」；查询时枚举另一条竖边的 x2，按带符号边长 d 累加上下两种正方形三个顶点的计数乘积。
# 时间复杂度：add 为 O(1)，count 为 O(不同 x 的个数)；空间复杂度：O(n)，n 为已添加的点数。
class DetectSquares:  # 统计类，需要支持 add 与 count 两种操作
    def __init__(self):  # 构造函数
        self.cnt = defaultdict(Counter)  # self.cnt[x][y] 表示坐标 (x, y) 上的点数，缺失的键在访问时自动补 0

    def add(self, point: List[int]) -> None:  # point = [x, y]，把一个点加入统计
        x, y = point  # 拆出横纵坐标
        self.cnt[x][y] += 1  # 对应坐标的计数加一

    def count(self, point: List[int]) -> int:  # 返回能与 point 组成轴对齐正方形的已有点三元组个数
        x1, y1 = point  # 查询点的横纵坐标
        if x1 not in self.cnt:  # 没有任何已添加的点与查询点同横坐标，构不成竖直边
            return 0  # 直接返回 0
        ans = 0  # ans 累加所有可能的正方形个数
        for x2 in self.cnt.keys():  # 枚举另一条竖边的横坐标
            if x2 != x1:  # x2 必须与 x1 不同，否则会退化成同一条竖线
                d = x2 - x1  # 正方形边长（带符号），纵向偏移量也取它
                ans += self.cnt[x2][y1] * self.cnt[x1][y1 + d] * self.cnt[x2][y1 + d]  # 上侧正方形：另两顶点为 (x1, y1+d) 与 (x2, y1+d)，三点计数相乘
                ans += self.cnt[x2][y1] * self.cnt[x1][y1 - d] * self.cnt[x2][y1 - d]  # 下侧正方形：另两顶点为 (x1, y1-d) 与 (x2, y1-d)，三点计数相乘
        return ans  # 返回正方形总数


# Your DetectSquares object will be instantiated and called as such:
# obj = DetectSquares()
# obj.add(point)
# param_2 = obj.count(point)
