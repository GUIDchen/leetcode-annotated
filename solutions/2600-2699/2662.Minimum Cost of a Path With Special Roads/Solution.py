# 题目：2662. 前往目标的最小代价（Minimum Cost of a Path With Special Roads）
# 核心思路：在「起点 + 所有特殊道路出口」等关键状态上用堆做 Dijkstra 式松弛，每次用当前点直接走到终点的代价更新答案，再经由每条特殊道路扩展新状态。
# 时间复杂度：O(E log E)，E 为入堆状态数（受特殊道路条数限制）；空间复杂度：O(E)，堆与访问集合。
class Solution:  # LeetCode 约定的题解类
    def minimumCost(  # start：起点；target：终点；specialRoads：每条特殊道路 [x1,y1,x2,y2,cost]
        self, start: List[int], target: List[int], specialRoads: List[List[int]]  # 签名折行的第二部分：起点、终点与特殊道路列表
    ) -> int:  # 返回最小代价（整数）
        def dist(x1: int, y1: int, x2: int, y2: int) -> int:  # 内部函数：曼哈顿距离，即两个坐标之间普通行走的代价
            return abs(x1 - x2) + abs(y1 - y2)  # 横纵坐标差取绝对值相加

        q = [(0, start[0], start[1])]  # 小根堆：元素为（当前累计代价，横坐标，纵坐标），起点代价为 0
        vis = set()  # 访问集合：记录已经确定最优代价的坐标，避免重复扩展
        ans = inf  # 答案初值取正无穷，后面用更小的路径代价不断收紧
        while q:  # 堆非空就继续松弛
            d, x, y = heappop(q)  # 弹出当前累计代价最小的状态
            if (x, y) in vis:  # 该坐标已经处理过（已有不劣的代价）
                continue  # 直接跳过，避免重复扩展
            vis.add((x, y))  # 标记该坐标已处理
            ans = min(ans, d + dist(x, y, *target))  # 从当前点直接走到终点，用这条路径的代价更新答案（*target 解包成两个坐标）
            for x1, y1, x2, y2, cost in specialRoads:  # 枚举每条特殊道路，尝试从当前点绕行
                heappush(q, (d + dist(x, y, x1, y1) + cost, x2, y2))  # 入堆：走到道路入口的代价 + 道路固定花费，出口作为新状态
        return ans
