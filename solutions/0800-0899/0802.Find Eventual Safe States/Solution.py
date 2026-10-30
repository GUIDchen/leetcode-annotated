# 题目：802. 找到最终的安全状态（Find Eventual Safe States）
# 思路：反向建图后做拓扑排序，出度为 0 的节点安全，逐层剥离后仍能保留下来的节点就是安全节点。
# 时间复杂度：O(n + m)，n 为节点数、m 为边数；空间复杂度：O(n + m)，存反向图与出度。
class Solution:  # LeetCode 约定的题解类
    def eventualSafeNodes(self, graph: List[List[int]]) -> List[int]:  # graph：邻接表；返回所有安全节点（按下标升序）
        rg = defaultdict(list)  # 反向图，用 defaultdict 省去判空的样板代码
        indeg = [0] * len(graph)  # 每个节点的有效出度，拓扑剥离时递减
        for i, vs in enumerate(graph):  # 同时拿到节点下标与其出边列表
            for j in vs:  # 遍历节点 i 的每条出边 i → j
                rg[j].append(i)  # 反向记录边 j → i
            indeg[i] = len(vs)  # i 的初始出度就是它出边的条数
        q = deque([i for i, v in enumerate(indeg) if v == 0])  # 把所有出度为 0 的节点作为拓扑排序的起点
        while q:  # 逐层剥离安全节点
            i = q.popleft()  # 取出队头节点
            for j in rg[i]:  # 遍历反向邻居，也就是原图中指向 i 的前驱
                indeg[j] -= 1  # 前驱少掉一条可行出边
                if indeg[j] == 0:  # 前驱出度归零，说明它也安全
                    q.append(j)  # 入队等待继续剥离
        return [i for i, v in enumerate(indeg) if v == 0]  # 出度为 0 的都是安全节点，按下标升序返回
