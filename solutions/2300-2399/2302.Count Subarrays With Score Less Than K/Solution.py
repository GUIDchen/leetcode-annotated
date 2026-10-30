# 题目：2302. 统计得分小于 K 的子数组数目（Count Subarrays With Score Less Than K）
# 思路：用 accumulate 求前缀和，枚举右端点，对该端点对应的子数组长度二分，找满足区间和乘长度小于 k 的最大长度并累加。
# 时间复杂度：O(n log n)，每个右端点二分一次；空间复杂度：O(n)，需要前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def countSubarrays(self, nums: List[int], k: int) -> int:  # nums：正整数数组；k：得分上限
        s = list(accumulate(nums, initial=0))  # 前缀和，s[i] 是前 i 个元素之和，initial=0 让空前缀也占一格
        ans = 0  # 满足条件的子数组计数
        for i in range(1, len(s)):  # 枚举右端点
            l, r = 0, i  # 二分长度区间为 0 到 i
            while l < r:  # 二分求满足条件的最大长度
                mid = (l + r + 1) >> 1  # 上取整的中点，配合 l = mid 避免死循环
                if (s[i] - s[i - mid]) * mid < k:  # 区间 [i-mid, i) 的元素和乘长度即得分，判断是否小于 k
                    l = mid  # 长度 mid 可行，向右收缩区间
                else:  # 得分不小于 k，说明长度过大
                    r = mid - 1  # 向左收缩区间
            ans += l  # 长度为 1 到 l 的子数组都满足条件，累加 l 个
        return ans  # 返回满足条件的子数组总数
