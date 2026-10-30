# 题目：2814. 避免淹死并到达目的地的最短时间（Minimum Time Takes to Reach Destination Without Drowning）
# 思路：先用所有水域做多源 BFS 求出每格的最早淹没时刻 g，再从起点 S 做 BFS，只走「第 t+1 秒踏入时水未到（g > t+1）」的格子，首次到达 D 的时间即答案。
# 时间复杂度：O(m×n)，两遍 BFS 每格最多入队一次；空间复杂度：O(m×n)，淹没时刻表、访问标记与队列。
class Solution:  # LeetCode 约定的题解类
    def minimumSeconds(self, land: List[List[str]]) -> int:  # land：字符网格，'.' 可走、'*' 水、'S' 起点、'D' 终点、'X' 石头
        m, n = len(land), len(land[0])  # 行数与列数，后面到处都要用
        vis = [[False] * n for _ in range(m)]  # 访问标记矩阵：防止同一格重复入队
        g = [[inf] * n for _ in range(m)]  # 淹没时刻矩阵：inf 表示该格永远不会被淹
        q = deque()  # 双端队列当 BFS 队列，popleft 是 O(1)
        si = sj = 0  # 起点坐标，题目保证存在，这里先初始化为 0
        for i, row in enumerate(land):  # 逐行扫描，同时拿到行号与整行内容
            for j, c in enumerate(row):  # 再逐列扫描，拿到列号与当前字符
                match c:  # 结构化模式匹配，按字符分派
                    case "*":  # 水域：作为多源 BFS 的源点
                        q.append((i, j))  # 所有水域一起入队，第 0 秒同时开始扩散
                    case "S":  # 起点：只记录位置，留给第二遍 BFS
                        si, sj = i, j  # 记住起点的行列
        dirs = (-1, 0, 1, 0, -1)  # 四方向增量，pairwise 成对取出 (a, b) 即上下左右
        t = 0  # 当前时间从 0 秒开始
        while q:  # 第一遍 BFS：逐层扩散，算出每格的淹没时刻
            for _ in range(len(q)):  # 先锁定本层节点数，保证同一秒的格子一起处理
                i, j = q.popleft()  # 取出队首坐标
                g[i][j] = t  # 该格在第 t 秒被水覆盖
                for a, b in pairwise(dirs):  # 枚举四个方向
                    x, y = i + a, j + b  # 邻居坐标
                    if (  # 条件用括号跨多行书写，可读性更好
                        0 <= x < m  # 行下标不能越界
                        and 0 <= y < n  # 列下标不能越界
                        and not vis[x][y]  # 还没被水扫描过
                        and land[x][y] in ".S"  # 水只能漫过空地 '.' 和起点 'S'，石头与终点不可被淹
                    ):  # 四个条件同时满足才继续
                        vis[x][y] = True  # 标记已访问
                        q.append((x, y))  # 入队，下一秒继续扩散
            t += 1  # 本层处理完，进入下一秒
        t = 0  # 第二遍 BFS 的时间重新从 0 计
        q = deque([(si, sj)])  # 队列换成只包含起点
        vis = [[False] * n for _ in range(m)]  # 重新开一张干净的访问标记表
        vis[si][sj] = True  # 起点标记为已访问
        while q:  # 第二遍 BFS：找从 S 到 D 的最短安全时间
            for _ in range(len(q)):  # 锁定本层节点数，层内时间相同
                i, j = q.popleft()  # 取出队首坐标
                if land[i][j] == "D":  # 站到终点上就立即返回当前秒数（BFS 先到即最短）
                    return t  # 返回答案
                for a, b in pairwise(dirs):  # 枚举四个方向
                    x, y = i + a, j + b  # 邻居坐标
                    if (  # 同上，多行书写四个约束
                        0 <= x < m  # 行下标不越界
                        and 0 <= y < n  # 列下标不越界
                        and g[x][y] > t + 1  # 关键约束：第 t+1 秒踏入时水必须还没到
                        and not vis[x][y]  # 该格尚未访问
                        and land[x][y] in ".D"  # 只能进入空地 '.' 或终点 'D'，石头 'X' 不可通行
                    ):  # 四个条件同时满足才继续
                        vis[x][y] = True  # 标记已访问
                        q.append((x, y))  # 入队，下一秒继续扩展
            t += 1  # 本层处理完，时间加一
        return -1  # 队列空了还没到终点，说明无法安全抵达
