# 3829. 设计共享出行系统 / Design Ride Sharing System（中等）
# 核心思路：全局自增计数 t 充当排队序号，骑手与司机分别放进有序列表并存入 (t, id)，匹配时各弹出最前面的元素；哈希表记住骑手序号以支持取消。
# 复杂度：新增与取消均 O(log n)（SortedList 插入/删除），匹配为 O(log n)；空间 O(n)。
class RideSharingSystem:  # 设计共享出行系统：骑手与司机分别排队，先到先服务

    def __init__(self):  # 构造函数：初始化排队序号与两个有序队列
        self.t = 0  # 全局自增序号，代表加入时间的先后
        self.riders = SortedList()  # 骑手有序列表，元素为 (序号, 骑手 id)
        self.drivers = SortedList()  # 司机有序列表，元素为 (序号, 司机 id)
        self.d = defaultdict(int)  # 骑手 id → 加入序号，取消时用于定位

    def addRider(self, riderId: int) -> None:  # 新增一名等待中的骑手
        self.d[riderId] = self.t  # 记录该骑手的加入序号
        self.riders.add((self.t, riderId))  # 把 (序号, id) 加入有序列表
        self.t += 1  # 序号自增，保证单调递增

    def addDriver(self, driverId: int) -> None:  # 新增一名等待中的司机
        self.drivers.add((self.t, driverId))  # 把 (序号, id) 加入司机有序列表
        self.t += 1  # 序号同样自增，与骑手共用一条时间线

    def matchDriverWithRider(self) -> List[int]:  # 为最早等待的司机匹配最早等待的骑手
        if len(self.riders) < 1 or len(self.drivers) < 1:  # 任一方为空时无法匹配
            return [-1, -1]  # 无匹配时按约定返回 [-1, -1]
        return [self.drivers.pop(0)[1], self.riders.pop(0)[1]]  # 分别弹出两个队列的首元素（序号最小、等待最久），取 id 组成答案

    def cancelRider(self, riderId: int) -> None:  # 取消某骑手的等待请求
        self.riders.discard((self.d[riderId], riderId))  # 按 (序号, id) 从有序列表中移除，不存在时 discard 静默忽略


# Your RideSharingSystem object will be instantiated and called as such:
# obj = RideSharingSystem()
# obj.addRider(riderId)
# obj.addDriver(driverId)
# param_3 = obj.matchDriverWithRider()
# obj.cancelRider(riderId)
