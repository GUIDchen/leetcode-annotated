# 题目：1197. 进击的骑士（Minimum Knight Moves）
# 思路：从 (0,0) 出发做 BFS，八个方向逐层扩展，按层计数，第一次遇到目标时的层数即最少步数。
# 时间复杂度：O(V + E)，V、E 为可达点与边数；空间复杂度：O(V)，访问集合最多存 V 个坐标。
class Solution:  # LeetCode 约定的题解类
    def minKnightMoves(self, x: int, y: int) -> int:  # x、y 是目标坐标，返回从 (0,0) 到 (x,y) 的最少步数
        q = deque([(0, 0)])  # BFS 双端队列，初始只有起点 (0,0)
        ans = 0  # ans 记录已走的步数（BFS 的层数）
        vis = {(0, 0)}  # 集合记录访问过的坐标，防止重复入队
        dirs = ((-2, 1), (-1, 2), (1, 2), (2, 1), (2, -1), (1, -2), (-1, -2), (-2, -1))  # 骑士的八种 L 形走法
        while q:  # 队列非空就继续搜索
            for _ in range(len(q)):  # 按当前层长度遍历，保证同一层的点步数相同
                i, j = q.popleft()  # 从队首取出一个坐标
                if (i, j) == (x, y):  # 判断是否已经到达目标点
                    return ans  # 返回当前层数，即最少步数
                for a, b in dirs:  # 枚举八个方向
                    c, d = i + a, j + b  # c、d 是走一步之后的新坐标
                    if (c, d) not in vis:  # 新坐标没访问过才扩展
                        vis.add((c, d))  # 标记为已访问
                        q.append((c, d))  # 新坐标入队，留待下一层处理
            ans += 1  # 本层处理完，步数加一
        return -1  # 理论上不会到这里；返回 -1 表示不可达
