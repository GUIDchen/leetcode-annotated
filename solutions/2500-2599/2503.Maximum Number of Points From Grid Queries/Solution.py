# 题目：2503. 矩阵查询可获得的最大分数（Maximum Number of Points From Grid Queries）
# 思路：把查询按值升序排序，用小根堆从 (0,0) 开始按格子值递增“解锁”格子，堆顶值小于当前查询值就出堆计分；查询递增，cnt 只增不减。
# 时间复杂度：O(m·n log(m·n) + k log k)，每个格子最多入堆出堆一次；空间复杂度：O(m·n + k)。
class Solution:  # LeetCode 约定的题解类
    def maxPoints(self, grid: List[List[int]], queries: List[int]) -> List[int]:  # grid 是矩阵，queries 是查询数组；返回每个查询对应的最大分数
        m, n = len(grid), len(grid[0])  # m 行 n 列
        qs = sorted((v, i) for i, v in enumerate(queries))  # 把 (查询值, 原下标) 打包后按查询值升序排序
        ans = [0] * len(qs)  # ans 按查询的原始下标保存答案
        q = [(grid[0][0], 0, 0)]  # 小根堆：元素为 (格子值, 行, 列)，按格子值从小到大出堆
        cnt = 0  # cnt：当前已到达的格子数，也就是该查询的分数
        vis = [[False] * n for _ in range(m)]  # vis 标记格子是否已经入堆，防止重复入堆
        vis[0][0] = True  # 起点 (0, 0) 标记为已访问
        for v, k in qs:  # 按查询值从小到大依次处理
            while q and q[0][0] < v:  # 堆顶格子的值严格小于 v 时，该格子才可以被走到
                _, i, j = heappop(q)  # 弹出堆顶，取出其行列坐标
                cnt += 1  # 该格子计入分数
                for a, b in pairwise((-1, 0, 1, 0, -1)):  # 枚举四个相邻方向（相邻两项组成一个方向）
                    x, y = i + a, j + b  # 算出相邻格子的行列坐标
                    if 0 <= x < m and 0 <= y < n and not vis[x][y]:  # 坐标合法且未被访问过
                        heappush(q, (grid[x][y], x, y))  # 先标记再入堆，避免同一格子被重复加入
                        vis[x][y] = True  # 把相邻格子加入小根堆，等待后续查询处理
            ans[k] = cnt  # 把当前累计分数作为该查询的答案
        return ans  # 返回按原始下标排列的答案
