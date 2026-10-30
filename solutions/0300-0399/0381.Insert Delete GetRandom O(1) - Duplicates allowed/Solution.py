# 题目：381. O(1) 时间插入、删除和获取随机元素 - 允许重复（Insert Delete GetRandom O(1) - Duplicates allowed）
# 思路：动态数组存全部元素，哈希表记录「值 → 该值出现的所有下标集合」；删除时用尾元素填洞并同步修正下标集合。
# 时间复杂度：insert / remove / getRandom 平均 O(1)；空间复杂度：O(n)，数组与全部下标集合共 O(n) 空间。
import random  # 导入 random 模块，getRandom 需要随机取样


class RandomizedCollection:  # 设计题要求的类名
    def __init__(self):  # 构造函数：两个容器初始为空
        """
        Initialize your data structure here.
        """
        self.m = {}  # 值 → 该值在数组中出现的所有下标集合
        self.l = []  # 动态数组，保存全部元素，支持 O(1) 随机下标访问

    def insert(self, val: int) -> bool:  # 插入 val，返回「插入前是否不含该值」
        """
        Inserts a value to the collection. Returns true if the collection did not already contain the specified element.
        """
        idx_set = self.m.get(val, set())  # 取 val 的下标集合，不存在时先给一个空集合
        idx_set.add(len(self.l))  # 新元素将被追加到数组末尾，记录它即将占据的下标
        self.m[val] = idx_set  # 写回哈希表（val 原本不存在时这就是新建条目）
        self.l.append(val)  # 把 val 追加到数组尾部，与前一步记录的下标保持一致
        return len(idx_set) == 1  # 集合大小为 1 说明这是首次插入，返回 True

    def remove(self, val: int) -> bool:  # 删除 val 的任意一次出现，返回「是否存在过该值」
        """
        Removes a value from the collection. Returns true if the collection contained the specified element.
        """
        if val not in self.m:  # 哈希表里没有 val 这个键，说明无元素可删
            return False  # 不存在，按题目要求返回 False
        idx_set = self.m[val]  # 取出 val 的全部下标集合
        idx = next(iter(idx_set))  # 任取一个待删除的下标
        last_idx = len(self.l) - 1  # 数组末尾下标，准备用尾元素填补空位
        self.l[idx] = self.l[last_idx]  # 把尾元素复制到要删除的位置
        idx_set.remove(idx)  # 从 val 的下标集合中删掉该位置

        last_idx_set = self.m[self.l[last_idx]]  # 取出尾元素（它刚被搬到 idx）原本的下标集合
        if last_idx in last_idx_set:  # 该集合里可能还记着 last_idx，而末尾即将被弹出
            last_idx_set.remove(last_idx)  # 先移除即将失效的末尾下标
        if idx < last_idx:  # 尾元素已被搬到位置 idx，新下标小于末尾下标
            last_idx_set.add(idx)  # 把新位置下标加回该元素的集合
        if not idx_set:  # val 的所有出现都删完了
            self.m.pop(val)  # 从哈希表中彻底移除 val 这个键
        self.l.pop()  # 删掉数组尾部元素
        return True  # 删除成功

    def getRandom(self) -> int:  # 等概率随机返回集合中的一个元素
        """
        Get a random element from the collection.
        """
        return -1 if len(self.l) == 0 else random.choice(self.l)  # 集合为空时返回 -1，否则等概率随机取一个元素


# Your RandomizedCollection object will be instantiated and called as such:
# obj = RandomizedCollection()
# param_1 = obj.insert(val)
# param_2 = obj.remove(val)
# param_3 = obj.getRandom()
