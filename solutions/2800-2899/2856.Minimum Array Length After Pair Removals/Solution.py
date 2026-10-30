# 题目：2856. 删除数对后的最小数组长度（Minimum Array Length After Pair Removals）
# 核心思路：每次删除出现次数最多的两种不同值各一个，用大根堆模拟，删除次数最多则剩余长度最少。
# 时间复杂度：O(n + m log m)，m 为不同值的个数；空间复杂度：O(m)。
class Solution:  # LeetCode 约定的题解类
    def minLengthAfterRemovals(self, nums: List[int]) -> int:  # nums 为有序数组，可删除任意两个不同值的元素
        cnt = Counter(nums)  # 统计每个值出现的次数
        pq = [-x for x in cnt.values()]  # 用负数模拟大根堆（heapq 是小根堆）
        heapify(pq)  # 原地建堆，代价为不同值个数
        ans = len(nums)  # 剩余元素个数
        while len(pq) > 1:  # 只要还有至少两种不同的值就能继续配对
            x, y = -heappop(pq), -heappop(pq)  # 取出个数最多的两种值（取负还原）
            x -= 1  # 各自消耗一个元素
            y -= 1  # 同上
            if x > 0:  # 还有剩余就放回堆中
                heappush(pq, -x)  # 以负数形式放回
            if y > 0:  # 第二种值同理
                heappush(pq, -y)  # 以负数形式放回
            ans -= 2  # 配对成功，剩余元素减 2
        return ans  # 返回剩余长度
