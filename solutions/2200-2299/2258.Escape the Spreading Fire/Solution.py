# 题目：2258. 逃离火灾（Escape the Spreading Fire）
# 思路：二分答案 t，check(t) 先让火自由扩散 t 分钟，再让火与人逐分钟同步推进做 BFS，人只能走火未覆盖的空地，判断能否到达右下角。
# 时间复杂度：O(m * n * log(m * n))，二分 log 轮、每轮两次 BFS；空间复杂度：O(m * n)，着火表和访问表。
class Solution:  # LeetCode 约定的题解类
    def maximumMinutes(self, grid: List[List[int]]) -> int:  # grid：0 空地、1 火源、2 墙；返回最多可等待的分钟数
        def spread(q: Deque[int]) -> Deque[int]:  # 让当前着火点扩散一分钟，返回新着火点队列
            nq = deque()  # 收集这一分钟新烧起来的格子
            while q:  # 逐个处理本轮已知的着火点
                i, j = q.popleft()  # 取出队首格子坐标
                for a, b in pairwise(dirs):  # 遍历四个方向向量
                    x, y = i + a, j + b  # 相邻格的行列坐标
                    if 0 <= x < m and 0 <= y < n and not fire[x][y] and grid[x][y] == 0:  # 在界内、未着火且是空地才会被点燃
                        fire[x][y] = True  # 标记该格已着火
                        nq.append((x, y))  # 放进下一轮的扩散队列
            return nq  # 返回新产生的火源

        def check(t: int) -> bool:  # 判断「先等 t 分钟再出发」能否安全逃到终点
            for i in range(m):  # 逐行重置着火表
                for j in range(n):  # 逐列重置着火表
                    fire[i][j] = False  # 清掉上一轮二分留下的着火标记
            q1 = deque()  # 火 BFS 使用的队列
            for i, row in enumerate(grid):  # 遍历每一行及其下标
                for j, x in enumerate(row):  # 遍历行内每个格子的值
                    if x == 1:  # 该格是火源
                        fire[i][j] = True  # 火源所在格立刻算作已着火
                        q1.append((i, j))  # 火源入队
            while t and q1:  # 让火先自由扩散 t 分钟（火已无法扩散时提前结束）
                q1 = spread(q1)  # 扩散一分钟
                t -= 1  # 剩余等待时间减一
            if fire[0][0]:  # 出发点已被火覆盖，人无法动身
                return False  # 该等待时间不可行
            q2 = deque([(0, 0)])  # 人从左上角出发
            vis = [[False] * n for _ in range(m)]  # 人本轮是否到过某格
            vis[0][0] = True  # 标记起点已访问
            while q2:  # 人还能继续扩展就继续走
                for _ in range(len(q2)):  # 按层扩展：只处理这一分钟内的所有位置
                    i, j = q2.popleft()  # 取出队首坐标
                    if fire[i][j]:  # 人到得比火晚，该格已被烧到
                        continue  # 作废这个位置，不能再从这里扩展
                    for a, b in pairwise(dirs):  # 尝试四个相邻方向
                        x, y = i + a, j + b  # 相邻格的行列坐标
                        if (  # 依次判断能否进入该相邻格
                            0 <= x < m  # 行坐标在界内
                            and 0 <= y < n  # 列坐标在界内
                            and not vis[x][y]  # 这一格还没走过
                            and not fire[x][y]  # 这一格还没着火
                            and grid[x][y] == 0  # 这一格是空地（既不是墙也不是火源）
                        ):  # 条件全部满足才允许移动
                            if x == m - 1 and y == n - 1:  # 正好踏进右下角终点
                                return True  # 能逃出去，该等待时间可行
                            vis[x][y] = True  # 标记已访问，避免重复入队
                            q2.append((x, y))  # 入队，下一分钟从这里继续扩展
                q1 = spread(q1)  # 人走完这一分钟，火也扩散一分钟
            return False  # 队列耗尽仍未到终点，说明该等待时间不可行

        m, n = len(grid), len(grid[0])  # 网格的行数与列数（闭包函数会用到）
        l, r = -1, m * n  # 二分区间：-1 表示不等待也走不掉，m * n 当作「无穷大」的上界
        dirs = (-1, 0, 1, 0, -1)  # 方向数组，相邻两项组成 (上、右、下、左) 的位移
        fire = [[False] * n for _ in range(m)]  # 着火表，check 会复用它并逐轮重置
        while l < r:  # 二分查找可行的最大等待时间
            mid = (l + r + 1) >> 1  # 上取整的中点，避免 l == mid 时死循环
            if check(mid):  # 等待 mid 分钟可以逃生
                l = mid  # 可行就抬高下界
            else:  # 等待 mid 分钟无法逃生
                r = mid - 1  # 缩小上界
        return int(1e9) if l == m * n else l  # 取到上界说明可以无限等待，按题目要求返回 1e9
