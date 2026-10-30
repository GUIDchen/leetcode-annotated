# 题目：1926. 迷宫中离入口最近的出口（Nearest Exit from Entrance in Maze）
# 思路：从入口开始分层 BFS，用 ans 记录当前层数；第一次遇到边界上的空格子就返回层数，队列空了则返回 -1。
# 时间复杂度：O(mn)，每个格子最多入队一次；空间复杂度：O(mn)，队列最多存放全部格子。
class Solution:  # LeetCode 约定的题解类
    def nearestExit(self, maze: List[List[str]], entrance: List[int]) -> int:  # maze：迷宫网格；entrance：入口坐标
        m, n = len(maze), len(maze[0])  # m 是行数，n 是列数
        i, j = entrance  # 拆出入口的行、列坐标
        q = deque([(i, j)])  # BFS 双端队列，初始只放入口
        maze[i][j] = "+"  # 把入口改成墙，表示已访问
        ans = 0  # 当前已经扩散的步数（层数）
        while q:  # 队列非空说明还有可达格子待扩展
            ans += 1  # 进入下一层，步数加一
            for _ in range(len(q)):  # 只遍历当前层的节点数量
                i, j = q.popleft()  # 取出队首坐标
                for a, b in [[0, -1], [0, 1], [-1, 0], [1, 0]]:  # 四个方向的偏移量
                    x, y = i + a, j + b  # 邻居坐标
                    if 0 <= x < m and 0 <= y < n and maze[x][y] == ".":  # 邻居在界内且是未访问的空格子
                        if x == 0 or x == m - 1 or y == 0 or y == n - 1:  # 空格子位于迷宫边界，可以作为出口
                            return ans  # 分层 BFS 保证这是最近的出口
                        q.append((x, y))  # 合法邻居入队，留待下一层扩展
                        maze[x][y] = "+"  # 入队时立即标记为已访问
        return -1  # 走遍所有可达格子也没有出口
