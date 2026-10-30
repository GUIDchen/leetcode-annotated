# 题目：380. O(1) 时间插入、删除和获取随机元素（Insert Delete GetRandom O(1)）
# 思路：动态数组存元素支持随机下标访问，哈希表存「值 → 下标」；删除时用尾元素覆盖被删位置，避免数组搬移。
# 时间复杂度：insert / remove / getRandom 平均 O(1)；空间复杂度：O(n)，数组与哈希表各存 n 个元素。
class RandomizedSet:  # 设计题要求的类名
    def __init__(self):  # 构造函数：容器初始为空
        self.d = {}  # 值 → 在数组中的下标
        self.q = []  # 动态数组，支持 O(1) 随机下标访问

    def insert(self, val: int) -> bool:  # 插入 val，若已存在则返回 False
        if val in self.d:  # 已存在，说明重复
            return False  # 重复插入按题目要求返回 False
        self.d[val] = len(self.q)  # 记录新元素在数组中的下标（即将追加到末尾）
        self.q.append(val)  # 把 val 追加到数组尾部
        return True  # 插入成功

    def remove(self, val: int) -> bool:  # 删除 val，若不存在则返回 False
        if val not in self.d:  # 不存在，说明无元素可删
            return False  # 不存在，直接返回 False
        i = self.d[val]  # 先取出 val 在数组中的下标
        self.d[self.q[-1]] = i  # 尾元素马上要被搬到位置 i，先更新它记录的下标
        self.q[i] = self.q[-1]  # 用尾元素覆盖待删除的位置，避免整体前移
        self.q.pop()  # 删掉尾部那份多余的元素
        self.d.pop(val)  # 最后从哈希表中移除 val
        return True  # 删除成功

    def getRandom(self) -> int:  # 等概率随机返回集合中的一个元素
        return choice(self.q)  # random.choice 在数组上等概率取样


# Your RandomizedSet object will be instantiated and called as such:
# obj = RandomizedSet()
# param_1 = obj.insert(val)
# param_2 = obj.remove(val)
# param_3 = obj.getRandom()
