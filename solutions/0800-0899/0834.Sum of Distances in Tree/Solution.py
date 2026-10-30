# 题目：834. 树中距离之和（Sum of Distances in Tree）
# 思路：两遍 DFS。第一遍以 0 为根求出每个结点的子树大小与根的距离和 ans[0]；第二遍用换根公式 ans[j] = ans[i] + n - 2·size[j] 自上而下推出全部答案。
# 时间复杂度：O(n)，每个结点被两遍 DFS 各访问一次；空间复杂度：O(n)，邻接表加 ans、size 两个数组。
class Solution:  # LeetCode 约定的题解类
    def sumOfDistancesInTree(self, n: int, edges: List[List[int]]) -> List[int]:  # 返回每个结点到其余所有结点的距离之和
        def dfs1(i: int, fa: int, d: int):  # 第一遍后序 DFS：i 当前结点，fa 父结点，d 是 i 到根 0 的距离
            ans[0] += d  # 把 i 到根的距离累加，最终得到根结点的距离和 ans[0]
            size[i] = 1  # 子树大小先计入结点自己
            for j in g[i]:  # 遍历 i 的所有邻居
                if j != fa:  # 跳过父结点，避免沿来路边回走
                    dfs1(j, i, d + 1)  # 先递归处理子树，深度加一
                    size[i] += size[j]  # 后序累加：子树 j 的规模加到 i 上

        def dfs2(i: int, fa: int, t: int):  # 第二遍先序 DFS：i 当前结点，fa 父结点，t 是结点 i 的距离和
            ans[i] = t  # 记录当前结点的答案
            for j in g[i]:  # 遍历 i 的所有邻居
                if j != fa:  # 只沿子树方向递归，跳过父结点
                    dfs2(j, i, t - size[j] + n - size[j])  # 换根公式：子树内 size[j] 个点距离减 1，其余 n-size[j] 个点距离加 1

        g = defaultdict(list)  # 邻接表（LeetCode 环境已导入 defaultdict）
        for a, b in edges:  # 逐条无向边建图
            g[a].append(b)  # a 的邻居中加入 b
            g[b].append(a)  # b 的邻居中加入 a

        ans = [0] * n  # ans[i] 表示结点 i 到其余所有结点的距离之和
        size = [0] * n  # size[i] 表示以 i 为根的子树的结点个数
        dfs1(0, -1, 0)  # 以 0 为根做第一次 DFS，得到 ans[0] 与全部子树大小
        dfs2(0, -1, ans[0])  # 以 ans[0] 为起点做第二次 DFS，换根求出所有结点答案
        return ans  # 返回答案数组
