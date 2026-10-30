# 题目：933. 最近的请求次数（Number of Recent Calls）
# 思路：用队列维护滑动窗口。每次 ping 先入队，再把早于 t-3000 的队首弹掉，剩下的元素个数就是答案。
# 时间复杂度：均摊 O(1)，每个请求最多入队、出队各一次；空间复杂度：O(W)，W 为 3000 毫秒窗口内的请求数。
class RecentCounter:  # 按题目要求实现的计数器类
    def __init__(self):  # 构造函数
        self.q = deque()  # 双端队列，队首是最早的请求时间

    def ping(self, t: int) -> int:  # t 是本次请求的时间戳（毫秒，严格递增）
        self.q.append(t)  # 新请求追加到队尾
        while self.q[0] < t - 3000:  # 把早于 t-3000 的请求从队首弹出，维护长度为 3000 的窗口
            self.q.popleft()  # 弹出队首
        return len(self.q)  # 窗口内的请求数即答案


# 下面三行是 LeetCode 判题器给出的调用示例（本题实现的是类而不是单个函数）。
# Your RecentCounter object will be instantiated and called as such:
# obj = RecentCounter()
# param_1 = obj.ping(t)
