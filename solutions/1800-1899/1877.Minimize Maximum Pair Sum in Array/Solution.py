# 题目：1877. 数组中最大数对和的最小值（Minimize Maximum Pair Sum in Array）
# 思路：先升序排序，再让最小元素配最大元素（贪心：一大一小配对才能把每对和压平），所有配对和中的最大值即为答案。
# 时间复杂度：O(n log n)，由排序决定；空间复杂度：O(1)，只用了生成器表达式所需的常数空间。
class Solution:  # LeetCode 约定的题解类
    def minPairSum(self, nums: List[int]) -> int:  # nums：长度为偶数的整数数组；返回所有配对方案中最小的「最大数对和」
        nums.sort()  # 原地升序排序，让最小值与最大值可以两两配对
        return max(x + nums[-i - 1] for i, x in enumerate(nums[: len(nums) >> 1]))  # 枚举前一半元素 x，与对称位置 nums[-i-1] 配对，取配对和的最大值作为答案
