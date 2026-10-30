# 题目：909. 蛇梯棋（Snakes and Ladders）
# 核心思路：把格子编号 1..n² 当图的节点做 BFS，每步最多走 6 格，遇到蛇或梯子就跳到目标格，层数即最少步数。
# 时间复杂度：O(n²)，每个格子最多入队一次；空间复杂度：O(n²)，访问集合与队列。
class Solution:  # LeetCode 约定的题解类
    def snakesAndLadders(self, board: List[List[int]]) -> int:  # board：蛇梯棋盘（-1 表示普通格，其余表示跳转目标）；返回最少步数
        n = len(board)  # 棋盘边长，格子编号为 1..n*n
        q = deque([1])  # BFS 队列，从起点 1 号格开始
        vis = {1}  # 已访问集合，避免同一个格子重复入队
        ans = 0  # 当前 BFS 层数，也就是最少掷骰次数
        m = n * n  # 终点编号，也是掷骰子不能越过的上界
        while q:  # 队列非空就继续扩展
            for _ in range(len(q)):  # 逐层处理，保证同层节点步数相同
                x = q.popleft()  # 取出队首格子
                if x == m:  # 到达终点
                    return ans  # 返回当前层数作为最少步数
                for y in range(x + 1, min(x + 6, m) + 1):  # 掷骰子走 1..6 步，且不能越过终点
                    i, j = divmod(y - 1, n)  # 把编号换算成行列（行从下往上数）
                    if i & 1:  # 奇数行的编号方向与偶数行相反
                        j = n - j - 1  # 反转列下标，还原蛇形编号的真实位置
                    i = n - i - 1  # 行号在上方，需要翻转成从上往下数的下标
                    z = y if board[i][j] == -1 else board[i][j]  # 普通格停在 y，蛇或梯子则跳到目标格
                    if z not in vis:  # 目标格还没访问过
                        vis.add(z)  # 标记为已访问
                        q.append(z)  # 加入队列，等待下一层扩展
            ans += 1  # 一层处理完，步数加一
        return -1  # 队列耗尽仍未到达终点，返回 -1
