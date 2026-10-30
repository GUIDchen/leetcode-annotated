# 题目：855. 考场就座（Exam Room）
# 思路：用有序表维护所有空区间，按「落座后与最近者的距离」排序，每次取最优区间拆成两段；leave 时合并左右两段。
# 时间复杂度：单次 seat/leave 为 O(log n)；空间复杂度：O(n)，存放空区间与前后驱映射。
class ExamRoom:  # 考场类
    def __init__(self, n: int):  # n 为座位总数
        def dist(x):  # 计算空区间 x=(l, r) 落座后到最近者的距离
            l, r = x  # 解包区间端点
            return r - l - 1 if l == -1 or r == n else (r - l) >> 1  # 贴边界只能坐端点，距离为区间长度；否则坐中点，距离为长度一半

        self.n = n  # 保存座位总数
        self.ts = SortedList(key=lambda x: (-dist(x), x[0]))  # 空区间按「距离降序、左端点升序」排序，取第一个即最优
        self.left = {}  # 已坐位置 → 左侧最近的已坐位置
        self.right = {}  # 已坐位置 → 右侧最近的已坐位置
        self.add((-1, n))  # 初始只有一个跨越全场的虚拟空区间

    def seat(self) -> int:  # 安排一人就座并返回座位号
        s = self.ts[0]  # 取优先级最高的空区间
        p = (s[0] + s[1]) >> 1  # 默认坐在中点
        if s[0] == -1:  # 区间贴着左边界
            p = 0  # 只能坐 0 号座位
        elif s[1] == self.n:  # 区间贴着右边界
            p = self.n - 1  # 只能坐最后一个座位
        self.delete(s)  # 该区间被占用，先删除
        self.add((s[0], p))  # 拆出左半段区间
        self.add((p, s[1]))  # 拆出右半段区间
        return p  # 返回座位号

    def leave(self, p: int) -> None:  # p 位置的人离开
        l, r = self.left[p], self.right[p]  # 找到左右相邻的已坐位置
        self.delete((l, p))  # 删除左半段区间
        self.delete((p, r))  # 删除右半段区间
        self.add((l, r))  # 合并为一个空区间

    def add(self, s):  # 加入空区间并维护前后驱映射
        self.ts.add(s)  # 插入有序表
        self.left[s[1]] = s[0]  # 记录右端点的左邻居
        self.right[s[0]] = s[1]  # 记录左端点的右邻居

    def delete(self, s):  # 删除空区间并清理前后驱映射
        self.ts.remove(s)  # 从有序表移除
        self.left.pop(s[1])  # 清理右端点的左邻居记录
        self.right.pop(s[0])  # 清理左端点的右邻居记录


# Your ExamRoom object will be instantiated and called as such:
# obj = ExamRoom(n)
# param_1 = obj.seat()
# obj.leave(p)
