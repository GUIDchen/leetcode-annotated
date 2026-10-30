# 题目：1396. 设计地铁系统（Design Underground System）
# 思路：两个字典分别记录「乘客 id → (进站时间, 进站站点)」和「(起点站, 终点站) → (总耗时, 行程次数)」；出站时累加，查询时相除得到平均时间。
# 时间复杂度：每次操作平均 O(1)；空间复杂度：O(n)，两张字典随操作次数增长。
class UndergroundSystem:  # 题目要求设计的地铁系统类
    def __init__(self):  # 构造函数：初始化两张空字典
        self.ts = {}  # 乘客 id → (进站时间, 进站站点)
        self.d = {}  # (起点站, 终点站) → (总耗时, 行程次数)

    def checkIn(self, id: int, stationName: str, t: int) -> None:  # id 号乘客在 t 时刻从 stationName 进站
        self.ts[id] = (t, stationName)  # 记录该乘客的进站时间与进站站点

    def checkOut(self, id: int, stationName: str, t: int) -> None:  # id 号乘客在 t 时刻从 stationName 出站
        t0, station = self.ts[id]  # 取出该乘客的进站时间 t0 与进站站点 station
        x = self.d.get((station, stationName), (0, 0))  # 取出该线路已累计的 (总耗时, 次数)，不存在时用 (0, 0) 作为默认值
        self.d[(station, stationName)] = (x[0] + t - t0, x[1] + 1)  # 把本次耗时 t - t0 累加，并把行程次数加一后写回

    def getAverageTime(self, startStation: str, endStation: str) -> float:  # 查询从 startStation 到 endStation 的平均耗时
        x = self.d[(startStation, endStation)]  # 取出该线路的总耗时与行程次数
        return x[0] / x[1]  # 相除得到平均时间并返回


# Your UndergroundSystem object will be instantiated and called as such:
# obj = UndergroundSystem()
# obj.checkIn(id,stationName,t)
# obj.checkOut(id,stationName,t)
# param_3 = obj.getAverageTime(startStation,endStation)
