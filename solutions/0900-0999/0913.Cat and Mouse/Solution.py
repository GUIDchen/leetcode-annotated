# 题目：913. 猫和老鼠（Cat and Mouse）
# 核心思路：博弈论 + 反向拓扑 BFS。从已知终局（鼠进洞判鼠胜、猫抓到鼠判猫胜）反向推导：前驱若有一步能走到自己获胜的局面则必胜，否则不断减少它的出边计数，计数为 0 说明无路可赢则必败。
# 时间复杂度：O(n^3)，状态数 O(n^2) 且每条边只松弛一次；空间复杂度：O(n^2)，保存 ans 与 degree 两个三维表。
HOLE, MOUSE_START, CAT_START = 0, 1, 2  # 洞、老鼠起点、猫起点的节点编号
MOUSE_TURN, CAT_TURN = 0, 1  # 用 0/1 表示当前轮到谁行动
MOUSE_WIN, CAT_WIN, TIE = 1, 2, 0  # 三种可能结果，0 同时兼作「尚未确定」


class Solution:  # 题解类
    def catMouseGame(self, graph: List[List[int]]) -> int:  # graph 是邻接表；返回 1 鼠胜、2 猫胜、0 平局
        def get_prev_states(state):  # 求某个状态的全部前驱状态，供反向 BFS 使用
            m, c, t = state  # 拆出鼠位置、猫位置、行动方
            pt = t ^ 1  # 上一回合的行动方是当前行动方取反
            pre = []  # 收集前驱状态
            if pt == CAT_TURN:  # 上一回合由猫行动，说明猫是从某个邻居 pc 走到 c 的
                for pc in graph[c]:  # 枚举猫所有可能的上一位置
                    if pc != HOLE:  # 猫不能在洞里，非法前驱要排除
                        pre.append((m, pc, pt))  # 记录这个合法前驱
            else:  # 否则上一回合由老鼠行动，老鼠是从某邻居 pm 走到 m 的
                for pm in graph[m]:  # 枚举老鼠所有可能的上一位置
                    pre.append((pm, c, pt))  # 老鼠可以进洞，无需过滤
            return pre  # 返回全部前驱

        n = len(graph)  # 节点个数
        ans = [[[0, 0] for _ in range(n)] for _ in range(n)]  # ans[m][c][t] 记录结果，0 表示尚未确定
        degree = [[[0, 0] for _ in range(n)] for _ in range(n)]  # degree[m][c][t] 记录该状态还有多少条出边未被判负
        for i in range(n):  # 遍历老鼠的位置
            for j in range(1, n):  # 遍历猫的位置，猫不会在洞 0 里，所以从 1 开始
                degree[i][j][MOUSE_TURN] = len(graph[i])  # 轮老鼠走时，出边数等于老鼠所在点的度数
                degree[i][j][CAT_TURN] = len(graph[j])  # 轮猫走时，出边数等于猫所在点的度数
            for j in graph[HOLE]:  # 猫不能进洞，扣除这些非法出边
                degree[i][j][CAT_TURN] -= 1  # 洞的邻居作为猫的位置时少一条进洞的边
        q = deque()  # 反向 BFS 队列
        for j in range(1, n):  # 终局一：老鼠在洞里，两种轮次都是老鼠胜
            ans[0][j][MOUSE_TURN] = ans[0][j][CAT_TURN] = MOUSE_WIN  # 把两个轮次的结果一起标记为老鼠胜
            q.append((0, j, MOUSE_TURN))  # 轮老鼠走的状态入队，作为传播起点
            q.append((0, j, CAT_TURN))  # 轮猫走的状态同样入队
        for i in range(1, n):  # 终局二：猫和老鼠同处一个非洞节点，猫立刻抓住老鼠
            ans[i][i][MOUSE_TURN] = ans[i][i][CAT_TURN] = CAT_WIN  # 两个轮次的结果一起标记为猫胜
            q.append((i, i, MOUSE_TURN))  # 轮老鼠走的状态入队
            q.append((i, i, CAT_TURN))  # 轮猫走的状态入队
        while q:  # 反向 BFS 主循环
            state = q.popleft()  # 取出一个结果已确定的状态
            t = ans[state[0]][state[1]][state[2]]  # 注意变量 t 被复用：这里表示该状态的结果
            for prev_state in get_prev_states(state):  # 遍历所有能一步走到该状态的前驱
                pm, pc, pt = prev_state  # 拆出前驱的三个维度
                if ans[pm][pc][pt] == TIE:  # 只处理结果尚未确定的前驱
                    win = (t == MOUSE_WIN and pt == MOUSE_TURN) or (  # 轮到该行动方走、且结果就是该行动方获胜，则前驱能一步取胜
                        t == CAT_WIN and pt == CAT_TURN  # 续行：猫行动且猫胜的情况
                    )  # 布尔表达式结束
                    if win:  # 前驱存在走向自己胜利的走法
                        ans[pm][pc][pt] = t  # 立即判定前驱为胜（胜局优先）
                        q.append(prev_state)  # 入队，继续向前传播
                    else:  # 否则这条边对前驱的行动方不利
                        degree[pm][pc][pt] -= 1  # 它的可选走法减一
                        if degree[pm][pc][pt] == 0:  # 走法全部耗尽，说明怎么走都会输
                            ans[pm][pc][pt] = t  # 前驱必败，结果与后继相同
                            q.append(prev_state)  # 入队，继续向前传播
        return ans[MOUSE_START][CAT_START][MOUSE_TURN]  # 初始状态的结果就是答案
