# 题目：749. 隔离病毒（Contain Virus）
# 核心思路：每轮 DFS 找出所有病毒连通块并统计各自的威胁边界与所需防火墙数，隔离边界最大的块，其余块向外扩散一格，直到没有新感染。
# 时间复杂度：O((mn)^2)，每轮遍历全图做 DFS，最多 mn 轮；空间复杂度：O(mn)，访问标记与各块坐标集合。
class Solution:  # LeetCode 约定的题解类
    def containVirus(self, isInfected: List[List[int]]) -> int:  # isInfected：0 未感染、1 已感染的网格，直接在原网格上模拟
        def dfs(i, j):  # 内部闭包：遍历 (i, j) 所在的整块病毒，同时记录边界与建墙数
            vis[i][j] = True  # 标记已访问，防止重复搜索
            areas[-1].append((i, j))  # 把格子坐标追加到当前（最后加入的）病毒块
            for a, b in [[0, -1], [0, 1], [-1, 0], [1, 0]]:  # 枚举左右下上四个方向
                x, y = i + a, j + b  # 计算邻居坐标
                if 0 <= x < m and 0 <= y < n:  # 邻居必须落在网格内
                    if isInfected[x][y] == 1 and not vis[x][y]:  # 邻居是未访问的感染格，属于同一块
                        dfs(x, y)  # 递归深入，遍历连通部分
                    elif isInfected[x][y] == 0:  # 邻居是空地：会被这一块传染，需要在此建墙
                        c[-1] += 1  # 这个方向贡献一段防火墙
                        boundaries[-1].add((x, y))  # 用集合去重，同一片空地只算一次威胁

        m, n = len(isInfected), len(isInfected[0])  # 记录行列数，供闭包与主循环使用
        ans = 0  # 累计需要的防火墙数量
        while 1:  # 每轮先分析所有病毒块，再决定隔离谁、谁继续扩散
            vis = [[False] * n for _ in range(m)]  # 每轮重新初始化访问标记
            areas = []  # 本轮的病毒块格子列表
            c = []  # 本轮各病毒块的防火墙数量
            boundaries = []  # 本轮各病毒块的威胁空地集合
            for i, row in enumerate(isInfected):  # 逐行扫描网格
                for j, v in enumerate(row):  # 逐列扫描
                    if v == 1 and not vis[i][j]:  # 遇到未访问的感染格，说明发现了一个新病毒块
                        areas.append([])  # 为新块准备格子列表
                        boundaries.append(set())  # 为新块准备威胁集合
                        c.append(0)  # 为新块准备防火墙计数
                        dfs(i, j)  # DFS 填满上面三个容器
            if not areas:  # 没有任何病毒块，说明已经全部隔离或清除
                break  # 结束模拟
            idx = boundaries.index(max(boundaries, key=len))  # 取边界规模最大的块；index 返回它第一次出现的下标
            ans += c[idx]  # 隔离这一块消耗的防火墙数计入答案
            for k, area in enumerate(areas):  # 逐个处理每一块
                if k == idx:  # 被选中的块执行隔离
                    for i, j in area:  # 遍历该块的所有格子
                        isInfected[i][j] = -1  # 标记为已隔离，后续既不算病毒也不会再扩散
                else:  # 其他块继续向外扩散
                    for i, j in area:  # 遍历该块的所有格子
                        for a, b in [[0, -1], [0, 1], [-1, 0], [1, 0]]:  # 枚举四个相邻方向
                            x, y = i + a, j + b  # 计算邻居坐标
                            if 0 <= x < m and 0 <= y < n and isInfected[x][y] == 0:  # 邻居在网格内且是空地
                                isInfected[x][y] = 1  # 空地被感染，下一轮算作新的病毒格
        return ans  # 返回累计的防火墙数量
