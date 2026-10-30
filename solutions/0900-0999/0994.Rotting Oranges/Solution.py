# 题目：994. 腐烂的橘子（Rotting Oranges）
# 思路：多源 BFS。所有腐烂橘子同时入队，每分钟向上下左右扩散一层，用 cnt 记录剩余新鲜橘子数。
# 时间复杂度：O(mn)，每个格子最多入队一次；空间复杂度：O(mn)，队列最多存放全部格子。
class Solution:  # LeetCode 约定的题解类
    def orangesRotting(self, grid: List[List[int]]) -> int:  # grid：0 空格 / 1 新鲜橘子 / 2 腐烂橘子；返回到全部腐烂所需的最少分钟数
        m, n = len(grid), len(grid[0])  # m、n 分别是网格的行数与列数
        cnt = 0  # cnt 记录当前还剩下的新鲜橘子数
        q = deque()  # 多源 BFS 队列，先放入所有一开始就腐烂的橘子
        for i, row in enumerate(grid):  # 枚举每一行及其下标
            for j, x in enumerate(row):  # 枚举该行的每一格及其下标
                if x == 2:  # 腐烂橘子作为 BFS 源点
                    q.append((i, j))  # 入队，等待向外扩散
                elif x == 1:  # 新鲜橘子只需先计数
                    cnt += 1  # 新鲜橘子总数加一
        ans = 0  # ans 记录已经过去的分钟数
        dirs = (-1, 0, 1, 0, -1)  # 四个方向写成相邻成对的形式，配合 pairwise 依次取用
        while q and cnt:  # 还有腐烂橘子且还有新鲜橘子，就继续扩散
            ans += 1  # 进入下一分钟
            for _ in range(len(q)):  # 只处理当前这一层，保证同一层的橘子属于同一分钟
                i, j = q.popleft()  # 取出一个腐烂橘子坐标
                for a, b in pairwise(dirs):  # 依次得到四个方向 (dx, dy)
                    x, y = i + a, j + b  # 计算邻居坐标
                    if 0 <= x < m and 0 <= y < n and grid[x][y] == 1:  # 邻居在网格内且为新鲜橘子才会被感染
                        grid[x][y] = 2  # 标记为腐烂，避免重复访问
                        q.append((x, y))  # 新腐烂的橘子入队，下一分钟继续扩散
                        cnt -= 1  # 剩余新鲜橘子数减一
                        if cnt == 0:  # 新鲜橘子全部感染完
                            return ans  # 当前分钟结束后恰好清空，返回分钟数
        return -1 if cnt else 0  # 队列空了还有剩余说明被隔离返回 -1；否则本来就没有新鲜橘子返回 0
