# 题目：895. 最大频率栈（Maximum Frequency Stack）
# 核心思路：字典记每个值的出现次数，小顶堆存 (-频率, -时间戳, 值)，让频率最高、最晚入栈的元素排在堆顶。
# 时间复杂度：push/pop 均 O(log n)；空间复杂度：O(n)，每次 push 入堆一个三元组。
class FreqStack:  # 最大频率栈：pop 返回出现次数最多的元素，次数相同时取最晚入栈的
    def __init__(self):  # 构造函数：初始化计数表、堆与时间戳
        self.cnt = defaultdict(int)  # 每个值当前的出现次数，键不存在时默认为 0
        self.q = []  # 小顶堆存放 (-频率, -时间戳, 值)，负号让频率最高、最新的元素排在堆顶
        self.ts = 0  # 单调递增的时间戳，用来区分入栈先后

    def push(self, val: int) -> None:  # 入栈：更新计数并把新状态压入堆
        self.ts += 1  # 时间戳自增
        self.cnt[val] += 1  # 该值出现次数加一
        heappush(self.q, (-self.cnt[val], -self.ts, val))  # 取负号后，频率更大、时间戳更新的元组更小，会浮到堆顶

    def pop(self) -> int:  # 出栈：弹出堆顶元素
        val = heappop(self.q)[2]  # 堆顶就是目标元素，元组第 3 项才是值
        self.cnt[val] -= 1  # 该值弹出一个，出现次数减一
        return val  # 返回被弹出的值


# Your FreqStack object will be instantiated and called as such:
# obj = FreqStack()
# obj.push(val)
# param_2 = obj.pop()
