# 题目：542. 01 矩阵（01 Matrix）
# 思路：多源 BFS。先把所有 0 当作源点入队，再逐层向外扩展，每个 1 第一次被访问时的层数就是它到最近 0 的距离。
# 时间复杂度：O(m*n)，每个格子最多入队一次；空间复杂度：O(m*n)，答案矩阵与队列。
class Solution:  # LeetCode 约定的题解类
    def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:  # mat 是只含 0/1 的矩阵，返回每个位置到最近 0 的曼哈顿距离
        m, n = len(mat), len(mat[0])  # m、n 分别是矩阵的行数与列数
        ans = [[-1] * n for _ in range(m)]  # 答案矩阵，先全部填 -1 表示「尚未计算距离」，同时兼作访问标记
        q = deque()  # 双端队列作为 BFS 队列，存放待向外扩展的坐标
        for i, row in enumerate(mat):  # 第一遍扫描：同时拿到行下标 i 与该行内容 row
            for j, x in enumerate(row):  # 再逐个取出列下标 j 与格子的值 x
                if x == 0:  # 遇到值为 0 的格子
                    ans[i][j] = 0  # 0 到自己的距离就是 0
                    q.append((i, j))  # 把它入队，作为距离扩展的源点
        dirs = (-1, 0, 1, 0, -1)  # 四个方向的偏移量：上下左右，(a, b) 成对取值
        while q:  # 队列非空说明还有可向外扩展的格子
            i, j = q.popleft()  # 取出队首坐标（本层已确定距离的格子）
            for a, b in pairwise(dirs):  # 把偏移量两两配对，依次得到四个相邻方向
                x, y = i + a, j + b  # 相邻格子的行列坐标
                if 0 <= x < m and 0 <= y < n and ans[x][y] == -1:  # 位置合法且该格子还没被赋值，说明这是它第一次被最短路访问到
                    ans[x][y] = ans[i][j] + 1  # 距离等于当前格子距离加 1，BFS 保证这是最近 0 的距离
                    q.append((x, y))  # 新格子入队，继续向外扩展
        return ans  # 返回填好的距离矩阵
