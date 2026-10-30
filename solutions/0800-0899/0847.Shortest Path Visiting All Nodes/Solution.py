# 题目：847. 访问所有节点的最短路径（Shortest Path Visiting All Nodes）
# 思路：状态压缩 BFS，状态为（当前节点, 已访问集合掩码），按层扩展直到掩码覆盖全部节点。
# 时间复杂度：O(2^n * n^2)，共 2^n * n 个状态；空间复杂度：O(2^n * n)，vis 集合与队列。
class Solution:  # LeetCode 约定的题解类
    def shortestPathLength(self, graph: List[List[int]]) -> int:  # graph 是邻接表；返回访问所有节点所需的最短步数
        n = len(graph)  # 节点个数，也决定状态掩码的位数
        q = deque()  # BFS 队列，元素是（当前节点, 已访问节点掩码）；deque 由判题环境提供
        vis = set()  # 已入队状态集合，避免重复扩展
        for i in range(n):  # 每个节点都可以作为起点，全部作为初始状态入队
            q.append((i, 1 << i))  # 起点 i 的掩码只有第 i 位为 1
            vis.add((i, 1 << i))  # 记录该初始状态，防止后续重复入队
        ans = 0  # 当前步数，随 BFS 层数递增
        while 1:  # BFS 主循环，条件恒真，靠内部的 return 结束
            for _ in range(len(q)):  # 一次只处理当前层，len(q) 在循环开始时固定
                i, st = q.popleft()  # 取出队首：当前节点 i 与已访问掩码 st
                if st == (1 << n) - 1:  # 掩码已覆盖全部 n 位，所有节点都访问过
                    return ans  # 返回当前步数，BFS 保证最短
                for j in graph[i]:  # 枚举节点 i 的所有邻居
                    nst = st | 1 << j  # 走一步到 j，把第 j 位加入掩码
                    if (j, nst) not in vis:  # 该状态没出现过才扩展
                        vis.add((j, nst))  # 标记新状态已入队
                        q.append((j, nst))  # 新状态入队，留待下一层扩展
            ans += 1  # 本层处理完毕，步数加一
