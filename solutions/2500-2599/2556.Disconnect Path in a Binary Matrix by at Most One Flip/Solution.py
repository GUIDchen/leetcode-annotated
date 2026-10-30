# 题目：2556. 二进制矩阵中翻转最多一次使路径不连通（Disconnect Path in a Binary Matrix by at Most One Flip）
# 思路：DFS 把走过的格子置 0。第一次搜索判断连通性并清空一条路径，恢复起点和终点后再搜第二次；若仍连通说明存在两条内部不相交的路径，无法只翻一个格子切断。
# 时间复杂度：O(mn)，两次 DFS 每个格子最多访问一次；空间复杂度：O(mn)，递归栈最坏深度为 m + n。
class Solution:  # LeetCode 约定的题解类
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:  # grid 中 1 表示可走，问能否只翻一个格子就切断所有路径
        def dfs(i, j):  # 递归找一条到终点的路径，走过的格子置 0 标记为已访问
            if i >= m or j >= n or grid[i][j] == 0:  # 越界或格子不可走（被访问过的格子也是 0）
                return False  # 这条路走不通
            grid[i][j] = 0  # 标记当前格子已访问，防止来回绕圈
            if i == m - 1 and j == n - 1:  # 到达终点
                return True  # 说明找到了路径
            return dfs(i + 1, j) or dfs(i, j + 1)  # 只能往下或往右走，任一方向能到终点即可

        m, n = len(grid), len(grid[0])  # 行数和列数；dfs 内部引用它们，调用时已经赋值
        a = dfs(0, 0)  # 第一次搜索：判断起点到终点是否本来就连通
        grid[0][0] = grid[-1][-1] = 1  # DFS 会把起点和终点也置 0，先恢复才能再搜一次
        b = dfs(0, 0)  # 第二次搜索：第一次的路径已被清空，若仍连通说明还有第二条不相交路径
        return not (a and b)  # 两次都连通就无法一刀切断，返回 False
