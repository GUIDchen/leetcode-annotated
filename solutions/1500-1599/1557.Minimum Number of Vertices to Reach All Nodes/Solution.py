# 题目：1557. 可以到达所有点的最少点数目（Minimum Number of Vertices to Reach All Nodes）
# 思路：入度为 0 的点必须被选为起点，而它们又能到达其余所有点，所以直接统计入度为 0 的节点即可。
# 时间复杂度：O(n + m)，n 为点数、m 为边数；空间复杂度：O(n)，用于存放入度计数。
class Solution:  # LeetCode 约定的题解类
    def findSmallestSetOfVertices(self, n: int, edges: List[List[int]]) -> List[int]:  # n：节点个数；edges：有向边列表
        cnt = Counter(t for _, t in edges)  # Counter 统计每个终点 t 出现的次数，即节点 t 的入度（未出现的键按 0 处理）
        return [i for i in range(n) if cnt[i] == 0]  # 入度为 0 的节点必须作为起点，列表推导按编号升序生成答案
