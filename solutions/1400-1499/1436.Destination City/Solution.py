# 题目：1436. 旅行终点站（Destination City）
# 思路：用集合收集所有作为起点出现过的城市，再从各航段的终点里挑出从未当过起点的那个。
# 时间复杂度：O(n)，n 为航段数；空间复杂度：O(n)，集合最多保存 n 个城市名。
class Solution:  # LeetCode 约定的题解类
    def destCity(self, paths: List[List[str]]) -> str:  # paths 的每一项是 [起点城市, 终点城市] 的一条航段
        s = {a for a, _ in paths}  # 集合推导式：一次性收集所有航段的起点城市
        return next(b for _, b in paths if b not in s)  # 在终点城市里找第一个从未当过起点的，它只进不出，就是旅行终点站
