# 题目：2242. 节点序列的最大得分（Maximum Score of a Node Sequence）
# 思路：枚举中间那条边 (a, b)，再各取 a、b 点权最大的前 3 个邻居即可覆盖最优解；用四重循环并检查四个点互不相同来更新答案。
# 时间复杂度：O(n + m log m)，n 为点数、m 为边数，主要花在按点权对每个点的邻居取前 3 大；空间复杂度：O(n + m)，邻接表开销。
class Solution:  # LeetCode 约定的题解类
    def maximumScore(self, scores: List[int], edges: List[List[int]]) -> int:  # scores 是点权，edges 是无向边
        g = defaultdict(list)  # 邻接表：g[u] 存放所有与 u 直接相连的点
        for a, b in edges:  # 遍历每条无向边
            g[a].append(b)  # a 的邻居中加入 b
            g[b].append(a)  # b 的邻居中加入 a（无向边需双向登记）
        for k in g.keys():  # 对每个出现过的点裁剪邻居列表
            g[k] = nlargest(3, g[k], key=lambda x: scores[x])  # 只保留点权最大的前 3 个邻居，凑四元序列够用了
        ans = -1  # 答案初值 -1，表示目前还没有可行的序列
        for a, b in edges:  # 枚举作为序列中间的那条边 (a, b)
            for c in g[a]:  # 枚举 a 的邻居 c，作为序列的第一个点
                for d in g[b]:  # 枚举 b 的邻居 d，作为序列的最后一个点
                    if b != c != d != a:  # 链式比较：四个点两两不同，避免同一个点被重复使用
                        t = scores[a] + scores[b] + scores[c] + scores[d]  # 累加四个点的点权
                        ans = max(ans, t)  # 用当前得分刷新最大值
        return ans  # 返回最大得分；不存在合法序列时保持 -1
