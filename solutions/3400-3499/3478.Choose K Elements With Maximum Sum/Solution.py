# 3478. 选出和最大的 K 个元素（Choose K Elements With Maximum Sum）
# 核心思路：把 (nums1[i], i) 排序后用指针 j 把 nums1 值严格小于当前值的元素对应的 nums2 值维护进大小不超过 k 的小根堆，堆内和即答案，nums1 相等的元素共享同一批候选。
# 复杂度：时间 O(n log n)，空间 O(n)
class Solution:  # 解题类
    def findMaxSum(self, nums1: List[int], nums2: List[int], k: int) -> List[int]:  # 返回每个下标对应的、至多 k 个元素的最大和
        arr = [(x, i) for i, x in enumerate(nums1)]  # 把 (nums1 的值, 原始下标) 打包并用于排序
        arr.sort()  # 按 nums1 的值升序排序
        pq = []  # 小根堆，保留当前最大的至多 k 个 nums2 值
        s = j = 0  # s 是堆内和，j 是尚未入堆的左指针
        n = len(arr)  # 元素个数
        ans = [0] * n  # 存放每个下标的答案
        for h, (x, i) in enumerate(arr):  # 从最小的 nums1 值开始向后推进
            while j < h and arr[j][0] < x:  # 把 nums1 值严格小于 x 的元素补进候选集合
                y = nums2[arr[j][1]]  # 取该候选元素对应的 nums2 值
                heappush(pq, y)  # 压入小根堆
                s += y  # 同步累加堆内和
                if len(pq) > k:  # 堆内元素超过 k 个时
                    s -= heappop(pq)  # 弹出堆顶最小值并从和中扣除
                j += 1  # 左指针右移，该元素之后不再计入
            ans[i] = s  # 当前堆内和就是下标 i 的答案
        return ans  # 返回答案数组
