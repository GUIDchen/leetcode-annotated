# 题目：803. 打砖块（Bricks Falling When Hit）
# 思路：逆向思考——先删掉所有会被击打的砖并统计稳定砖块，再按时间倒序把砖补回，用并查集观察与「屋顶」虚拟节点相连集合的大小增量，减去砖自身即本次掉落数。
# 时间复杂度：O(mn + k·α(mn))，并查集近似 O(1)；空间复杂度：O(mn)，并查集与网格副本。
class Solution:  # LeetCode 约定的题解类
    def hitBricks(self, grid: List[List[int]], hits: List[List[int]]) -> List[int]:  # grid：砖块矩阵；hits：击打顺序；返回每次击打掉落的砖数
        def find(x):  # 并查集查找，带路径压缩（闭包引用后面的 p）
            if p[x] != x:  # 还没直接指向根
                p[x] = find(p[x])  # 递归压缩，把父指针直接接到根上
            return p[x]  # 返回所在集合的根

        def union(a, b):  # 合并两个集合
            pa, pb = find(a), find(b)  # 分别找出各自的根
            if pa != pb:  # 不同集合才需要合并
                size[pb] += size[pa]  # 把 a 所在集合的大小累加到 b 所在集合
                p[pa] = pb  # 让 a 的根指向 b 的根

        m, n = len(grid), len(grid[0])  # 行数、列数
        p = list(range(m * n + 1))  # 并查集父数组，多一个屋顶虚拟节点 m*n
        size = [1] * len(p)  # 每个集合初始大小为 1
        g = deepcopy(grid)  # 深拷贝网格，避免改动输入
        for i, j in hits:  # 先把所有会被击打的砖清空
            g[i][j] = 0  # 置 0 表示该位置没有砖
        for j in range(n):  # 首行的砖天然稳定，与屋顶相连
            if g[0][j] == 1:  # 该位置首行有砖
                union(j, m * n)  # 并入屋顶虚拟节点
        for i in range(1, m):  # 从第二行开始处理
            for j in range(n):  # 逐列处理
                if g[i][j] == 0:  # 空位不用合并
                    continue  # 跳过本次循环
                if g[i - 1][j] == 1:  # 上方有砖
                    union(i * n + j, (i - 1) * n + j)  # 上下相邻的砖块合并
                if j > 0 and g[i][j - 1] == 1:  # 左侧有砖（j > 0 防越界）
                    union(i * n + j, i * n + j - 1)  # 左右相邻的砖块合并
        ans = []  # 倒序收集结果
        for i, j in hits[::-1]:  # 按时间倒序回放击打
            if grid[i][j] == 0:  # 原本这里就没有砖
                ans.append(0)  # 这次击打自然掉 0 块
                continue  # 跳过后续合并逻辑
            g[i][j] = 1  # 把砖补回去
            prev = size[find(m * n)]  # 补砖前，与屋顶连通集合的大小
            if i == 0:  # 补回的是首行的砖
                union(j, m * n)  # 直接挂到屋顶上
            for a, b in [(-1, 0), (1, 0), (0, 1), (0, -1)]:  # 枚举上下左右四个方向
                x, y = i + a, j + b  # 计算邻居坐标
                if 0 <= x < m and 0 <= y < n and g[x][y] == 1:  # 邻居在界内且有砖
                    union(i * n + j, x * n + y)  # 与相邻砖块合并
            curr = size[find(m * n)]  # 补砖后，与屋顶连通集合的大小
            ans.append(max(0, curr - prev - 1))  # 增量减去这块砖自身，就是本次掉落的砖数
        return ans[::-1]  # 倒序结果翻回时间正序
