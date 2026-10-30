# 题目：2368. 受限条件下可到达节点的数目（Reachable Nodes With Restrictions）
# 核心思路：建无向邻接表，把 restricted 直接塞进 visited 集合当墙，再从 0 号节点 DFS，自身加所有未访问邻居的可达数量。
# 时间复杂度：O(n)，每个节点至多访问一次；空间复杂度：O(n)，邻接表、visited 集合与递归栈。
class Solution:  # LeetCode 约定的题解类
    def reachableNodes(  # 参数分多行书写：n 个节点、无向边 edges、受限节点 restricted
        self, n: int, edges: List[List[int]], restricted: List[int]  # n：节点个数；edges：无向边；restricted：禁止经过的节点
    ) -> int:  # 返回从 0 号节点出发能到达的节点个数
        def dfs(i: int) -> int:  # 内层递归函数：统计从 i 出发可达的节点数（包含 i 自己）
            vis.add(i)  # 进入就标记已访问，防止走回头路造成死循环
            return 1 + sum(j not in vis and dfs(j) for j in g[i])  # 自身算 1 个，再加上所有「未被访问」邻居的可达数量

        g = defaultdict(list)  # 邻接表：键是节点，值是与它相邻的节点列表，缺失的键自动补空列表
        for a, b in edges:  # 遍历每条无向边
            g[a].append(b)  # 记录 a → b 的邻边
            g[b].append(a)  # 记录 b → a 的邻边，双向添加才是无向图
        vis = set(restricted)  # 受限节点一开始就放进 visited，dfs 会自动绕开它们
        return dfs(0)  # 从 0 号节点开始统计答案
