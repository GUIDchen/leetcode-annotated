# 题目：1984. 学生分数的最小差值（Minimum Difference Between Highest and Lowest of K Scores）
# 思路：排序后最优的 k 个分数一定是连续的一段，用生成器枚举所有长度为 k 的窗口取最小极差。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，不计排序内部开销。
class Solution:  # LeetCode 约定的题解类
    def minimumDifference(self, nums: List[int], k: int) -> int:  # 返回选出 k 个分数后的最小极差
        nums.sort()  # 原地升序排序，使最优的 k 个分数成为连续的一段
        return min(nums[i + k - 1] - nums[i] for i in range(len(nums) - k + 1))  # 枚举所有长度为 k 的窗口，取「右端点减左端点」的最小值
