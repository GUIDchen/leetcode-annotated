# 题目：275. H 指数 II（H-Index II）
# 思路：citations 已升序，H 指数满足单调性，二分答案 mid，用 citations[n-mid] >= mid 判断可行性，不断收缩区间取最大可行值。
# 时间复杂度：O(log n)，二分答案；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def hIndex(self, citations: List[int]) -> int:  # citations：非递减排序的引用次数数组
        n = len(citations)  # n：论文篇数
        left, right = 0, n  # 二分区间 [left, right]，答案范围是 0..n
        while left < right:  # 区间没收缩完就继续二分
            mid = (left + right + 1) >> 1  # 取上中位数，配合下面 left = mid 才不会死循环
            if citations[n - mid] >= mid:  # citations[n-mid] 是倒数第 mid 篇，它 ≥ mid 说明 mid 可行
                left = mid  # mid 可行，尝试更大的答案
            else:  # 否则 mid 不可行
                right = mid - 1  # 收缩右边界
        return left  # left == right 即最大可行的 H 指数
