# 题目：3364. 最小正和子数组（Minimum Positive Sum Subarray）
# 思路：枚举左端点 i 与右端点 j，用增量 s 实时维护子数组和；当长度落在 [l, r] 且 s > 0 时更新最小答案。
# 时间复杂度：O(n^2)，需要枚举所有子数组端点；空间复杂度：O(1)，只用到常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def minimumSumSubarray(self, nums: List[int], l: int, r: int) -> int:  # nums：输入数组；l、r：子数组长度允许的闭区间范围
        n = len(nums)  # 数组长度，作为循环上界
        ans = inf  # 答案初值取无穷大，表示还没有找到合法子数组
        for i in range(n):  # 枚举子数组左端点 i
            s = 0  # 以 i 开头的子数组和，随右端点扩展而累加，避免重复求和
            for j in range(i, n):  # 枚举右端点 j，此时子数组为 nums[i..j]
                s += nums[j]  # 增量加入右端点元素，O(1) 得到新的子数组和
                if l <= j - i + 1 <= r and s > 0:  # 长度 j - i + 1 要在 [l, r] 内，且子数组和为正
                    ans = min(ans, s)  # 用当前正和更新最小答案
        return -1 if ans == inf else ans  # 找不到合法子数组时返回 -1，否则返回最小正和
