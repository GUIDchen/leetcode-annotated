# 题目：1162. 地图分析（As Far from Land as Possible）
# 思路：多源 BFS，把所有陆地同时作为起点向外扩展，最后一层的层数即最远海洋格的曼哈顿距离。
# 时间复杂度：O(n²)，每个格子最多入队一次；空间复杂度：O(n²)，队列与地图同阶。
class Solution:  # LeetCode 约定的题解类
    def maxDistance(self, grid: List[List[int]]) -> int:  # grid 中 1 是陆地、0 是海洋，返回离陆地最远的海洋格到最近陆地的距离
        n = len(grid)  # 方阵边长
        q = deque((i, j) for i in range(n) for j in range(n) if grid[i][j])  # 所有陆地格作为多源 BFS 的起点入队
        ans = -1  # 距离答案，全陆地或全海洋时保持 -1
        if len(q) in (0, n * n):  # 没有陆地或全是陆地，都不存在海洋格
            return ans  # 直接返回 -1
        dirs = (-1, 0, 1, 0, -1)  # 四邻方向首尾闭合，便于 pairwise 取相邻两数
        while q:  # 逐层向外扩展
            for _ in range(len(q)):  # 固定当前层的节点数
                i, j = q.popleft()  # 取出队首坐标
                for a, b in pairwise(dirs):  # 依次得到上、右、下、左四个方向的偏移
                    x, y = i + a, j + b  # 邻居坐标
                    if 0 <= x < n and 0 <= y < n and grid[x][y] == 0:  # 邻居在界内且是尚未访问的海洋格
                        grid[x][y] = 1  # 标记为已到达，其距离已确定
                        q.append((x, y))  # 入队，下一层继续扩展
            ans += 1  # 每扩展一层，距离加一
        return ans  # 返回最远海洋格到最近陆地的距离
