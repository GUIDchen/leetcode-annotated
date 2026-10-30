# 题目：1940. 排序数组之间的最长公共子序列（Longest Common Subsequence Between Sorted Arrays）
# 思路：数组内部元素互不相同，于是「在每个数组中都出现」等价于「出现次数等于数组个数」；统计每个值的出现次数后按值升序筛出来。
# 时间复杂度：O(S + 101)，S 为所有数组元素总数；空间复杂度：O(101) = O(1)。
class Solution:  # LeetCode 约定的题解类
    def longestCommonSubsequence(self, arrays: List[List[int]]) -> List[int]:  # arrays：若干升序数组，返回它们共有的元素
        cnt = [0] * 101  # cnt[x] 记录数值 x 一共在多少个数组中出现过，初值全 0
        for row in arrays:  # 逐个数组统计
            for x in row:  # 遍历当前数组中的每个元素
                cnt[x] += 1  # 该值的出现次数加一
        return [x for x, v in enumerate(cnt) if v == len(arrays)]  # enumerate 给出（数值 x, 出现次数 v），只保留在所有数组中都出现的值
