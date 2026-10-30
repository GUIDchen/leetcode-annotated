# 题目：2077. 殊途同归（Paths in Maze That Lead to Same Room）
# 思路：走廊构成无向图，枚举每个房间 i 的邻居组合 (j, k)，若 j、k 也相邻就得到一个三元环；每个环被数 3 次，最后除以 3。
# 时间复杂度：O(n + m + Σ deg(i)²)；空间复杂度：O(n + m)，用于邻接表。
class Solution:  # LeetCode 约定的题解类
    def numberOfPaths(self, n: int, corridors: List[List[int]]) -> int:  # n 是房间数（编号 1..n），corridors 是无向边列表
        g = defaultdict(set)  # 邻接表：房间号 → 邻居集合
        for a, b in corridors:  # 逐条读入走廊
            g[a].add(b)  # a 的邻居集合里加入 b
            g[b].add(a)  # b 的邻居集合里加入 a（无向图）
        ans = 0  # 统计三元环被数到的次数
        for i in range(1, n + 1):  # 枚举每个房间作为三元环的中间点
            for j, k in combinations(g[i], 2):  # 枚举该房间的任意两个不同邻居（组合，避免重复）
                if j in g[k]:  # 两个邻居也相邻，说明 i-j-k-i 是一个长度为 3 的环
                    ans += 1  # 计数加一
        return ans // 3  # 同一个三元环被 3 个顶点各数一次，除以 3
