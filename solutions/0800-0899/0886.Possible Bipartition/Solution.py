# 题目：886. 可能的二分法（Possible Bipartition）
# 思路：把「互相讨厌」建成无向图，DFS 二分染色；相邻点同色即冲突，所有连通块都染成功才可行。
# 时间复杂度：O(n + m)，m 为讨厌关系数，每条边访问两次；空间复杂度：O(n + m)，邻接表 + 染色数组。
class Solution:  # LeetCode 约定的题解类
    def possibleBipartition(self, n: int, dislikes: List[List[int]]) -> bool:  # n 个结点，dislikes 为互相讨厌的点对
        def dfs(i, c):  # 内嵌 dfs：把结点 i 染成颜色 c，返回当前连通块能否二分
            color[i] = c  # 先给当前结点上色
            for j in g[i]:  # 遍历与 i 相邻的所有结点
                if color[j] == c:  # 邻居颜色与自己相同，出现冲突
                    return False  # 冲突即无法二分
                if color[j] == 0 and not dfs(j, 3 - c):  # 邻居未染色时递归染成相反色 3-c，递归失败则返回 False
                    return False  # 递归染色失败，向上传递冲突
            return True  # 当前连通块染色成功

        g = defaultdict(list)  # 邻接表：defaultdict 访问缺失键时自动创建空列表
        color = [0] * n  # 0 表示未染色，1 和 2 表示分属两组
        for a, b in dislikes:  # 逐条关系建无向图
            a, b = a - 1, b - 1  # 编号 1..n 转成 0..n-1
            g[a].append(b)  # a 讨厌 b，加边 a→b
            g[b].append(a)  # b 讨厌 a，加反向边，构成无向图
        return all(c or dfs(i, 1) for i, c in enumerate(color))  # 对每个未染色点开启新连通块（已染色 c 非 0 直接通过）；all 短路，遇到失败立即返回 False
