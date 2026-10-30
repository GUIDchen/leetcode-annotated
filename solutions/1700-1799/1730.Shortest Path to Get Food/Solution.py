# 题目：1730. 获取食物的最短路径（Shortest Path to Get Food）
# 思路：从 '*' 出发做 BFS，按层扩散并就地标记走过的空地，第一次碰到 '#' 时的层数即最短距离。
# 时间复杂度：O(m*n)，每个格子最多入队一次；空间复杂度：O(m*n)，队列最坏存下所有空地。
class Solution:  # LeetCode 约定的题解类
    def getFood(self, grid: List[List[str]]) -> int:  # grid：'*' 是起点、'#' 是食物、'O' 是空地、'X' 是障碍
        m, n = len(grid), len(grid[0])  # m 是行数，n 是列数
        i, j = next((i, j) for i in range(m) for j in range(n) if grid[i][j] == '*')  # 先用生成器定位起点坐标，找不到会抛异常
        q = deque([(i, j)])  # BFS 队列，起点先入队
        dirs = (-1, 0, 1, 0, -1)  # 四方向增量表，相邻两项组成一对
        ans = 0  # 已经走过的步数
        while q:  # 队列非空就继续按层扩展
            ans += 1  # 进入下一层，步数加一
            for _ in range(len(q)):  # 只弹当前层已有的节点，保证层序清晰
                i, j = q.popleft()  # 取出队头坐标
                for a, b in pairwise(dirs):  # 依次取出四个方向对
                    x, y = i + a, j + b  # 相邻格子的坐标
                    if 0 <= x < m and 0 <= y < n:  # 未越界才继续判断
                        if grid[x][y] == '#':  # 遇到食物
                            return ans  # 当前步数就是最短距离
                        if grid[x][y] == 'O':  # 只有空地可以继续走
                            grid[x][y] = 'X'  # 就地标记为已访问，避免重复入队
                            q.append((x, y))  # 入队等待下一层扩展
        return -1  # 走不到食物，返回 -1
