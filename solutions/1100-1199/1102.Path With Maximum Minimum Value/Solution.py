# 题目：1102. 得分最高的路径（Path With Maximum Minimum Value）
# 思路：把格子按值升序排序后用 pop() 从大到小激活，并查集合并已激活的相邻格子，两端首次连通时的值即答案。
# 时间复杂度：O(mn log(mn))，主要是排序；空间复杂度：O(mn)，并查集与被激活格子的集合。
class Solution:  # LeetCode 约定的题解类
    def maximumMinimumPath(self, grid: List[List[int]]) -> int:  # grid 是权值矩阵
        def find(x: int) -> int:  # 带路径压缩的查找函数
            if p[x] != x:  # 还不是根就继续往上找
                p[x] = find(p[x])  # 递归找到根后回填，压缩路径
            return p[x]  # 返回根节点

        m, n = len(grid), len(grid[0])  # m 行 n 列
        p = list(range(m * n))  # 并查集初始化，二维坐标压平成一维下标
        q = [(v, i, j) for i, row in enumerate(grid) for j, v in enumerate(row)]  # 收集所有 (值, 行, 列)，供之后按值取用
        q.sort()  # 按值升序排序，配合 pop() 就能每次取最大值
        ans = 0  # ans 记录当前已加入的最小值
        dirs = (-1, 0, 1, 0, -1)  # 四方向偏移，pairwise 把它两两配对成 (dx, dy) 四个方向
        vis = set()  # 已被激活的格子集合
        while find(0) != find(m * n - 1):  # 左上角与右下角尚未连通时继续加点
            v, i, j = q.pop()  # 取出当前值最大的格子并激活
            ans = v  # 记录当前加入的值，答案就是两端首次连通那一刻的值
            vis.add((i, j))  # 标记该格子已激活
            for a, b in pairwise(dirs):  # 枚举四个相邻方向
                x, y = i + a, j + b  # 计算相邻格子的坐标
                if (x, y) in vis:  # 邻居已激活，才可能与当前格子连通
                    p[find(i * n + j)] = find(x * n + y)  # 合并当前格子与邻居所在的集合
        return ans  # 返回答案
