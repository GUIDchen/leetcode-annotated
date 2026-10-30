# 题目：2858. 可以到达每一个节点的最少边反转次数（Minimum Edge Reversals So Every Node Is Reachable）
# 思路：把有向边建成带权无向图（原方向权值 1、反方向 -1），先 DFS 求出以 0 为根的答案，再换根 DP 推出每个节点的答案。
# 复杂度：时间 O(n + m)，两次 DFS 各遍历每条边一次；空间 O(n + m)，邻接表加递归栈。
class Solution:  # LeetCode 约定的题解类
    def minEdgeReversals(self, n: int, edges: List[List[int]]) -> List[int]:  # n：节点数；edges：有向边，要求选定根后能到达所有节点
        ans = [0] * n  # ans[i] 表示以 i 为根时需要反转的边数
        g = [[] for _ in range(n)]  # 邻接表：g[i] 里存 (邻居, 权值)，1 沿原边，-1 需反转
        for x, y in edges:  # 把每条有向边拆成两条带权无向边
            g[x].append((y, 1))  # 原方向 x→y，权值 1，不需要反转
            g[y].append((x, -1))  # 反方向 y→x 需要反转，权值记为 -1

        def dfs(i: int, fa: int):  # 第一次 DFS：统计以 0 为根时的反转次数
            for j, k in g[i]:  # 遍历当前节点的每条邻边
                if j != fa:  # 跳过父节点，避免走回头路
                    ans[0] += int(k < 0)  # 反向边权值是 -1，说明要反转一次
                    dfs(j, i)  # 递归处理子树

        dfs(0, -1)  # 以 0 为根求初始答案，-1 表示没有父节点

        def dfs2(i: int, fa: int):  # 第二次 DFS：换根，由父节点答案推子节点答案
            for j, k in g[i]:  # 遍历当前节点的每条邻边
                if j != fa:  # 只处理真正的子节点
                    ans[j] = ans[i] + k  # 换根递推：沿原边不变，反向边答案减 1
                    dfs2(j, i)  # 继续向子树扩散答案

        dfs2(0, -1)  # 从根 0 出发把答案推到每个节点
        return ans  # 返回所有节点的最少反转次数
