# 题目：675. 为高尔夫比赛砍树（Cut Off Trees for Golf Event）
# 思路：必须按树高升序砍树，所以先排序；相邻两棵树之间用 A*（曼哈顿距离作启发函数）求最短步数并累加，任一段不可达就返回 -1。
# 时间复杂度：O(T * m * n log(mn))，T 为树的个数，每段 A* 最坏遍历整个网格；空间复杂度：O(m * n)，距离字典与堆。
class Solution:  # LeetCode 约定的题解类
    def cutOffTree(self, forest: List[List[int]]) -> int:  # forest：网格，0 不可通行，1 草地，大于 1 是树
        def f(i, j, x, y):  # 启发函数：两点之间的曼哈顿距离
            return abs(i - x) + abs(j - y)  # 行差绝对值加列差绝对值

        def bfs(i, j, x, y):  # A*：从 (i, j) 走到 (x, y) 的最短步数
            q = [(f(i, j, x, y), i, j)]  # 小根堆，元素为 (f = g + h, 行, 列)
            dist = {i * n + j: 0}  # 距离字典，键是一维编号，起点距离为 0（n 在闭包里取外层变量）
            while q:  # 堆不空就继续扩展
                _, i, j = heappop(q)  # 取出 f 值最小的节点
                step = dist[i * n + j]  # 该节点当前的步数
                if (i, j) == (x, y):  # 到达目标位置
                    return step  # 第一次弹出即是最短步数
                for a, b in [[0, -1], [0, 1], [-1, 0], [1, 0]]:  # 枚举上下左右四个方向
                    c, d = i + a, j + b  # 走一步后的新坐标
                    if 0 <= c < m and 0 <= d < n and forest[c][d] > 0:  # 不越界且可通行（0 是障碍）
                        if c * n + d not in dist or dist[c * n + d] > step + 1:  # 没访问过，或者能走到更短的步数
                            dist[c * n + d] = step + 1  # 更新更短的步数
                            heappush(q, (dist[c * n + d] + f(c, d, x, y), c, d))  # 用新的 f 值入堆
            return -1  # 搜完仍未到达，说明不可达

        m, n = len(forest), len(forest[0])  # 行数与列数，供内层函数通过闭包读取
        trees = [  # 收集所有树：三元组 (树高, 行, 列)
            (forest[i][j], i, j) for i in range(m) for j in range(n) if forest[i][j] > 1  # 只保留树高大于 1 的格子
        ]
        trees.sort()  # 按树高升序排序，得到唯一的砍树顺序
        i = j = 0  # 当前位置从左上角 (0, 0) 出发
        ans = 0  # 累计总步数
        for _, x, y in trees:  # 按从矮到高依次砍树
            t = bfs(i, j, x, y)  # 求从当前位置到目标树的最短步数
            if t == -1:  # 走不到
                return -1  # 无法完成比赛
            ans += t  # 累加这一段步数
            i, j = x, y  # 当前位置移动到刚砍完的树
        return ans  # 返回砍完所有树的总步数
