# 题目：3367. 移除边之后的权重最大和（Maximize Sum of Weights after Edge Removals）
# 思路：树上 DP，dfs 返回「每点度数不超过 k 时的最大和」与「给父边留一个空位时的最大和」，子边按增益 w + b - a 降序取前 k-1 条。
# 时间复杂度：O(n log n)，每个节点要对子边增益排序；空间复杂度：O(n)，邻接表与递归栈开销。
class Solution:  # LeetCode 约定的题解类
    def maximizeSumOfWeights(self, edges: List[List[int]], k: int) -> int:  # edges：带权边列表；k：每个节点允许保留的最大边数
        def dfs(u: int, fa: int) -> Tuple[int, int]:  # 递归函数：u 为当前节点，fa 为父节点
            s = 0  # s：孩子都按「可连父边」取最优时的汇总和
            t = []  # t：收集每条孩子边的正增益
            for v, w in g[u]:  # 遍历 u 的每条邻边（邻居 v，边权 w）
                if v == fa:  # 遇到父节点就跳过，避免顺着树往回走
                    continue  # 跳过父边
                a, b = dfs(v, u)  # 递归拿到孩子的两种最优值：a 为可连父边，b 为给父边留空位
                s += a  # 先把孩子的 a 累加，后面再用增益替换
                if (d := (w + b - a)) > 0:  # 海象运算符算出保留这条边的增益并只收正值：边权 + 孩子腾位收益 - 孩子的 a
                    t.append(d)  # 记录这条边的正增益
            t.sort(reverse=True)  # 增益降序排序，优先保留收益最大的边
            return s + sum(t[:k]), s + sum(t[: k - 1])  # 返回两种值：连满 k 条边、只连 k-1 条边（给父边留空位）

        n = len(edges) + 1  # 节点数 = 边数 + 1
        g: List[List[Tuple[int, int]]] = [[] for _ in range(n)]  # 邻接表：g[u] 保存 (邻居, 边权) 组成的对
        for u, v, w in edges:  # 逐条边建立无向图
            g[u].append((v, w))  # u 侧记录通向 v 的那条边
            g[v].append((u, w))  # v 侧记录通向 u 的那条边
        x, y = dfs(0, -1)  # 从 0 号节点作为树根开始做树形 DP，父节点记为 -1
        return max(x, y)  # 根节点没有父边，两种状态取最大即为答案
