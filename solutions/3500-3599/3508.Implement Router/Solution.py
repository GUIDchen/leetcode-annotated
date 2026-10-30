# 题目：3508. 设计路由器（Implement Router）
# 思路：哈希集合判重 + 双端队列按入队顺序存包 + 每个目的地各维护一张按时间升序的时间戳表。入队前若已达到内存上限就先弹出队首；getCount 用 bisect_left 在「尚未被弹出」的那段后缀上二分，靠每个目的地的已弹出计数定位起点。
# 时间复杂度：addPacket 与 forwardPacket 均摊 O(1)，getCount 为两次二分 O(log m)；空间复杂度：O(memoryLimit)，队列与去重集合都受内存上限约束。
class Router:  # 路由器类，支持加包、按序弹包与区间计数

    def __init__(self, memoryLimit: int):  # 构造函数，读入内存上限
        self.lim = memoryLimit  # 记录内存上限
        self.vis = set()  # 已入队包的键集合，用于 O(1) 判重
        self.q = deque()  # 按入队顺序存包的队列
        self.idx = defaultdict(int)  # 每个目的地已被弹出的包数（默认 0）
        self.d = defaultdict(list)  # 每个目的地的时间戳列表（默认空表）

    def addPacket(self, source: int, destination: int, timestamp: int) -> bool:  # 加入一个包，重复包返回 False
        x = self.f(source, destination, timestamp)  # 生成该包的唯一键
        if x in self.vis:  # 该包此前已经入过队
            return False  # 重复包直接拒绝
        self.vis.add(x)  # 标记该包已存在
        if len(self.q) >= self.lim:  # 队列已满，需要腾出位置
            self.forwardPacket()  # 弹出最旧的包（返回值此处丢弃）
        self.q.append((source, destination, timestamp))  # 新包追加到队尾
        self.d[destination].append(timestamp)  # 同步写入目的地的升序时间戳表
        return True  # 添加成功

    def forwardPacket(self) -> List[int]:  # 弹出并返回队首最旧的包
        if not self.q:  # 队列为空
            return []  # 没有可弹出的包，返回空列表
        s, d, t = self.q.popleft()  # 弹出队首并拆出源、目的、时间戳
        self.vis.remove(self.f(s, d, t))  # 从判重集合中删掉该包的键
        self.idx[d] += 1  # 该目的地的已弹出计数加一，后续统计从这里开始
        return [s, d, t]  # 返回被弹出的包

    def f(self, a: int, b: int, c: int) -> tuple:  # 把三元组组成元组键，供集合判重
        return (a, b, c)  # 元组可哈希，天然用于去重与回收

    def getCount(self, destination: int, startTime: int, endTime: int) -> int:  # 统计某目的地在 [startTime, endTime] 闭区间内的包数
        ls = self.d[destination]  # 取该目的地的升序时间戳列表
        k = self.idx[destination]  # 已弹出的前缀长度，二分只需在其后的后缀中进行
        i = bisect_left(ls, startTime, k)  # 从下标 k 开始，第一个时间戳 >= startTime 的位置
        j = bisect_left(ls, endTime + 1, k)  # 从下标 k 开始，第一个时间戳 > endTime 的位置
        return j - i  # 下标之差即区间内的包数


# Your Router object will be instantiated and called as such:
# obj = Router(memoryLimit)
# param_1 = obj.addPacket(source,destination,timestamp)
# param_2 = obj.forwardPacket()
# param_3 = obj.getCount(destination,startTime,endTime)
