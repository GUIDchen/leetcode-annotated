# 题目：1765. 地图中的最高点（Map of Highest Peak）
# 思路：多源 BFS。把所有水域格子当作源点入队并令其高度为 0，再一层层向外扩散，每扩散一层高度加 1；这样相邻格子高度差不超过 1，且高度尽可能大。
# 时间复杂度：O(m * n)，每个格子最多入队一次；空间复杂度：O(m * n)，答案矩阵与 BFS 队列。
class Solution:  # LeetCode 约定的题解类
    def highestPeak(self, isWater: List[List[int]]) -> List[List[int]]:  # isWater：1 表示水域、0 表示陆地；返回每个格子的最高高度
        m, n = len(isWater), len(isWater[0])  # m 是行数，n 是列数
        ans = [[-1] * n for _ in range(m)]  # 答案矩阵，先全部填 -1 表示高度尚未确定
        q = deque()  # 双端队列，存放已经确定高度的格子坐标
        for i, row in enumerate(isWater):  # 遍历每一行，同时拿到行号 i 与该行 row
            for j, v in enumerate(row):  # 遍历该行的每一列，j 是列号，v 是格子值
                if v:  # v 为真（值为 1）说明该格子是水域
                    q.append((i, j))  # 水域坐标入队，作为多源 BFS 的源点
                    ans[i][j] = 0  # 水域高度固定为 0
        while q:  # 队列非空就继续按层扩散
            i, j = q.popleft()  # 取出队首坐标（i 行 j 列）
            for a, b in pairwise((-1, 0, 1, 0, -1)):  # pairwise 把相邻两项两两配对，得到四个方向向量 (-1,0)、(0,1)、(1,0)、(0,-1)
                x, y = i + a, j + b  # 算出相邻格子的坐标 x、y
                if 0 <= x < m and 0 <= y < n and ans[x][y] == -1:  # 越界或高度已确定（不等于 -1）就跳过
                    ans[x][y] = ans[i][j] + 1  # 相邻格子高度 = 当前高度 + 1，保证差值不超过 1 且尽量大
                    q.append((x, y))  # 新确定的格子入队，继续扩散
        return ans  # 返回每个格子的最高高度
