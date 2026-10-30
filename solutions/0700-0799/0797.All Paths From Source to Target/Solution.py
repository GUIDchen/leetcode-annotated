# 题目：797. 所有可能的路径（All Paths From Source to Target）
# 思路：用双端队列做广度优先搜索，队列元素是「从 0 走到当前节点的完整路径」；路径末尾是当前节点，到达终点 n-1 就收集，否则把每个邻居接在路径后面入队。
# 时间复杂度：O(n·2^n)，路径条数最坏为指数级且每条长度 O(n)；空间复杂度：O(n·2^n)，队列里保存所有部分路径。
class Solution:  # LeetCode 约定的题解类
    def allPathsSourceTarget(self, graph: List[List[int]]) -> List[List[int]]:  # graph：有向无环图的邻接表
        n = len(graph)  # 节点个数，终点编号是 n-1
        q = deque([[0]])  # 队列元素是完整路径，deque 让出队操作是 O(1)
        ans = []  # 收集所有到达终点的路径
        while q:  # 队列非空就继续搜索
            path = q.popleft()  # 取出一条路径继续扩展
            u = path[-1]  # 路径末尾就是当前节点
            if u == n - 1:  # 已经到达终点
                ans.append(path)  # 记录这条完整路径
                continue  # 终点没有后继，换下一条路径
            for v in graph[u]:  # 枚举当前节点的所有邻居
                q.append(path + [v])  # 复制路径并追加邻居，保证各条路径互不干扰
        return ans  # 返回所有路径
