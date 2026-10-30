# 题目：310. 最小高度树（Minimum Height Trees）
# 思路：树的「重心」问题。反过来用拓扑剥叶子：每轮剥掉所有度数为 1 的叶子，最后剩下的 1~2 个节点就是答案。
# 时间复杂度：O(n)，每个节点最多入队、出队一次；空间复杂度：O(n)，邻接表、度数数组与队列。
class Solution:  # LeetCode 约定的题解类
    def findMinHeightTrees(self, n: int, edges: List[List[int]]) -> List[int]:  # n：节点数；edges：无向边列表，每条边是 [a, b]
        if n == 1:  # 只有一个节点时它自己就是唯一的最小高度树根
            return [0]  # 直接返回节点 0
        g = [[] for _ in range(n)]  # 邻接表：g[u] 保存与 u 相邻的所有节点
        degree = [0] * n  # 每个节点的度数（相邻节点个数）
        for a, b in edges:  # 遍历每条无向边
            g[a].append(b)  # 把 b 加入 a 的邻接表
            g[b].append(a)  # 把 a 加入 b 的邻接表（无向边要双向记录）
            degree[a] += 1  # a 的度数加一
            degree[b] += 1  # b 的度数加一
        q = deque(i for i in range(n) if degree[i] == 1)  # 双端队列：初始装入所有叶子（度数为 1 的节点）
        ans = []  # 每轮剥完后剩下的节点，最后一轮剩下的就是候选根
        while q:  # 不断剥叶子，直到最后只剩 1~2 个节点
            ans.clear()  # 清空上一轮结果，ans 只保留最后一轮剥掉的节点
            for _ in range(len(q)):  # 按层处理：只处理本层现有的 len(q) 个叶子
                a = q.popleft()  # 弹出队头叶子
                ans.append(a)  # 记录本轮剥掉的节点
                for b in g[a]:  # 遍历该叶子的所有邻居
                    degree[b] -= 1  # 剥掉 a 后邻居的度数减一
                    if degree[b] == 1:  # 度数变成 1 说明它成了新叶子
                        q.append(b)  # 新叶子入队，留到下一层处理
        return ans  # 最后一轮剩下的节点（1~2 个）就是最小高度树的根
