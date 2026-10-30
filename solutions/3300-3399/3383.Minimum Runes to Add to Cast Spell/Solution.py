# 题目：3383. 施法所需最低符文数量（Minimum Runes to Add to Cast Spell）
# 思路：有向边表示符文流动；先用晶体做多源 BFS 标记免费可达点，再对剩余点 DFS 求逆后序，按「上游优先」逐个补符文并 BFS 扩散计数。
# 时间复杂度：O(n + m)，每个点最多入队/访问一次；空间复杂度：O(n + m)，存邻接表、访问标记与拓扑序列。
class Solution:  # LeetCode 约定的题解类
    def minRunesToAdd(  # 方法签名开始（参数较多，拆成多行书写）
        self, n: int, crystals: List[int], flowFrom: List[int], flowTo: List[int]  # n：符文总数；crystals：初始晶体；flowFrom/flowTo：有向流动边
    ) -> int:  # 返回需要新增的最少符文数量
        def bfs(q: Deque[int]):  # 多源 BFS：把 q 中节点能流到且未点亮的符文全部标记为 1
            while q:  # 队列非空就继续扩散
                a = q.popleft()  # 取出队首（左端）节点
                for b in g[a]:  # 遍历它的所有出边邻居
                    if vis[b] == 1:  # 已经点亮过就不再重复处理
                        continue  # 跳过，保证每个点最多入队一次
                    vis[b] = 1  # 标记为已点亮
                    q.append(b)  # 入队继续向后扩散

        def dfs(a: int):  # DFS：把尚未点亮的块内节点标 2，并按后序写进 seq
            vis[a] = 2  # 状态 2：该点还需要补符文，且已访问过
            for b in g[a]:  # 遍历邻居
                if vis[b] > 0:  # 已访问过（1 或 2）就剪枝
                    continue  # 跳过
                dfs(b)  # 递归深入
            seq.append(a)  # 后序写入：下游先入列、上游后入列

        g = [[] for _ in range(n)]  # 邻接表：g[a] 保存从 a 能流到的符文
        for a, b in zip(flowFrom, flowTo):  # 枚举每一条流动边
            g[a].append(b)  # 建边 a -> b

        q = deque(crystals)  # 初始队列由所有晶体组成（多源 BFS 的起点）
        vis = [0] * n  # 访问状态：0=未点亮，1=已点亮，2=DFS 标记的待补符文点
        for x in crystals:  # 晶体本身天生可用
            vis[x] = 1  # 直接标记为已点亮
        bfs(q)  # 第一轮扩散：算出免费就能点亮的集合

        seq = []  # seq 保存 DFS 的后序
        for i in range(n):  # 枚举每个符文
            if vis[i] == 0:  # 仍然点不亮的说明在某个待补符文块里
                dfs(i)  # 对该块做 DFS
        seq.reverse()  # 反转后序，得到「上游在前、下游在后」的顺序
        ans = 0  # ans：需要新增的最少符文数
        for i in seq:  # 按上游到下游的顺序遍历
            if vis[i] == 2:  # 只处理 DFS 之后仍是状态 2 的点
                q = deque([i])  # 在这里补一个符文，作为新的 BFS 起点
                vis[i] = 1  # 标记为已点亮（相当于新晶体）
                bfs(q)  # 从新起点再扩散一次
                ans += 1  # 计数加一
        return ans  # 返回答案
