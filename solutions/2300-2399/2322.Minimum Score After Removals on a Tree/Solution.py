# 题目：2322. 从树中删除边的最小分数（Minimum Score After Removals on a Tree）
# 核心思路：先固定第一刀把树切成两半并求出其中一侧的异或和，再在这侧内部枚举第二刀，用三段异或值的极差更新最小分数。
# 时间复杂度：O(n^2)，每条边都会触发一次内部 DFS；空间复杂度：O(n)，邻接表与递归栈。
class Solution:  # LeetCode 约定的题解类
    def minimumScore(self, nums: List[int], edges: List[List[int]]) -> int:  # nums：节点权值；edges：无向边列表
        def dfs(i: int, fa: int) -> int:  # 求以 i 为根、父节点为 fa 的子树的异或和
            res = nums[i]  # 先放入当前节点权值
            for j in g[i]:  # 遍历 i 的所有邻居
                if j != fa:  # 跳过父节点，避免走回头路
                    res ^= dfs(j, i)  # 异或上这棵子树的结果
            return res  # 返回子树异或和

        def dfs2(i: int, fa: int) -> int:  # 固定第一刀后，在子树内部枚举第二刀
            nonlocal s, s1, ans  # 声明要修改外层变量：全树异或和、第一刀一侧的值与答案
            res = nums[i]  # 当前节点权值
            for j in g[i]:  # 遍历邻居
                if j != fa:  # 不回头
                    s2 = dfs2(j, i)  # 递归得到 j 子树异或和，即第二刀切下的那一部分
                    res ^= s2  # 把这部分并入当前子树
                    mx = max(s ^ s1, s2, s1 ^ s2)  # 三段异或值中的最大值
                    mn = min(s ^ s1, s2, s1 ^ s2)  # 三段异或值中的最小值
                    ans = min(ans, mx - mn)  # 极差即分数，更新最小分数
            return res  # 返回子树异或和

        g = defaultdict(list)  # 邻接表：节点 -> 邻居列表
        for a, b in edges:  # 遍历每条边建图
            g[a].append(b)  # a 的邻居加上 b
            g[b].append(a)  # b 的邻居加上 a
        s = reduce(lambda x, y: x ^ y, nums)  # 全树所有节点权值的异或和
        n = len(nums)  # 节点个数
        ans = inf  # 答案先置为无穷大
        for i in range(n):  # 枚举第一条被删边的一个端点
            for j in g[i]:  # 枚举第一条被删边的另一个端点
                s1 = dfs(i, j)  # 求出第一刀切下那一侧的异或和
                dfs2(i, j)  # 在这一侧内部枚举第二刀
        return ans  # 返回最小分数
