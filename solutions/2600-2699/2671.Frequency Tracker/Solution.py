# 题目：2671. 频率跟踪器（Frequency Tracker）
# 思路：cnt 记「数字 → 出现次数」，freq 记「出现次数 → 有多少个数字正好出现这么多次」；增删时同步搬动这两个计数。
# 时间复杂度：add / deleteOne / hasFrequency 都是 O(1)；空间复杂度：O(n)，两张哈希表最多存 n 个不同数字及其次数。
class FrequencyTracker:  # 频率跟踪器：cnt 记每个数的出现次数，freq 记每种出现次数被多少个数拥有
    def __init__(self):  # 构造函数：defaultdict(int) 在访问缺失键时自动给出 0，省去判空
        self.cnt = defaultdict(int)  # cnt[number] = number 当前出现的次数
        self.freq = defaultdict(int)  # freq[t] = 出现次数恰好为 t 的数字个数

    def add(self, number: int) -> None:  # 让 number 的出现次数加 1
        self.freq[self.cnt[number]] -= 1  # 先把 number 从「旧次数」的计数里减掉
        self.cnt[number] += 1  # 出现次数真正加 1
        self.freq[self.cnt[number]] += 1  # 再把它计入「新次数」的计数

    def deleteOne(self, number: int) -> None:  # 若 number 存在就删除一个；不存在时什么都不做
        if self.cnt[number]:  # 计数为 0 说明这个数从未出现，直接跳过
            self.freq[self.cnt[number]] -= 1  # 从「旧次数」的计数中移除 number
            self.cnt[number] -= 1  # 出现次数减 1
            self.freq[self.cnt[number]] += 1  # 把 number 加入「新次数」的计数（减到 0 时落到 freq[0]，不影响查询）

    def hasFrequency(self, frequency: int) -> bool:  # 查询是否恰好有数字出现了 frequency 次
        return self.freq[frequency] > 0  # freq[frequency] 大于 0 说明存在这样的数字


# 以下是 LeetCode 判题器给出的调用示例，不属于题解代码，原样保留
# Your FrequencyTracker object will be instantiated and called as such:
# obj = FrequencyTracker()
# obj.add(number)
# obj.deleteOne(number)
# param_3 = obj.hasFrequency(frequency)
