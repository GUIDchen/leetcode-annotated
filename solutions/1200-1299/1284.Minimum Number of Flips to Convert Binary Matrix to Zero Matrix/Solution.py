# 题目：1284. 转化为全零矩阵的最少反转次数（Minimum Number of Flips to Convert Binary Matrix to Zero Matrix）
# 思路：把整个矩阵压成一个二进制整数作为状态，从初始状态做 BFS，每次翻转某格及其上下左右，首次到达 0 即为最少次数。
# 时间复杂度：O(2^(mn)·mn)，状态数不超过 2^(mn)，每个状态尝试 mn 种翻转；空间复杂度：O(2^(mn))。
class Solution:  # LeetCode 约定的题解类
    def minFlips(self, mat: List[List[int]]) -> int:  # mat 是 0/1 矩阵，返回把它变成全零矩阵的最少翻转次数
        m, n = len(mat), len(mat[0])  # m 为行数，n 为列数
        state = sum(1 << (i * n + j) for i in range(m) for j in range(n) if mat[i][j])  # 用生成器求和把二维矩阵压成一个整数：第 (i, j) 格对应第 i * n + j 位，值为 1 时计入
        q = deque([state])  # BFS 队列，从初始状态开始扩展
        vis = {state}  # 已访问状态集合，防止同一状态被重复处理
        ans = 0  # ans 记录已翻转的次数，也就是 BFS 当前层数
        dirs = [0, -1, 0, 1, 0, 0]  # 五个翻转位置的方向偏移：中心 (0,0) 加上下左右 (0,-1) (-1,0) (0,1) (1,0)
        while q:  # 队列非空就继续按层扩展
            for _ in range(len(q)):  # 只处理当前层的这些状态，层数即翻转次数
                state = q.popleft()  # 取出队首状态
                if state == 0:  # 状态为 0 说明已是全零矩阵
                    return ans  # 当前层数就是最少翻转次数，直接返回
                for i in range(m):  # 枚举本次要翻转的格子所在行
                    for j in range(n):  # 枚举本次要翻转的格子所在列
                        nxt = state  # 复制当前状态，在副本上做一次翻转
                        for k in range(5):  # 依次翻转中心格及其上下左右共 5 个位置
                            x, y = i + dirs[k], j + dirs[k + 1]  # x、y 是被翻转位置的坐标
                            if not 0 <= x < m or not 0 <= y < n:  # 该位置越界则跳过，不做翻转
                                continue  # 越界时进入下一次循环
                            if nxt & (1 << (x * n + y)):  # 该位当前为 1
                                nxt -= 1 << (x * n + y)  # 把这一位清零，即完成 1 → 0 的翻转
                            else:  # 否则该位为 0
                                nxt |= 1 << (x * n + y)  # 把这一位置 1，即完成 0 → 1 的翻转
                        if nxt not in vis:  # 这是从未出现过的新状态
                            vis.add(nxt)  # 记录已访问，避免重复入队
                            q.append(nxt)  # 加入队列，留待下一层继续扩展
            ans += 1  # 本层全部处理完，翻转次数加一，进入下一层
        return -1  # 队列耗尽仍无法变成全零矩阵，返回 -1
