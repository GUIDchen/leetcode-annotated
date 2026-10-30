# 题目：1263. 推箱子（Minimum Moves to Move a Box to Their Target Location）
# 思路：状态为（人的位置，箱子的位置）；推箱子代价 1 放队尾、人空走代价 0 放队首，用双端队列做 0-1 BFS，首次弹出目标状态时的代价即最少推动次数。
# 时间复杂度：O((mn)²)，状态数为 mn×mn、每个状态 4 次转移；空间复杂度：O((mn)²)，vis 表与队列。
class Solution:  # LeetCode 约定的题解类
    def minPushBox(self, grid: List[List[str]]) -> int:  # grid 是字符网格：'S' 人、'B' 箱子、'T' 目标、'#' 障碍
        def f(i: int, j: int) -> int:  # 内部坐标压缩函数
            return i * n + j  # 行优先编号：i * n + j；n 在调用时已由外层绑定

        def check(i: int, j: int) -> bool:  # 合法性判断：坐标不越界且不是墙
            return 0 <= i < m and 0 <= j < n and grid[i][j] != "#"  # 链式比较同时检查上下左右边界与障碍物

        for i, row in enumerate(grid):  # 扫描整个网格找起点
            for j, c in enumerate(row):  # 同时取得列下标 j 与该格字符 c
                if c == "S":  # 找到人的起点
                    si, sj = i, j  # 记下人的初始位置
                elif c == "B":  # 否则判断是否为箱子起点
                    bi, bj = i, j  # 记下箱子的初始位置
        m, n = len(grid), len(grid[0])  # 行列数；f 与 check 在定义时并不求值，因此放在后面赋值也来得及
        dirs = (-1, 0, 1, 0, -1)  # 四方向增量交错成对，配合 pairwise 得到 (上、右、下、左)
        q = deque([(f(si, sj), f(bi, bj), 0)])  # 双端队列：元素为（人的编号，箱子的编号，已推动次数）
        vis = [[False] * (m * n) for _ in range(m * n)]  # vis[人的编号][箱子的编号] 标记二元状态是否访问过
        vis[f(si, sj)][f(bi, bj)] = True  # 标记初始状态
        while q:  # 队列非空则继续搜索
            s, b, d = q.popleft()  # 弹出队首：s 人编号、b 箱子编号、d 已推动次数
            bi, bj = b // n, b % n  # 先还原箱子的行、列坐标
            if grid[bi][bj] == "T":  # 箱子到达目标格 T
                return d  # 0-1 BFS 保证此刻 d 最小，可以直接返回
            si, sj = s // n, s % n  # 再还原人的行、列坐标
            for a, b in pairwise(dirs):  # pairwise 依次取出相邻两元素组成方向增量；注意此处的 b 覆盖了上面的箱子变量，但箱子坐标已存于 bi,bj
                sx, sy = si + a, sj + b  # 人朝该方向走一步后的坐标
                if not check(sx, sy):  # 越界或撞墙则无法走，放弃该方向
                    continue  # 跳过本次方向
                if sx == bi and sy == bj:  # 人的目标格正是箱子所在，等价于推箱子
                    bx, by = bi + a, bj + b  # 箱子被推到的位置 = 箱子当前坐标 + 同方向增量
                    if not check(bx, by) or vis[f(sx, sy)][f(bx, by)]:  # 箱子位置非法，或该状态已经访问过
                        continue  # 跳过本次方向
                    vis[f(sx, sy)][f(bx, by)] = True  # 标记新状态：人在箱子原位，箱子前进一格
                    q.append((f(sx, sy), f(bx, by), d + 1))  # 推动一次代价为 1，放队尾
                elif not vis[f(sx, sy)][f(bi, bj)]:  # 否则只是人空走一步（箱子不动），且状态未访问
                    vis[f(sx, sy)][f(bi, bj)] = True  # 标记该状态已访问
                    q.appendleft((f(sx, sy), f(bi, bj), d))  # 空走代价为 0，放队首，维持队列按代价非递减
        return -1  # 队列耗尽仍无法抵达目标，返回 -1
