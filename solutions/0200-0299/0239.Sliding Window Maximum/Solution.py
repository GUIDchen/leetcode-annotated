# 题目：239. 滑动窗口最大值（Sliding Window Maximum）
# 思路：小根堆里存 (-数值, 下标)，取负后堆顶就是窗口最大值；取堆顶前按下标把滑出窗口的堆顶弹掉。
# 时间复杂度：O(n log n)，每个元素至多入堆、出堆各一次；空间复杂度：O(n)，堆中最多同时保存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:  # nums 是输入数组，k 是窗口大小
        q = [(-v, i) for i, v in enumerate(nums[: k - 1])]  # 第一个窗口除末位外的元素入堆，数值取负，让小根堆顶部变成最大值
        heapify(q)  # 线性时间把列表整理成堆
        ans = []  # 保存每个窗口的最大值
        for i in range(k - 1, len(nums)):  # 窗口右端从 k-1 逐格右滑到数组末尾
            heappush(q, (-nums[i], i))  # 新进入窗口的元素连同下标入堆
            while q[0][1] <= i - k:  # 堆顶下标早于窗口左边界 i-k+1，已经滑出窗口
                heappop(q)  # 弹出过期堆顶，直到堆顶落在当前窗口内
            ans.append(-q[0][0])  # 取负号还原堆顶数值，即当前窗口最大值
        return ans  # 返回所有窗口最大值
