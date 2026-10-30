# 题目：3552. 网格传送门旅游（Grid Teleportation Traversal）
# 思路：把“走到相邻格”看作权 1 的边、“使用传送门跳到同字母格”看作权 0 的边，用 0-1 BFS 求最短路：权 0 的转移压入队头、权 1 的压入队尾；每种字母的传送门只展开一次，整体复杂度保持线性。
# 时间复杂度：O(m·n)，每个格子最多入队常数次、每个传送门只展开一次；空间复杂度：O(m·n)，存放距离表与队列。
class Solution:  # LeetCode 约定的题解类
    def minMoves(self, matrix: List[str]) -> int:  # matrix：字符网格；返回从左上角走到右下角的最少移动次数
        m, n = len(matrix), len(matrix[0])  # m、n：网格的行数与列数
        g = defaultdict(list)  # g：传送门字符 -> 该字符的所有格子坐标
        for i, row in enumerate(matrix):  # 枚举行下标 i 与该行内容
            for j, c in enumerate(row):  # 枚举行内列下标 j 与字符 c
                if c.isalpha():  # 字母表示传送门
                    g[c].append((i, j))  # 按字符归类收集坐标
        dirs = (-1, 0, 1, 0, -1)  # 四方向偏移，相邻两项配成一个方向 (dx, dy)
        dist = [[inf] * n for _ in range(m)]  # dist[i][j]：从起点到达 (i,j) 的最少移动次数
        dist[0][0] = 0  # 起点距离为 0
        q = deque([(0, 0)])  # 0-1 BFS 使用的双端队列，起点入队
        while q:  # 队列非空就继续扩展
            i, j = q.popleft()  # 取出队首坐标
            d = dist[i][j]  # d：到达当前格子的最少移动次数
            if i == m - 1 and j == n - 1:  # 到达右下角终点
                return d  # 0-1 BFS 的出队顺序保证首次到达即最短路
            c = matrix[i][j]  # c：当前格子上的字符
            if c in g:  # 当前格子是传送门，且该字符还未被展开过
                for x, y in g[c]:  # 枚举同字符的所有传送目标格
                    if d < dist[x][y]:  # 若经由传送门到达更优才更新
                        dist[x][y] = d  # 传送不消耗移动次数，距离保持为 d
                        q.appendleft((x, y))  # 边权为 0，压入队头以维持队列单调性
                del g[c]  # 同一字符的传送门只需展开一次
            for a, b in pairwise(dirs):  # 枚举四个相邻方向
                x, y = i + a, j + b  # 相邻格子的坐标 (x, y)
                if (  # 以下四个条件需同时成立才可走这一步
                    0 <= x < m  # 行坐标不越界
                    and 0 <= y < n  # 列坐标不越界
                    and matrix[x][y] != "#"  # 目标格不是障碍
                    and d + 1 < dist[x][y]  # 且能刷新更短距离
                ):  # 条件判断结束
                    dist[x][y] = d + 1  # 走一步代价为 1
                    q.append((x, y))  # 边权为 1，压入队尾
        return -1  # 队列耗尽仍无法到达终点
