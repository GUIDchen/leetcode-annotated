# 题目：2924. 找到冠军 II（Find Champion II）
# 思路：冠军是从未被战胜过的队伍，统计每支队伍的入度，入度为 0 的队伍恰好只有一支时它就是冠军，否则返回 -1。
# 时间复杂度：O(n + m)，m 为边数；空间复杂度：O(n)，额外使用入度数组。
class Solution:  # LeetCode 约定的题解类
    def findChampion(self, n: int, edges: List[List[int]]) -> int:  # n 支队伍，edges 中的 [u, v] 表示 u 比 v 强
        indeg = [0] * n  # 入度：每支队伍被多少支队伍战胜
        for _, v in edges:  # 遍历每条边，只关心终点
            indeg[v] += 1  # 被战胜的队伍入度加一
        return -1 if indeg.count(0) != 1 else indeg.index(0)  # 入度为 0 的队伍唯一时才是冠军，否则返回 -1
