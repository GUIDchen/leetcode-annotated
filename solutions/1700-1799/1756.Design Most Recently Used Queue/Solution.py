# 题目：1756. 设计最近使用（MRU）队列（Design Most Recently Used Queue）
# 思路：用列表维护 1..n 的顺序，fetch(k) 取出第 k 个元素后把它删掉并追加到队尾（即最近使用位置）。
# 时间复杂度：init O(n)、fetch O(n)（删除元素需搬移后续元素）；空间复杂度：O(n)，列表保存 n 个元素。
class MRUQueue:  # 题目要求实现的 MRU 队列类
    def __init__(self, n: int):  # 构造函数：队列初始存入 1..n
        self.q = list(range(1, n + 1))  # 生成 [1, 2, ..., n] 作为队列的初始内容

    def fetch(self, k: int) -> int:  # 取出并返回当前第 k 个元素，同时把它移动到队尾
        ans = self.q[k - 1]  # 题目下标从 1 开始，先记下第 k 个元素的值
        self.q[k - 1 : k] = []  # 用切片赋值成空列表，等价于删除下标 k-1 处的元素
        self.q.append(ans)  # 把这个元素追加到队尾，表示它成为最近使用的元素
        return ans  # 返回被取出的元素


# Your MRUQueue object will be instantiated and called as such:  # LeetCode 判题器的调用方式说明
# obj = MRUQueue(n)  # 用整数 n 构造队列对象
# param_1 = obj.fetch(k)  # 每次调用 fetch(k) 取出第 k 个元素
