# 题目：4085. 找到颜色树的根（Find Root of a Colored Tree）
# 核心思路：先把颜色映射成 0/1/2 并按边建无向邻接表，再逐个节点检验能否作根：度数不能超过 3；邻居中不能出现与自己同色的点，也不能有两个「另一种」颜色的邻居；满足「度数小于 3 且缺少那种颜色的邻居」的点就是合法根。
# 时间复杂度：O(n)，建图与逐点检验各一遍；空间复杂度：O(n)，邻接表及常数级计数器。
class Solution:  # LeetCode 约定的题解类
    def findColoredRoot(self, edges: list[list[int]], colors: str) -> int:  # edges：树的边；colors：每个节点的颜色字符；返回合法根的编号，不存在返回 -1
        d = {"W": 0, "R": 1, "B": 2}  # 把三种颜色映射成 0/1/2 的下标
        n = len(colors)  # n 为节点个数，节点编号 0 ~ n-1
        g = [[] for _ in range(n)]  # g 为无向邻接表
        for u, v in edges:  # 逐条边建图
            g[u].append(v)  # 把 v 加入 u 的邻居列表
            g[v].append(u)  # 把 u 加入 v 的邻居列表（无向图双向添加）
        ans = -1  # ans 记录找到的根，初始为「不存在」
        for u, vs in enumerate(g):  # 枚举每个节点作为候选根
            if len(vs) > 3:  # 度数超过 3 的节点不可能是合法根
                return -1  # 直接判定整体无解
            cnt = [0] * 3  # cnt 统计邻居中三种颜色各出现多少次
            for v in vs:  # 遍历 u 的全部邻居
                cnt[d[colors[v]]] += 1  # 对应颜色的计数加一
            c = d[colors[u]]  # c 为 u 自己的颜色编号
            if cnt[c] > 0 or cnt[(c + 2) % 3] > 1:  # 存在同色邻居，或者「另一种」颜色邻居多于一个，都不合法
                return -1  # 判定整体无解
            if len(vs) < 3 and cnt[(c + 2) % 3] == 0:  # 度数小于 3 且没有那种被禁止的邻居颜色，u 可以作根
                ans = u  # 更新答案为该节点
        return ans  # 返回找到的根，找不到则为 -1
