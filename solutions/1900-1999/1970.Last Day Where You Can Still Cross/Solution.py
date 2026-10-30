# 题目：1970. 你能穿过矩阵的最后一天（Last Day Where You Can Still Cross）
# 思路：能通过的天数具有单调性（第 k 天能过则更早的日子一定能过），于是对天数二分；判定时把前 k 天被淹的格子当作障碍，用多源 BFS 从第 0 行所有陆地出发，看能否走到第 row-1 行。
# 时间复杂度：O(row * col * log(row * col))，二分 log 次、每次 BFS 扫一遍网格；空间复杂度：O(row * col)，网格与队列。
class Solution:  # LeetCode 约定的题解类
    def latestDayToCross(self, row: int, col: int, cells: List[List[int]]) -> int:  # row/col：网格行数与列数；cells[i] 是第 i+1 天被水淹没的格子
        def check(k: int) -> bool:  # 判定第 k 天是否还能从最上行走通到最下行
            g = [[0] * col for _ in range(row)]  # 新建网格：0 表示陆地，1 表示水或已访问
            for i, j in cells[:k]:  # 取前 k 天被淹的格子
                g[i - 1][j - 1] = 1  # 输入坐标是 1-based，减 1 换成 0-based 并标记为水
            q = [(0, j) for j in range(col) if g[0][j] == 0]  # 多源 BFS 的起点：最一行的全部陆地格子
            for x, y in q:  # 边遍历边 append，列表天然可当队列用（BFS 层序扩展）
                if x == row - 1:  # 已经到达最后一行，说明可以穿过
                    return True  # 提前返回成功
                for a, b in pairwise(dirs):  # pairwise 依次给出相邻对 (dirs[i], dirs[i+1])，即四个方向
                    nx, ny = x + a, y + b  # 相邻格的坐标
                    if 0 <= nx < row and 0 <= ny < col and g[nx][ny] == 0:  # 坐标合法且该格是未访问的陆地
                        q.append((nx, ny))  # 入队等待继续扩展
                        g[nx][ny] = 1  # 入队时立刻标记，防止同一格被重复入队
            return False  # 扩展结束仍未到最下行，说明第 k 天走不通

        n = row * col  # 网格总格子数，也就是可能的最大天数
        l, r = 1, n  # 二分区间 [1, n]
        dirs = (-1, 0, 1, 0, -1)  # 四个方向的紧凑写法：(dirs[i], dirs[i+1]) 即第 i 个方向的偏移
        while l < r:  # 二分查找最后一个「能通过」的天数
            mid = (l + r + 1) >> 1  # 中点向上取整，避免只剩两个元素时死循环
            if check(mid):  # 第 mid 天能通过
                l = mid  # 答案至少是 mid，收缩左边界
            else:  # 第 mid 天过不去
                r = mid - 1  # 答案一定小于 mid
        return l  # 循环结束时 l == r，即最后能穿过的天数
