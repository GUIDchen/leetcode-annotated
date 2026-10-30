# 题目：1027. 最长等差数列（Longest Arithmetic Subsequence）
# 思路：动态规划。f[i][d + 500] 表示以 nums[i] 结尾、公差为 d 的最长等差数列长度；枚举 (i, k) 数对，用 f[k][d + 500] + 1 转移。
# 时间复杂度：O(n^2)，枚举所有数对；空间复杂度：O(n * 1001)，即二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def longestArithSeqLength(self, nums: List[int]) -> int:  # nums：输入数组；返回最长等差子序列的长度
        n = len(nums)  # n 是数组长度
        f = [[1] * 1001 for _ in range(n)]  # DP 表初值全为 1（每个元素自身就是长度 1 的等差序列），公差下标上限 1000
        ans = 0  # 记录过程中的最长长度
        for i in range(1, n):  # 枚举等差数列最后一个元素的下标 i
            for k in range(i):  # 枚举前一个元素的下标 k（k < i）
                j = nums[i] - nums[k] + 500  # 公差平移到非负下标：范围 [-500, 500] 映射到 [0, 1000]
                f[i][j] = max(f[i][j], f[k][j] + 1)  # 由以 k 结尾、同一公差的序列长度加一转移而来，取较大者
                ans = max(ans, f[i][j])  # 用当前状态更新全局最大值
        # 遍历结束后 ans 就是以某个元素结尾的最长等差数列长度
        return ans  # 返回最长长度
