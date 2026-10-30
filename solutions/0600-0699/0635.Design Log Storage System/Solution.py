# 题目：635. 设计日志存储系统（Design Log Storage System）
# 思路：日志按插入顺序存进列表；查询时按粒度把时间戳截成等长前缀，前缀落在 [start, end] 内即命中，用列表推导一次筛出。
# 时间复杂度：put 为 O(1)，retrieve 为 O(m)（m 为日志条数）；空间复杂度：O(m)。
class LogSystem:  # 设计题：日志存储系统
    def __init__(self):  # 构造函数：初始化日志列表与粒度映射表
        self.logs = []  # 所有日志按插入顺序保存为 (id, timestamp)
        self.d = {  # 粒度名到时间戳前缀长度的映射
            "Year": 4,  # 年粒度：截取前 4 位，如 2017
            "Month": 7,  # 月粒度：截取前 7 位，如 2017:01
            "Day": 10,  # 日粒度：截取前 10 位，如 2017:01:01
            "Hour": 13,  # 时粒度：截取前 13 位，如 2017:01:01:23
            "Minute": 16,  # 分粒度：截取前 16 位，如 2017:01:01:23:59
            "Second": 19,  # 秒粒度：截取前 19 位，即完整时间戳
        }  # 映射表结束

    def put(self, id: int, timestamp: str) -> None:  # 插入一条日志
        self.logs.append((id, timestamp))  # 按到达顺序追加，列表天然保持插入顺序

    def retrieve(self, start: str, end: str, granularity: str) -> List[int]:  # 查询 [start, end] 区间内、指定粒度下的日志 id
        i = self.d[granularity]  # 查表得到该粒度需要比较的时间戳前缀长度
        return [id for id, ts in self.logs if start[:i] <= ts[:i] <= end[:i]]  # 列表推导：把时间戳截成等长前缀再做字符串比较，命中就收集 id


# Your LogSystem object will be instantiated and called as such:
# obj = LogSystem()
# obj.put(id,timestamp)
# param_2 = obj.retrieve(start,end,granularity)
