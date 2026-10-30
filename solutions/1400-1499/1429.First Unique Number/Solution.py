# 题目：1429. 第一个唯一数字（First Unique Number）
# 思路：Counter 统计频次，OrderedDict 只保留当前唯一的数字并记住插入顺序，查询时取首个键即可。
# 时间复杂度：add O(1)，showFirstUnique O(1)；空间复杂度：O(n)，n 为出现过的不同值个数。
class FirstUnique:  # 设计题：频次表 + 有序字典，只让「当前唯一」的值留在字典里
    def __init__(self, nums: List[int]):  # 构造：nums 为初始数字序列
        self.cnt = Counter(nums)  # Counter 一次统计每个数字的出现次数
        self.unique = OrderedDict({v: 1 for v in nums if self.cnt[v] == 1})  # OrderedDict 记住插入顺序，只收初始时就唯一的数字，之后取第一个即 O(1)

    def showFirstUnique(self) -> int:  # 返回当前第一个只出现一次的数字，没有则返回 -1
        return -1 if not self.unique else next(v for v in self.unique.keys())  # 字典为空返回 -1；否则取字典的第一个键（最早插入的唯一值）

    def add(self, value: int) -> None:  # 动态追加一个数字
        self.cnt[value] += 1  # 频次加一，它可能因此不再唯一
        if self.cnt[value] == 1:  # 加完后恰为 1，说明这是它第一次出现
            self.unique[value] = 1  # 新晋唯一值，插入有序字典尾部
        elif value in self.unique:  # 否则它已经重复过，但仍可能还留在字典里
            self.unique.pop(value)  # 从字典中移除，避免被当成唯一值返回


# Your FirstUnique object will be instantiated and called as such:
# obj = FirstUnique(nums)
# param_1 = obj.showFirstUnique()
# obj.add(value)
