# 题目：1466. 重新规划路线（Reorder Routes to Make All Paths Lead to the City Zero）
# 核心思路：把每条有向边建成带权无向边，从父侧走向子侧记代价 1，从子侧走向父侧记代价 0；从 0 号城市 DFS 把代价求和即为需要改向的边数。
# 时间复杂度：O(n)，每条边只访问两次；空间复杂度：O(n)，邻接表存 2(n-1) 条记录。
class Solution:  # LeetCode 约定的题解类
    def minReorder(self, n: int, connections: List[List[int]]) -> int:  # n 是城市数，connections 里每条记录是一条有向边 a -> b
        def dfs(a: int, fa: int) -> int:  # 当前城市 a 与父城市 fa，返回子树里需要改向的边数
            return sum(c + dfs(b, a) for b, c in g[a] if b != fa)  # 累加所有非父边：c 是这条边是否需要改向（0/1），再加上孩子子树的代价

        g = [[] for _ in range(n)]  # 邻接表，每个元素存 (邻居, 改向代价)
        for a, b in connections:  # 遍历每条原始有向边 a -> b
            g[a].append((b, 1))  # 从 a 走向 b：a 是父侧，最终需要 b -> a，与原方向相反，代价 1
            g[b].append((a, 0))  # 从 b 走向 a：b 是父侧，最终需要 a -> b，与原方向一致，代价 0
        return dfs(0, -1)  # 从 0 号城市出发，-1 表示没有父节点
