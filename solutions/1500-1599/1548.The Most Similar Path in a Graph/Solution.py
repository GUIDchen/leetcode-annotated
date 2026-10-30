# 题目：1548. 图中最相似的路径（The Most Similar Path in a Graph）
# 思路：按目标路径逐位置做 DP，f[i][j] 表示路径前 i+1 个位置走完且停在点 j 时的最少不同名字数；pre 记录前驱用于回溯。
# 时间复杂度：O(m·(n+E))（m 目标路径长度、n 点数、E 边数）；空间复杂度：O(m·n)（DP 表 + 前驱表）。
class Solution:  # LeetCode 约定的题解类
    def mostSimilar(  # 求解方法：返回与 targetPath 名字序列最相似的节点序列
        self, n: int, roads: List[List[int]], names: List[str], targetPath: List[str]  # n：点数；roads：无向边；names：各点名字；targetPath：目标名字序列
    ) -> List[int]:  # 返回值是具体的节点编号序列
        g = [[] for _ in range(n)]  # 邻接表：g[x] 存放与点 x 直接相连的所有点
        for a, b in roads:  # 遍历每条无向边
            g[a].append(b)  # 建立 a -> b 的邻接关系
            g[b].append(a)  # 建立 b -> a 的邻接关系（无向图两条都要加）
        m = len(targetPath)  # 目标路径长度，也就是 DP 的层数
        f = [[inf] * n for _ in range(m)]  # f[i][j]：前 i+1 个位置走完并停在点 j 时，名字不匹配的最小个数
        pre = [[-1] * n for _ in range(m)]  # pre[i][j]：取到最优时上一位置停留的节点编号，-1 表示无前驱
        for j, s in enumerate(names):  # 单独初始化第 0 层：路径第一个位置可以落在任意点
            f[0][j] = targetPath[0] != s  # 名字不同记 1 点代价，相同记 0（布尔值直接当整数用）
        for i in range(1, m):  # 从第 1 层开始逐层递推（相邻位置必须在图中有边相连）
            for j in range(n):  # 枚举第 i 个位置当前停靠的点 j
                for k in g[j]:  # 枚举 j 的邻居 k，作为第 i-1 个位置的可能落点
                    if (t := f[i - 1][k] + (targetPath[i] != names[j])) < f[i][j]:  # 海象运算符：先算转移代价，再判断是否更优
                        f[i][j] = t  # 更新第 i 层停在 j 的最小代价
                        pre[i][j] = k  # 记录最优前驱，供最后还原路径
        k = 0  # k 保存最优终点的节点编号
        mi = inf  # mi 保存当前找到的最小代价
        for j in range(n):  # 在所有终点中挑代价最小的那个
            if f[-1][j] < mi:  # 发现更小的代价
                mi = f[-1][j]  # 更新最小代价
                k = j  # 更新最优终点节点
        ans = [0] * m  # 结果数组，按位置存放节点编号
        for i in range(m - 1, -1, -1):  # 从最后一层往前逐层回溯
            ans[i] = k  # 把当前层的节点编号填进答案
            k = pre[i][k]  # 顺着前驱退回到上一层的节点
        return ans  # 回溯完成，ans 就是最相似的节点序列
