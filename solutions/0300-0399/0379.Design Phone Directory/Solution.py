# 题目：379. 电话目录管理系统（Design Phone Directory）
# 思路：用一个哈希集合维护所有当前可分配的号码，取号时弹出一个、归还时加回，均摊 O(1)。
# 时间复杂度：构造 O(n)，get / check / release 平均 O(1)；空间复杂度：O(n)，集合最多存 n 个号码。
class PhoneDirectory:  # 设计题要求的类名

    def __init__(self, maxNumbers: int):  # maxNumbers 为号码总数，号码取值范围 [0, maxNumbers - 1]
        self.available = set(range(maxNumbers))  # 用集合保存全部初始可用的号码

    def get(self) -> int:  # 取出一个可用号码并从集合中删除，无可用时返回 -1
        if not self.available:  # 集合为空表示号码已耗尽
            return -1  # 没有可用号码，按题目约定返回 -1
        return self.available.pop()  # 集合 pop 会弹出并删除一个元素，即分配该号码

    def check(self, number: int) -> bool:  # 判断某个号码当前是否仍可分配
        return number in self.available  # 在集合中即表示可用

    def release(self, number: int) -> None:  # 归还号码，使其可以再次被分配
        self.available.add(number)  # 重新加入可用集合


# Your PhoneDirectory object will be instantiated and called as such:
# obj = PhoneDirectory(maxNumbers)
# param_1 = obj.get()
# param_2 = obj.check(number)
# obj.release(number)
