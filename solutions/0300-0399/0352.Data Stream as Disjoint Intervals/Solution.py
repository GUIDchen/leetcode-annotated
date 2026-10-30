# 题目：352. 将数据流变为多个不相交区间（Data Stream as Disjoint Intervals）
# 思路：用 SortedDict 以左端点为键保存有序区间，插入 val 时用 bisect_right 定位左右邻居，分四种情形合并。
# 时间复杂度：addNum 为 O(log n)、getIntervals 为 O(n)；空间复杂度：O(n)，n 为不同数字个数。
class SummaryRanges:  # 题目要求的有序区间数据结构类
    def __init__(self):  # 构造函数
        self.mp = SortedDict()  # 有序字典：键是区间左端点，值是 [左端点, 右端点]，按键升序

    def addNum(self, val: int) -> None:  # 加入一个数字 val，并与相邻区间合并
        n = len(self.mp)  # 当前区间个数，同时用作“不存在该邻居”的越界下标
        ridx = self.mp.bisect_right(val)  # 第一个左端点大于 val 的下标，即右邻居
        lidx = n if ridx == 0 else ridx - 1  # 左邻居下标为 ridx 减一；没有左邻居时记为 n（越界即表示不存在）
        keys = self.mp.keys()  # 取键视图（有序），便于按下标访问
        values = self.mp.values()  # 取值视图，与键视图一一对应
        if (  # 情形一：左右邻居都存在，且 val 恰好填上两段缝隙，可三合一
            lidx != n  # 左邻居确实存在
            and ridx != n  # 右邻居确实存在
            and values[lidx][1] + 1 == val  # val 紧接左区间右端
            and values[ridx][0] - 1 == val  # val 紧贴右区间左端
        ):  # 条件结束
            self.mp[keys[lidx]][1] = self.mp[keys[ridx]][1]  # 合并后左区间的右端点延伸到右区间的右端点
            self.mp.pop(keys[ridx])  # 右区间已被吸收，删除它的记录
        elif lidx != n and val <= values[lidx][1] + 1:  # 情形二：val 落在左区间内部或紧邻其右端，就并入左区间
            self.mp[keys[lidx]][1] = max(val, self.mp[keys[lidx]][1])  # 右端点取两者较大值；val 在区间内部时保持不变
        elif ridx != n and val >= values[ridx][0] - 1:  # 情形三：val 紧邻右区间左端或落在其内部，就并入右区间
            self.mp[keys[ridx]][0] = min(val, self.mp[keys[ridx]][0])  # 左端点取两者较小值；val 在区间内部时保持不变
        else:  # 情形四：val 与任何已有区间都不相邻
            self.mp[val] = [val, val]  # 以 val 为左右端点新建一个单点区间

    def getIntervals(self) -> List[List[int]]:  # 返回当前的全部区间
        return list(self.mp.values())  # 把有序的值视图转成列表返回，天然有序且互不相交


# 下面是 LeetCode 模板注释，仅演示对象的构造与调用方式
# # Your SummaryRanges object will be instantiated and called as such:
# # obj = SummaryRanges()
# # obj.addNum(val)
# # param_2 = obj.getIntervals()
