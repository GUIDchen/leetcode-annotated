# 题目：731. 我的日程安排表 II（My Calendar II）
# 思路：SortedDict 维护时间轴上的差分（startTime 处 +1，endTime 处 -1）；每次插入后按时间顺序累加前缀和，若某处超过 2 说明出现三重预订，随即回滚。
# 时间复杂度：每次 book 需遍历整个有序字典，为 O(n)；空间复杂度：O(n)，最多存 2n 个时间点。
class MyCalendarTwo:  # 日程表类，支持在允许双重预订的前提下判断是否会三重预订
    def __init__(self):  # 构造函数：初始化按 key 有序的字典
        self.sd = SortedDict()  # SortedDict 是 sortedcontainers 提供的按 key 有序映射（LeetCode 环境已预置）

    def book(self, startTime: int, endTime: int) -> bool:  # startTime、endTime 是本次要预订的半开区间 [startTime, endTime)
        self.sd[startTime] = self.sd.get(startTime, 0) + 1  # 起点处差分 +1；get 默认 0 兼容该时间点首次出现
        self.sd[endTime] = self.sd.get(endTime, 0) - 1  # 终点处差分 -1，表示这段占用到此结束
        s = 0  # s 用来扫描前缀和，即当前时刻的预订层数
        for v in self.sd.values():  # 按时间从小到大遍历所有差分值
            s += v  # 累加得到当前时刻的预订层数
            if s > 2:  # 层数超过 2 说明这次预订会造成三重预订
                self.sd[startTime] -= 1  # 回滚起点处的差分
                self.sd[endTime] += 1  # 回滚终点处的差分
                return False  # 预订失败返回 False
        return True  # 全程层数都不超过 2，预订成功


# 下面是 LeetCode 判题器自动生成的调用示例，原样保留，仅作说明
# Your MyCalendarTwo object will be instantiated and called as such:  # 判题器给出的调用示例，原样保留
# obj = MyCalendarTwo()  # 示例：构造对象
# param_1 = obj.book(startTime,endTime)  # 示例：调用 book
