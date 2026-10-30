# 题目：1036. 逃离大迷宫（Escape a Large Maze）
# 思路：把障碍坐标放进集合，从起点和终点各做一次 DFS；访问格子数超过障碍能围住的上界 k^2/2 就说明冲出了包围圈，两趟都逃出才算成功。
# 时间复杂度：O(k^2)，k 是障碍数量；空间复杂度：O(k^2)，用于两趟 DFS 的 visited 集合。
class Solution:  # LeetCode 约定的题解类
    def isEscapePossible(  # 方法签名：blocked 是障碍坐标，source 是起点，target 是终点
        self, blocked: List[List[int]], source: List[int], target: List[int]  # 参数续行：blocked 障碍列表、source 起点、target 终点
    ) -> bool:  # 返回布尔值，表示能否逃出大迷宫
        def dfs(source: List[int], target: List[int], vis: set) -> bool:  # 内层 DFS：从 source 出发找 target，vis 记录本趟访问过的格子
            vis.add(tuple(source))  # 把当前格子转成元组加入访问集合，避免重复搜索
            if len(vis) > m:  # 访问格子数超过上界 m
                return True  # 说明已冲出障碍围成的包围圈，直接判定逃出
            for a, b in pairwise(dirs):  # pairwise 依次取出 (上, 下) 与 (左, 右) 两组方向偏移
                x, y = source[0] + a, source[1] + b  # 按当前方向偏移算出邻居坐标
                if 0 <= x < n and 0 <= y < n and (x, y) not in s and (x, y) not in vis:  # 邻居在棋盘内、不是障碍、也没有被访问过
                    if [x, y] == target or dfs([x, y], target, vis):  # 邻居正好是终点，或者从邻居继续递归能到达终点
                        return True  # 能到达目标，向上返回 True
            return False  # 四个方向都走不通，返回 False

        s = {(x, y) for x, y in blocked}  # 把 blocked 转成元组集合，便于 O(1) 判断某格是否为障碍
        dirs = (-1, 0, 1, 0, -1)  # 方向数组：相邻两项组成一个方向，共四个方向
        n = 10**6  # 棋盘一边长度为 10^6，合法坐标范围是 [0, n)
        m = len(blocked) ** 2 // 2  # 关键上界：k 个障碍最多围住约 k^2/2 个格子
        return dfs(source, target, set()) and dfs(target, source, set())  # 起点与终点各做一次 DFS，两趟都逃出包围圈才算成功（闭包在调用时才读取 s/dirs/n/m）
