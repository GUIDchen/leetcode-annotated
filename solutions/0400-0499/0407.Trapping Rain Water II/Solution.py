# 题目：407. 接雨水 II（Trapping Rain Water II）
# 思路：用小根堆维护木桶边界，每次弹出水面最低的边界格，向四邻域扩展并结算存水，新水位取两者较大值。
# 时间复杂度：O(mn log(mn))，每格入堆出堆各一次；空间复杂度：O(mn)，访问标记矩阵加堆。
class Solution:  # LeetCode 约定的题解类
    def trapRainWater(self, heightMap: List[List[int]]) -> int:  # heightMap 是每格柱子的高度，返回能接住的雨水总量
        m, n = len(heightMap), len(heightMap[0])  # 矩阵的行数 m 与列数 n
        vis = [[False] * n for _ in range(m)]  # 访问标记矩阵，防止同一格重复入堆
        pq = []  # 用列表充当小根堆（heappush/heappop 由判题环境提供）
        for i in range(m):  # 先遍历所有行
            for j in range(n):  # 再遍历所有列
                if i == 0 or i == m - 1 or j == 0 or j == n - 1:  # 判断是否落在最外圈（只有外圈能作为初始边界）
                    heappush(pq, (heightMap[i][j], i, j))  # 外圈格入堆，水面高度先取其自身高度
                    vis[i][j] = True  # 标记外圈已访问
        ans = 0  # 累计接住的雨水体积
        dirs = (-1, 0, 1, 0, -1)  # 四邻域方向数组，成对取用即上、右、下、左
        while pq:  # 边界非空就继续向内扩展
            h, i, j = heappop(pq)  # 弹出当前水面最低的边界格
            for a, b in pairwise(dirs):  # 相邻方向成对遍历（pairwise 由判题环境提供，无需 import）
                x, y = i + a, j + b  # 相邻格坐标
                if x >= 0 and x < m and y >= 0 and y < n and not vis[x][y]:  # 坐标合法且尚未访问才处理
                    ans += max(0, h - heightMap[x][y])  # 邻格更低时差值即可存的水量
                    vis[x][y] = True  # 标记邻格已访问
                    heappush(pq, (max(h, heightMap[x][y]), x, y))  # 新水面高度取自身高度与 h 的较大者，入堆继续向外扩展
        return ans  # 返回接住的雨水总量
