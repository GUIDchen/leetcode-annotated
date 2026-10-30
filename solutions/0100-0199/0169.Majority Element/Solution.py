# 题目：169. 多数元素（Majority Element）
# 核心思路：Boyer-Moore 摩尔投票，遇到相同元素票数加一、不同元素票数减一；出现次数过半的元素在抵消后必然留下。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只维护候选元素与票数。
class Solution:  # LeetCode 约定的题解类
    def majorityElement(self, nums: List[int]) -> int:  # 求出现次数严格大于 n/2 的元素
        cnt = m = 0  # cnt：候选票数；m：当前候选元素
        for x in nums:  # 遍历数组中的每个元素
            if cnt == 0:  # 票数为 0，说明之前的候选已被完全抵消
                m, cnt = x, 1  # 以当前元素作为新候选，票数记为 1
            else:  # 候选仍然有效
                cnt += 1 if m == x else -1  # 与候选相同则加一票，不同则抵消一票
        return m  # 多数元素超过一半，最终剩下的候选就是答案
