# 题目：2538. 最大价值和与最小价值和的差值（Difference Between Maximum and Minimum Price Sum）
# 思路：树形 DP。dfs 返回 (a, b)：a 为以 i 为起点且计入末端权值的最大路径和，b 为不计末端权值的版本。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，邻接表与递归栈。
class Solution:  # LeetCode 约定的题解类
    def maxOutput(self, n: int, edges: List[List[int]], price: List[int]) -> int:  # n 为节点数，edges 为无向边，price 为节点价值
        def dfs(i, fa):  # 内层 DFS：i 为当前节点，fa 为父节点
            a, b = price[i], 0  # a 至少含 i 自身价值；b 不计末端价值，故从 0 起算
            for j in g[i]:  # 遍历 i 的邻居
                if j != fa:  # 跳过父节点，避免走回头的边
                    c, d = dfs(j, i)  # 递归子节点，拿到含末端价值的 c 与不含末端价值的 d
                    nonlocal ans  # 声明 ans 来自外层函数，不是 dfs 的局部变量
                    ans = max(ans, a + d, b + c)  # 用 a+d 或 b+c 组合出经过 i 的路径，更新全局最大值
                    a = max(a, price[i] + c)  # 更新 a：把子节点方向更长的路径接在 i 之后
                    b = max(b, price[i] + d)  # 更新 b：同理，但末端节点价值不计入
            return a, b  # 返回以 i 为起点的两个最大路径和

        g = defaultdict(list)  # 邻接表，defaultdict 让未出现的键自动得到空列表
        for a, b in edges:  # 遍历每条边
            g[a].append(b)  # 建立 a 到 b 的边
            g[b].append(a)  # 建立 b 到 a 的反向边
        ans = 0  # 答案初值为 0
        dfs(0, -1)  # 从 0 号节点出发遍历整棵树，dfs 内部会更新 ans
        return ans  # 返回最大路径和与最小路径和之差
