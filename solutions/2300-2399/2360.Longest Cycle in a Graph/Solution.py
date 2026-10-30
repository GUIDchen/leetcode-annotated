# 题目：2360. 图中的最长环（Longest Cycle in a Graph）
# 思路：每个点出度至多为 1，每个连通块形如“链 + 环”；沿出边走到无路或撞到已访问点，再在本次路径中定位环并取最长。
# 时间复杂度：O(n)，每个点至多被访问一次；空间复杂度：O(n)，访问标记数组与路径列表。
class Solution:  # LeetCode 约定的题解类
    def longestCycle(self, edges: List[int]) -> int:  # edges：每个点唯一的出边，-1 表示没有出边；返回最长环的长度
        n = len(edges)  # n 为节点总数
        vis = [False] * n  # 访问标记，保证每个点只被走一次
        ans = -1  # 没有环时按题目要求返回 -1
        for i in range(n):  # 依次枚举尚未访问的点作为起点
            if vis[i]:  # 已经访问过，说明属于之前处理过的链或环
                continue  # 跳过当前点
            j = i  # 从 i 开始沿出边前进
            cycle = []  # 记录本次走过的点（按访问顺序）
            while j != -1 and not vis[j]:  # 一直走到无出边（j == -1）或遇到已访问点为止
                vis[j] = True  # 标记当前点已访问，之后不再重复处理
                cycle.append(j)  # 把当前点按顺序记入本次路径
                j = edges[j]  # 沿出边继续前进
            if j == -1:  # 走到链尾：没有形成环
                continue  # 本连通块没有环，继续处理下一个起点
            m = len(cycle)  # m 为本次路径的长度
            k = next((k for k in range(m) if cycle[k] == j), inf)  # 找 j 在 cycle 中的位置；找不到时取 inf，使 m - k 为负数而不影响答案
            ans = max(ans, m - k)  # 环长 = 路径总长减去环入口前的链长
        return ans  # 返回最长环的长度
