# 题目：1695. 删除子数组的最大得分（Maximum Erasure Value）
# 思路：滑动窗口 + 前缀和。窗口内元素必须互不相同，用数组 d 记录每个值上次出现的下标 1 位置，左端点 j 只会单调右移。
# 时间复杂度：O(n)，每个元素至多进出窗口各一次；空间复杂度：O(V)，d 的长度取决于 max(nums)。
class Solution:  # LeetCode 约定的题解类
    def maximumUniqueSubarray(self, nums: List[int]) -> int:  # nums：可以删除的子数组所在的输入数组
        d = [0] * (max(nums) + 1)  # d[v]：值 v 上一次出现的「右端点下标 + 1」，0 表示从未出现
        s = list(accumulate(nums, initial=0))  # 前缀和：s[i] = nums[0] + ... + nums[i-1]，initial=0 补上边界
        ans = j = 0  # ans：最大得分；j：当前合法窗口的左端点（下标从 0 开始）
        for i, v in enumerate(nums, 1):  # i 是窗口右端点的 1 基下标，v 是刚并入窗口的元素
            j = max(j, d[v])  # 若 v 之前出现过，窗口左端点必须跳过它的上一次出现位置
            ans = max(ans, s[i] - s[j])  # 用前缀和 O(1) 算出当前窗口和，并更新答案
            d[v] = i  # 记录 v 本次出现的位置，供后面重复时收缩窗口使用
        return ans  # 返回所有无重复元素连续子数组中的最大和
