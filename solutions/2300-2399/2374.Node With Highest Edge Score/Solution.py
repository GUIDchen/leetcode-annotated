# 题目：2374. 边积分最高的节点（Node With Highest Edge Score）
# 思路：一次遍历，边 i -> edges[i] 把起点编号 i 累加到终点 edges[i] 的分数上，同时维护最高分节点（同分取小编号）。
# 时间复杂度：O(n)，只遍历一遍边数组；空间复杂度：O(n)，cnt 列表保存每个节点的边积分。
class Solution:  # LeetCode 约定的题解类
    def edgeScore(self, edges: List[int]) -> int:  # edges[i] 表示一条从 i 指向 edges[i] 的有向边
        ans = 0  # 当前边积分最高的节点，初始为 0 号节点
        cnt = [0] * len(edges)  # cnt[j] 是终点为 j 的所有边的起点编号之和
        for i, j in enumerate(edges):  # 同时取出边的起点 i 与终点 j
            cnt[j] += i  # 把起点编号 i 计入终点 j 的边积分
            if cnt[ans] < cnt[j] or (cnt[ans] == cnt[j] and j < ans):  # 分数更高，或同分但编号更小
                ans = j  # 更新答案
        return ans  # 返回边积分最高（同分取最小编号）的节点
