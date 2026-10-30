# 3905. 多源图像渲染（Multi Source Flood Fill）
# 思路：把所有源点作为第 0 层队列，逐层向相邻的空白格扩散颜色；同一层多个源点染同一格时取颜色较大者。
# 复杂度：时间复杂度 O(n*m)，每个格子最多被染色一次；空间复杂度 O(n*m)。
class Solution:  # LeetCode 约定的题解类
    def colorGrid(self, n: int, m: int, sources: list[list[int]]) -> list[list[int]]:  # n,m：网格尺寸；sources：多源染色点 [行,列,颜色]
        ans = [[0] * m for _ in range(n)]  # 结果网格，0 表示尚未染色
        q = sources  # 直接拿源点列表当作第 0 轮队列
        dirs = (-1, 0, 1, 0, -1)  # 四方向偏移量，相邻两项组成一个方向向量
        for r, c, color in q:  # 先把所有源点自身染色
            ans[r][c] = color  # 源点的颜色
        while q:  # 逐层扩散，直到没有新格子
            vis = defaultdict(int)  # 本轮每个待染色格子收到的最大颜色
            for r, c, color in q:  # 遍历上一轮的所有格子
                for a, b in pairwise(dirs):  # pairwise 取相邻两项组成一个方向向量
                    x, y = r + a, c + b  # 相邻格子的坐标
                    if not 0 <= x < n or not 0 <= y < m or ans[x][y]:  # 越界或已经被染色的格子跳过
                        continue  # 跳过该方向
                    vis[(x, y)] = max(vis[(x, y)], color)  # 同一格子被多个源点覆盖时取较大颜色
            q.clear()  # 清空队列，准备装入下一轮
            for (x, y), color in vis.items():  # 把本轮确定颜色的格子正式染色
                q.append((x, y, color))  # 新染色的格子作为下一轮扩散起点
                ans[x][y] = color  # 写入最终颜色
        return ans  # 返回染色后的网格
