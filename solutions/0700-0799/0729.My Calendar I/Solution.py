# 题目：729. 我的日程安排表 I（My Calendar I）
# 思路：用 SortedDict 以「结束时间 → 开始时间」维护已预订区间；插入前二分找到第一个结束时间大于 start 的区间，若其开始时间小于 end 则重叠。
# 时间复杂度：每次 book 为 O(log n) 的二分查找；空间复杂度：O(n)，保存 n 个已预订区间。
class MyCalendar:  # 日程表类，只支持一次预订不冲突的判断
    def __init__(self):  # 构造函数：初始化有序字典
        self.sd = SortedDict()  # SortedDict 是 sortedcontainers 提供的按 key 有序映射（LeetCode 环境已预置）

    def book(self, start: int, end: int) -> bool:  # start、end 是本次要预订的半开区间 [start, end)
        idx = self.sd.bisect_right(start)  # bisect_right(start) 得到第一个键大于 start 的位置，即第一个结束时间大于 start 的区间
        if idx < len(self.sd) and self.sd.values()[idx] < end:  # 存在这样的区间且它的开始时间小于 end，说明两段相交
            return False  # 冲突则拒绝本次预订
        self.sd[end] = start  # 不冲突，以 end 为键、start 为值登记该区间
        return True  # 登记成功返回 True


# 下面是 LeetCode 判题器自动生成的调用示例，原样保留，仅作说明
# Your MyCalendar object will be instantiated and called as such:  # 判题器给出的调用示例，原样保留
# obj = MyCalendar()  # 示例：构造对象
# param_1 = obj.book(start,end)  # 示例：调用 book
