# 题目：274. H 指数（H-Index）
# 思路：把引用次数降序排序，然后从 n 向下枚举 h，第一个满足 citations[h-1] >= h 的 h 就是最大 H 指数。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，原地排序。
class Solution:  # LeetCode 约定的题解类
    def hIndex(self, citations: List[int]) -> int:  # citations：每篇论文的引用次数
        citations.sort(reverse=True)  # 原地降序排序
        for h in range(len(citations), 0, -1):  # 从 n 递减枚举 h，range 右端 0 不包含，因此 h 最小为 1
            if citations[h - 1] >= h:  # 降序后 citations[h-1] 是前 h 篇里引用最少的一篇
                return h  # 满足「至少 h 篇被引 ≥ h」，直接返回 h
        return 0  # 所有 h 都不满足，H 指数为 0
