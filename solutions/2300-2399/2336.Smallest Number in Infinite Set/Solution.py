# 题目：2336. 无限集中的最小数字（Smallest Number in Infinite Set）
# 核心思路：用有序集合保存「当前还在集合里的正整数」，最多调用 1000 次，所以初始化 1..1000；取最小值取首元素，放回即插入。
# 时间复杂度：构造 O(1000 log 1000)，popSmallest/addBack 均为 O(log n)；空间复杂度：O(1000) 即 O(1)。
class SmallestInfiniteSet:  # 无限集合类：维护当前还可用的正整数
    def __init__(self):  # 构造函数：初始化集合内容
        self.s = SortedSet(range(1, 1001))  # 装入 1..1000（end=1001 取不到），覆盖题目保证的最大调用次数

    def popSmallest(self) -> int:  # 弹出并返回集合中的最小数字
        x = self.s[0]  # 有序集合下标 0 处就是最小值
        self.s.remove(x)  # 按值删除这个最小值，模拟「被取出」
        return x  # 返回刚取出的最小值

    def addBack(self, num: int) -> None:  # 把一个之前被取出的数字放回集合
        self.s.add(num)  # 直接加入即可；有序集合会去重并保持有序


# Your SmallestInfiniteSet object will be instantiated and called as such:
# obj = SmallestInfiniteSet()
# param_1 = obj.popSmallest()
# obj.addBack(num)
