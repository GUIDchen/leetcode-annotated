# 题目：1403. 非递增顺序的最小子序列（Minimum Subsequence in Non-Increasing Order）
# 思路：把数组降序排序，从大到小贪心累加子序列和 t；用总和 s 判断剩余和 s - t，一旦 t > s - t 立即停止，这样元素个数最少。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，存放结果与排序副本。
class Solution:  # LeetCode 约定的题解类
    def minSubsequence(self, nums: List[int]) -> List[int]:  # nums 为输入数组
        ans = []  # 存放最终子序列
        s, t = sum(nums), 0  # 元组解包：s 是数组总和，t 是子序列当前和
        for x in sorted(nums, reverse=True):  # 不改动 nums，用 sorted 产生降序副本后遍历
            t += x  # 累加子序列和
            ans.append(x)  # 把当前元素加入结果
            if t > s - t:  # s - t 为剩余元素之和，严格大于才满足题意
                break  # 满足条件即停止，保证子序列最短
        return ans  # 返回子序列（天然是非递增顺序）
