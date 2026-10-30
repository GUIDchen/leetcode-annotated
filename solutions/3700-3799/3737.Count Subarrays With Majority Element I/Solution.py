# 3737. 统计主要元素子数组数目 I / Count Subarrays With Majority Element I
# 核心思路：枚举左右端点，用计数器维护区间内 target 的出现次数，若其出现次数严格大于区间长度的一半则答案加一。
# 复杂度：时间 O(n^2)，空间 O(1)。
class Solution:  # 定义 LeetCode 解法类
    def countMajoritySubarrays(self, nums: List[int], target: int) -> int:  # 返回 target 为多数元素的子数组个数
        n = len(nums)  # 数组长度
        ans = 0  # 答案计数
        for i in range(n):  # 枚举子数组左端点
            cnt = 0  # 当前子数组内 target 的出现次数
            for j in range(i, n):  # 枚举子数组右端点
                cnt += int(nums[j] == target)  # 把右端点纳入统计
                if cnt * 2 > j - i + 1:  # target 出现次数严格超过区间长度的一半
                    ans += 1  # 该子数组满足条件，答案加一
        return ans  # 返回答案
