# 3459. 最长 V 形对角线段的长度 / Length of Longest V-Shaped Diagonal Segment
# 核心思路：从每个值为 1 的格子出发，沿 4 条对角线方向做记忆化深搜，允许在途中拐弯一次，取能走出的最长 V 形段。
# 复杂度：时间复杂度 O(m·n)，空间复杂度 O(m·n)。
class Solution:  # 题解类
    def lenOfVDiagonal(self, grid: List[List[int]]) -> int:  # 求最长的 V 形对角线段的长度
        @cache
        def dfs(i: int, j: int, k: int, cnt: int) -> int:  # 记忆化深搜：cnt 为 1 表示还能拐弯
            x, y = i + dirs[k], j + dirs[k + 1]  # 按方向 k 计算下一个格子的坐标
            target = 2 if grid[i][j] == 1 else (2 - grid[i][j])  # V 形段要求的下一格数值：1→2、2→0、0→2
            if not 0 <= x < m or not 0 <= y < n or grid[x][y] != target:  # 越界或数值不满足要求
                return 0  # 无法继续延伸
            res = dfs(x, y, k, cnt)  # 继续沿原方向前进
            if cnt > 0:  # 还有拐弯机会
                res = max(res, dfs(x, y, (k + 1) % 4, 0))  # 也可以在此处拐弯，之后不再能拐弯
            return 1 + res  # 当前格自身贡献 1

        m, n = len(grid), len(grid[0])  # 网格行数与列数，dfs 内会引用这两个闭包变量
        dirs = (1, 1, -1, -1, 1)  # 四个对角线方向的增量，首尾相接便于用 (k+1)%4 拐弯
        ans = 0  # 答案
        for i, row in enumerate(grid):  # 枚举起点行
            for j, x in enumerate(row):  # 枚举起点列
                if x == 1:  # V 形段必须以 1 开头
                    for k in range(4):  # 枚举四个出发方向
                        ans = max(ans, dfs(i, j, k, 1) + 1)  # 加上起点自身后更新答案
        return ans  # 返回最长 V 形对角线段长度
