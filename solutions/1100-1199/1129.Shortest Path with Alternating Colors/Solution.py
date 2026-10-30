# 题目：1129. 颜色交替的最短路径（Shortest Path with Alternating Colors）
# 思路：以 (节点, 到达该节点所用边的颜色) 为状态做 BFS：队列初始放入 (0, 红) 与 (0, 蓝) 两个虚拟起点，扩展时把颜色取反再沿该颜色的出边走，状态第一次被访问时的层数就是最短交替路径长度。
# 时间复杂度：O(n + e)，每个 (节点, 颜色) 状态最多入队一次；空间复杂度 O(n + e)，需要存图与访问标记。
class Solution:  # LeetCode 约定的题解类
    def shortestAlternatingPaths(  # 参数较多，按 LeetCode 风格折行书写签名
        self, n: int, redEdges: List[List[int]], blueEdges: List[List[int]]  # self 是实例；n 是节点数；redEdges/blueEdges 是红蓝边
    ) -> List[int]:  # 返回到各节点的最短交替路径长度
        g = [defaultdict(list), defaultdict(list)]  # g[颜色][起点] 存该颜色出边的终点，颜色 0 红、1 蓝
        for i, j in redEdges:  # 建立红色有向边
            g[0][i].append(j)  # 红边 i → j
        for i, j in blueEdges:  # 建立蓝色有向边
            g[1][i].append(j)  # 蓝边 i → j
        ans = [-1] * n  # ans[i] 为最短距离，-1 表示不可达
        vis = set()  # vis：已访问的 (节点, 到达所用颜色) 状态集合
        q = deque([(0, 0), (0, 1)])  # 节点 0 分别以「虚拟红边」「虚拟蓝边」到达入队，便于首步选择颜色
        d = 0  # d：当前层距离，即已走过的边数
        while q:  # 队列非空就继续扩展
            for _ in range(len(q)):  # 按层处理，保证同层距离一致
                i, c = q.popleft()  # 取出节点与到达它所用的颜色
                if ans[i] == -1:  # 第一次到达该节点即为最短路
                    ans[i] = d  # 记录最短距离
                vis.add((i, c))  # 标记该状态已访问
                c ^= 1  # 下一步必须换颜色
                for j in g[c][i]:  # 遍历新颜色下的所有出边
                    if (j, c) not in vis:  # 该状态未访问过才入队
                        q.append((j, c))  # 入队继续扩展
            d += 1  # 本层结束，距离加一
        return ans  # 返回到各节点的最短交替路径长度
