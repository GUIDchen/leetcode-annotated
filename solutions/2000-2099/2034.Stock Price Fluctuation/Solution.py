# 题目：2034. 股票价格波动（Stock Price Fluctuation）
# 思路：字典记录「时间戳 → 当前价格」，SortedList 维护全部有效价格；更新时先删掉该时间戳的旧价格再加入新价格，并用 last 记录最新时间戳。
# 时间复杂度：update 为 O(log n)，current/maximum/minimum 均为 O(1)；空间复杂度：O(n)，每个时间戳保存一份价格。
class StockPrice:  # 维护「时间戳 → 价格」并支持查询最新/最高/最低价的数据结构类
    def __init__(self):  # 构造函数：初始化三份成员状态
        self.d = {}  # 字典：时间戳 → 该时刻的当前价格
        self.ls = SortedList()  # 有序容器：保存所有有效价格，支持 O(log n) 增删与取首尾
        self.last = 0  # 出现过的最大时间戳，初始为 0

    def update(self, timestamp: int, price: int) -> None:  # timestamp 时刻的价格更新为 price
        if timestamp in self.d:  # 同一时间戳可能被多次更新，旧价格要先从有序容器中移除
            self.ls.remove(self.d[timestamp])  # 只删一个旧值（价格可能重复，remove 按值删一个）
        self.d[timestamp] = price  # 用新价格覆盖字典中的记录
        self.ls.add(price)  # 新价格加入有序容器，参与极值查询
        self.last = max(self.last, timestamp)  # 时间戳不保证递增到达，所以取最大值来维护「最新」

    def current(self) -> int:  # 返回最新时间戳对应的价格
        return self.d[self.last]  # last 就是出现过的最大的那个时间戳

    def maximum(self) -> int:  # 返回当前最高价格
        return self.ls[-1]  # SortedList 升序，末尾元素即最大值

    def minimum(self) -> int:  # 返回当前最低价格
        return self.ls[0]  # SortedList 升序，首元素即最小值


# 下面是 LeetCode 判题器自动生成的调用示例注释，原样保留。
# Your StockPrice object will be instantiated and called as such:
# obj = StockPrice()
# obj.update(timestamp,price)
# param_2 = obj.current()
# param_3 = obj.maximum()
# param_4 = obj.minimum()
