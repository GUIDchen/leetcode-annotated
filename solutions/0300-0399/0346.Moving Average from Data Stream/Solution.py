# 题目：346. 数据流中的移动平均值（Moving Average from Data Stream）
# 思路：用长度固定为 size 的环形数组保存最近的元素，同时维护窗口元素之和，每次减去被覆盖的旧值、加上新值。
# 时间复杂度：构造 O(size)，next 为 O(1)；空间复杂度：O(size)，环形数组。
class MovingAverage:  # 移动平均值类

    def __init__(self, size: int):  # size：滑动窗口大小，即最多保留最近多少个数据
        self.s = 0  # 窗口内元素之和，随元素进出增量维护
        self.data = [0] * size  # 环形数组，长度固定为 size，初始全 0
        self.cnt = 0  # 累计处理过的元素个数，用于取模定位和计算真实窗口长度

    def next(self, val: int) -> float:  # val：数据流新到的值；返回最近 size 个值的平均值
        i = self.cnt % len(self.data)  # 对 size 取模得到本轮要覆盖的槽位下标，形成环形复用
        self.s += val - self.data[i]  # 先减去槽位里的旧值、再加上新值，避免每次重新求和
        self.data[i] = val  # 把新值写入槽位，替换掉被挤出窗口的旧值
        self.cnt += 1  # 已处理元素个数加一，用来判断窗口是否已满
        return self.s / min(self.cnt, len(self.data))  # 元素不足 size 个时按实际个数 cnt 求平均，满了之后按 size 求平均


# Your MovingAverage object will be instantiated and called as such:
# obj = MovingAverage(size)
# param_1 = obj.next(val)
