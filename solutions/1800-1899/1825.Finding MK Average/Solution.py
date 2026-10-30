# 题目：1825. 求出 MK 平均值（Finding MK Average）
# 核心思路：用 lo/mid/hi 三个有序表分别保存窗口内最小的 k 个、中间部分、最大的 k 个元素，mid 维护元素和 s；每次加入新元素并淘汰最旧元素后，把三部分大小调回 k / m-2k / k，平均值即 s 整除 (m-2k)。
# 时间复杂度：addElement 为 O(log m)，calculateMKAverage 为 O(1)；空间复杂度：O(m)，队列与三个有序表合计最多 m 个元素。
class MKAverage:  # 题解类：维护最近 m 个数并计算 MK 平均值
    def __init__(self, m: int, k: int):  # 构造函数：m 为窗口大小，k 为剔除的最小/最大元素个数
        self.m = m  # 保存窗口大小
        self.k = k  # 保存剔除个数
        self.s = 0  # 中间部分元素之和
        self.q = deque()  # 双端队列保存窗口内元素，用于淘汰最旧元素
        self.lo = SortedList()  # 保存最小的 k 个元素
        self.mid = SortedList()  # 保存中间部分元素
        self.hi = SortedList()  # 保存最大的 k 个元素

    def addElement(self, num: int) -> None:  # 加入一个新元素
        if not self.lo or num <= self.lo[-1]:  # 比 lo 最大值还小，归入最小的 k 个
            self.lo.add(num)  # 放入 lo
        elif not self.hi or num >= self.hi[0]:  # 或比 hi 最小值还大，归入最大的 k 个
            self.hi.add(num)  # 放入 hi
        else:  # 否则属于中间部分
            self.mid.add(num)  # 放入 mid
            self.s += num  # mid 的和同步累加
        self.q.append(num)  # 新元素入队，队首始终是窗口内最旧的元素
        if len(self.q) > self.m:  # 窗口元素超过 m 个，需要淘汰最旧元素
            x = self.q.popleft()  # 取出最旧元素
            if x in self.lo:  # 它在 lo 中
                self.lo.remove(x)  # 从 lo 删除
            elif x in self.hi:  # 或在 hi 中
                self.hi.remove(x)  # 从 hi 删除
            else:  # 否则在 mid 中
                self.mid.remove(x)  # 从 mid 删除
                self.s -= x  # mid 的和扣掉它
        while len(self.lo) > self.k:  # lo 超过 k 个，把最大值挪进 mid
            x = self.lo.pop()  # 取出 lo 的最大值
            self.mid.add(x)  # 放入 mid
            self.s += x  # mid 的和增加
        while len(self.hi) > self.k:  # hi 超过 k 个，把最小值挪进 mid
            x = self.hi.pop(0)  # 取出 hi 的最小值（下标 0）
            self.mid.add(x)  # 放入 mid
            self.s += x  # mid 的和增加
        while len(self.lo) < self.k and self.mid:  # lo 不足 k 个时从 mid 补最小的
            x = self.mid.pop(0)  # 取 mid 的最小值
            self.lo.add(x)  # 放入 lo
            self.s -= x  # mid 的和减少
        while len(self.hi) < self.k and self.mid:  # hi 不足 k 个时从 mid 补最大的
            x = self.mid.pop()  # 取 mid 的最大值
            self.hi.add(x)  # 放入 hi
            self.s -= x  # mid 的和减少

    def calculateMKAverage(self) -> int:  # 计算最近 m 个数的 MK 平均值
        return -1 if len(self.q) < self.m else self.s // (self.m - 2 * self.k)  # 元素不足 m 个返回 -1，否则用 mid 的和整除中间元素个数（m - 2k）


# 判题器实例化对象后的调用示例（下面的原注释原样保留）
# Your MKAverage object will be instantiated and called as such:
# obj = MKAverage(m, k)
# obj.addElement(num)
# param_2 = obj.calculateMKAverage()
