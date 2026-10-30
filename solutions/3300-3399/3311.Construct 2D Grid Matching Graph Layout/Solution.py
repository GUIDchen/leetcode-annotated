# 题目：3311. 构造符合图结构的二维矩阵（Construct 2D Grid Matching Graph Layout）
# 思路：用度数判断矩阵形状并求出第一行——有度 1 即单行；无度 4 即两行（取角点及其同度数的邻居）；否则从角点沿「度数小于 4」的边界一路走到另一个角点。之后每行展开：当前行每个节点取第一个未访问的邻居，即为它正下方的格子。
# 复杂度：时间 O(n + m)，建图与逐行扫描各遍历邻接表一次；空间 O(n + m)，邻接表与访问标记的规模。
class Solution:  # LeetCode 约定的题解类
    def constructGridLayout(self, n: int, edges: List[List[int]]) -> List[List[int]]:  # n 为节点个数，edges 为无向边，返回还原出来的二维矩阵
        g = [[] for _ in range(n)]  # 邻接表：g[i] 存放节点 i 的所有邻居
        for u, v in edges:  # 逐条读入无向边
            g[u].append(v)  # u 的邻居加入 v
            g[v].append(u)  # v 的邻居加入 u，无向图双向都要存
        deg = [-1] * 5  # deg[d] 记录某个度数为 d 的节点，-1 表示不存在这种度数
        for x, ys in enumerate(g):  # x 是节点编号，ys 是它的邻居列表
            deg[len(ys)] = x  # 以度数作下标记下该节点；同度数取最后一个即可
        if deg[1] != -1:  # 存在度数为 1 的节点，图退化成链，矩阵只有一行
            row = [deg[1]]  # 单行矩阵，唯一元素就是这个端点
        elif deg[4] == -1:  # 没有度数为 4 的节点，矩阵只有两行
            x = deg[2]  # 取一个角点（度数 2）
            for y in g[x]:  # 在角点的邻居里找同行的另一个角点
                if len(g[y]) == 2:  # 度数也为 2，说明它同样是角点
                    row = [x, y]  # 两个角点组成长度为 2 的第一行
                    break  # 已找到，跳出查找
        else:  # 其余情况：矩阵至少 3 行 3 列，存在度数为 4 的内部节点
            x = deg[2]  # 从某个角点（度数 2）出发
            row = [x]  # 角点是第一行第一列
            pre = x  # pre 记录上一个节点，避免走回头路
            x = g[x][0]  # 先沿一条边移动到相邻节点
            while len(g[x]) > 2:  # 只要还不是角点（度数大于 2），就继续沿边界前进
                row.append(x)  # 当前边界节点加入第一行
                for y in g[x]:  # 在邻居中挑选下一步
                    if y != pre and len(g[y]) < 4:  # 不能回头；度数小于 4 说明仍在边界上（度数为 4 会走进内部）
                        pre = x  # 前驱更新为当前节点
                        x = y  # 移动到下一个边界节点
                        break  # 找到就跳出内层循环
            row.append(x)  # 最后一个角点也要加入第一行

        ans = [row]  # 矩阵以第一行初始化
        vis = [False] * n  # 标记节点是否已放进矩阵
        for _ in range(n // len(row) - 1):  # 剩余行数 = 总行数 - 1，逐行向下构造
            for x in row:  # 先把当前行的节点全部标记为已使用
                vis[x] = True  # 标记当前节点
            nxt = []  # 待生成的下一行
            for x in row:  # 当前行每个节点各找一个向下的邻居
                for y in g[x]:  # 遍历它的邻居
                    if not vis[y]:  # 第一个未使用的邻居就是它正下方的节点
                        nxt.append(y)  # 按列顺序收集，保持与上一行列对齐
                        break  # 每个节点只需一个向下的邻居，找到即停
            ans.append(nxt)  # 下一行加入答案
            row = nxt  # 迭代：把下一行当作新的当前行
        return ans  # 返回构造出的二维矩阵
