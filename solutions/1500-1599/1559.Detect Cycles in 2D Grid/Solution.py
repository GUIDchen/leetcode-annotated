# 题目：1559. 二维网格图中探测环（Detect Cycles in 2D Grid）
# 思路：对每个未访问的同字符连通块做 DFS（用栈模拟），队列元素带上来源坐标以排除回头路；遇到同字符且已访问的相邻格子即说明成环。
# 时间复杂度：O(m·n)，每个格子至多入栈一次；空间复杂度：O(m·n)，访问矩阵与栈。
class Solution:  # LeetCode 约定的题解类
    def containsCycle(self, grid: List[List[str]]) -> bool:  # grid：字符矩阵；判断同字符格子能否连成一个环
        m, n = len(grid), len(grid[0])  # m 为行数，n 为列数
        vis = [[False] * n for _ in range(m)]  # 访问标记矩阵，初始全为 False
        dirs = (-1, 0, 1, 0, -1)  # 方向数组：相邻两项组成「上、右、下、左」四个方向向量
        for i, row in enumerate(grid):  # 枚举行
            for j, x in enumerate(row):  # 枚举列
                if vis[i][j]:  # 已经访问过，说明它属于之前处理过的连通块
                    continue  # 跳过，避免重复搜索
                vis[i][j] = True  # 新的连通块起点，先标记为已访问
                q = [(i, j, -1, -1)]  # 栈元素：(当前行, 当前列, 来源行, 来源列)，起点没有来源故记 -1
                while q:  # 栈不空就继续遍历该连通块
                    x, y, px, py = q.pop()  # 弹出当前格子，同时取出它的来源格子
                    for dx, dy in pairwise(dirs):  # 相邻两项组成一个方向向量 (dx, dy)
                        nx, ny = x + dx, y + dy  # 相邻格子坐标
                        if 0 <= nx < m and 0 <= ny < n:  # 保证相邻格子不越界
                            if grid[nx][ny] != grid[i][j] or (nx == px and ny == py):  # grid[i][j] 是该连通块起点的字符；字符不同或走回来源格子都跳过
                                continue  # 不是本块内的合法新走向，忽略
                            if vis[nx][ny]:  # 同字符且已访问，说明另一条路径也能到达，成环
                                return True  # 找到环直接返回 True
                            vis[nx][ny] = True  # 标记相邻格子已访问
                            q.append((nx, ny, x, y))  # 入栈，并把当前格子记为它的来源
        return False  # 遍历完所有格子仍没找到环
