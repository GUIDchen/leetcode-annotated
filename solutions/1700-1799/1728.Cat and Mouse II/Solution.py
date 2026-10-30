# 题目：1728. 猫和老鼠 II（Cat and Mouse II）
# 思路：状态为 (老鼠位置, 猫位置, 轮到谁走)，从已知终局出发反向 BFS 推胜负；用出度计数处理「所有后继都对当前方不利则当前方必败」。
# 时间复杂度：O(V^2 * E)，V 是编号空间、E 是每格可跳达的格子数；空间复杂度：O(V^2)，需要保存每个状态的结论与出度。
class Solution:  # LeetCode 约定的题解类
    def canMouseWin(self, grid: List[str], catJump: int, mouseJump: int) -> bool:  # grid 是棋盘，catJump/mouseJump 是两个棋子各自的最大跳跃距离
        m, n = len(grid), len(grid[0])  # m 是行数，n 是列数
        cat_start = mouse_start = food = 0  # 猫、老鼠、食物三者位置的一维编号
        dirs = (-1, 0, 1, 0, -1)  # 四方向增量表，相邻两项组成 (dx, dy)
        g_mouse = [[] for _ in range(m * n)]  # 每个格子按老鼠规则一步能到达的格子列表
        g_cat = [[] for _ in range(m * n)]  # 每个格子按猫规则一步能到达的格子列表

        # 第一步：扫描棋盘记录三个关键位置，并按两种跳跃规则建图
        for i, row in enumerate(grid):  # 逐行遍历棋盘
            for j, c in enumerate(row):  # 逐列取出当前格子的字符
                if c == "#":  # 障碍格不能停留，也不必建边
                    continue  # 跳过这个格子
                v = i * n + j  # 二维坐标压成一维编号
                if c == "C":  # 当前格是猫的起点
                    cat_start = v  # 记下猫的起点编号
                elif c == "M":  # 当前格是老鼠的起点
                    mouse_start = v  # 记下老鼠的起点编号
                elif c == "F":  # 当前格是食物
                    food = v  # 记下食物编号
                for a, b in pairwise(dirs):  # 依次取四个相邻方向对 (a, b)
                    for k in range(mouseJump + 1):  # 老鼠沿该方向最多跳 mouseJump 步，k = 0 表示原地
                        x, y = i + k * a, j + k * b  # 落点坐标
                        if not (0 <= x < m and 0 <= y < n and grid[x][y] != "#"):  # 越界或撞墙
                            break  # 再往前同样不可达，结束这个方向
                        g_mouse[v].append(x * n + y)  # 记录老鼠从 v 可一步到达该格
                    for k in range(catJump + 1):  # 猫沿同一方向最多跳 catJump 步
                        x, y = i + k * a, j + k * b  # 落点坐标
                        if not (0 <= x < m and 0 <= y < n and grid[x][y] != "#"):  # 越界或撞墙
                            break  # 同方向后续格子都不可达，跳出
                        g_cat[v].append(x * n + y)  # 记录猫从 v 可一步到达该格
        return self.calc(g_mouse, g_cat, mouse_start, cat_start, food) == 1  # 结论 1 表示老鼠胜，转成 bool 返回

    # 反向 BFS：从已知终局出发，把胜负结论传播给所有一步能到达它的状态
    def calc(  # 返回起点结论：1 老鼠胜、2 猫胜
        self,  # 实例本身
        g_mouse: List[List[int]],  # 老鼠的可达图
        g_cat: List[List[int]],  # 猫的可达图
        mouse_start: int,  # 老鼠起点编号
        cat_start: int,  # 猫起点编号
        hole: int,  # 食物所在编号，是老鼠的获胜位置
    ) -> int:  # 返回值就是胜负结论
        def get_prev_states(state):  # 求一步能到达 state 的所有前驱状态
            m, c, t = state  # 拆出老鼠位置、猫位置、轮次
            pt = t ^ 1  # 前驱轮次与当前相反：0 和 1 用异或互换
            pre = []  # 收集前驱
            if pt == 1:  # 前驱轮到猫走，只有猫的位置变化
                for pc in g_cat[c]:  # 枚举猫能一步到达的格子
                    if ans[m][pc][1] == 0:  # 只保留结论还没确定的状态，避免重复入队
                        pre.append((m, pc, pt))  # 记录这个前驱
            else:  # 前驱轮到老鼠走，只有老鼠的位置变化
                for pm in g_mouse[m]:  # 枚举老鼠能一步到达的格子
                    if ans[pm][c][0] == 0:  # 同样只保留结论未知的状态
                        pre.append((pm, c, 0))  # 第三项固定为 0，表示轮到老鼠
            return pre  # 返回前驱列表

        n = len(g_mouse)  # 编号空间大小
        degree = [[[0, 0] for _ in range(n)] for _ in range(n)]  # degree[m][c][t] 保存该状态剩余的后继个数
        for i in range(n):  # 枚举轮到走棋一方的位置
            for j in range(n):  # 枚举另一方的位置
                degree[i][j][0] = len(g_mouse[i])  # 轮到老鼠时，出度就是老鼠的走法数
                degree[i][j][1] = len(g_cat[j])  # 轮到猫时，出度就是猫的走法数

        # ans[m][c][t]：0 表示未知，1 表示老鼠胜，2 表示猫胜
        ans = [[[0, 0] for _ in range(n)] for _ in range(n)]  # 初始化所有状态为未知
        q = deque()  # 双端队列作为 BFS 容器
        for i in range(n):  # 用一个变量同时枚举两个棋子的位置
            ans[hole][i][1] = 1  # 轮到猫走而老鼠已在食物格：老鼠胜
            ans[i][hole][0] = 2  # 轮到老鼠走而猫已在食物格：猫先吃过，猫胜
            ans[i][i][1] = ans[i][i][0] = 2  # 同格则猫已抓住老鼠，两种轮次都是猫胜
            q.append((hole, i, 1))  # 把上面四个终局状态依次入队
            q.append((i, hole, 0))  # 老鼠已在食物格，轮到猫走
            q.append((i, i, 0))  # 两只同格，轮到老鼠
            q.append((i, i, 1))  # 两只同格，轮到猫
        while q:  # 队列非空就继续传播结论
            state = q.popleft()  # 取出队头状态
            t = ans[state[0]][state[1]][state[2]]  # 该状态的结论将传给它的前驱
            for prev_state in get_prev_states(state):  # 枚举一步能到达该状态的前驱
                pm, pc, pt = prev_state  # 拆出前驱三个分量
                if pt == t - 1:  # 前驱轮次与结论相反：前驱方一步就能走到对自己有利的状态
                    ans[pm][pc][pt] = t  # 前驱立刻得到同一结论
                    q.append(prev_state)  # 入队继续传播
                else:  # 前驱与结论同轮次：前驱方走到的是对自己不利的状态
                    degree[pm][pc][pt] -= 1  # 前驱的可用后继少一个
                    if degree[pm][pc][pt] == 0:  # 所有后继都对前驱方不利
                        ans[pm][pc][pt] = t  # 前驱必败，继承同一结论
                        q.append(prev_state)  # 入队继续传播
        return ans[mouse_start][cat_start][0]  # 返回题意起点（轮到老鼠走）的结论
