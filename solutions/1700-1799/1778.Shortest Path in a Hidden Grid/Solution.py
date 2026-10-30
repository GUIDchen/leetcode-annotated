# 题目：1778. 未知网格中的最短路径（Shortest Path in a Hidden Grid）
# 思路：先用 DFS 在隐藏网格上探索，记录所有可走格子与目标位置；再用 BFS 从起点出发求到目标的最短步数。
# 时间复杂度：O(S)，S 为探索到的可达格子数；空间复杂度：O(S) 用于存访问集合与队列。
# """
# This is GridMaster's API interface.
# You should not implement it, or speculate about its implementation
# """
# class GridMaster(object):
#    def canMove(self, direction: str) -> bool:
#
#
#    def move(self, direction: str) -> bool:
#
#
#    def isTarget(self) -> None:
#
#


class Solution(object):  # LeetCode 约定的题解类
    def findShortestPath(self, master: "GridMaster") -> int:  # master：隐藏网格的交互接口
        def dfs(i: int, j: int):  # 内部 DFS：探索网格并记录目标位置，i、j 是当前坐标
            if master.isTarget():  # 当前格子就是目标
                nonlocal target  # 声明要修改外层作用域中的 target
                target = (i, j)  # 记录目标坐标
                return  # 找到目标就结束这条分支
            for k, c in enumerate(s):  # 依次尝试四个方向
                x, y = i + dirs[k], j + dirs[k + 1]  # 邻居坐标
                if master.canMove(c) and (x, y) not in vis:  # 能走过去且没有访问过
                    vis.add((x, y))  # 标记已访问
                    master.move(c)  # 移动到邻居格子
                    dfs(x, y)  # 继续深入探索
                    master.move(s[(k + 2) % 4])  # 回溯：沿反方向走回原格子

        s = "URDL"  # 四个方向字符：上、右、下、左
        dirs = (-1, 0, 1, 0, -1)  # 与方向字符对应的坐标增量
        target = None  # 目标坐标，None 表示尚未找到
        vis = set()  # 已访问（可通行）格子集合
        dfs(0, 0)  # 从起点 (0,0) 开始探索
        if target is None:  # 没有可达的目标
            return -1  # 返回 -1
        vis.discard((0, 0))  # 移除起点，之后把集合当作 BFS 的“未访问”标记
        q = deque([(0, 0)])  # BFS 队列，起点入队
        ans = -1  # 已走步数，初始 -1，进入循环后先加一
        while q:  # 队列非空就继续
            ans += 1  # 进入新的一层，步数加一
            for _ in range(len(q)):  # 只处理当前这一层的格子
                i, j = q.popleft()  # 取出队首坐标
                if (i, j) == target:  # 到达目标
                    return ans  # 返回当前步数，即最短距离
                for a, b in pairwise(dirs):  # 相邻元素两两配对，得到四个方向增量
                    x, y = i + a, j + b  # 邻居坐标
                    if (x, y) in vis:  # 邻居可通行且尚未访问
                        vis.remove((x, y))  # 标记为已访问
                        q.append((x, y))  # 邻居入队
        return -1  # 队列空了仍未到达目标
