# 题目：480. 滑动窗口中位数（Sliding Window Median）
# 思路：用「取负」的大根堆 small 存较小的一半、小根堆 large 存较大的一半，中位数只取自两个堆顶；删除用 defaultdict 记待删次数做懒删除，元素冒到堆顶时才真正弹出。
# 时间复杂度：每次 add_num/remove_num 是 O(log k)，共 n 次操作即 O(n log k)；空间复杂度：O(k)，两个堆与延迟删除表都只存窗口内的元素。
class MedianFinder:  # 辅助结构：维护长度固定为 k 的滑窗，支持加元素、删元素、取中位数
    def __init__(self, k: int):  # k 是窗口大小，决定中位数取单个堆顶还是两个堆顶的平均
        self.k = k  # 记录窗口大小
        self.small = []  # 存较小一半的堆；Python 只有小根堆，所以存相反数来当大根堆用
        self.large = []  # 存较大一半的小根堆
        self.delayed = defaultdict(int)  # 懒删除计数：值 → 尚未真正从堆中弹出的次数
        self.small_size = 0  # small 中的有效元素个数（不含待删除的）
        self.large_size = 0  # large 中的有效元素个数（不含待删除的）

    def add_num(self, num: int):  # 向结构中加入一个新元素
        if not self.small or num <= -self.small[0]:  # small 为空，或新值不大于 small 堆顶的相反数（即真实最大值），说明它属于较小的一半
            heappush(self.small, -num)  # 存入取负后的值，这样小根堆的堆顶就对应较小一半里的最大值
            self.small_size += 1  # 较小一半的有效元素数加一
        else:  # 否则新值属于较大的一半
            heappush(self.large, num)  # 直接存入小根堆
            self.large_size += 1  # 较大一半的有效元素数加一
        self.rebalance()  # 加入后两堆大小可能失衡，调整一次

    def find_median(self) -> float:  # 返回当前窗口的中位数
        return -self.small[0] if self.k & 1 else (-self.small[0] + self.large[0]) / 2  # 奇数个元素时中位数是较小一半的最大值；偶数时取两个堆顶的平均

    def remove_num(self, num: int):  # 从结构中删除一个元素：窗口右移时移出最左端的那个值
        self.delayed[num] += 1  # 懒删除：先只记录待删次数，真正弹出留到它成为堆顶时再做
        if num <= -self.small[0]:  # 要删的值属于较小一半
            self.small_size -= 1  # 较小一半的有效元素数减一
            if num == -self.small[0]:  # 只有它正压在堆顶时才需要真正弹出
                self.prune(self.small)  # 清理 self.small 堆顶的过期元素
        else:  # 要删的值属于较大一半
            self.large_size -= 1  # 较大一半的有效元素数减一
            if num == self.large[0]:  # 位于 large 的堆顶
                self.prune(self.large)  # 清理 large 堆顶的过期元素
        self.rebalance()  # 删除后重新平衡两堆

    def prune(self, pq: List[int]):  # pq 就是 self.small 或 self.large 之一
        sign = -1 if pq is self.small else 1  # 收到的是小根堆本身，所以比较待删键时要还原符号：small 存的是相反数
        while pq and sign * pq[0] in self.delayed:  # 堆非空且堆顶仍有待删标记时才需要处理
            self.delayed[sign * pq[0]] -= 1  # 用掉一次待删标记
            if self.delayed[sign * pq[0]] == 0:  # 判断这次用掉之后是否已经没有待删记录了
                self.delayed.pop(sign * pq[0])  # 归零就删掉这个键，避免残留 0 干扰后面的判断
            heappop(pq)  # 真正弹出这个已过期的堆顶

    def rebalance(self):  # 维持「small 比 large 多 0 个或 1 个元素」这一不变式
        if self.small_size > self.large_size + 1:  # small 太多，挪一个到 large
            heappush(self.large, -heappop(self.small))  # 弹出 small 的堆顶（存的是相反数，取反后即较小一半的最大值）交给 large
            self.small_size -= 1  # 同步两堆的有效元素计数
            self.large_size += 1  # 同上：large 加一
            self.prune(self.small)  # 挪走后 small 的新堆顶也可能已过期
        elif self.small_size < self.large_size:  # 反之 large 太多，挪一个到 small
            heappush(self.small, -heappop(self.large))  # 弹出 large 的最小值，取负后压入 small
            self.large_size -= 1  # 同步两堆的有效元素计数
            self.small_size += 1  # 同上：small 加一
            self.prune(self.large)  # large 的新堆顶同样需要清理


class Solution:  # 主解：用上面的 MedianFinder 维护长度 k 的滑动窗口
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:  # nums 是原数组，k 是窗口长度；返回每个窗口的中位数组成的列表
        finder = MedianFinder(k)  # 构造窗口大小为 k 的维护器
        for x in nums[:k]:  # 先把前 k 个元素装进窗口
            finder.add_num(x)  # 逐个加入
        ans = [finder.find_median()]  # 记录第一个窗口的中位数
        for i in range(k, len(nums)):  # 窗口每右移一格
            finder.add_num(nums[i])  # 加入新的右端元素
            finder.remove_num(nums[i - k])  # 移出原来的左端元素
            ans.append(finder.find_median())  # 记录当前窗口的中位数
        return ans  # 返回所有窗口的中位数序列
