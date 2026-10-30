# 题目：2104. 子数组范围和（Sum of Subarray Ranges）
# 思路：枚举左端点 i，右端点 j 向右扩展，扩展过程中维护区间最小值与最大值，累加每个子数组的极差。
# 时间复杂度：O(n^2)，双重循环枚举全部子数组；空间复杂度：O(1)，只用了常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def subArrayRanges(self, nums: List[int]) -> int:  # nums 是输入数组，返回所有子数组极差之和
        ans, n = 0, len(nums)  # ans 累加答案，n 是数组长度
        for i in range(n - 1):  # 枚举子数组左端点；长度至少为 2 才有极差，所以到 n-2
            mi = mx = nums[i]  # 以 i 开头、长度为 1 的区间最小值和最大值都是 nums[i]
            for j in range(i + 1, n):  # 右端点从 i+1 开始向右扩展
                mi = min(mi, nums[j])  # 把 nums[j] 纳入区间后更新最小值
                mx = max(mx, nums[j])  # 同时更新最大值
                ans += mx - mi  # 这个子数组的极差是 mx - mi，累加进答案
        return ans  # 返回所有子数组极差之和
