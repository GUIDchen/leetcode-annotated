# 题目：2349. 设计数字容器系统（Design a Number Container System）
# 思路：字典 d 存「下标 → 数字」，字典 g 存「数字 → 有序下标集合」；change 先摘掉旧数字，find 取集合最小值。
# 时间复杂度：change 为 O(log n)，find 为 O(1)；空间复杂度：O(m)，m 是被赋过值的下标个数。
class NumberContainers:  # 数字容器系统：支持按下标改值、按数字查最小下标
    def __init__(self):  # 构造函数
        self.d = {}  # 下标 → 当前数字
        self.g = defaultdict(SortedSet)  # 数字 → 有序下标集合，缺失的键会被自动建成空集合

    def change(self, index: int, number: int) -> None:  # 把下标 index 处的数字改成 number
        if index in self.d:  # 该下标此前被赋过值，需要先清理旧数字的索引
            old_number = self.d[index]  # 记下该下标原来的数字
            self.g[old_number].remove(index)  # 从旧数字的有序集合里移除这个下标
        self.d[index] = number  # 更新下标到新数字的映射
        self.g[number].add(index)  # 把下标加入新数字的有序集合（SortedSet 自动维护顺序）

    def find(self, number: int) -> int:  # 查询数字 number 所在的最小下标
        ids = self.g[number]  # 取出该数字的有序下标集合（未出现过则为空集合）
        return ids[0] if ids else -1  # 集合非空就返回最小下标，否则按题意返回 -1


# Your NumberContainers object will be instantiated and called as such:
# obj = NumberContainers()
# obj.change(index,number)
# param_2 = obj.find(number)
