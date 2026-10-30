# 题目：286. 墙与门（Walls and Gates）—— 把每个空房间填成到最近门的距离，门记 0，墙记 -1，空房间初值 2**31-1。
# 核心思路：多源 BFS。把所有门一次性入队当作第 0 层，逐层向外扩散，空房间第一次被到达时的层数即最短距离。
# 时间复杂度：O(m·n)，每个格子最多入队一次；空间复杂度：O(m·n)，队列最坏情况下装下所有格子。
class Solution:  # LeetCode 约定的题解类
    def wallsAndGates(self, rooms: List[List[int]]) -> None:  # rooms：原地修改的矩阵，无返回值
        # 题目要求原地修改、不返回结果，下面是该约定的说明文档字符串（内容不可改动）
        """
        Do not return anything, modify rooms in-place instead.
        """
        m, n = len(rooms), len(rooms[0])  # 行数、列数（题意保证矩阵非空）
        inf = 2**31 - 1  # 用题面里的 INT_MAX 值表示“还不可达的空房间”
        q = deque([(i, j) for i in range(m) for j in range(n) if rooms[i][j] == 0])  # 多源 BFS 的起点：把所有门一次性入队，距离都为 0
        d = 0  # 当前扩散层数（即到门的距离）
        while q:  # 队列非空说明还有可达的空房间没被填过
            d += 1  # 进入下一层，距离加一
            for _ in range(len(q)):  # 只处理本层节点：len(q) 在处理前求值，新入队的节点留到下一层
                i, j = q.popleft()  # 取出队首坐标
                for a, b in [[0, 1], [0, -1], [1, 0], [-1, 0]]:  # 四个方向：右、左、下、上
                    x, y = i + a, j + b  # 邻居坐标
                    if 0 <= x < m and 0 <= y < n and rooms[x][y] == inf:  # 不越界，且是尚未访问的空房间（门和墙不是 inf，会被跳过）
                        rooms[x][y] = d  # 第一次到达即最短距离
                        q.append((x, y))  # 作为下一层次的起点入队
