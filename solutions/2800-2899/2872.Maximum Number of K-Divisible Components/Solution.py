# 题目：2872. 可以被 K 整除连通块的最大数目（Maximum Number of K-Divisible Components）
# 思路：以 0 为根做后序 DFS，某棵子树的和能被 k 整除就把它切下来成为一块，只把余数部分向上合并。
# 时间复杂度：O(n)，每个节点与每条边只访问一次；空间复杂度：O(n)，邻接表与递归栈。
class Solution:  # LeetCode 约定的题解类
    def maxKDivisibleComponents(  # 参数较长所以分行书写：n 是节点数，edges 是无向边，values 是权值，k 是整除因子
        self, n: int, edges: List[List[int]], values: List[int], k: int  # 接收 self 与全部题目参数
    ) -> int:  # 返回最多能切出的、可被 k 整除的连通块数目
        def dfs(i: int, fa: int) -> int:  # 后序 DFS：i 为当前节点，fa 为父节点，返回当前子树和
            s = values[i]  # 以 i 为根的子树和，先算上自己的权值
            for j in g[i]:  # 遍历 i 的所有邻居
                if j != fa:  # 跳过父节点，避免走回头路
                    s += dfs(j, i)  # 递归累加子树的贡献
            nonlocal ans  # 声明 ans 来自外层函数，才能在闭包里修改它
            ans += s % k == 0  # 子树和能被 k 整除就多切一块，布尔值当 0/1 使用
            return s  # 把当前子树和返回给父节点

        g = [[] for _ in range(n)]  # 邻接表：g[u] 保存所有与 u 相邻的节点
        for a, b in edges:  # 逐条边建图
            g[a].append(b)  # a 的邻居里加入 b
            g[b].append(a)  # b 的邻居里加入 a（无向图要双向添加）
        ans = 0  # 可切出的连通块计数
        dfs(0, -1)  # 以 0 号节点为根开始 DFS，根的父节点记为 -1
        return ans  # 返回答案
