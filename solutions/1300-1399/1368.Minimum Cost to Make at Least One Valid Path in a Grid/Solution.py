# 题目：1368. 使网格图至少有一条有效路径的最小代价（Minimum Cost to Make at Least One Valid Path in a Grid）
# 思路：0-1 BFS（双端队列）。沿当前箭头走代价为 0 入队首，改箭头代价为 1 入队尾，第一次到达终点时的代价即最小。
# 时间复杂度：O(m·n)，每格最多出队一次；空间复杂度：O(m·n)，vis 集合与队列。
class Solution:  # LeetCode 约定的题解类
    def minCost(self, grid: List[List[int]]) -> int:  # grid：每格是箭头方向（1 右、2 左、3 下、4 上），返回最小修改代价
        m, n = len(grid), len(grid[0])  # m、n 分别是网格的行数与列数
        dirs = [[0, 0], [0, 1], [0, -1], [1, 0], [-1, 0]]  # dirs 下标 1~4 对应右、左、下、上
        q = deque([(0, 0, 0)])  # 双端队列，元素为 (行, 列, 到达该格的代价)
        vis = set()  # vis 记录已经处理过的格子
        while q:  # 队列非空就继续扩展
            i, j, d = q.popleft()  # 取队首元素
            if (i, j) in vis:  # 该格子已经处理过
                continue  # 跳过
            vis.add((i, j))  # 标记为已处理
            if i == m - 1 and j == n - 1:  # 到达右下角
                return d  # 直接返回当前代价，0-1 BFS 保证它最小
            for k in range(1, 5):  # 枚举四个方向
                x, y = i + dirs[k][0], j + dirs[k][1]  # 候选邻格坐标
                if 0 <= x < m and 0 <= y < n:  # 判断邻格是否仍在网格内
                    if grid[i][j] == k:  # 当前箭头正好指向 k，可以零代价前进
                        q.appendleft((x, y, d))  # 代价不变，插入队首
                    else:  # 否则需要改一次箭头方向
                        q.append((x, y, d + 1))  # 代价加 1，插入队尾
        return -1  # 队列耗尽仍未到达终点，返回 -1
