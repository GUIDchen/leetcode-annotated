# 题目：2850. 将石头分散到网格图的最少移动次数（Minimum Moves to Spread Stones Over Grid）
# 核心思路：把 3x3 的石头分布转成不可变元组作为状态做按层 BFS，每步把一块石头移到相邻且石头数少于 2 的格子。
# 时间复杂度：O(状态数 * 9 * 4)，3x3 且石头总数不超过 9，状态数很小；空间复杂度：O(状态数)。
class Solution:  # LeetCode 约定的题解类
    def minimumMoves(self, grid: List[List[int]]) -> int:  # grid 是 3x3 网格，元素表示该格的石头数
        q = deque([tuple(tuple(row) for row in grid)])  # 用两层元组表示不可变状态并入队，元组可哈希才能放进 vis
        vis = set(q)  # 起点状态标记为已访问
        ans = 0  # ans 表示已经移动的步数
        dirs = (-1, 0, 1, 0, -1)  # 方向数组，相邻两项配成一个方向向量
        while 1:  # 不断向外扩展，直到找到目标状态
            for _ in range(len(q)):  # 只处理当前层（range(len(q)) 在进入循环时求值）
                cur = q.popleft()  # 取出队首状态
                if all(x for row in cur for x in row):  # 每个格子都非零，说明石头已均分，当前 ans 即最少步数
                    return ans  # 返回答案
                for i in range(3):  # 枚举行
                    for j in range(3):  # 枚举列
                        if cur[i][j] > 1:  # 只有石头数大于 1 的格子才有石头可搬
                            for a, b in pairwise(dirs):  # 相邻两项 (a, b) 构成一个方向向量
                                x, y = i + a, j + b  # 计算目标格坐标
                                if 0 <= x < 3 and 0 <= y < 3 and cur[x][y] < 2:  # 目标格在界内且石头数小于 2 才可以接收
                                    nxt = [list(row) for row in cur]  # 复制成可变的列表网格，便于修改
                                    nxt[i][j] -= 1  # 源格搬走一块石头
                                    nxt[x][y] += 1  # 目标格增加一块石头
                                    nxt = tuple(tuple(row) for row in nxt)  # 重新转成不可变元组作为新状态
                                    if nxt not in vis:  # 状态没出现过才继续扩展
                                        vis.add(nxt)  # 标记为已访问
                                        q.append(nxt)  # 入队，留待下一层处理
            ans += 1  # 本层处理完毕，步数加一
