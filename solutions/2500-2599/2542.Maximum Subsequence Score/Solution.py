# 题目：2542. 最大子序列的分数（Maximum Subsequence Score）
# 思路：按 nums2 降序排序后依次加入，用最小堆维护最大的 k 个 nums1；当前 nums2 就是所选集合的最小值。
# 时间复杂度：O(n log n)，排序加堆操作；空间复杂度：O(n)，排序副本与堆。
class Solution:  # LeetCode 约定的题解类
    def maxScore(self, nums1: List[int], nums2: List[int], k: int) -> int:  # 返回选 k 个下标时 sum(nums1) * min(nums2) 的最大值
        nums = sorted(zip(nums2, nums1), reverse=True)  # 把两个数组成对打包并按 nums2 降序排序，元组比较时 nums1 只作为次序决定项
        q = []  # 用列表当小顶堆，保存当前选中的 nums1 值
        ans = s = 0  # ans 记录历史最优分数，s 维护堆中元素之和
        for a, b in nums:  # 按 nums2 从大到小遍历；a 是 nums2，b 是 nums1
            s += b  # 把当前 nums1 计入候选和
            heappush(q, b)  # 压入小顶堆（heappush 由判题环境的 from heapq import * 提供，不补 import）
            if len(q) == k:  # 凑满 k 个元素就尝试更新答案
                ans = max(ans, s * a)  # 分数 = 选中的 nums1 之和 × 选中集合中最小的 nums2，即 s * a
                s -= heappop(q)  # 弹出堆中最小的 nums1 并同步扣掉它的值，给后续元素腾位置
        return ans  # 返回最大分数
