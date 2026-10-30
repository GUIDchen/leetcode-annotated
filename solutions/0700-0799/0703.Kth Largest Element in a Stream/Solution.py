# 题目：703. 数据流中的第 K 大元素（Kth Largest Element in a Stream）
# 思路：用小顶堆只保留最大的 k 个元素，堆顶就是这 k 个里最小的，即第 k 大；每次插入后若超过 k 个就弹出最小值。
# 时间复杂度：单次 add 为 O(log k)，构造函数为 O(n log k)；空间复杂度：O(k)，堆中最多保存 k 个元素。
class KthLargest:  # LeetCode 约定的题解类（构造时传入 k 与初始数据流）

    def __init__(self, k: int, nums: List[int]):  # 构造函数：k 是要求的第 k 大，nums 是初始的数据流
        self.k = k  # 把 k 记到实例属性，add 里要靠它维持堆的大小
        self.min_q = []  # 堆初始化为空列表，heapq 提供的就是小顶堆
        for x in nums:  # 逐个把初始元素喂进堆
            self.add(x)  # 复用 add 的插入与收缩逻辑，保证初始化后也是「最大的 k 个」

    def add(self, val: int) -> int:  # 加入一个新值，返回当前数据流中的第 k 大元素
        heappush(self.min_q, val)  # 先把新值压入小顶堆
        if len(self.min_q) > self.k:  # 堆内元素个数超过 k 个
            heappop(self.min_q)  # 弹出最小值，保证堆里始终只有最大的 k 个
        return self.min_q[0]  # 堆顶是这 k 个元素中最小的那个，也就是第 k 大


# Your KthLargest object will be instantiated and called as such:
# obj = KthLargest(k, nums)
# param_1 = obj.add(val)
