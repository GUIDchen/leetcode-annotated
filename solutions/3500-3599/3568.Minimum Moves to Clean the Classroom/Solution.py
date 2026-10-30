# 题目：3568. 清理教室的最少移动（Minimum Moves to Clean the Classroom）
# 思路：状态 BFS。状态由 (行, 列, 剩余体力, 尚未清理的垃圾掩码) 组成，从起点 S 逐层扩展；走到 R 把体力重置为 energy，其余格子消耗 1 点体力，走到 L 则清掉对应的一位掩码，体力耗尽的状态直接丢弃；最早出现掩码为 0 的那一层就是最少移动次数。
# 时间复杂度：O(m * n * energy * 2^L)，每个状态扩展 4 个方向；空间复杂度：O(m * n * energy * 2^L)，即访问标记数组的规模。
class Solution:  # LeetCode 约定的题解类
    def minMoves(self, classroom: List[str], energy: int) -> int:  # classroom：教室网格；energy：初始体力；返回清理全部垃圾的最少移动次数，无法完成时返回 -1
        m, n = len(classroom), len(classroom[0])  # 教室的行数与列数
        d = [[0] * n for _ in range(m)]  # d[i][j] 记录格子 (i,j) 上垃圾的编号，用作状态掩码的位下标
        x = y = cnt = 0  # x、y 记录起点坐标，cnt 统计垃圾堆数
        for i, row in enumerate(classroom):  # 逐行扫描教室
            for j, c in enumerate(row):  # 逐列扫描每个字符
                if c == "S":  # 找到起点
                    x, y = i, j  # 记录起点坐标
                elif c == "L":  # 找到一堆垃圾
                    d[i][j] = cnt  # 给这堆垃圾分配一个位编号
                    cnt += 1  # 垃圾计数加一
        if cnt == 0:  # 教室里没有垃圾，不需要移动
            return 0  # 直接返回 0
        vis = [  # 访问标记的四个维度依次是行、列、剩余体力、未清理垃圾掩码
            [[[False] * (1 << cnt) for _ in range(energy + 1)] for _ in range(n)]  # 为每个格子生成 [剩余体力][掩码] 的二维布尔表
            for _ in range(m)  # 行数为 m，至此访问标记构建完成
        ]  # 访问标记列表收尾
        q = [(x, y, energy, (1 << cnt) - 1)]  # 起点入队，掩码全 1 表示所有垃圾都还没清理
        vis[x][y][energy][(1 << cnt) - 1] = True  # 标记起点状态已访问
        dirs = (-1, 0, 1, 0, -1)  # 方向数组，相邻两项组成上下左右的行列偏移
        ans = 0  # 记录已经走过的步数，也就是 BFS 的层数
        while q:  # 按层向外扩展，直到队列为空
            t = q  # t 是当前层的全部状态
            q = []  # 清空队列，用来收集下一层的状态
            for i, j, cur_energy, mask in t:  # 逐个处理当前层的状态
                if mask == 0:  # 掩码为 0 表示所有垃圾都已清理
                    return ans  # 当前层数即最少移动次数
                if cur_energy <= 0:  # 体力已耗尽，无法再走动
                    continue  # 丢弃该状态
                for k in range(4):  # 枚举四个方向
                    x, y = i + dirs[k], j + dirs[k + 1]  # 计算相邻格子的坐标
                    if 0 <= x < m and 0 <= y < n and classroom[x][y] != "X":  # 越界或撞上障碍物 X 都不能走
                        nxt_energy = (  # 新体力：走到 R 重置为 energy，其余格子消耗 1 点
                            energy if classroom[x][y] == "R" else cur_energy - 1  # 条件表达式的真分支与假分支
                        )  # 体力计算结束
                        nxt_mask = mask  # 新掩码先沿用当前值
                        if classroom[x][y] == "L":  # 目标格是一堆垃圾
                            nxt_mask &= ~(1 << d[x][y])  # 清掉该垃圾对应的位，表示已经清理
                        if not vis[x][y][nxt_energy][nxt_mask]:  # 新状态没访问过才允许入队
                            vis[x][y][nxt_energy][nxt_mask] = True  # 标记新状态已访问
                            q.append((x, y, nxt_energy, nxt_mask))  # 把新状态加入下一层
            ans += 1  # 一层扩展完，步数加一
        return -1  # 队列耗尽仍未清完，说明无法完成
