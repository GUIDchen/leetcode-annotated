# 题目：2102. 序列顺序查询（Sequentially Ordinal Rank Tracker）
# 思路：用 SortedList 维护按 (-score, name) 有序的集合，get 时按下标 ++i 依次取出第 1、2、3... 好的记录。
# 时间复杂度：单次 add / get 均为 O(log n)；空间复杂度：O(n)，保存全部记录。
class SORTracker:  # 题目要求实现的类
    def __init__(self):  # 构造函数：初始化有序列表和查询下标
        self.sl = SortedList()  # SortedList 自动保持有序，支持按下标 O(log n) 取值
        self.i = -1  # 查询下标，第一次 get 后自增为 0

    def add(self, name: str, score: int) -> None:  # add：往榜单里加入一条 name、score 记录
        self.sl.add((-score, name))  # 分数取负让高分排前面；同分时按名字字典序升序

    def get(self) -> str:  # get：按调用顺序返回第 1、2、3... 好的景点名
        self.i += 1  # 名次下标前移一位，第几次调用就取第几个
        return self.sl[self.i][1]  # 取出该名次元素的第二个分量，也就是名字


# Your SORTracker object will be instantiated and called as such:
# obj = SORTracker()
# obj.add(name,score)
# param_2 = obj.get()
