# 题目：3266. K 次乘运算后的最终数组 II（Final Array State After K Multiplication Operations II）
# 思路：先用小根堆朴素模拟到堆顶元素不小于原数组最大值，此后每次操作都落在最小值上，故剩余 k 次可均摊倍数，用快速幂一次性乘回并按顺序分配余数。
# 时间复杂度：O(n log n + (n log m)·log n + n log k)，空间复杂度：O(n)，用于堆。
class Solution:  # LeetCode 约定的题解类
    def getFinalState(self, nums: List[int], k: int, multiplier: int) -> List[int]:  # nums：输入数组；k：操作次数；multiplier：每次乘的倍数；返回操作后的数组
        if multiplier == 1:  # 乘数为 1 时数组不会发生任何变化
            return nums  # 直接返回原数组
        pq = [(x, i) for i, x in enumerate(nums)]  # 用 (值, 下标) 建堆，下标用于最后写回结果
        heapify(pq)  # 原地建堆，得到小根堆
        m = max(nums)  # m：原数组最大值，也是朴素模拟阶段的上界
        while k and pq[0][0] < m:  # 只要还有操作次数且最小值仍小于 m，就继续朴素模拟
            x, i = heappop(pq)  # 取出最小的元素及其下标
            heappush(pq, (x * multiplier, i))  # 乘 multiplier 后重新入堆
            k -= 1  # 消耗一次操作次数
        n = len(nums)  # n：数组长度
        mod = 10**9 + 7  # mod：结果取模常量
        pq.sort()  # 排序后堆中元素按 (值, 下标) 升序排列
        for i, (x, j) in enumerate(pq):  # 按 (值, 下标) 升序依次写回数组
            nums[j] = x * pow(multiplier, k // n + int(i < k % n), mod) % mod  # 剩余 k 次操作均摊到 n 个元素：每个多乘 k//n 次，排名前 k%n 的再多乘一次
        return nums  # 返回最终数组
