# 题目：2056. 棋盘上有效移动组合的数目（Number of Valid Move Combinations On Chessboard）
# 思路：回溯枚举每个棋子的走法（原地不动，或沿某个方向走到某一格停下），用 dist 记录各棋子的逐时刻占用格，检查同一时刻同格与路径阻挡来排除冲突。
# 时间复杂度：指数级，每个棋子至多约 1 + 8 × 8 种走法；空间复杂度：O(n × 8 × 8)，每个棋子的路径占用表。
rook_dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)]  # 车的四个直线方向
bishop_dirs = [(1, 1), (1, -1), (-1, 1), (-1, -1)]  # 象的四个斜线方向
queue_dirs = rook_dirs + bishop_dirs  # 皇后的方向 = 车 + 象


def get_dirs(piece: str) -> List[Tuple[int, int]]:  # 根据棋子类型返回方向表
    match piece[0]:  # 按类型首字母匹配
        case "r":  # 车
            return rook_dirs  # 返回车的方向
        case "b":  # 象
            return bishop_dirs  # 返回象的方向
        case _:  # 其余按皇后处理
            return queue_dirs  # 返回皇后的方向


class Solution:  # 题解类
    def countCombinations(self, pieces: List[str], positions: List[List[int]]) -> int:  # pieces 是棋子类型，positions 是初始坐标
        def check_stop(i: int, x: int, y: int, t: int) -> bool:  # 判断第 i 个棋子在 t 时刻停在 (x,y) 是否安全
            return all(dist[j][x][y] < t for j in range(i))  # 更早的棋子都没有占用该格到 t 之后

        def check_pass(i: int, x: int, y: int, t: int) -> bool:  # 判断行进途中经过 (x,y) 的时刻 t 是否与更早棋子冲突
            for j in range(i):  # 逐个比较更早的棋子
                if dist[j][x][y] == t:  # 同一时刻占用同一格就相撞
                    return False  # 冲突
                if end[j][0] == x and end[j][1] == y and end[j][2] <= t:  # 更早棋子已停在该格且停下时刻不晚于 t
                    return False  # 挡路，冲突
            return True  # 路径可行

        def dfs(i: int) -> None:  # 回溯：为第 i 个棋子选择一种走法
            if i >= n:  # 所有棋子都安排完
                nonlocal ans  # 需要修改外层计数变量
                ans += 1  # 合法组合加一
                return  # 返回上一层
            x, y = positions[i]  # 第 i 个棋子的起点
            dist[i][:] = [[-1] * m for _ in range(m)]  # 清空该棋子的路径占用表
            dist[i][x][y] = 0  # 起点在时刻 0 被占用
            end[i] = (x, y, 0)  # 记录停在起点
            if check_stop(i, x, y, 0):  # 情况一：原地不动
                dfs(i + 1)  # 在不动的前提下安排下一个棋子
            dirs = get_dirs(pieces[i])  # 该棋子可走的方向
            for dx, dy in dirs:  # 枚举每个方向
                dist[i][:] = [[-1] * m for _ in range(m)]  # 每个方向开始前重置路径
                dist[i][x][y] = 0  # 重新标记起点
                nx, ny, nt = x + dx, y + dy, 1  # 沿该方向的第一格坐标与时刻
                while 1 <= nx < m and 1 <= ny < m and check_pass(i, nx, ny, nt):  # 一格一格前进，直到出界或撞车
                    dist[i][nx][ny] = nt  # 标记该格在第 nt 时刻被占用
                    end[i] = (nx, ny, nt)  # 记录新的终点
                    if check_stop(i, nx, ny, nt):  # 停在这里若合法
                        dfs(i + 1)  # 递归安排下一个棋子
                    nx += dx  # 继续沿方向推进
                    ny += dy  # 列坐标同步推进
                    nt += 1  # 时刻加一

        n = len(pieces)  # 棋子个数
        m = 9  # 坐标 1..8，9 是开区间上界
        dist = [[[-1] * m for _ in range(m)] for _ in range(n)]  # dist[i][x][y]：第 i 个棋子的路径占用表
        end = [(0, 0, 0) for _ in range(n)]  # end[i]：第 i 个棋子的终点与停下时刻
        ans = 0  # 合法组合计数器
        dfs(0)  # 从第 0 个棋子开始搜索
        return ans  # 返回组合总数
