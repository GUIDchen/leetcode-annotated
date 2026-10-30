# 题目：2497. 图中最大星和（Maximum Star Sum of a Graph）
# 思路：负权邻居一律不选；为每个点收集正权邻居的点权并降序排序，枚举中心取「自身权值 + 前 k 大邻居」的最大值。
# 时间复杂度：O(n + m + 邻居总数 log 邻居数)，m 为边数；空间复杂度：O(n + m)。
class Solution:  # LeetCode 约定的题解类
    def maxStarSum(self, vals: List[int], edges: List[List[int]], k: int) -> int:  # vals 是各点点权，edges 是无向边，k 是星形最多能带的邻居数
        g = defaultdict(list)  # 邻接表：g[i] 只收集正权的邻居点权，负权邻居不会带来收益
        for a, b in edges:  # 遍历每条无向边，同时解包两个端点
            if vals[b] > 0:  # b 的权值为正才值得放进 a 的候选列表
                g[a].append(vals[b])  # 记录 b 的点权，供 a 作为中心时选取
            if vals[a] > 0:  # 同理处理反方向：a 的权值为正就放进 b 的候选列表
                g[b].append(vals[a])  # 记录 a 的点权
        for bs in g.values():  # 把每个中心的候选邻居点权从大到小排序
            bs.sort(reverse=True)  # 逆序排序，保证切片取到的前 k 个就是最大的 k 个
        # 以每个点为星形中心：自身权值 + 最大 k 个正权邻居（切片自动截断），
        # 再对所有中心取最大值；min 的效果由 [:k] 的上界自动完成。另需注意不在图里的点也在 vals 中参与比较。
        return max(v + sum(g[i][:k]) for i, v in enumerate(vals))
