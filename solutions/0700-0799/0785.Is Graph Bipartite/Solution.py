# 题目：785. 判断二分图（Is Graph Bipartite）
# 思路：对每个连通分量做 DFS 二染色（颜色 1 与 -1），一旦发现相邻两点同色就说明不是二分图。
# 时间复杂度：O(n + m)，每个点与每条边只访问一次；空间复杂度：O(n)，颜色数组与递归栈。
class Solution:  # LeetCode 约定的题解类
    def isBipartite(self, graph: List[List[int]]) -> bool:  # graph 是邻接表，返回这张无向图能否二染色
        def dfs(a: int, c: int) -> bool:  # 把结点 a 染成颜色 c，成功返回 True
            color[a] = c  # 记录结点 a 的颜色
            for b in graph[a]:  # 枚举 a 的所有邻居
                if color[b] == c or (color[b] == 0 and not dfs(b, -c)):  # 邻居同色即冲突；邻居未染色则递归染成反色，失败同样算冲突
                    return False  # 有矛盾，这片连通分量不是二分图
            return True  # a 引出的所有分支都染色成功

        n = len(graph)  # 结点个数
        color = [0] * n  # 0 表示未染色，1 与 -1 表示两种颜色
        for i in range(n):  # 图可能不连通，逐个点检查是否需要开启新分量
            if color[i] == 0 and not dfs(i, 1):  # 从未染色的点出发，任选颜色 1 开始染色
                return False  # 某个分量染色失败，整体不是二分图
        return True  # 全部分量都能二染色，返回 True
