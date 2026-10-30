# 3874. 具有恰好一个峰值的有效子数组（Valid Subarrays With Exactly One Peak）
# 核心思路：先找出所有「严格大于左右邻居」的峰位置；对每个峰 p，统计以它为唯一峰的子数组数量——左端点只能落在 p-k 到上一个峰之间，右端点只能落在 p 到 p+k 到下一个峰之间，两端方案数相乘再累加。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(n)。
class Solution:  # 题解类
    def validSubarrays(self, nums: list[int], k: int) -> int:  # 返回恰好含一个峰值且长度受限的子数组个数
        n = len(nums)  # 数组长度
        peaks = []  # 记录所有峰值的下标
        for i in range(1, n - 1):  # 首尾不可能成为峰值，从 1 遍历到 n-2
            if nums[i] > nums[i - 1] and nums[i] > nums[i + 1]:  # 严格大于左右邻居即为峰值
                peaks.append(i)  # 记录该峰位置

        ans = 0  # 答案累加器
        for j, p in enumerate(peaks):  # 枚举每一个峰，p 为峰下标
            left_min = max(p - k, 0)  # 左端点最远只能到 p-k，且不能越界
            if j > 0:  # 左侧还存在前一个峰
                left_min = max(left_min, peaks[j - 1] + 1)  # 左端点不能越过前一个峰，否则会出现两个峰

            right_max = min(p + k, n - 1)  # 右端点最远只能到 p+k，且不能越界
            if j < len(peaks) - 1:  # 右侧还存在后一个峰
                right_max = min(right_max, peaks[j + 1] - 1)  # 右端点不能越过后一个峰，否则会出现两个峰

            ans += (p - left_min + 1) * (right_max - p + 1)  # 左端点方案数 × 右端点方案数
        return ans  # 返回有效子数组总数
