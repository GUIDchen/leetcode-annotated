# 题目：170. 两数之和 III - 数据结构设计（Two Sum III - Data Structure Design）
# 思路：字典记录「数值 → 出现次数」，find 时遍历已有数值 x，看补数 value - x 是否存在；x 与补数相同时要求出现次数大于 1。
# 时间复杂度：add 为 O(1)，find 为 O(k)（k 是不同数值个数）；空间复杂度：O(k)，存下所有加入过的数值。
class TwoSum:  # LeetCode 约定的题解类：支持 add 与 find 两数之和的数据结构

    def __init__(self):  # 构造函数：初始化计数器
        self.cnt = defaultdict(int)  # 字典：键是数值，值是出现次数；defaultdict(int) 让缺失键的默认计数为 0

    def add(self, number: int) -> None:  # 加入一个新数字
        self.cnt[number] += 1  # 该数字的计数加一，重复加入时次数累加

    def find(self, value: int) -> bool:  # 判断容器中是否存在两个数之和恰好等于 value
        for x, v in self.cnt.items():  # 遍历每个数值 x 及其出现次数 v
            y = value - x  # 还需要的另一个数（补数）
            if y in self.cnt and (x != y or v > 1):  # 补数存在，且（两个数不同 或 同一个数至少出现两次）才算一对
                return True  # 找到一对，立即返回 True
        return False  # 遍历完都没有配对成功


# Your TwoSum object will be instantiated and called as such:
# obj = TwoSum()
# obj.add(number)
# param_2 = obj.find(value)
