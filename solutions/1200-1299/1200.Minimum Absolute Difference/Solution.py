# 题目：1200. 最小绝对差（Minimum Absolute Difference）
# 思路：排序后最小绝对差只可能出现在相邻元素之间；用 pairwise 求最小差，再筛出所有达到该差的相邻对。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，为返回结果的开销。
class Solution:  # LeetCode 约定的题解类
    def minimumAbsDifference(self, arr: List[int]) -> List[List[int]]:  # arr 是输入数组，返回所有绝对差等于最小绝对差的数对
        arr.sort()  # 原地升序排序，使最小绝对差只出现在相邻元素之间
        mi = min(b - a for a, b in pairwise(arr))  # pairwise 相邻遍历，取相邻差的最小值作为 mi
        return [[a, b] for a, b in pairwise(arr) if b - a == mi]  # 再次相邻遍历，保留差等于 mi 的数对，天然按升序输出
