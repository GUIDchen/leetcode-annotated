# 3565. 顺序网格路径覆盖 / Sequential Grid Path Cover
# 核心思路：回溯搜索。从每个值为 0 或 1 的格子出发 DFS 走出一条覆盖全部 m*n 个格子的路径，用位掩码标记已访问格子，并保证经过带编号的格子时编号必须逐个递增。
# 复杂度：时间最坏 O(4^(m*n))（指数级搜索，靠剪枝收敛），空间 O(m*n)
class Solution:  # 定义解题类
    def findPath(self, grid: List[List[int]], k: int) -> List[List[int]]:  # 返回按编号顺序覆盖整个网格的路径
        def f(i: int, j: int) -> int:  # 把二维坐标压缩成一维编号
            return i * n + j  # 行优先编号，用作位掩码的下标

        def dfs(i: int, j: int, v: int):  # 从 (i, j) 出发继续搜索，v 表示下一个应当出现的编号
            nonlocal st  # 声明后续要修改外层的访问标记
            path.append([i, j])  # 把当前格子加入路径
            if len(path) == m * n:  # 已经覆盖所有格子
                return True  # 找到合法路径，直接返回成功
            st |= 1 << f(i, j)  # 标记当前格子已访问
            if grid[i][j] == v:  # 当前格子带有编号
                v += 1  # 下一个格子需要编号加一
            for a, b in pairwise(dirs):  # 把方向数组两两配对枚举四个方向
                x, y = i + a, j + b  # 计算相邻格子的坐标
                if (  # 判断相邻格子是否可以走
                    0 <= x < m  # 行坐标在界内
                    and 0 <= y < n  # 列坐标在界内
                    and (st & 1 << f(x, y)) == 0  # 该格子尚未访问
                    and grid[x][y] in (0, v)  # 下一格必须为空或正好是所需编号
                ):  # 结束可走条件
                    if dfs(x, y, v):  # 递归继续搜索
                        return True  # 子树成功则整体成功
            path.pop()  # 回溯，撤销当前格子
            st ^= 1 << f(i, j)  # 清除已访问标记
            return False  # 四个方向都走不通，返回失败

        m, n = len(grid), len(grid[0])  # 网格的行数与列数
        st = 0  # 位掩码记录路径上已访问的格子
        path = []  # 记录当前路径经过的格子坐标
        dirs = (-1, 0, 1, 0, -1)  # 四个方向的增量，两两配对使用
        for i in range(m):  # 枚举行
            for j in range(n):  # 枚举列
                if grid[i][j] in (0, 1):  # 只能从空格或编号 1 出发
                    if dfs(i, j, 1):  # 从该格开始尝试搜索
                        return path  # 成功则返回记录的路径
                    path.clear()  # 失败后清空路径
                    st = 0  # 并清空访问标记
        return []  # 找不到合法路径时返回空列表
