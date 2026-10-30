# 题目：827. 最大人工岛（Making A Large Island）
# 思路：先 DFS 把每块陆地连通块编号、用 Counter 统计面积，再枚举每个 0，把四邻不同的岛号放进集合求和再加 1，全程取最大值。
# 时间复杂度：O(n^2)，每个格子只被处理常数次；空间复杂度：O(n^2)，标记矩阵 p 与递归栈。
class Solution:  # LeetCode 约定的题解类
    def largestIsland(self, grid: List[List[int]]) -> int:  # grid 是 0/1 方阵，返回最多改一个 0 为 1 后能得到的最大岛面积
        def dfs(i: int, j: int):  # 内层 DFS：从 (i, j) 淹没整块连通块；无返回值，靠闭包修改 p 与 cnt
            p[i][j] = root  # 打上当前岛号 root，同时作为已访问标记
            cnt[root] += 1  # 当前岛的面积加一
            for a, b in pairwise(dirs):  # pairwise 把 5 个偏移量两两配对，正好给出四个方向 (a, b)
                x, y = i + a, j + b  # 邻居坐标
                if 0 <= x < n and 0 <= y < n and grid[x][y] and p[x][y] == 0:  # 不越界、是陆地、且尚未被编号
                    dfs(x, y)  # 递归访问该邻居

        n = len(grid)  # 方阵边长（DFS 里引用的 n 在调用前已经赋好值）
        cnt = Counter()  # Counter：cnt[id] 就是编号 id 的岛面积，访问缺失键得到 0
        p = [[0] * n for _ in range(n)]  # p[i][j] 记录格子属于哪块岛，0 表示不是已编号的陆地
        dirs = (-1, 0, 1, 0, -1)  # 四个方向的偏移量，首尾各一个 -1 以便 pairwise 配对
        root = 0  # 当前岛号，从 0 开始递增
        for i, row in enumerate(grid):  # 第一遍：给每块陆地连通块编号并统计面积；逐行扫描并拿到行号 i 与整行 row
            for j, x in enumerate(row):  # 逐格扫描，拿到列号 j 与格值 x
                if x and p[i][j] == 0:  # 是陆地且还没编号，说明发现新岛
                    root += 1  # 分配新岛号
                    dfs(i, j)  # 淹没整块岛，面积记入 cnt
        ans = max(cnt.values() or [0])  # 不填海时的答案：cnt 的最大值；全是水时 cnt 为空，用 or [0] 兜底避免 max 报错
        for i, row in enumerate(grid):  # 第二遍：尝试把每个 0 填成 1；逐行扫描
            for j, x in enumerate(row):  # 逐格扫描
                if x == 0:  # 只处理水格子（填成陆地才有收益）
                    s = set()  # 收集四邻不同的岛号，集合天然去重
                    for a, b in pairwise(dirs):  # 枚举四个方向
                        x, y = i + a, j + b  # 邻居坐标；这里的 x, y 遮蔽了外层同名变量，但外层 x 每轮都会重新赋值，所以无影响
                        if 0 <= x < n and 0 <= y < n:  # 只检查不越界
                            s.add(p[x][y])  # 记下邻格所属岛号（水格为 0，面积为 0，不影响结果）
                    ans = max(ans, sum(cnt[root] for root in s) + 1)  # 填海面积 = 新格子 1 + 相邻岛面积之和（生成器变量 root 同样只是遮蔽外层同名变量）
        return ans  # 返回最大人工岛面积
