# 题目：3107. 使数组中位数等于 K 的最少操作数（Minimum Operations to Make Median of Array Equal to K）
# 思路：先排序，定位上中位数 m；把 nums[m] 调到 k，再向左扫掉所有大于 k 的元素、或向右扫掉所有小于 k 的元素，逐个补齐差值。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，只在原列表上原地排序。
class Solution:  # LeetCode 约定的题解类
    def minOperationsToMakeMedianK(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：目标中位数
        nums.sort()  # 排序后中位数才有确定下标
        n = len(nums)  # 数组长度
        m = n >> 1  # 上中位数下标，偶数个元素时取右侧那个
        ans = abs(nums[m] - k)  # 先把中位数本身调整到 k 的代价
        if nums[m] > k:  # 中位数偏大，左侧偏大的数也要下调
            for i in range(m - 1, -1, -1):  # 从 m 向左逐个扫描
                if nums[i] <= k:  # 已经不大于 k，再往左更小，可以停止
                    break  # 结束循环
                ans += nums[i] - k  # 这个大于 k 的元素必须降到 k
        else:  # 中位数偏小，右侧偏小的数也要上调
            for i in range(m + 1, n):  # 从 m 向右逐个扫描
                if nums[i] >= k:  # 已经不小于 k，再往右更大，可以停止
                    break  # 结束循环
                ans += k - nums[i]  # 这个小于 k 的元素必须升到 k
        return ans  # 返回最少操作次数
