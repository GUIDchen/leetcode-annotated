# 题目：3235. 判断矩形的两个角落是否可达（Check if the Rectangle Corner Is Reachable）
# 思路：圆是一堵堵墙，若相交的圆从矩形的「左边或上边」连成一条链通到「右边或下边」，就把两个角落隔开；用 DFS 判断这种阻断链是否存在。
# 时间复杂度：O(n^2)，每个圆只搜一次、每次枚举 n 个邻居；空间复杂度：O(n)，vis 数组与递归栈。
class Solution:  # LeetCode 约定的题解类
    def canReachCorner(  # 起点角 (0,0) 与终点角 (xCorner, yCorner)，circles 里每个元素是 [圆心 x, 圆心 y, 半径]
        self, xCorner: int, yCorner: int, circles: List[List[int]]  # self 之后的三个形参：两个角点坐标与圆列表
    ) -> bool:  # 返回 bool：True 表示两个角落互相可达
        # 内层继续用闭包函数，方便复用到两处角点判断
        def in_circle(x: int, y: int, cx: int, cy: int, r: int) -> int:  # 判断点 (x, y) 是否在圆 (cx, cy, r) 内（含边界）；返回类型标成 int 沿用源码写法
            return (x - cx) ** 2 + (y - cy) ** 2 <= r**2  # 用平方距离和 r^2 比较，避免开方带来的精度问题

        def cross_left_top(cx: int, cy: int, r: int) -> bool:  # 判断圆是否与矩形的「左边或上边」相交，这两条边是起点角的邻边
            a = abs(cx) <= r and 0 <= cy <= yCorner  # a：圆心到左边界 x=0 的距离不超过 r，且交点的 y 落在 [0, yCorner] 内
            b = abs(cy - yCorner) <= r and 0 <= cx <= xCorner  # b：圆心到上边界 y=yCorner 的距离不超过 r，且交点的 x 落在 [0, xCorner] 内
            return a or b  # 与左边或上边任一相交，就切住了起点一侧

        def cross_right_bottom(cx: int, cy: int, r: int) -> bool:  # 判断圆是否与矩形的「右边或下边」相交，这两条边是终点角的邻边
            a = abs(cx - xCorner) <= r and 0 <= cy <= yCorner  # a：圆心到右边界 x=xCorner 的距离不超过 r，且交点的 y 落在 [0, yCorner] 内
            b = abs(cy) <= r and 0 <= cx <= xCorner  # b：圆心到下边界 y=0 的距离不超过 r，且交点的 x 落在 [0, xCorner] 内
            return a or b  # 与右边或下边任一相交，就切住了终点一侧

        # 递归函数，返回 True 表示找到一条通向右下边界的阻断链
        def dfs(i: int) -> bool:  # 从第 i 个圆出发做深度优先搜索，看能否沿相交的圆连到右边或下边
            x1, y1, r1 = circles[i]  # 解包当前圆的圆心与半径
            if cross_right_bottom(x1, y1, r1):  # 当前圆已经碰到右边或下边，阻断链在此打通
                return True  # 返回 True 表示这条链成立
            vis[i] = True  # 标记该圆已访问，防止在相交环上重复搜索
            for j, (x2, y2, r2) in enumerate(circles):  # 枚举所有圆，j 是下标，(x2, y2, r2) 是邻居候选
                if vis[j] or not ((x1 - x2) ** 2 + (y1 - y2) ** 2 <= (r1 + r2) ** 2):  # vis[j] 为真说明搜过；圆心距大于半径和说明两圆相离，两种情况都跳过
                    continue  # 换下一个邻居
                if (  # 还需保证只沿「朝右下推进」的圆链搜索，避免绕过角点时几何误判
                    (x1 * r2 + x2 * r1 < (r1 + r2) * xCorner)  # 条件一：加权圆心 x 坐标小于 (r1+r2)*xCorner，保证接触点在这条边之内
                    and (y1 * r2 + y2 * r1 < (r1 + r2) * yCorner)  # 条件二：加权圆心 y 坐标同样要在 (r1+r2)*yCorner 之内
                    and dfs(j)  # 条件三：从邻居 j 出发还能继续走到右下边界
                ):  # 三个条件都成立才进入分支
                    return True  # 邻居也能连通终点侧，整条链成立
            return False  # 所有邻居都试过仍未连通，返回 False

        vis = [False] * len(circles)  # 一开始所有圆都未访问，vis[i] 对应第 i 个圆
        for i, (x, y, r) in enumerate(circles):  # 枚举每个圆，i 是下标，(x, y, r) 是圆心与半径
            if in_circle(0, 0, x, y, r) or in_circle(xCorner, yCorner, x, y, r):  # 起点角或终点角被某个圆盖住时，两个角落直接不可达
                return False  # 角点被覆盖，返回 False
            if (not vis[i]) and cross_left_top(x, y, r) and dfs(i):  # 圆心碰到左边/上边，且从它 DFS 能连到右边/下边
                return False  # 存在完整阻断链，起点到不了终点
        return True  # 没有任何阻断链，起点可以到达终点
