# 题目：2123. 使矩阵中的 1 互不相邻的最小操作数（Minimum Operations to Remove Adjacent Ones in Matrix）
# 核心思路：按 (i+j) 奇偶把 1 染成二分图两侧，相邻的 1 连边；最少删除数 = 该二分图的最大匹配数。
# 时间复杂度：O(V*E)，匈牙利算法每个左侧点 DFS 一次；空间复杂度：O(V + E)，邻接表、匹配数组与访问集合。
class Solution:  # LeetCode 约定的题解类
    def minimumOperations(self, grid: List[List[int]]) -> int:  # grid：只含 0/1 的矩阵
        def find(i: int) -> int:  # 匈牙利算法：尝试给左侧点 i 找一条增广路（闭包引用外层 g/vis/match）
            for j in g[i]:  # 遍历 i 的所有邻接右侧点
                if j not in vis:  # 本轮还没访问过 j 才继续深搜
                    vis.add(j)  # 标记 j 已访问
                    if match[j] == -1 or find(match[j]):  # j 空闲，或者 j 的原配可以改配到别处
                        match[j] = i  # 把右侧点 j 改配给左侧点 i
                        return 1  # 增广成功，匹配数可以加一
            return 0  # 所有邻点都试过仍无法增广，返回失败

        g = defaultdict(list)  # 左侧点编号 → 它能到达的右侧点（邻接表；默认空列表省去判空）
        m, n = len(grid), len(grid[0])  # m 是行数，n 是列数
        for i, row in enumerate(grid):  # 枚举行，row 是这一行的列表
            for j, v in enumerate(row):  # 枚举列，v 是该格子的值
                if (i + j) % 2 and v:  # 只把 (i+j) 为奇数且值为 1 的格子当作二分图左侧
                    x = i * n + j  # 把二维坐标压成一维编号，方便当作点下标
                    if i < m - 1 and grid[i + 1][j]:  # 下方相邻格也是 1，说明存在一条边
                        g[x].append(x + n)  # 一维编号下「下一行同一列」正好是 x + n
                    if i and grid[i - 1][j]:  # 上方相邻格也是 1
                        g[x].append(x - n)  # 「上一行同一列」是 x - n
                    if j < n - 1 and grid[i][j + 1]:  # 右方相邻格也是 1
                        g[x].append(x + 1)  # 「同一行右一列」是 x + 1
                    if j and grid[i][j - 1]:  # 左方相邻格也是 1
                        g[x].append(x - 1)  # 「同一行左一列」是 x - 1

        match = [-1] * (m * n)  # match[j]：右侧点 j 当前匹配的左侧点，-1 表示尚未匹配
        ans = 0  # ans 累计最大匹配数，也就是最少要删掉的 1 的个数
        for i in g.keys():  # 逐个左侧点做增广
            vis = set()  # 本轮的访问集合，每个左侧点重新开始
            ans += find(i)  # 增广成功则匹配数加一
        return ans  # 返回最大匹配数，即最少操作数
