# 题目：1091. 二进制矩阵中的最短路径（Shortest Path in Binary Matrix）
# 思路：从左上角出发做八方向 BFS，入队时直接把格子改成 1 当障碍（复用 grid 省掉 visited），队列第一次弹出右下角时的层数就是最短路径长度。
# 时间复杂度：O(n²)，每个格子最多入队一次；空间复杂度：O(n²)，BFS 队列最坏存下一层的全部格子。
class Solution:  # LeetCode 约定的题解类
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:  # grid 中 0 可走、1 是障碍，返回最短路径经过的格子数
        if grid[0][0]:  # 起点就是障碍，根本无法出发
            return -1  # 直接判无解
        n = len(grid)  # 方阵边长
        grid[0][0] = 1  # 把起点标记为已访问（直接改 grid，省一个 visited 数组）
        q = deque([(0, 0)])  # BFS 双端队列，初始只有起点
        ans = 1  # 起点本身算作路径上的第 1 个格子
        while q:  # 队列非空说明还有待扩展的格子
            for _ in range(len(q)):  # 先固定本层节点数，保证一层一层向外扩散
                i, j = q.popleft()  # 取出队首坐标
                if i == j == n - 1:  # 到达右下角（两个坐标都等于 n-1）
                    return ans  # BFS 首次到达即为最短路径
                for x in range(i - 1, i + 2):  # 枚举八邻域的行坐标
                    for y in range(j - 1, j + 2):  # 枚举八邻域的列坐标
                        if 0 <= x < n and 0 <= y < n and grid[x][y] == 0:  # 坐标不越界且该格子可走（值为 0）
                            grid[x][y] = 1  # 入队前先标记为已访问，避免重复入队
                            q.append((x, y))  # 邻居入队，留到下一层扩展
            ans += 1  # 本层处理完，路径长度加一
        return -1  # 队列空了仍未到达右下角，说明无路可走
