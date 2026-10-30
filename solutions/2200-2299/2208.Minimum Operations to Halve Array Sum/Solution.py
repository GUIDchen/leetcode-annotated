# 题目：2208. 将数组和减半的最少操作次数（Minimum Operations to Halve Array Sum）
# 核心思路：贪心，每次操作当前最大的数（它减半后下降最多）；用小顶堆存相反数来模拟大顶堆。
# 时间复杂度：O(n log n)，每次操作两次堆操作；空间复杂度：O(n)，堆中存放 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def halveArray(self, nums: List[int]) -> int:  # nums 是待减半的数组
        s = sum(nums) / 2  # 目标是让总和减少原总和的一半，s 表示还需要减少多少
        pq = []  # 小顶堆，存相反数，堆顶 -x 就是当前最大值
        for x in nums:  # 遍历原数组
            heappush(pq, -x)  # 取负后入堆，这样堆顶对应最大的原值
        ans = 0  # 记录操作次数
        while s > 0:  # 还没减够就继续操作
            t = -heappop(pq) / 2  # 弹出当前最大值并减半，这是本次的减少量
            s -= t  # 剩余需要减少的量扣掉本次减少量
            heappush(pq, -t)  # 减半后的值取负重新入堆
            ans += 1  # 操作次数加一
        return ans  # 返回最少操作次数
