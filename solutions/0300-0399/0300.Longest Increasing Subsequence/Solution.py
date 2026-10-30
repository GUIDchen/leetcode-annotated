# 题目：300. 最长递增子序列（Longest Increasing Subsequence）
# 思路：动态规划，f[i] 表示以 nums[i] 结尾的最长严格递增子序列长度，从前向后用 j 枚举所有可接在后面的前驱。
# 时间复杂度：O(n^2)，两层循环枚举数对；空间复杂度：O(n)，保存长度为 n 的 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def lengthOfLIS(self, nums: List[int]) -> int:  # nums：输入数组；返回最长严格递增子序列的长度
        n = len(nums)  # 数组长度
        f = [1] * n  # f[i]：以 nums[i] 结尾的最长递增子序列长度，每项至少为 1（只含自己）
        for i in range(1, n):  # 从第二个元素开始递推
            for j in range(i):  # 枚举 i 之前的所有位置作为前驱
                if nums[j] < nums[i]:  # 严格递增：前驱值必须小于当前值才能接上
                    f[i] = max(f[i], f[j] + 1)  # 接上 j 之后长度是 f[j]+1，与现有 f[i] 取较大者
        return max(f)  # 答案不一定在末尾，要取整张 DP 表的最大值
