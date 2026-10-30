# 题目：2389. 和有限的最长子序列（Longest Subsequence With Limited Sum）
# 思路：先排序并求前缀和，答案就是前缀和数组中 ≤ 查询值的元素个数，用 bisect_right 直接查得。
# 时间复杂度：O(n log n + q log n)，排序 O(n log n)、每个查询二分 O(log n)；空间复杂度：O(n)，额外的前缀和列表。
class Solution:  # LeetCode 约定的题解类
    def answerQueries(self, nums: List[int], queries: List[int]) -> List[int]:  # nums：候选数组；queries：每个查询的上限
        nums.sort()  # 升序排序：要取尽量多的数，就应优先选最小的数
        s = list(accumulate(nums))  # 前缀和列表，s[i] 表示前 i+1 个最小元素之和
        return [bisect_right(s, q) for q in queries]  # 第一个 > q 的前缀和下标，即能取的个数
