# 题目：773. 滑动谜题（Sliding Puzzle）
# 核心思路：把 2×3 局面编码成 6 位字符串，从初始局面做 BFS，逐层扩展 0 与上下左右交换后的新局面，首次遇到目标串即最少步数。
# 时间复杂度 O(6!·6)，状态数最多 720 个；空间复杂度 O(6!)，用于 vis 集合与队列。
class Solution:  # LeetCode 约定的题解类
    def slidingPuzzle(self, board: List[List[int]]) -> int:  # board：2×3 的初始棋盘；返回还原为目标串的最少移动次数，无解返回 -1
        t = [None] * 6  # 长度 6 的复用缓冲：编码时逐位写入，避免每次都新建列表

        def gets():  # 闭包：把当前 board 按行优先编码成 6 位字符串
            for i in range(2):  # 枚举两行
                for j in range(3):  # 枚举三列
                    t[i * 3 + j] = str(board[i][j])  # 数字转字符写入缓冲的 i*3+j 位置
            return ''.join(t)  # 拼接成状态字符串返回

        def setb(s):  # 闭包：把状态字符串 s 解码写回 board
            for i in range(2):  # 枚举两行
                for j in range(3):  # 枚举三列
                    board[i][j] = int(s[i * 3 + j])  # 取出对应字符转成整数，写回棋盘

        def f():  # 闭包 f：生成 0 与上下左右交换后的全部后继状态
            res = []  # 存放后继状态的编码
            i, j = next((i, j) for i in range(2) for j in range(3) if board[i][j] == 0)  # 找到数字 0 所在的行 i 与列 j
            for a, b in [[0, -1], [0, 1], [1, 0], [-1, 0]]:  # 四个方向：(行增量, 列增量) 对应上、右、下、左
                x, y = i + a, j + b  # 计算交换目标格坐标
                if 0 <= x < 2 and 0 <= y < 3:  # 目标格必须落在 2×3 棋盘内
                    board[i][j], board[x][y] = board[x][y], board[i][j]  # 交换 0 与目标格
                    res.append(gets())  # 编码候选局面并加入结果
                    board[i][j], board[x][y] = board[x][y], board[i][j]  # 交换回来还原棋盘，避免影响后续方向
            return res  # 返回所有后继状态

        start = gets()  # 初始状态编码
        end = "123450"  # 目标状态：0 在右下角，其余按 1 到 5 排列
        if start == end:  # 开局即目标状态
            return 0  # 答案为 0 步
        vis = {start}  # 已访问集合，初始只含起点
        q = deque([start])  # BFS 队列，初始只放起点
        ans = 0  # ans 记录已走步数
        while q:  # 队列非空就继续按层扩展
            ans += 1  # 进入新的一层，步数加一
            for _ in range(len(q)):  # 只处理当前层的 len(q) 个状态，保证 ans 与层数同步
                x = q.popleft()  # 取出队首状态
                setb(x)  # 把状态还原到 board 上
                for y in f():  # 枚举所有后继状态
                    if y == end:  # 一步到达目标，当前步数就是答案
                        return ans  # 返回最少步数
                    if y not in vis:  # 后继状态未访问过才入队
                        vis.add(y)  # 标记为已访问
                        q.append(y)  # 加入队列，下一层扩展
        return -1  # 所有状态搜完仍未到达目标，返回 -1 表示无解
