# 3835. 开销小于等于 K 的子数组数目 / Count Subarrays With Cost Less Than or Equal to K（中等）
# 核心思路：滑动窗口配合两个单调队列求窗口最大值与最小值，代价 =(max-min)×长度；代价超过 k 时右移左端点，之后以 r 结尾的合法子数组数为 r-l+1。
# 复杂度：每个下标最多入队出队各一次，时间 O(n)，空间 O(n)。
class Solution:  # 统计代价不超过 k 的子数组个数
    def countSubarrays(self, nums: List[int], k: int) -> int:  # 返回满足条件的子数组数目
        ans = 0  # 答案计数
        q1 = deque()  # 单调递减队列，存窗口最大值的下标
        q2 = deque()  # 单调递增队列，存窗口最小值的下标
        l = 0  # 滑动窗口左端点
        for r, x in enumerate(nums):  # 右端点 r 与当前元素 x 一起遍历
            while q1 and nums[q1[-1]] <= x:  # 弹出队尾所有不大于 x 的下标，保持队列递减
                q1.pop()  # 被 x 击败的较小值出队
            while q2 and nums[q2[-1]] >= x:  # 弹出队尾所有不小于 x 的下标，保持队列递增
                q2.pop()  # 被 x 击败的较大值出队
            q1.append(r)  # 当前下标入最大值队列
            q2.append(r)  # 当前下标入最小值队列
            while l < r and (nums[q1[0]] - nums[q2[0]]) * (r - l + 1) > k:  # 代价 (窗口最大值-窗口最小值)×窗口长度 超过 k 时收缩左端点
                l += 1  # 左端点右移，窗口代价单调不增
                if q1[0] < l:  # 最大值队首下标已滑出窗口
                    q1.popleft()  # 从队首弹出
                if q2[0] < l:  # 最小值队首下标已滑出窗口
                    q2.popleft()  # 从队首弹出
            ans += r - l + 1  # 以 r 结尾、左端点取 l..r 的子数组共 r-l+1 个，全部合法
        return ans  # 返回合法子数组总数
