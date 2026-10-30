# 题目：4080. 设计公交车座位预订系统（Design Bus Seat Booking System）
# 核心思路：把座位拆成「第 i 排、第 j 列」，用 cost_data 记录该座位当前计入的费用（0 表示空座）；A 座与相邻 B 座同时被占、D 座与相邻 C 座同时被占时费用升为 3，否则为 1。再维护已预订座位数 min_tot 与总费用 tot，toggle 每次只做常数次更新。
# 时间复杂度：toggle / getTotalTime / getMinTime 均为 O(1)；空间复杂度：O(n)，n 为排数，每排固定 4 个座位的费用记录。
class BusBooking:  # 公交车座位预订系统
    def __init__(self, n: int):  # 构造函数，n 为公交车的排数
        self.tot = 0  # 初始没有任何预订，总耗时为 0
        self.min_tot = 0  # 初始已预订座位数为 0
        self.cost_data = [[0] * 4 for _ in range(n)]  # 开辟 n 排、每排 4 个座位，费用全部初始化为 0

    def toggle(self, seat: str) -> None:  # 切换一个座位的预订状态，seat 形如 "A1"、"D10"
        i = int(seat[1:]) - 1  # 座位号数字部分转成整数，再减一得到从 0 开始的行下标
        j = ord(seat[0]) - ord("A")  # 首字母 A/B/C/D 映射为列下标 0/1/2/3
        if self.cost_data[i][j] > 0:  # 该座位已有费用，说明它被预订过，这次操作即为取消
            self.min_tot -= 1  # 已预订座位数减一
            self.tot -= self.cost_data[i][j]  # 总耗时减去该座位当初计入的费用
            self.cost_data[i][j] = 0  # 把该座位标记回空座
            return  # 取消完成，不再执行新增逻辑
        cost = 1  # 默认该座位单独占一个时间单位，费用为 1
        if (j == 0 and self.cost_data[i][1] > 0) or (  # 条件一：A 座与相邻的 B 座同时被占；或者（见下一行）
            j == 3 and self.cost_data[i][2] > 0  # 条件二：D 座与相邻的 C 座同时被占
        ):  # 两个相邻冲突条件判断结束，命中则二者必须错开
            cost = 3  # 相邻冲突时本次预订需要 3 个时间单位
        self.min_tot += 1  # 新预订一个座位，已预订座位数加一
        self.tot += cost  # 总耗时累加本次座位的费用
        self.cost_data[i][j] = cost  # 记录该座位当前计入的费用，供后续取消与冲突判断使用

    def getTotalTime(self) -> int:  # 返回按当前预订顺序累计的总耗时
        return self.tot  # 直接返回维护好的总费用

    def getMinTime(self) -> int:  # 返回最优安排下的最小总耗时
        return self.min_tot  # 每个座位各占一个时间单位，最小值就等于已预订座位数


# Your BusBooking object will be instantiated and called as such:  # 判题器的调用方式示例（注释原文保持不变）
# obj = BusBooking(n)  # 用排数 n 实例化对象
# obj.toggle(seat)  # 切换座位 seat 的预订状态
# param_2 = obj.getTotalTime()  # 取总耗时
# param_3 = obj.getMinTime()  # 取最小耗时
