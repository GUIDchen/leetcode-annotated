# 题目：1014. 最佳观光组合（Best Sightseeing Pair）
# 思路：把得分拆成 (values[i] + i) + (values[j] - j)，边遍历边维护左半部分的最大值，即可在线求出最大得分。
# 时间复杂度：O(n)，一趟扫描；空间复杂度：O(1)，只用两个变量。
class Solution:  # LeetCode 约定的题解类
    def maxScoreSightseeingPair(self, values: List[int]) -> int:  # values：每个景点的评分
        ans = mx = 0  # ans 目前的最优得分，mx 之前位置中 values[i] + i 的最大值
        for j, x in enumerate(values):  # 同时取得下标 j 与评分 x
            ans = max(ans, mx + x - j)  # 用此前最优的左端点与当前右端点配对（mx 已含 +i，这里补上 x - j），更新答案
            mx = max(mx, x + j)  # 当前景点也作为后续的候选左端点，值为 x + j
        return ans  # 返回最大得分
