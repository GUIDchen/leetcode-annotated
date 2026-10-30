# 题目：2192. 有向无环图中一个节点的所有祖先（All Ancestors of a Node in a Directed Acyclic Graph）
# 思路：以每个结点 s 为起点做一次 BFS，凡是从 s 能到达的结点 j，都把 s 追加进 ans[j]。
# 时间复杂度：O(n·(n+m))，需做 n 次 BFS；空间复杂度：O(n+m)，邻接表、访问集合与结果。
class Solution:  # LeetCode 约定的题解类
    def getAncestors(self, n: int, edges: List[List[int]]) -> List[List[int]]:  # n：结点个数；edges：描述有向边的列表
        def bfs(s: int):  # 以 s 为祖先做一次广度优先搜索
            q = deque([s])  # 双端队列存放待扩展结点，起点是 s
            vis = {s}  # 集合记录本次已访问的结点，避免重复扩展
            while q:  # 队列非空就继续
                i = q.popleft()  # 从左侧弹出队首结点
                for j in g[i]:  # 枚举 i 的每个直接后继
                    if j not in vis:  # j 本次还没有访问过
                        vis.add(j)  # 标记为已访问
                        q.append(j)  # 入队，继续向后扩展
                        ans[j].append(s)  # s 能到达 j，所以 s 是 j 的祖先

        g = defaultdict(list)  # 邻接表：访问缺失的键时会自动创建空列表
        for u, v in edges:  # 遍历每条有向边 u -> v
            g[u].append(v)  # 建立 u 指向 v 的关系
        ans = [[] for _ in range(n)]  # 结果：ans[j] 存放 j 的全部祖先
        for i in range(n):  # 让每个结点依次当一次祖先
            bfs(i)  # 从 i 出发搜索
        return ans  # 返回结果；i 递增插入，每个列表天然升序
