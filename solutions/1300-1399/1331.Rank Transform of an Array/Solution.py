# 题目：1331. 数组序号转换（Rank Transform of an Array）
# 思路：sorted(set(arr)) 得到有序去重表，元素在表中的下标加一就是它的序号；bisect_right 返回第一个大于 x 的位置，正好等于序号（从 1 开始）。
# 时间复杂度：O(n log n)，排序加 n 次二分；空间复杂度：O(n)，去重表与答案列表。
class Solution:  # 题解类
    def arrayRankTransform(self, arr: List[int]) -> List[int]:  # arr：输入数组，返回每个元素的序号（从 1 开始，重复元素同序号）
        t = sorted(set(arr))  # 去重后升序排列，t 中下标即名次（0 起）
        return [bisect_right(t, x) for x in arr]  # bisect_right 返回第一个大于 x 的下标，即从 1 开始的序号
