# 题目：2146. 价格范围内最高排名的 K 样物品（K Highest Ranked Items Within a Price Range）
# 思路：从起点广度优先搜索得到每个可走格子的最短距离，把价格在区间内的格子按 (距离, 价格, 行, 列) 排序后取前 k 个。
# 时间复杂度：O(mn log(mn))，BFS 为 O(mn)、排序占主导；空间复杂度：O(mn)，队列与候选列表最坏存下全部格子。
class Solution:  # LeetCode 约定的题解类
    def highestRankedKItems(  # 求价格在区间内、排名最高的 k 个物品坐标
        self, grid: List[List[int]], pricing: List[int], start: List[int], k: int  # grid：价格网格；pricing：价格区间；start：起点；k：取前几名
    ) -> List[List[int]]:  # 返回值是若干个 [行, 列] 坐标
        m, n = len(grid), len(grid[0])  # m、n 分别是网格的行数与列数
        row, col = start  # 拆出 BFS 起点的行、列坐标
        low, high = pricing  # 拆出允许的价格区间 [low, high]
        q = deque([(row, col)])  # BFS 双端队列，初始只有起点
        pq = []  # 候选物品列表，元素是 (距离, 价格, 行, 列)
        if low <= grid[row][col] <= high:  # 起点本身若价格在区间内，距离为 0 也是候选
            pq.append((0, grid[row][col], row, col))  # 记录起点物品
        grid[row][col] = 0  # 起点标记为已访问（0 表示墙或已走过）
        dirs = (-1, 0, 1, 0, -1)  # 四方向偏移表，配合 pairwise 生成上、右、下、左四个向量
        step = 0  # 当前 BFS 层的距离
        while q:  # 队列非空就继续搜索
            step += 1  # 进入下一层，距离加一
            for _ in range(len(q)):  # 只处理进入本轮时的这一层节点
                x, y = q.popleft()  # 从左端取出队首坐标
                for a, b in pairwise(dirs):  # 相邻两项配对，得到四个方向向量
                    nx, ny = x + a, y + b  # 计算出相邻格子的坐标
                    if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] > 0:  # 未越界且该格可走
                        if low <= grid[nx][ny] <= high:  # 价格落在区间内就记为候选物品
                            pq.append((step, grid[nx][ny], nx, ny))  # 记录距离、价格与坐标
                        grid[nx][ny] = 0  # 标记为已访问，避免重复入队
                        q.append((nx, ny))  # 入队，等待下一层扩展
        pq.sort()  # 按 (距离, 价格, 行, 列) 的字典序整体排序
        return [list(x[2:]) for x in pq[:k]]  # 取前 k 个，并把元组里的 (行, 列) 转成列表
