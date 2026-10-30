# 题目：2900. 最长相邻不相等子序列 I（Longest Unequal Adjacent Groups Subsequence I）
# 思路：groups 中连续相同的一段只需保留一个词，按下标顺序取每段的第一个词即可得到最长合法子序列。
# 时间复杂度：O(n)，只需一次遍历；空间复杂度：O(n)，用于保存答案列表。
class Solution:  # LeetCode 约定的题解类
    def getLongestSubsequence(self, words: List[str], groups: List[int]) -> List[str]:  # words 是候选词，groups 是对应的分组号
        return [words[i] for i, x in enumerate(groups) if i == 0 or x != groups[i - 1]]  # 列表推导：只保留下标 0 或与前一分组不同的位置，即每段相同分组的段首，其个数就是最长长度
