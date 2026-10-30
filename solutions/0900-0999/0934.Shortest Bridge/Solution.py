# 题目：934. 最短的桥（Shortest Bridge）
# 思路：先 DFS 把第一座岛整块染色并入队，再用多源 BFS 逐层向外扩张海水，第一次碰到第二座岛时的层数就是最短桥长。
# 时间复杂度：O(n^2)，每个格子最多被访问常数次；空间复杂度：O(n^2)，队列与递归栈最坏会存下整个网格。
class Solution:  # LeetCode 约定的题解类
    def shortestBridge(self, grid: List[List[int]]) -> int:  # grid 中 1 是陆地、0 是海水；返回连接两座岛所需翻转的最小 0 的个数
        def dfs(i, j):  # 把与 (i, j) 连通的第一座岛整块标记并收集进队列
            q.append((i, j))  # 先入队，作为多源 BFS 的起点之一（n、dirs、q 在调用时才求值，闭包可以后定义）
            grid[i][j] = 2  # 标 2 表示“属于第一座岛且已访问”
            for a, b in pairwise(dirs):  # pairwise 把 dirs 两两配对，得到四个方向 (a, b)
                x, y = i + a, j + b  # 相邻格子的坐标
                if 0 <= x < n and 0 <= y < n and grid[x][y] == 1:  # 先做边界检查，再判断是否仍是未访问的陆地
                    dfs(x, y)  # 继续向同岛的其它陆地扩散

        n = len(grid)  # 网格边长
        dirs = (-1, 0, 1, 0, -1)  # 四方向偏移量，相邻两个数组成一个 (a, b) 方向
        q = deque()  # 双端队列，充当多源 BFS 的队列
        i, j = next((i, j) for i in range(n) for j in range(n) if grid[i][j])  # 第一个值为 1 的格子必然是第一座岛的一部分
        dfs(i, j)  # DFS 把整座岛染色并全部入队
        ans = 0  # ans 记录当前已扩张的海水层数，也就是桥长
        while 1:  # 循环直到某次扩张碰到第二座岛并直接 return
            for _ in range(len(q)):  # 只处理当前层的格子，层数才不会错乱
                i, j = q.popleft()  # 取出队首格子
                for a, b in pairwise(dirs):  # 枚举四个相邻方向
                    x, y = i + a, j + b  # 相邻格子的坐标
                    if 0 <= x < n and 0 <= y < n:  # 只处理网格内的格子
                        if grid[x][y] == 1:  # 遇到 1 说明到达第二座岛，当前层数就是最短桥长
                            return ans  # 直接返回答案
                        if grid[x][y] == 0:  # 遇到 0 说明是可扩张的海水
                            grid[x][y] = 2  # 把海水标成 2，表示已经访问，防止重复入队
                            q.append((x, y))  # 入队，作为下一层继续扩张的起点
            ans += 1  # 一整层扩张完，桥长加一
