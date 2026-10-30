# 题目：1810. 隐藏网格下的最小消耗路径（Minimum Path Cost in a Hidden Grid）
# 思路：先用 DFS 借 GridMaster 探明整张地图并记录每格花费，再在已知地图上跑 Dijkstra，求起点到终点的最小花费。
# 时间复杂度：O(V + E log V)，V 为可达格子数；空间复杂度：O(V)，用于存地图与距离表。
# """
# This is GridMaster's API interface.
# You should not implement it, or speculate about its implementation
# """
# class GridMaster(object):
#    def canMove(self, direction: str) -> bool:
#
#
#    def move(self, direction: str) -> int:
#
#
#    def isTarget(self) -> bool:
#
#


class Solution(object):  # LeetCode 约定的题解类（这里用 object 基类，判题器不依赖继承）
    def findShortestPath(self, master: "GridMaster") -> int:  # master：黑盒机器人，提供 canMove / move / isTarget 三个方法
        def dfs(x: int, y: int) -> None:  # 内部辅助函数：深搜把机器人能到达的格子及其花费记录下来
            nonlocal target  # 声明要修改外层作用域里的 target，而不是新建局部变量
            if master.isTarget():  # 当前格就是终点
                target = (x, y)  # 记录终点坐标
            for k in range(4):  # 依次尝试四个方向
                dx, dy = dirs[k], dirs[k + 1]  # 相邻两项组成该方向的增量 (dx, dy)
                nx, ny = x + dx, y + dy  # 相邻格的坐标
                if (  # 判断能否走到相邻格：坐标合法、没探索过、机器人也允许
                    0 <= nx < m  # 行坐标在范围内
                    and 0 <= ny < n  # 列坐标在范围内
                    and g[nx][ny] == -1  # 该格尚未探索过
                    and master.canMove(s[k])  # 机器人允许朝这个方向移动
                ):  # 条件全部满足，进入下方处理
                    g[nx][ny] = master.move(s[k])  # 真正走过去，并记录该格的花费
                    dfs(nx, ny)  # 从新格子继续深搜
                    master.move(s[(k + 2) % 4])  # 回溯：沿反方向（索引加 2 再取模）走回原格

        dirs = (-1, 0, 1, 0, -1)  # 方向数组：相邻两项组成 (dx, dy)，依次是上、右、下、左
        s = "URDL"  # 与 dirs 一一对应的方向字母
        m = n = 200  # 地图边长上限，200 x 200 足够覆盖题目数据范围
        g = [[-1] * n for _ in range(m)]  # 地图花费表，-1 表示未探索或不可通行
        target = (-1, -1)  # 终点坐标，(-1, -1) 表示还没找到
        sx = sy = 100  # 起点放在地图正中间，四面都有足够的探索空间
        dfs(sx, sy)  # 从起点出发探明整张可达地图
        if target == (-1, -1):  # 始终没找到终点
            return -1  # 不可达，按题意返回 -1
        pq = [(0, sx, sy)]  # 小根堆，元素为 (当前累计花费, x, y)
        dist = [[inf] * n for _ in range(m)]  # 最短路距离表，初值全为无穷大
        dist[sx][sy] = 0  # 起点到自身距离为 0
        while pq:  # Dijkstra 主循环
            w, x, y = heappop(pq)  # 弹出当前花费最小的状态
            if (x, y) == target:  # 第一次弹出终点，即为最短路
                return w  # 返回最小花费
            for dx, dy in pairwise(dirs):  # 把 dirs 拆成相邻的 (dx, dy) 对来遍历四个方向
                nx, ny = x + dx, y + dy  # 相邻格的坐标
                if (  # 只有坐标合法、该格可走、且能带来更短距离才松弛
                    0 <= nx < m  # 行坐标在范围内
                    and 0 <= ny < n  # 列坐标在范围内
                    and g[nx][ny] != -1  # 该格已探索且可通行
                    and w + g[nx][ny] < dist[nx][ny]  # 新路径比已知方案更短
                ):  # 条件全部满足，进入下方更新
                    dist[nx][ny] = w + g[nx][ny]  # 更新最短距离
                    heappush(pq, (dist[nx][ny], nx, ny))  # 把更优状态压入堆，供后续继续松弛
        return -1  # 堆空说明终点不可达
