# 题目：2617. 网格图中最少访问的格子数（Minimum Number of Visited Cells in a Grid）
# 思路：按行优先顺序做 BFS 式 DP，同时为每行、每列维护 (步数, 下标) 的小根堆；堆顶若已跳不到当前格子就弹出，剩下的堆顶给出到达当前格子的最小步数来源。
# 时间复杂度：O(mn log(mn))，每个格子最多入堆出堆各一次；空间复杂度：O(mn)，dist 数组与行列堆。
class Solution:  # LeetCode 约定的题解类
    def minimumVisitedCells(self, grid: List[List[int]]) -> int:  # grid[i][j] 表示从该格出发向右/向下最多可走的步数；返回左上到右下的最少访问格数
        m, n = len(grid), len(grid[0])  # 行数 m 与列数 n
        dist = [[-1] * n for _ in range(m)]  # dist[i][j] 为走到该格的最少步数，-1 表示暂不可达
        dist[0][0] = 1  # 起点本身算访问 1 个格子
        row = [[] for _ in range(m)]  # 每行一个小根堆（用 heappush/heappop 维护），元素为 (步数, 列下标)
        col = [[] for _ in range(n)]  # 每列一个小根堆，元素为 (步数, 行下标)
        for i in range(m):  # 行优先遍历，保证用到的来源格子都已算好
            for j in range(n):  # 逐列处理
                while row[i] and grid[i][row[i][0][1]] + row[i][0][1] < j:  # 堆顶格子的最远可达列已小于 j，属于过期信息
                    heappop(row[i])  # 弹出过期项
                if row[i] and (dist[i][j] == -1 or dist[i][j] > row[i][0][0] + 1):  # 从本行某可达格子一步跳过来，更优才更新
                    dist[i][j] = row[i][0][0] + 1  # 步数为来源格子步数 + 1
                while col[j] and grid[col[j][0][1]][j] + col[j][0][1] < i:  # 列方向同理：堆顶格子的最远可达行已小于 i
                    heappop(col[j])  # 弹出过期项
                if col[j] and (dist[i][j] == -1 or dist[i][j] > col[j][0][0] + 1):  # 从本列某可达格子一步跳过来，更优才更新
                    dist[i][j] = col[j][0][0] + 1  # 步数为来源格子步数 + 1
                if dist[i][j] != -1:  # 该格可达，才把它的信息登记到行列堆
                    heappush(row[i], (dist[i][j], j))  # 登记到所在行
                    heappush(col[j], (dist[i][j], i))  # 登记到所在列
        return dist[-1][-1]  # 终点的最少步数，不可达时即为 -1
